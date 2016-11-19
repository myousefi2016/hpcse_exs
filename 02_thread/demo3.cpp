    #include <stdio.h>  
    #include <stdlib.h>  
    #include <iostream> // std::cout  
    #include <thread>   // std::thread  
    static const int num_threads = 10;  
    //This function will be called from a thread  
    void call_from_thread(int tid) {  
        std::cout << "Launched by thread " << tid << std::endl;  
    }  
    int main() {  
        std::thread t[num_threads];  
        //Launch a group of threads  
        for (int i = 0; i < num_threads; ++i) {  
            t[i] = std::thread(call_from_thread, i);  
        }  
        std::cout << "Launched from the mainn";  
        //Join the threads with the main thread  
        for (int i = 0; i < num_threads; ++i) {  
            t[i].join();  
        }  
        return 0;  
    }  