#include <iostream>
#include<iostream>

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
public:
	smart_ptr_toy()
	{
		obj = new Toy("SomeName");
	};
	smart_ptr_toy(std::string _name)
	{
		obj = new Toy(_name);
	}
	smart_ptr_toy(const smart_ptr_toy* other)
	{
		obj = new Toy(*other->obj);
	}
	smart_ptr_toy& operator=(const smart_ptr_toy* other)
	{
		if (this == other)
			return *this;
		if (obj != nullptr)
			delete obj;
		obj = new Toy(*other->obj);
		return *this;
	}
	~smart_ptr_toy() { delete obj; };
};
class Dog
{
private:
	std::string name;
	int age;
	std::shared_ptr<Toy> lovelyToy;
public:
	Dog(std::string _name, std::shared_ptr<Toy> toy, int _age) :name(_name),lovelyToy(toy)
	{
		if (_age >= 0 && _age < 20)
			age = _age;
		
	}
	Dog(std::string _name) :Dog(_name,std::make_shared<Toy>("SomeToy"), 0) {};
	Dog(int _age) : Dog("None", std::make_shared<Toy>("SomeToy"), _age) {};
	Dog():Dog("None", std::make_shared<Toy>("SomeToy"), 0) {};
	void copyToy(const Dog& oth)
	{
		lovelyToy = oth.lovelyToy;
	}
};

int main()
{
	std::shared_ptr<Toy> Boll = std::make_shared<Toy>("Ball");
	std::shared_ptr<Toy> Bon = std::make_shared<Toy>("Bon");

	Dog a("steik", Boll, 10);
	Dog b("smoll", Boll, 4); 
	Dog c("krak", Bon, 2); 
	Dog d("slon", Boll, 8);
	Dog e("robert", Bon, 11);
	e.copyToy(b);
	Boll.reset();
	Bon.reset();
	return 0;
}
