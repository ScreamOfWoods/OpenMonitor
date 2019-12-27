#ifndef RAM_H
#define RAM_H

#include <cstdint>

//Random Access Memory abstraction class
class RAM
{
	private:
        //Variables
        std::uint64_t mem_total;
        std::uint64_t mem_free;
        std::uint64_t mem_available;
        std::uint64_t cached;
        std::uint64_t swap_total;
        std::uint64_t swap_free;
        std::uint64_t dirty;
	public:
		//Constructors
		RAM();

		//Functions
        std::uint64_t getMemTotal();
        std::uint64_t getMemFree();
	    std::uint64_t getMemAvailable();
	    std::uint64_t getCached();
	    std::uint64_t getSwapTotal();
	    std::uint64_t getSwapFree();
	    std::uint64_t getDirty();
		void setMemTotal(std::uint64_t mem_total);
		void setMemFree(std::uint64_t mem_free);
		void setMemAvailable(std::uint64_t mem_available);
		void setCached(std::uint64_t cached);
		void setSwapTotal(std::uint64_t swap_total);
		void setSwapFree(std::uint64_t swap_free);
		void setDirty(std::uint64_t dirty);
};

#endif //RAM_H
