#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

inline void diplayState(unsigned long long nbGen, unsigned long long nbPat);

int main()
{
    unsigned int nbPers=5000, nbPatronyms=4, generationMax=0, rangeToDisplay=1; /// !!! nbPers=nb of MALES
    if(nbPers<nbPatronyms)
    {
        cerr << "Error: you need at least as much patronyms as persons" << endl;
        return -1;
    }
    if(nbPers%nbPatronyms!=0)
    {
        cerr << "Warning: number of persons isn't multiple of number of patronyms" << endl;
        nbPers-=nbPers%nbPatronyms;
    }
    default_random_engine gen(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<> dis(0, 3);
    unsigned int personsWithSamePatronym=nbPers/nbPatronyms;
    vector<long long> nbPersonsWithPatronym(nbPatronyms, personsWithSamePatronym);
    unsigned int generation=0, halfLife=0, halfLifeTime=nbPatronyms/2;
    diplayState(generation, nbPersonsWithPatronym.size());
    for(generation=1; (generation<generationMax || generationMax==0) && (nbPersonsWithPatronym.size()>1); generation++)
    {
        for(int j=0; j<(int)nbPersonsWithPatronym.size(); j++)
        {
            unsigned int nbPersonsWithThisPatronym=nbPersonsWithPatronym[j];
            for(unsigned int k=0; k<nbPersonsWithThisPatronym; k++)
            {
                int familyToChange=j;
                while(familyToChange==j)
                {
                    familyToChange=rand()%nbPersonsWithPatronym.size();
                }
                switch(dis(gen))
                {
                case 0:
                    nbPersonsWithPatronym[j]--;
                    nbPersonsWithPatronym[familyToChange]++;
                    break;
                case 1:
                    nbPersonsWithPatronym[j]++;
                    nbPersonsWithPatronym[familyToChange]--;
                    break;
                }
                if(nbPersonsWithPatronym[j]<=0)
                {
                    nbPersonsWithPatronym.erase(nbPersonsWithPatronym.begin() + j);
                    j--;
                    break;
                }
                if(nbPersonsWithPatronym[familyToChange]<=0)
                {
                    nbPersonsWithPatronym.erase(nbPersonsWithPatronym.begin() + familyToChange);
                    if(familyToChange<j)
                    {
                        j--;
                    }
                    if(nbPersonsWithPatronym.size() <= 1)
                    {
                        break;
                    }
                }
            }
        }
        if(generation%rangeToDisplay==0)
        {
            diplayState(generation, nbPersonsWithPatronym.size());
        }
        if(nbPersonsWithPatronym.size()<=halfLifeTime && halfLife==0)
        {
            halfLife=generation;
        }
    }
    cout << generation-1 << " generations needed in a way to have only one patronym" << endl;
    cout << "Half life: " << halfLife << " generations" << endl;
    return 0;
}

inline void diplayState(unsigned long long nbGen, unsigned long long nbPat)
{
    cout << "Generation " << nbGen << ": " << nbPat << " patronyms" << endl;
}
