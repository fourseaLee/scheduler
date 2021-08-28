#include <scheduler.h>
#include <iostream>
#include <threadgroup.hpp>
#include <util.h>
void test()
{
	std::cout << "test" << std::endl;
}
int main(int argc, char* argv[])
{

	CScheduler scheduler;
	//ThreadGroup threadGroup;
    	scheduler.scheduleEvery(test, 1000);
	CScheduler::Function serviceLoop = std::bind(&CScheduler::serviceQueue, &scheduler);
	//threadGroup.create_thread(boost::bind(&TraceThread<CScheduler::Function>, "scheduler", serviceLoop));
//	threadGroup.create_thread(boost::bind(test));
    	std::thread  thread_scheduler(std::bind(&TraceThread<CScheduler::Function>, "scheduler", serviceLoop));
	thread_scheduler.join();

/*	int counter{0};
	CScheduler::Function dummy = [&counter]{
		std::cout << "dummy: " << counter << std::endl; 
		counter++;};

	// schedule jobs for 2, 5 & 8 minutes into the future

	scheduler.scheduleEvery(dummy, 2*1000);
	scheduler.scheduleEvery(dummy, 5*1000);
	scheduler.scheduleEvery(dummy, 8*1000);
// check taskQueue
    std::chrono::system_clock::time_point first, last;
    size_t num_tasks = scheduler.getQueueInfo(first, last);

    std::thread scheduler_thread([&]() { scheduler.serviceQueue(); });

    // bump the scheduler forward 5 minutes
    //scheduler.MockForward(5*60*1000);

    // ensure scheduler has chance to process all tasks queued for before 1 ms from now.
    scheduler.scheduleFromNow([&scheduler] { scheduler.stop(); }, 1);
    scheduler_thread.join();
    while(true)
    {
	    
    }*/

	return 0;
}
