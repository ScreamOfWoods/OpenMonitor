CXX = g++
CXX_FLAGS = -Wall -g

objects = processor.o physical_thread.o proc_parser.o

server_reporter: $(objects)
	$(CXX) $(CXX_FLA) -o server_reporer.exe $(objects)

processor.o: processor.h
physical_thread.o: physical_thread.h processor.h
proc_parser.o: processor.h physical_thread.h
