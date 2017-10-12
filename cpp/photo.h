#ifndef PHOTO_H
#define PHOTO_H
#include "multimedia.h"

class Photo : public Multimedia
{

// pour permettre à la classe Database de faire des new de Film
friend class DataBase;

private:
    float latitude=0;
    float longitude=0;

    //ce constructeur servira pour la fabrique d'objets createMultimedia dans database
    Photo(){}
    //constructeur private pour empêcher le new sans passer par la table Database
    Photo(string _name,string _pathname, float _latitude, float _longitude): Multimedia(_name, _pathname){
         latitude = _latitude;
         longitude = _longitude;
    }

public:

    virtual ~Photo(){
        cout<< "décès:";
        print(cout);
    }

    virtual float getLatitude() const {return latitude;}

    virtual float getLongitude() const{return longitude;}

    /**
     * renvoie le nom de la classe, utilisé pour la fabrique d'objet, pour la sé/désérialisation
     */
    virtual string getNameClass() const override{return "Photo";}

    virtual void setLatitude(float lt){latitude = lt;}

    virtual void setLongitude(float lg){longitude = lg;}

    /**
     * écrit les attributs de la photo dans un ostream s
     */
    void print(ostream& s) const override{
        s << name <<' '<< pathname <<' '<< latitude <<' '<<longitude;
    }

    /**
     * joue le multimedia Photo sur le serveur
     */
    void playMultimedia() const override{
        string str = "imagej "+ pathname+" &";
        system(str.c_str());
    }

    /**
     * écrit les attributs de Photo, pour la sérialisation
     */
    void write(ostream & f) const override {
        f << getNameClass() << '\n';
        Multimedia::write(f);
        f << latitude << '\n' << longitude << '\n';
    }

    /**
     * lit les attributs de Photo, pour la désérialisation
     */
    void read(istream & f) override {

        Multimedia::read(f);
        //on passe par des variables temporaires car getline ne prend que des string
        string lat;
        string lon;
        getline(f, lat);
        getline(f, lon);
        latitude = stof(lat);
        longitude = stof(lon) ;
    }

};

#endif // PHOTO_H
