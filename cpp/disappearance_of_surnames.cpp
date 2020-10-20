#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

inline void diplayState(unsigned long long nbGen, unsigned long long nbPat);

int main()
{
    unsigned int nbPers=1000, nbPatronyms=200, generationMax=500000, rangeToDisplay=10; /// !!! nbPers=nb of MALES
    srand(time(nullptr));
    if(nbPers%nbPatronyms!=0)
    {
        cerr << "Warning: number of persons isn't multiple of number of patronyms" << endl;
        nbPers-=nbPers%nbPatronyms;
    }
    unsigned int personsWithSamePatronym=nbPers/nbPatronyms;
    vector<long long> nbPersonsWithPatronym(nbPatronyms, personsWithSamePatronym);
    unsigned int generation=0;
    diplayState(generation, nbPersonsWithPatronym.size());
    for(generation=1; (generation<generationMax) && (nbPersonsWithPatronym.size()>1); generation++)
    {
        for(int j=0; j<nbPersonsWithPatronym.size(); j++)
        {
            unsigned int nbPersonsWithThisPatronym=nbPersonsWithPatronym[j];
            for(unsigned int k=0; k<nbPersonsWithThisPatronym; k++)
            {
                int familyToChange=j;
                while(familyToChange==j)
                {
                    familyToChange=rand()%nbPersonsWithPatronym.size();
                }
                switch(rand()%4)
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
    }
    cout << generation-1 << " generations needed in a way to have only one patronym" << endl;
    return 0;
}

inline void diplayState(unsigned long long nbGen, unsigned long long nbPat)
{
    cout << "Generation " << nbGen << ": " << nbPat << " patronyms" << endl;
}
