CXX=g++ -std=c++11 -Wall -Wextra 

all: tests.o stack.cpp
	$(CXX) -o main.cpp stack.cpp
main: main.cpp stack.cpp
	$(CXX) -o calculator main.cpp stack.cpp
tests.o: tests.cpp
	$(CXX) -o tests.o -c tests.cpp
clean:
	rm -f calculator tests.o
