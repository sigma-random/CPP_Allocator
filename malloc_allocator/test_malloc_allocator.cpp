#include <iostream>
#include <vector>
#include <algorithm>

#include "malloc_allocator.h"

/*
	g++ test_malloc_allocator.cpp -o test_malloc_allocator  --static  -g
*/


using namespace std; 


class MyClass
{
public:
	MyClass() { cout<<"MyClass::MyClass()"<<endl; };
	MyClass(int uid) { cout<<"MyClass::MyClass(int uid)"<<endl; };
	MyClass(int uid, string name) { cout<<"MyClass::MyClass(int uid, string name)"<<endl; };
	MyClass(const MyClass&) { cout<<"MyClass::MyClass(const MyClass&)"<<endl; };
	~MyClass() { cout<<"MyClass::~MyClass()"<<endl; };
	void operator =(const MyClass&) {};

public:
	int uid;
	string name;
};


void test_malloc_allocator()
{
	malloc_allocator<int> 	int_allocator;
	int* int_array;
	int size_array = 10;

	int_array = int_allocator.allocate(size_array);

	cout<<"int_array = "<<std::hex<<int_array<<endl;

	int_allocator.deallocate(int_array, size_array);

}


void test_std_int_vector()
{
	vector< int, std::allocator<int> >  int_vec(4);

	int_vec[0] = 0;
	int_vec[1] = 1;
	int_vec[2] = 2;
	int_vec[3] = 3;
	int_vec.push_back(8);
	int_vec.push_back(9);

	vector< int >::iterator itr;
	for(itr = int_vec.begin(); itr != int_vec.end(); itr++) {
		cout<<*itr<<endl;
	}	
}

void test_specific_int_vector()
{
	vector< int, malloc_allocator<int> >  int_vec(4);

	int_vec[0] = 0;
	int_vec[1] = 1;
	int_vec[2] = 2;
	int_vec[3] = 3;

	// int_vec.push_back(8);
	// int_vec.push_back(9);

	vector< int, malloc_allocator<int> >::iterator itr;
	for(itr = int_vec.begin(); itr != int_vec.end(); itr++) {
		cout<<*itr<<endl;
	}

}

void test_specific_string_vector()
{
	vector< string, malloc_allocator<string> >  str_vec(4);

	str_vec[0] = "0";
	str_vec[1] = "1";
	str_vec[2] = "2";
	str_vec[3] = "3";

	// str_vec.push_back("8");
	// str_vec.push_back("9");

	vector< string, malloc_allocator<string> >::iterator itr;
	for(itr = str_vec.begin(); itr != str_vec.end(); itr++) {
		cout<<*itr<<endl;
	}

}

void test_specific_class_vector()
{
	vector< MyClass, malloc_allocator<MyClass> >  class_vec(4);

	class_vec[0].uid = 0;
	class_vec[0].name = "class 0";

	class_vec[1].uid = 1;
	class_vec[1].name = "class 1";

	class_vec[2].uid = 2;
	class_vec[2].name = "class 2";

	class_vec[3].uid = 3;
	class_vec[3].name = "class 3";

	vector< MyClass, malloc_allocator<MyClass> >::iterator itr;
	for(itr = class_vec.begin(); itr != class_vec.end(); itr++) {
		cout<<(*itr).uid<<endl;
		cout<<(*itr).name<<endl;
	}

}

int main()
{
	
	test_malloc_allocator();

	test_std_int_vector();

	test_specific_int_vector();

	test_specific_string_vector();

	test_specific_class_vector();

	return(0);
}
	