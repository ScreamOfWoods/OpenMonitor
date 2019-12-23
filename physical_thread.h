#ifndef PHYSICAL_THREAD_H
#define PHYSICAL_THREAD_H

#include "processor.h"

//Physical thread abstraction extends Processor class
class PhysicalThread : public Processor
{
	private:
		//Variables
		int thread_id;
		int core_id;
		double thread_clock;
	public:
		//Constructors
		PhysicalThread(std::string vendor_id, std::string model_name, int number_of_cores,
				int thread_id, int core_id, double thread_clock);
		PhysicalThread();

		//Functions
		void setThreadID(int threadID);
		void setCoreID(int coreID);
		void setThreadClock(double thread_clock);
		int getThreadID();
		int getCoreID();
		double getThreadClock();
};

#endif //PHYSICAL_THREAD_H
