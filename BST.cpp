#ifndef bs
#define bs
#include<iostream>
#include"Tree.cpp"
using namespace std;
class BST: public Tree
{
	public:
		BST* lnode = nullptr;
		BST* rnode = nullptr;
		BST* parent = nullptr;
		
		BST():Tree(){};
		BST(int address, int size, int key):Tree(address, size, key){};
		BST* getRoot();
		BST* Insert(int address, int size, int key);
		bool Delete(Dictionary* d);
		void deleteNode();
		BST* Find(int key, bool equal);
		BST* getFirst();
		BST* getNext();
		bool loopCheck(BST* x, BST* y);
		bool sanity();
};

BST* BST::getRoot()
{
	if(this)
	{
		if(!this->parent)
			return this->rnode;
	}		
	else
		return this->parent->getRoot();	
}

BST* BST::Insert(int address, int size, int key)
{
	BST* x = this->getRoot();
	
	if(!x)
	{
		BST* y = new BST(address,size,key);
		y->parent = this;
		this->rnode = y;
		return y;
	}
	
	int c;//0 means left and 1 means right
	while(x && (x->lnode||x->rnode))
	{
		if(x->key<key)
			c=1;
		else if(x->key>key)
			c=0;
		else
		{
			if(x->address<address)
				c=1;
			else
				c=0;	
		}
		
		if(c==0)
		{
			if(x->lnode)
				x=x->lnode;
			else
				break;	
		}
		else
		{
			if(x->rnode)
				x=x->rnode;
			else
				break;	
		}		
	}
	
	BST* y = new BST(address,size,key);
	y->parent = x;
	if(x->key>key)
		x->lnode = y;
	else if(x->key<key)
		x->rnode = y;
	else
	{
		if(x->address<address)
			x->rnode=y;
		else
			x->lnode=y;	
	}
	return y;			
}

void BST::deleteNode()
{
	if(!this->lnode && !this->rnode)
	{
		if(this->parent->lnode == this)
			this->parent->lnode = nullptr;
		if(this->parent->rnode == this)
			this->parent->rnode = nullptr;
		this->lnode = nullptr;
		this->rnode = nullptr;
		return;	
	}
	
	if(!this->lnode)
	{
		this->rnode->parent = this->parent;
		if(this->parent->lnode == this)
			this->parent->lnode = this->rnode;
		if(this->parent->rnode == this)
			this->parent->rnode = this->rnode;
		this->rnode = nullptr;
		return;		
	}
	
	else if(!this->rnode)
	{
		this->lnode->parent = this->parent;
		if(this->parent->lnode == this)
			this->parent->lnode = this->lnode;
		if(this->parent->rnode == this)
			this->parent->rnode = this->lnode;
		this->lnode = nullptr;
		return;		
	}
	
	BST* x = this->rnode;
	while(x && x->lnode)
		x=x->lnode;
	BST* y = new BST(x->address,x->size,x->key);
	y->lnode = this->lnode;
	y->rnode = this->rnode;
	y->parent = this->parent;
	y->lnode->parent = y;
	y->rnode->parent = y;
	if(y->parent->lnode == this)
		y->parent->lnode = y;
	else
		y->parent->rnode = y;
	
	x->deleteNode();			
}

bool BST::Delete(Dictionary* d)
{
	BST* x = this->getRoot();
	while(x)
	{
		if(x->key<d->key)
			x=x->rnode;
		else if(x->key>d->key)
			x=x->lnode;
		else
		{
			if(x->address<d->address)
				x=x->rnode;
			else if(x->address>d->address)
				x=x->lnode;
			else
			{
				if(x->size == d->size)
				{
					x->deleteNode();
					return true;
				}
				else
					return false;		
			}		
		}		
	}
	return false;
}

BST* BST::Find(int key, bool equal)
{
	BST* x = this->getRoot();
	BST* y = nullptr;
	BST* z = nullptr;
	while(x)
	{
		if(x->key<key)
			x = x->rnode;
		else
		{
			if(x->key==key)
				z = x;
			else
				y = x;
			x = x->lnode;		
		}	
	}
	
	if(!equal)
	{
		if(!z)
			return y;
	}
	
	if(!z)
		return nullptr;
	
	return z;
}

BST* BST::getFirst()
{
	BST* x = this->getRoot();
	while(x && x->lnode)
		x=x->lnode;
	return x;	
}

BST* BST::getNext()
{
	if(!this->parent)
		return nullptr;
	if(this->rnode)
	{
		BST* x = this->rnode;
		while(x->lnode)
			x=x->lnode;
		return x;	
	}
	else
	{
		BST* x = this;
		while(x && x->parent && x->parent->lnode!=x)
			x=x->parent;
		if(!x->parent)
			return nullptr;
		else
			return x->parent;		
	}	
}

bool BST::loopCheck(BST* x, BST* y)
{
	if(!x)
		return true;
	
	if(!y->Find(x->address, true))
	{
		y->Insert(x->address, x->size, x->address);
		return loopCheck(x->lnode, y) && loopCheck(x->rnode, y);	
	}	
	else
		return false;
}

bool BST::sanity()
{
	BST* x = this;
	
	if(!x->parent)
	{
		if(!((!x->lnode) && (x->address == -1 && x->size == -1 && x->key == -1)))
			return false;
		else
		{
			if(!x->rnode)
				return true;
		}	
	}
	
	BST* y = this;
	BST* z = this->parent;
	while(z && z->parent && y->parent)
	{
		if(y==z)
			return false;
		y = y->parent;
		z = z->parent;
		if(z && z->parent)
			z=z->parent;	
	}
	
	x = z;
	if(!x)
		x = y;
		
	if(!x->parent)
	{
		if(!(x->address==-1 && x->size == -1 && x->key == -1))
		{
			cout<<1<<endl;
			return false;
		}
		if(x->lnode)
			return false;
	}
	
	BST* a = new BST;
	
	if(!loopCheck(x->rnode, a))
		return false;
		
	for(x=this->getFirst();x->getNext()!=nullptr;x=x->getNext())
	{
		if(x->key>x->getNext()->key)
		{
			cout<<2<<endl;
			return false;
		}
		else if(x->key == x->getNext()->key)
		{
			if(x->address>x->getNext()->address)
			{
				cout<<3<<endl;
				return false;
			}
		}
		
		if(x->lnode && x->lnode->parent!=x)
		{
			cout<<4<<endl;
			return false;
		}
		if(x->rnode && x->rnode->parent!=x)
		{
			cout<<5<<endl;
			return false;
		}
		
		if(x->lnode && x->rnode)
		{
			if((x->rnode == x->lnode)||(x->lnode == x->parent)||(x->rnode == x->parent))
			{
				cout<<6<<endl;
				return false;
			}
		}
	}
	
	return true;		
}

#endif
