#include "film.h"

void Film::setTabDurations(int * durationtab, int numchapters){
    delete []tabdurations;
    tabdurations = new int[numchapters];
    for(int i = 0; i < numchapters; ++i){
            tabdurations[i] = durationtab[i];
    }
    numberchapters= numchapters;
}

const int * Film::getTabDurations() const{
    return tabdurations;
}

int Film::getNumberChapters() const{
    return numberchapters;
}

string Film::getNameClass() const {
    return "Film";
}

void Film::print(ostream& s) const {

    s << name <<' '<< pathname << ' '<< duration << ' ';
    s << '[';
    for(unsigned int k = 0; k < numberchapters-1; k++){
        s << tabdurations[k] <<',';
    }
    s << tabdurations[numberchapters-1];
    s << ']';
}

void Film::write(ostream & f) const {
    //on chaîne les méthodes write
    f << getNameClass() << '\n';
    Multimedia::write(f);
    //on ne fait pas appel ici à la méthode write de Video
    //pour ne pas écrire deux fois le nom de la classe
    f << duration << '\n';
    //d'abord numberchapters car facilitera après la relecture
    f << numberchapters << '\n';
    f << '[';
    for(unsigned int k = 0; k < numberchapters-1; k++){
        f << tabdurations[k] <<',';
    }
    f << tabdurations[numberchapters-1];
    f << ']' << '\n';
}

void Film::read(istream & f) {
    Multimedia::read(f);

    //on n'appelle pas read de Video ici
    //car sinon read de multimedia sera encore rappelée ce qui perturbera la lecture
    string d;
    getline(f, d);
    duration = stoi(d);

    string nc;
    getline(f, nc);

    //Reconstitution du tableau des durées
    string tab;
    getline(f, tab);
    tab.erase(0,1); //supprime le '['
    tab.pop_back(); //supprime le ']'

    vector<string> cop;
    stringstream ss(tab); // convertit la string en stream
    string tok;

    while(getline(ss, tok, ',')) {
            cop.push_back(tok);
            cout << tok;
    }

    int * table = new int[stoi(nc)];

    for(int i = 0; i < stoi(nc); i++){
            table[i] = stoi(cop[i]);
    }

    // modifie le tableau de durées en conséquence et l'attribut de nombre de chapitres
    setTabDurations(table, stoi(nc));
}
