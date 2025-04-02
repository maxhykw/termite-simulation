#include "doctest.h"
#include "coord.hpp"

// Classe Coord
// Définition du constructeur de la classe Coord

Coord::Coord(int lig, int col) : ligne_{lig}, colonne_{col} {
	if ((ligne_ < 0 or ligne_ >= tailleGrille) or (colonne_ < 0 or colonne_ >= tailleGrille))
		throw invalid_argument("Les coordonnées ne sont pas dans la grille !");
}
TEST_CASE("Constructeur Coord") {
	CHECK(Coord{0, 0} == Coord{0, 0});
	CHECK(Coord{2, 5} == Coord{2, 5});
	CHECK(Coord{tailleGrille-1, tailleGrille-1} == Coord{tailleGrille-1, tailleGrille-1});
	CHECK_THROWS_AS((Coord{-2, 5}), invalid_argument);
	CHECK_THROWS_AS((Coord{2, -5}), invalid_argument);
	CHECK_THROWS_AS((Coord{-2, -5}), invalid_argument);
	CHECK_THROWS_AS((Coord{tailleGrille, 4}), invalid_argument);
	CHECK_THROWS_AS((Coord{4, tailleGrille}), invalid_argument);
}

// Définitions des méthodes de la classe Coord

int Coord::getLig() const { 
	return ligne_; 
}
TEST_CASE("Méthode getLig") {
	CHECK(Coord{0, 0}.getLig() == 0);
	CHECK(Coord{1, 4}.getLig() == 1);
	CHECK(Coord{4, 1}.getLig() == 4);
}

int Coord::getCol() const { 
	return colonne_;
}
TEST_CASE("Méthode getCol") {
	CHECK(Coord{0, 0}.getCol() == 0);
	CHECK(Coord{1, 4}.getCol() == 4);
	CHECK(Coord{4, 1}.getCol() == 1);	
}

// Définition des opérateurs pour la classe Coord

ostream &operator<<(ostream &out, const Coord &c) { 
	out << "(" << c.getLig() << ", " << c.getCol() << ")";
	return out;
}
TEST_CASE("Opérateur d'affichage Coord") {
	ostringstream ch;
	ch << Coord{2, 4};
	CHECK(ch.str() == "(2, 4)");
	
	ch.str("");
	ch << Coord{4, 2};
	CHECK(ch.str() == "(4, 2)");
}

bool operator==(const Coord &c1, const Coord &c2) {
	return (c1.getCol() == c2.getCol()) and (c1.getLig() == c2.getLig());
}
TEST_CASE("Opérateur d'égalité Coord") {
	CHECK(Coord{0, 0} == Coord{0, 0});
	CHECK(Coord{7, 0} == Coord{7, 0});
	CHECK(Coord{0, 7} == Coord{0, 7});
	CHECK_FALSE(Coord{1, 7} == Coord{0, 7});
	CHECK_FALSE(Coord{7, 1} == Coord{7, 0});
	CHECK_FALSE(Coord{7, 8} == Coord{8, 7});
}

bool operator!=(const Coord &c1, const Coord &c2) {
	return not (c1 == c2);
}
TEST_CASE("Opérateur d'inégalité Coord") {
	CHECK_FALSE(Coord{0, 0} != Coord{0, 0});
	CHECK_FALSE(Coord{7, 0} != Coord{7, 0});
	CHECK_FALSE(Coord{0, 7} != Coord{0, 7});
	CHECK(Coord{1, 7} != Coord{0, 7});
	CHECK(Coord{7, 1} != Coord{7, 0});
	CHECK(Coord{7, 8} != Coord{8, 7});
}

// Type énuméré Direction
// Définition des opérateurs pour ce type

ostream &operator<<(ostream &out, const Direction &d) {
	switch (d) {
		case Direction::Nord :      out << "Nord";       break;
		case Direction::NordEst :   out << "Nord-Est";   break;
		case Direction::Est :       out << "Est";        break;
		case Direction::SudEst :    out << "Sud-Est";    break;
		case Direction::Sud :       out << "Sud";        break;
		case Direction::SudOuest :  out << "Sud-Ouest";  break;
		case Direction::Ouest :     out << "Ouest";      break;
		case Direction::NordOuest : out << "Nord-Ouest"; break;
		default : throw invalid_argument("La direction n'est pas valide !");
	}
	return out;
}
TEST_CASE("Opérateur d'affichage Direction") {
	ostringstream ch;
	Direction d1 = Direction::NordOuest;
	ch << d1;
	CHECK(ch.str() == "Nord-Ouest");

	ch.str("");
	Direction d2 = Direction::Sud;
	ch << d2;
	CHECK(ch.str() == "Sud");
}

// Définition des fonctions pour ce type

Direction aGauche(Direction d) {
	switch (d) {
		case Direction::NordEst :   return Direction::Nord;
		case Direction::Est :       return Direction::NordEst;
		case Direction::SudEst :    return Direction::Est;
		case Direction::Sud :       return Direction::SudEst;
		case Direction::SudOuest :  return Direction::Sud;
		case Direction::Ouest :     return Direction::SudOuest;
		case Direction::NordOuest : return Direction::Ouest;
		case Direction::Nord :      return Direction::NordOuest;
	    default : throw invalid_argument("La direction n'est pas valide !");
	}
}
Direction aDroite(Direction d) {
	switch (d) {
		case Direction::NordOuest : return Direction::Nord;
		case Direction::Nord :      return Direction::NordEst;
		case Direction::NordEst :   return Direction::Est;
		case Direction::Est :       return Direction::SudEst;
		case Direction::SudEst :    return Direction::Sud;
		case Direction::Sud :       return Direction::SudOuest;
		case Direction::SudOuest :  return Direction::Ouest;
		case Direction::Ouest :     return Direction::NordOuest;
		default : throw invalid_argument("La direction n'est pas valide !");
	}
}
TEST_CASE("Fonction aGauche & aDroite") {
	Direction d1 = Direction::Nord;
	Direction d2 = Direction::Est;
	Direction d3 = Direction::Sud;
	Direction d4 = Direction::Ouest;
	Direction d5 = Direction::SudOuest;
	SUBCASE("aGauche") {
		CHECK(aGauche(d1) == Direction::NordOuest);
		CHECK(aGauche(d2) == Direction::NordEst);
		CHECK(aGauche(d3) == Direction::SudEst);
		CHECK(aGauche(d4) == Direction::SudOuest);
		CHECK(aGauche(d5) == Direction::Sud);
	}
	SUBCASE("aDroite") {
		CHECK(aGauche(d1) == Direction::NordOuest);
		CHECK(aGauche(d2) == Direction::NordEst);
		CHECK(aGauche(d3) == Direction::SudEst);
		CHECK(aGauche(d4) == Direction::SudOuest);
		CHECK(aGauche(d5) == Direction::Sud);
	}
	CHECK(aGauche(aDroite(d1)) == d1);
	CHECK(aGauche(aDroite(d3)) == d3);
	CHECK(aDroite(aGauche(d1)) == d1);
	CHECK(aDroite(aGauche(d3)) == d3);

	CHECK(aDroite(aDroite(aDroite(aDroite(aDroite(aDroite(aDroite(aDroite(d1)))))))) == d1);
	CHECK(aGauche(aGauche(aGauche(aGauche(aGauche(aGauche(aGauche(aGauche(d1)))))))) == d1);
}

Direction oppose(Direction d) {
	return aGauche(aGauche(aGauche(aGauche(d))));
}
TEST_CASE("Fonction oppose") {
	Direction d1 = Direction::Nord;
	Direction d2 = Direction::SudEst;
	CHECK(oppose(d1) == Direction::Sud);
	CHECK(oppose(d2) == Direction::NordOuest);
}

Coord devantCoord(Coord c, Direction d) {
	int x, y;
	x = 0 ; y = 0;
	switch (d) {
		case Direction::Nord :              y = 1;  break;
		case Direction::NordEst :   x = 1;  y = 1;  break;
		case Direction::Est :       x = 1;          break;
		case Direction::SudEst :    x = 1;  y = -1; break;
		case Direction::Sud :               y = -1; break;
		case Direction::SudOuest :  x = -1; y = -1; break;
		case Direction::Ouest :     x = -1;         break;
		case Direction::NordOuest : x = -1; y = 1;  break;
	    default : throw invalid_argument("La direction n'est pas valide !");
	}
	return Coord{c.getLig() + x, c.getCol() + y};
}
TEST_CASE("Fonction devantCoord") {
	// W! Ces tests peuvent ne pas fonctionner selon la grille
	CHECK(devantCoord(Coord{3, 2}, Direction::Nord)  == Coord{3, 3});
	CHECK(devantCoord(Coord{3, 2}, Direction::Ouest) == Coord{2, 2});
	CHECK(devantCoord(Coord{3, 2}, Direction::Sud)   == Coord{3, 1});
	CHECK(devantCoord(Coord{3, 2}, Direction::Est)   == Coord{4, 2});
	CHECK(devantCoord(Coord{3, 2}, Direction::NordOuest) == Coord{2, 3});
	CHECK(devantCoord(Coord{3, 2}, Direction::NordEst) == Coord{4, 3});
	CHECK(devantCoord(Coord{3, 2}, Direction::SudOuest) == Coord{2, 1});
	CHECK(devantCoord(Coord{3, 2}, Direction::SudEst) == Coord{4, 1});

	// Si l'on avance, puis tourne 4 fois à droite (ou à gauche), puis avance encore, on revient à la coordonnée de départ
	Coord c_init = Coord{tailleGrille/2, tailleGrille/2};
	Direction d;
	Direction direc4FoisDroite;
	Direction direc4FoisGauche;
	for (int i = 0; i < 8; i += 1) {
		d = Direction(i);
		Coord avanceDirec = devantCoord(c_init, d);
		direc4FoisDroite = aDroite(aDroite(aDroite(aDroite(d)))); 
		direc4FoisGauche = aGauche(aGauche(aGauche(aGauche(d))));
		CHECK(devantCoord(avanceDirec, direc4FoisDroite) == c_init);
		CHECK(devantCoord(avanceDirec, direc4FoisGauche) == c_init);
	}

	// Tests des quatres coins de la grille
	CHECK_THROWS_AS(devantCoord(Coord{0, 0}, Direction::Sud), invalid_argument);
	CHECK_THROWS_AS(devantCoord(Coord{0, 0}, Direction::Ouest), invalid_argument);
	CHECK_THROWS_AS(devantCoord(Coord{0, tailleGrille - 1}, Direction::Nord), invalid_argument);
	CHECK_THROWS_AS(devantCoord(Coord{tailleGrille - 1, 0}, Direction::Est), invalid_argument);
	CHECK_THROWS_AS(devantCoord(Coord{tailleGrille - 1, tailleGrille - 1}, Direction::NordEst), invalid_argument);
}