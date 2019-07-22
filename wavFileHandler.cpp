
/**
 * This program convert WAV files to mp3 in C++14
 *
 *
 *  @author Ali Valizadeh
 *  @date   July 2019
 *
 */

#include <iostream>
#include <string.h>
#include <stdio.h>
#include "wavFileHandler.hpp"

using namespace std;

bool WavFileHandler::parseWavFile(const char *fileName)
{
	bool retVal = false;
	
	FILE *fp = fopen(fileName, "rb");
	if(fp == NULL)
	{
		cout << "Error in opening of file: " << fileName << endl;
		retVal = false;
	}
	else if(checkHeader(fp))
	{
		fileSize = getFileSize(fp);
		if(fileSize != (wavHdr.chunkSize+8)){
			cout << "-----> ERROR in parsing of file: " << fileName << endl;
			retVal = false;
		}
		else{
			retVal = true;
		}
	}
	else{
		cout << "-----> ERROR in parsing of file: " << fileName << endl;
		retVal = false;
	}

	//printHeader();

	fclose(fp);
	
	return retVal;
}


// This function can be used to probe inside of the wave files
void WavFileHandler::printHeader()
{
   cout << "RIFF header     " << wavHdr.RIFF          << endl;
   cout << "Chunk size      " << wavHdr.chunkSize     << endl;
   cout << "WAVE header     " << wavHdr.WAVE          << endl;
   cout << "FMT             " << wavHdr.FMT           << endl;
   cout << "Subchunk1 size  " << wavHdr.subchunk1Size << endl;
   cout << "Audio format    " << wavHdr.AudioFormat   << endl;
   cout << "Num of chans    " << wavHdr.NumChannels   << endl;
   cout << "Samples per sec " << wavHdr.sampleRate    << endl;
   cout << "Bytes per sec   " << wavHdr.byteRate      << endl;
   cout << "Block align     " << wavHdr.blockAlign    << endl;
   cout << "Bits per sample " << wavHdr.bitsPerSample << endl;
   cout << "Subchunk2 ID    " << wavHdr.subchunk2ID   << endl;
   cout << "Subchunk2 size  " << wavHdr.subchunk2Size << endl;
}


int WavFileHandler::getFileSize(FILE *f)
{
   long int fSize = 0;
   fseek(f,0,SEEK_END);
   fSize=ftell(f);
   fseek(f,0,SEEK_SET);
   return fSize;
}


bool WavFileHandler::checkHeader(FILE *f){
	int16_t checkVal = 0;
	
	fread(&(wavHdr.RIFF),1,4,f); wavHdr.RIFF[4] = '\0';
	
	fread(&(wavHdr.chunkSize),sizeof(int32_t),1,f);
	
	fread(&(wavHdr.WAVE),1,4,f); wavHdr.WAVE[4] = '\0';
	
	fread(&(wavHdr.FMT),1,4,f); wavHdr.FMT[4]='\0';
	
	fread(&(wavHdr.subchunk1Size),sizeof(int32_t),1,f);
	
	fread(&(wavHdr.AudioFormat),sizeof(int16_t),1,f);
	
	fread(&(wavHdr.NumChannels),sizeof(int16_t),1,f);
	
	fread(&(wavHdr.sampleRate),sizeof(int32_t),1,f);
	
	fread(&(wavHdr.byteRate),sizeof(int32_t),1,f);
	
	fread(&(wavHdr.blockAlign),sizeof(int16_t),1,f);
	
	fread(&(wavHdr.bitsPerSample),sizeof(int16_t),1,f);
	
	fread(&(wavHdr.subchunk2ID),1,4,f);wavHdr.subchunk2ID[4] = '\0';
	
	fread(&(wavHdr.subchunk2Size),sizeof(int32_t),1,f);

	if (0 != strcmp(wavHdr.RIFF, "RIFF"))
	{
	 checkVal = -1;
	}
	if (0 != strcmp(wavHdr.WAVE, "WAVE"))
	{
	 checkVal = -2;
	}
	if (0 != strcmp(wavHdr.FMT, "fmt "))
	{
	 checkVal = -3;
	}
	if (0 != strcmp(wavHdr.subchunk2ID, "data"))
	{
	 checkVal = -4;
	}
	if (16 != wavHdr.subchunk1Size)
	{
	 checkVal = -5;
	}
	if (1 != wavHdr.AudioFormat)
	{
	 checkVal = -6;
	}
	if ( 2 < wavHdr.NumChannels)
	{
	 checkVal = -7;
	}
	if (20 != wavHdr.chunkSize - wavHdr.subchunk1Size - wavHdr.subchunk2Size)
	{
	 checkVal = -8;
	}

	if(checkVal < 0)
	{
		return false;
	}
	else
		return true;
}

