#include "groupe.h"


void Groupe::printGroupe(ostream& s) const {

    for (list<MultPtr>::const_iterator it = this->begin(); it != this->end(); ++it){
       (*it)->print(cout);
    }
}


