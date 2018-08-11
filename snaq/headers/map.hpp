#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <string>
#include "snake.hpp"

class Map {
	private :
		Snake& _snake;
		std::vector< std::vector<int> > _map;
		std::vector<int> _bouffe;
		int _size;

	public:
		bool end();
		void update();
		void move_snake(std::vector<int> v);
		std::string print();
		Map(Snake& snake, int s);

};

#endif