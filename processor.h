#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <iostream>
#include <cstdint>
#include <vector>

//Processor abstraction
class Processor
{
	private:
		//Variables
		std::string vendor_id;
		std::string model_name;
		std::int32_t number_of_cores;
	public:
		//Constructors
		Processor(std::string vendor_id, std::string model_name, std::int32_t number_of_cores);
		Processor();

		//Functions
		void setVendorID(std::string vendor_id);
		void setModelName(std::string model_name);
		void setNumberOfCores(std::int32_t number_of_cores);
		std::string getVendorID();
		std::string getModelName();
		std::int32_t getNumberOfCores();
};

#endif //PROCESSOR_H
