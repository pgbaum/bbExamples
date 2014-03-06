#include "scrolledLedMatrix.h"
#include <cassert>

ScrolledLedMatrix::ScrolledLedMatrix( const char *dev, int address )
      : lm( dev, address )
{
}

int ScrolledLedMatrix::bufferChar( char c, int color, int dotWidth )
{
   const int charSize = lm.setChar( c, color );
   const uint8_t *p = lm.getBuffer();
   std::copy( p, p + charSize * dotWidth, charBuffer );
   return charSize;
}

void ScrolledLedMatrix::doLoops( int color, int numLoops )
{
   const int dotWidth = lm.getDotWidth();
   const int xRes = lm.getXResolution();
   assert( 2 * xRes * dotWidth == BUF_SIZE );
   int nextCharPos = 0;
   int nextChar = 0;
   int charSize = 0;
   for( ; nextChar < (int)text.size(); ++nextChar )
   {
      charSize = bufferChar( text[nextChar], color, dotWidth );
      // copy to output buffer
      if( nextCharPos + charSize <= 2 * xRes )
      {
         std::copy( charBuffer, charBuffer + charSize * dotWidth,
               buffer + nextCharPos * dotWidth );
         nextCharPos += charSize + 1;
      }
      else
         break;
   }

   while( numLoops > 0 )
   {
      lm.setBuffer( buffer );
      lm.displayBuffer();

      // shift by one dot
      std::copy( buffer + dotWidth, buffer + BUF_SIZE, buffer );
      std::fill( buffer + BUF_SIZE - dotWidth, buffer + BUF_SIZE, 0 );

      if( --nextCharPos + charSize <= 2 * xRes )
      {
         std::copy( charBuffer, charBuffer + charSize * dotWidth,
               buffer + nextCharPos * dotWidth );
         nextCharPos += charSize + 1;
         if( ++nextChar >= (int)text.size() )
         {
            nextChar = 0;
            --numLoops;
         }
         charSize = bufferChar( text[nextChar], color, dotWidth );
      }
      if( sig.wait( std::chrono::milliseconds( 100 ) ) )
         return;
   }

   // scroll until display is clear
   for( ; nextCharPos > 0; --nextCharPos )
   {
      lm.setBuffer( buffer );
      lm.displayBuffer();

      // shift by one dot
      std::copy( buffer + dotWidth, buffer + BUF_SIZE, buffer );
      std::fill( buffer + BUF_SIZE - dotWidth, buffer + BUF_SIZE, 0 );

      if( sig.wait( std::chrono::milliseconds( 100 ) ) )
         return;
   }
}

void ScrolledLedMatrix::setText( const char *txt, int color, int numLoops )
{
   if( isRunning() )
      stop();

   text = txt;
   lm.clearBuffer();
   std::fill( buffer, buffer + BUF_SIZE, 0 );
   if( text.empty() )
   {
      lm.displayBuffer();
      return;
   }

   thread = std::thread( [=] { doLoops( color, numLoops ); } );
}

bool ScrolledLedMatrix::isRunning() const
{
   return thread.joinable();
}

void ScrolledLedMatrix::wait()
{
   thread.join();
}

void ScrolledLedMatrix::stop()
{
   sig.signal();
   thread.join();
   sig.reset();
}

