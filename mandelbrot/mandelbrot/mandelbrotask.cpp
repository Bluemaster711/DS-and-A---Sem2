#include "mandelbrot.h"
#include "mandelbrotask.h"
#include "mandelbrotfarm.h"
#include <mutex>
#include <queue>
#include <vector>
#include <thread>


void Farm::add_task(Task* task) {
	
	//add task to the queue
	aqueue.push(task);

}

void Farm::run() {


	//define cpu's
	const uint8_t CPU = std::thread::hardware_concurrency();

	//created vector to add threads too
	std::vector<std::thread*>athread;

	for (int cont = 0; cont < CPU; cont++) {

		//add thread to list
		athread.push_back(new std::thread([&] {
			while (true) {
				//return if no task's left
				if (aqueue.empty())
					return;

				//protect the shared queue - to avoid duplicate tasks
				farm_m.lock();
				//take the task
				Task* t = aqueue.front();
				//remove task
				aqueue.pop();
				//allow other threads to take a task
				farm_m.unlock();

				//run the tread
				t->run();
				delete t;
				
			}
		

			}));


		//join all threads
		athread[cont]->join();

	
	

	

	}

}