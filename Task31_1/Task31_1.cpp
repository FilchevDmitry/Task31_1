#include <iostream>

class Toy
{
private:
	std::string name;
public:
	Toy(std::string _name) :name(_name) {};
	Toy() :Toy("SomeToy") {};
};

class shared_ptr_toy
{
private:
	Toy* obj;
	int count = 0;
	void remove()
	{
		--(count);
		if (count == 0)
		{
			delete obj;
			count = 0;
		}
	}
public:
	shared_ptr_toy(Toy* toy)
	{
		obj = toy;
		count=1;
	};
	shared_ptr_toy(const shared_ptr_toy* other)
	{
		obj = other->obj;
		count = other->count;
		++(count);
	}
	shared_ptr_toy& operator=(const shared_ptr_toy* other)
	{
		if (count > 0)
			remove();
		if (this != other)
		{
			obj = other->obj;
			count = other->count;
			++(count);
		}
		return *this;
	}
	~shared_ptr_toy()
	{
		remove();
	};
};


int main()
{
	Toy s("dfg");
	shared_ptr_toy b(s);

	return 0;
}