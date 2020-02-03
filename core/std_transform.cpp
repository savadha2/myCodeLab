#include <iostream>
#include <vector>
#include <functional>


int main(int argc, char* argv[]){
	std::vector<double> a = {1, 2, 3};
	std::transform(a.begin(), a.end(), a.begin(), [&](double i){return i / a[a.size()-1];});
	std::for_each(a.begin(), a.end(), [](double i){std::cout<<i<<" ";});
	std::cout<<std::endl;
	return 0;
}