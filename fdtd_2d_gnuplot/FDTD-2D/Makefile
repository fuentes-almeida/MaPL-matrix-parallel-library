CCOMP=g++		#compilador
CLINK=g++		#linkeo
LFLAGS= -Wall -g	#bandera de debuggeo
CFLAGS=  -c	#banderas de compilacion
EXEC=ejecutable
OBJDIR:=obj
CFILEDIR:=src
BINDIR:=bin
CFILES:=$(wildcard $(CFILEDIR)/*.cpp)
LIBS:=$(wildcard $(CFILEDIR)/*.hpp)
OBJS:=$(patsubst $(CFILEDIR)/%.cpp,$(OBJDIR)/%.o,$(CFILES))
DIREXEC:=$(addprefix $(BINDIR)/,$(EXEC))

$(DIREXEC): $(OBJS) $(LIBS)
	$(CCOMP)  $(LFLAGS) $(OBJS) -o $@ 

$(OBJDIR)/%.o: $(CFILEDIR)/%.cpp $(LIBS)
	$(CCOMP) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJS) $(DIREXEC) 

run:
	./bin/ejecutable

	
