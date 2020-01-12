CC = gcc
CC_FLAGS = -lpthread -ldl

CXX = g++
CXX_FLAGS = -Wall -Wextra -g -std=c++11 -fsanitize=address

objects = host.o processor.o physical_thread.o proc_parser.o ram.o process.o host_to_json.o sql_adapter.o sqlite3.o

server_reporter: $(objects)
	$(CXX) $(CXX_FLAGS) -o server_reporer.exe $(objects) $(CC_FLAGS)

sqlite: sqlite3.c sqlite3.h shell.c
	$(CC) shell.c sqlite3.c $(CC_FLAGS) -o sqlite3

sqlite3.o: sqlite3.c sqlite3.h
	$(CC) -c sqlite3.c -o sqlite3.o

host.o: host.h
processor.o: processor.h
physical_thread.o: physical_thread.h processor.h
ram.o: ram.h
proc_parser.o: processor.h physical_thread.h
process.o: process.h
host_to_json.o: host_to_json.h
sql_adapter.o:  sql_adapter.h host_to_json.h host.h
