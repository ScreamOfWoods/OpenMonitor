#ifndef SQL_ADAPTER_H
#define SQL_ADAPTER_H

#include <iostream>
#include <cstdint>

#include "sqlite3.h"
#include "host.h"
#include "host_to_json.h"

#define DB_PATH "list_serversDB.db"

class SqlAdapter
{
    private:
        //Variables
        sqlite3* database;
        Host host_machine;
        HostToJson json_host;

        std::string description;
        int32_t accessibility;

        //Functions
        int openDb();
        std::string insertHosts();
        std::string insertStatistics(int64_t host_id, std::string date_logged);
    public:
        //Constructors
        SqlAdapter(Host host_machine, HostToJson json_host, 
                std::string description, int32_t accessibility);

        //Functions;
        void writeToDatabase();
};

#endif //SQL_ADAPTER_H
