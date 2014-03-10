CXXFLAGS += -g -std=c++0x -Wall -pedantic
LIBS     += -lpthread

all: gpiTest gpoTest

gpiTest: gpiTest.o gpio.o
	$(CXX) $(CXXFLAGS) $^ $(LIBS) -o $@

gpoTest: gpoTest.o gpio.o
	$(CXX) $(CXXFLAGS) $^ $(LIBS) -o $@

.PHONY: clean
clean:
	rm -f gpiTest gpoTest *.o

