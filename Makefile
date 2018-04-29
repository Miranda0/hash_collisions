OBJS = QuadraticProbing.o SeparateChaining.o LinearProbing.o
CC = g++
CPPFLAGS = -Wall -c -g -std=c++11
LFLAGS = -Wall -g

# a: $(OBJS)
#	$(CC) $(LFLAGS) $(OBJS) -o a

all: testAim1 testAim2

testAim1: testAim1.o $(OBJS)
	$(CC) $(LFLAGS) -o aim1 testAim1.o $(OBJS)

testAim2: testAim2.o $(OBJS)
	$(CC) $(LFLAGS) -o aim2 testAim2.o $(OBJS)
	
testAim1.o: testAim1.cpp
	$(CC) $(CPPFLAGS) testAim1.cpp

testAim2.o: testAim2.cpp
	$(CC) $(CPPFLAGS) testAim2.cpp
	
LinearProbing.o: LinearProbing.h LinearProbing.cpp
	$(CC) $(CPPFLAGS) LinearProbing.cpp

QuadraticProbing.o: QuadraticProbing.h QuadraticProbing.cpp
	$(CC) $(CPPFLAGS) QuadraticProbing.cpp

SeparateChaining.o: SeparateChaining.h SeparateChaining.cpp
	$(CC) $(CPPFLAGS) SeparateChaining.cpp

clean: 
	rm -f *.o 
	rm -f aim2
	rm -f aim1