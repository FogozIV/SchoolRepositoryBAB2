#include<iostream>
#include<string>
#include<iomanip>
#include<algorithm>
#include<list>
#include<vector>

using namespace std;

class Salarie{
    protected:
        string name;
        int salaries;
    public:
        istream& saisie(istream& stream=cin);
        ostream& display(ostream& stream=cout, bool end=true);
        string getName(){
            return this->name;
        }
        int getSalaries(){
            return this->salaries;
        } 
};


class Cadre;
class Employee;

class Actionnaire{
    string name;
    int money;
    public:
        istream& saisie(istream& stream=cin, bool m=true, int forced=-1);
        ostream& display(ostream& stream=cout, bool end=true);
        void promo(vector<Cadre>&, list<Employee>&);
        void baisse(list<Employee>& employees);
        int getMoney(){
            return this->money;
        }
};

class Heritier : public Actionnaire{
    char sexe;
    public:
        istream& saisie(int forced, istream& stream=cin);
        ostream& display(ostream& stream=cout, bool end=true);
};

class Employee : public Salarie{
    int age;
    public:
        istream& saisie(istream& stream=cin);
        ostream& display(ostream& stream=cout, bool end=true);
        void increase(int amount){
            salaries += amount;
            salaries < 0 ? salaries = 0 : salaries;
        }
        int getAge(){
            return this->age;
        }
        bool operator==(Employee b){
            return this->age == b.getAge() && this->name == b.getName() && this->salaries == b.getSalaries();
        }
};

class Cadre : public Salarie{
    int age;
    public:
        Cadre(){};
        Cadre(Employee e);
        istream& saisie(istream& stream=cin);
        ostream& display(ostream& stream=cout, bool end=true);
};

int displayMenu();

void mainLoop(list<Employee>&, vector<Cadre>&, Actionnaire*&, vector<Heritier>&, bool&);

template<template<typename, typename> class Container, typename Type, typename Allocator>
void addMore(Container<Type, Allocator>& container, string text, bool end=true){
    cout << "Combien de " << text << " voulez vous entrer ?";
    int amount;
    cin >> amount;
    cin.ignore();
    for(int i = 0; i < amount; i++){
        Type t;
        cin >> t;
        container.insert(end ? container.end() : container.begin(), t);
    }
}

template<typename Container>
void display(Container& container){
    for(auto a : container){
        cout << a << endl << endl;
    }
}

void applyDemocratie(Actionnaire*& action, vector<Heritier>& heritiers);

int main(){
    list<Employee> employees;
    vector<Cadre> cadres;
    Actionnaire* action = NULL; //empty
    vector<Heritier> heritiers;
    bool loop = true;

    while(loop){
        mainLoop(employees, cadres, action, heritiers, loop);
    }

    return EXIT_SUCCESS;
}

int displayMenu(){
    cout << "Que voulez vous faire ? " << endl;
    cout << "1. Saisie d'une liste d'employés" << endl;
    cout << "2. Saisie d'un vecteur de Cadres" << endl;
    cout << "3. Créer l'actionnaire" << endl;
    cout << "4. Promotions" << endl;
    cout << "5. Baisse des salaires par l'actionnaire" << endl;
    cout << "6. Grève Actionnaire remplacé par ses héritiers" << endl;
    int choice;
    cin >> choice;
    cin.ignore();
    return choice;
}

istream& operator>>(istream& stream, Actionnaire*& a){
    return a->saisie(stream);
}


void mainLoop(list<Employee>& employees, vector<Cadre>& cadres, Actionnaire*& action, vector<Heritier>& heritiers, bool& loop){
    switch(displayMenu()){
        case 1:
            cout << "Affichage de la liste des employees : " << endl; 
            addMore(employees, "employé");
            display(employees);
            break;
        case 2:
            addMore(cadres, "cadre", false);
            cout << "Affichage de la liste des cadres : " << endl;
            display(cadres);
            break;
        case 3:
            if(action == NULL && heritiers.size() == 0){
                action = new Actionnaire;
                cin >> action ;
                action->display();
            }else{
                cout << "Un actionnaire existe déjà ou il a été remplacé par la démocratie" << endl;
            }
            break;
        case 4:
            if(heritiers.size() != 0){
                cout << "Le regne de l'actionnaire est termine" << endl;
            }else
            if(action == NULL){
                cout << "Il n'y a aucun actionnaire" << endl;
            }else{
                action->promo(cadres, employees);
            }
            break;
        case 5:
            if(heritiers.size() != 0){
                cout << "Le regne de l'actionnaire est termine" << endl;
            }else
            if(action == NULL){
                cout << "Il n'y a aucun actionnaire" << endl;
            }else{
                action->baisse(employees);
                display(employees);
            }
            break;
        case 6:
            if(action == NULL){
                cout << "Il n'y a aucun actionnaire à détroner!" << endl;
            }else{
                applyDemocratie(action, heritiers);
                display(heritiers);    
            }
            break;
    }
}

istream& Salarie::saisie(istream& stream){
    cout << "Son Nom ? ";
    getline(stream, this->name);
    cout << "Son salaire ? ";
    stream >> this->salaries;
    stream.ignore();
    return stream;
}

istream& Employee::saisie(istream& stream){
    Salarie::saisie(stream);
    cout << "Son age ? ";
    stream >> this->age;
    stream.ignore();
    return stream;
}

istream& Cadre::saisie(istream& stream){
    Salarie::saisie(stream);
    cout << "Son age ? ";
    stream >> this->age;
    stream.ignore();
    return stream;
}

istream& Actionnaire::saisie(istream& stream, bool m, int forced){
    cout << "Nom " << (m ? "actionnaire" : "heritier") << " : ";
    getline(stream, this->name);
    if(m){
        cout << "Fortune : ";
        stream >> this->money;
        stream.ignore();
    }else{
        this->money = forced;
    }
    return stream;
}

istream& Heritier::saisie(int forced, istream& stream){
    Actionnaire::saisie(stream, false, forced);
    cout << "Quel est son sexe ?";
    stream>> this->sexe;
    return stream.ignore();
}

ostream& Salarie::display(ostream& stream, bool end){
    stream << "Nom : " << this->name << endl << "Salaire : " << this->salaries;
    if(end)
        stream<< endl;
    return stream;
}

ostream& Employee::display(ostream& stream, bool end){
    Salarie::display(stream) << "Age : " << this->age;
    return end ? stream << endl : stream; //more compact
}

ostream& Cadre::display(ostream& stream, bool end){
    Salarie::display(stream) << "Age : " << this->age;
    return end ? stream << endl : stream;
}

ostream& Actionnaire::display(ostream& stream, bool end){
    stream << "Nom : " << this->name << endl << "Fortune : " << this->money;
    return end ? stream << endl : stream;
}

ostream& Heritier::display(ostream& stream, bool end){
    Actionnaire::display(stream) << "Sexe : " << this->sexe;
    return end ? stream << endl : stream;
}

void Actionnaire::promo(vector<Cadre>& cadres, list<Employee>& employees){
    list<Employee> manipulation(employees);
    manipulation.sort([](Employee a, Employee b){return a.getAge() > b.getAge();});

    /*
        Just in case we want to increase the amount of promotion
    */
    for(int i = 0; i < 2; i++){
        employees.remove(*manipulation.begin());
        cadres.insert(cadres.begin(), Cadre(*manipulation.begin()));
        manipulation.erase(manipulation.begin());
    }
    cout << "Affichage des cadres " << endl;
    ::display(cadres);
    cout << "Affichage des employes" << endl;
    ::display(employees);
}

void Actionnaire::baisse(list<Employee>& employees){
    for(Employee& e: employees){
        e.increase(-5);
    }
}
istream& operator>>(istream& stream, Salarie& salarie){
    return salarie.saisie(stream);
}

istream& operator>>(istream& stream, Employee& e){
    return e.saisie(stream);
}

istream& operator>>(istream& stream, Cadre& e){
    return e.saisie(stream);
}

ostream& operator<<(ostream& stream, Actionnaire& a){
    return a.display(stream, false);
}

ostream& operator<<(ostream& stream, Employee& a){
    return a.display(stream, false);
}

ostream& operator<<(ostream& stream, Cadre& a){
    return a.display(stream, false);
}

ostream& operator<<(ostream& stream, Heritier& a){
    return a.display(stream, false);
}

ostream& operator<<(ostream& stream, Salarie& a){
    return a.display(stream, false);
}

void applyDemocratie(Actionnaire*& action, vector<Heritier>& heritiers){
    if(action == NULL)
        return;
    int money = action->getMoney();

    cout << "Combien d'héritier ? ";
    int herAmount;
    cin >> herAmount;
    cin.ignore();
    for(int i = 0; i < herAmount; i++){
        Heritier her;
        her.saisie(money / (herAmount - i));
        heritiers.insert(heritiers.begin(), her);
        money -= her.getMoney();
    }
    delete action;
    action = NULL;
}

Cadre::Cadre(Employee e){
    this->name = e.getName();
    this->age = e.getAge();
    this->salaries = e.getSalaries();
}
