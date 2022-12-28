In this project, I wrote 1 .cpp file and 2 .cxx file with their coorsponding .h file. It contains a Makefile with all the commands for all three files, so you can run them all together at the same time instead of manually type in the commands. 

Commands for individual files: 
priorityqueue.cpp priorityqueue.h
g++ buildheap.cxx priorityqueue.cpp priorityqueue.h -o main
./main TestCase1.buildheap.json

buildheap.cxx buildheap.h
//g++ buildheap.cxx priorityqueue.cpp priorityqueue.h -o main
//./main TestCase1.buildheap.json

createteams.cxx createteams.h
//g++ createteams.cxx priorityqueue.cpp priorityqueue.h -o main
//./main TestCase1.createteams.json
