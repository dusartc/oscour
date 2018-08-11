#ifndef JOUEUR_HPP
#define JOUEUR_HPP

class Joueur {
	public:
		int x;
		int y;
		bool nextmove;
		bool momentum;

		void avance();
		void saute();
		void sautavant();

		Joueur();
};

#endif
