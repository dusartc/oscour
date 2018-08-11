#include "map.hpp"
#include "snake.hpp"
#include <iostream>
#include "macro.hpp"
#include <stdlib.h>
#include <time.h>

int main(){
	Snake s;
	Map m(s, 20);
	m.update();
	std::cout << m.print() << std::endl;

	int i;
	srand(time(NULL));
	while(!m.end()){
		i = rand() % 4;
		if(i == 0) m.move_snake(UP);
		if(i == 1) m.move_snake(DOWN);
		if(i == 2) m.move_snake(LEFT);
		if(i == 3) m.move_snake(RIGHT);
		m.update();
		std::cout << m.print() << std::endl;
	}
	return 0;
}