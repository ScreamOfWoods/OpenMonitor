#include <iostream>
#include <cstdint>

#include "process.h"

using namespace std;

Process::Process() {}

Process::Process(int32_t pid, string command, char state, uint64_t umode_time, 
        uint64_t smode_time, int32_t priority, int32_t nice, int64_t num_threads,
        string start_time, uint64_t start_time_ticks, uint64_t virtual_memory_bytes,
        uint64_t physical_memory_bytes, int32_t exit_code)
{
    this->pid = pid;
    this->command = command;
    this->state = state;
    this->umode_time = umode_time;
    this->smode_time = smode_time;
    this->priority = priority;
    this->nice = nice;
    this->num_threads = num_threads;
    this->start_time = start_time;
    this->start_time_ticks = start_time_ticks;
    this->virtual_memory_bytes = virtual_memory_bytes;
    this->physical_memory_bytes = physical_memory_bytes;
    this->exit_code = exit_code;
}


int32_t Process::getPid()
{
    return pid;
}

string Process::getCommand()
{
    return command;
}

char Process::getState()
{
    return state;
}

uint64_t Process::getUmodeTime()
{
    return umode_time;
}

uint64_t Process::getSmodeTime()
{
    return smode_time;
}

int32_t Process::getPriority()
{
    return priority;
}

int32_t Process::getNice()
{
    return nice;
}

int64_t Process::getNumThreads()
{
    return num_threads;
}

string Process::getStartTime()
{
    return start_time;
}

uint64_t Process::getStartTimeTicks()
{
    return start_time_ticks;
}

uint64_t Process::getVirtualMemory()
{
    return virtual_memory_bytes;
}

uint64_t Process::getPhysicalMemory()
{
    return physical_memory_bytes;
}

int32_t Process::getExitCode()
{
    return exit_code;
}


void Process::setPid(int32_t pid)
{
    this->pid = pid;
}

void Process::setCommand(string command)
{
    this->command = command;
}

void Process::setState(char state)
{
    this->state = state;
}

void Process::setUmodeTime(uint64_t umode_time)
{
    this->umode_time = umode_time;
}

void Process::setSmodeTime(uint64_t smode_time)
{
    this->smode_time = smode_time;
}

void Process::setPriority(int32_t priority)
{
    this->priority = priority;
}

void Process::setNice(int32_t nice)
{
    this->nice = nice;
}

void Process::setNumThreads(uint32_t num_threads)
{
    this->num_threads = num_threads;
}

void Process::setStartTime(string start_time)
{
    this->start_time = start_time;
}

void Process::setStartTimeTicks(uint64_t start_time_ticks)
{
    this->start_time_ticks = start_time_ticks;
}

void Process::setVirtualMemory(uint64_t virtual_memory_bytes)
{
    this->virtual_memory_bytes = virtual_memory_bytes;
}

void Process::setPhysicalMemory(uint64_t physical_memory_bytes)
{
    this->physical_memory_bytes = physical_memory_bytes;
}

void Process::setExitCode(int32_t exit_code)
{
    this->exit_code = exit_code;
}

