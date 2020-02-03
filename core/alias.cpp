#include<algorithm>
#include<utility>
#include<iostream>
#include<vector>

template<class T>
using interval_t = std::pair<T, T>;

int main(int argc, char* argv[]){
	std::vector<interval_t<int>> a={{1, 2}, {3, 4}};
	a.emplace_back(6, 7);

	for(const auto& i: a){
		std::cout<<"["<<i.first<<", "<<i.second<<"]"<<std::endl;
	}
	//std::vector<std::pair<int, int>> a = {{1,2}};
	return 0;
}