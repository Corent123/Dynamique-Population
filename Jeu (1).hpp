#ifndef Jeu_HPP
#define Jeu_HPP

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <exception>
#include "doctest.h"
#include "coord.hpp"
#include "animal.hpp"
#include "population.hpp"
#include "Grille.hpp"

class Jeu{
private:
    Population populationJeu;
    Grille grilleJeu;
    
public:
    // Constructeur
    
    /** Constructeur qui permet de déclarer une variable de la classe Jeu,
     * ainsi que d'initialiser la population et la grille telle qu'il y ait environ 7% 
     * de renard, 20% de lapin et 73% de case Vide.
     **/
    Jeu();
    
    // Getter (afin de pouvoir tester les différentes fonctions membres)
    
    /** Fonction qui renvoie une copie de la grille
     * @return une copie de la grille du jeu
     **/
    Grille getGrille() const;
    /** Fonction qui renvoie une copie de la population
     * @return une copie de la population
     **/
    Population getPopulation() const;
    
    // Fonctions membres : Fonctionnement Jeu
    
    /** Procédure qui ajoute dans un animal dans grilleJeu et dans populationJeu
     * @param E : variable de type Espece (type énumérés) correspondant à l'espèce de l'animal que l'on ajoute à la population
     * @param C : variable de type Coord Coordonnées de l'animal dans la grille du jeu
     **/
    void ajouteAnimal(Espece E, Coord &C);
    /** Fonction membres qui renvoie l'ensembles des coordonnées des emplacements vides voisins des 
        coordonnées passées en paramètres
     * @param C : variable de type coordonées. Les coordonnées de l'emplacement 
       dans la grille dont l'on veut connaitre les coordoonées vides voisins
     * @return Un Ensemble de coordonnées coorespondant à des emplacement vides.
     **/
    Ensemble voisinsVides(Coord C) const;
    /** Fonction membres qui renvoie l'ensembles des coordonnées des emplacements voisins occupés par des lapins
        coordonnées passées en paramètres
     * @param C : variable de type coordonées. Les coordonnées de l'emplacement 
       dans la grille dont l'on donne les voisins
     * @return Un Ensemble de coordonnées coorespondant à des emplacement occupés par des lapins
     **/
    Ensemble voisinsLapins(Coord C) const;
    /** Procédure qui déplace un animal dans la grille. Les lapins sont déplacés dans des emplacements vides si possible et il se reproduise s'ils ont assez de cases voisines vides.
        les renards perdent un point de nourriture, si leur nourriture atteint 0 alors il meurt ils sont supprimées de la grille et de pla population. Sinon, ils sont déplacés sur les cases avec des lapins s'ils ont des voisins autour d'eux, dans ce cas le renard passer
        en paramètres mangera un lapin et l'on supprime le lapin de la population. Si aucun lapin n'est dans une case voisins du renard,
        alors le renard se déplace de façon aléatoire sur un emplacement vide si possible, si le renard se déplace il a une chance de se reproduire si son attribut nourriture est assze élevé.
      * @param A : variable de type Animal qui correspond à l'animal que l'on désire déplacer dans la grille. L'animal peut-être un lapin
      ou un renard.
      **/
    void deplacement(Animal &A);
    
    // Fonctions membres : affichage PPM et console
    
    /** Procédure qui affiche dans la console la grille en caractères ascii, un renard est représenté par un 'R', un lapin est représenté           par un 'L' tandis que les cases vides sont représentés par le caractère zéro '0'. **/
    void affichage() const;
    /** Procédure qui ecrit un fichier PPM dans lequel la grille est représenté. La fonction représente un renard par des pixels rouges, un         lapin est représenté par des pixels bleus tandis que les emplacement vides de la grille sont représentés par des pixels blancs. Un           emplacement de la grille est représenté par 20 pixels de largeur et 20 de hauteur. Une grille de taille 20 x 20 est donc représenté         par une image de taille 400x400. La fonction affiche aussi le nombre de lapin et de renard.**/
    void affichagePPM(std::string Cible) const;
    
    //Fonctions membres : verification de la Coherence du Jeu
    /** Fonctions membres vérifiant qu'il n'y ait pas de problème de cohérence entre les coordonnées stockées dans une variable Animal et           les coordonnées où se trouve sont identifiant.
     * @return bool : s'il y a une erreur de cohérence la fonction renvoie false sinon elle renvoie true. 
     **/
    bool verifieGrille() const;
    /** Procédures vérifiant que les différentes données stockées dans populationJeu et grilleJeu correspondent bien et qu'il n'y ait               pas d'erreur de cohérence. On vérifie si l'animal est stocké à l'emplacement correspondant à son identifiant dans la population. Si 
        l'animal est stocké à l'emplacement correspondant à son emplacement dans la population du Jeu. Si les coordonnées de l'animal ne             correspondent pas un emplacement vide de la grille ou que les coordonnées de l'animal ne correspndent pas au coordonnées où il se           trouve dans la grille. Enfin, on vérifie si la grille contient un animal qui n'existe pas dans la population.
     **/
    void IntegriteModele() const;
};

void affichage_test();

#endif