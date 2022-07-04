all:
	g++ -std=c++17 main.cpp -IEigen -ISDL2/include -LSDL2/lib -Wall -lmingw32 -lSDL2main -lSDL2 -o main