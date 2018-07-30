#include "joueur.hpp"

Joueur::Joueur() {
	x = 0;
	y = 0;
}

void Joueur::avance() {
	x += 1;
}

void Joueur::saute() {
	x += 3;
}
