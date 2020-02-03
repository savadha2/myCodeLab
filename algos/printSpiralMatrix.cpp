#include<vector>
#include<iostream>


using matrix_t = std::vector<std::vector<int>>;
void PrintSpiral(const matrix_t& spiral_matrix){

	int nrows = spiral_matrix.size();
	int ncols = spiral_matrix[0].size();
	int start_row = 0, start_col = 0;
	int nelems = nrows * ncols;
	int print_counter = 0;
	auto printelem = [&spiral_matrix](size_t r, size_t c)->void{std::cout<<spiral_matrix[r][c]<<" ";};
	while(true){
		for(int c = start_col; c < ncols; ++c){
			printelem(start_row, c);
		}

		for(int r = start_row+1; r < nrows; ++r){
			printelem(r, ncols-1);
		}

		for(int c = ncols-2; c >=start_col; --c){
			printelem(nrows-1, c);
		}

		for(int r = nrows - 2; r>start_row; --r){
			printelem(r, start_col);
		}

		start_row++;
		start_col++;
		nrows--;
		ncols--;
		if(ncols < 0 || nrows < 0) break;
		if(ncols-1 < start_col || nrows - 1 < start_row) break;

	}
	std::cout<<std::endl;
	
}

int main(int argc, char* argv []){
	matrix_t spiral_matrix = {{1, 2, 3, 4}, {12, 13 , 14, 5},{11, 16, 15, 6}, {10, 9, 8, 7}};
	PrintSpiral(spiral_matrix);
	return 0;
}