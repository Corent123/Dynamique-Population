#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "Jeu.hpp"

int main(){
    std::srand((unsigned int)std::time(0));
    Jeu jeu;
    Animal A;
    vector<int> animalsIds;
    int random;
    int tour = 1;
    std::string S;
    
    jeu.affichagePPM("animation/img0.ppm");
    for (int i = 0; i < 60; i++){ 
        animalsIds = jeu.getPopulation().getIds();
        while (animalsIds.size() != 0){
            random = std::rand() % animalsIds.size();
            A = jeu.getPopulation().get(animalsIds[random]);
            jeu.deplacement(A);
            animalsIds[random] = animalsIds[animalsIds.size()-1];
            animalsIds.pop_back();
            for (int j = 0; j < animalsIds.size(); j++){
                try{
                    jeu.getPopulation().get(animalsIds[j]);
                } catch (invalid_argument &e) {
                     animalsIds[j] = animalsIds[animalsIds.size()-1];
                     animalsIds.pop_back();
                }     
            }
        }
        jeu.IntegriteModele();
        S = "animation/img";
        S += std::to_string(tour) + ".ppm";
        jeu.affichagePPM(S);
        tour += 1;
    }   
    return 0;
}