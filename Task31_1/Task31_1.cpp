#include<iostream>
#include<string>

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
	int* count;
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
		count = new int(1);
	};
	shared_ptr_toy(std::string _name)
	{
		obj = new Toy(_name);
		count =new int(1);
	};
	shared_ptr_toy(const shared_ptr_toy* other)
	{
		obj = other->obj;
		
		++(*count);
	}
	shared_ptr_toy& operator=(const shared_ptr_toy* other)
	{
		if (*count > 0)
			remove();
		if (this != other)
		{
			obj = other->obj;
			++(*count);
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
shared_ptr_toy make_shared_toy(std::string& _name)
{
	return shared_ptr_toy(_name);
};

class Dog
{
private:
	std::string name;
	int age;
	shared_ptr_toy lovelyToy;
public:
	Dog(std::string _name, shared_ptr_toy(toy), int _age) :name(_name), lovelyToy(toy)
	{
		if (_age >= 0 && _age < 20)
			age = _age;
	}
	Dog(std::string _name) :Dog(_name, shared_ptr_toy("SomeToy"), 0) {};
	Dog(int _age) : Dog("None", shared_ptr_toy("SomeToy"), _age) {};
	Dog() :Dog("None", shared_ptr_toy("SomeToy"), 0) {};

};

int main()
{
	shared_ptr_toy s("green");
	shared_ptr_toy d(s);
	shared_ptr_toy f(s);
	std::cout << "end";


	return 0;
}