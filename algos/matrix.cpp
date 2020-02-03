#include<vector>
#include<iostream>
#include<typeinfo>
#include<type_traits>
template<class T>
class Matrix{
	private:
	int nrows_, ncols_;
	std::vector<std::vector<T>> mat_;
	public:
	explicit Matrix(int nrows, int ncols):  nrows_(nrows), ncols_(ncols), mat_(nrows, std::vector<T>(ncols)){}
	//Matrix() = delete;
	void print(){
		for(int i = 0; i < nrows_; ++i){
			for(int j=0; j< ncols_; ++j){
				std::cout<<mat_[i][j]<<" ";
			}
			std::cout<<std::endl;
		}
	}
	//explicit Matrix()
};

int main(int argc, char* argv[]){
	int nrows = 3, ncols = 3;
	Matrix<double> mat(nrows, ncols);
	Matrix<double> mat2(mat);
	mat.print();
	mat2.print();
	Matrix<int> mat3(nrows, ncols);
	std::cout<<std::is_same<decltype(mat), decltype(mat3)>::value<<std::endl;
	return 0;
}