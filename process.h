#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <cstdint>

class Process 
{
    private:
        //Variables
        int32_t pid;
        std::string command;
        char state;
        uint64_t umode_time;
        uint64_t smode_time;
        int32_t priority;
        int32_t nice;
        int64_t num_threads;
        std::string start_time;
        uint64_t start_time_ticks;
        uint64_t virtual_memory_bytes;
        uint64_t physical_memory_bytes;
        int32_t exit_code;
        double cpu_load;
    public:
        //Constructors
        Process();
        Process(int32_t pid, std::string command, char state, uint64_t umode_time, 
                uint64_t smode_time, int32_t priority, int32_t nice, int64_t num_threads,
                std::string start_time, uint64_t start_time_ticks, uint64_t virtual_memory_bytes,
                uint64_t physical_memory_bytes, int32_t exit_code);

        //Functions
        int32_t getPid() const;
        std::string getCommand() const;
        char getState() const;
        uint64_t getUmodeTime() const;
        uint64_t getSmodeTime() const;
        int32_t getPriority() const;
        int32_t getNice() const;
        int64_t getNumThreads() const;
        std::string getStartTime() const;
        uint64_t getStartTimeTicks() const;
        uint64_t getVirtualMemory() const;
        uint64_t getPhysicalMemory() const;
        int32_t getExitCode() const;
        double getCpuLoad() const;
        void setPid(int32_t pid);
        void setCommand(std::string command);
        void setState(char state);
        void setUmodeTime(uint64_t umode_time);
        void setSmodeTime(uint64_t smode_time);
        void setPriority(int32_t priority);
        void setNice(int32_t nice);
        void setNumThreads(uint32_t num_threads);
        void setStartTime(std::string start_time);
        void setStartTimeTicks(uint64_t start_time_ticks);
        void setVirtualMemory(uint64_t virtual_memory_bytes);
        void setPhysicalMemory(uint64_t physical_memory_bytes);
        void setExitCode(int32_t exit_code);
        void setCputLoad(double cpu_load);
};

#endif //PROCESS_H
