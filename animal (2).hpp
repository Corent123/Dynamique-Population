#ifndef animal_HPP
#define animal_HPP

#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <cstdlib>
#include <ctime>
#include "doctest.h"
#include "coord.hpp"

#define FoodInit 5
#define FoodLapin 5
#define MaxFood 10
#define MinFreeBirthLapin 4
#define ProbReproLapin 0.30
#define FoodReprod 8
#define ProdBirthRenard 0.05

enum class Espece{Lapin, Renard};

class Animal{
private:
    Espece espece;
    Coord coord;
    int identifiant;
    int nourriture;
public:
    //Constructeur
    /** Constructeur qui initialise une variable de type Animal, le principale but est de pouvoir réaliser des arrays d'Animal ce qui n'est pas possible sans ce constructeur
    **/
    Animal();
    /** Constructeur qui initialise un Animal en fonction des paramètres passés en argument
     *@param Espece: permet d'initialiser l'attribut espece.
     *@param coord: permet d'initialiser l'attribut coord.
     *@param identifiant: permet d'initialiser l'identifiant de l'animal
     La nourriture de l'animal est initialise avec FoodInit (5)
     **/
    Animal(Espece, Coord, int);

    //Fonction membre : getter
    /** Fonction membre renvoyant l'espece de l'animal
     *@return Espece : l'espece de l'animal
     **/
    Espece getEspece() const;
    /** Fonction membre renvoyant les coordoonnées de l'animal dans une grille
     *@retun Coord: Les coordonnées de l'animal dans une grille
     **/
    Coord getCoord() const;
    /** Fonction membre renvoyant l'identifiant de l'animal dans une population
     *@return int: indentifiant de l'animal dans une population
     **/
    int getId() const;
    /** Fonction membre renvoyant le score de nourriture d'un animal entre 0 et 10.
     *@return int: le score de nourriture de l'animal
     **/
    int getNourriture() const;

    //setter
    /** Fonction membre (Procédure) permettant de modifier l'attribut coordonnées
     *@param Coord : les nouvelles coordonnées que l'on veut attribuer à l'animal.
     **/
    void setCoord(Coord);

    //Etat
    /** Fonction membre (Procédure) qui met à jour le score de nourriture d'un animal en lui ajoutant FoodLapin (5) mais en ne dépassant pas MasFood(10). Fonction utilisée pour les renards.
     **/
    void mange();
    /** Fonction membre (Procédure) qui met à jour le score nourriture d'un animal lorsqu'il ne mange en lui soustraiant 1.
    **/
    void jeune();
    /**Fonction membre ne modifiant pas l'objet courant qui indique si le score de nourriture est à zéro (utilisé pour les renards)
     *@return bool: true si le score de nourriture d'un renard est (inférieur ou) égal à zéro false sinon.
     **/
    bool meurt() const;
    /** Fonction membre ne modifiant pas l'objet courant qui vérifie si le score de nourriture d'un renard est supérieur à FoodReprod(8), si c'est le cas le renard à ProdBirthRenard (0.05) de se reproduire.
     *@return bool : true si le renard se reproduit false sinon.
     **/
    bool seReproduit() const; //renard
    /** Fonction membre ne modifiant pas l'objet courant qui vérifie si le nombre de voisin vides du lapin est supérieur à MinFreeBirthLapin(4), si c'est le cas le lapin à ProbReproLapin(0.30) chance de se reproduire.
     *@param int : le nombre de voisin vide de l'animal dans une grille
     *@return bool: true si le lapin se reproduit, false sinon.
     **/
    bool seReproduit(int) const; //Lapin
    
    //Affichage
    /** Fonction membre ne modifiant pas l'objet courant qui renvoie un charactère en fonction de l'espece de l'objet courant
     *@return char: 'R' pour les renard et 'L' pour les lapins.
     **/
    char toString() const;
};


#endif