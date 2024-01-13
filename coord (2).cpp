#include "coord.hpp"

Coord::Coord(){
    x = 0;
    y = 0;
}

Coord::Coord(int lig, int col){
    if (lig < 0 or lig >= TAILLEGRILLE or col < 0 or col >= TAILLEGRILLE)
        throw std::invalid_argument("Coordonnée incorrecte");
    x = lig;
    y = col;
}

Coord::Coord(int score){
    int tmpX = score / TAILLEGRILLE;
    int tmpY = score % TAILLEGRILLE;
     // On teste aussi tmpY car pr z < 0, z % d < 0 avec d un entier (en C++, C...)
    if (tmpX < 0 or tmpX >= TAILLEGRILLE or tmpY < 0)
        throw std::invalid_argument("Coordonnée incorrecte");
    x = tmpX;
    y = tmpY;
}

int Coord::toInt() const{
    return x * TAILLEGRILLE + y;   
}

TEST_CASE("Méthode ToInt"){
    Coord C1{4, 2};
    CHECK(C1.toInt() == 82);
    Coord C2{6, 6};
    CHECK(C2.toInt() == 126);
    Coord C3{0, 19};
    CHECK(C3.toInt() == 19);
    Coord C4{0, 0};
    CHECK(C4.toInt() == 0);
    Coord C5{19, 19};
    CHECK(C5.toInt() == 399);
}

int Coord::getX() const{
    return x;
}

int Coord::getY() const{
    return y;
}

std::ostream& operator<<(std::ostream& out, Coord C){
    out << '(' << C.getX() << ", " << C.getY() << ')';
    return out;
}

bool operator==(Coord A, Coord B){
    return ( A.getX() == B.getX() and A.getY() == B.getY() );   
}

TEST_CASE("Constructeurs / Getter"){
    SUBCASE("Constructeurs(lig/col)"){
        int err = 0;
        try {Coord{-1, 18};}
        catch(std::invalid_argument &e) {err = 1;}
        CHECK(err);
        err = 0;
        try {Coord{-6, 29};}
        catch(std::invalid_argument &e) {err = 1;}
        CHECK(err);
        err = 0;
        try {Coord{7, 20};}
        catch(std::invalid_argument &e) {err = 1;}
        CHECK(err);
        err = 0;
        try {Coord{7, 18};}
        catch(std::invalid_argument &e) {err = 1;}
        CHECK_FALSE(err);
    }
    SUBCASE("Constructeurs(score)"){
        int err = 0;
        try {Coord{TAILLEGRILLE*TAILLEGRILLE};}
        catch(std::invalid_argument &e) {err = 1;}
        CHECK(err);
        err = 0;
        try {Coord{-1};}
        catch(std::invalid_argument &e) {err = 1;}
        CHECK(err);
        Coord C1{TAILLEGRILLE+1};
        CHECK(C1.getX() == 1);
        CHECK(C1.getY() == 1);
        Coord C2{0};
        CHECK(C2.getX() == 0);
        CHECK(C2.getY() == 0);
        Coord C3{TAILLEGRILLE*TAILLEGRILLE-1};
        CHECK(C3.getX() == TAILLEGRILLE-1);
        CHECK(C3.getY() == TAILLEGRILLE-1);
    }
    SUBCASE("Getter"){
        Coord C1{4, 2};
        CHECK(C1.getX() == 4);
        CHECK(C1.getY() == 2);
        Coord C2{6, 6};
        CHECK(C2.getX() == 6);
        CHECK(C2.getY() == 6);
        Coord C3{0, 19};
        CHECK(C3.getX() == 0);
        CHECK(C3.getY() == 19);
    }
}

TEST_CASE("operator<<"){
    Coord C1{4, 2};
    Coord C2{6, 6};
    Coord C3{0, 19};
    
    std::ostringstream st;
    st << C1;
    CHECK(st.str() == "(4, 2)");
    st.str("");
    st << C2;
    CHECK(st.str() == "(6, 6)");
    st.str("");
    st << C3;
    CHECK(st.str() == "(0, 19)");
}

TEST_CASE("operator=="){
    Coord C1{4, 2};
    Coord C2{6, 6};
    Coord C3{0, 19};
    
    CHECK(C1 == Coord{4, 2});
    CHECK(C2 == Coord{6, 6});
    CHECK(C3 == Coord{0, 19});
}

// Fonction pour la classe Ensemble

Ensemble::Ensemble(){
    card = 0;    
}

bool Ensemble::estVide() const{
    return card == 0;    
}

TEST_CASE("Est_vide"){
    Ensemble C1;
    CHECK(C1.estVide());
    Ensemble C2;
    C2.ajoute(5);
    CHECK_FALSE(C2.estVide());
    Ensemble C3;
    C3.ajoute(1);
    C3.ajoute(2);
    CHECK_FALSE(C3.estVide());
}

int Ensemble::cardinal() const{
    return card;    
}

int Ensemble::getE(int i) const{
    return t[i];    
}

std::ostream& operator<<(std::ostream& out, Ensemble E){
    int i;
    out << '{';
    for(i = 0; i < E.cardinal(); ++i){
        out << E.getE(i) << ", ";
        if (i % TAILLEGRILLE == TAILLEGRILLE-1) out << std::endl;    
    }
    out << '}';
    return out;
}

TEST_CASE("opérateur d'affichage"){
    Ensemble C1;
    std::ostringstream st;
    st << C1;
    CHECK(st.str() == "{}");
    C1.ajoute(42);
    st.str("");
    st << C1;
    CHECK(st.str() == "{42, }");
    C1.ajoute(2);
    st.str("");
    st << C1;
    CHECK(st.str() == "{42, 2, }");
    Ensemble C2;
    for (int i = 0; i < 20; ++i) C2.ajoute(i);
    st.str("");
    st << C2;
    CHECK(st.str() == "{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, \n}");
}

void Ensemble::ajoute(int elem){
    if (card + 1 >= MAXCARD) throw std::runtime_error("Taille maximale de l'ensemble atteinte");
    t[card] = elem;
    ++card;
}

int Ensemble::tire(){
    if (card == 0) throw std::runtime_error("Array vide");
    if (card == 1) {--card; return t[0];}
    int ind = rand() % card;
    int e = t[ind];
    --card;
    for (int i = ind; i < card; ++i) t[i] = t[i+1];
    return e;
}

TEST_CASE("Fonction Tire"){
    std::srand(std::time(NULL));
    Ensemble E1;
    CHECK_THROWS_AS(E1.tire(), std::runtime_error);
    E1.ajoute(1);
    int a = E1.tire();
    CHECK(a == 1);
    CHECK(E1.estVide());
    for (int i = 0; i < 5; ++i) E1.ajoute(i*i);
    int c = E1.cardinal();
    a = E1.tire();
    CHECK(c-1 == E1.cardinal());
    int v = 0;
    for (int i = 0; i < 5; ++i){
        if (a == i * i) v = 1;    
    }
    CHECK(v);
}

bool operator==(Ensemble E1, Ensemble E2){
    if (E1.cardinal() != E2.cardinal()){std::cout << 1; return false;}
    for (int i = 0; i < E1.cardinal(); ++i){
            if (E1.getE(i) != E2.getE(i)) return false;
    }
    return true;
}

Ensemble Coord::voisin() const{
    Ensemble E;
    int im = std::max(x-1, 0);
    int iM = std::min(x+1, TAILLEGRILLE-1);
    int jm = std::max(y-1, 0);
    int jM = std::min(y+1, TAILLEGRILLE-1);
    for (int i = im; i <= iM; ++i){
        for(int j = jm; j <= jM; ++j){
          if (i != x or j != y) {
              E.ajoute(Coord{i, j}.toInt());
          }
        }
    }
    return E;
}

TEST_CASE("Voisin"){
    //Coin haut gauche de la grille
    Ensemble E;
    E = (Coord{0, 0}).voisin();
    Ensemble ET1;
    ET1.ajoute(Coord{0, 1}.toInt());
    ET1.ajoute(Coord{1, 0}.toInt());
    ET1.ajoute(Coord{1, 1}.toInt());
    CHECK(E == ET1);
    // endroit à l'intérieur de la grille
    Ensemble ET2;
    E = (Coord{5, 5}).voisin();
    ET2.ajoute(Coord{4, 4}.toInt());
    ET2.ajoute(Coord{4, 5}.toInt());
    ET2.ajoute(Coord{4, 6}.toInt());
    ET2.ajoute(Coord{5, 4}.toInt());
    ET2.ajoute(Coord{5, 6}.toInt());
    ET2.ajoute(Coord{6, 4}.toInt());
    ET2.ajoute(Coord{6, 5}.toInt());
    ET2.ajoute(Coord{6, 6}.toInt());
    CHECK(E == ET2);
    // endroit à l'intérieur de la grille
    Ensemble ET3;
    E = (Coord{7, 5}).voisin();
    ET3.ajoute(Coord{6, 4}.toInt());
    ET3.ajoute(Coord{6, 5}.toInt());
    ET3.ajoute(Coord{6, 6}.toInt());
    ET3.ajoute(Coord{7, 4}.toInt());
    ET3.ajoute(Coord{7, 6}.toInt());
    ET3.ajoute(Coord{8, 4}.toInt());
    ET3.ajoute(Coord{8, 5}.toInt());
    ET3.ajoute(Coord{8, 6}.toInt());
    CHECK(E == ET3);
    // au bord haut de la grille
    E = (Coord{9, 0}).voisin();
    Ensemble ET4;
    ET4.ajoute(Coord{8, 0}.toInt());
    ET4.ajoute(Coord{8, 1}.toInt());
    ET4.ajoute(Coord{9, 1}.toInt());
    ET4.ajoute(Coord{10, 0}.toInt());
    ET4.ajoute(Coord{10, 1}.toInt());
    CHECK(E == ET4);
    // bord gauche de la grille
    E = (Coord{0, 9}).voisin();
    Ensemble ET5;
    ET5.ajoute(Coord{0, 8}.toInt());
    ET5.ajoute(Coord{0, 10}.toInt());
    ET5.ajoute(Coord{1, 8}.toInt());
    ET5.ajoute(Coord{1, 9}.toInt());
    ET5.ajoute(Coord{1, 10}.toInt());
    CHECK(E == ET5);
    //
}