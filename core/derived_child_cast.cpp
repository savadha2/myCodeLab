#include<iostream>
#include<string>

class BaseSystem{
public:
	BaseSystem(std::string name):name_(name){}
	std::string name_;
	virtual void print() const{
		std::cout<<"I am "<<name_<<std::endl;
	}

	virtual void onemoreprint() const=0;


};

class ChildSystem: public BaseSystem{
public:
	ChildSystem(std::string name):BaseSystem(name){}
	void print() const override final{
		std::cout<<"I am "<<name_<<std::endl;
	}
	void onemoreprint() const override final{
		std::cout<<"I am in onemoreprint"<<std::endl;
	}
};

void castandprint(const BaseSystem& base){
	base.print();
	base.onemoreprint();
}

int main(int argc, char* argv[]){
	ChildSystem child = ChildSystem("Child");
	castandprint(child);
	return 0;
}