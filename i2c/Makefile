CXXFLAGS += -g -std=c++0x -Wall -pedantic
LIBS     += -lpthread

all: scrolledLedMatrixTest ledMatrixTest

scrolledLedMatrixTest: scrolledLedMatrixTest.o scrolledLedMatrix.o ledMatrix.o i2c.o
	$(CXX) $(CXXFLAGS) $^ $(LIBS) -o $@

ledMatrixTest: ledMatrixTest.o ledMatrix.o i2c.o
	$(CXX) $(CXXFLAGS) $^ $(LIBS) -o $@

.PHONY: clean
clean:
	rm -f scrolledLedMatrixTest ledMatrixTest *.o

