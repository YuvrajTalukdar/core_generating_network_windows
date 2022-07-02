#declare the variabler
CC=g++
LIBS= -lpthread
# use -Wall for displaying all warnings
CXXFLAGS= -std=c++17 -march=native -mtune=native -O2
CXXFLAGS2= -std=c++17 -march=native -mtune=native -g
all: a.exe

a.exe: main.o genetic_algorithm.o core_class.o menu.o input_raw_to_prepared.o segment_class.o
	$(CC) -o a.exe main.o menu.o genetic_algorithm.o core_class.o input_raw_to_prepared.o segment_class.o $(LIBS) $(OPENCVLIBS) $(CXXFLAGS)

main.o: main.cpp
	$(CC) $(CXXFLAGS) $(LIBS) -c main.cpp

menu.o: menu.cpp
	$(CC) $(CXXFLAGS) $(LIBS) -c menu.cpp

input_raw_to_prepared.o: input_raw_to_prepared.cpp
	$(CC) $(CXXFLAGS) $(LIBS) -c input_raw_to_prepared.cpp

segment_class.o: segment_class.cpp
	$(CC) $(CXXFLAGS) $(LIBS) -c segment_class.cpp

core_class.o: core_class.cpp
	$(CC) $(CXXFLAGS) $(LIBS) -c core_class.cpp

genetic_algorithm.o: genetic_algorithm.cpp
	$(CC) $(CXXFLAGS) $(LIBS) -c genetic_algorithm.cpp

debug: a.debug

a.debug: main_debug.o genetic_algorithm_debug.o core_class_debug.o menu_debug.o input_raw_to_prepared_debug.o segment_class_debug.o
	$(CC) -o a.debug main_debug.o menu_debug.o input_raw_to_prepared_debug.o genetic_algorithm_debug.o core_class_debug.o segment_class_debug.o $(LIBS) $(OPENCVLIBS) $(CXXFLAGS2)

main_debug.o: main.cpp
	$(CC) $(CXXFLAGS2) $(LIBS) -c main.cpp -o main_debug.o

menu_debug.o: menu.cpp
	$(CC) $(CXXFLAGS2) $(LIBS) -c menu.cpp -o menu_debug.o

input_raw_to_prepared_debug.o: input_raw_to_prepared.cpp 
	$(CC) $(CXXFLAGS2) $(LIBS) -c input_raw_to_prepared.cpp -o input_raw_to_prepared_debug.o

segment_class_debug.o: segment_class.cpp
	$(CC) $(CXXFLAGS2) $(LIBS) -c segment_class.cpp -o segment_class_debug.o

core_class_debug.o: core_class.cpp
	$(CC) $(CXXFLAGS2) $(LIBS) -c core_class.cpp -o core_class_debug.o

genetic_algorithm_debug.o: genetic_algorithm.cpp
	$(CC) $(CXXFLAGS2) $(LIBS) -c genetic_algorithm.cpp -o genetic_algorithm_debug.o

clean:
	rm -rf *o a.out a.debug a.exe
