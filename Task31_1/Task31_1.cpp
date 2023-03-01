#include <iostream>
#include<iostream>

template<typename T>
class SmartPointer {
public:
	SmartPointer(T* ptr) {
		ref = ptr;
		ref_count = (unsigned*)malloc(sizeof(unsigned));
		*ref_count = 1;
	}

	SmartPointer(SmartPointer& sptr) {
		ref = sptr.ref;
		ref_count = sptr.ref_count;
		++(*ref_count);
	}

	/* Перезаписываем оператор равенства (eqal), поэтому, когда вы установите
	 * один умный указатель в другой, число ссылок старого указателя
	 * уменьшится, а нового — увеличится.
	 */
	SmartPointer& operator=(SmartPointer& sptr) {
		/* Если уже присвоено объекту, удаляем одну ссылку. */
		if (*ref_count > 0) {
			remove();
		}
		if (this != &sptr) {
			ref = sptr.ref;
			ref_count = sptr.ref_count;
			++(*ref_count);
		}
		return *this;
	}

	~SmartPointer() {
		remove(); // удаляем одну ссылку на объект.
	}

	T operator*() {
		return *ref;
	}

protected:
	void remove() {
		--(*ref_count);
		if (ref_count == 0) {
			delete ref;
			free(ref_count);
			ref = NULL;
			ref_count = NULL;
		}
	}

	T* ref;
	unsigned* ref_count;
};

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
/*
* #include <iostream>

class Toy {
	std::string nameToy;
public:
	Toy() : nameToy("Some toy") {};
	Toy(const std::string name) : nameToy(name) {};
	~Toy() {};
	std::string& get_name() {
		return nameToy;
	}
};

class shared_ptr_toy {
	Toy* pToy;
	int* num;
public:
	shared_ptr_toy();
	shared_ptr_toy(const Toy& t);
	shared_ptr_toy(const shared_ptr_toy& pt);
	shared_ptr_toy& operator=(const shared_ptr_toy& pt);
	~shared_ptr_toy();
};

shared_ptr_toy::shared_ptr_toy() : pToy(nullptr), num(nullptr) {
	std::cout << "--Create empty ptr" << std::endl;
}

shared_ptr_toy::shared_ptr_toy(const Toy& t) : pToy(new Toy(t)), num(new int(1)) {
	std::cout << "--Create ptr: " << pToy->get_name() << " all_ptr = " << *num << std::endl;
}

shared_ptr_toy::shared_ptr_toy(const shared_ptr_toy& pt) {
	pToy = pt.pToy;
	num = pt.num;
	++(*num);
	std::cout << "--Copy ptr: " << pToy->get_name() << " all_ptr = " << *num << std::endl;
}

shared_ptr_toy& shared_ptr_toy::operator=(const shared_ptr_toy& pt) {
	if (this == &pt) {
		return *this;
	}

	if (--(*num) == 0) {
		std::cout << "--Delete ptr oper=: " << pToy->get_name() << " all_ptr = " << *num << std::endl;
		delete num;
		delete pToy;
	}

	if (pt.pToy) {
		pToy = pt.pToy;
		num = pt.num;
		++(*num);
		std::cout << "--Oper= ptr: " << pToy->get_name() << " all_ptr = " << *num << std::endl;
		return *this;
	}

	pToy=nullptr;
	num = nullptr;
	std::cout << "--Oper= nullptr " << std::endl;
	return *this;
}

shared_ptr_toy::~shared_ptr_toy() {
	if (pToy) {
		if (--(*num) == 0) {
			std::cout << "--Delete ptr: " << pToy->get_name() << " all_ptr = " << *num << std::endl;
			delete num;
			delete pToy;
		} else {
			std::cout << "--Delete ptr: " << pToy->get_name() << " all_ptr = " << *num << std::endl;
		}
	} else {
		std::cout << "--Delete nullptr: " << std::endl;
	}
}

shared_ptr_toy make_shared_toy(const Toy& toy) {
	shared_ptr_toy ptr(toy);
	return ptr;
}

shared_ptr_toy make_shared_toy(const std::string& str) {
	Toy toy(str);
	shared_ptr_toy ptr(toy);
	return ptr;
}

int main() {
	Toy toyO("Toy 1");

	std::cout << "1" << std::endl;
	shared_ptr_toy ptr1 = make_shared_toy(toyO);

	std::cout << "2" << std::endl;
	shared_ptr_toy ptr2 = ptr1;

	std::cout << "3" << std::endl;
	shared_ptr_toy ptr3;

	std::cout << "4" << std::endl;
	ptr2 = ptr3;

	std::cout << "5" << std::endl;
	shared_ptr_toy ptr4 = make_shared_toy("Toy 2");

	std::cout << "6" << std::endl;
	ptr1 = ptr4;
	std::cout << "7" << std::endl;

}
*/
/*
include <iostream>

class Toy
{
	std::string name;

public:
	Toy() : name("Some toy") {}

	Toy(std::string _name) : name(_name) {}

	std::string getName()
	{
		return name;
	}

	~Toy() {}
};

class shared_ptr_toy
{
	Toy* ptr = nullptr;
	int* refCount;

public:
	shared_ptr_toy()
	{
		ptr = new Toy();
		refCount = new int(1);
	}

	shared_ptr_toy(std::string _name)
	{
		ptr = new Toy(_name);
		refCount = new int(1);
	}

	shared_ptr_toy(const shared_ptr_toy& other)
	{
		this->ptr = other.ptr;
		this->refCount = other.refCount;
		refIncrease();
	}

	shared_ptr_toy& operator =(const shared_ptr_toy& other)
	{
	if (this == &other) return *this;
		if (this->ptr != nullptr)
		{
			this->refDicrease();
		}

		this->ptr = other.ptr;
		this->refCount = other.refCount;
		this->refIncrease();
		return *this;
	}

	~shared_ptr_toy()
	{
		refDicrease();
	}

private:
	void refIncrease()
	{
		++(*this->refCount);
	}

	void refDicrease()
	{
		--(*this->refCount);
		if (*this->refCount == 0)
		{
			delete ptr;
			delete refCount;
		}
	}
};

shared_ptr_toy make_shared(std::string name)
{
	return shared_ptr_toy(name);
}

shared_ptr_toy make_share(Toy* toy)
{
	return shared_ptr_toy(toy->getName());
}

class Dog
{
	std::string name;
	int age = 0;
	shared_ptr_toy lovelyToy;

public:
	Dog() : name("Some name"), age(0) {}

	Dog(std::string _name) : name(_name), age(0) {}

	Dog(std::string _name, int _age, shared_ptr_toy _toy) : name(_name), lovelyToy(_toy)
	{
		if (_age >= 0 && _age < 30)
		{
			age = _age;
		}
		else
		{
			age = 0;
		}
	}

	void copyLovelyToy(const shared_ptr_toy& other)
	{
		this->lovelyToy = other;
	}

	~Dog() {}
};

int main()
{
	shared_ptr_toy ball = make_shared("Ball");

	Dog a("Sharik", 10, ball);

	return 0;
}
*/