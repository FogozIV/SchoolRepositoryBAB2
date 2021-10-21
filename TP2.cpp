#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<algorithm>
#include<list>
#include<vector>
#include<iterator>

using namespace std;

class Personne{
    int id;
    string name;
    public:
        void saisie();
        void affichage();
        int getId();
        string getName();
        void setName(string);
        void importFromFile(istream&);
};

class Etudiant{
    static int currentId;
    int id;
    string name;
    public:
        Etudiant();
        void saisie();
        void affichage();
        int getId();
        string getName();
        void setName(string name);
        void importFromFile(istream&);
};

class Prof{
    static int currentId;
    int id;
    string name, service;
    public:
        Prof();
        void saisie();
        void affichage();
        int getId();
        string getName();
        string getService();
        void setService(string service);
        void setName(string name);
        void importFromFile(istream&);
};

void displayMenu();

template<typename Type, typename LV>
void addElement(LV&, int, Type*);

template<typename Type, typename LV>
void askElements(LV&, string);

template<typename LV>
void display(LV);

template<typename Type, typename LV>
void deleteIndex(LV&, int);

template<typename Type, typename LV, typename UV>
void mainLoop(LV&, int&, bool&, list<string>&, UV&);

template<typename Type, typename LV>
void readFile(LV&, string);


const string states[] = {"etudiant", "prof"};
const string filenames[] = {"Etudiant.txt", "Prof.txt"};

int main(){
    //Declaration of dynamic array with a default size of pointer size
    vector<Prof*> profs;
    list<Etudiant*> etudiants;
    list<string> strings;
    int state = 0;
    bool loop = true;
    do{
        if(state == 0){
            mainLoop<Etudiant, list<Etudiant*>, vector<Prof*>>(etudiants, state, loop, strings, profs);
        }else{
            mainLoop<Prof, vector<Prof*>, list<Etudiant*>>(profs, state, loop, strings, etudiants);
        }
    }while(loop);
    return EXIT_SUCCESS;
}

//Methods
void displayMenu(string current_state){
    cout <<"Actuellement en train de travailler avec les " << current_state << "s." << endl;
    cout << "0. Inverse entre etudiant et prof" << endl;
    cout << "1. Saisie et afficher un tableau de " << current_state << endl;
    cout << "2. Ajouter au debut et Afficher (" << current_state << ")" << endl;
    cout << "3. Supprimer au debut et Afficher (" << current_state << ")" << endl;
    cout << "4. Creer liste1 contenant les noms et Afficher (" << current_state << ")" << endl; 
    cout << "5. Quitter" << endl;
}

template<typename Type, typename LV>
void addElement(LV &array, int index, Type* element){
    if(index < 0 || index > array.size()){ 
        cout << "Mauvais index" << endl;
        return;
    }
    auto a = array.begin();
    advance(a, index);
    array.insert(a, element);
}

template<typename Type, typename LV>
void askElements(LV& array, string current_state){
    cout << "Combien de " << current_state << " voulez-vous ajouter ? ";
    int amount;
    cin >> amount;
    cin.ignore();
    Type* t;
    for(int i = 0; i < amount; i++){
        t = new Type();
        t->saisie();
        addElement<Type, LV>(array, 0, t);
    }
}

template<typename LV>
void display(LV array){
    for(auto t : array){
        cout << (t) << endl;
    }
}

template<typename Type, typename LV>
void deleteIndex(LV &array, int index){
    if(index < 0 || index >= array.size()){
        cout << "Mauvais index" << endl;
        return;
    }
    auto a = array.begin();
    advance(a, index);
    array.erase(a);
}


template<typename Type, typename LV, typename UV>
void mainLoop(LV &array, int& state, bool& loop, list<string>& strings, UV &other){   
    int index;
    cout << "Que voulez-vous faire ? " << endl;
    displayMenu(states[state]);
    cin >> index;
    cin.ignore();
    Type* f;
    switch(index){
        case 0:
            state= (state+1)%2;
            break;
        case 1:
            askElements<Type, LV>(array, states[state]);
            display<LV>(array);
            break;
        case 2:
            f = new Type();
            f->saisie();
            addElement<Type, LV>(array, 0, f);
            display<LV>(array);
            break;
        case 3:
            deleteIndex<Type, LV>(array, 0);
            display<LV>(array);
            break;
        case 4:
            //array.sort([](Type* a, Type* b){return a->getId() < b->getId();});
            strings.clear();
            for(auto a : array){
                strings.push_back(a->getName());
            }
            for(auto a: other){
                strings.push_back(a->getName());
            }
            display<list<string>>(strings);
            break;
        case 5:
            loop = false;
            break;
        default:
            cout << "Veuillez entrer un nombre entre 0 et 5" << endl;
            break;
    }
}


template<typename Type, typename LV>
void readFile(LV &array, string filename){
    ifstream lecture;
    lecture.open(filename);
    if(lecture){
        int amount;
        lecture >> amount;
        lecture.ignore();
        Type* temp = NULL;
        for(int i =0; i < amount; i++){
            temp = new Type();
            temp->importFromFile(lecture);
            array.push_back(temp);
        }
        lecture.close();
    }else{
        cout << "Le fichier " << filename << " n'existe pas ! " << endl;
    }
}


//Classes currentId
int Etudiant::currentId = 1;
int Prof::currentId = 1;

//Classes constructors
Etudiant::Etudiant(){
    this->id = this->currentId;
    this->currentId++;
}

Prof::Prof(){
    this->id = this->currentId;
    this->currentId++;
}

//Classes saisie
void Etudiant::saisie(){
    cout << "Veuillez renseigner le nom de l'etudiant : ";
    getline(cin, this->name);
}

void Prof::saisie(){
    cout << "Veuillez renseigner le nom du prof : ";
    getline(cin, this->name);
}

//Classes affichage
void Etudiant::affichage(){
    cout << "Etudiant:\n\tId : " << this->id << "\n\tNom : " << this->name << endl;
}

void Prof::affichage(){
    cout << "Prof:\n\tId : " << this->id << "\n\tNom : " << this->name << endl;
}

//Classes fileImporter
void Etudiant::importFromFile(istream& i){
    getline(i, this->name);
}

void Prof::importFromFile(istream& i){
    getline(i, this->name, ';');
    getline(i, this->service, '\n');
}


//Classes getter
int Etudiant::getId(){
    return this->id;
}

string Etudiant::getName(){
    return this->name;
}

int Prof::getId(){
    return this->id;
}

string Prof::getName(){
    return this->name;
}

string Prof::getService(){
    return this->service;
}

//Classes setter
void Etudiant::setName(string name){
    this->name = name;
}

void Prof::setName(string name){
    this->name = name;
}

void Prof::setService(string service){
    this->service = service;
}

//cout implementation
std::ostream &operator<<(std::ostream &os, Prof* &prof){
    return os << "Prof:\n\tId : " << prof->getId() << "\n\tNom : " << prof->getName();
}

std::ostream &operator<<(std::ostream &os, Etudiant* &etudiant){
    return os << "Etudiant:\n\tId : " << etudiant->getId() << "\n\tNom : " << etudiant->getName();
}
