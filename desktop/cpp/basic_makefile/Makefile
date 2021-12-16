# Achmadi's Simple Makefile

# Make macro definition
# to define a macro
##### MACRO = SOMETHING
# to call a macro
##### $(MACRO)

# specify final app output of the object
PROJECT = hallo

# spesify C/C++ Sources code ( *.c or *.cpp )
CCSRC= hello.c test_1.c
CXXSRC=

# spesify C/C++ Include folder (*.h)
CCINC=
CXXINC=

# default C/C++ compiler
CC = gcc
CXX = g++

# default C/C++ Objects
CCOBJ= $(CCSRC:%.c=%.o)
CXXOBJ=$(CXXSRC:%.c=%.o)

# default C/C++ Objects (Alternative)
# CCOBJA= $(CCSRC:.c=.o)
# CXXOBJA=$(CXXSRC:.c=.o)

# default C/C++ flags
CCFLAG= -Wall
CXXFLAG= -Wall

#default C/C++ defines
CCDEFINE=
CXXDEFINE=

# default C/C++ libs
CCLIB=
CXXLIB=

# Compiling rules

# Compiling general rules
##### $(TARGET): $(SOURCES)
##### [TAB] $(COMPILING_COMMANDS)

$(PROJECT):$(CCOBJ)
	$(CC) $(CCFLAG) $(CCOBJ) -o $(PROJECT)
	
# Compiling inference rule. One statement for each file sources
##### $< means source filename at this step
##### $@ means target filename at this step
##### %.c means for each *.c file per step
##### %.o means for each *.o file per step.
	
%.o: %.c
	$(CC) $(CCFLAG) -c $< -o $@
	
# alternative. This all means has same meaning like above

# $(PROJECT):$(CCOBJA)
# 	$(CC) $(CCFLAG) $(CCOBJA) -o $(PROJECT)
# 	
# .c.o:
# 	$(CC) $(CCFLAG) -c $< -o $@

# cleaning process. Use this for remove all builded objects and rebuild entire projects
clean: 
	rm *.o $(PROJECT)