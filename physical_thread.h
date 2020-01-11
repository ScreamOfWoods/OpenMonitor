#ifndef PHYSICAL_THREAD_H
#define PHYSICAL_THREAD_H

#include <cstdint>
#include "processor.h"
#include "json.hpp"

//Physical thread abstraction extends Processor class
class PhysicalThread : public Processor
{
	private:
		//Variables
		int32_t thread_id;
		int32_t core_id;
		double thread_clock;
	public:
		//Constructors
		PhysicalThread(std::string vendor_id, std::string model_name, int32_t number_of_cores,
				int32_t thread_id, int32_t core_id, double thread_clock);
		PhysicalThread();

		//Functions
		void setThreadID(int32_t threadID);
		void setCoreID(int32_t coreID);
		void setThreadClock(double thread_clock);
		int32_t getThreadID() const;
		int32_t getCoreID() const;
		double getThreadClock() const;
};

#endif //PHYSICAL_THREAD_H
