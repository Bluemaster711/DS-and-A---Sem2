// Race conditions example
// Adam Sampson <a.sampson@abertay.ac.uk>

#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <condition_variable>

#include "account.h"

// Import things we need from the standard library
using std::chrono::milliseconds;
using std::this_thread::sleep_for;
using std::cout;
using std::endl;
using std::thread;
using std::condition_variable;

typedef std::chrono::steady_clock the_clock;

condition_variable myvari;
Account bill;
std::mutex account_m;
bool bill_is_ready = false;
//std::mutex bill_m;

void adding() {
	std::cout << "running\n";
	for (int y = 0; y < 1000000; y++)
	{
		//std::lock_guard<std::mutex>guard(bill_m);
		sleep_for(milliseconds(500));
		{
			std::unique_lock<std::mutex>guard(account_m);

			//bill.account_m;
			bill.add(17, 29);
			bill_is_ready = true;

		}

		myvari.notify_all();
		//std::mutex::unlock;

	}
}

void consumer() {
	
	while(true)
		{
			std::unique_lock<std::mutex>lock(account_m);
	


			myvari.wait(lock, []() {

				return bill_is_ready;

				});
			//bill_is_ready = true;

			

			cout << "total avalible amount" << bill.total() << endl;

			bill_is_ready = false;

		}



}


//1729.00

void threads() {


	const int THREADS = 10;

	std::vector<std::thread>threadlist;

	threadlist.reserve(THREADS);





	for (int i = 0; i < THREADS; i++) {
		threadlist.emplace_back(&adding);
		threadlist.emplace_back(&consumer);
	}

	for (auto& thread : threadlist) {
		thread.join();
	}

	



}



int main(int argc, char* argv[])
{
	cout << "Initial: " << bill.total() << "\n";


	//the_clock::time_point start = the_clock::now();
	threads();
	//the_clock::time_point end = the_clock::now();

	/*thread t1(consumer);
	thread t2(adding);

	t1.join();
	t2.join();*/


	//bill.add(4, 17);
	//bill.add(3, 0);
	//bill.add(10, 99);


	cout << "Total: " << bill.total() << "\n";

	//auto time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
	//cout << "Time taken " << time_taken << " nanoseconds." << endl;

	return 0;
}



//first attempt without mutex 32million nanoseconds

//seconds attemp with mutex 400million nanoseconds

//12 times longer