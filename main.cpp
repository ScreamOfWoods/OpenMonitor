#include <iostream>
#include <vector>
#include <unistd.h>
#include <getopt.h>
#include <cstdlib>
#include <cerrno>
#include <thread>
#include <chrono>

#include "proc_parser.h"
#include "host_to_json.h"
#include "sql_adapter.h"

using namespace std;

string server_description = "";
int32_t sample_time_seconds = 5;
int32_t srv_access = 5;
bool verbosity = false;

void print_usage()
{
   cout<<endl;
   cout<<"NAME:"<<endl; 
   cout<<"\tserver_reporter"<<endl;
   cout<<"\tSmall C++ program to report server statistics to a database"<<endl;
   cout<<endl;
   cout<<"SYNOPSYS:"<<endl;
   cout<<"\tserver_reporter [OPTIONS]"<<endl;
   cout<<endl;
   cout<<"OPTIONS"<<endl;
   cout<<"\t-d --description <description>"<<endl;
   cout<<"\t\tServer description that will be shown in the user interface. Example rpi-srv"<<endl;
   cout<<"\t-a --access-level <description>"<<endl;
   cout<<"\t\tAccess level of the server. 0 is TopSecret; bigger numbers can be accessed by more users."<<endl;
   cout<<"\t-t --sample-time-seconds <description>"<<endl;
   cout<<"\t\tDuration (seconds) between extracting data. Default 5 seconds."<<endl;
   cout<<"\t-v --verbose"<<endl;
   cout<<"\t\tAdd verbose prints."<<endl;
   cout<<"\t-h --help"<<endl;
   cout<<"\t\tPrint this message."<<endl;
   cout<<endl;
}

void parseArgs(int argc, char *argv[])
{
    static struct option long_options[] = {
       {"description",          required_argument,  0,  'd' },
       {"access-level",         required_argument,  0,  'a' },
       {"sample-time-seconds",  required_argument,  0,  't' },
       {"verbose",              no_argument,        0,  'v' },
       {"help",                 no_argument,        0,  'h' },
       {0,         0,                 0,  0 }
   };

    while(true) {
        int option_index = 0;
        int c = getopt_long(argc, argv, "d:a:t:vh", long_options, &option_index);
        if (c == -1)
           break;

        switch(c) {
            case 'd':
                server_description = string(optarg);
                break;
            case 'a':
                try {
                    srv_access = stoi(optarg);
                } catch(...) {
                    fprintf(stderr, "Failed to parse %s!\n", optarg);
                    fprintf(stderr, "Please provide a valid positive integer\n");
                    print_usage();
                    exit(EXIT_FAILURE);
                }
                if(srv_access < 0) {
                    fprintf(stderr, "Please provide a valid positive integer\n");
                    print_usage();
                    exit(EXIT_FAILURE);
                }
                break;
            case 't':
                try {
                    sample_time_seconds = stoi(optarg);
                } catch(...) {
                    fprintf(stderr, "Failed to parse %s!\n", optarg);
                    fprintf(stderr, "Please provide a valid positive integer\n");
                    print_usage();
                    exit(EXIT_FAILURE);
                }
                if(sample_time_seconds < 0) {
                    fprintf(stderr, "Please provide a valid positive integer\n");
                    print_usage();
                    exit(EXIT_FAILURE);
                }
                break;
            case 'v':
                verbosity = true;
                break;
            case 'h':
                print_usage();
                exit(EXIT_SUCCESS);
            case '?':
                fprintf(stderr, "Unknown option %c\n", optopt);
                print_usage();
                exit(EXIT_FAILURE);
            case ':':
                fprintf(stderr, "Missing option for %c\n", optopt);
                print_usage();
                exit(EXIT_FAILURE);
            default:
                fprintf(stderr, "?? getopt returned character code 0%o ??\n", c);
                print_usage();
                exit(EXIT_FAILURE);
        }
    }

    if(server_description.empty()) {
        fprintf(stderr, "Argument --server-description is mandatory!\n");
        print_usage();
        exit(EXIT_FAILURE);
    }
}

void mainLoop()
{
    while(true) {
        ProcParser proc_parser = ProcParser();

        cout<<"Parsing /proc/ ..."<<endl;

        proc_parser.initSearchTokens();
        proc_parser.parseCpuInfo();
        proc_parser.parseMemInfo();
        proc_parser.parseLoadavg();
        proc_parser.parseUptime();
        proc_parser.parseHostnameKernelVerion();
        proc_parser.parseFibTrie();
        proc_parser.parseStat();
        proc_parser.parseProcessStat();

        cout<<"Done!"<<endl;
        cout<<"Converting to JSON"<<endl;

        HostToJson j = HostToJson(proc_parser.getHostMachine());
        cout<<"Done!"<<endl;
        cout<<"Generating query"<<endl;
        SqlAdapter sa = SqlAdapter(proc_parser.getHostMachine(), j, server_description, srv_access);
        sa.writeToDatabase();
        cout<<"Done!"<<endl;

        if(verbosity) {
            for(uint32_t i = 0; i < proc_parser.getHostMachine().getThreads().size(); i++) {
                cout<<proc_parser.getHostMachine().getThreads().at(i).getThreadID()<<" "<<proc_parser.getHostMachine().getThreads().at(i).getThreadClock()<<endl;
            }

            for(uint32_t i = 0; i < proc_parser.getHostMachine().getIpAddresses().size(); i++){
                cout<<"Ip: "<<proc_parser.getHostMachine().getIpAddresses().at(i)<<endl;
            }

            vector<Process> procs = proc_parser.getHostMachine().getProcesses();
            for(uint32_t i = 0; i < procs.size(); i++) {
                printf("Pid %d command %s start_time %s cpu_load %lf\n", procs.at(i).getPid(), procs.at(i).getCommand().c_str(), procs.at(i).getStartTime().c_str(), procs.at(i).getCpuLoad());
            }

            printf("Total Memory: %lu Available Memory %lu\n", proc_parser.getHostMachine().getRAM().getMemTotal(), proc_parser.getHostMachine().getRAM().getMemAvailable());

            printf("Loadavg 1: %d\n",proc_parser.getHostMachine().getLoadavg1());
            printf("Uptime %.2lf; UPtime Idle: %.2lf\n", proc_parser.getHostMachine().getUptime(), proc_parser.getHostMachine().getUptimeIdle());
            printf("Kernel version %s; Hostname %s\n", proc_parser.getHostMachine().getKernelVersion().c_str(), proc_parser.getHostMachine().getHostname().c_str());

            cout<<"JSON"<<endl;
            cout<<"================"<<endl;
            cout<<j.getJsonDocument().dump()<<endl;   
        }
    
        cout<<"Now sleeping..."<<endl;
        this_thread::sleep_for(chrono::seconds(sample_time_seconds));
    }
}

int main(int argc, char *argv[])
{
    parseArgs(argc, argv);
    cout<<"Running on: "<<server_description<<" with sample time: "<<sample_time_seconds<<"s. ";
    cout<<"Access level: "<<srv_access<<endl;
    mainLoop();

	return 0;
}
