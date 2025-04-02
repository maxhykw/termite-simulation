#include "doctest.h"
#include "grille.hpp"

// Type abstrait Grille

// Définitions des méthodes pour ce type

void Grille::poseBrindille(Coord c) {
	if (not estVide(c) or contientTunnel(c)) throw runtime_error("Ne peux pas placer de brindille car la case est déjà occupée !");
	g_[c.getLig()][c.getCol()].brindille = true;
}
TEST_CASE("Méthode poseBrindille") {
	Grille g;
	Coord c1 = Coord{0, 0};
	Coord c2 = Coord{3, 5};
	Coord c3 = Coord{6, 2};
	Coord c4 = Coord{2, 6};
	g.poseBrindille(c1);
	g.poseBrindille(c2);
	g.poseBrindille(c3);
	g.poseTermite(c4, 0);
	Coord c5 {5, 5};
	Coord c6 {7, 7};
	g.creeTunnel(c5, c6, 0);
	for (int i = 0; i < tailleGrille; i ++) {
		for (int j = 0; j < tailleGrille; j ++) {
			Coord c = Coord{i, j};
			if (c != c1
			 && c != c2
			 && c != c3
			 && c != c4) CHECK_FALSE(g.contientBrindille(c));
			else {
				if (c == c4) CHECK_FALSE(g.contientBrindille(c));
				else CHECK(g.contientBrindille(c));
			}
		}
	}
	CHECK_THROWS_AS(g.poseBrindille(c1), runtime_error);
	CHECK_THROWS_AS(g.poseBrindille(c2), runtime_error);
	CHECK_THROWS_AS(g.poseBrindille(c3), runtime_error);
	CHECK_THROWS_AS(g.poseBrindille(c4), runtime_error);
	CHECK_THROWS_AS(g.poseBrindille(c5), runtime_error); // Ne peut pas poser de brindille a l'entrée d'un tunnel
	CHECK_THROWS_AS(g.poseBrindille(c6), runtime_error);
}

void Grille::enleveBrindille(Coord c) {
	if (not contientBrindille(c)) throw runtime_error("Il n'y a pas de brindille dans cette case !");
	g_[c.getLig()][c.getCol()].brindille = false;
}
TEST_CASE("Méthode enleveBrindille") {
	Grille g;
	Coord c1 = Coord{0, 0};
	Coord c2 = Coord{3, 5};
	Coord c3 = Coord{6, 2};
	Coord c4 = Coord{2, 6};
	g.poseBrindille(c1);
	g.poseBrindille(c2);
	g.poseBrindille(c3);
	g.poseTermite(c4, 0);

	g.enleveBrindille(c1);
	g.enleveBrindille(c2);
	for (int i = 0; i < tailleGrille; i++) {
		for (int j = 0; j < tailleGrille; j++) {
			Coord c = Coord{i, j};
			if (c != c3) CHECK_FALSE(g.contientBrindille(c));
			else CHECK(g.contientBrindille(c));
		}
	}
	CHECK_THROWS_AS(g.enleveBrindille(c1), runtime_error);
	CHECK_THROWS_AS(g.enleveBrindille(c2), runtime_error);
	CHECK_THROWS_AS(g.enleveBrindille(c4), runtime_error);
}

bool Grille::contientBrindille(Coord c) const {
	return g_[c.getLig()][c.getCol()].brindille;
}
TEST_CASE("Méthode contientBrindille") {
	Grille g = Grille();
	Coord c1 = Coord{0, 0};
	Coord c2 = Coord{2, 4};
	Coord c3 = Coord{3, 4};
	g.poseBrindille(c1);
	g.poseBrindille(c2);
	g.poseBrindille(c3);
	for (int i = 0; i < tailleGrille ; i++) {
		for (int j = 0; j < tailleGrille; j++) {
			Coord c = Coord{i, j};
			if (c != c1
			&& c != c2
			&& c != c3) CHECK_FALSE(g.contientBrindille(c));
			else CHECK(g.contientBrindille(c));
		}
	}   
}

void Grille::poseTermite(Coord c, int idT) {
	if (not estVide(c)) 
		throw runtime_error("Ne peut pas placer de termite car la case est déjà occupée !");
	if (contientTunnel(c) and voisinsLibreTunnel(c).size() == 0)
		throw runtime_error("Ne peut pas placer de termite car la case contient une entrée de tunnel entourée !");
	g_[c.getLig()][c.getCol()].idT = idT;
}
TEST_CASE("Méthode poseTermite") {
	Grille g;
	Coord c1 = Coord{1, 0};
	Coord c2 = Coord{3, 5};
	Coord c3 = Coord{6, 2};
	Coord c4 = Coord{2, 4};
	g.poseTermite(c1, 0);
	g.poseTermite(c2, 1);
	g.poseTermite(c3, 2);
	g.poseBrindille(c4);
	Coord c5 = Coord{0, 1};
	Coord c6 = Coord{1, 1};
	g.poseTermite(c5, 3);
	g.poseTermite(c6, 4);
	g.creeTunnel(Coord{0, 0}, Coord{5, 5}, 0); 
	for (int i = 0; i < tailleGrille; i ++) {
		for (int j = 0; j < tailleGrille; j ++) {
			Coord c = Coord{i, j};
			if (c != c1
			 && c != c2
			 && c != c3			 
			 && c != c4
			 && c != c5
			 && c != c6) CHECK(g.estVide(c));
			else {
				if (c == c4) CHECK(g.contientBrindille(c));
				else CHECK(g.numeroTermite(c) != -1);
			}
		}
	}
	CHECK_THROWS_AS(g.poseTermite(c1, 3), runtime_error);
	CHECK_THROWS_AS(g.poseTermite(c2, 4), runtime_error);
	CHECK_THROWS_AS(g.poseTermite(c3, 5), runtime_error);
	CHECK_THROWS_AS(g.poseTermite(c4, 6), runtime_error);
	CHECK_THROWS_AS(g.poseTermite(Coord{0, 0}, 7), runtime_error); // L'entrée (0, 0) est entourée 
}

void Grille::enleveTermite(Coord c) {
	if (estVide(c) or contientBrindille(c)) throw runtime_error("Ne peut pas enlever de termite sur cette case car elle ne contient pas de termite !");
	g_[c.getLig()][c.getCol()].idT = -1;
}
TEST_CASE("Méthode enleveTermite") {
	Grille g;
	Coord c1 = Coord{0, 0};
	Coord c2 = Coord{3, 5};
	Coord c3 = Coord{6, 2};
	Coord c4 = Coord{2, 4};
	g.poseTermite(c1, 0);
	g.poseTermite(c2, 1);
	g.poseTermite(c3, 2);
	g.poseBrindille(c4);

	g.enleveTermite(c1);
	g.enleveTermite(c2);
	for (int i = 0; i < tailleGrille; i++) {
		for (int j = 0; j < tailleGrille; j++) {
			Coord c = Coord{i, j};
			if (c != c3 and c != c4) CHECK(g.estVide(c));
		}
	}
	CHECK(g.numeroTermite(c3) == 2);
	CHECK(g.contientBrindille(c4));
	CHECK_THROWS_AS(g.enleveTermite(c1), runtime_error);
	CHECK_THROWS_AS(g.enleveTermite(c2), runtime_error);
	CHECK_THROWS_AS(g.enleveTermite(c4), runtime_error);
}

int Grille::numeroTermite(Coord c) const {
	return g_[c.getLig()][c.getCol()].idT;
}
TEST_CASE("Méthode numeroTermite") {
	Grille g;
	Coord c1 = Coord{0, 0};
	Coord c2 = Coord{2, 9};
	Coord c3 = Coord{7, 3};
	Coord c4 = Coord{4, 4};
	g.poseTermite(c1, 0);
	g.poseTermite(c2, 13);
	g.poseTermite(c3, 6);
	g.poseBrindille(Coord{4, 4});
	CHECK(g.numeroTermite(c1) == 0);
	CHECK(g.numeroTermite(c2) == 13);
	CHECK(g.numeroTermite(c3) == 6);
	CHECK(g.numeroTermite(c4) == -1);
}

bool Grille::estVide(Coord c) const {
	return not (contientBrindille(c)) and numeroTermite(c) == -1;
}
TEST_CASE("Méthode estVide") {
	Grille g;
	Coord c1 = Coord{2, 5};
	Coord c2 = Coord{6, 7};
	for (int i = 0; i < tailleGrille; i++) {
		for (int j = 0; j < tailleGrille; j++) {
			CHECK(g.estVide(Coord{i, j}));
		}
	}
	g.poseBrindille(c1);
	g.poseTermite(c2, 4);
	CHECK_FALSE(g.estVide(c1));
	CHECK_FALSE(g.estVide(c2));
}

ostream &operator<<(ostream &out, const Grille &g) {
	for (int i = 0 ; i < tailleGrille ; i++) {
		for (int j = 0 ; j < tailleGrille ; j++) {
			out << " | ";
			if (g.estVide(Coord{i, j}))                out << " ";
			else if (g.contientBrindille(Coord{i, j})) out << "B";
			else                                       out << "T";
		}
		out << " |" << endl;
	}
	return out;
}

bool Grille::contientTunnel(Coord c) const {
	return g_[c.getLig()][c.getCol()].idTunnel != -1;
}
TEST_CASE("Méthode contientTunnel") {
	Grille g;
	Coord c1 = Coord{0, 0};
	Coord c2 = Coord{2, 9};
	Coord c3 = Coord{7, 3};
	Coord c4 = Coord{4, 4};
	g.creeTunnel(c1, c2, 0);
	g.creeTunnel(c3, c4, 1);
	for (int i = 0; i < tailleGrille ; i++) {
		for (int j = 0; j < tailleGrille; j++) {
			Coord c = Coord{i, j};
			if (c != c1
			&& c != c2
			&& c != c3
			&& c != c4) CHECK_FALSE(g.contientTunnel(c));
			else CHECK(g.contientTunnel(c));
		}
	}   
}

int Grille::numeroTunnel(Coord c) const {
	return g_[c.getLig()][c.getCol()].idTunnel;
}
TEST_CASE("Méthode numeroTunnel") {
	Grille g;
	Coord c1 = Coord{0, 0};
	Coord c2 = Coord{2, 9};
	Coord c3 = Coord{7, 3};
	Coord c4 = Coord{4, 4};
	g.creeTunnel(c1, c2, 0);
	g.creeTunnel(c3, c4, 1);
	CHECK(g.numeroTunnel(c1) == 0);
	CHECK(g.numeroTunnel(c2) == 0);
	CHECK(g.numeroTunnel(c3) == 1);
	CHECK(g.numeroTunnel(c4) == 1);
	Coord c5 {8, 9};
	Coord c6 {3, 5};
	CHECK(g.numeroTunnel(c5) == -1);
	CHECK(g.numeroTunnel(c6) == -1);
}

void Grille::creeTunnel(Coord c1, Coord c2, int id) {
	if (not estVide(c1) or not estVide(c2))
		throw invalid_argument("Une voire les deux cases ne sont pas disponibles !");
	if (c1 == c2)
		throw invalid_argument("Les coordonnées ne peuvent pas être les mêmes !");
	if (contientTunnel(c1) or contientTunnel(c2))
		throw invalid_argument("Une des deux cases est déjà l'entrée d'un autre tunnel !");
	if (id == -1)
		throw invalid_argument("Insérer un identifiant correcte !"); 
	for (int i = 0 ; i < tailleGrille ; i++) {
		for (int j = 0 ; j < tailleGrille ; j++) {
			if (numeroTunnel(Coord{i, j}) == id)
				throw invalid_argument("L'identifiant est déjà utilisé !");
		}
	}
	g_[c1.getLig()][c1.getCol()].idTunnel = id;
	g_[c2.getLig()][c2.getCol()].idTunnel = id;
}
TEST_CASE("Méthode creeTunnel") {
	Grille g;
	Coord c1 = Coord{0, 0};
	Coord c2 = Coord{3, 5};
	Coord c3 = Coord{6, 2};
	Coord c4 = Coord{2, 4};
	g.creeTunnel(c1, c2, 0);
	g.creeTunnel(c3, c4, 1);
	for (int i = 0; i < tailleGrille; i ++) {
		for (int j = 0; j < tailleGrille; j ++) {
			Coord c = Coord{i, j};
			if (c != c1
			 && c != c2
			 && c != c3
			 && c != c4) CHECK(g.estVide(c));
			else 
				CHECK(g.numeroTunnel(c) != -1);
		}
	}
	CHECK(g.numeroTunnel(c1) == 0);
	CHECK(g.numeroTunnel(c2) == 0);
	CHECK(g.numeroTunnel(c3) == 1);
	CHECK(g.numeroTunnel(c4) == 1);

	Coord c5 = Coord{9, 5};
	Coord c6 = Coord{3, 8};
	g.poseTermite(c5, 0);
	CHECK_THROWS_AS(g.creeTunnel(c5, c6, 2), invalid_argument); // Cas d'une ou deux cases occupées 
	CHECK_THROWS_AS(g.creeTunnel(c5, c5, 2), invalid_argument); // Cas de coordonnées identiques 
	CHECK_THROWS_AS(g.creeTunnel(c2, c5, 2), invalid_argument); // Cas d'une case qui est déjà l'entrée d'un autre tunnel 
	CHECK_THROWS_AS(g.creeTunnel(c2, c5, 0), invalid_argument); // Cas d'un identifiant déjà usé 
	CHECK_THROWS_AS(g.creeTunnel(Coord{10, 10}, Coord{10, 10}, -1), invalid_argument); // Identifiant "-1"
}

void Grille::enleveTunnel(Coord c) {
	if (not contientTunnel(c))
		throw invalid_argument("La case ne contient pas d'entrée à un tunnel !");
	g_[CoordAutreEntree(c).getLig()][CoordAutreEntree(c).getCol()].idTunnel = -1;
	g_[c.getLig()][c.getCol()].idTunnel = -1;
	
}
TEST_CASE("Méthode enleveTunnel") {
	Grille g;
	Coord c1 {0, 0};
	Coord c2 {3, 5};
	Coord c3 {6, 2};
	Coord c4 {2, 4};
	g.creeTunnel(c1, c2, 0);
	g.creeTunnel(c3, c4, 1);
	for (int i = 0; i < tailleGrille; i++) {
		for (int j = 0; j < tailleGrille; j++) {
			Coord c = Coord{i, j};
			if (c != c1
			 && c != c2
			 && c != c3
			 && c != c4) CHECK(g.estVide(c));
			else
				CHECK(g.contientTunnel(c));
		}
	}	
	CHECK(g.numeroTunnel(c3) == 1);
	CHECK(g.numeroTunnel(c4) == 1);

	g.enleveTunnel(c3);

	CHECK(g.numeroTunnel(c3) == -1);
	CHECK(g.numeroTunnel(c4) == -1);
	CHECK_THROWS_AS(g.enleveTunnel(c3), invalid_argument);
	CHECK_THROWS_AS(g.enleveTunnel(c4), invalid_argument);
}

Coord Grille::CoordAutreEntree(Coord c) const {
	if (numeroTunnel(c) == -1)
		throw invalid_argument("La case n'a pas de tunnel"); 
	for (int i = 0 ; i < tailleGrille ; i++) {
		for (int j = 0 ; j < tailleGrille ; j++) {
			if (numeroTunnel(c) == numeroTunnel(Coord{i, j}) and c != Coord{i, j}) 
				return Coord{i, j};
		}
	}
	throw invalid_argument("Coordonnée invalide"); // Normalement on n'atteindra jamais ici
}
TEST_CASE("Méthode CoordAutreEntree") {
	Grille g;
	Coord c1 {0, 0};
	Coord c2 {3, 5};
	Coord c3 {6, 2};
	Coord c4 {2, 4};
	Coord c5 {9, 9};
	g.creeTunnel(c1, c2, 0);
	g.creeTunnel(c3, c4, 1);
	CHECK(g.CoordAutreEntree(c1) == c2);
	CHECK(g.CoordAutreEntree(c2) == c1);	
	CHECK(g.CoordAutreEntree(c3) == c4);
	CHECK(g.CoordAutreEntree(c4) == c3);
	CHECK_THROWS_AS(g.CoordAutreEntree(c5), invalid_argument);
}

vector<Direction> Grille::voisinsLibreTunnel(Coord c) const {
	vector<Direction> res = vector<Direction>{};
	Direction d = Direction::Nord;
	for (int _ = 0 ; _ < 8 ; _++) {
		try {
			if (estVide(devantCoord(c, d))) res.push_back(d);
		} catch (invalid_argument &e) {}
		d = aDroite(d);
	}
	return res;
}
TEST_CASE("Méthode voisinsLibreTunnel") {
	Grille g;
	Coord c1 {0, 0};
	Coord c2 {5, 5};
	g.creeTunnel(c1, c2, 0);
	g.poseBrindille(Coord{1, 0}); // On entoure l'entrée de coordonnée c1
	g.poseBrindille(Coord{0, 1});	
	g.poseBrindille(Coord{1, 1});
	
	CHECK(g.voisinsLibreTunnel(c2).size() == 8);
	
	CHECK(g.voisinsLibreTunnel(c1).size() == 0);
	g.enleveBrindille(Coord{1, 0});
	CHECK(g.voisinsLibreTunnel(c1).size() == 1);
	
	CHECK(g.voisinsLibreTunnel(c1)[0] == Direction::Est);
}