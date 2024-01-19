#include "Vector.hpp"
#include "Matrix.hpp"
#include "Function.hpp"
#include "LineSearchOptimizer.hpp"
#include "CholeskySolverLDLT.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include <math.h>
#include "Configuration.hpp"

using namespace std;

extern double c1,c2;


Vector LineSearchOptimizer::steepestDescentDirection(Function fx, Vector *x){

    c1 = 1e-4;
    c2 = 0.1;
    fx.gradient(x);
    int dimension =  fx.getDimension();

    Vector descentDirection = fx.gradient(x);

    return -descentDirection;    
}

Vector LineSearchOptimizer::newtonDescentDirection(Function fx, Vector *x){

    c1 = 1e-4;
    c2 = 0.9;
    Matrix hessian = fx.hessian(x);
    Matrix hessianCopy = hessian.duplicate();
    int length = x->getLength();
    Vector gradient = fx.gradient(x);
    Vector descentDirection(length);
    mySolver->load(&hessianCopy, &descentDirection, &gradient);
    mySolver->solve();

    return -descentDirection;
}

double LineSearchOptimizer::stepLengthSecondOrder(string condition, double stepLength, Vector x, Function fx, Vector descentDirection){

    Vector gradient = fx.gradient(&x);
    bool validConditionResult = validCondition(condition, stepLength, &x, fx, descentDirection, gradient);

    if (validConditionResult){
        return stepLength;
    }
    else{
        double phi01 = fx.evaluate(&x);
        double phi02 = gradient * descentDirection;

        Vector x_new = stepLength * descentDirection + x;

        double phia1 = fx.evaluate(&x_new);

        double stepLengthNew = (stepLength*stepLength * phi02)/(2.0 * (phi01 + phi02*stepLength - phia1));
        return stepLengthNew;
    }       
}

double LineSearchOptimizer::stepLengthThirdOrder(string condition, double stepLength, Vector x, Function fx, Vector descentDirection){

    Vector gradient = fx.gradient(&x);
    bool validConditionResult = validCondition(condition, stepLength, &x, fx, descentDirection, gradient);

    if (validConditionResult){
        return stepLength;
    }
    else{
        double phi01 = fx.evaluate(&x);
        double phi02 = gradient * descentDirection;
        double phi03 = descentDirection * (fx.hessian(&x) * descentDirection);

        double b=phi02;
        double c=0.5*phi03;

        Vector x_new = stepLength * descentDirection + x;
        double phi_alpha2 = fx.evaluate(&x_new);
        double d=(phi_alpha2-phi01-stepLength*phi02-0.5*stepLength*stepLength*phi03)/(stepLength*stepLength*stepLength);
        double stepLengthNew = (-c + sqrt(c*c - 3*b*d)) / (3*d);

        if (c*c-3*b*d<0) return stepLength;
        if (stepLengthNew>0) return stepLengthNew;
        else return stepLength;
    }
}

double LineSearchOptimizer::stepLengthBacktracking(string condition, double stepLength, Vector x, Function fx, Vector descentDirection){

    Vector gradient = fx.gradient(&x);
    bool validConditionResult = validCondition(condition, stepLength, &x, fx, descentDirection, gradient);

    if (validConditionResult){
        return stepLength;
    }
    else{
        double phi01 = fx.evaluate(&x);
        double phi02 = gradient * descentDirection;

        Vector x_new = stepLength * descentDirection + x;

        double phia1 = fx.evaluate(&x_new);

        double stepLengthNew = (stepLength*stepLength * phi02)/(2.0 * (phi01 + phi02*stepLength - phia1));

        int maxite=10,count=0,tracking=0,x1=2,x2=5,x3=3;
        double stepLengthBacktracking=stepLengthNew;
        while(validCondition(condition, stepLengthBacktracking, &x, fx, descentDirection, gradient) && count<maxite)
        {
            tracking++;
            if (tracking>x2)
            {
                stepLengthBacktracking=x3*stepLengthBacktracking;
                tracking=0;
            }
            else
                stepLengthBacktracking=stepLengthBacktracking/x1;
            count++;
        }
        if (count==10)
            return stepLengthNew;

        else
            return stepLengthBacktracking;
    }



}

bool LineSearchOptimizer::validWeakWolfeCondition(double stepLength, Vector *x, Function fx, Vector descentDirection, Vector gradient){

    double gradientInnerProduct = gradient * descentDirection;
    Vector x_new = stepLength * descentDirection + *x;
    double armijoLHS = fx.evaluate(&x_new);
    double armijoRHS = fx.evaluate(x) + c1*stepLength*gradientInnerProduct;

    double curvatureRHS = c2*gradientInnerProduct;

    Vector gradientNew = fx.gradient(&x_new);

    double curvatureLHS = gradientNew * descentDirection;

    bool armijoCondition = armijoLHS <= armijoRHS;
    bool curvatureCondition = curvatureLHS >= curvatureRHS;

    return armijoCondition && curvatureCondition;
}

bool LineSearchOptimizer::validStrongWolfeCondition(double stepLength, Vector *x, Function fx, Vector descentDirection, Vector gradient)
{
    double gradientInnerProduct = gradient * descentDirection;
    Vector x_new = stepLength * descentDirection + *x;
    double armijoLHS = fx.evaluate(&x_new);
    double armijoRHS = fx.evaluate(x) + c1*stepLength*gradientInnerProduct;

    double curvatureRHS = c2*gradientInnerProduct;

    Vector gradientNew = fx.gradient(&x_new);

    double curvatureLHS = gradientNew * descentDirection;

    bool armijoCondition = armijoLHS <= armijoRHS;
    bool curvatureCondition = fabs(curvatureLHS) <= fabs(curvatureRHS);

    return armijoCondition && curvatureCondition;
}

bool LineSearchOptimizer::validGoldsteinCondition(double stepLength, Vector *x, Function fx, Vector descentDirection, Vector gradient)
{
    double c=0.05;
    double gradientInnerProduct = gradient * descentDirection;
    Vector x_new = stepLength * descentDirection + *x;
    double goldsteinRHS1 = fx.evaluate(&x_new);
    double goldsteinLHS2 = goldsteinRHS1;

    double goldsteinLHS1 = fx.evaluate(x) + (1-c) * stepLength * gradient * descentDirection;
    double goldsteinRHS2 = fx.evaluate(x) + c * stepLength * gradient * descentDirection;

    bool goldsteinCondition1 = goldsteinLHS1 <= goldsteinRHS1;
    bool goldsteinCondition2 = goldsteinLHS2 <= goldsteinRHS2;

    return goldsteinCondition1 && goldsteinCondition2;
}

bool LineSearchOptimizer::validCondition(string condition, double stepLength, Vector *x, Function fx, Vector descentDirection, Vector gradient)
{
    bool validConditionResult = false;
    //Vector gradient = fx.gradient(x);

    if (condition == "WeakWolfeCondition"){
        validConditionResult = validWeakWolfeCondition(stepLength, x, fx, descentDirection, gradient);
    }
    if (condition == "StrongWolfeCondition"){
        validConditionResult = validStrongWolfeCondition(stepLength, x, fx, descentDirection, gradient);
    }
    if (condition == "GoldsteinCondition"){
        validConditionResult = validGoldsteinCondition(stepLength, x, fx, descentDirection, gradient);
    }

    return validConditionResult;
}