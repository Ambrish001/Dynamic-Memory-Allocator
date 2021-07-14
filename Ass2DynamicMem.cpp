#include"Ass1DynamicMem.cpp"

class Ass2DynamicMem: public Ass1DynamicMem
{
	public:
		Ass2DynamicMem():Ass1DynamicMem(){};
		Ass2DynamicMem(int size):Ass1DynamicMem(size){};
		Ass2DynamicMem(int size, int ver):Ass1DynamicMem(size,ver){};
		void Defragment();		
};

void Ass2DynamicMem::Defragment()
{
	if(this->var==2)
	{
		BST* x = new BST;
		if(!this->freeBlock->getFirst())
			return;	
		
		for(Dictionary* d=this->freeBlock->getFirst();d!=NULL;d=d->getNext())
			x->Insert(d->address, d->size, d->key);
		
		Dictionary* e = x->getFirst();
		
		for(Dictionary* d = x->getFirst()->getNext(); d!=NULL; d = d->getNext())
		{
			if(e->address + e->size == x->address)
			{
				freeBlock->Insert(e->address, e->size + d->size, e->size + d->size);
				BST* y = new BST(e->address, e->size, e->key);
				freeBlock->Delete(y);
				BST* z = new BST(d->address, d->size, d->key);
				freeBlock->Delete(z);
				
				d->address = e->address;
				d->key = e->address;
				d->size = e->size + d->size;
				e = d;
			}
			else
				e=d;
		}
		x = nullptr;
		return;	
	}
	
	else if(this->var==3)
	{
		AVL* x = new AVL;
		if(!this->freeBlock->getFirst())
			return;
		for(Dictionary* d = this->freeBlock->getFirst();d!=NULL;d = d->getNext())
			x->Insert(d->address,d->size,d->address);
		
		Dictionary* e = x->getFirst();
		
		for(Dictionary* d = x->getFirst()->getNext(); d!=NULL;d=d->getNext())
		{
			if(e->address+e->size == d->address)
			{
				freeBlock->Insert(e->address,e->size+d->size,e->size+d->size);
				AVL* y = new AVL(e->address,e->size,e->size);
				freeBlock->Delete(y);
				AVL* z = new AVL(d->address,d->size,d->size);
				freeBlock->Delete(z);
				
				d->address = e->address;
				d->key = e->address;
				d->size = e->size+d->size;
				e = d;
			}
			else
				e = d;
		}
		x = nullptr;
		return;		
	}
}

