#ifndef DATABASE_H
#define DATABASE_H

#include "multimedia.h"
#include "photo.h"
#include "video.h"
#include "film.h"
#include "groupe.h"

#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "tcpserver.h"

#include <map>
using namespace std;
using namespace cppu;

typedef std::shared_ptr<Film> FilmPtr;
typedef std::shared_ptr<Video> VideoPtr;
typedef std::shared_ptr<Photo> PhotoPtr;
typedef std::shared_ptr<Groupe> GpPtr;

/**
 * classe pour la gestion cohérente des données et implémentant
 * le traitement des requêtes avec la méthode processRequest
 */
class DataBase
{
private:
    map<string, MultPtr> objectsTab;
    map<string, GpPtr> groupsTab;

public:
    //DataBase(map<string, MultPtr> _objectsTab, map<string, GpPtr> _groupsTab);
    DataBase(){}


    /**
     *  crée une photo dans la table des multimédias de la base de données
     */
    PhotoPtr createPhoto(string _name,string _pathname, float _latitude,
                      float _longitude) ;
    /**
     *  crée une vidéo dans la table des multimédias de la base de données
     */
    VideoPtr createVideo(string _name, string _pathname, int _duration);

    /**
     *  créer un film dans la table des multimédias de la base de données
     */
    FilmPtr createFilm(string _name, string _pathname, int _duration,
                    const int  *_tabdurations, int _numberchapters);

    /**
     *  crée un groupe à partir d'un nom dans la table des groupes de la base de données
     */
    GpPtr createGroup(string _name);

    /**
     *  affiche tous les objets multimédia de la table de multimédias de la base de données
     */
    void print(ostream& s, string name) const;

    /**
     *  joue un multimédia sur le serveur
     */
    void play(ostream& s, string name) const;

    /**
     *  sérialise les objets de la map d'objets en écrivant dans un fichier
     */
    bool save(const string & fileName) const;

    /**
     *  fabrique d'objets pour la sérialisation
     */
    MultPtr createMultimedia(const string & classname) const;

    /**
     * déséréalise à partir d'un fichier contenant les objets
     * multimédia et leurs attributs
     */
    bool load(const string & fileName);

    /**
     *  traite les requêtes du client
     */
    bool processRequest(TCPConnection& cnx, const string& request, string& response);

};

#endif // DATABASE_H
