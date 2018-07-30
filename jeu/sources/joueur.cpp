#include "joueur.hpp"

Joueur::Joueur() {
	x = 0;
	y = 0;
	nextmove = false;
	momentum = false;
}

void Joueur::avance() {
	x += 1;
}

void Joueur::saute() {
	if(nextmove){
		y-=1;
	} else {
		y+=1;
	}
}

void Joueur::sautavant() {
	x+=1;
	if(momentum){
		y-=1;
	} else {
		y+=1;
	}
}
