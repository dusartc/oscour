#include <iostream>
#include "map.cpp"
#include "joueur.cpp"
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
using namespace std;

int main(int argc, char *argv[]){
	srand(time(NULL));
	Map m;
	Joueur j;
	bool end = false;
	string s;
	m.addObs(5);
	m.addObs(15);
	m.addObs(20);
	m.addObs(55);
	m.addObs(95);
//	cout << "joueur x : " << j.x << endl;
	while(!end) {
		
		s = "o";
		for(int i=j.x+1;i<min(m._longueur,j.x+10);i++){
			if(find(m._obs.begin(), m._obs.end(), i) != m._obs.end()) {
				s += "|";
			} else {
				s += "_";
			}		
		}	
		s += " fitness : ";

		cout << s << j.x << endl;
		for (vector<int>::iterator it = m._obs.begin(); it !=m. _obs.end(); it++){
			if( j.x == *it ){
				end = true;
				cout << "rip" << endl;
			} 
		}
		if(j.x == m._longueur) end = true;

		if(rand()%10+1 > 5){
			j.avance();
		} else {
			j.saute();
		}
		usleep(1000000);
		system("clear"); //degueulasse/20
	}
}
