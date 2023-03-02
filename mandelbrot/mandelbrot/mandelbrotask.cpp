#include "mandelbrot.h"
#include "mandelbrotask.h"
#include "mandelbrotfarm.h"
#include <mutex>
#include <queue>
#include <vector>
#include <thread>


void Farm::add_task(Task* task) {

	aqueue.push(task);

}

void Farm::run() {

	const uint8_t CPU = std::thread::hardware_concurrency();

	std::vector<std::thread*>athread;

	for (int cont = 0; cont < CPU; cont++) {

		athread.push_back(new std::thread([&] {
			while (true) {
				if (aqueue.empty())
					return;

				farm_m.lock();
				Task* t = aqueue.front();
				aqueue.pop();
				farm_m.unlock();

				t->run();
				delete t;
			}
		
			}));

		athread[cont]->join();

	

	}

}