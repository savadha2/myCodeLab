#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>


enum status_t{
	SUCCESS,
	FAILURE
};

/*
This Timeout class has a 
timer() method and a
execute() method()
if the execute() method does not run within timeout_millis_, 
it should be stopped and should return Failure
You can print "Failed" in main() - already implemented for you
if executed() method runs before timeout_millis_,
it should halt the timer and return success
You can print "Executed Successfully" - already implemented for you
*/

/* Task is to find the bug and fix it*/
class TimeoutClass{
private:
	size_t max_iters_;
	uint64_t timeout_millis_;
	status_t status_;
	bool halt_process_;
	bool halt_timer_;
	std::condition_variable cv_;
	std::mutex mutex_;
	std::chrono::steady_clock::time_point start_time;
public:
	TimeoutClass(size_t max_iters, uint64_t timeout_millis): 
	max_iters_(max_iters), 
	timeout_millis_(timeout_millis),
	halt_process_(false),
	halt_timer_(false){}

	/*
	execute prints "I am counting i" for max_iters_ and sleeps 100 milliseconds
	so total time of execution is ~100 * max_iters_ millis
	if 100 * max_iters_ > timeout_millis_=> Failure
	if 100 * max_iters_ < timeout_millis_ => Success
	ignore corner case when it is equal - either could happen
	*/
	status_t execute(){
		std::thread timer_thread = std::thread(&TimeoutClass::timer, this);
		//std::thread monitor_thread = std::thread(&TimeoutClass::monitor, this);
		//HINT: IS the line below problematic?
		std::unique_lock<std::mutex> lk(mutex_);
		for(size_t i=0; i < max_iters_; i++){
			std::cout<<"I am counting "<<i<<std::endl;
			
			if(halt_process_){
				timer_thread.join();
				return status_t::FAILURE;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}

		// The code below is a hint
		/*if(!halt_process_){
			halt_timer_ = true;
			cv_.notify_one();
		}*/
		halt_timer_ = true;
		mutex_.unlock();
		cv_.notify_one();
		timer_thread.join();
		return status_t::SUCCESS;
	}
	void timer(){
		start_time = std::chrono::steady_clock::now();
		std::unique_lock<std::mutex> lk(mutex_);
		auto end_time = start_time + std::chrono::milliseconds(timeout_millis_);
		if(!cv_.wait_until(lk, end_time, [this](){
			return halt_timer_;}
			)
			)
		{
			halt_process_ = true;
		}
		return;
	}

};

int main(int argc, char* argv[]){
	//the line below should print "Executed Successfully"
	//TimeoutClass time_out_success(12, 1400);

	//the line below should print "Failed"
	//(if you want to run this, comment out the above line)
	TimeoutClass time_out(20, 1000); 

	status_t status = time_out.execute();
	if(status==status_t::SUCCESS){
		std::cout<<"Executed successfully"<<std::endl;
	}else{
		std::cout<<"Failed"<<std::endl;
	}
	return 0;
}