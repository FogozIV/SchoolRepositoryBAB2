#include<iostream>
#include<string>
#include<iomanip>
#include<algorithm>
#include<fstream>
#include<list>
#include<vector>

using namespace std;

const int MAXNOTE = 3;

class Personne{
    protected:
        int id;
        string name;
    public:
        int getId(){
            return this->id;
        }
        string getName(){
            return this->name;
        }
        void setName(string name){
            this->name = name;
        }
};

class Etudiant: public Personne{
    protected:
        int notes[MAXNOTE];
        int noteAmount = 0;
    public:
        Etudiant();
        ~Etudiant();
        void saisie();
        void affichage();
        int getNoteAmount(){
            return this->noteAmount;
        }
        void addNote(int note){
            if(noteAmount>=MAXNOTE){
                return;
            }
            this->notes[this->noteAmount++] = note;
        }

        int getNote(int index){
            return this->notes[index];
        }
};

class Prof: public Personne{
    protected:
        string service;
    public:
        Prof();
        ~Prof();
        void saisie();
        void affichage();
        string getService(){
            return this->service;
        }
        string setService(string service){
            this->service = service;
        }
};


void displayMenu();

template<typename Type, typename LV>
void addElement(LV&, int, Type*);

template<typename Type, typename LV>
void askElements(LV&, string);

template<typename LV>
void display(LV);

template<typename LV>
void deleteIndex(LV&, int);

template<typename Type, typename LV, typename UV>
void mainLoop(LV&, int&, bool&, list<string>&, UV&);

template<typename Type, typename LV>
void readFile(LV&, string);


const string states[] = {"etudiant", "prof"};

int main(){
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
    cout << "5. Lire depuis un fichier" << endl;
    cout << "6. Quitter" << endl;
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
        cin >> t;
        addElement<Type, LV>(array, 0, t);
    }
}

template<typename LV>
void display(LV array){
    for(auto t : array){
        cout << (t) << endl;
    }
}

template<typename LV>
void deleteIndex(LV &array, int index){
    if(index < 0 || index >= array.size()){
        cout << "Mauvais index" << endl;
        return;
    }
    auto a = array.begin(); //iterator
    advance(a, index);
    delete (*a);
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
            cin >> f;
            addElement<Type, LV>(array, 0, f);
            display<LV>(array);
            break;
        case 3:
            deleteIndex<LV>(array, 0);
            display<LV>(array);
            break;
        case 4:
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
            {
                string filename;
                cout << "Quel est le nom du fichier ? ";
                cin >> filename;
                cin.ignore(); //ignore the \n
                readFile<Type, LV>(array, filename);
                display<LV>(array);
                break;
            }
        case 6:
            loop = false;
            break;
        default:
            cout << "Veuillez entrer un nombre entre 0 et 6" << endl;
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
            lecture >> temp;
            array.push_back(temp);
        }
        lecture.close();
    }else{
        cout << "Le fichier " << filename << " n'existe pas ! " << endl;
    }
}

//Implémentations Prof

Prof::Prof(){
    static int current_id = 1;
    this->id = current_id++;
}
Prof::~Prof(){
    cout << "Le prof avec l'id : " << this->id << ", le nom : " << this->name << " et le service : "<< this->service << " a été détruit " << endl;
}

void Prof::saisie(){
    cout << "Veuillez renseigner le nom du prof : ";
    getline(cin, this->name);
    cout << "Veuillez renseigner le service du prof : ";
    getline(cin, this->service);
}

void Prof::affichage(){
    cout << "Prof:\n\tId : " << this->id << "\n\tNom : " << this->name << "\n\tService : " << this->service << "\n";
}



//Implémentation étudiant
Etudiant::Etudiant(){
    static int current_id = 1;
    this->id = current_id++;
}
        
Etudiant::~Etudiant(){
    cout << "L'etudiant avec l'id : " << this->id << " et le nom : " << this->name << " a été détruit " << endl;
}

void Etudiant::saisie(){
    cout << "Veuillez renseigner le nom de l'étudiant : ";
    getline(cin, this->name);
    cout << "Combien de note voulez-vous entrer (MAX " << MAXNOTE << ") ?";
    cin >> this->noteAmount;
    this->noteAmount = min(this->noteAmount, 3);
    for(int i = 0; i < this->noteAmount; i++){
        cout << "Veuillez entrer la note " << (i+1) << " : "; 
        cin >> notes[i];
    }
    cin.ignore();
}

void Etudiant::affichage(){
    cout << "Etudiant:\n\tId : " << this->id << "\n\tNom : " << this->name;
    if(noteAmount)
        cout << "\n\tNotes : ";
        for(int i = 0; i < this->noteAmount; i++){
        cout << "Note " << (i+1) << " : " << notes[i];
    }
    cout << "\n";
}

ostream & operator<<(ostream& stream, Prof* prof){
    return stream << "Prof:\n\tId : " << prof->getId() << "\n\tNom : " << prof->getName() << "\n\tService : " << prof->getService();
}

ifstream & operator>>(ifstream & stream, Prof* prof){
    string temp;
    getline(stream, temp, ';');
    prof->setName(temp);
    getline(stream, temp);
    prof->setService(temp);
    return stream;
}

istream & operator >> (istream & stream, Prof*  prof){
    string temp;
    cout << "Veuillez renseigner le nom du prof : ";
    getline(stream, temp);
    prof->setName(temp);
    cout << "Veuillez renseigner le service du prof : ";
    getline(stream, temp);
    prof->setService(temp);
    return stream;
}

ostream & operator<<(ostream& stream, Etudiant* etudiant){
    stream << "Etudiant:\n\tId : " << etudiant->getId() << "\n\tNom : " << etudiant->getName();
    if(etudiant->getNoteAmount()){
        stream << "\n\tNotes : ";
        for(int i = 0; i < etudiant->getNoteAmount(); i++){
            stream << "\n\t\tNote " << (i+1) << " : " <<etudiant->getNote(i) << endl;
        }
    }
    return stream;
}

ifstream & operator>>(ifstream& stream, Etudiant* etudiant){
    string temp;
    getline(stream, temp);
    istringstream tempStream(temp);
    getline(tempStream, temp, ';');
    etudiant->setName(temp);
    int tempNote;
    while(!tempStream.eof()){
        tempStream>>tempNote;
        tempStream.ignore();
        etudiant->addNote(tempNote);
    }
    return stream;
}

istream & operator>>(istream& stream, Etudiant* etudiant){
    string temp;
    int tempN, tempN2;
    cout << "Veuillez renseigner le nom de l'étudiant : ";
    getline(stream, temp);
    etudiant->setName(temp);
    cout << "Combien de note voulez-vous entrer ? (MAX " << MAXNOTE << ")";
    stream >> tempN;
    tempN = min(tempN, 3);
    for(int i = 0; i < tempN; i++){
        cout << "Veuillez entrer la note " << (i+1) << " : "; 
        stream >> tempN2;
        etudiant->addNote(tempN2);
    }
    stream.ignore();
    return stream;
}
