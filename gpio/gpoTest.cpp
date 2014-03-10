/*
Copyright (c) 2014, Peter G. Baum
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "gpio.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <stdexcept>

void set( GPO *g, bool val )
{
   std::cout << (val ? "On\n" : "Off\n");
   g->set( val );
   std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );
}

void doIt( const char *pin )
{
   {
      std::cout << "Init with High\n";
      GPO gpio( pin, true );
      std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );
      set( &gpio, 0 );
      set( &gpio, 1 );
      set( &gpio, 0 );
   }
   std::this_thread::sleep_for( std::chrono::milliseconds( 2000 ) );
   {
      std::cout << "Init with Low\n";
      GPO gpio( pin, false );
      std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );
      set( &gpio, 1 );
      set( &gpio, 0 );
      set( &gpio, 1 );
   }
}

int main( int argc, char *argv[] )
{
   const char *pin = "USR0";
   if( argc == 2 )
      pin = argv[1];

   std::cout << "Starting testing " << pin << '\n';
   try
   {
      doIt( pin );
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


   std::cout << "Exit\n";
}
