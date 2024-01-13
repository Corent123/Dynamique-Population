#include "animal.hpp"

Animal::Animal(){
    espece = Espece{};
    coord = Coord{};
    identifiant = int{};
    nourriture = FoodInit;
}

Animal::Animal(Espece E, Coord C, int id){
    espece = E;
    coord = C;
    identifiant = id;
    nourriture = FoodInit;
}

Espece Animal::getEspece() const{
    return espece;    
}

Coord Animal::getCoord() const{
    return coord;    
}

int Animal::getId() const{
    return identifiant;    
}

int Animal::getNourriture() const{
    return nourriture;    
}

TEST_CASE("Getter"){
    Animal L{Espece::Lapin, Coord{2, 5}, 45};
    Animal R{Espece::Renard, Coord{7, 8}, 148};
    SUBCASE("Espece"){
        CHECK(L.getEspece() == Espece::Lapin);
        CHECK(R.getEspece() == Espece::Renard);
    }
    SUBCASE("Coord"){
        CHECK(L.getCoord() == Coord{2, 5});
        CHECK(R.getCoord() == Coord{7, 8});
    }
    SUBCASE("Id"){
        CHECK(L.getId() == 45);
        CHECK(R.getId() == 148);
    }
    SUBCASE("Nourriture"){
        CHECK(L.getNourriture() == FoodInit);
        R.jeune();
        CHECK(R.getNourriture() == FoodInit-1); 
    }
}

void Animal::setCoord(Coord C){
    coord = C;
}

TEST_CASE("setCoord"){
    Animal L{Espece::Lapin, Coord{2, 5}, 45};
    Animal R{Espece::Renard, Coord{7, 8}, 148};
    L.setCoord(Coord{0, 19});
    CHECK(L.getCoord() == Coord{0, 19});
    R.setCoord(Coord{7, 9});
    CHECK(R.getCoord() == Coord{7, 9});
}

// Méthode pour les renards normalement
void Animal::mange(){
    int a = nourriture + FoodLapin;
    if (a >= MaxFood) nourriture = MaxFood;
    else nourriture = a;
}

void Animal::jeune(){
    nourriture -= 1;
}

TEST_CASE("Mange/jeune"){
    Animal R1{Espece::Renard, Coord{0, 1}, 0};
    R1.jeune(); R1.jeune();
    CHECK(R1.getNourriture() == 3);
    R1.mange();
    CHECK(R1.getNourriture() == 8);
    
    Animal R2{Espece::Renard, Coord{7, 6}, 1};
    R2.mange();
    CHECK(R2.getNourriture() == MaxFood);
    R2.mange();
    CHECK(R2.getNourriture() == MaxFood);
}

// méthode seReproduit pour les lapins
bool Animal::seReproduit(int voisin) const{
    float r;
    if (voisin >= MinFreeBirthLapin){
        r = (std::rand() % 100)/ 100.0;
        return (r) < ProbReproLapin;
    }
    return false;
}

TEST_CASE("Reproduction Lapin"){
    std::srand(std::time(0));
    Animal L{Espece::Lapin, Coord{0, 1}, 0};
    float m = 0.;
    CHECK_FALSE(L.seReproduit(3));
    for(int i = 0; i < 1000; ++i){
        if(L.seReproduit(MinFreeBirthLapin)) ++m;
    }
    m = m / 1000.0;
    int a;
    if((m > (ProbReproLapin-0.05) and m < (ProbReproLapin+0.05))) a = 1;
    else a = 0;
    CHECK(a); //La fonction rand() ne renvoie qu'une unique valeur, le check ne fonctionne pas car m = 0 ou m = 1, dans les deux cas a = 0.
}

bool Animal::seReproduit() const{
    float r;
    if ( nourriture >= FoodReprod){
        r = (std::rand() % 100)/ 100.0;
        return (r) < ProdBirthRenard;    
    }
    return false;
}

TEST_CASE("Reproduction Renard"){
    std::srand(std::time(NULL));
    Animal R{Espece::Renard, Coord{5, 7}, 1};
    float m = 0;
    CHECK_FALSE(R.seReproduit());
    R.mange();
    for(int i = 0; i < 1000; ++i){
        if(R.seReproduit()) ++m;
    }
    m = m / 1000.0;
    int a;
    if((m > ProdBirthRenard-0.05 and m <= ProdBirthRenard+0.05)) a = 1;
    else a = 0;
    CHECK(a);
}

bool Animal::meurt() const{
    return nourriture <= 0;    
}

TEST_CASE("meurt"){
    Animal R{Espece::Renard, Coord{5, 7}, 1};
    R.jeune(); R.jeune(); R.jeune();
    CHECK_FALSE(R.meurt());
    R.jeune(); R.jeune();
    CHECK(R.meurt());
}

char Animal::toString() const{
    switch(espece){
        case Espece::Lapin: return 'L';
        case Espece::Renard: return 'R';
    }
    throw std::invalid_argument(" Espece non valide ");
}

TEST_CASE("toString"){
    Animal R{Espece::Renard, Coord{7, 8}, 0};
    Animal L{Espece::Lapin, Coord{10, 17}, 1};
    CHECK(R.toString() == 'R');
    CHECK(L.toString() == 'L');
}