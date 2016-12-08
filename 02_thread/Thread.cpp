#include <stdio.h>
#include <stdlib.h>

#include <iostream> // std::cout
#include <thread>   // std::thread
#include <vector>

void thread_task() {
    std::cout << "hello thread" << std::endl;
}

/*
 * ===  FUNCTION  =========================================================
 *         Name:  main
 *  Description:  program entry routine.
 * ========================================================================
 */
int main(int argc, const char *argv[])
{
	int nthreads = 4;
	std::vector<std::thread> Threads(nthreads);
	for(int i=0; i<nthreads; ++i) {
    	Threads[i] = std::thread([](){thread_task();});
	}
	for(auto & t:Threads) {
	    t.join();
	}

    return 0;
}  /* ----------  end of function main  ---------- */

