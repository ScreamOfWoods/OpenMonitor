#ifndef HOST_TO_JSON
#define HOST_TO_JSON

#include "json.hpp"
#include "host.h"

//Export the Host class to json string
class HostToJson
{
    private:
        //Variables
        nlohmann::json jdoc;
        Host host_machine;

        //Functions
        void createJsonObject();
        void addProcessorsToJson();
        void addProcessesToJson();
        void addAddressesToJson();
    public:
        //Construcotrs
        HostToJson(Host host_machine);
        HostToJson();

        //Functions
        nlohmann::json& getJsonDocument();
        Host& getHostMachine();
        void setHostMachine(Host host_machine);
};


#endif //HOST_TO_JSON
