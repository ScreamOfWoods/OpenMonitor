#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <locale>
#include <functional>
#include <algorithm>
#include <cstdint>
#include <cinttypes>
#include <dirent.h>
#include <cerrno>
#include <ctime>
#include <unistd.h>

#include "processor.h"
#include "physical_thread.h"
#include "proc_parser.h"
#include "ram.h"
#include "host.h"

using namespace std;

ProcParser::ProcParser()
{
    host_machine = Host();
}

void ProcParser::addThread(std::string vendor_id, std::string model_name, int32_t number_of_cores,
				int32_t thread_id, int core_id, double thread_clock)
{
	PhysicalThread p = PhysicalThread(vendor_id, model_name, number_of_cores,
		thread_id, core_id, thread_clock);
	host_machine.addThread(p);
}

void ProcParser::parseCpuInfo()
{
	ifstream cpuinfo;
	string line;

	cpuinfo.open(CPUINFO_PATH, std::ios::in);
	if(!cpuinfo.is_open()) {
		cerr<<"Failed to open "<<CPUINFO_PATH<<endl;
		exit(EXIT_FAILURE);
	}
	char delimiter = ':';

	string vendor_id, model_name, number_of_cores, thread_id, thread_clock, core_id;
	while(getline(cpuinfo, line)){
		if(line.empty())
			continue;

		uint32_t pos = line.find(delimiter);
		string property = line.substr(0, pos);
		string value = "";
		if(pos+1 < line.length()-1) {
			value = line.substr(pos+1, line.back());
		}

		//Working whitespace remover
		property.erase(remove_if(property.begin(), property.end(),
					bind(isspace<char>, placeholders::_1, locale::classic())), property.end());
		if(value.length() > 1) {
			value = value.substr(1, value.length() - 1);
		}
		if(property.compare("powermanagement")) {
			int32_t found = getValueFromProperty(cpu_tokens, property);
			switch(found) {
				case 0:
					vendor_id = value;
					break;
				case 1:
					model_name = value;
					break;
				case 2:
					number_of_cores = value;
					break;
				case 3:
					thread_id = value;
					break;
				case 4:
					thread_clock = value;
					break;
				case 5:
					core_id = value;
					break;
			}
			continue;
		}
		cout<<vendor_id<<" | "<<model_name<<" | "<<number_of_cores<<" | "<<thread_id<<" | "<<thread_clock<<" | "<<core_id<<endl;

		addThread(vendor_id, model_name, stoi(number_of_cores), stoi(thread_id),
				stoi(core_id), stod(thread_clock));
	}

	cpuinfo.close();
}

void ProcParser::parseMemInfo()
{
	ifstream meminfo;
	string line;

	meminfo.open(MEMINFO_PATH, std::ios::in);
	if(!meminfo.is_open()) {
		cerr<<"Failed to open "<<MEMINFO_PATH<<endl;
		exit(EXIT_FAILURE);
	}
	char delimiter = ':';

	while(getline(meminfo, line)){
		if(line.empty())
			continue;

		uint32_t pos = line.find(delimiter);
		string property = line.substr(0, pos);
		string value = "";

        if(pos+1 < line.length()-1) {
			value = line.substr(pos+1, line.back());
		}

		int32_t found = getValueFromProperty(mem_tokens, property);
		switch(found) {
			case 0:
				host_machine.getRAM().setMemTotal(stoull(value));
				break;
			case 1:
				host_machine.getRAM().setMemFree(stoull(value));
				break;
			case 2:
				host_machine.getRAM().setMemAvailable(stoull(value));
				break;
			case 3:
				host_machine.getRAM().setCached(stoull(value));
				break;
			case 4:
				host_machine.getRAM().setSwapTotal(stoull(value));
				break;
			case 5:
				host_machine.getRAM().setSwapFree(stoull(value));
				break;
			case 6:
				host_machine.getRAM().setDirty(stoull(value));
				break;
		}
	}
}

void ProcParser::parseLoadavg()
{
	FILE* file_instance;
	if((file_instance = fopen(LOADAVG_PATH, "r")) == NULL) {
		cerr<<"Failed to open "<<LOADAVG_PATH<<endl;
		exit(EXIT_FAILURE);
	}

	float load1, load5, load15;
	int runnable_kern_procs, existing_kern_procs, last_pid;
	if((fscanf(file_instance, "%f %f %f %d/%d %d", &load1, &load5, &load15, 
		&runnable_kern_procs, &existing_kern_procs, &last_pid)) != 6) {
		cerr<<"Failed to properly read "<<LOADAVG_PATH<<endl;
        fclose(file_instance);
		exit(EXIT_FAILURE);
	}

	host_machine.setLoadavg1(int8_t (load1 * 100));
	host_machine.setLoadavg5(int8_t (load5 * 100));
	host_machine.setLoadavg15(int8_t (load15 * 100));

	printf("Loadavg: %.2f %.2f %.2f %d/%d %d\n", load1, load5, load15, runnable_kern_procs, existing_kern_procs, last_pid);

    fclose(file_instance);
}

void ProcParser::parseUptime()
{
    FILE* file_instance;
    if((file_instance = fopen(UPTIME_PATH, "r")) == NULL) {
		cerr<<"Failed to open "<<UPTIME_PATH<<endl;
		exit(EXIT_FAILURE);
    }

    double uptime, uptime_idle;
    if((fscanf(file_instance, "%lf %lf", &uptime, &uptime_idle) != 2)) {
		cerr<<"Failed to properly read "<<UPTIME_PATH<<endl;
        fclose(file_instance);
		exit(EXIT_FAILURE);
    }

    host_machine.setUptime(uptime);
    host_machine.setUptimeIdle(uptime_idle);

    fclose(file_instance);
}

void ProcParser::parseHostnameKernelVerion()
{
	ifstream host_info;
	string line = "";

	host_info.open(HOSTNAME_PATH, std::ios::in);
	if(!host_info.is_open()) {
		cerr<<"Failed to open "<<HOSTNAME_PATH<<endl;
		exit(EXIT_FAILURE);
	}
    
    getline(host_info, line);
    if(line.empty()) {
        cerr<<"Failed to properly read: "<<HOSTNAME_PATH<<endl;
        host_info.close();
        exit(EXIT_FAILURE);
    }

    host_machine.setHostname(line);
    host_info.close();

	host_info.open(KERNEL_VER_PATH, std::ios::in);
	if(!host_info.is_open()) {
		cerr<<"Failed to open "<<KERNEL_VER_PATH<<endl;
		exit(EXIT_FAILURE);
	}
    
    getline(host_info, line);
    if(line.empty()) {
        cerr<<"Failed to properly read: "<<KERNEL_VER_PATH<<endl;
        host_info.close();
        exit(EXIT_FAILURE);
    }

    host_machine.setKernelVersion(line);
    host_info.close();
}

void ProcParser::parseFibTrie()
{
	ifstream fib_trie;
	string line = "";

	fib_trie.open(FIB_TRIE_PATH, std::ios::in);
	if(!fib_trie.is_open()) {
		cerr<<"Failed to open "<<FIB_TRIE_PATH<<endl;
		exit(EXIT_FAILURE);
	}

    string delimiter = "|-- ";
    vector<string> ips;
    while(getline(fib_trie, line)) {
        line = trim(line);
        auto found = line.find(delimiter);
        if(found == string::npos)
            continue;
        //Remove delimiter from the string when extracting the ip address
        found += 4;

        line = line.substr(found, line.back());

        if(startsWith(line, "127"))
            continue;
        if(startsWith(line, "169.254"))
            continue;
        if(endsWith(line, ".0"))
            continue;
        if(endsWith(line, ".255"))
            continue;

        ips.push_back(line);
    }
    removeDuplicates(&ips);
    host_machine.setIpAddresses(ips);
}

void ProcParser::parseProcessStat()
{
    DIR *dir;
    struct dirent *dir_entity;

    if((dir = opendir("/proc")) == NULL) {
        fprintf(stderr, "Failed to open /proc %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    while((dir_entity = readdir(dir)) != NULL) {
        int64_t proc_entry;
        try{
            proc_entry = stoi(dir_entity->d_name);
            char dir_name[256];
            if(snprintf(dir_name, 256, "/proc/%ld/stat", proc_entry) < 0) {
                fprintf(stderr, "Sprintf failed to create /proc/<num>/stat entity: %s\n", strerror(errno));
                exit(EXIT_FAILURE);
            }

            FILE *proc_entry_file = fopen(dir_name, "r");
            if(proc_entry_file == NULL) {
                fprintf(stderr, "Failed to open %s. Reason %s\n", dir_name, strerror(errno));
                exit(EXIT_FAILURE);
            }

            char command_cstr[_POSIX_PATH_MAX];
            char state;
            long int num_threads, cutime, cstime, itrealvalue, cguest_time;
            string command, start_time;
            unsigned long sig, blocked, guest_time, start_data, end_data, start_brk, arg_start, arg_end;
            unsigned int flags, rt_prio, policy;
            unsigned int env_start, env_end;
            int pid, exit_code, ppid, pgrp, session, tty_nr, tpgid, processor, exit_signal;
            unsigned long priority, nice, umode_time, smode_time, virtual_memory_bytes, physical_memory_bytes;
            unsigned long minflt, cminflt, majflt, cmajflt, rsslim;
            unsigned long long start_time_ticks, delayacct;
            unsigned long startcode, endcode, startstack, kstkesp, kstkeip;
            unsigned long sigignore, sigcatch, wchan, nswap, cnswap;
//            int pid;

            if(fscanf(proc_entry_file, "%d %s %c %d %d %d %d %d %u %lu %lu %lu %lu %lu "
                                        "%lu %ld %ld %ld %ld %ld %ld %llu %lu %ld %lu "
                                        "%lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu "
                                        "%d %d %u %u %llu %lu %ld %lu %lu %lu %lu %lu %d %d %d",
                &pid, command_cstr, &state, &ppid, &pgrp, &session, &tty_nr, &tpgid, &flags, &minflt, 
                &cminflt, &majflt, &cmajflt, &umode_time, &smode_time, &cutime, &cstime, &priority,
                &nice, &num_threads, &itrealvalue, &start_time_ticks, &virtual_memory_bytes,
                &physical_memory_bytes, &rsslim, &startcode, &endcode, &startstack, &kstkesp,
                &kstkeip, &sig, &blocked, &sigignore, &sigcatch, &wchan, &nswap, &cnswap, 
                &exit_signal, &processor, &rt_prio, &policy, &delayacct, &guest_time,
                &cguest_time, &start_data, &end_data, &start_brk, &arg_start, &arg_end,
                &env_start, &env_end, &exit_code) != 52) {

                fclose(proc_entry_file);
                
                fprintf(stderr, "Failed to read %s! Reason %s\n", dir_name, strerror(errno));
                //exit(EXIT_FAILURE);
            } 
            //printf("PID: %" PRId32 "\n", pid);


            fprintf(stdout, ">>>>%d %s %c %d %d %d %d %d %u %lu %lu %lu %lu %lu "
                                        "%lu %ld %ld %ld %ld %ld %ld %llu %lu %ld %lu "
                                        "%lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu "
                                        "%d %d %u %u %llu %lu %ld %lu %lu %lu %lu %lu %d %d %d<<<<\n",
                pid, command_cstr, state, ppid, pgrp, session, tty_nr, tpgid, flags, minflt, 
                cminflt, majflt, cmajflt, umode_time, smode_time, cutime, cstime, priority,
                nice, num_threads, itrealvalue, start_time_ticks, virtual_memory_bytes,
                physical_memory_bytes, rsslim, startcode, endcode, startstack, kstkesp,
                kstkeip, sig, blocked, sigignore, sigcatch, wchan, nswap, cnswap, 
                exit_signal, processor, rt_prio, policy, delayacct, guest_time,
                cguest_time, start_data, end_data, start_brk, arg_start, arg_end,
                env_start, env_end, exit_code); 

#if 0
            fprintf(stdout, "\n>>>>%d %s %c %d %d %d %d %d %u %lu %lu %lu %lu %lu "
                                        "%lu %ld %ld %ld %ld %ld %ld %llu %lu %ld %lu "
                                        "%lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu "
                                        "%d %d %u %u %llu %lu %ld %lu %lu %lu %lu %lu %lu %lu %d<<<<\n",
                pid, command_cstr, state, ppid, pgrp, session, tty_nr, tpgid, flags, minflt, 
                cminflt, majflt, cmajflt, umode_time, smode_time, cutime, cstime, priority,
                nice, num_threads, itrealvalue, start_time_ticks, virtual_memory_bytes,
                physical_memory_bytes, rsslim, startcode, endcode, startstack, kstkesp,
                kstkeip, sig, blocked, sigignore, sigcatch, wchan, nswap, cnswap, 
                exit_signal, processor, rt_prio, policy, delayacct, guest_time,
                cguest_time, start_data, end_data, start_brk, arg_start, arg_end,
                env_start, env_end, exit_code); 
            //break;
#endif
                fclose(proc_entry_file);
        } catch(invalid_argument exception) { }
    }

    closedir(dir);
}

//TODO create proc stat abstraction? and fill it
void ProcParser::parseStat()
{
    FILE* proc_stat;
    if((proc_stat = fopen(STAT_PATH, "r")) == NULL) {
		cerr<<"Failed to open "<<STAT_PATH<<endl;
		exit(EXIT_FAILURE);
    }

    unsigned long long user, nice, system, idle;
    unsigned long long boot_time, processes, procs_running;

    if( (fscanf(proc_stat, "%*s %llu %llu %llu %llu %*llu "
        "%*llu %*llu %*llu %*llu %*llu", &user, &nice, &system, &idle)) != 4) {
        fprintf(stderr, "Failed to read %s\n", STAT_PATH);
        fclose(proc_stat);
        exit(EXIT_FAILURE);        
    }
    
    char *line = NULL;
    size_t len = 0;
    while((getline(&line, &len, proc_stat)) != -1) {
        string pass_line = string(line);
        if(startsWith(pass_line, "btime")) {
            if((sscanf(line, "%*s %llu", &boot_time)) != 1) {
                fprintf(stderr, "Failed to read %s\n", STAT_PATH);
                fclose(proc_stat);
                exit(EXIT_FAILURE);        
            }
        }

        if(startsWith(pass_line, "processes")) {
            if((sscanf(line, "%*s %llu", &processes)) != 1) {
                fprintf(stderr, "Failed to read %s\n", STAT_PATH);
                fclose(proc_stat);
                exit(EXIT_FAILURE);        
            }
        }

        if(startsWith(pass_line, "procs_running")) {
            if((sscanf(line, "%*s %llu", &procs_running)) != 1) {
                fprintf(stderr, "Failed to read %s\n", STAT_PATH);
                fclose(proc_stat);
                exit(EXIT_FAILURE);        
            }
        }
    }
    if(line)
        free(line);

    printf("cpu %llu %llu %llu %llu\n", user, nice, system, idle);
    printf("btime %llu processes %llu running %llu\n", boot_time, processes, procs_running);
    fclose(proc_stat);
}

string ProcParser::trim(const std::string& str)
{
    const auto strBegin = str.find_first_not_of(" \t");
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(" \t");
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

void ProcParser::removeDuplicates(vector<string>* vec)
{
    sort( vec->begin(), vec->end() );
    vec->erase( unique( vec->begin(), vec->end() ), vec->end() );
}

bool ProcParser::startsWith(string str, string token)
{
    auto found = str.find(token);
    if(found == string::npos)
        return false;
    return true;
}

bool ProcParser::endsWith(string full, string ending)
{
    if(full.length() >= ending.length()) {
        return (0 == full.compare(full.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

void ProcParser::initSearchTokens()
{
	//Cpuinfo tokens
	cpu_tokens.push_back("vendor_id");
	cpu_tokens.push_back("modelname");
	cpu_tokens.push_back("cpucores");
	cpu_tokens.push_back("processor");
	cpu_tokens.push_back("cpuMHz");
	cpu_tokens.push_back("coreid");

	//Meminfo tokens
	mem_tokens.push_back("MemTotal");
	mem_tokens.push_back("MemFree");
	mem_tokens.push_back("MemAvailable");
	mem_tokens.push_back("Cached");
	mem_tokens.push_back("SwapTotal");
	mem_tokens.push_back("SwapFree");
	mem_tokens.push_back("Dirty");
}

int32_t ProcParser::getValueFromProperty(vector<string> tokens, string property)
{
	vector<string>::iterator it = find(tokens.begin(), tokens.end(), property);
	if(it == tokens.end())
		return -1;
	return distance(tokens.begin(), it);
}

Host& ProcParser::getHostMachine()
{
    return host_machine;
}

int32_t main()
{
	ProcParser proc_parser = ProcParser();

	proc_parser.initSearchTokens();
	proc_parser.parseCpuInfo();
	proc_parser.parseMemInfo();
	proc_parser.parseLoadavg();
	proc_parser.parseUptime();
	proc_parser.parseHostnameKernelVerion();
	proc_parser.parseFibTrie();
    proc_parser.parseStat();
	proc_parser.parseProcessStat();

	for(uint32_t i = 0; i < proc_parser.getHostMachine().getThreads().size(); i++) {
		cout<<proc_parser.getHostMachine().getThreads().at(i).getThreadID()<<" "<<proc_parser.getHostMachine().getThreads().at(i).getThreadClock()<<endl;
	}

    for(uint32_t i = 0; i < proc_parser.getHostMachine().getIpAddresses().size(); i++){
        cout<<"Ip: "<<proc_parser.getHostMachine().getIpAddresses().at(i)<<endl;
    }

	printf("Total Memory: %lu Available Memory %lu\n", proc_parser.getHostMachine().getRAM().getMemTotal(), proc_parser.getHostMachine().getRAM().getMemAvailable());

    printf("Loadavg 1: %d\n",proc_parser.getHostMachine().getLoadavg1());
    printf("Uptime %.2lf; UPtime Idle: %.2lf\n", proc_parser.getHostMachine().getUptime(), proc_parser.getHostMachine().getUptimeIdle());
    printf("Kernel version %s; Hostname %s\n", proc_parser.getHostMachine().getKernelVersion().c_str(), proc_parser.getHostMachine().getHostname().c_str());

	return 0;
}
