/**
 * This program convert WAV files to mp3 in C++14
 *
 *
 *  @author Ali Valizadeh
 *  @date   July 2019
 *
 */

#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <experimental/filesystem>
#include "wav_to_mp3.hpp"
#include "wavFileHandler.hpp"
#ifdef LINUX
#include <sys/types.h>
#include <dirent.h>
#endif
#include <lame/lame.h>

using namespace std;

string Wav_to_mp3_worker::convert_name(string wav)
{
    for(string s:{".wav", ".Wav", ".WAV"}){
        size_t found = wav.rfind(s);
        if (found != string::npos){
            wav.replace (found, 4, ".mp3");
            return wav; 
        }
    }
    return "";
}
vector<string> Converter::get_file_lists()
{
    cout << "Starting file_list\n";
    vector<string> v;
    if (__cplusplus == 201703L) {
        for(auto& entry: experimental::filesystem::directory_iterator(path)){
            v.push_back(entry.path().filename());
            if(verbose) cout << "list file " << entry.path().filename();
        }
    }else{
#ifdef LINUX
        cout << "Get file_list\n";
        DIR *dir;
        struct dirent *it;
        dir = opendir(path.c_str());
        if(dir != NULL ){
            while((it = readdir(dir)) != NULL) {
               if(strcmp(it->d_name, ".") != 0 && strcmp(it->d_name, "..") != 0){
                   v.push_back(string(it->d_name));
                   if(verbose) cout << "list file " << it->d_name << endl;
               }
            }
            closedir(dir);
            if(v.size() == 0){
            	cout << "There is not any file in the path: " << path << endl;
            }
        }
        else{
             cout << "Can not open path: " << path << endl;
        }
        return v;
#else // for Windows

    WIN32_FIND_DATA fdFile;
    HANDLE hFind = NULL;
    char sPath[2048];

    sprintf(sPath, "%s\\*.*", path);

    if((hFind = FindFirstFile(sPath, &fdFile)) == INVALID_HANDLE_VALUE){
         cout << "Can not open path: " << path << endl;
         return v;
    }

    do
    {
        if(strcmp(fdFile.cFileName, ".") != 0
                && strcmp(fdFile.cFileName, "..") != 0)
        {
            if(!(fdFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)){
                 v.push_back(fdFile.cFileName);
                 if(verbose) cout << "list file " << fdFile.cFileName << endl;
            }
        }
    }
    while(FindNextFile(hFind, &fdFile));

    FindClose(hFind);
    if(v.size() == 0){
        cout << "There is not any file in the path: " << path << endl;

    return v;
#endif
    }
}

void Wav_to_mp3_worker::converting(string a_wav, string a_mp3)
{
	int read, write;
	const int PCM_SIZE = 8192;
	const int MP3_SIZE = 8192;
	short int pcm_buffer[PCM_SIZE*2];
	unsigned char mp3_buffer[MP3_SIZE*2];
	lame_t lameHandle = NULL;

	cout << "CONVERTING......" << a_wav << " -> " << a_mp3 << endl;

#ifdef LINUX
	string f_wav = path + "/" + a_wav;
	string f_mp3 = path + "/" + a_mp3;
#else // for Windows
	string f_wav = path + "\\" + a_wav;
	string f_mp3 = path + "\\" + a_mp3;
#endif

	wavHdrSt wavHdr;
	WavFileHandler waveHandler;
	if(waveHandler.parseWavFile(f_wav.c_str() ) )
	{
		wavHdr = waveHandler.getWavHeader();
	}
	else{
		return;
	}

	lameHandle = lame_init();
	if(lameHandle == NULL){
		cout << "File " <<  f_wav << ": lame_init fails" << endl;
		return;
	}
	lame_set_num_channels(lameHandle, wavHdr.NumChannels);
	lame_set_quality(lameHandle, 3);
	lame_set_in_samplerate(lameHandle, wavHdr.sampleRate);
	lame_set_VBR(lameHandle, vbr_rh);

	if(lame_init_params(lameHandle) == -1){
		cout << "File: " << f_wav << ": lame_init fails" << endl;
		return;
	}

	FILE *pcm = fopen(f_wav.c_str(), "rb");
	if(pcm == NULL){
		cout << "File: " << f_wav << ": open error" << endl;
		return;
	}
	FILE *mp3 = fopen(f_mp3.c_str(), "wb");
	if(mp3 == NULL){
		cout << "File: " << f_mp3 << ": open error" << endl;
		return;
	}

	do {
		read = fread(pcm_buffer, 2*sizeof(short int), PCM_SIZE, pcm);
		if (read == 0) // flush
			write = lame_encode_flush(lameHandle, mp3_buffer, MP3_SIZE);
		else{
			if (wavHdr.NumChannels == 1)
			{
				write = lame_encode_buffer(lameHandle, pcm_buffer, pcm_buffer, read*2 , mp3_buffer, MP3_SIZE);
			}
			else
			{
				write = lame_encode_buffer_interleaved(lameHandle, pcm_buffer, read, mp3_buffer, MP3_SIZE);
			}
			if (write < 0)
			{
				cout << "File " <<  f_mp3 << ": write error" << endl;				
				remove(f_mp3.c_str());
				return;
			}
		}
			//write = lame_encode_buffer_interleaved(lame, pcm_buffer, read, mp3_buffer, MP3_SIZE);
		fwrite(mp3_buffer, write, 1, mp3);
	} while (read != 0);

	lame_close(lameHandle);
	fclose(mp3);
	fclose(pcm);
}
