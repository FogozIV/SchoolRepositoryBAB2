#include<iostream>
#include<string>
#include<iomanip>
#include<algorithm>
#include<list>
#include<vector>
#include<map>
#include<fstream>

#define SPACE_NOTE 3

using namespace std;

class Personne{
    //Empty this is for fun :)

};


class Etudiant : Personne{
    static int SPACE_ID;
    string id;
    static int SPACE_NAME;
    string name;
    list<int> notes;
    public:
        void setId(string id){
            this->id = id;
            SPACE_ID = max(SPACE_ID, (int) id.size() + 1);
        }

        void setName(string name){
            this->name = name;
            SPACE_NAME = max(SPACE_NAME, (int) name.size() + 1);
        }

        void addNote(int note){
            this->notes.push_back(note);
        }

        static int _SPACE_ID(){
            return SPACE_ID;
        }

        static int _SPACE_NAME(){
            return SPACE_NAME;
        }

        static ostream& GLOBAL(ostream& stream){
            return stream << "Etudiant : "  << endl << left<< setw(SPACE_ID) << "Id" << setw(SPACE_NAME) << "Name" << "Note";
        }

        string getName(){
            return this->name;
        }

        string getId(){
            return this->id;
        }

        list<int> getNotes(){
            return this->notes;
        }

        string getKey(){
            return this->id;
        }

};

int Etudiant::SPACE_ID = 4;
int Etudiant::SPACE_NAME = 8;


class Prof : Personne{
    static int SPACE_NAME;
    string name;
    static int SPACE_MATIERE;
    vector<string> matieres;
    public:
        void setName(string name){
            this->name = name;
            SPACE_NAME = max(SPACE_NAME, (int) name.size() + 1);
        }

        void addMatiere(string matiere){
            this->matieres.push_back(matiere);
            SPACE_MATIERE = max(SPACE_MATIERE, (int) matiere.size() + 1);
        }

        static int _SPACE_NAME(){
            return SPACE_NAME;
        }

        static int _SPACE_MATIERE(){
            return SPACE_MATIERE;
        }

        static ostream& GLOBAL(ostream& stream){
            return stream << "Prof : " << endl << left << setw(SPACE_NAME) << "Nom :" << setw(SPACE_MATIERE) << "Matiere :"; 
        }

        vector<string> getMatiere() {
            return this->matieres;
        }

        string getName(){
            return this->name;
        }

        string getKey(){
            return this->name;
        }
};

int Prof::SPACE_NAME = 8;
int Prof::SPACE_MATIERE = 9;

string states[] = {"Prof", "Etudiant"};


void displayMenu(bool state);

template<typename B>
void display(map<string, B> m){
    B::GLOBAL(cout) << endl; 
    auto it= m.begin();
    for(; it!= m.end(); it++){
        cout << it->second << endl;
    }
    cout << endl;
}

template<typename Current>
void operation(map<string, Etudiant>&, map<string, Prof>&, bool&, bool&, map<string, Current>&);

template<typename Type>
void readFile(map<string, Type>& map, string filename){
    ifstream input(filename);
    if(input){
        while(!input.eof()){
            Type t;
            input >> t;
            map[t.getKey()]= t;
        }
    }else{
        cout << "Erreur le fichier n'existe pas";
    }
}

int main(){
    map<string, Etudiant> mapE;
    map<string, Prof> mapP;
    bool loop = true;
    bool state = false;
    do{
        if(state)
            operation(mapE, mapP, state, loop, mapE);
        else
            operation(mapE, mapP, state, loop, mapP);
    }while(loop);
    return EXIT_SUCCESS;
}


void displayMenu(bool state){
    cout << "Que voulez vous faire ? " << endl;
    cout << "0. Inverse entre etudiant et prof" << endl;
    cout << "1. Saisir une map " << (state ? "d'etudiant" : "de prof") << " et afficher" << endl;
    cout << "2. Chercher si la map contient un " << states[state] << ", le supprimer et afficher" << endl;
    cout << "3. Suppression du contenu des 2 maps et afficher " << endl;
    cout << "4. Quitter" << endl;
}

template<typename Current>
void operation(map<string, Etudiant>& etudiants, map<string, Prof>& profs, bool& state, bool& loop, map<string, Current>& current){
    displayMenu(state);
    int choice;
    cin >> choice;
    cin.ignore();
    switch(choice){
        case 0:
            state = !state;
            break;
        case 1:
            {
                cout << "Quel est le nom du fichier ? ";
                string filename;
                getline(cin, filename);
                readFile(current, filename);
                display(current);
                break;
            }
        case 2:
            {
                cout << "Quel est le " << (state ? "id" : "nom") << " que vous chercher ?";
                string name;
                getline(cin, name);
                auto it = current.find(name);
                if(it != current.end()){
                    current.erase(it);
                }
                display(current);
                break;
            }
        case 3:
            etudiants.clear();
            profs.clear();
            display(etudiants);
            display(profs);
            break;
        case 4:
            loop = false;
            break;
        default:
            cout << "Erreur veuillez entrer une operation valide " << endl;
    }
}






ifstream& operator>>(ifstream& stream, Etudiant& e){
    string tempS;
    getline(stream, tempS, ';');
    e.setId(tempS);
    getline(stream, tempS, ';');
    e.setName(tempS);
    int nbr, temp;
    stream >> nbr;
    stream.ignore(); //ignore the ";"
    for(int i =0; i < nbr; i++){
        stream >> temp;
        stream.ignore();//ignore the ";" or "\n"
        e.addNote(temp);
    }
    return stream;
}

ifstream& operator>>(ifstream& stream, Prof& p){
    string tempS;
    getline(stream, tempS, ';');
    p.setName(tempS);
    int nbr;
    stream >> nbr;
    stream.ignore();
    for(int i =0; i < nbr; i++){
        getline(stream, tempS, ';');
        p.addMatiere(tempS);
    }
    stream.ignore(); //ignore the "\n"
    return stream;
}


ostream& operator<<(ostream& stream, Etudiant& e){
    stream << left <<setw(Etudiant::_SPACE_ID()) << e.getId() << setw(Etudiant::_SPACE_NAME()) << e.getName();
    list<int> notes = e.getNotes();
    for(int a : notes){
        stream << left << setw(SPACE_NOTE) << a;
    } 
    return stream;
}

ostream& operator<<(ostream& stream, Prof& p){
    stream << left << setw(Prof::_SPACE_NAME()) << p.getName();
    for(string mat : p.getMatiere()){
        stream << left << setw(Prof::_SPACE_MATIERE()) << mat;
    }
    return stream;
}
