#include"List.cpp"

class DLList: public List
{
	public:
		DLList* next = nullptr;
		DLList* prev = nullptr;
	
		DLList():List()
		{
			DLList* x = new DLList(-1,-1,-1);
			this->next = x;
			x->prev = this;
		};
		DLList(int address, int size, int key):List(address, size, key){};
		DLList* Insert(int address, int size, int key);
		bool Delete(Dictionary* d);	
		DLList* Find(int k, bool equal);
		DLList* getFirst();
		DLList* getNext();
		bool Sanity();
};

DLList* DLList::Insert(int address, int size, int key)
{
	if(!this||(!this->next))
		return nullptr;
	
	DLList* x = new DLList(address, size, key);
	this->next->prev = x;
	x->next = this->next;
	this->next = x;
	x->prev = this;	
	return x;
}

bool DLList::Delete(Dictionary* d)
{
	if(!d)
		return false;
	
	DLList* x = new DLList;
	for(x = this->getFirst();x!=nullptr;x=x->getNext())
	{
		if((x->address == d->address) && (x->size == d->size) && (x->key == d->key))
		{
			x->prev->next = x->next;
			x->next->prev = x->prev;
			x = nullptr;
			return true;
		}
	}
	return false;
}

DLList* DLList::Find(int k, bool equal)
{
	DLList* x = new DLList;
	for(x = this->getFirst();x!=nullptr;x=x->getNext())
	{
		if(equal)
		{
			if(x->key==k)
				return x;
		}
		else
		{
			if(x->key>=k)
				return x;
		}
	}
	return nullptr;
}

DLList* DLList::getFirst()
{
	if(!this)
		return nullptr;
	
	if(!this->prev)
	{
		if(this->next->next == nullptr)
			return nullptr;
		else
			return this->next;	
	}
	else
	{
		return this->prev->getFirst();
	}	
}

DLList* DLList::getNext()
{
	if(!this||!(this->next)||!(this->next->next))
		return nullptr;
	else
		return this->next;
}

bool DLList::Sanity()
{
	//nullptr DLList and Empty DLList
	if(!this)
		return true;
	
	if(!(this->getFirst()))
	{
		if((this->next->size!=-1)||(this->next->address!=-1)||(this->next->key!=-1))
		{
			return false;
		}
		return true;
	}
	
	//Check for Cycle
	DLList* x = new DLList;
	x = this->getFirst();
	DLList* y = new DLList;
	y = this->getFirst()->getNext();
	for(;x!=nullptr;x=x->getNext())
	{
		if(!y)
			break;
		if(x==y)
			return false;
		y=y->getNext();
		if(!y)
			break;
		y=y->getNext();		
	}
	
	DLList* z = new DLList;
	z = this->getFirst();
	
	//Check Head
	if((z->prev->size)!=-1||(z->prev->address)!=-1||(z->prev->key)!=-1||(z->prev->prev))
		return false;
	
	//Check validity of each element
	for(;z->next!=nullptr;z=z->next)
	{
		if(!(z == z->next->prev)||!(z == z->prev->next))
			return false;
	}
	
	//Check Tail	
	if((z->size!=-1)||(z->address!=-1)||(z->key!=-1)||(z->next!=nullptr))
		return false;	
			
	return true;
}

