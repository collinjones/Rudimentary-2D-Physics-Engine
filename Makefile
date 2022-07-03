INCLUDE_PATHS = -Iinclude/

all:
	g++ -std=c++17 $(INCLUDE_PATHS) main.cpp -ISDL2/include -LSDL2/lib -Wall -lmingw32 -lSDL2main -lSDL2 -o main