#include "scrolledLedMatrix.h"
#include <iostream>

void doIt()
{
   ScrolledLedMatrix sm( "/dev/i2c-1", 0x70 );
   sm.setText( "3 Times ", LedMatrix::GREEN, 3 );
   sm.wait();
   sm.setText( "3 seconds", LedMatrix::GREEN, 300 );
   std::this_thread::sleep_for( std::chrono::milliseconds( 3000 ) );
   sm.stop();
   sm.setText( "And again", LedMatrix::GREEN, 300 );
   std::this_thread::sleep_for( std::chrono::milliseconds( 3000 ) );
   sm.setText( " The End.", LedMatrix::GREEN, 1 );
   sm.wait();
}

int main( int argc, char *argv[] )
{
   try
   {
      if( argc == 2 )
      {
         ScrolledLedMatrix sm( "/dev/i2c-1", 0x70 );
         sm.setText( argv[1], LedMatrix::GREEN, 3 );
         sm.wait();
      }
      else
         doIt( );
   }
   catch( const std::exception &e )
   {
      std::cerr << "Error: " << e.what() << '\n';
      return 1;
   }
   catch( ... )
   {
      std::cerr << "Unknown error\n";
      return 1;
   }
}

