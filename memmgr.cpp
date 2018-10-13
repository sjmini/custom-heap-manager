
#include <stdio.h>
#include <vector>
#include <string>
using namespace std;

#include "memmgr.h"
#include "classes.h"

MemoryManager gMemoryManager;

void* MemoryManager::allocate(size_t size)
{
	printf("HSJ %d\n", size);
	void* base = 0;
	//printf("MemoryManager::allocate(size = %d)\n", size);


	//56
	if(JOB_SCHEDULER_SIZE == size){
		printf("in allocation jobscheduler\n");

		if (Byte60PtrList.empty())
		{
			base = new char[60 * POOL_SIZE];
			MemoryPoolList.push_back(base);
			InitialiseByte60List(base);
		}
		void* blockPtr = Byte60PtrList.front();
		*((static_cast<char*>(blockPtr)) + 58) = 60; //size of block set
		*((static_cast<char*>(blockPtr)) + 59) = 0; //block is no longer free
		Byte60PtrList.pop_front();
		return blockPtr;
	}
	//JOB_SCHEDULER for Object Template
	else if(64 == size){
		printf("in allocation object\n");

		if (Byte68PtrList.empty())
		{
			base = new char[68 * POOL_SIZE];
			MemoryPoolList.push_back(base);
			InitialiseByte68List(base);
		}
	
		void* blockPtr = Byte68PtrList.front();
		*((static_cast<char*>(blockPtr)) + 66) = 68; //size of block set
		*((static_cast<char*>(blockPtr)) + 67) = 0; //block is no longer free
		Byte68PtrList.pop_front();
		return blockPtr;
	}	
	if (size > 0 && size <= 4) {
		printf("in allocation 4\n");
		if (Byte8PtrList.empty())
		{
			base = new char[8 * POOL_SIZE];
			MemoryPoolList.push_back(base);
			InitialiseByte8List(base);
		}
		void* blockPtr = Byte8PtrList.front();
		*((static_cast<char*>(blockPtr)) + 6) = 8; //size of block set
		*((static_cast<char*>(blockPtr)) + 7) = 0; //block is no longer free
		Byte8PtrList.pop_front();
		return blockPtr;
	}
	else if (size > 4 && size <= 12) {
		printf("in allocation 12\n");
		if (Byte16PtrList.empty())
		{
			base = new char[8 * POOL_SIZE];
			MemoryPoolList.push_back(base);
			InitialiseByte16List(base);
		}
		void* blockPtr = Byte16PtrList.front();
		*((static_cast<char*>(blockPtr)) + 14) = 16; //size of block set
		*((static_cast<char*>(blockPtr)) + 15) = 0; //block is no longer free
		Byte16PtrList.pop_front();
		return blockPtr;
	}
	else if (size > 12 && size <= 20) {
		printf("in allocation 20\n");
		if (Byte24PtrList.empty())
		{
			base = new char[24 * POOL_SIZE];
			MemoryPoolList.push_back(base);
			InitialiseByte24List(base);
		}
		void* blockPtr = Byte24PtrList.front();
		*((static_cast<char*>(blockPtr)) + 22) = 24; //size of block set
		*((static_cast<char*>(blockPtr)) + 23) = 0; //block is no longer free
		Byte24PtrList.pop_front();
		return blockPtr;
	}
	else if (size > 20 && size <= 28) {
		printf("in allocation 28\n");
	
		if (Byte32PtrList.empty())
		{
			base = new char[32 * POOL_SIZE];
			MemoryPoolList.push_back(base);
			InitialiseByte32List(base);
		}
		void* blockPtr = Byte32PtrList.front();
		*((static_cast<char*>(blockPtr)) + 30) = 32; //size of block set
		*((static_cast<char*>(blockPtr)) + 31) = 0; //block is no longer free
		Byte32PtrList.pop_front();
		return blockPtr;
	}
	else if (size > 28 && size <= 36) {
		printf("in allocation 36\n");
		if (Byte40PtrList.empty())
		{
			base = new char[40 * POOL_SIZE];
			MemoryPoolList.push_back(base);
			InitialiseByte40List(base);
		}
		void* blockPtr = Byte40PtrList.front();
		*((static_cast<char*>(blockPtr)) + 38) = 40; //size of block set
		*((static_cast<char*>(blockPtr)) + 39) = 0; //block is no longer free
		Byte40PtrList.pop_front();
		return blockPtr;
	}
	else if (size > 36 && size <= 44) {
		printf("in allocation 44\n");
		if (Byte48PtrList.empty())
		{
			base = new char[48 * POOL_SIZE];
			MemoryPoolList.push_back(base);
			InitialiseByte48List(base);
		}
		void* blockPtr = Byte48PtrList.front();
		*((static_cast<char*>(blockPtr)) + 46) = 48; //size of block set
		*((static_cast<char*>(blockPtr)) + 47) = 0; //block is no longer free
		Byte48PtrList.pop_front();
		return blockPtr;
	}
	
	return 0;
}

void MemoryManager::free(void* object)
{
	unsigned char* init = static_cast<unsigned char*>(object);

	while (1)
	{
		int count = 0;
		while (*init != 0xde)  //this loop shall never iterate more than 
		{                      // MAX_BLOCK_SIZE times and hence is O(1)
			init++;
			count++;
			if (count > MAX_BLOCK_SIZE)
			{
				printf("runtime heap memory corruption near %x", object);
				exit(1);
			}
		}
		if (*(++init) == 0xad)  // we have hit the guard bytes
			break;  // from the outer while 
	}
	init++;  // ignore size byte
	int size = static_cast<int>(*init);
	init++;
	*init = 1; // set free/available byte
//	int size = (unsigned int)init - (unsigned int)object - 3;

	if (size > 0 && size <= 4)
		Byte8PtrList.push_front(static_cast<unsigned char*>(object));
	else if (size > 8 && size <= 12)
		Byte16PtrList.push_front(static_cast<unsigned char*>(object));
	else if (size > 12 && size <= 20)
		Byte24PtrList.push_front(static_cast<unsigned char*>(object));
	else if (size > 20 && size <= 28)
		Byte32PtrList.push_front(static_cast<unsigned char*>(object));
	else if (size > 28 && size <= 36)
		Byte40PtrList.push_front(static_cast<unsigned char*>(object));
	else if (size > 36 && size <= 44)
		Byte48PtrList.push_front(static_cast<unsigned char*>(object));
	else if (size == 60)
		Byte60PtrList.push_front(static_cast<unsigned char*>(object));
	else if (size == 68)
		Byte68PtrList.push_front(static_cast<unsigned char*>(object));
}

void MemoryManager::InitialiseByte8List(void* base)
{
	for (int i = 0; i < POOL_SIZE; ++i)
	{
		char* guardByteStart = &(static_cast<char*>(base)[i * 8]) + 4;
		*guardByteStart = (char)0xde;
		guardByteStart++;
		*guardByteStart = (char)0xad;   //end of block
		guardByteStart++;
		*guardByteStart = 8;      //sizeof block
		guardByteStart++;
		*guardByteStart = 1;      //block  available
		Byte8PtrList.push_front(&(static_cast<char*>(base)[i * 8]));
	}
}

void MemoryManager::InitialiseByte16List(void* base)
{
	for (int i = 0; i < POOL_SIZE; ++i)
	{
		char* guardByteStart = &(static_cast<char*>(base)[i * 16]) + 12;
		*guardByteStart = (char)0xde;
		guardByteStart++;
		*guardByteStart = (char)0xad;   //end of block
		guardByteStart++;
		*guardByteStart = 16;     //sizeof block
		guardByteStart++;
		*guardByteStart = 1;      //block  available
		Byte16PtrList.push_front(&(static_cast<char*>(base)[i * 16]));
	}
}

void MemoryManager::InitialiseByte24List(void* base)
{
	for (int i = 0; i < POOL_SIZE; ++i)
	{
		char* guardByteStart = &(static_cast<char*>(base)[i * 24]) + 20;
		*guardByteStart = (char)0xde;
		guardByteStart++;
		*guardByteStart = (char)0xad;   //end of block
		guardByteStart++;
		*guardByteStart = 24;     //sizeof block
		guardByteStart++;
		*guardByteStart = 1;      //block  available
		Byte24PtrList.push_front(&(static_cast<char*>(base)[i * 24]));
	}
}

void MemoryManager::InitialiseByte32List(void* base)
{
	for (int i = 0; i < POOL_SIZE; ++i)
	{
		char* guardByteStart = &(static_cast<char*>(base)[i * 32]) + 28;
		*guardByteStart = (char)0xde;
		guardByteStart++;
		*guardByteStart = (char)0xad;   //end of block
		guardByteStart++;
		*guardByteStart = 32;     //sizeof block
		guardByteStart++;
		*guardByteStart = 1;      //block  available
		Byte32PtrList.push_front(&(static_cast<char*>(base)[i * 32]));
	}
}

void MemoryManager::InitialiseByte40List(void* base)
{
	for (int i = 0; i < POOL_SIZE; ++i)
	{
		char* guardByteStart = &(static_cast<char*>(base)[i * 40]) + 36;
		*guardByteStart = (char)0xde;
		guardByteStart++;
		*guardByteStart = (char)0xad;   //end of block
		guardByteStart++;
		*guardByteStart = 40;     //sizeof block
		guardByteStart++;
		*guardByteStart = 1;      //block  available
		Byte40PtrList.push_front(&(static_cast<char*>(base)[i * 40]));
	}
}

void MemoryManager::InitialiseByte48List(void* base)
{
	for (int i = 0; i < POOL_SIZE; ++i)
	{
		char* guardByteStart = &(static_cast<char*>(base)[i * 48]) + 44;
		*guardByteStart = (char)0xde;
		guardByteStart++;
		*guardByteStart = (char)0xad;   //end of block
		guardByteStart++;
		*guardByteStart = 48;     //sizeof block
		guardByteStart++;
		*guardByteStart = 1;      //block  available
		Byte48PtrList.push_front(&(static_cast<char*>(base)[i * 48]));
	}
}

void MemoryManager::InitialiseByte60List(void* base)
{
	for (int i = 0; i < POOL_SIZE; ++i)
	{
		char* guardByteStart = &(static_cast<char*>(base)[i * 60]) + 56;
		*guardByteStart = (char)0xde;
		guardByteStart++;
		*guardByteStart = (char)0xad;   //end of block
		guardByteStart++;
		*guardByteStart = 60;     //sizeof block
		guardByteStart++;
		*guardByteStart = 1;      //block  available
		Byte60PtrList.push_front(&(static_cast<char*>(base)[i * 60]));
	}
}

void MemoryManager::InitialiseByte68List(void* base)
{
	for (int i = 0; i < POOL_SIZE; ++i)
	{
		char* guardByteStart = &(static_cast<char*>(base)[i * 68]) + 64;
		*guardByteStart = (char)0xde;
		guardByteStart++;
		*guardByteStart = (char)0xad;   //end of block
		guardByteStart++;
		*guardByteStart = 68;     //sizeof block
		guardByteStart++;
		*guardByteStart = 1;      //block  available
		Byte68PtrList.push_front(&(static_cast<char*>(base)[i * 68]));
	}
}
