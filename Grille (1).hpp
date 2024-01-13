#ifndef Grille_HPP
#define Grille_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "coord.hpp"
#include "animal.hpp"
#include "doctest.h"

class Grille{
private:
    std::vector<std::vector<int>> G;
public:
    //Constructeur
    
    /** alloue la mémoire nécessaire pour le vecteur à deux dimensions et initialise toutes ces cases à -1. 
    **/
    Grille();
    
    // Fonction membre : Getter
    
     /** Fonction membre ne modifiant pas l'état de l'objet courant permettnat d'obteniir l'entier stockée dans une case de la grille
     *@param Coord: Coordonnées de la case dont l'on souhaite connaitre la valeur
     *@return int: valeur de case dont les coordonnées sont passéés en paramètres.
     **/
    int getCase(Coord) const;
    
    //Fonction membre: Setter
    
    /** Fonction membre (procédure) affectant une valeur à une case de la grille
     *@param Coord: Coordonnées de la case que l'on modifie, si la case n'est pas vide throw invalid_argument
     **/
    void setCase(int id, Coord); 
    //Fonction membre : Etat
    /** Fonction membre ne modifiant pas l'état de l'objet courant permettant de vérifier si une case de la grille est vide
     *@param Coord: coordonnées de la case que l'on étudie
     *@return bool: return true si la case est vide, false sinon.
     **/
    bool caseVide(Coord) const;
    /** Fonction Membre (Procédure) vidant une case de la grille, c'est-à-dire lui affeter -1.
     *@param Coord: coordonnées de la grille que l'on souhaite vider, si la case est déjà vide thro invalid_argument
     **/
    void videCase(Coord); //si la case est déjà libre : exception
};

#endif