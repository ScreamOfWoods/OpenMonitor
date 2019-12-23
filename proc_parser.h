#ifndef PROC_PARSER_H
#define PROC_PARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "processor.h"
#include "physical_thread.h"

#define CPUINFO_PATH "/proc/cpuinfo"

//Proc fs parser class.
class ProcParser
{
	private:
		//Variables
		std::vector<PhysicalThread> cpu_threads;
	public:

		//Constructors
		ProcParser();

		//Functions
		std::vector<PhysicalThread> getCpuThreads();
		void addThread(std::string vendor_id, std::string model_name, int number_of_cores,
				int thread_id, int core_id, double thread_clock);
		void removeThread();
		void parseCpuInfo();
		void parseStat();
		void parseLoadavg();
};
#endif //PROC_PARSER_H
