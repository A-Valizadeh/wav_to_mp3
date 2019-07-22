/**
 * This program convert WAV files to mp3 in C++14
 *
 *
 *  @author Ali Valizadeh
 *  @date   July 2019
 *
 */

#ifndef WAV_TO_MP3_H
#define WAV_TO_MP3_H

#include <iostream>
#include <vector>
#include <deque>
#include <thread>
#include <mutex>
#include <condition_variable>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define WIN32
#else
#define LINUX
#endif

using namespace std;


/**
 *
 *  This class (Wav_queue) implements a queue for keeping wav file list.
 *  class methods: 
 *               (1) void fill(vector<string> in_items): This method is used to insert files to the queue
 *               (2) string pop(): This method is used to delete files from queue
 *               (3) size_t size(): Returns the size of queue
 *
 */
class Wav_queue {
    private:
        deque<string> items;
        mutex item_mutex;
    public:
        Wav_queue(){}
        void fill(vector<string> in_items){
            for(auto item:in_items)
                items.push_back(item);
        }
        size_t size(){ return items.size(); }
        string pop(){
            unique_lock<mutex> lock(item_mutex);
            if(items.empty()) return "";
            string front = items.front();
            items.pop_front();
            return front;
        }
};


/**
 *
 *  This class (Wav_to_mp3_worker) implements the actual conversion task from wav to mp3.
 *  class methods: 
 *               (1) Wav_to_mp3_worker(Wav_queue* in_queue, int in_id, string in_path): constructor
 *               (2) string convert_name(string wav): This method converts file extention from "Wav",
 *                               "wav" or "WAV" to "mp3" and returns the whole mp3 file name as a result.
 *               (3) void set_queue(Wav_queue* queue): By this method the queue of files which was made,
 *                                 is put inside of a member variable of type "Wav_queue" (queue class).
 *               (4) void start(): This method Starts a thread for converting one wav file to mp3.
 *                                  the callback funtion for thread is named working() which is another
 *                                  methods of this class (Wav_to_mp3_worker).
 *               (5) void wait_to_finish(): This method does a thread joining task and waits for the
 *                                  started thread in the start() method to be ended.
 *               (6) static void working(Wav_to_mp3_worker* obj): This method gets a file from the
 *                                  wav queue and does some checks and after that calles a function
 *                                  named "converting" which is a method of this class
 *                                  (Wav_to_mp3_worker) too.
 *               (7) void converting(string wav, string mp3): This method is the most important function
 *                                   to this project because it actually uses lame library and converts
 *                                   one wav file to mp3.
 *                                  
 *
 */
class Wav_to_mp3_worker {
    private:
        Wav_queue* wav_queue;
        thread worker_thread;
		string path;
        int verbose;
        int id;
    public:
        Wav_to_mp3_worker(Wav_queue* in_queue, int in_id, string in_path){ 
            wav_queue = in_queue;
            id = in_id;
			path = in_path;
            verbose = 0;
        }
        string convert_name(string wav);
        void converting(string wav, string mp3);
        void set_verbose(int in_verbose){ verbose = in_verbose; }
        void set_queue(Wav_queue* queue){ wav_queue = queue; }
        void wait_to_finish(){
            worker_thread.join();
        }
        void start(){
            worker_thread = thread(Wav_to_mp3_worker::working, this);
        }
        static void working(Wav_to_mp3_worker* obj){
            string wav_name;
            string mp3_name;
            if(obj->verbose) cout << "Start worker thread " << obj->id << endl;
            while(true){
                wav_name = obj->wav_queue->pop(); 
                if(obj->verbose) cout << "Get wav file "<< wav_name << endl;
                if(wav_name == "") break;
                mp3_name = obj->convert_name(wav_name);
                if(obj->verbose) cout << "To mp3 file "<< mp3_name << endl;
                if(mp3_name != "")
                    obj->converting(wav_name, mp3_name);
                else{
                    if(obj->verbose){
                                      if(wav_name != "." && wav_name != "..")
                                            cout << "Not wav file "<< wav_name << endl;
                    }
                }
            }
            if(obj->verbose) cout << "End worker thread " << obj->id << endl;
        }
};



/**
 *
 *  This class (Converter) is the most impotrant class for converting wav files to mp3 project.
 *  class methods: 
 *               (1) Converter(): constructor
 *               (2) Converter(string path): constructor which set the path for wav files
 *               (3) void set_verbose(int in_verbose):This method is set a member variable by which
 *                                                     we can get more printed result
 *               (4) void cpp_version(): This method prints the C++ standard version. 
 *                                       In this projet C++14 was used.
 *               (5) void set_path(string in_path): A method to set the path for wav files
 *               (6) int get_core_number(): This method returns number of cores available in the system
 *               (7) bool converting(): This method is the main routin for the conversion.
 *                       In this method, number of cores is got at first.
 *                       (the number of cores is computed by actual number of cores multiplied by a
 *                        factor: N*factor. This is done for reducing the wait times of the cores for 
 *                        io operations)
 *                       Then the wav files list is produced and inserted to the queue. 
 *                       After that, N*factor objects from class "Wav_to_mp3_worker" which is named
 *                       "Workers"is inastaced and their start() method is called to do the actual 
 *                       wav to mp3 conversion task.
 *                       At the end, the converting() method from "Converter" class, waits for all
 *                       workers to be finished.
 *
 */
class Converter {
    private:
        string path;
        int core_number;
        const int factor = 2; // Coefficient by which we always set number of cores greater than the number of threads to decrease wait time for each core. So, if a core is blocked by io operation, it can switch to another thread.
        Wav_queue wav_queue;
        int verbose;
    public:
        Converter():path{""}{}
        Converter(string path):path{path}{}
        void set_verbose(int in_verbose){
            verbose = in_verbose; 
        }
        void cpp_version(){
            if (__cplusplus == 201703L) cout << "C++17\n";
            else if (__cplusplus == 201402L) cout << "C++14\n";
            else if (__cplusplus == 201103L) cout << "C++11\n";
            else if (__cplusplus == 199711L) cout << "C++98\n";
            else cout << "pre-standard C++\n";
        }
        vector<string> get_file_lists();
	vector<string> file_list;
        int get_core_number(){ return thread::hardware_concurrency(); }
        void set_path(string in_path){ path = in_path; }
        bool converting(){
            core_number = get_core_number() * factor;
            file_list = get_file_lists();
            if(file_list.size() == 0){
            	return false;
            }
            wav_queue.fill(file_list);
            Wav_to_mp3_worker *workers[core_number]; 
            // Init Workers 
            if(verbose) cout << "Init Workers number: " << core_number << endl;
            for(auto i=0; i<core_number; ++i){
                workers[i] = new Wav_to_mp3_worker(&wav_queue, i, path);
            }
            // Start Workers 
            if(verbose) cout << "Start Workers .....\n";
            for(auto i=0; i<core_number; ++i){
                workers[i]->set_verbose(verbose);
		if(verbose) cout << "Start Worker" << i << endl;
                workers[i]->start();
            }
            // Wait for Workers to finish
            if(verbose) cout << "Wait for Workers to finish\n";
            for(auto i=0; i<core_number; ++i){
		if(verbose) cout << "Wait to Worker" << i << endl;
                workers[i]->wait_to_finish();
            }
            return true;
        }
        ~Converter(){}
};

#endif

