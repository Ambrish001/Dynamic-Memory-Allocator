#ifndef tr
#define tr
#include"Dictionary.cpp"
class Tree: public Dictionary
{
	public:
		Tree* lnode = nullptr;
		Tree* rnode = nullptr;
		Tree* parent = nullptr;
		
		Tree(): Dictionary(-1,-1,-1)
		{
			this->lnode = nullptr;
			this->rnode = nullptr;
			this->parent = nullptr;
		};
		Tree(int address, int size, int key): Dictionary(address, size, key)
		{
			this->lnode = nullptr;
			this->rnode = nullptr;
			this->parent = nullptr;
		};
		virtual Tree* Insert(int address, int size, int key){};
		virtual bool Delete(Dictionary* d){};
		virtual Tree* Find(int key, bool equal){};
		virtual Tree* getFirst(){};
		virtual Tree* getNext(){};
		virtual bool sanity(){};
};
#endif
