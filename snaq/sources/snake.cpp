#include "snake.hpp"
#include "macro.hpp"

using namespace std;

Snake::Snake() {
	for (int i = 5; i < 10; ++i){
		_snake.push_back({5,i});
	}
}

void Snake::move(vector<int> v, bool mange){
	_snake.push_front({_snake.front()[0] + v[0], _snake.front()[1] + v[1]});
	if(!mange){
		_snake.pop_back();
	}
}

bool Snake::dead(){
	vector<int> first = _snake.front();
	list< vector<int> > l = _snake;
	l.sort();
	l.unique();
	return l.size() != _snake.size();
}