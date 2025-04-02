#include "doctest.h"
#include "termite.hpp"

// Constructeurs de la classe Termite

Termite::Termite(int idT, Coord c) : idT_{idT}, c_{c}, d_{Direction::Nord}, brindille_{false}, sablier_{dureeSablier} {}
TEST_CASE("Constructeur Termite") {
	vector<Termite> colonie = vector<Termite>{};
	Termite t0 = Termite{0, Coord{0, 0}};
	Termite t1 = Termite{1, Coord{0, 1}};
	colonie.push_back(t0);
	colonie.push_back(t1);
	CHECK(colonie.size() == 2);
}

// Méthodes concernant le termite lui-même

string Termite::toString() const {
	string s;
	switch (d_) {
		case Direction::Nord :
		case Direction::Sud :       s = " | "; break;
			
		case Direction::NordEst:    
		case Direction::SudOuest :  s = " / "; break;
			
		case Direction::Est :
		case Direction::Ouest :     s = " - "; break;

		case Direction::SudEst :
		case Direction::NordOuest : s = " \\ "; break;
		default : break;
	}
	return s;
}
TEST_CASE("Méthode toString") {
	Termite t = Termite{0, Coord{0, 0}};
	CHECK(t.toString() == " | ");
	t.tourneADroite();
	CHECK(t.toString() == " / ");
	t.tourneADroite();
	CHECK(t.toString() == " - ");
	t.tourneADroite();
	CHECK(t.toString() == " \\ ");
}

int Termite::idTermite() const{
	return idT_;
}
TEST_CASE("Méthode idTermite") {
	Termite t0 = Termite{0, Coord{0, 0}};
	Termite t1 = Termite{1, Coord{0, 1}};
	CHECK(t0.idTermite() == 0);
	CHECK(t1.idTermite() == 1);
}

Direction Termite::directionTermite() const {
	return d_;
}
TEST_CASE("Méthode directionTermite") {
	Termite t2 = Termite{0, Coord{0, 0}};
	Termite t1 = Termite{1, Coord{2, 5}};
	CHECK(t1.directionTermite() == Direction::Nord);
	CHECK(t2.directionTermite() == Direction::Nord);
}

Coord Termite::coordonnee() const {
	return c_;
}
TEST_CASE("Méthode coordonnee") {
	Termite t1 = Termite{0, Coord{0, 0}};
	Termite t2 = Termite{1, Coord{7, 5}};
	CHECK(t1.coordonnee() == Coord{0, 0});
	CHECK(t2.coordonnee() == Coord{7, 5});
}

Coord Termite::devant() const {
	return devantCoord(c_, d_);
}
TEST_CASE("Méthode devant") {
	Termite t1 = Termite{0, Coord{0, 0}};
	Termite t2 = Termite{1, Coord{7, 5}};
	CHECK(t1.devant() == Coord{0, 1});
	CHECK(t2.devant() == Coord{7, 6});
}

bool Termite::porteBrindille() const {
	return brindille_;
}
TEST_CASE("Méthode porteBrindille") {
	Grille g;
	Termite t1 = Termite{0, Coord{0, 0}};
	Termite t2 = Termite{4, Coord{4, 2}};
	Termite t3 = Termite{2, Coord{3, 5}};
	g.poseBrindille(t3.devant());
	t3.chargeBrindille(g);
	CHECK_FALSE(t1.porteBrindille());
	CHECK_FALSE(t2.porteBrindille());
	CHECK(t3.porteBrindille());
}

void Termite::tourneADroite() {
	d_ = aDroite(d_);
}
TEST_CASE("Méthode tourneADroite") {
	Termite t = Termite{0, Coord{0, 0}};
	t.tourneADroite();
	CHECK(t.directionTermite() == Direction::NordEst);	
	t.tourneADroite();
	CHECK(t.directionTermite() == Direction::Est);
}

void Termite::tourneAGauche() {
	d_ = aGauche(d_);
}
TEST_CASE("Méthode tourneAGauche") {
	Termite t = Termite{0, Coord{0, 0}};
	t.tourneAGauche();
	CHECK(t.directionTermite() == Direction::NordOuest);	
	t.tourneAGauche();
	CHECK(t.directionTermite() == Direction::Ouest);
}

void Termite::tourneAleat() {
	int prob = rand() % 2;
	if (prob == 0) d_ = aGauche(d_);
	else d_ = aDroite(d_);
}
TEST_CASE("Méthode tourneAleat") {
	Termite t1 = Termite{0, Coord{0, 0}};
	Termite t2 = Termite{4, Coord{2, 8}};
	t1.tourneAleat();
	t2.tourneAleat();
	CHECK_FALSE(t1.directionTermite() == Direction::Nord);
	CHECK_FALSE(t2.directionTermite() == Direction::Nord);
}


// Méthode concernant également la grille

bool Termite::laVoieEstLibre(const Grille &g) const {
	try {
		devant();
	} catch (invalid_argument &e) { return false; }
	return g.estVide(devant());
}
TEST_CASE("Méthode laVoieEstLibre") {
	Grille g;
	int id = 0;
	Termite t0 = Termite{0, Coord{tailleGrille/2, tailleGrille/2}};
	Termite t1 = Termite{1, t0.devant()};
	Termite t2 = Termite{2, Coord{0, 0}};
	t2.tourneAGauche();
	vector<Termite> colonie = vector<Termite>{t0, t1, t2};    // Vecteur contenant les termites qui existent
	for (Termite t : colonie) {
		g.poseTermite(t.coordonnee(), id);  // On pose chaque termite sur sa case
		id++;
	}
	CHECK_FALSE(t0.laVoieEstLibre(g));
	CHECK(t1.laVoieEstLibre(g));
	CHECK_FALSE(t2.laVoieEstLibre(g));
}

bool Termite::brindilleEnFace(const Grille &g) const {
	try { 
		devant(); 
	} catch (invalid_argument &e) { return false; }
	return g.contientBrindille(devant());
}
TEST_CASE("Méthode brindilleEnFace") {
	Grille g;
	int id = 0;
	Termite t = Termite{0, Coord{0, 0}};
	vector<Termite> colonie = vector<Termite>{t};
	for (Termite t : colonie) {
		g.poseTermite(t.coordonnee(), id); 
		id++;
	}
	t.tourneAGauche();
	CHECK_FALSE(t.brindilleEnFace(g)); // Termite regarde le mur
	t.tourneADroite();
	g.poseBrindille(t.devant());
	CHECK(t.brindilleEnFace(g));
	t.tourneADroite();
	CHECK_FALSE(t.brindilleEnFace(g)); // Termite regarde une case vide
}

vector<Direction> Termite::voisinsLibre(const Grille &g) const {
	vector<Direction> res = vector<Direction>{};
	Direction d = d_;
	for (int _ = 0 ; _ < 8 ; _++) {
		try {
			if (g.estVide(devantCoord(c_, d))) res.push_back(d);
		} catch (invalid_argument &e) {}
		d = aDroite(d);
	}
	return res;
}
TEST_CASE("Méthode voisinsLibre") {
	Grille g;
	int id = 0;
	Termite t = Termite{0, Coord{0, 0}};
	vector<Termite> colonie = vector<Termite>{t};
	for (Termite t : colonie) {
		g.poseTermite(t.coordonnee(), id); 
		id++;
	}
	g.poseBrindille(Coord{0, 1});
	CHECK(t.voisinsLibre(g).size() == 2);
	CHECK(t.voisinsLibre(g)[0] == Direction::NordEst);
	CHECK(t.voisinsLibre(g)[1] == Direction::Est);
}

void Termite::avance(Grille &g) {
	if (laVoieEstLibre(g)) {
		g.enleveTermite(c_);
		g.poseTermite(devant(), idT_);
		c_ = devant();
	} else
		throw runtime_error("La case devant le termite n'est pas disponible donc il n'a pas pu avancer !");
}
TEST_CASE("Méthode avance") {
	Grille g;
	int id = 0;
	Termite t = Termite{0, Coord{0, 0}};
	vector<Termite> colonie = vector<Termite>{t};
	for (Termite t : colonie) {
		g.poseTermite(t.coordonnee(), id); 
		id++;
	}
	t.tourneAGauche();
	CHECK_THROWS_AS(t.avance(g), runtime_error);
	t.tourneADroite();
	t.avance(g);
	CHECK(t.coordonnee() == Coord{0, 1});
	CHECK(g.numeroTermite(t.coordonnee()) == 0);
	CHECK_FALSE(g.numeroTermite(Coord{0, 0}) == 0);
	g.poseBrindille(t.devant());
	CHECK_THROWS_AS(t.avance(g), runtime_error);
}

void Termite::chargeBrindille(Grille &g) {
	if (brindille_)
		throw runtime_error("Le termite porte déjà une brindille !");
	else if (not brindilleEnFace(g))
		throw runtime_error("La case devant ne contient pas de brindille !");
	else {
		brindille_ = true;
		g.enleveBrindille(devant());
	}
}
TEST_CASE("Méthode chargeBrindille") {
	Grille g;
	int id = 0;
	Termite t = Termite{0, Coord{0, 0}};
	vector<Termite> colonie = vector<Termite>{t};
	for (Termite t : colonie) {
		g.poseTermite(t.coordonnee(), id); 
		id++;
	}
	CHECK_THROWS_AS(t.chargeBrindille(g), runtime_error); // Pas de brindille devant
	g.poseBrindille(t.devant());
	t.chargeBrindille(g);
	CHECK_FALSE(t.brindilleEnFace(g)); 
	CHECK(t.porteBrindille());
	g.poseBrindille(t.devant());
	CHECK(t.brindilleEnFace(g));
	CHECK_THROWS_AS(t.chargeBrindille(g), runtime_error); // Porte déjà un brindille
}

void Termite::dechargeBrindille(Grille &g) {
	if (not brindille_)
		throw runtime_error("Le termite ne porte pas de brindille !");
	else if (not g.estVide(devant()))
		throw runtime_error("Ne peut pas poser de brindille car la case devant n'est pas vide !");
	else if (g.contientTunnel(devant()))
		throw runtime_error("Ne peut pas poser de brindille car la case devant contient une entrée de tunnel !");
	else {
		brindille_ = false;
		g.poseBrindille(devant());
	}
}
TEST_CASE("Méthode dechargeBrindille") {
	Grille g;
	int id = 0;
	Termite t = Termite{0, Coord{0, 0}};
	Termite t2 = Termite{1, Coord{3, 6}};
	vector<Termite> colonie = vector<Termite>{t, t2};
	for (Termite t : colonie) {
		g.poseTermite(t.coordonnee(), id); 
		id++;
	}
	CHECK_THROWS_AS(t.dechargeBrindille(g), runtime_error); // Termite ne porte pas de brindille
	g.poseBrindille(t.devant()); 
	t.chargeBrindille(g);
	g.poseBrindille(t.devant()); 
	CHECK_THROWS_AS(t.dechargeBrindille(g), runtime_error); // Brindille devant, ne peut rien poser
	t.tourneADroite();
	t.dechargeBrindille(g);
	CHECK(t.brindilleEnFace(g)); 

	g.poseBrindille(t2.devant());
	t2.chargeBrindille(g);
	Coord c1 {2, 2};
	Coord c2 {3, 7};
	g.creeTunnel(c1, c2, 0);
	CHECK_THROWS_AS(t2.dechargeBrindille(g), runtime_error); // La case devant contient une entrée de tunnel
}

void Termite::passeTunnel(Grille &g) {
	// Si l'autre bout du tunnel est entouré sur le moment
	if (g.voisinsLibreTunnel(g.CoordAutreEntree(coordonnee())).size() == 0) 
		marcheAleatoire(g);
	else {
		bool tempBrind = brindille_; // Pour ne pas perdre ses données en le supprimant (en le "téléportant") d'où il est 
		bool tempSablier = sablier_;
		Coord c = coordonnee();
		Direction d = g.voisinsLibreTunnel(g.CoordAutreEntree(c))[rand() % g.voisinsLibreTunnel(c).size()]; // On choisit une direction aléatoire parmi celles qui sont libres			
		Coord coordAutreBout = devantCoord(c, d);
		g.poseTermite(coordAutreBout, idTermite()); // On le pose à l'autre bout, mais dans une des cases libre autour de l'entrée 
		g.enleveTermite(c); 
		brindille_ = tempBrind; // Une fois à l'autre bout, il reprend ses valeurs d'attributs
		sablier_ = tempSablier;
		d_ = d;
	}
}
TEST_CASE("Méthode passeTunnel") {
	Grille g;
	int id = 0;
	Termite t1 = Termite{0, Coord{0, 0}};
	Termite t2 = Termite{1, Coord{3, 6}};
	vector<Termite> colonie = vector<Termite>{t1, t2};
	for (Termite t : colonie) {
		g.poseTermite(t.coordonnee(), id); 
		id++;
	}
	Coord c1 {1, 0};
	Coord c2 {4, 6};
	g.creeTunnel(c1, c2, 0);
	CHECK(t1.coordonnee() == Coord{0, 0});
	CHECK(t2.coordonnee() == Coord{3, 6});
	t1.avance(g);
	t2.avance(g);
	CHECK_FALSE(t1.coordonnee() == Coord{0, 0});
	CHECK_FALSE(t2.coordonnee() == Coord{0, 0});
		
	Coord c3 {tailleGrille-1, tailleGrille-1};
	Coord c4 {7, 7};
	g.creeTunnel(c3, c4, 1);
	g.poseBrindille(Coord{tailleGrille-2, tailleGrille-2}); // On entoure l'entrée se trouvant au coin de la grille 
	g.poseBrindille(Coord{tailleGrille-1, tailleGrille-2}); 
	g.poseBrindille(Coord{tailleGrille-2, tailleGrille-1});
		
	Termite t3 = Termite{2, Coord{6, 7}};
	g.poseTermite(t3.coordonnee(), t3.idTermite());
	t3.avance(g);
	// On vérifie que le termite a juste marché aléatoirement, sans s'être téléporté vers l'autre bout 
	CHECK(t3.coordonnee() != Coord{6, 7});
	CHECK(t3.coordonnee() != Coord{tailleGrille-2, tailleGrille-2}); 
	CHECK(t3.coordonnee() != Coord{tailleGrille-1, tailleGrille-2});
	CHECK(t3.coordonnee() != Coord{tailleGrille-2, tailleGrille-1});
}
		
bool Termite::tunnelEnFace(const Grille &g) const {
	try { 
		devant(); 
	} catch (invalid_argument &e) { return false; }
	return g.contientTunnel(devant());
}
TEST_CASE("Méthode tunnelEnFace") {
	Grille g;
	int id = 0;
	Termite t = Termite{0, Coord{0, 0}};
	vector<Termite> colonie = vector<Termite>{t};
	for (Termite t : colonie) {
		g.poseTermite(t.coordonnee(), id); 
		id++;
	}
	t.tourneAGauche();
	CHECK_FALSE(t.tunnelEnFace(g)); // Termite regarde le mur
	t.tourneADroite();
	Coord c1 = devantCoord(t.coordonnee(), t.directionTermite());
	Coord c2 {5, 5};
	g.creeTunnel(c1, c2, 0);
	CHECK(t.tunnelEnFace(g));
	t.tourneADroite();
	CHECK_FALSE(t.tunnelEnFace(g)); // Termite regarde une case vide
}

void Termite::marcheAleatoire(Grille &g) {
	vector<Direction> voisins = voisinsLibre(g);
	bool tourne;
	if (laVoieEstLibre(g)) {
		tourne = float(rand())/float(RAND_MAX) <= probaTourner;
	} else tourne = true;
	if (tourne) {
		if (int(voisins.size()) == 0) {
			tourneAleat();
			return;
		} else d_ = voisins[rand() % int(voisins.size())];
	}
	avance(g);
}
TEST_CASE("Méthode marcheAleatoire") {
	Grille g;
	int id = 0;
	Termite t = Termite{0, Coord{0, 0}};
	vector<Termite> colonie = vector<Termite>{t};
	for (Termite t : colonie) {
		g.poseTermite(t.coordonnee(), id);
		id++;
	}
	g.poseBrindille(Coord{1, 0});
	g.poseBrindille(Coord{1, 1});
	g.poseBrindille(Coord{0, 1});
	t.marcheAleatoire(g);
	CHECK_FALSE(t.directionTermite() == Direction::Nord);
	while (t.directionTermite() != Direction::Nord) {
		t.tourneADroite();
	}
	t.chargeBrindille(g);
	t.marcheAleatoire(g);
	CHECK(t.coordonnee() != Coord{0, 0});
}

void Termite::vieTermite(Grille &g) {
	// Si le termite porte une brindille
	if (brindille_) {
		// Si le termite veut poser sa brindille mais n'a pas encore trouvé d'emplacement
		if (sablier_ == 0) {
			// Si le termite a trouvé un bon emplacement
			if (brindilleEnFace(g) and voisinsLibre(g).size() >= 2) {
				sablier_ = -1;    // Le termite note qu'il a trouvé un bon emplacement
				tourneAleat();    
			} else if (g.contientTunnel(coordonnee()))
				passeTunnel(g);      // Le termite passe dans le tunnel
			else 
				marcheAleatoire(g);    // Le termite continue de chercher un bon emplacement
		} else {
			// Si le termite à noté un emplacement pour poser sa brindille
			if (sablier_ == -1) {
				// Si la case devant le termite est vide
				if (laVoieEstLibre(g)) {
					dechargeBrindille(g);    // Le termite pose sa brindille
					sablier_ = dureeSablier;    // Le termite peut aller chercher une autre brindille
				}
				else tourneAleat();    // Le termite continue de tourner
			// Si le termite ne veut pas poser sa brindille
			} else {
				if (g.contientTunnel(coordonnee()))
					passeTunnel(g);
				else {
					marcheAleatoire(g);
					sablier_ -= 1;
				}
			}
		}
	// Si le termite ne porte pas de brindille
	} else {
		// Si le termite cherche une brindille
		if (sablier_ == 0) {
			// Si il a trouvé une brindille
			if (brindilleEnFace(g)) {
				chargeBrindille(g);    // Le termite prend la brindille qu'il a trouvé
				sablier_ = dureeSablier;    // Le termite peut aller trouver un emplacement pour la poser
			// Si il n'a pas trouvé de brindille
			} else if (g.contientTunnel(coordonnee()))
				passeTunnel(g);
			else 
				marcheAleatoire(g);    // Le termite continue de chercher
		// Si le termite ne cherche pas de brindille
		} else if (g.contientTunnel(coordonnee()))
			passeTunnel(g);
		else {
			marcheAleatoire(g);    // Le termite continue de s'éloigner
			sablier_ -= 1;
		}
	}
}
TEST_CASE("Méthode vieTermite") {
	Grille g;
	int id = 0;
	Termite t0 = Termite{0, Coord{0, 0}};
	Termite t1 = Termite{1, Coord{0, tailleGrille/4}};
	Termite t2 = Termite{2, Coord{tailleGrille/4, tailleGrille/4}};
	Termite t3 = Termite{3, Coord{tailleGrille/4, 0}};
	vector<Termite> colonie = vector<Termite>{t0, t1, t2, t3};
	for (Termite t : colonie) {
		g.poseTermite(t.coordonnee(), id);
		id++;
	}
	Coord c = Coord{tailleGrille/8, tailleGrille/8};
	g.poseBrindille(c);
	while (g.contientBrindille(c)) {
		for (int i = 0; i < int(colonie.size()); i++) {
			colonie[i].vieTermite(g);
		}
	}
	int gagnant = -1;
	for (int i = 0; i < int(colonie.size()); i += 1) {
		cout << "Le termite " << i << " pense être dans la case de coordonnées " << colonie[i].coordonnee();
		if (g.numeroTermite(colonie[i].coordonnee()) == i) cout << " et l'est vraiment" << endl;
		else cout << " mais ne l'est pas..." << endl;
		if (colonie[i].porteBrindille()) gagnant = i;
	}
	cout << "Le termite qui a attrapé la brindille en premier est le termite " << gagnant << endl;
}


