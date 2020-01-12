#ifndef HOST_H
#define HOST_H

#include <cstdint>
#include <string>
#include <vector>

#include "physical_thread.h"
#include "ram.h"
#include "process.h"

//Host machine abstraction
class Host
{
	private:
        //Variables
        int64_t dbid;

        int8_t loadavg_1;
        int8_t loadavg_5;
        int8_t loadavg_15;
        uint32_t number_of_processes;
        uint32_t procs_running;
        uint64_t cpu_time;
        uint64_t boot_time;
        double uptime;
        double uptime_idle;
        std::string kernel_version;
        std::string hostname;
        std::vector<std::string> ip_addresses;
        std::vector<std::string> mac_addresses;

        std::vector<PhysicalThread> threads;
        std::vector<Process> processes;
        RAM random_access_memory;
	public:
        //Constructors
        Host();

        //Functions
        int64_t getDbId();
		int8_t getLoadavg1();
		int8_t getLoadavg5();
		int8_t getLoadavg15();
        uint32_t getNumberOfProcesses();
        uint32_t getProcsRunning();
        uint64_t getCpuTime();
        uint64_t getBootTime();
        double getUptime();
        double getUptimeIdle();
        std::string getKernelVersion();
        std::string getHostname();
        std::vector<std::string>& getIpAddresses();
        std::vector<std::string>& getMacAddresses();
        std::vector<PhysicalThread>& getThreads();
        std::vector<Process>& getProcesses();
        RAM& getRAM();
        void addThread(PhysicalThread thread);
        void setDbId(int64_t dbid);
		void setLoadavg1(std::int8_t loadavg_1);
		void setLoadavg5(std::int8_t loadavg_5);
		void setLoadavg15(std::int8_t loadavg_15);
        void setNumberOfProcesses(uint32_t number_of_processes);
        void setProcsRunning(uint32_t procs_running);
        void setCpuTime(uint64_t cpu_time);
        void setBootTime(uint64_t boot_time);
        void setUptime(double uptime);
        void setUptimeIdle(double uptime_idle);
        void setKernelVersion(std::string kernel_version);
        void setHostname(std::string hostname);
        void addIpAddresses(std::string ip_address);
        void addMacAddresses(std::string mac_address);
        void setIpAddresses(std::vector<std::string> ip_addresses);
        void setMacAddresses(std::vector<std::string> mac_addresses);
        void setRAM(RAM ram);
};

#endif //HOST_H
