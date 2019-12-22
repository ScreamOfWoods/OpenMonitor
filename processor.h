#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <iostream>

//Processor abstraction
class Processor
{
	private:
		//Variables
		std::string vendor_id;
		std::string model_name;
		int number_of_cores;
		double clock_speed_mhz;
	public:
		//Constructors
		Processor(std::string vendor_id, std::string model_name, int number_of_cores, double clock_speed_mhz);
		Processor();

		//Functions
		void setVendorID(std::string vendor_id);
		void setModelName(std::string model_name);
		void setNumberOfCores(int number_of_cores);
		void setClockSpeedMhz(double clock_speed_mhz);
		std::string getVendorID();
		std::string getModelName();
		int getNumberOfCores();
		double getClockSpeedMhz();
};

#endif //PROCESSOR_H
