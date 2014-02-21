CXXFLAGS += -g -std=c++0x -Wall -pedantic
LIBS     += -lpthread

i2cTest: i2cTest.o i2c.o
	$(CXX) $(CXXFLAGS) $^ $(LIBS) -o $@

signalTest: signalTest.o
	$(CXX) $(CXXFLAGS) $^ $(LIBS) -o $@

gpoTest: gpoTest.o gpio.o
	$(CXX) $(CXXFLAGS) $^ $(LIBS) -o $@

.PHONY: clean
clean:
	rm -f *.o

