#include"BST.cpp"

class AVL: public BST
{
	public:
		AVL* lnode = nullptr;
		AVL* rnode = nullptr;
		AVL* parent = nullptr;
		int height;
		
		AVL():BST(){};
		AVL(int address, int size, int key):BST(address,size,key)
		{
			this->height=0;
		};
		AVL* getRoot();
		bool chkHeight(); 
		AVL* balance(AVL* error, AVL* child, AVL* grandchild);
		AVL* Insert(int address, int size, int key);
		void deleteNode();
		bool Delete(Dictionary* d);
		AVL* Find(int k, bool equal);
		AVL* getFirst();
		AVL* getNext();
		int getHeight(AVL* x);
		bool Sanity();
};

AVL* AVL::getRoot()
{
	if(!this->parent)
		return this->rnode;
	else
		return this->parent->getRoot();		
}

bool AVL::chkHeight()
{
	//Height 0 corresponds to a leaf node and a null node has height of -1
	int lh=-1;
	int rh=-1;
	if(this->lnode)
		lh = this->lnode->height;
	if(this->rnode)
		rh = this->rnode->height;
	
	if(rh>lh)
	{
		if(rh>lh+1)
			return false;
		this->height = rh+1;
		return true;	
	}		
	else
	{
		if(lh>rh+1)
			return false;
		this->height = lh+1;
		return true;	
	}
}

AVL* AVL::balance(AVL* error, AVL* child, AVL* grandchild)
{
	AVL* x;
	if(child == error->lnode)
	{
		if(grandchild == child->lnode)
		{
			child->parent = error->parent;
			if(error->parent->lnode == error)
				error->parent->lnode = child;
			else
				error->parent->rnode = child;	
			error->lnode = child->rnode;
			if(error->lnode)
				error->lnode->parent = error;
			child->rnode = error;
			error->parent = child;
			x = child;		
		}
		else
		{
			grandchild->parent = error->parent;
			if(error->parent->lnode == error)
				error->parent->lnode = grandchild;
			else
				error->parent->rnode = grandchild;
			
			error->lnode = grandchild->rnode;
			if(error->lnode)
				error->lnode->parent=error;
			
			child->rnode = grandchild->lnode;
			if(grandchild->lnode)
				grandchild->lnode->parent = child;
			
			grandchild->lnode = child;
			child->parent = grandchild;
			grandchild->rnode = error;
			error->parent = grandchild;
			
			x = grandchild;				
		}
	}
	else
	{
		if(grandchild == child->lnode)
		{
			grandchild->parent = error->parent;
			if(error->parent->lnode == error)
				error->parent->lnode = grandchild;
			else
				error->parent->rnode = grandchild;
			
			error->rnode = grandchild->lnode;
			if(error->rnode)
				error->rnode->parent = error;
			
			child->lnode = grandchild->rnode;
			if(grandchild->rnode)
				grandchild->rnode->parent = child;
			
			grandchild->rnode = child;
			child->parent = grandchild;
			grandchild->lnode = error;
			error->parent = grandchild;
			
			x = grandchild;				
		}
		else
		{
			child->parent = error->parent;
			if(error->parent->lnode == error)
				error->parent->lnode = child;
			else
				error->parent->rnode = child;
				
			error->rnode = child->lnode;
			if(error->rnode)
				error->rnode->parent = error;
			
			child->lnode = error;
			error->parent = child;
			
			x = child;			
		}
	}
	error->chkHeight();
	child->chkHeight();
	grandchild->chkHeight();
	return x;
}

AVL* AVL::Insert(int address, int size, int key)
{
	AVL* x = this->getRoot();
	
	if(!x)
	{
		AVL* y = new AVL(address, size, key);
		y->parent = this;
		this->rnode = y;
		return y;
	}
	int chk;//0 - left && 1 - right
	while(x && (x->lnode||x->rnode))
	{
		if(x->key<key)
			chk=1;
		else if(x->key>key)
			chk=0;
		else
		{
			if(x->address<address)
				chk=1;
			else
				chk=0;	
		}
		
		if(chk==0)
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
	
	AVL* y = new AVL(address,size,key);
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
	
	AVL* error = y->parent->parent;
	AVL* child = y->parent;
	if(child->height<1)
		child->height=1;
	
	AVL* grandchild = y;
	bool chkError = false;
	while(!chkError && error->parent)
	{
		chkError = !error->chkHeight();
		if(chkError)
		{
			error=this->balance(error,child,grandchild);
			chkError = true;
		}
		grandchild=child;
		child=error;
		error=error->parent;
	}
	return y;			
}

void AVL::deleteNode()
{
	if(!this->parent)
		return;
	
	if(!this->lnode && !this->rnode)
	{
		if(this->parent->lnode == this)
			this->parent->lnode = nullptr;
		if(this->parent->rnode == this)
			this->parent->rnode = nullptr;
		this->lnode=nullptr;
		this->rnode=nullptr;	
	}
	else if(!this->lnode)
	{
		this->rnode->parent = this->parent;
		if(this->parent->lnode == this)
			this->parent->lnode = this->rnode;
		if(this->parent->rnode == this)
			this->parent->rnode = this->rnode;
		this->rnode=nullptr;		
	}
	else if(!this->rnode)	
	{
		this->lnode->parent = this->parent;
		if(this->parent->lnode == this)
			this->parent->lnode = this->lnode;
		if(this->parent->rnode == this)
			this->parent->rnode = this->lnode;
		this->lnode=nullptr;		
	}
	
	if(!this->lnode||!this->rnode)
	{
		this->height=-1;
		AVL* error = this->parent;
		AVL* child;
		AVL* grandchild;
		bool chkerror;
		while(error->parent)
		{
			chkerror = !error->chkHeight();
			if(chkerror)
			{
				int lh=-1,rh=-1;
				if(error->lnode)
					lh = error->lnode->height;
				if(error->rnode)
					rh = error->rnode->height;
				if(lh>=rh)
					child = error->lnode;
				else
					child = error->rnode;
				int lth=-1,rth=-1;
				if(child->lnode)
					lth = child->lnode->height;
				if(child->rnode)
					rth = child->rnode->height;
				if(lth>=rth)
					grandchild = child->lnode;
				else
					grandchild = child->rnode;
				error = this->balance(error, child, grandchild);								
			}
			error = error->parent;
		}
		return;
	}
	AVL* x = this->rnode;
	while(x && x->lnode)
		x = x->lnode;
	
	AVL* y  = new AVL(x->address,x->size,x->key);
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

bool AVL::Delete(Dictionary* d)
{
	AVL* x = this->getRoot();
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
				if(x->size==d->size)
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

AVL* AVL::Find(int k, bool equal)
{
	AVL* x = this->getRoot();
	AVL* y = nullptr;
	AVL* z = nullptr;
	while(x)
	{
		if(x->key<k)
			x=x->rnode;
		else
		{
			if(x->key==k)
				z = x;
			else
				y=x;
			x=x->lnode;		
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

AVL* AVL::getFirst()
{
	AVL* x = this->getRoot();
	while(x && x->lnode)
		x=x->lnode;
	return x;	
}

AVL* AVL::getNext()
{
	if(!this->parent)
		return nullptr;
	if(this->rnode)
	{
		AVL* x = this->rnode;
		while(x->lnode)
			x=x->lnode;
		return x;	
	}
	else
	{
		AVL* x = this;
		while(x && x->parent && x->parent->lnode!=x)
			x=x->parent;
		if(!x->parent)
			return nullptr;
		else
			return x->parent;		
	}		
}

int AVL::getHeight(AVL* x)
{
	if(!x)
		return -1;
	int lh=-1,rh=-1;
	if(x->lnode)
		lh = x->lnode->height;
	if(x->rnode)
		rh = x->rnode->height;
	if(this->getHeight(x->lnode)==-2||this->getHeight(x->rnode)==-2)
		return -2;
	if(lh>rh)
	{
		if(x->height!=lh+1)
			cout<<"Height was not updated :(\n";
		if((lh>rh+1)||(x->height!=lh+1))
			return -2;	
	}
	else
	{
		if(x->height!=rh+1)
			cout<<"Height was not updated :(\n";
		if((rh>lh+1)||(x->height!=rh+1))
			return -2;		
	}
	return x->height;				
}

bool AVL::Sanity()
{
	if(!BST::sanity())
		return false;
	if(this->getRoot())
	{
		if(this->getHeight(this->getRoot())==-2)
			return false;
	}
	return true;	
}

