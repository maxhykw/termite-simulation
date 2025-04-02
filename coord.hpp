#ifndef COORD_HPP
#define COORD_HPP

#include <stdexcept>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

// Constante tailleGrille
const int tailleGrille = 20;

// Type énuméré Direction
enum class Direction {Nord, NordEst, Est, SudEst, Sud, SudOuest, Ouest, NordOuest}; 

// Classe Coord
class Coord { 
	
	public : 
	
	// Constructeur
	
		//* Constructeur à partir de numéros de ligne et de colonne 
		//* @param[in] lig : entier
		//* @param[in] col : entier	
		Coord (int lig, int col);

	// Méthodes
	
		//* Récupérer le numéro de ligne d'une coordonnée
		//* @return le numéro de ligne d'une coordonnée
		int getLig() const;

		//* Récupérer le numéro de colonne d'une coordonnée
		//* @return le numéro de colonne d'une coordonnée
		int getCol() const;

	private : 
		
		int ligne_, colonne_;
	
};


// Surcharge des opérateurs pour la classe Coord

//* Opérateur d'affichage sur une coordonnée
ostream &operator<<(ostream &out, const Coord &c);

//* Opérateur d'égalité entre deux coordonnées
bool operator==(const Coord &c1, const Coord &c2);

//* Opérateur d'inégalité entre deux coordonnées
bool operator!=(const Coord &c1, const Coord &c2);


// Surcharge des opérateurs pour ce type

//* Opérateur d'affichage sur une Direction
ostream &operator<<(ostream &out, const Direction &d);


// Fonctions pour ce type

//* Indique la direction à gauche d'une direction donnée 
//* param[out] d : la Direction considérée
//* @return la direction à gauche de d
Direction aGauche(Direction d);

//* Indique la direction à droite d'une direction donnée 
//* param[out] d : la Direction considérée
//* @return la direction à droite de d
Direction aDroite(Direction d);

//* Indique la direction à opposé d'une direction donnée 
//* param[out] d : la Direction considérée
//* @return la direction opposé à d
Direction oppose(Direction d);

//* Indique la coordonnée devant une coordonnée donnée dans une direction donnée
//* param[out] c : la Coordonnée considérée
//* param[out] d : la Direction considérée
//* @return la coordonnée résultante
Coord devantCoord(Coord c, Direction d);


#endif