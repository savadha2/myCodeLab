#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

enum status_t{
	SUCCESS,
	FAILURE
};

status_t status;
std::atomic<bool> halt(false);
bool child_done(false);
std::condition_variable cv;
std::mutex mtx;

void timer(int64_t milliseconds){
    auto t_start = std::chrono::steady_clock::now();
    auto t_end = t_start + std::chrono::milliseconds(milliseconds);
	std::unique_lock<std::mutex> lck(mtx);
	if(!cv.wait_until(lck, t_end, [](){
		 return child_done;
		 })
		)
	{
		halt=true;
	}
	cv.notify_one();
	return;
}

void executechild(size_t max_iters){
	for(size_t i = 0; i < max_iters; ++i){
		std::unique_lock<std::mutex> lck(mtx);
		std::cout<<"I am counting "<<i<<std::endl;
		if(halt){
			status = status_t::FAILURE;
			return;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	status = status_t::SUCCESS;
	child_done = true;
	cv.notify_one();
	return;
}

void execute(size_t max_iters, int64_t wait_time_millis){
	std::thread timer_thread(timer, wait_time_millis);
	std::thread print_thread(executechild, max_iters);
	timer_thread.join();
	print_thread.join();
}

int main(int argc, char* argv[]){
	execute(12, 1100);
	if(status==status_t::SUCCESS){
		std::cout<<"Success"<<std::endl;
	}else{
		std::cout<<"Failed"<<std::endl;
	}
	return 0;
}