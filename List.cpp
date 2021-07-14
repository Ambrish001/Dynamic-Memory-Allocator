#include"Dictionary.cpp"

class List: public Dictionary
{
	public:
		List* next = nullptr;
		List* prev = nullptr;
		
		List():Dictionary(0,0,0)
		{
			this->prev = nullptr;
			this->next = nullptr;
		};
		List(int address, int size, int key):Dictionary(address, size, key)
		{
			this->prev = nullptr;
			this->next = nullptr;
		};
		virtual List* Insert(int address, int size, int key){};
		virtual bool Delete(Dictionary* d){};
		virtual List* Find(int k, bool equal){};
		virtual List* getFirst(){};
		virtual List* getNext(){};
		virtual bool Sanity(){};
};
