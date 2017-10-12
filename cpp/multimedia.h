#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class Multimedia
{

//droit d'accès donné à Database pour qu'elle puisse faire des new de Multimedia
friend class Database;

protected:
    string name;
    string pathname;

    // les constructeurs sont ici déclarés protected pour empêcher les new directs autres que ceux de la table
    Multimedia();
    Multimedia(string name,string pathname);

public:

    virtual ~Multimedia(){}

    virtual string getName() const;
    virtual string getPathName() const;
    virtual string getNameClass() const = 0;

    virtual void setName(string name);
    virtual void setPathName(string pathname);

    virtual void print(ostream& s) const;

    virtual void playMultimedia() const = 0;

    /**
     * écrit les attributs communs à tous les multimédias, pour la sérialisation
     */
    virtual void write(ostream & f) const;

    /**
     * lit les attributs communs à tous les multimédias, pour la désérialisation
     */
    virtual void read(istream & f);

};

#endif // MULTIMEDIA_H
