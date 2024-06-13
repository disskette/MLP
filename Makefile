CC = g++ 
LDFLAGS = -g -std=c++11 -Wall -Werror -pedantic -lpthread 
SOURCES= neuron.hpp layer.hpp perceptron.hpp main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = MLP




$(EXECUTABLE): $(OBJECTS) $(LDLIBS)
	$(CXX) $(LDFLAGS) $(OBJECTS) $(LDLIBS) -o $@

.PHONY: clean
clean: 
	rm MLP main.o

.PHONY: distclean
distclean:
	$(EXECUTABLE)