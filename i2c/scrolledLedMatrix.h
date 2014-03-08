#ifndef SCROLLEDLEDMATRIX_H_INCLUDED
#define SCROLLEDLEDMATRIX_H_INCLUDED
#include "ledMatrix.h"
#include "../utilities/signal.h"
#include <string>
#include <thread>

class ScrolledLedMatrix
{
public:
   ScrolledLedMatrix( const char *dev, int address );
   void setText( const char *txt, int color, int numLoops );
   bool isRunning() const;
   void wait();
   void stop();

private:
   static const int BUF_SIZE = 2 * LedMatrix::BUF_SIZE;
   uint8_t charBuffer[LedMatrix::BUF_SIZE];
   uint8_t buffer[BUF_SIZE];
   LedMatrix lm;
   std::string text;
   std::thread thread;
   Signal      sig;

   int bufferChar( char c, int color, int dotWidth );
   void doLoops( int color, int numLoops );
};

#endif

