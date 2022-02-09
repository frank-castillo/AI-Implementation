#include <iostream>

/*
* Parameter passing
* 1- Pass by value
* 2- Pass by reference
* 3- Pass by pointer
* 4- Pass by const reference
*/

void Print(int i);

void Swap(int a, int b)
{
	int temp = a;
	a = b;
	b = temp;
}
// This wont swap anything, as it only swaps then local variables
// inside their scope and copy of the parameters

void Swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}
// This on the other hand will actually swap your local numbers
// What you pass as paramter is a memory address location

// Then what happens in this case?
void Swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void Test()
{
	int i = 42;

	int* iptr;
	iptr = &i;

	//int& iref;
	//iref = i; // This is not possible!

	// Reference variable can only be initialized, not assigned later on
	// That is becasue there is an implicit const to the memory it should address
	// & === *const -> equivalent

	int i = 42; // Initialization

	int j;
	j = 30; // Assignment

	///////////////////////////////////////////////////////////////

	// You always read "const" from right to left!

	char* c;				// c is a pointer to character
	const char* c;			// c is a pointer to character constant
	char* const c;			// c is a constant pointer to a character
	const char* const c;	// c is a constant pointer to a character constant
	const char& c;			// c is a reference to character constant
}

class Elephant
{
public:
	void Dance() { /*888*/ };

	// This will be our non const interface
	int GetHP() { return hp; }
	float GetWeight() { return weight; }

	// This will be our const interface -> when we use const <type>& var;
	int GetHP() const { return hp; }
	float GetWeight() const { return weight; }

private:
	char lots[10000000];
	int hp;
	float weight;
};

void Print(int i);
void Print(const int& i);
void Print(Elephant e);
void Print(Elephant& e);
void Print(Elephant* e);
void Print(const Elephant& e)
{
	printf("hp = %d, w = %f", e.GetHP(), e.GetWeight());
}

// Both pointer and refrence are adresses to memory and they are seen as the same
// inside our memory
// The main difference is the way we use their syntax and how we use them!
// With address, we can use the variable as is; with poointer we need to dereference

// Size of variables
// int = 4 bytes
// float = 4 bytes
// char = 1 byte
// bool = 1 byte
// double = 8 bytes
// Elephant = 3000 bytes

// Size of pointers
// int = 8 bytes
// float = 8 bytes
// char = 8 bytes
// bool = 8 bytes
// double = 8 bytes
// Elephant = 8 bytes

// In memory, it wont matter if it ispointer or reference, they both will be
// 8 bytes, we are communicating where! not what they are (type)

// As we can see, the top section is not compatible in sizze with the bottom
// section. That is why we use dereference when using * (pointer)

// Callstack is all the memory your functions need
// Data column and adress columns are what make up the callstack
// Bottom of stack is higher adress and the top is lower address

// WHEN YOU WITE CODE, GIVE AS LITTLE CONTROL TO THEM AS POSSIBLE!
// JUST ALLOW THEM TO MAKE THEIR WORK AND PROTECT YOUR CODE!

// If what you are passing is a primitive type, just pass by value.
// Otherwise, pass as const <type>&
// If we want to use this safe technique, we must add const to our functions that are const
// This way the compiler will understand which functions can be used when the object is const