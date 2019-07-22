/**
 * This program convert WAV files to mp3 in C++14
 *
 *
 *  @author Ali Valizadeh
 *  @date   July 2019 
 *
 */

#include<iostream>
#include"wav_to_mp3.hpp"

using namespace std;

int main(int argc, char *argv[])
{
   if (argc != 2)
   {
      cout << "usage: " << argv[0] << " pathname" << endl;
      return 1;
   }

   Converter C;
   C.cpp_version();
   C.set_verbose(0);
   C.set_path(argv[1]);
   C.converting();
   return 0;
}
