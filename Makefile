CXX = g++
CXX_FLAGS = -Wall -Wextra -g -std=c++11

objects = host.o processor.o physical_thread.o proc_parser.o ram.o

server_reporter: $(objects)
	$(CXX) $(CXX_FLA) -o server_reporer.exe $(objects)

host.o: host.h
processor.o: processor.h
physical_thread.o: physical_thread.h processor.h
ram.o: ram.h
proc_parser.o: processor.h physical_thread.h
