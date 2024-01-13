#include "Jeu.hpp"

// Constructeur
Jeu::Jeu(){

    populationJeu = Population{};
    grilleJeu = Grille{};
    
    float vA;
    Coord C;
    for (int i = 0; i < TAILLEGRILLE; ++i){
        for (int j = 0; j < TAILLEGRILLE; ++j){
            vA = rand() % 101 / 100.0;
            C = Coord{i, j};
            if (vA < 0.07) {
                ajouteAnimal(Espece::Renard, C); 
            }
            else if (vA >= 0.07 and vA < 0.27){
                ajouteAnimal(Espece::Lapin, C);
            }
            else grilleJeu.setCase(-1, C);
        }
    }
}

//Fonction Membre : Getter
Grille Jeu::getGrille() const{
    return grilleJeu;    
}

Population Jeu::getPopulation() const{
    return populationJeu;
}


// Fonctions membres : Fonctionnement Jeu
void Jeu::ajouteAnimal(Espece E, Coord &C){
    int id = populationJeu.reserve();
    Animal A{E, C, id};
    grilleJeu.setCase(id, C);
    populationJeu.set(A);
}

TEST_CASE("Constructeur/ajouteAnimal"){
    /** On vérifie que l'on a environ 7% de renard, 20% de lapin et 73% de vide dans le Jeu, le test peut échouer mais cela reste rare**/
    Jeu J;
    float lapin = 0, renard = 0, vide = 0;
    int id;
    for (int i = 0; i < TAILLEGRILLE; ++i){
        for (int j = 0; j < TAILLEGRILLE; ++j){
            id = J.getGrille().getCase(Coord{i, j}); // ne marchera surement pas.
            if(id != -1 and J.getPopulation().get(id).getEspece() == Espece::Lapin){
                ++lapin;    
            } else if (id != -1 and J.getPopulation().get(id).getEspece() == Espece::Renard){
                ++renard;    
            } else {
                ++vide;    
            }
        }
    }
    lapin /= TAILLEGRILLE*TAILLEGRILLE;
    renard /= TAILLEGRILLE*TAILLEGRILLE;
    vide /= TAILLEGRILLE*TAILLEGRILLE;
    int corr = 0;
    if (lapin >= 0.15 and lapin <= 0.25) corr = 1;
    CHECK(corr); // Test Lapin
    corr = 0;
    if (renard >= 0.02 and renard <= 0.12) corr = 1;
    CHECK(corr); // Test Renard
    corr = 0;
    if (vide >= 0.68 and vide <= 0.78) corr = 1;
    CHECK(corr);
    corr = 0;
}

bool Jeu::verifieGrille() const{
    int id;
    Coord C;
    int a = 0;
    for (int i = 0; i < TAILLEGRILLE; ++i){
        for(int j = 0; j < TAILLEGRILLE; ++j){
            id = grilleJeu.getCase(Coord{i, j});
            if (id != -1) ++a;
            if (id != -1 and not (populationJeu.get(id).getCoord() == Coord{i, j})){
                return false;    
            }
        }
    }
    return true;
}

TEST_CASE("verifieGrille"){
    Jeu J;
    CHECK(J.verifieGrille());
}

Ensemble Jeu::voisinsVides(Coord C) const{
    Ensemble E = C.voisin(); // Coords voisines
    Ensemble ensembleCoordVide;
    int coordTest;
    while (E.cardinal() != 0){
       coordTest = E.tire();
        if ( grilleJeu.caseVide(Coord{coordTest}) ) ensembleCoordVide.ajoute(coordTest);
    }
    return ensembleCoordVide;
}

TEST_CASE("voisinsVides"){
   Jeu J;
   Ensemble E;
   int coord;
   int corr = 1;
   for (int i = 0; i < TAILLEGRILLE; ++i){
       for (int j = 0; j < TAILLEGRILLE; ++j){
           E = J.voisinsVides(Coord{i, j});
           while (E.cardinal() != 0){
               coord = E.tire();
               if (J.getGrille().getCase(Coord{coord}) != -1){
                   corr = 0;
                   break;
               }
           }
       }
   }
   CHECK(corr);
}

Ensemble Jeu::voisinsLapins(Coord C) const{
    Ensemble E = C.voisin();
    Ensemble ensembleCoordLapin;
    int coordTest;
    int id;
    while(E.cardinal() != 0){
        coordTest = E.tire();
        if (not grilleJeu.caseVide(Coord{coordTest}) ){
            id = grilleJeu.getCase(coordTest);    
            if ( populationJeu.get(id).getEspece() == Espece::Lapin){
                ensembleCoordLapin.ajoute(coordTest);    
            }
        }
    }
    return ensembleCoordLapin;
}

TEST_CASE("voisinsLapins"){
    Jeu J;
    Ensemble E;
    int coord;
    int corr = 1;
    int id;
    for (int i = 0; i < TAILLEGRILLE; ++i){
        for (int j = 0; j < TAILLEGRILLE; ++j){
            E = J.voisinsLapins(Coord{i, j});
            while (E.cardinal() != 0){
                coord = E.tire();
                id = J.getGrille().getCase(Coord{coord});
                if (id != -1 and J.getPopulation().get(id).getEspece() != Espece::Lapin){
                   corr = 0;
                   break;
               }
           }
       }
   }
   CHECK(corr);
}

void Jeu::deplacement(Animal &A){
    int nbVoisinLapin;
    Ensemble voisinLapin;
    int nbVoisinVide;
    Ensemble voisinVide;
    Coord coordAvantMove;
    int coordMove;
    
    coordAvantMove = A.getCoord();
    voisinLapin = voisinsLapins(coordAvantMove);
    nbVoisinLapin = voisinLapin.cardinal();
    voisinVide = voisinsVides(coordAvantMove);
    nbVoisinVide = voisinVide.cardinal();
    if (A.getEspece() == Espece::Lapin){
        if ( nbVoisinVide != 0){
            coordMove = voisinVide.tire();
            grilleJeu.videCase(coordAvantMove);
            A.setCoord(Coord{coordMove});
            populationJeu.set(A);
            grilleJeu.setCase(A.getId(), Coord{coordMove});
            if (A.seReproduit(nbVoisinVide)){
                ajouteAnimal(Espece::Lapin, coordAvantMove);
            }
         }
    } else if (A.getEspece() == Espece::Renard){
        coordMove = -1;
        A.jeune();
        if ( A.meurt() ){
            populationJeu.supprime(grilleJeu.getCase(coordAvantMove));
            grilleJeu.videCase(coordAvantMove);
        } else if ( nbVoisinLapin != 0) {
            coordMove = voisinLapin.tire();
            A.mange();
            populationJeu.supprime(grilleJeu.getCase(Coord{coordMove}));
            grilleJeu.videCase(Coord{coordMove});  
        } else if ( nbVoisinVide != 0){
            coordMove = voisinVide.tire();
        }
        if ( coordMove != -1) {
            grilleJeu.videCase(A.getCoord());
            A.setCoord(Coord{coordMove});
            populationJeu.set(A);
            grilleJeu.setCase(A.getId(), Coord{coordMove});
            if ( A.seReproduit() ) {
                ajouteAnimal(Espece::Renard, coordAvantMove);
            }
        }
    }   
}

TEST_CASE("Deplacement"){
    /** Dans le test suivant, on cherche à regarder si la fonction deplacement entraine des problèmes, notamment la disparition ou l'apparition de renard en cours de jeu, on ne cherche pas à simuler le jeu, ainsi, certains animaux se déplace plusieurs fois**/
    std::srand(std::time(0));
    Jeu J;
    J.affichage();
    int id;
    Animal A;
    int corr = 1;
    for (int i = 0 ; i < TAILLEGRILLE; ++i){
        for (int j = 0; j < TAILLEGRILLE; ++j){
           id = J.getGrille().getCase(Coord{i, j});
           if (id != -1) {
               A = J.getPopulation().get(id);
               J.deplacement(A);
           }
        }
    }
    try {
        J.verifieGrille();
        J.IntegriteModele();
    } catch (std::runtime_error &e){
        corr = 0;
    }
    CHECK(corr);
    
    Jeu J2;
    Animal A1 = J2.getPopulation().get(J2.getPopulation().getIds()[0]);
    Animal A2 = A1;
    J2.deplacement(A2);
    CHECK_FALSE(A1.getCoord() == A2.getCoord());
    CHECK(A1.getId() == A2.getId());
    CHECK(A1.getEspece() == A2.getEspece());
}

void Jeu::affichage() const{
    for (int i = 0; i < TAILLEGRILLE; ++i){
        for (int j = 0; j < TAILLEGRILLE; ++j){
            if (grilleJeu.getCase(Coord{i, j}) == -1) std::cout << std::setw(3) << '0' << " | ";
            else  std::cout << std::setw(3) << populationJeu.get(grilleJeu.getCase(Coord{i, j})).toString() << " | ";
        }
        std::cout<<std::endl;
    }
}

void Jeu::affichagePPM(std::string Cible) const{
    std::ofstream fichier;
    fichier.open(Cible);
    
    fichier << "P3" << "\n";
    fichier << TAILLEGRILLE*20 <<" " << TAILLEGRILLE*20 << "\n";
    fichier << 255 << "\n"; 
    
    int lapin = 0;
    int renard = 0;
    int a = 0;
    std::ostringstream s;
    for(int i = 0; i < TAILLEGRILLE; ++i){
       for(int j = 0; j < TAILLEGRILLE; ++j){
           a = grilleJeu.getCase(Coord{i, j});
           if (a == -1){
               for (int k = 0; k < 20; ++k){
                   fichier << "255" << ' ' << "255" << ' ' << "255" << ' ';
                   s << "255" << ' ' << "255" << ' ' << "255" << ' ';
               }
           } else if (populationJeu.get(a).getEspece() == Espece::Renard){
               renard += 1;
               for (int k = 0; k < 20; ++k){
                   fichier << "255" << ' ' << '0' << ' ' << '0' << ' ';
                   s << "255" << ' ' << '0' << ' ' << '0' << ' ';
               }
           } else {
               lapin += 1;
               for (int k = 0; k < 20; ++k){
                   fichier << '0' << ' ' << '0' << ' ' << "255" << ' ';
                   s << '0' << ' ' << '0' << ' ' << "255" << ' ';
               }
           }
       }
       for (int k = 0; k < 20; ++k) fichier << s.str();
       s.str("");
       fichier << "\n";
    }
    std::cout << " Nombre de Lapin: " << lapin << std::endl;
    std::cout << " Nombre de Renard: " << renard << std::endl;
    fichier.close();
}

void affichage_test(){
    Jeu J;
    J.affichage();
    J.affichagePPM("Jeu.ppm");
}

void Jeu::IntegriteModele() const{
    std::vector<int> identifiants = populationJeu.getIds();
    for (long unsigned int i = 0; i < identifiants.size(); ++i){
        if ( identifiants[i] != populationJeu.get(identifiants[i]).getId()){
            std::cout << " L'animal n'est pas stocké à l'emplacement correspondant à son identifiant" << std::endl;
            throw std::runtime_error("Erreur De coherence : Identifiant animal");
        }
    }
    Animal A;
    for (long unsigned int id = 0; id < identifiants.size() ;++id){
        A = populationJeu.get(identifiants[id]);
        if (grilleJeu.getCase(A.getCoord()) == -1){
            std::cout << "Un animal pense être dans un emplacement vide la grille" << std::endl;
            throw std::runtime_error("Erreur de coherence animal-grille");
        }
    }
    try{
        if (not verifieGrille() ){
            std::cout << "La grille contient un animal dont les coordonnées ne correspondent pas à son emplacement dnas la grille qui n'existe pas dans la population" << std::endl;
            throw std::runtime_error( "Erreur de coherence animal-grille" );
        }
    } catch (std::invalid_argument &e) { // erreur levé dans la fonction membre get de la classe population
        std::cout << "La grille contient un animal qui n'existe pas dans la population : " << e.what() << std::endl;
        throw std::runtime_error( "Erreur de coherence grille-animal" );
    }
}

TEST_CASE("IntegriteModele"){
    Jeu J;
    int err = 1;
    try {
        J.IntegriteModele();    
    } catch (std::runtime_error &e){
        err = 0;
    }
    CHECK(err);
}
