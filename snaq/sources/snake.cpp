#include "snake.hpp"
#include "macro.hpp"
#include <iostream>

using namespace std;

Snake::Snake() {
	for (int i = 5; i < 10; ++i){
		_snake.push_back({5,i});
	}
	_done = LEFT;
	_cantdo = RIGHT;
}

void Snake::move(vector<int> v, bool mange){
	if(v == _cantdo) {
		move(_done, mange);
	} else {
		_snake.push_front({_snake.front()[0] + v[0], _snake.front()[1] + v[1]});
		_done = v;
		if(v == RIGHT) _cantdo = LEFT;
		if(v == LEFT) _cantdo = RIGHT;
		if(v == UP) _cantdo = DOWN;
		if(v == DOWN) _cantdo = UP;
		if(!mange){
			_snake.pop_back();
		}
	}
}

bool Snake::dead(){
	vector<int> first = _snake.front();
	list< vector<int> > l = _snake;
	l.sort();
	l.unique();
	return l.size() != _snake.size();
}