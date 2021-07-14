#include"LinkedList.cpp"
#include"AVL.cpp"
#include <stdint.h>
class DynamicMem
{
	public:
		const int fix = 1000000;
		uint8_t* Memory;	
		Dictionary* freeBlock;
		Dictionary* allocBlock;
		int var;
		
		DynamicMem(int size, int ver);
		DynamicMem(int size){DynamicMem(size, 1);};
		DynamicMem(){DynamicMem(fix, 1);};
		virtual int Allocate(int allsize){};
		virtual int Free(int begin){};
		virtual void Defragment(){}; 
};

DynamicMem::DynamicMem(int size, int ver)
{
	Memory = new uint8_t[size];
	var=ver;
	if(var==1)
	{
		freeBlock = new DLList();
		allocBlock = new DLList();
		freeBlock->Insert(0,size,size);
	}
	else if(var==2)
	{
		freeBlock = new BST();
		allocBlock = new BST();
		freeBlock->Insert(0,size,size);
	}
	else
	{
		freeBlock = new AVL();
		allocBlock = new AVL();
		freeBlock->Insert(0,size,size);
	}
}

