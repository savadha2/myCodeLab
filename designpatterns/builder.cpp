#include<iostream>
#include<string>
#include<vector>

class HTMLBuilder;

class HTMLElement{
private:
	friend class HTMLBuilder;
	std::string name_;
	std::string text_;
	std::vector<HTMLElement> children_;
public:
	HTMLElement(std::string name, std::string text): 
	name_(name), text_(text){}
	size_t numchildren() const{
		return children_.size();
	}

};

class HTMLBuilder{
	HTMLElement root_;
public:
	HTMLBuilder(const std::string& name, const std::string& text = std::string()): 
	root_(name, text){}
	HTMLBuilder& add_child(const std::string& name, const std::string& text){
		root_.children_.emplace_back(name, text);
		return *this;
	}
	operator HTMLElement() const{return root_;}

};

int main(int arcg, char* argv[]){
	HTMLElement el = HTMLBuilder("ul").add_child("li", "abcd").add_child("li", "cdef");
	std::cout<<"root has "<<el.numchildren()<<" children"<<std::endl;
	return 0;
}