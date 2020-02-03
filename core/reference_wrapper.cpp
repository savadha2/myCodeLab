#include <functional>
#include <string>
#include <iostream>
#include <vector>

class Base{
public:
	std::string name_;
	Base(std::string name) : name_(name){}
	void printName(){
		std::cout<<"I am "<<name_<<std::endl;
	}
};

class Derived : public Base{
public:
	Derived(std::string name) : Base(name){}
};

std::vector<std::reference_wrapper<Base>> test_vector; 
void add_child(Base& base){
	test_vector.push_back(base);
}

int main(int argc, char* argv[]){
	Base b = Base("base");
	Derived d = Derived("derived");
	add_child(b);
	add_child(d);
	for(auto v : test_vector){
		v.get().printName();
	}
}