#include<iostream>
#include<vector>

int main(int argc, char* argv[]){
	std::vector<int> a = {1, 2, 3};
	std::vector<int> b = {1, 2, 4};
	std::cout<<(a<b)<<std::endl;
}