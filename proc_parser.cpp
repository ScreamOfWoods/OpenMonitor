#include <iostream>
#include <fstream>
#include <string>
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

void ProcParser::addThread(std::string vendor_id, std::string model_name, int number_of_cores,
				double clock_speed_mhz, int thread_id, int core_id, double thread_clock)
{
	PhysicalThread p = PhysicalThread(vendor_id, model_name, number_of_cores, clock_speed_mhz,
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
		if(value.length() > 1)
			value = value.substr(1, value.length() - 1);
		cout<<property<<"||"<<value<<endl;
	}

	cpuinfo.close();
}

int main()
{
	ProcParser proc_parser = ProcParser();

	proc_parser.parseCpuInfo();

	return 0;
}
