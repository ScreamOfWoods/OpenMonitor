#include <iostream>
#include <string>

#include "physical_thread.h"
#include "processor.h"

using namespace std;

PhysicalThread::PhysicalThread(string vendor_id, string model_name, int number_of_cores,
	   	double clock_speed_mhz, int thread_id, int core_id, double thread_clock) : 
	Processor(vendor_id, model_name, number_of_cores, clock_speed_mhz)
{
	this->thread_clock = thread_clock;
	this->thread_id = thread_id;
	this->core_id = core_id;
}

PhysicalThread::PhysicalThread() {}

void PhysicalThread::setThreadID(int thread_id)
{
	this->thread_id = thread_id;
}

void PhysicalThread::setThreadClock(double thread_clock)
{
	this->thread_clock = thread_clock;
}

void PhysicalThread::setCoreID(int core_id)
{
	this->core_id = core_id;
}

int PhysicalThread::getThreadID()
{
	return thread_id;
}

int PhysicalThread::getCoreID()
{
	return core_id;
}

double PhysicalThread::getThreadClock()
{
	return thread_clock;
}
