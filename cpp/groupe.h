#ifndef GROUPE_H
#define GROUPE_H

#include <list>
#include <string>
#include "multimedia.h"

typedef std::shared_ptr<Multimedia> MultPtr;

using namespace std;

/**
 * Classe liste de multimédias
 */
class Groupe : public list<MultPtr>
{

private:
    string name="";

public:
    Groupe();

    Groupe(string _name){
        name = _name;
    }

    virtual ~Groupe(){}

    virtual string getName(){return name;}

    /**
     *affiche tous les multimédias du groupe avec leurs attributs
     */
    void printGroupe(ostream& s) const;
};

#endif // GROUPE_H
