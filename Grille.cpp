#include "Grille.hpp"

Grille::Grille(){
    std::srand(std::time(NULL));
    G = std::vector<std::vector<int>> (TAILLEGRILLE);
    for(int i = 0; i < TAILLEGRILLE; ++i) {
        G[i] = std::vector<int>(TAILLEGRILLE, -1);
    }
}

bool Grille::caseVide(Coord C) const{
    if (G[C.getX()][C.getY()] == -1) return true;
    return false;
}

int Grille::getCase(Coord C) const{
    return G[C.getX()][C.getY()];
}

void Grille::videCase(Coord C){
    if (caseVide(C)) throw std::runtime_error("Case déjà libre");
    G[C.getX()][C.getY()] = -1;    
}

void Grille::setCase(int id, Coord C){
    if (not caseVide(C)) throw std::runtime_error("case déjà réservé");
    G[C.getX()][C.getY()] = id;     
}

// Pour tester les différentes fonctions membres, on a besoin des autres fonctions membres
TEST_CASE("Constructeur/caseVide/getCase/setCase"){
    Grille grille1;
    SUBCASE("setCase/getCase/videCase/caseVide"){
        grille1.setCase(1, Coord{1, 8});
        CHECK(grille1.getCase(Coord{1, 8}) == 1);
        grille1.setCase(2, Coord{2, 4});
        CHECK(grille1.getCase(Coord{2, 4}) == 2);
        CHECK_THROWS(grille1.setCase(100, Coord{2, 4}));
        CHECK(grille1.getCase(Coord{0, TAILLEGRILLE-1}) == -1);
        CHECK(grille1.getCase(Coord{0, 0}) == -1);
        
        CHECK(grille1.caseVide(Coord{0, 0}));
        CHECK(grille1.caseVide(Coord{0, TAILLEGRILLE-1}));
        
        
        CHECK_FALSE(grille1.caseVide(Coord{2, 4}));
        CHECK_FALSE(grille1.caseVide(Coord{1, 8}));
        
        grille1.videCase(Coord{2, 4});
        CHECK(grille1.caseVide(Coord{2, 4}));
        grille1.videCase(Coord{1, 8});
        CHECK(grille1.caseVide(Coord{1, 8}));
        CHECK_THROWS(grille1.videCase(Coord{1, 8}));
    }
    SUBCASE("Constructeur"){
        int test = 1;
        Grille grille2;
        for(int i = 0; i < TAILLEGRILLE; ++i){
            for(int j = 0; j < TAILLEGRILLE; ++j){
                if (not grille2.caseVide(Coord{i, j})) test = 0;
            }
        }
        CHECK(test);
    }
}
