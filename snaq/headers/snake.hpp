#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <list>
#include <vector>

class Snake {
	public:
		std::list< std::vector<int> > _snake;
		
		void move(std::vector<int> v, bool mange);
		bool dead();
		Snake();
};

#endif