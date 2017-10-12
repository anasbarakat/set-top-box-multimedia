
#define VERSION_NOUVELLE
#ifdef VERSION_ANCIENNE

#include "multimedia.h"
#include "photo.h"
#include "video.h"
#include "film.h"
#include "groupe.h"
#include "database.h"

typedef std::shared_ptr<Film> FilmPtr;
typedef std::shared_ptr<Video> VideoPtr;

int main(){

/*
 // remarque: le code commenté n'est plus compilable car
 //les constructeurs des différents multimédias sont private
 //pour interdire les new dans passer par la classe database
    //Test de video
    Video * v = new Video("tele", "path", 100);
    v->print(cout);

    //Test tableaux de multimedia
    Multimedia ** multimedias = new Multimedia * [5];

    unsigned int count = 0;
    multimedias[count++] = new Photo("a","patha",10, 20);
    multimedias[count++] = new Video("b","pathb", 100);
    multimedias[count++] = new Photo("c","pathc",20, 40);
    multimedias[count++] = new Video("d","pathd", 200);
    multimedias[count++] = new Photo("e","pathe",20.1, 40.2);

    for(unsigned int k = 0; k < 5; k++){
        multimedias[k]->print(cout);
    }

    delete [] multimedias;


    //Test Films
    int tab[3];
    for(unsigned int k = 0; k < 3; k++){
        tab[k] = k;
    }

    Film * f = new Film("oss117", "path", 100, tab, 3);
    f-> print(cout);

    Film * f2 = new Film("oss12", "path2", 100, tab, 3);
    f2-> print(cout);

    int tab2[7];
    for(unsigned int k = 0; k < 7; k++){
        tab2[k] = k;
    }
    f2-> setTabDurations(tab2,7);
    f2-> print(cout);

    int tab3[10];
    for(unsigned int k = 0; k < 7; k++){
        tab3[k] = 3*k;
    }

    Film * f3 = new Film("oana2", "pathooooo", 45, tab3, 3);
    f3-> getDuration();
    f3->getTabDurations();
    f3->print(cout);

    //Multimédias avec les smartPointers
    VideoPtr vs = VideoPtr(new Video("tele", "path", 100));
    FilmPtr fs = FilmPtr(new Film("oss117", "path", 100, tab, 3));
    FilmPtr f2s = FilmPtr(new Film("oss12", "path2", 100, tab, 3));
    FilmPtr f3s = FilmPtr(new Film("oana2", "pathooooo", 45, tab3, 3));


    //Test Groupes
    Groupe * g1 = new Groupe("GROUPE1");
    g1->push_back(fs);
    g1->push_back(vs);
    g1->push_back(f2s);


    Groupe * g2 = new Groupe("GROUPE2");
    g2->push_back(f3s);
    g2->push_back(f2s);

    cout << "MON GROUPE1" << endl;
    g1->printGroupe(cout);

    cout << "MON GROUPE2" << endl;
    g2->printGroupe(cout);

    g2->pop_back();

    cout<< "MON NOUVEAU GROUPE2" <<endl;
    g2->printGroupe(cout);

    cout<< "gr1" <<endl;
    g1->printGroupe(cout);

    g1->pop_back();

    cout<< "gr1 new" <<endl;
    g1->printGroupe(cout);

    */
    //Test de Database


    int tab[3];
    for(unsigned int k = 0; k < 3; k++){
        tab[k] = k;
    }

    DataBase * table = new DataBase();
    table->createFilm("oss7", "path", 100, tab, 3);
    table->createVideo("tele", "pathououou", 100);
    table->print(cout,"oss7");
    table->print(cout, "tele" );


}
#endif

#ifdef VERSION_NOUVELLE

#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include "tcpserver.h"
#include "database.h"

using namespace std;
using namespace cppu;

const int PORT = 3330;

int main(int argc, char* argv[])
{
    int tab[3];
    for(unsigned int k = 0; k < 3; k++){
        tab[k] = k;
    }

  // cree le TCPServer
  shared_ptr<TCPServer> server(new TCPServer());

  // cree l'objet qui gère les données
  shared_ptr<DataBase> base(new DataBase());

/*
  base->createFilm("oss7", "path", 100, tab, 3);
  base->createVideo("tele", "pathououou", 100);
  base->createFilm("oss8", "pathokok", 100, tab, 3);
  base->createFilm("oss117", "pathini", 100, tab, 3);
  base->createPhoto("Paris","mypath", 10000, 19)->setLatitude(222);

  //Test de sérialisation
  base->save("testSerialize.txt");
*/

  //Test de désérialisation
  base->load("testSerialize.txt");

  base->print(cout, "Paris");//on cherche Paris et tele après
  //les avoir créé à partir du fichier "testSerialize.txt" qui les contient
  base->print(cout, "tele");
  base->print(cout, "oss7");


  // le serveur appelera cette méthode chaque fois qu'il y a une requête
  server->setCallback(*base, &DataBase::processRequest);

  // lance la boucle infinie du serveur
  cout << "Starting Server on port " << PORT << endl;
  int status = server->run(PORT);

  // en cas d'erreur
  if (status < 0) {
    cerr << "Could not start Server on port " << PORT << endl;
    return 1;
  }

  return 0;
}

#endif
