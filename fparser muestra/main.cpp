#include "fparser/fparser.hh"
#include <iostream>
using namespace std;
int main(){
	double x[] = {2.0};
	FunctionParser fparser;
	fparser.Parse( "x^2 + sin(x)", "x" );
	double y = fparser.Eval(x);
	cout << "y = " << y << endl << endl;
	return 0;
}
