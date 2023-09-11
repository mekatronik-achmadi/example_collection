APP		= calc

CXXSRC	= main.cpp calc.cpp
CXXINC	= -I./

CXX		= g++
CXXOBJ	= $(CXXSRC:%.cpp=%.o)
CXXFLAG	= -Wall -g3
CXXDEFS	=
CXXLIBS	=`pkg-config gtkmm-3.0 --cflags --libs`
CXXOPTS	= $(CXXFLAG) $(CXXINC) $(CXXDEFS) $(CXXLIBS)

all: $(APP)

$(APP): $(CXXOBJ)
	$(CXX) $(CXXOPTS) $(CXXOBJ) -o $(APP)

%.o: %.cpp
	$(CXX) $(CXXOPTS) -c $< -o $@

clean:
	rm -vf *.o $(APP)

.PHONY: clean

