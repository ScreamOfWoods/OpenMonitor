#include <iostream>
#include <string>
#include <cstdint>

#include "processor.h"
#include "physical_thread.h"

using namespace std;

//Definitions
Processor::Processor(string vendor_id, string model_name, int32_t number_of_cores)
{
	this->vendor_id = vendor_id;
	this->model_name = model_name;
	this->number_of_cores = number_of_cores;
}

Processor::Processor()
{ 
    vendor_id = "";
    model_name = "";
    number_of_cores = 0;
}

string Processor::getVendorID() const
{
	return vendor_id;
}

string Processor::getModelName() const
{
	return model_name;
}

int32_t Processor::getNumberOfCores() const
{
	return number_of_cores;
}
void Processor::setVendorID(string vendor_id)
{
	this->vendor_id = vendor_id;
}

void Processor::setModelName(string model_name)
{
	this->model_name = model_name;
}

void Processor::setNumberOfCores(int32_t number_of_cores)
{
	this->number_of_cores = number_of_cores;
}
