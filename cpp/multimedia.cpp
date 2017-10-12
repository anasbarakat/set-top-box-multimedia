#include "multimedia.h"

Multimedia::Multimedia()
{

}

Multimedia::Multimedia(string _name, string _pathname){
    name = _name;
    pathname = _pathname;

}

string Multimedia::getName() const{
    return name;
}

string Multimedia::getPathName() const{
    return pathname;
}

void Multimedia::setName(string n){
    name = n;
}

void Multimedia::setPathName(string pn){
    pathname = pn;
}

void Multimedia::print(ostream& s) const{
    s << name <<' '<< pathname;
}

void Multimedia::write(ostream & f) const {
    f << name << '\n' << pathname << '\n';
}

void Multimedia::read(istream & f) {
    getline(f, name);
    getline(f, pathname);
}



