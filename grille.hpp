#ifndef GRILLE_HPP
#define GRILLE_HPP

#include <iostream>
#include <array>
#include <stdexcept>
#include <sstream>
#include <vector>

using namespace std;

#include "coord.hpp"

// Structure Case
struct Case {
	
	int idT, idTunnel;
	bool brindille;

	// Constructeurs
		
	//* Constructeur par défaut
	Case() : idT{-1}, idTunnel{-1}, brindille{false} {};
	
};


// Type abstrait Grille
class Grille {

	public :

	// Méthodes

		//* Pose une brindille dans la grille à une coordonnée donnée
		//* param[in] c : la coordonnée considérée
		void poseBrindille(Coord c);

		//* Enlève une brindille de la grille à une coordonnée donnée
		//* param[in] c : la coordonnée considérée
		void enleveBrindille(Coord c);

		//* Indique si une brindille se trouve à une coordonnée donnée
		//* dans le tableau.
		//* param[in] c : la coordonnée considérée
		bool contientBrindille(Coord c) const;

		//* Pose un termite de numéro idT dans la grille à une 
		//* coordonnée donnée
		//* param[in] c : la Coordonnée considérée
		//* param[in] idT : un entier
		void poseTermite(Coord c, int idT);

		//* Enlève un termite de la grille à une coordonnée donnée
		//* param[in] c : la coordonnée considérée
		void enleveTermite(Coord c);

		//* Récupére le numéro d'un termite à une coordonnée donnée
		//* param[in] c : la coordonnée considérée
		//* @return le numéro du termite, s'il est présent
		int numeroTermite(Coord c) const;

		//* Teste si une case de coordonnée donnée est vide ou non
		//* param[in] c : la coordonnée considérée
		bool estVide(Coord c) const;
	
	// Méthodes relatives à l'implémentation des tunnels 
	
		//* Teste si une case de coordonnée donnée contient une entrée à un tunnel ou non
		//* param[in] c : la coordonnée considérée
		bool contientTunnel(Coord c) const;
	
		//* Indique le numéro du tunnel de la case de coordonnée donnée
		//* param[in] c : la coordonnée considérée
	    int numeroTunnel(Coord c) const;
	
		//* Crée un tunnel entre deux coordonnées données d'identifiant id
		//* param[in] c1 : Coordonnée
		//* param[in] c2 : Coordonnée
		//* param[in] id : entier
		void creeTunnel(Coord c1, Coord c2, int id);

		//* Enlève un tunnel à partir de la coordonnée d'une de ses entrées
		//* param[in] c : Coordonnée
		void enleveTunnel(Coord c);

		//* Trouve la coordonnée de l'autre bout du tunnel de la coordonnée donnée
		//* param[in] c : Coordonnée
		Coord CoordAutreEntree(Coord c) const;
	
		//* Renvoyer un vecteur de directions pointant les cases libres autour de l'entrée
		//* param[in] g : Grille
		vector<Direction> voisinsLibreTunnel(Coord c) const;
	
	private :

		array<array<Case, tailleGrille>, tailleGrille> g_;

};

// Surcharge des opérateurs pour le type abstrait Grille

//* Surcharge de l'opérateur d'affichage sur une Grille
ostream &operator<<(ostream &out, const Grille &g);



#endif