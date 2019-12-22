#include <iostream>
#include <string>

#include "processor.h"

using namespace std;

//Definitions
Processor::Processor(string vendor_id, string model_name, int number_of_cores, double clock_speed_mhz)
{
	this->vendor_id = vendor_id;
	this->model_name = model_name;
	this->number_of_cores = number_of_cores;
	this->clock_speed_mhz = clock_speed_mhz;
}

Processor::Processor() { }

void Processor::setVendorID(string vendor_id)
{
	this->vendor_id = vendor_id;
}

void Processor::setModelName(string model_name)
{
	this->model_name = model_name;
}

void Processor::setNumberOfCores(int number_of_cores)
{
	this->number_of_cores = number_of_cores;
}

void Processor::setClockSpeedMhz(double clock_speed_mhz)
{
	this->clock_speed_mhz = clock_speed_mhz;
}

std::string Processor::getVendorID()
{
	return vendor_id;
}

std::string Processor::getModelName()
{
	return model_name;
}

int  Processor::getNumberOfCores()
{
	return number_of_cores;
}

double Processor::getClockSpeedMhz()
{
	return clock_speed_mhz;
}
