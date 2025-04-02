#ifndef TERMITE_HPP
#define TERMITE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <random>

#include "coord.hpp"
#include "grille.hpp"

using namespace std;

// Paramètres constant pour les termites

const float probaTourner = 0.1;
const int dureeSablier = 6;

// Classe Termite

class Termite {

	public : 

	// Constructeurs

		//* Constructeur à partir d'un identifiant et de coordonnées
		//* @param[in] idT : entier
		//* @param[in] c   : Coordonnées
		Termite(int idT, Coord c);

	// Méthodes concernant le termite lui-même

		//* Convertir l'animal en chaîne de caractères (pour l'affichage)
		string toString() const;

		//* Renvoie l'identifiant d'un termite
		int idTermite() const;
	
		//* Renvoyer la direction du Termite.
		Direction directionTermite() const;

		//* Renvoyer les coordonnées du termite
		Coord coordonnee() const;

		//* Renvoyer les coordonnées de la case devant le termite
		Coord devant() const;

		//* Indiquer si le termite porte une brindille ou non
		bool porteBrindille() const;
	
		//* Faire tourner le termite à droite
		void tourneADroite();

		//* Faire tourner le termite à gauche
		void tourneAGauche();

		//* Faire tourner le termite dans un sens aléatoire
		void tourneAleat();

	// Méthodes concernant également la grille

		//* Indiquer si la case devant le termite est libre, ou non
		//* param[in] g : Grille
		bool laVoieEstLibre(const Grille &g) const;

		//* Indiquer si la case devant le termite contient une brindille, ou non
		//* param[in] g : Grille
		bool brindilleEnFace(const Grille &g) const;

		//* Renvoyer un vecteur de directions pointant les cases libres autour du termite
		//* param[in] g : Grille
		vector<Direction> voisinsLibre(const Grille &g) const;

		//* Faire avancer le termite d'une case
		//* param[out] g : Grille
		void avance(Grille &g);

		//* Faire prendre le termite une brindille qui est devant
		//* param[out] g : Grille
		void chargeBrindille(Grille &g);		
	
		//* Faire poser le termite sa brindille, devant lui
		//* param[out] g : Grille
		void dechargeBrindille(Grille &g);

		//* Déplacer aléatoirement le termite
		//* param[in/out] g : Grille
		void marcheAleatoire(Grille &g);

		//* Algorithme intégral du termite
		//* param[in/out] g : Grille
		void vieTermite(Grille &g);

	// ... et les tunnels
	
		//* Fait utiliser au termite le tunnel (le plasse a l'autre bout et le fait avancer);
		//* param[in/out] g : Grille
		void passeTunnel(Grille &g);
	
		//* Indiquer si la case devant le termite contient une entrée de tunnel, ou non
		//* param[in] g : Grille
		bool tunnelEnFace(const Grille &g) const;
	
	private : 

		int idT_;
		Coord c_;
		Direction d_;
		bool brindille_;
		int sablier_;
};


#endif
