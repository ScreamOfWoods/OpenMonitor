#include <cstdint>
#include <string>
#include <vector>

#include "host.h"
#include "ram.h"
#include "process.h"

using namespace std;

Host::Host()
{
    random_access_memory = RAM();
    loadavg_1 = 0;
    loadavg_5 = 0;
    loadavg_15 = 0;
    number_of_processes = 0;
    uptime = 0;
    kernel_version = "";
    hostname = "";
    dbid = 0;
}

void Host::addThread(PhysicalThread thread)
{
    threads.push_back(thread);
}

int64_t Host::getDbId()
{
    return dbid;
}

int8_t Host::getLoadavg1()
{
    return loadavg_1;
}

int8_t Host::getLoadavg5()
{
    return loadavg_5;
}

int8_t Host::getLoadavg15()
{
    return loadavg_15;
}

uint32_t Host::getNumberOfProcesses()
{
    return number_of_processes;
}

uint32_t Host::getProcsRunning()
{
    return procs_running;
}

uint64_t Host::getCpuTime()
{
    return cpu_time;
}

uint64_t Host::getBootTime()
{
    return boot_time;
}

double Host::getUptime()
{
    return uptime;
}

double Host::getUptimeIdle()
{
    return uptime_idle;
}

string Host::getKernelVersion()
{
    return kernel_version;
}

string Host::getHostname()
{
    return hostname;
}

vector<string>& Host::getIpAddresses()
{
    return ip_addresses;
}

vector<string>& Host::getMacAddresses()
{
    return mac_addresses;
}

vector<PhysicalThread>& Host::getThreads()
{
    return threads;
}

vector<Process>& Host::getProcesses()
{
    return processes;
}

RAM& Host::getRAM()
{
    return random_access_memory;
}

void Host::setDbId(int64_t dbid)
{
    this->dbid = dbid;
}

void Host::setLoadavg1(int8_t loadavg_1)
{
    this->loadavg_1 = loadavg_1;
}

void Host::setLoadavg5(int8_t loadavg_5)
{
    this->loadavg_5 = loadavg_5;
}

void Host::setLoadavg15(int8_t loadavg_15)
{
    this->loadavg_15 = loadavg_15;
}

void Host::setNumberOfProcesses(uint32_t number_of_processes)
{
    this->number_of_processes = number_of_processes;
}

void Host::setProcsRunning(uint32_t procs_running)
{
    this->procs_running = procs_running;
}

void Host::setCpuTime(uint64_t cpu_time)
{
    this->cpu_time = cpu_time;
}

void Host::setBootTime(uint64_t boot_time)
{
    this->boot_time = boot_time;
}

void Host::setUptime(double uptime)
{
    this->uptime = uptime;
}

void Host::setUptimeIdle(double uptime_idle)
{
    this->uptime_idle = uptime_idle;
}

void Host::setKernelVersion(string kernel_version)
{
    this->kernel_version = kernel_version;
}

void Host::setHostname(string hostname)
{
    this->hostname = hostname;
}

void Host::addIpAddresses(string ip_address)
{
    ip_addresses.push_back(ip_address);
}

void Host::addMacAddresses(string mac_address)
{
    mac_addresses.push_back(mac_address);
}

void Host::setIpAddresses(vector<string> ip_addresses)
{
    this->ip_addresses = ip_addresses;
}

void Host::setMacAddresses(vector<string> mac_addresses)
{
    this->mac_addresses = mac_addresses;
}

void Host::setRAM(RAM ram)
{
    this->random_access_memory = ram;
}
