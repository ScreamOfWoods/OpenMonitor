#include <iostream>
#include <string>
#include <cstdint>

#include "physical_thread.h"
#include "processor.h"

using namespace std;

PhysicalThread::PhysicalThread(string vendor_id, string model_name, int32_t number_of_cores,
	   	int32_t thread_id, int32_t core_id, double thread_clock) :
	Processor(vendor_id, model_name, number_of_cores)
{
	this->thread_clock = thread_clock;
	this->thread_id = thread_id;
	this->core_id = core_id;
}

PhysicalThread::PhysicalThread() 
{
    thread_clock = 0.0f;
    core_id = 0;
    thread_id = 0;
}

void PhysicalThread::setThreadID(int32_t thread_id)
{
	this->thread_id = thread_id;
}

void PhysicalThread::setThreadClock(double thread_clock)
{
	this->thread_clock = thread_clock;
}

void PhysicalThread::setCoreID(int32_t core_id)
{
	this->core_id = core_id;
}

int32_t PhysicalThread::getThreadID()
{
	return thread_id;
}

int32_t PhysicalThread::getCoreID()
{
	return core_id;
}

double PhysicalThread::getThreadClock()
{
	return thread_clock;
}
