// CustomMemMgr.cpp : Defines the entry point for the console application.
//

#include "memmgr.h"
#include "classes.h"
#include "rlist.h"

#include <stdio.h>

int main(int argc, char* argv[])
//int _tmain(int argc, _TCHAR* argv[])
{
	for (long i = 0; i < 500000; ++i)
	{
		JobScheduler* job = new JobScheduler;
//		printf("printing job\n");
		printf("job: %x\n", job);

		Object<JobScheduler>* objJob = new Object<JobScheduler>;
		printf("Object<Job>: %x\n", objJob);

		RList<Object<JobScheduler>*> list;
		list.push(objJob);

		//Object<JobScheduler>* objJob2 = list.pop();

		/*
		Coordinate*   point = new Coordinate;
		printf("point: %x\n", point);
		Object<Coordinate>* objpoint = new Object<Coordinate>;
		printf("Object<Coordinate>: %x\n", objpoint);
		
		Complex*      number = new Complex;
		printf("number: %x\n", number);
		Object<Complex>* objNumber = new Object<Complex>;
		printf("Object<Complex>: %x\n", objNumber);
		*/

		delete job;
		delete objJob;

		getchar();

		/*
		delete point;
		delete objpoint;
		getchar();

		delete number;
		delete objNumber;
		getchar();
		*/
		//delete number;
	}
	return 0;
}

