#include <iostream>
#include <cstdint>
#include "ram.h"

using namespace std;

RAM::RAM() { mem_total = 0;}

uint64_t RAM::getMemTotal()
{
	return this->mem_total;
}

uint64_t RAM::getMemFree()
{
	return mem_free;
}

uint64_t RAM::getMemAvailable()
{
	return mem_available;
}

uint64_t RAM::getCached()
{
	return cached;
}

uint64_t RAM::getSwapTotal()
{
	return swap_total;
}

uint64_t RAM::getSwapFree()
{
	return swap_free;
}

uint64_t RAM::getDirty()
{
	return dirty;
}

void RAM::setMemTotal(uint64_t mem_total)
{
	this->mem_total = mem_total;
}

void RAM::setMemFree(uint64_t mem_free)
{
	this->mem_free = mem_free;
}
void RAM::setMemAvailable(uint64_t mem_available)
{
	this->mem_available = mem_available;
}

void RAM::setCached(uint64_t cached)
{
	this->cached = cached;
}

void RAM::setSwapTotal(uint64_t swap_total)
{
	this->swap_total = swap_total;
}

void RAM::setSwapFree(uint64_t swap_free)
{
	this->swap_free = swap_free;
}

void RAM::setDirty(uint64_t dirty)
{
	this->dirty = dirty;
}
