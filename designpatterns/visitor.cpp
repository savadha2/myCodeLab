#include <iostream>
#include <string>


class Cat; 
class Dog;

class PetVisitor{
public:
	virtual void visit(Cat* p) = 0;
	virtual void visit(Dog* p) = 0;
};


class Pet{
private:
	std::string color_;
public:
	Pet(std::string color): color_(color){}
	virtual void accept(PetVisitor& v) = 0;
	std::string get_color() const{
		return color_;
	}

};
template <typename Derived>
class Visitable: public Pet{
	//using Pet::Pet;
public:
	Visitable(std::string color): Pet(color){}
	void accept(PetVisitor& v){
		v.visit(static_cast<Derived*>(this));
	}
};

class Cat: public Visitable<Cat>{
public:
	Cat(std::string color): Visitable<Cat>(color){}
	//virtual void accept(PetVisitor& v){ v.visit(this);}

};

class Dog: public Visitable<Dog>{
public:
	Dog(std::string color): Visitable<Dog>(color){}
	//virtual void accept(PetVisitor& v){ v.visit(this);}
};


class FeedVisitor: public PetVisitor{
public:
	virtual void visit(Cat* cat){
		std::cout<<"Feed "<<cat->get_color()<<" Cat Dal"<<std::endl;
	}
	virtual void visit(Dog* dog){
		std::cout<<"Feed "<<dog->get_color()<<" Dog Spinach"<<std::endl;
	}
};


int main(int argc, char* argv[]){
	Pet* cat = new Cat("White");
	Pet* dog = new Dog("Brown");
	FeedVisitor fv;

	cat->accept(fv);
	dog->accept(fv);
	return 0;
}