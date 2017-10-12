#ifndef VIDEO_H
#define VIDEO_H
#include "multimedia.h"

/**
 *classe Video qui donne le droit d'accès à la classe Database pour lui permettre de faire des new de Film
 */
class Video : public Multimedia
{

friend class DataBase;

protected:
    int duration=0;

    /**
     * constructeur vide utilisé pour la fabrique d'objets pour la sérialisation:
     * voir la méthode createMultimedia dans database.cpp
     */
    Video(){}

    /**
     *constructeur private pour empêcher le new sans passer par la table Database
     */
    Video(string _name, string _pathname, int _duration): Multimedia(_name, _pathname){
        duration = _duration;
    }

public:

    virtual ~Video(){
        cout<< "décès:";
        print(cout);
    }

    virtual int getDuration() const {return duration;}

    virtual string getNameClass() const override{return "Video";}

    virtual void setDuration(int d){duration = d;}

    void print(ostream& s) const override{
        //on aurait pu ici chaîner les méthodes print (avec celle de Multimedia)
        s << name <<' '<< pathname << ' '<< duration;
    }

    /**
     * joue le multimédia video
     */
    void playMultimedia() const override{
        string str = "mpv "+ pathname+" &";
        system(str.c_str());
    }

    /**
     * écrit les attributs de Video, pour la sérialisation
     */
    void write(ostream & f) const override {
        f << getNameClass() << '\n';
        //on chaîne les méthodes write
        Multimedia::write(f);
        f << duration << '\n';
    }

    /**
     * lit les attributs de Video, pour la désérialisation
     */
    void read(istream & f) override {
        Multimedia::read(f);
        string d;
        getline(f, d);
        //la fonction stoi de std convertit une string en entier
        duration = stoi(d);
    }
};

#endif // VIDEO_H
