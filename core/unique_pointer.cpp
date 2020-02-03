#include<iostream>
#include <memory>


class Base{
public:
	Base() = default;
	virtual void print(){
		std::cout<<"I am base"<<std::endl;
	}
	virtual ~Base(){
		std::cout<<"Destroying Base!"<<std::endl;
	}
};

class Derived : public Base{
public:
	Derived() = default;
	virtual ~Derived() {
		std::cout<<"Destroying Derived!"<<std::endl;
	}
	void print(){
		std::cout<<"I am derived"<<std::endl;
	}
};


void UseRaw(Base* base){
	std::cout<<"--------------------"<<std::endl;
	std::cout<<"using raw "<<std::endl;
	base->print();
	std::cout<<"--------------------"<<std::endl;
}

void UseRawRef(Base& base){
	std::cout<<"--------------------"<<std::endl;
	std::cout<<"using raw ref "<<std::endl;
	base.print();
	std::cout<<"--------------------"<<std::endl;
}

/*create()
sink()
reseat();*/

void UseRef(std::unique_ptr<Base>& base){ //and try with move below - indicate possible reset, can also be a sink
	//auto copy(base.get()); // why is this not destroying the pointer? like in main?
	//auto copy(std::move(base));
	auto copy(base.get()); //base.get() is of type Base*, copy is of type Base* - not unique pointer
	std::cout<<"--------------------"<<std::endl;
	std::cout<<"using ref "<<std::endl;
	base->print();
	copy->print();
	std::cout<<base.get()<<std::endl;
	//std::cout<<copy<<std::endl;
	std::cout<<"--------------------"<<std::endl;

	//destructor not called when copy goes out of scope. why?
	//delete copy;
}

void UsePointer(std::unique_ptr<Base>* base){
	std::cout<<"--------------------"<<std::endl;
	std::cout<<"using Pointer "<<std::endl;
	base->get()->print();
	std::cout<<"--------------------"<<std::endl;
}

std::unique_ptr<Base> create(int choice){

	if(choice==0)
		return std::make_unique<Base>();
	else if(choice==1){
		return std::make_unique<Derived>();
	}else{
		throw;

	}

}

int main(int argc, char* argv[]){
	/*Example  - creation 1*/
	//Base* base = new(Base);
	//std::unique_ptr<Base> a(base);

	/*Example - */
	//delete base; // what happens here
	//Rule 1: don't delete a raw pointer if you use it to initialize unique ptr, 
	//unique pointer will take care of this for you

	//Creation 2
	//std::unique_ptr<Base> b(new (Base)); //Better you don't have to worry about Rule 1

	//Creation 3
	//std::unique_ptr<Base> c(b); // what happens here? what is this anyway?

	//creation 4
	//std::unique_ptr<Base> c(std::move(b)); // what is std::move - HINT: it does not move

	//b->print(); // what happens here
	//if(b) b->print(); // Rule 2: always check if unique pointer is valid.

	//creation 5
	//std::unique_ptr<Base> d = a;

	//creation 6
	
	//std::unique_ptr<Base> e(a.get()); - > Don't do it
	//a.release();
	//if(e) e->print();

	//creation 7.
	//std::unique_ptr<Base> f = std::make_unique<Base>(); 
	//Rule 3: prefer make shared as there is an exception safety issue with using raw pointer to construct - not covering here

	//returning unique pointer from function

	//passing unique pointer to function
	//UseRaw(a.get());
	//if(a) a->print(); // what happens here
	//UseRef(a);
	//UseRawRef(std::move(*a));
	//if(a) a->print();
	//UsePointer(&a);
	//UseRef(a);
	//if(a) a->print();
	//UseRef(std::move(a)); // why does this fail

	//unique pointers in class - pitfall

	//when to use unique pointers

	//when to use pointers at all
	/*Base* h(base);
	auto m = std::move(a);
	m->print();
	if(a) a->print();*/
	//delete h;
	std::unique_ptr<Base> m = create(0); //create base
	m->print();//i am base
	std::unique_ptr<Base> n = create(1); // create derived
	n->print();//i am derived
	return 0;
}