#include <iostream>
#include <vector>
#include <cstdint>
#include <chrono>
#include <ctime>
#include <regex>

#include "host_to_json.h"
#include "host.h"
#include "sql_adapter.h"
#include "sqlite3.h"

using namespace std;
using namespace chrono;

SqlAdapter::SqlAdapter(Host host_machine, HostToJson json_host, string description, int32_t accessibility)
{
    this->host_machine = host_machine;
    this->json_host = json_host;
    this->description = description;
    this->accessibility = accessibility;
}

#if 1
int SqlAdapter::openDb()
{
    if(sqlite3_open(DB_PATH, &database)) {
        fprintf(stderr, "Failed to open database: %s", DB_PATH);
        sqlite3_close(database);
        return 0;
    }
    return 1;
}

string SqlAdapter::insertHosts()
{
    string ins = "INSERT INTO hosts( description, accessibility ) VALUES ( ";
    string vals = "\"" + description + "\", " + "\"" + to_string(accessibility) + "\" );";

    return ins + vals;
}

string SqlAdapter::insertStatistics(int64_t host_id, string date_logged)
{
    string jstr = json_host.getJsonDocument().dump();
    regex r("\"");
    jstr = regex_replace(jstr, r, "");
    string ins = "INSERT INTO statistics( host_id, date_logged, json_data ) VALUES ( ";
    string vals = "\"" + to_string(host_id) + "\", " + "\"" + date_logged + "\", " 
        + "\"" + jstr + "\" );";

    return ins + vals;
}

void SqlAdapter::writeToDatabase()
{
    string date;
    time_t t = system_clock::to_time_t(chrono::system_clock::now());
    date = ctime(&t);
    
    if(!openDb()) {
        exit(EXIT_FAILURE);
    }

    sqlite3_exec(database, "BEGIN EXCLUSIVE TRANSACTION;", NULL, NULL, NULL);

    if(!host_machine.getDbId()) {
        //cout<<insertHosts()<<endl;
        sqlite3_exec(database, insertHosts().c_str(), NULL, NULL, NULL);
        host_machine.setDbId(sqlite3_last_insert_rowid(database));
    }

    //cout<<insertStatistics(host_machine.getDbId(), date)<<endl;
    sqlite3_exec(database, insertStatistics(host_machine.getDbId(), date).c_str(), NULL, NULL, NULL);
    sqlite3_exec(database, "END TRANSACTION;", NULL, NULL, NULL);

    sqlite3_close(database);
}
#endif
