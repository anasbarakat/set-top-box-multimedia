#include "database.h"

/*Le constructeur ici pourrait être utile pour créer une table à partir des tables d'un autre utilisateur par exemple
si le premier veut copier la base d'un autre utilisateur
DataBase::DataBase(map<string, MultPtr> _objectsTab, map<string, GpPtr> _groupsTab)
{
    objectsTab = _objectsTab;
    groupsTab = _groupsTab;
}
*/

FilmPtr DataBase::createFilm(string _name, string _pathname, int _duration, const int *_tabdurations, int _numberchapters){
     FilmPtr f(new Film(_name, _pathname, _duration,_tabdurations,_numberchapters));
     objectsTab[_name] = f;
     return f;
}

PhotoPtr DataBase::createPhoto(string _name, string _pathname, float _latitude, float _longitude){

    PhotoPtr p(new Photo(_name, _pathname,_latitude, _longitude));
    objectsTab[_name] = p ;
    return p;

}

VideoPtr DataBase::createVideo(string _name, string _pathname, int _duration){
    VideoPtr v(new Video(_name, _pathname,_duration));
    objectsTab[_name] = v;
    return v;

}

GpPtr DataBase::createGroup(string _name){
    GpPtr g(new Groupe(_name));
    groupsTab[_name] = GpPtr(new Groupe(_name));
    return g;
}

void DataBase::print(ostream& s, string name) const{

    auto it = objectsTab.find(name);
    auto it2 = groupsTab.find(name);

    if(it!=objectsTab.end()){

            it->second->print(s);
            if(it2!=groupsTab.end()){
                    it2->second->printGroupe(s);
            }
    }else{
        s << "L'objet cherché n'existe pas dans la base de données"<< endl;
    }
}

void DataBase::play(ostream& s, string name) const{

    auto it = objectsTab.find(name);

    if(it!=objectsTab.end()){

            it->second->playMultimedia();
    }
    else{
        s << "Le nom de multimédia cherché n'existe pas dans la base de données"<< endl;
    }

}

bool DataBase::save(const string & fileName) const{
    ofstream f(fileName);
    if (!f) {
        cerr << "Can't open file " << fileName << endl;  return false;
    }
    //itération sur les éléments de la map de multimédias
    for (auto const& it : objectsTab){
        it.second->write(f);
     }
    f.close();
    return true;
}

/**
 * crée un objet multimédia avec attributs par défaut en fonction de classname,
 *  dont les attributs seront rajoutés lors de la désérialisation
 */
MultPtr DataBase::createMultimedia(const string & classname) const{

       MultPtr object = nullptr;

       if(classname == "Photo"){
           object = PhotoPtr(new Photo());
        }
       if(classname == "Video"){
           object = VideoPtr(new Video());
       }
       if(classname == "Film"){
           object = FilmPtr(new Film());
        }
       if(object != nullptr)
           return object;
       else
           return nullptr;
}

/**
 * crée les objets et
 * les rajoute à la table d'objets multimédia, attribut de la map
 */
bool DataBase::load(const string & fileName){

    ifstream f(fileName);
    if (!f) {
        cerr << "Can't open file " << fileName << endl;  return false;
    }

    while (f) {       // pas d’erreur et pas en fin de fichier
        string className;
        getline(f, className);
        MultPtr m = createMultimedia(className);

        if(m) m->read(f);//le polymorphisme fait le travail ici

        if (f.fail()) {  // erreur de lecture
              return false;
        }
        else{
            string n = m->getName();
            objectsTab[n] = m;
        }
    }
    f.close();
    return true;
}

/**
 * Cette méthode est appelée chaque fois qu'il y a une requête à traiter.
 * C'une methode de la classe qui gere les données, afin qu'elle
 * puisse y accéder.
 *
 * Arguments:
 * - 'request' contient la requête
 * - 'response' sert à indiquer la réponse qui sera renvoyée au client
 * - si la fonction renvoie false la connexion est close.
 *
 * Cette fonction peut etre appelée en parallele par plusieurs threads (il y a
 * un thread par client).
 *
 * Elle gère les accès concurrentiels avec un verrou TCPLock
 */
bool DataBase::processRequest(TCPConnection& cnx, const string& request, string& response){

  cerr << "\nRequest: '" << request << "'" << endl;

  // 1) pour decouper la requête:
  // on peut par exemple utiliser stringstream et getline()
  stringstream ss;
  ss.str(request);

  //operation vaudra "chercher" ou "jouer"
  string operation = "";
  string name = "";

  getline(ss, operation,' ');
  getline(ss, name, ' ');

  cout << operation << endl;
  cout << name <<endl;

  stringstream strm;

  //on appelle la bonne méthode selon l'opération voulue par le client
  if(operation.compare("chercher") == 0){
      TCPLock lock(cnx, true);
      print(strm, name);
  }

  if(operation.compare("jouer") == 0){
      TCPLock lock(cnx);
      play(strm, name);
  }

  cout << strm.str();
  //response = "OK: " + request;
  response = strm.str();
  cerr << "response: " << response << endl;

  // renvoyer false si on veut clore la connexion avec le client
  return true;
}

