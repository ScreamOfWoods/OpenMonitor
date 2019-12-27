#ifndef PROC_PARSER_H
#define PROC_PARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>

#include "host.h"

#define UPTIME_PATH         "/proc/uptime"
#define CPUINFO_PATH        "/proc/cpuinfo"
#define MEMINFO_PATH        "/proc/meminfo"
#define LOADAVG_PATH        "/proc/loadavg"
#define HOSTNAME_PATH       "/proc/sys/kernel/hostname"
#define KERNEL_VER_PATH     "/proc/sys/kernel/version"

//Proc fs parser class.
class ProcParser
{
	private:
		//Variables
        Host host_machine;
		std::vector<std::string> cpu_tokens;
		std::vector<std::string> mem_tokens;

        //Functions
		std::string trim(const std::string& str);
		int32_t getValueFromProperty(std::vector<std::string> tokens, std::string property);
	public:

		//Constructors
		ProcParser();

		//Functions
		void addThread(std::string vendor_id, std::string model_name, int32_t number_of_cores,
				int32_t thread_id, int core_id, double thread_clock);
		void initSearchTokens();
		void parseCpuInfo();
		void parseMemInfo();
		void parseLoadavg();
        void parseUptime();
        void parseHostnameKernelVerion();
		void parseStat();
        Host& getHostMachine();
};
#endif //PROC_PARSER_H
