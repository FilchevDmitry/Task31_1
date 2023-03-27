#include <iostream>

class Toy
{
private:
	std::string name;
public:
	Toy(std::string _name) :name(_name) {};
	Toy() :Toy("SomeToy") {};
};

class smart_ptr_toy
{
private:
	Toy* obj;
	int* counting;
	void remove() {
		--(*counting);
		if (counting == 0) {
			delete obj;
			obj = NULL;
			counting = NULL;
		}
	}
public:
	smart_ptr_toy()
	{
		obj = new Toy("SomeName");
	};
	smart_ptr_toy(std::string _name)
	{
		obj = new Toy(_name);
	}
	smart_ptr_toy(const smart_ptr_toy& other)
	{
		obj = new Toy(*other.obj);
		++(*counting);
	}
	smart_ptr_toy& operator=(const smart_ptr_toy* other)
	{
		if (*counting>0)
			remove();
		if (this != other) 
		{
			obj = new Toy(*other->obj);
			counting = other->counting;
			++(*counting);
		}
			
		return *this;
	}
	~smart_ptr_toy() 
	{
		remove();
	};
};


int main()
{

	return 0;
}
