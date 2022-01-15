#include<iostream>
#include<string>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<list>
#include<set>


//started at 12:05
using namespace std;

const int NOTES = 2;



class Personne{
    protected:
        string name;
    public:
        istream& saisie(istream& stream=cin);
        ostream& display(ostream& stream=cout, bool end=true);
};

class Student : public Personne{
    int marks[NOTES];
    char sexe;
    public:
        istream& saisie(istream& stream=cin, bool marksLess=false);
        ostream& display(ostream& stream=cout, bool end=true);
        bool isGirl(){
            return this->sexe == 'F';
        }
        float calculateMoyenne(){
            return this->calculateSum()/NOTES;
        }
        float calculateSum(){
            float sum = 0;
            for(int i = 0; i < NOTES; i++)
                sum+=this->marks[i];
            return sum;
        }
        bool operator==(Student s){
            return this->name == s.name && this->sexe == s.sexe;
        }
        bool operator<(Student s){
            return this->name < s.name;
        }
        string getName(){
            return this->name;
        }
};



int displayMenu();

template<typename Container>
void display(Container container){
    for(auto a : container){
        cout << a << endl << endl;
    }
}

template<template<class, class> class Container, class Type, class U>
void addElement(Container<Type, U>&, string, bool=false);

void mainLoop(list<Student>&, vector<Student>&, set<Student>&, bool&);

template<template<typename, typename> class Container, class Type, class U> 
int calculateGirlAmount(Container<Type, U> l);

template<template<class, class> class Container, class Type, class U>//U must be entered if we want auto detection to work
float calculateMoyenne(Container<Type, U>, int pos);

template<template<typename, typename> class Container, class Type, class U> 
int findIndex(Container<Type, U>, Type t);


template<template<typename, typename> class Container, class Type, class U> 
void removeAndAdd(Container<Type, U>&, set<Type>&);

int main(){
    list<Student> first;
    vector<Student> second;
    set<Student> girlOnly;
    bool loop = true;

    while(loop){
        mainLoop(first, second, girlOnly, loop);
    }


    return EXIT_SUCCESS;
}


int displayMenu(){
    cout << "Que voulez vous faire ? " << endl;
    cout << "1. Saisie de liste d'étudiant de premiere" << endl;
    cout << "2. Saisie de vecteur d'étudiant de 2ème" << endl;
    cout << "3. Calculer le nombre de fille dans la liste" << endl;
    cout << "4. Calculer et afficher la moyenne de l'étudiant à la position P" << endl;
    cout << "5. Chercher un étudiant" << endl;
    cout << "6. Filles dans un tableau dynamique" << endl;
    cout << "7. Rien" << endl;
    cout << "8. Quitter" << endl;
    int choice;
    cin >> choice;
    cin.ignore();
    return choice;
}

template<template<class, class> class Container, class Type, class U>//U must be entered if we want auto detection to work
void addElement(Container<Type, U>& container, string text, bool end){
    cout<< "Combien d'étudiant de " << text << " voulez vous saisir ? ";
    int amount;
    cin >> amount;
    cin.ignore();
    for(int i = 0; i < amount; i++){
        Type t;
        cin >> t;
        container.insert(end ? container.end() : container.begin(), t);
    }
}

bool girlFilter(Student s){
    return s.isGirl();
}

void mainLoop(list<Student>& first, vector<Student>& second, set<Student>& girls, bool& loop){
    switch(displayMenu()){
        case 1:
            addElement(first, "premiere", true);
            cout << "Liste d'étudiant de premiere :" << endl;
            display(first);
            break;
        case 2:
            addElement(second, "seconde");
            cout << "Liste d'étudiant de seconde :" << endl;
            display(second);
            break;
        case 3:
            cout << "Il y a " << calculateGirlAmount(first) << " filles dans la première liste." << endl;
            break;
        case 4:
            {
                cout << "Quel est la position ?";
                int pos;
                cin >> pos;
                cin.ignore();
                float moyenne = calculateMoyenne(first, pos);
                moyenne < 0 ? (cout << "Position invalide [0 => " << first.size() << "[")<<endl :  (cout << "La moyenne est de " << moyenne << endl);
                break;
            }
        case 5:
            {
                Student s;
                s.saisie(cin, true);
                int index = findIndex(first, s);
                index < 0 ? (cout << "L'étudiant n'est pas dans la liste" << endl) : (cout << "L'étudiant se trouve dans la liste à la position " << index << endl);
                index = findIndex(second, s);
                index < 0 ? (cout << "L'étudiant n'est pas dans le vecteur" << endl) : (cout << "L'étudiant se trouve dans le vecteur à la position " << index << endl);
                break;
            }
        case 6:
            removeAndAdd(first, girls);
            
            removeAndAdd(second, girls);
            cout << "Tableau dynamique " << endl;
            display(girls);

            cout << "Liste" << endl;
            display(first);
            cout << "Vector" << endl;
            display(second);

            break;
        case 7:
            break;
        case 8:
            loop = false;
            break;
    }
}

template<template<typename, typename> class Container, class Type, class U> 
void removeAndAdd(Container<Type, U>& container, set<Type>& set){
    auto it = container.begin();
    while(it != container.end()){
        if(it->isGirl()){
            set.insert(set.begin(), *it);
            it = container.erase(it);
        }else{
            it++;
        }
    }
}

template<template<typename, typename> class Container, class Type, class U> 
int findIndex(Container<Type, U> container, Type t){
    int index = -1;
    bool found = false;
    for(auto it = container.begin(); it != container.end() && !found; it++){
        index++;
        found = t == *it;
    }
    return found ? index : -1;
}

template<template<class, class> class Container, class Type, class U>//U must be entered if we want auto detection to work
float calculateMoyenne(Container<Type, U> l, int pos){
    if(pos >= l.size() || pos <0){
        return -1;
    }
    typename Container<Type, U>::iterator it = l.begin();
    advance(it, pos);
    return it->calculateMoyenne();
}

template<template<typename, typename> class Container, class Type, class U> 
int calculateGirlAmount(Container<Type, U> l){
    int girlAmount = 0;
    const auto funct = [&girlAmount](Student a){a.isGirl() ? girlAmount++ : 0;}; //reference hack is insane
    for_each(l.begin(), l.end(), funct);
    return girlAmount;
}


istream& Personne::saisie(istream& stream){
    cout << "Nom ? ";
    getline(stream, this->name);
}

istream& Student::saisie(istream& stream, bool marksLess){
    Personne::saisie(stream);
    if(!marksLess){
        for(int i = 0; i < NOTES; i++){
            cout << "Note" << (i+1) << " ? ";
            stream >> this->marks[i];
        }
        stream.ignore();
    }
    cout << "Son sexe ?";
    stream >> this->sexe;
    return stream.ignore();
}

ostream& Personne::display(ostream& stream, bool end){
    stream << "Nom : " << this->name;
    return end ? stream << endl : stream;
}

ostream& Student::display(ostream& stream, bool end){
    Personne::display(stream);
    for(int i = 0; i < NOTES; i++){
        stream << "Note " << (i+1) << " : " << this->marks[i] << endl;
    }
    stream << "Sexe : " << this->sexe;
    return end ? stream << endl : stream;
}

ostream& operator<<(ostream& stream, Personne e){
    return e.display(stream, false);
}

ostream& operator<<(ostream& stream, Student e){
    return e.display(stream, false);
}

istream& operator>>(istream& stream, Personne& e){
    return e.saisie(stream);
}

istream& operator>>(istream& stream, Student& e){
    return e.saisie(stream);
}

bool operator<(Student a, Student b){
    return a.getName() < b.getName();
}
