#include<iostream>
#include<string>
class shared_ptr_toy;
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
	int* count=0;
	void remove()
	{
		--(*count);
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
		count=new int(1);
	};

	shared_ptr_toy(const shared_ptr_toy& other)
	{
		obj = other.obj;
		count = other.count;
		++*count;
	}
	shared_ptr_toy& operator=(const shared_ptr_toy* other)
	{
		if (*count > 0)
			remove();
		if (this != other)
		{
			obj = other->obj;
			count = other->count;
			++*count;
		}
		return *this;
	}
	~shared_ptr_toy() 
	{ 
		remove(); 
	}
};
shared_ptr_toy make_shared_toy(Toy* toy)
{
	return shared_ptr_toy(toy);
};
shared_ptr_toy make_shared_toy(const std::string& _name)
{
	return shared_ptr_toy(new Toy(_name));
};

//class Dog
//{
//private:
//	std::string name;
//	int age;
//	shared_ptr_toy lovelyToy;
//public:
//	Dog(std::string _name, make_shared_toy toy, int _age) :name(_name), lovelyToy(toy)
//	{
//		if (_age >= 0 && _age < 20)
//			age = _age;
//	}
//	Dog(std::string _name) :Dog(_name, make_shared_toy("SomeToy"), 0) {};
//	Dog(shared_ptr_toy(toy)) :Dog("None", toy, 0) {};
//	Dog(int _age) : Dog("None", make_shared_toy("SomeToy"), _age) {};
//	Dog() :Dog("None", make_shared_toy("SomeToy"), 0) {};
//
//};

int main()
{

	shared_ptr_toy ball1= make_shared_toy("boll");
	shared_ptr_toy ball2 = ball1;
	
	std::cout << "end";


	return 0;
}