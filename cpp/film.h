#ifndef FILM_H
#define FILM_H

#include "video.h"
#include <string>
#include <vector>

/**
 * classe Film qui hérite de Video
 */
class Film : public Video
{

// pour permettre à la classe Database de faire des new de Film
friend class DataBase;

private:
    int *tabdurations=nullptr;
    int numberchapters=0;

    Film(){}

    //constructeur private pour empêcher le new sans passer par la table Database
    Film(string _name, string _pathname, int _duration,
         const int  *_tabdurations, int _numberchapters)
        : Video(_name,_pathname,_duration){

        tabdurations = new int[numberchapters = _numberchapters];
        for(int i = 0; i < numberchapters; ++i){
                tabdurations[i] = _tabdurations[i];
        }
    }

public:

    virtual ~Film(){
        cout << "décès:";
        print(cout);
        delete[] tabdurations;
    }

    virtual void setTabDurations(int * durationtab, int numchapters);

    virtual const int * getTabDurations() const;

    virtual int getNumberChapters() const;

    /**
     * renvoie le nom de la classe, utile pour la fabrique d'objets pour la désérialisation
     */
    virtual string getNameClass() const override;

    /**
     * affiche les attributs de l'objet film
     */
    void print(ostream& s) const override;

    /**
     * écrit le nom de la classe "Film" et ses attributs, pour la sérialisation
     */
    void write(ostream & f) const override;

    /**
     * lit le nom de la classe "Film" et ses attributs, pour la désérialisation
     */
    void read(istream & f) override;
};

#endif // FILM_H
