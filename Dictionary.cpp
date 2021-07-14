#ifndef di
#define di
class Dictionary
{
	public:
		int key;
		int address;
		int size;
		
		Dictionary();
		Dictionary(int address, int size, int key);
		virtual Dictionary* Insert(int address, int size, int key){};
		virtual bool Delete(Dictionary* d){};
		virtual Dictionary* Find(int key, bool equal){};
		virtual Dictionary* getFirst(){};
		virtual Dictionary* getNext(){};
		virtual bool Sanity(){};
};

Dictionary::Dictionary()
{
	key=-1;	
	size=-1;
	address=-1;
}

Dictionary::Dictionary(int address, int size, int key)
{
	this->key = key;
	this->address = address;
	this->size = size;
}

#endif
