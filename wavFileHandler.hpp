
/**
 * This program convert WAV files to mp3 in C++14
 *
 *
 *  @author Ali Valizadeh
 *  @date   July 2019
 *
 */

#ifndef WAV_FILE_HANDLER_H
#define WAV_FILE_HANDLER_H

#include <stdint.h>

typedef struct
{
  char      RIFF[5];/*4+1 for trailing '\0'*/
  int32_t   chunkSize;     
  char      WAVE[5];/*4+1 for trailing '\0'*/
  char      FMT[5];/*4+1 for trailing '\0'*/
  int32_t   subchunk1Size;
  int16_t   AudioFormat;
  int16_t   NumChannels;
  int32_t   sampleRate;
  int32_t   byteRate;
  int16_t   blockAlign;
  int16_t   bitsPerSample;
  char      subchunk2ID[5];/*4+1 for trailing '\0'*/
  int32_t   subchunk2Size;
}wavHdrSt;

static const wavHdrSt EmptyHeader = {0};


/**
 *
 *  This class (WavFileHandler) implements all things neceessary for 
 *                              working with wav files in this project.
 *  class methods: 
 *               (1) WavFileHandler(): constructor
 *               (2) bool parseWavFile(const char *fileName): This method is the most important function
 *                              in this class that parses inputed wav file and checks its validity. 
 *                              This method calls other methods of the "WavFileHandler" class to does
 *                              its task. This method uses checkHeader(), getFileSize() and printHeader()
 *               (3) bool checkHeader(FILE *f): This method checks wav file header validity.
 *               (4) int32_t getFileSize(FILE *f): This method return size of wav file.
 *               (5) wavHdrSt getWavHeader(): This method returns header structure of 
 *
 */
class WavFileHandler {
	public:
			WavFileHandler() { wavHdr = EmptyHeader; fileSize = 0; }
			bool parseWavFile(const char *fileName);
			wavHdrSt getWavHeader() { return wavHdr; }
			void printHeader();
	private:
			bool checkHeader(FILE *f);
			int32_t getFileSize(FILE *f);
			int32_t fileSize;
			wavHdrSt wavHdr;

};

#endif
