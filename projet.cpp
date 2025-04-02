#include "coord.hpp"
#include "grille.hpp"
#include "termite.hpp"

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

// Constantes/Paramètres

const float densiteBrindille = 0.20;
const int nbTermites = 1;
const int nbTunnels = 3;

// Fonctions nous permettant la cohérence ainsi que la visualisation de la simulation

//* S'assure que tout est cohérent dans la simulation
//* @param[in] g       : Grille
//* @param[in] colonie : vecteur de Termite
void assureCoherence(const Grille &g, const vector<Termite> &colonie) {
	// Cohérence du point de vue des termites
	for (int i = 0; i < int(colonie.size()); i += 1) {
		// Cohérence de l'indice des termites
		if (colonie[i].idTermite() != i)
			throw logic_error("Un termite est mal rangé dans le vecteur de termite !");

		// Cohérence termite-grille
		if (g.numeroTermite(colonie[i].coordonnee()) != colonie[i].idTermite()) 
			throw logic_error("Un termite pense être dans une case qui ne le contient pas !");
	}

	// Cohérence du point de vue de la grille (grille-termite)
	for (int i = 0; i < tailleGrille; i += 1) {
		for (int j = 0; j < tailleGrille; j += 1) {
			Coord c = Coord{i, j};
			int idT = g.numeroTermite(c);
			if (idT != -1) {
				if (idT < int(colonie.size())) {
					if (colonie[idT].coordonnee() != c)
						throw logic_error("Une case contient un termite qui pense être ailleurs !");
				} else throw logic_error("Une case contient un termite qui n'existe pas !");
			}
		}
	}
}


//* Affiche la grille à l'état 
//* @param[in] g       : Grille
//* @param[in] colonie : vecteur de Termite
void afficheJeu(const Grille &g, const vector<Termite> &colonie) {
	for (int y = tailleGrille-1; y >= 0; y -= 1) {
		cout << endl;
		for (int x = 0; x < tailleGrille; x += 1) {
			Coord c = Coord{x, y};
			if (g.estVide(c)) {
				if (g.contientTunnel(c)) 
					cout << " O ";
				else 
					cout << "   ";
			} else {
				if (g.contientBrindille(c)) cout << " * ";
				else cout << colonie[g.numeroTermite(c)].toString();
			}
		}
	}
	cout << endl;
}



int main() {
	// Seed aléatoire
	srand(time(0)); 
	// Pour getchar()
	int c;
	Grille g;
	int nbPasse = 10;
	int x1, y1, x2, y2;	

	// Placement des tunnels
	for (int i = 0; i < nbTunnels ; i ++) {
		do {
			x1 = rand() % tailleGrille;
			y1 = rand() % tailleGrille;
			x2 = rand() % tailleGrille;
			y2 = rand() % tailleGrille;
		// Recherche de coordonnées valides afin de pouvoir poser chacun des tunnels aléatoirement
		} while (not g.estVide(Coord{x1, y1}) and not g.estVide(Coord{x2, y2}));  
		g.creeTunnel(Coord{x1, y1}, Coord{x2, y2}, i);
	}
	
	// Placement aléatoire des brindilles
	for (int i = 0; i < tailleGrille; i += 1) {
		for (int j = 0; j < tailleGrille; j += 1) {
			Coord c = Coord{i, j};
			if (g.estVide(c) and (not g.contientTunnel(c)) and float(rand())/float(RAND_MAX) <= densiteBrindille) g.poseBrindille(c);
		}
	}

	
	// Placement des termites
	vector<Termite> colonie = vector<Termite>{};
	for (int i = 0; i < nbTermites ; i ++) {
		do {
			x1 = rand() % tailleGrille;
			y1 = rand() % tailleGrille;
		// Recherche de coordonnées valides afin de pouvoir poser chacun des termites aléatoirement
		} while (not g.estVide(Coord{x1, y1}));   
		colonie.push_back(Termite{i, Coord{x1, y1}});
		g.poseTermite(Coord{x1, y1}, i);
	}

	// Lancement de la simulation
	afficheJeu(g, colonie);
	sleep(3);
	do {
		c = getchar();
			if (c == '*') 
				nbPasse *= 2;
			else if (c == '/' and (nbPasse / 2) > 0) 
				nbPasse /= 2;
			else if (c == '.') break; // Sinonm la boucle for est réitérée
		
		for (int _ = 0 ; _ < nbPasse ; _++) {
			system("clear");
			afficheJeu(g, colonie);
			usleep(180000);
			for (int i = 0; i < nbTermites; i += 1) {
				colonie[i].vieTermite(g);
			}
			assureCoherence(g, colonie);
		}
		cout << "Nombre de passes : " << nbPasse;
	} while (c != '.');
	
	system("clear");
	afficheJeu(g, colonie);
	return 0;
}
