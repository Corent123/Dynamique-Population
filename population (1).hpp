#ifndef population_HPP
#define population_HPP

#include <array>
#include <vector>
#include <iostream>
#include "doctest.h"
#include "coord.hpp"
#include "animal.hpp"

using namespace std;

class Population
{
private:
    array<Animal, MAXCARD> registre;
    array<bool, MAXCARD> ids; //true si l'empalcement est resérvé false sinon/

public:
    // constructeur
    /** Constructeur initialisation toutes les valeurs de l'array ids à false, ainsi la population est vide**/
    Population();

    // getter
    /** Fonction membre ne modifiant pas l'état de l'objet courant qui permet de renvoyer l'animal d'identifiant id
     *@param int : id doit être >=0 et < MAXCARD(400) et il fait aussi que ids[id] soit égale à true autrement throw invalid_argument
     *@return Animal : l'animal d'indentifiant id dans la population
     **/
    Animal get(int id) const; 
    /** Fonction membre qui renvoie le vecteur des identifiants de tous les animaux qui sont dans la population
     @return vector<int> : vecteur des entiers id tel que ids[id] soit true.
     **/
    vector<int> getIds() const;
    /** Fonction membre qui renvoie un entier id tel que ids[id] soit false et fasse en sorte que ids[id] devienne vrai
     *@return int: identifiant n'appartenant à aucun animal au moment ou la fonction est appelée.
     **/
    int reserve();

    // setter
    /** Fonction membre (Procédure) permettant d'ajouter un animal dans la population
     *@param Animal& : Animal qui ajouté à la population
    **/
    void set(Animal &a);

    // destructeur
    /**Fonction membre qui supprime un animal de la population
     *@param id: id correspond à l'identifiant de l'animal a supprimer, le paramètre doit être >=0 et <MAXCARD et il fait que ids[id] soit true, autrement throw invalid_argument.
     **/
    void supprime(int id);
};

#endif