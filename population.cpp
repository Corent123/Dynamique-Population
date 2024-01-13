#include "population.hpp"

Population::Population()
{
    for (int i = 0; i < MAXCARD; i++)
    {
        ids[i] = false;
    }
}

TEST_CASE( "Constructeur"){
    int corr = 1;
    Population P;
    if (P.getIds().size() != 0) corr = 0; 
    CHECK(corr);
}

Animal Population::get(int id) const
{
    if (id < 0 or id >= MAXCARD)
    {
        throw invalid_argument("identifiant inexistant");
    }
    if (not ids[id])
    {
        throw invalid_argument("l'animal n'existe pas");
    }
    return (registre[id]);
}

vector<int> Population::getIds() const
{
    vector<int> v = {};
    for (int i = 0; i < MAXCARD; i++)
    {
        if (ids[i] == true)
        {
            v.push_back(i);
        }
    }
    return v;
}

int Population::reserve()
{
    for (int i = 0; i < MAXCARD; i++)
    {
        if (not ids[i])
        {
            ids[i] = true;
            return i;
        }
    }
}

void Population::set(Animal &a)
{
    int id = a.getId();
    ids[id] = true;
    registre[id] = a;
}

void Population::supprime(int id)
{
    if (id >= MAXCARD or id < 0)
    {
        throw invalid_argument("identifiant non valide");
    }
    if (not ids[id]) throw invalid_argument("identifiant non réservé");
    ids[id] = false;
}

TEST_CASE("reserve/set/get/supprime")
{
    Population pop;
    CHECK_THROWS_WITH(pop.get(-1), "identifiant inexistant");
    CHECK_THROWS_WITH(pop.get(MAXCARD), "identifiant inexistant");
    CHECK_THROWS_WITH(pop.get(0), "l'animal n'existe pas");
    CHECK_THROWS_WITH(pop.supprime(0), "identifiant non réservé");
    CHECK_THROWS_WITH(pop.supprime(-1), "identifiant non valide");
    CHECK_THROWS_WITH(pop.supprime(MAXCARD), "identifiant non valide");
    int id = pop.reserve();
    CHECK(pop.getIds() == std::vector<int>{id});
    Animal anim = Animal{Espece::Lapin, Coord{0, 0}, id};
    pop.set(anim);
    CHECK(pop.get(id).getId() == id);
    CHECK(pop.get(id).getEspece() == Espece::Lapin);
    CHECK(pop.getIds() == std::vector<int>{id});
    pop.supprime(id);
    CHECK(pop.getIds() == std::vector<int>{});
}
