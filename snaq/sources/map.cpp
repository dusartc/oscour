#include <string>
#include "map.hpp"
#include "macro.hpp"
#include <iostream>
#include <sstream>

using namespace std;


Map::Map(Snake& snake, int s) : _snake(snake) {
	_size = s;
	_bouffe.push_back(4);
	_bouffe.push_back(4);
	_map.resize(s);
	for (int i = 0; i < s; i++) {
		_map[i].resize(s);
	}
}

void Map::move_snake(vector<int> v){
	if(v[0] == _bouffe[0] && v[1] == _bouffe[1]) {
		_snake.move(v, true);
		//TODO gen nouvelle bouffe
		return;
	}
	_snake.move(v, false);
}

void Map::update(){
	for (int i = 0; i < _size; i++) {
		for (int j = 0; j < _size; j++) {
			_map[i][j] = 0;
		}
	}
	for (list< vector<int> >::iterator lit = _snake._snake.begin(); lit != _snake._snake.end(); lit++) {
		_map[(*lit)[0]][(*lit)[1]] = 1;
	}
	_map[_bouffe[0]][_bouffe[1]] = 2;
}

string Map::print(){
	string ans;
	for (int i = 0; i < _size; i++) {
		for (int j = 0; j < _size; j++) {
			if(_map[i][j] == 0) {
				ans += ".";
			}
			if(_map[i][j] == 1) {
				ans += "+";
			}
			if(_map[i][j] == 2) {
				ans += "O";
			}
		}
		ans += "\n";
	}
	return ans;
}

bool Map::end(){
	return _snake.dead() && ((_snake._snake.front()[0] < 0 || _snake._snake.front()[0] > _size) || (_snake._snake.front()[1] < 0 || _snake._snake.front()[1] > _size));
}