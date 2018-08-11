#include "macro.hpp"
#include "map.hpp"
#include "snake.hpp"
#include <iostream>

int main(){
	Snake s;
	Map m(s, 20);
	m.update();
	std::cout << m.print() << std::endl;
	return 0;
}