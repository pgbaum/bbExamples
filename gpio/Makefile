CXXFLAGS += -g -std=c++0x -Wall -pedantic
LIBS     += -lpthread

gpoTest: gpoTest.o gpio.o
	$(CXX) $(CXXFLAGS) $^ $(LIBS) -o $@

.PHONY: clean
clean:
	rm -f gpoTest *.o

