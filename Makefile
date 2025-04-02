CXX=g++
CXXFLAGS= -Wall -std=c++17 -g -O3
EXEC_FILES= projet test
# LDFLAGS= -lsfml-system -lsfml-window -lsfml-graphics

all: projet

# Règle générique
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

test: coord.o grille.o termite.o test.o 
	$(CXX) $(LDFLAGS) -o $@ $^ 

projet: coord.o grille.o termite.o projet.o
	$(CXX) $(LDFLAGS) -o $@ $^ 

# Dépendances selon les fichiers
coord.o: coord.hpp
grille.o: grille.hpp coord.hpp
termite.o : termite.hpp coord.hpp grille.hpp

check: test
	./test 

clean:
	rm -f $(OBJ) $(EXEC_FILES)
