#include <iostream>

class Car
{
public:
	virtual ~Car(); // Use this to be able to delete properly any type of instantiation we do -> specially when using new
	virtual void Move()
	{
		OnMove();
		pos += vel * time;
	}// Polymorphism -> many forms
	// Pure virtual function can have bodies
	// All virtual does is to convert a class into an abstract class and prevent it's instantiation
	// This will then prompt you to define your own implementation of the funciton in the object (child) you are creating

	// With the above example, we create a function that will be called by all children and we create an internal function
	// that can be modified by the children yet will run the whole process defined inside the Move() function
protected:
	virtual void OnMove() = 0;

	int pos = 0;
	int vel = 0;
};

class Tesla : public Car
{
public:
	void OnMove() {/* Turn GPS On;*/ pos += 10; } // Function overriding
};

void Test()
{
	Tesla myTesla;
	myTesla.Move(); // Who's move should I call? -> Tesla::Move(myTesla) -> This is what the compiler sees
	// .Move() => No argument == This is called a zero paramater and this means that the object instantiated is being passed to know
	// who's function to call
	Car* ptr = &myTesla;
	ptr->Move(); // Compiler always resolves the call based on the caller's type
	// Virtual does the casting automatically for you based on the memory you have right now
	// It makes a pointer be able to take into other forms
	// V-Table is a lookup table

	Car* ptr2 = new Tesla;
	delete ptr2;

	// As soon as you have a virtual somewhere, always add a virtual destructor. Same applies to polymorphic classes	
}