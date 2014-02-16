#include "gpio.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <stdexcept>

int main( int argc, char *argv[] )
{
   const char *pin = "P8.10";
   if( argc == 2 )
      pin = argv[1];

   std::cout << "Starting testing " << pin << '\n';
   GPO gpio( pin );
   for( int k = 0; k < 5; ++k )
   {
      std::cout << "On\n";
      gpio.set( 1 );
      std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );
      std::cout << "Off\n";
      gpio.set( 0 );
      std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );
   }

   std::cout << "Exit\n";
}
