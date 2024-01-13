#ifndef coord_HPP
#define coord_HPP

#include <exception>
#include <iostream>
#include <sstream>
#include <array>
#include <ctime>
#include <cstdlib>
#include "doctest.h"

#define TAILLEGRILLE 20
#define MAXCARD 400

class Ensemble{
private:
    std::array<int, MAXCARD> t;
    int card;
    
public:
    //Constructeur
    /**Permet de déclarer un ensemble tel que le cardinal de l'ensemble soit égal à zéro et donc que l'ensemble soit vide
    **/
    Ensemble();
    
    //Fonctions membres
    /** Fonction membre indiquant si un ensemble à zéro élément.
     * @return bool : true si l'ensemble à zéro élément false sinon
     **/
    bool estVide() const;
    /** Fonction membre indiquant le nombre d'élément dans l'ensemble
     * @return int : le nombre d'éléments de l'ensemble
     **/
    int cardinal() const;
    /** Fonction membre (Procédure) qui permet d'ajouter un élément à un ensemble.
     * @param int : l'entier que l'on souhaite ajouter à l'ensemble.
     **/
    void ajoute(int elem);
    /** Fonction membre getter qui permet d'accéder à un élément de l'ensemble
     *@param int: L'indice de l'élément auquel l'on souhaite accéder
     *@return int: l'élément dont on a passé l'indice en argument
     **/
    int getE(int i) const;
    /** Fonction membre qui supprime un élément aléatoirement de l'ensemble et le renvoie
     *@return int: L'élément que l'on a supprimé de l'ensemble
     **/
    int tire();
};

class Coord{
private:
    int x, y;
public:
    /**Constructeur vide qui initialise une coordonnée à {0, 0}, l'interet du constructeur est de pouvoir utilisé Coord en paramètre de           fonction, ou pour pouvoir faire des array de Coord.
    **/
    Coord();
    /** Constructeur qui initialise une variable de type Coord selon deux entier passées en argument.
     *@param lig : entier correspondant à la coordonnée x respectant les condition >= 0 et < TAILLEGRILE(20)
     *@param col : entier correspondant à la coordonnée y respectant les condition >= 0 et < TAILLEGRILE(20)
    **/
    Coord(int lig, int col);
    /**Constructeur qui initialise une variable de type Coord selon un entier à partir duquel on peut extraire des coordonnées grâce à deux        opérations. {score / TAILLEGRILLE, score % TAILLEGRILLE}
    **/
    Coord(int score);
    
    // Fonction membre : getter
    /** Fonction membre permettant d'obtenir la coordonnée x.
     *@return int: la coordonnée x
     **/
    int getX() const;
    /** Fonction membre permettant d'obtenir la coordonnée y.
     *@return int: la coordonnée y.
     **/
    int getY() const;
    
    // Fonction membre : divers
    /** Fonction memmbre ne modifiant pas l'état de l'objet courant qui transforme une coordonnée en entier selon la formule 20*x+y
     *@return int : l'entier représentant les coordonnées.
     **/
    int toInt() const;
    /** Fonction membre ne modifiant pas l'état de l'objet courant qui renvoie les coordoonées voisines de l'objet courant.
     *@return Ensemble: Ensemble des coordonnées voisine de l'objet courant sous forme d'entier.
     **/
    Ensemble voisin() const;
};

//opérateur d'affichage de la classe coord
std::ostream& operator<<(std::ostream& out, Coord c);
//opérateur d'égalité
bool operator==(Coord A, Coord B);

// Opérateur d'affichage de l'ensemble
std::ostream& operator<<(std::ostream& out, Ensemble E);
#endif
