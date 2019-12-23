#include <iostream>
#include <string>

#include "processor.h"

using namespace std;

//Definitions
Processor::Processor(string vendor_id, string model_name, int number_of_cores)
{
	this->vendor_id = vendor_id;
	this->model_name = model_name;
	this->number_of_cores = number_of_cores;
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
