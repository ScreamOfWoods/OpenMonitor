#ifndef HOST_H
#define HOST_H

#include <cstdint>
#include <string>
#include <vector>

#include "physical_thread.h"
#include "ram.h"

//Host machine abstraction
class Host
{
	private:
        //Variables
		std::int8_t loadavg_1;
		std::int8_t loadavg_5;
		std::int8_t loadavg_15;
        std::uint32_t number_of_processes;
        double uptime;
        double uptime_idle;
		std::string kernel_version;
		std::string hostname;
		std::vector<std::string> ip_addresses;
		std::vector<std::string> mac_addresses;

        std::vector<PhysicalThread> threads;
        RAM random_access_memory;
	public:
        //Constructors
        Host();

        //Functions
		std::int8_t getLoadavg1();
		std::int8_t getLoadavg5();
		std::int8_t getLoadavg15();
        std::uint32_t getNumberOfProcesses();
        double getUptime();
        double getUptimeIdle();
        std::string getKernelVersion();
        std::string getHostname();
        std::vector<std::string> getIpAddresses();
        std::vector<std::string> getMacAddresses();
        std::vector<PhysicalThread> getThreads();
        RAM& getRAM();
        void addThread(PhysicalThread thread);
		void setLoadavg1(std::int8_t loadavg_1);
		void setLoadavg5(std::int8_t loadavg_5);
		void setLoadavg15(std::int8_t loadavg_15);
        void setNumberOfProcesses(uint32_t number_of_processes);
        void setUptime(double uptime);
        void setUptimeIdle(double uptime_idle);
        void setKernelVersion(std::string kernel_version);
        void setHostname(std::string hostname);
        void setIpAddresses(std::vector<std::string> ip_addresses);
        void setMacAddresses(std::vector<std::string> mac_addresses);
        void setRAM(RAM ram);
};

#endif //HOST_H
