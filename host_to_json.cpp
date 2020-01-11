#include <iostream>
#include <vector>

#include "host_to_json.h"
#include "host.h"
#include "json.hpp"
#include "physical_thread.h"
#include "ram.h"
#include "process.h"
#include "processor.h"

using namespace std;
using json = nlohmann::json;

HostToJson::HostToJson(Host host_machine)
{
    this->host_machine = host_machine;
    createJsonObject();
}

void HostToJson::createJsonObject()
{
    jdoc["loadavg_1"] = host_machine.getLoadavg1();
    jdoc["loadavg_5"] = host_machine.getLoadavg5();
    jdoc["loadavg_15"] = host_machine.getLoadavg15();
    jdoc["number_of_processes"] = host_machine.getNumberOfProcesses();
    jdoc["procs_running"] = host_machine.getProcsRunning();
    jdoc["cpu_time"] = host_machine.getCpuTime();
    jdoc["boot_time"] = host_machine.getBootTime();
    jdoc["uptime"] = host_machine.getUptime();
    jdoc["uptime_idle"] = host_machine.getUptimeIdle();
    jdoc["kernel_version"] = host_machine.getKernelVersion();
    jdoc["hostname"] = host_machine.getHostname();
    jdoc["ip_addresses"] = host_machine.getIpAddresses();
    jdoc["mac_addresses"] = host_machine.getMacAddresses();
     
    RAM r = host_machine.getRAM();
    jdoc["mem_total"] = r.getMemTotal();
    jdoc["mem_free"] = r.getMemFree();
    jdoc["mem_available"] = r.getMemAvailable();
    jdoc["cached"] = r.getCached();
    jdoc["swap_total"] = r.getSwapTotal();
    jdoc["swap_free"] = r.getSwapFree();
    jdoc["dirty"] = r.getDirty();

    addProcessorsToJson();
    addProcessesToJson();
}

void HostToJson::addProcessorsToJson()
{
    vector<PhysicalThread> threads = host_machine.getThreads();
    for(uint32_t i = 0; i < threads.size(); i++) {
        jdoc["processor"].push_back({
                {"thread_id", threads.at(i).getThreadID()},
                {"core_id", threads.at(i).getCoreID()},
                {"thread_clock", threads.at(i).getThreadClock()},
                {"vendor_id", threads.at(i).getVendorID()},
                {"model_name", threads.at(i).getModelName()},
                {"number_of_cores", threads.at(i).getNumberOfCores()}
                });
    }
}

void HostToJson::addProcessesToJson()
{
    vector<Process> procs = host_machine.getProcesses();
    for(uint32_t i = 0; i < procs.size(); i++) {
        jdoc["processes"].push_back({
                {"pid", procs.at(i).getPid()},
                {"command", procs.at(i).getCommand()},
                {"state", procs.at(i).getState()},
                {"umode_time", procs.at(i).getUmodeTime()},
                {"smode_time", procs.at(i).getSmodeTime()},
                {"priority", procs.at(i).getPriority()},
                {"nice", procs.at(i).getNice()},
                {"num_threads", procs.at(i).getNice()},
                {"start_time", procs.at(i).getStartTime()},
                {"start_time_ticks", procs.at(i).getStartTimeTicks()},
                {"virtual_memory_bytes", procs.at(i).getVirtualMemory()},
                {"physical_memory_bytes", procs.at(i).getPhysicalMemory()},
                {"exit_code", procs.at(i).getExitCode()},
                {"cpu_load", procs.at(i).getCpuLoad()}
               });

    }
}

json& HostToJson::getJsonDocument()
{
    return jdoc;
}
