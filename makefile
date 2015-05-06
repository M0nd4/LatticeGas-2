all:
	clang++ -I /usr/local/include/eigen3/  latticegas.cpp -o out && ./out

