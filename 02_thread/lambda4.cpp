    #include <iostream>  
    #include <thread>  
      

    int main(void) {  
      
        int i = 0;  
        std::thread t(  
                [&i]() {  
                    for (;;) {  
                        std::this_thread::sleep_for(std::chrono::seconds(1));  
                        i++;  
                    }  
                }  
        );  
      
        t.detach();  
      
        for (;;) {  
            for (;;) {  
                std::this_thread::sleep_for(std::chrono::seconds(1));  
                std::cout << "i = " << i << std::endl;  
            }  
        }  
      
        return 0;  
    }  