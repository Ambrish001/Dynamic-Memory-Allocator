#include"DynamicMemory.cpp"

class Ass1DynamicMem:public DynamicMem 
{
	public:
		Ass1DynamicMem():DynamicMem(){};
		Ass1DynamicMem(int size):DynamicMem(size){};
		Ass1DynamicMem(int size, int ver):DynamicMem(size, ver){};
		void Defragment(){return;};
		int Allocate(int allsize);
		int Free(int begin);
};

int Ass1DynamicMem::Allocate(int allsize)
{
	Dictionary* x = freeBlock->Find(allsize, false);
	if(!x||allsize<=0)
		return -1;
		
	freeBlock->Delete(x);
	
	if(x->size>allsize)
		freeBlock->Insert(x->address + allsize, x->size - allsize, x->size - allsize);
	
	allocBlock->Insert(x->address, allsize, x->address);
	
	return x->address;			
}

int Ass1DynamicMem::Free(int begin)
{
	Dictionary* x = allocBlock->Find(begin, true);
	
	if(!x)
		return -1;
	
	allocBlock->Delete(x);
	freeBlock->Insert(x->address, x->size, x->size);
	return 0;	
}

