CXXFLAGS += -g -std=c++0x -Wall -pedantic
LIBS     += -lpthread

scrolledLedMatrixTest: scrolledLedMatrixTest.o scrolledLedMatrix.o ledMatrix.o i2c.o
	$(CXX) $(CXXFLAGS) $^ $(LIBS) -o $@

ledMatrixTest: ledMatrixTest.o ledMatrix.o i2c.o
	$(CXX) $(CXXFLAGS) $^ $(LIBS) -o $@

signalTest: signalTest.o
	$(CXX) $(CXXFLAGS) $^ $(LIBS) -o $@

gpoTest: gpoTest.o gpio.o
	$(CXX) $(CXXFLAGS) $^ $(LIBS) -o $@

.PHONY: clean
clean:
	rm -f *.o

