#pragma once

#ifndef MENDELBROTASK_H
#define MENDELBROTASK_H



#include "mandelbrot.h"
#include <queue>
#include <thread>
#include <mutex>
#include <complex>

class Farm{

public:

	std::mutex farm_m;

	void add_task(Task *task);

	void run();


private:

	std::queue<Task*>aqueue;



};

#endif // !MENDELBROTASK_H