#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <locale>
#include <functional>
#include <algorithm>

#include "processor.h"
#include "physical_thread.h"
#include "proc_parser.h"

using namespace std;

ProcParser::ProcParser()
{

}

vector<PhysicalThread> ProcParser::getCpuThreads()
{
	return cpu_threads;
}

void ProcParser::addThread(std::string vendor_id, std::string model_name, int number_of_cores,
				int thread_id, int core_id, double thread_clock)
{
	PhysicalThread p = PhysicalThread(vendor_id, model_name, number_of_cores,
		thread_id, core_id, thread_clock);
	cpu_threads.push_back(p);
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

		int pos = line.find(delimiter);
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
			if(!property.compare("vendor_id")){
				vendor_id = value;
			}
			if(!property.compare("modelname")){
				model_name = value;
			}
			if(!property.compare("cpucores")){
				number_of_cores = value;
			}
			if(!property.compare("processor")){
				thread_id = value;
			}
			if(!property.compare("cpuMHz")){
				thread_clock = value;
			}
			if(!property.compare("coreid")){
				core_id = value;
			}
			continue;
		}
		cout<<vendor_id<<" | "<<model_name<<" | "<<number_of_cores<<" | "<<thread_id<<" | "<<thread_clock<<" | "<<core_id<<endl;

		addThread(vendor_id, model_name, stoi(number_of_cores), stoi(thread_id),
				stoi(core_id), stod(thread_clock));
	}

	cpuinfo.close();
}

int main()
{
	ProcParser proc_parser = ProcParser();

	proc_parser.parseCpuInfo();

	for(int i = 0; i < proc_parser.getCpuThreads().size(); i++) {
		cout<<proc_parser.getCpuThreads().at(i).getThreadID()<<" "<<proc_parser.getCpuThreads().at(i).getThreadClock()<<endl;
	}

	return 0;
}
