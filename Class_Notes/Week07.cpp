// Const correctness
// Const the data and const the address for every indirection you have
// Bitwise constness
// Conceptual constness

// Whenever you use the word const, you use Bitwise const to lock memory

//class PhoneBook
//{
//public:
//	struct Info
//	{
//		std::string name;
//	};
//
//	// Functions for iterating the contents
//	auto Reset() const { mCurrentIndex = 0; }
//	auto Next() const { mCurrentIndex++; }
//	const Info& GetNext() const { return mDatabase[ mCurrentIndex ]; }
//	auto end();
//
//private:
//	std::vector<Info> mDatabase;
//	mutable int mCurrentIndex;
//};
//
//void PrintAllContact(const PhoneBook& pb)
//{
//	pb.Reset();
//	while (true)
//	{
//		pb.GetNext();
//	}
//}

// If class uses iteration, we can use begin and end functions
// Mutable is used for achieving Conceptual constness
// It allows to change a variable despite the function being marked const
// Think of it as a back door to the code!
// 95% of time you wont use this, many people fuck it up!!!
// BE CAREFUL!!!!

void Test(int size)
{
	float f = 3.14f;

	// C - cast
	// Never use C cast!
	// It uses 2s compliment
	// Not reliable and you never know what it will actually do
	int i = (int)f;

	// C++ Cast
	int j = static_cast<int>(f);
	//static_cast;
	//dynamic_cast;
	//reinterpret_cast;
	//const_cast;

	// Static cast happens at build time - pre-compiler and linker
	// Dynamic cast happens at run time

	// Static array
	int myNums[100];
	// Dynamic instantiation
	int* myNums = new int[size];

	// Polymorphisms cannot be static_casted
	// Dynamic cast is used when you want to downcast

	/*Car* ptr = selectCar();
	Tesla* tpr = dynamic_cast<Tesla>(ptr);
	if (tpr != nullptr)
	{
		tpr->BineDogeCoin();
	*/
}

// Const cast allows you to take the const away and be able to manipulate it
// Another back door, but really big WTF!

// Proper way to print out a size_t is to use %zu

// Do not use new and delete anymore, use smart pointers!

// When you design a class, you want it to create the memory it will manage

// Make unique was created to immediately protect memory and avoid memory leaks
// Use unique for sole ownership
// Use shared for sharing data

// Type traits
// is_type_of -> 

// Syntax Error
// Linker Error
// RunTime Error -> hardest one to run into
// Static asserts are helpful to catch errors that will only appear under certain conditions 