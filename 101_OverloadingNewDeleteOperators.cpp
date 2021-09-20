101 _ Overloading New and Delete Operators _ C++   

//why we need to overload New and delete?
/*
	-sometime in some classes, we need to specialize the storage mechanism
		-eg: to  speedup the creation of object
		- to use the memory, that has been already used  by another object of the same class.
	-since, C++ doesnt provide GARBAGE COLLECTION, by overloading new and delete-- we can  provide GARBAGE COLLECTION, for our object.
	i.e., whenever our objects are no longer needed, they’ll be deleted automatically.

*/

//what does new operator do?  Short ans: mem.alloc
/*
Long Ans:
	-when we create an object of a class, say
Student *rs_ptr = new Student; // class Student
	-Two things takes place: (new “keyword” is responsible for both these actions)
		1. MEMORY ALLOCATION  (by calling the new “operator” for mem.alloc)
		2.OBJECT CONSTRUCTION (calling the Constructor of the class)
the new “OPERATOR” allows us to change the memory allocation technique or method, BUT doesnt have any impact over the responsibility of calling the constructor. That job of calling the constructor is done by the new “KEYWORD”

Therefore, overloading will only change the mem.allocation technique,we don’t have anything to do with calling constructor.

So, we will be writing OPERATOR FTN, which will be called when allocating memory for the object.

*/

// since ftns like malloc, free are present in <cstdlib> header, so include <cstdlib>

#include <iostream>
#include <cstdlib>  //we need malloc and free functions
#include <stdexcept> //since we need bad_alloc exception
using namespace std;
class Student{
string name; //privater var
int age;    //private var
public:
    Student(){  //default constructor
        name = "noname";
        age = 0;
    }
    Student(string name,int age){  //overloaded constructor
        this->name = name;
        this->age = age;
    }
    void disp(){
        cout<<"Name: "<<name<<"\nAge: "<<age<<endl;
    }
    //Overloading new and delete operator
    /*
    when new and delete operator are overloaded INSIDE THE CLASS,
    then the overloaded operator ftn will be called, whenever the object is created.
    If the new and delete operator are OVERLOADED GLOBALLY, i.e., OUTSIDE THE CLASS,
    then the overloaded operator ftn will be called, whenever we use new and delete in our code.
    i.e., GLOBAL SCOPE.
    */
    //Overloading new and delete operator
    /*since new returns the memory address, its a pointer that can hold any type.
    So, use void* as return type*/
    void *operator new(size_t size){ //size_t is a datatype, which can hold the LARGEST SINGLE piece of memory that can be allocated (or)
                                    //the size variable contains the no.of bytes we want to allocate
        void *ptr;
        cout<<"Overloaded new operator ftn called..\nsize is: "<<size<<endl;
        ptr = malloc(size);
        if(!ptr){   //if not alloacated
            bad_alloc ba; //throw exception
        }
        return ptr;   //return the pointer before end of the ftn
    }
    //Overloading delete operator
    void operator delete(void *pointer){ //delete operator doesnt return anything(i.e., void) and it takes 1 parameter i.e., the memory address(void *pointer)
        cout<<"Overloaded delete operator ftn called.."<<endl;
        free(pointer);  // free the allocated memory
    }
};
int main(){
    //create object
    Student *rsptr;
    //Since,allocating mem thru overloaded new ftn throws exception, if fails.So, keep it inside try block
    try{                    //try block
    rsptr = new Student("RS",34);
    rsptr->disp();
    delete rsptr;
    }catch(bad_alloc b){   //catch block
        cout<<b.what()<<endl; //call what()method of badalloc exception
     }
    return 0;
}
