This project contains a .cc file, SearchNewBooks.cc, that allows the user to use either binary or linear search to find requested books in a given list. The result contains the number of book that we find. Also, it contains the CPU time that take the program to run, so we can see the difference between linear search and binary search. 

It contain a Makefile. 

g++ -Wall -Werror -o SearchNewBooks SearchNewBooks.cc
./SearchNewBooks newBooks3.dat request3.dat result3.txt