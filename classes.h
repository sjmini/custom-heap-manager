#ifndef __CLASSES_H__
#define __CLASSES_H__

#include <string>
#include <vector>

#include "rlist.h"

extern MemoryManager gMemoryManager;

template <typename T>
class Object
{
private:
	unsigned int refCounter = 0;
	T obj;

public:
	Object() { 
		incRef();
	}

	void* operator new(size_t size)
	{
		printf("you are in object new operator %d\n", size);
		return gMemoryManager.allocate(size);
	};

	void operator delete(void* object)
	{
		printf("you are in object delete operator, ref:  %d\n",((Object *)object)->refCounter);
		if (((Object *)object)->refCounter == 1)
			gMemoryManager.free(object);
	};

	inline void incRef() { refCounter++; };
	inline void decRef() { refCounter--; };
};

class Complex
{
public:
	Complex() : r(0), c(0) {}
	Complex(double a, double b) : r(a), c(b) {}

	inline void* operator new(size_t size)
	{
		return gMemoryManager.allocate(size);
	};

	inline void operator delete(void* object)
	{
		gMemoryManager.free(object);
	};

private:
	double r; // Real Part
	double c; // Complex Part
};

class Coordinate
{
	int CoordX;
	int CoordY;
	int CoordZ;
	std::string name;
public:
	Coordinate() :CoordX(0), CoordY(0), CoordZ(0), name("") {}
	inline void* operator new(size_t size)
	{
		return gMemoryManager.allocate(sizeof(Coordinate));
	};

	inline void  operator delete(void* object)
	{
		gMemoryManager.free(object);
	};

};

class JobScheduler
{
	std::vector<int> JobNumber;
	std::vector<int> MaxJobTime;
	int              StartTime;
public:
	JobScheduler() { }

	
	inline void* operator new(size_t size)
	{
		printf("you are in new operator %d\n", sizeof(JobScheduler));
		return gMemoryManager.allocate(sizeof(JobScheduler));
	}

	inline void  operator delete(void* object)
	{
		printf("you are in delete operator\n");
		gMemoryManager.free(object);
	}

};

const int JOB_SCHEDULER_SIZE = sizeof(JobScheduler);

const int POOL_SIZE = 1024; //number of elements in a single pool
//can be chosen based on application requirements 

//const int MAX_BLOCK_SIZE = 44; //depending on the application it may change 
const int MAX_BLOCK_SIZE = 68; //depending on the application it may change 
//In above case it came as 44

#endif
