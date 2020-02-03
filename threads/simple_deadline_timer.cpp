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
std::atomic<bool> stop_timer(false);

void timer(double wait_time){
	std::chrono::steady_clock::time_point t_start = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point cur_time;
	cur_time = std::chrono::steady_clock::now();
	std::chrono::duration<double> time_elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(cur_time - t_start);
	while(time_elapsed.count() < wait_time && !stop_timer){
		cur_time = std::chrono::steady_clock::now();
		time_elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(cur_time - t_start);
		//std::cout<<"time_elapsed: "<<time_elapsed.count()<<std::endl;
	}
	if(!stop_timer) halt = true;
	return;
}

void executechild(size_t max_iters){
	for(size_t i = 0; i < max_iters; ++i){
		std::cout<<"I am counting "<<i<<std::endl;
		if(halt){
			status = status_t::FAILURE;
			return;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	status = status_t::SUCCESS;
	stop_timer = true;
	return;
}

void execute(size_t max_iters, double wait_time){
	std::thread timer_thread(timer, wait_time);
	std::thread print_thread(executechild, max_iters);

	timer_thread.join();
	print_thread.join();
}

int main(int argc, char* argv[]){
	execute(2, 0.1);
	if(status==status_t::SUCCESS){
		std::cout<<"Success"<<std::endl;
	}else{
		std::cout<<"Failed"<<std::endl;
	}
	return 0;
}