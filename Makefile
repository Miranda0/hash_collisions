OBJS = main.o 
CC = g++
CPPFLAGS = -Wall -c -g -std=c++11
LFLAGS = -Wall -g

a: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o a

main.o: main.cpp 
	$(CC) $(CPPFLAGS) main.cpp 

LinearProbing.o: LinearProbing.h LinearProbing.cpp
	$(CC) $(CPPFLAGS) LinearProbing.cpp

QuadraticProbing.o: QuadraticProbing.h QuadraticProbing.cpp
	$(CC) $(CPPFLAGS) QuadtraticProbing.cpp

SeparateChaining.o: SeparateChaining.h SeparateChaining.cpp
	$(CC) $(CPPFLAGS) SeparateChaining.cpp

clean: 
	rm -f *.o 
	rm -f a
