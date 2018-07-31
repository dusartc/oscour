#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "map.hpp"
#include "joueur.hpp"
using namespace std;

int main(int argc, char *argv[]){
	srand(time(NULL));
	Map m;
	Joueur j;
	bool end = false;
	string premiereLigne, deuxiemeLigne;
	m.addObs(5);
	m.addObs(15);
	m.addObs(20);
	m.addObs(55);
	m.addObs(95);
	m.addPtero(12);
//	cout << "joueur x : " << j.x << endl;
	while(!end) {
		if(j.y == 0){
			premiereLigne = " ";
			deuxiemeLigne = "o";
		} else {
			premiereLigne = "o";
			deuxiemeLigne = "_";
		}
		for(int i=j.x+1;i<min(m._longueur,j.x+10);i++){
			if(find(m._pteros.begin(), m._pteros.end(), i) != m._pteros.end()) {
				premiereLigne += "*";
			} else {
				premiereLigne += " ";
			}		
		}
		for(int i=j.x+1;i<min(m._longueur,j.x+10);i++){
			if(find(m._obs.begin(), m._obs.end(), i) != m._obs.end()) {
				deuxiemeLigne += "|";
			} else {
				deuxiemeLigne += "_";
			}		
		}	
		deuxiemeLigne += " fitness : ";

		cout << premiereLigne << "\n" << deuxiemeLigne << j.x << endl;
		for (vector<int>::iterator it = m._obs.begin(); it != m. _obs.end(); it++){
			if( j.x == *it and j.y==0){
				end = true;
				cout << "rip" << endl;
			} 
		}
		if(j.y == 1){
			for (vector<int>::iterator it = m._pteros.begin(); it != m. _pteros.end(); it++){
				if( j.y == *it){
					end = true;
					cout << "rip" << endl;
				} 
			}
		}
		if(j.x == m._longueur) end = true;

		if(j.momentum){
			j.sautavant();
			j.momentum = false;
		} else if(j.nextmove){
			j.saute();
			j.nextmove = false;
		} else {
			if(rand()%10+1 > 5){
				if(rand()%10+1 > 5){
					j.sautavant();
					j.momentum = true;
				} else {
					j.saute();
					j.nextmove = true;
				}
			} else {
				j.avance();
			}
		}
		m.process();
		usleep(1000000);
		system("clear"); //degueulasse/20
	}
}
