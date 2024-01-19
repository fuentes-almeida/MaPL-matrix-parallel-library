CCOMP=gcc		#compilador
CLINK=gcc		#linkeo
LFLAGS=-std=c99 	#bandera de debuggeo
CFLAGS=-std=c99	-c	#banderas de compilacion
EXEC=ejecutable
OBJDIR:=obj
CFILEDIR:=src
BINDIR:=bin
CFILES:=$(wildcard $(CFILEDIR)/*.c)
LIBS:=$(wildcard $(CFILEDIR)/*.h)
OBJS:=$(patsubst $(CFILEDIR)/%.c,$(OBJDIR)/%.o,$(CFILES))
DIREXEC:=$(addprefix $(BINDIR)/,$(EXEC))

$(DIREXEC): $(OBJS) $(LIBS)
	$(CCOMP) $(LFLAGS) -o $@ $(OBJS) -lm

$(OBJDIR)/%.o: $(CFILEDIR)/%.c $(LIBS)
	$(CCOMP) $(CFLAGS) $< -o $@

optimized:
	make CFLAGS="-O2 -Wall -std=c99 -c"; LFLAGS="-O2 -Wall"

debugging:
	make CFLAGS="-g -std=c99 -c"; LFLAGS="-g -std=c99 -o"

clean:
	rm -f $(OBJS) $(DIREXEC) 

run:
	./bin/ejecutable
	
help:
	@echo 	"Archivos a compilarse: obj/main.o obj/function.o obj/memo.o y bin/ejecutable\n Opciones de compilacion: make, make optimized, make debugging"
