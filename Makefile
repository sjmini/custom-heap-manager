main : CustomMemMgr.o memmgr.o
	g++ -o main CustomMemMgr.o memmgr.o

memmgr.o : memmgr.cpp memmgr.h classes.h
	g++ -c memmgr.cpp

CustomMemMgr.o : CustomMemMgr.cpp rlist.h classes.h
	g++ -c CustomMemMgr.cpp

clean:
	rm -f *.o
