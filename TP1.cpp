#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<algorithm>
#include<list>
#include<vector>
#include<iterator>

using namespace std;

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

template<typename Type>
void addElement(list<Type*>&, int, Type*);

template<typename Type>
void display(list<Type*>);

template<typename Type>
void deleteIndex(list<Type*>&, int);

template<typename Type>
void mainLoop(list<Type*>&, int&, bool&);

template<typename Type>
void readFile(list<Type*>&, string);


const string states[] = {"etudiant", "prof"};
const string filenames[] = {"Etudiant.txt", "Prof.txt"};

int main(){
    //Declaration of dynamic array with a default size of pointer size
    list<Prof*> profs;
    list<Etudiant*> etudiants;
    int state = 0;
    bool loop = true;
    do{
        if(state == 0){
            mainLoop(etudiants, state, loop);
        }else{
            mainLoop(profs, state, loop);
        }
    }while(loop);
    return EXIT_SUCCESS;
}

//Methods
void displayMenu(string current_state){
    cout <<"Actuellement en train de travailler avec les " << current_state << "s." << endl;
    cout << "0. Inverse entre etudiant et prof" << endl;
    cout << "1. Lire et afficher un tableau de " << current_state << endl;
    cout << "2. Ajouter au debut et Afficher (" << current_state << ")" << endl;
    cout << "3. Trier selon NOM et Afficher (" << current_state << ")" << endl;
    cout << "4. Trier selon Id et Afficher (" << current_state << ")" << endl; 
    cout << "5. Quitter" << endl;
}

template<typename Type>
void addElement(list<Type*> &array, int index, Type* element){
    if(index < 0 || index >= array.size()){ 
        cout << "Mauvais index" << endl;
        return;
    }
    auto a = array.begin();
    advance(a, index);
    array.insert(a, element);
}

template<typename Type>
void display(list<Type*> array){
    for(Type* t : array){
        t->affichage();
    }
}

template<typename Type>
void deleteIndex(list<Type*> &array, int index){
    if(index < 0 || index >= array.size()){
        cout << "Mauvais index" << endl;
        return;
    }
    array.erase(array.begin() + index);
}


template<typename Type>
void mainLoop(list<Type*> &array, int& state, bool& loop){   
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
            readFile(array, filenames[state]);
            display(array);
            break;
        case 2:
            f = new Type();
            f->saisie();
            addElement(array, 0, f);
            display(array);
            break;
        case 3:
            array.sort([](Type* a, Type* b){return a->getName() < b->getName();});
            display(array);
            break;
        case 4:
            array.sort([](Type* a, Type* b){return a->getId() < b->getId();});
            display(array);
            break;
        case 5:
            loop = false;
            break;
        default:
            cout << "Veuillez entrer un nombre entre 0 et 5" << endl;
            break;
    }
}


template<typename Type>
void readFile(list<Type*> &array, string filename){
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
