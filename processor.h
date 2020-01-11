#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <iostream>
#include <cstdint>
#include <vector>
#include "json.hpp"

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
		std::string getVendorID() const;
		std::string getModelName() const;
		std::int32_t getNumberOfCores() const;
};

#endif //PROCESSOR_H
