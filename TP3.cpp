#include<iostream>
#include<string>
#include<locale>
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
        string className;
    public:
        Personne(){
            static int current_id = 1;
            this->id = current_id++;
            this->className = "Personne";
        }
        void saisie();
        void affichage();
        int getId(){
            return this->id;
        }
        string getName(){
            return this->name;
        }
        void setName(string name){
            this->name = name;
        }
        string getClassName(){
            return this->className;
        }
        bool operator<(Personne b){
            return this->name < b.name;
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

class Etudiant;

class Direction : public Prof{
    protected:
        string title;
    public:
        Direction();
        void saisie();
        void affichage();
        string getTitle(){
            return this->title;
        }
        void setTitle(string title){
            this->title = title;
        }
        float calculateMoyenne(Etudiant e);
};

class Etudiant: public Personne{
    protected:
        int notes[MAXNOTE];
        int noteAmount = 0;
        float moyenne = -1;
        string year;
        friend float Direction::calculateMoyenne(Etudiant);
        friend ostream & operator<<(ostream&, Etudiant&);
    public:
        Etudiant();
        ~Etudiant();
        void saisie();
        void affichage();
        void addNote(int note){
            if(noteAmount>=MAXNOTE){
                return;
            }
            this->notes[this->noteAmount++] = note;
        }
        float getMoyenne(){
            return this->moyenne;
        }
        void setMoyenne(float moyenne){
            this->moyenne = moyenne;
        }
        string getYear(){
            return this->year;
        }
        void setYear(string year){
            this->year = year;
        }
        static bool complexSort(Etudiant a, Etudiant b){
            return a.year == b.year ? a.moyenne > b.moyenne : a.year < b.year;
        }
};

void displayMenu(string current_state);

template<typename Type, typename LV>
void addElement(LV&, int, Type);

template<typename Type, typename LV>
void askElements(LV&, string);

template<typename LV>
void display(LV&);

template<typename LV>
void deleteIndex(LV&, int);

void operations(vector<Prof>&, list<Etudiant>&, int&, bool&);

template<typename Type, typename LV>
void readFile(LV&, string);

const string states[] = {"etudiant", "prof"};

int main(){
    setlocale(LC_ALL, "fra");
    vector<Prof> profs;
    list<Etudiant> etudiants;
    int state = 0;
    bool loop = true;
    do{
        operations(profs, etudiants, state, loop);
    }while(loop);
    return EXIT_SUCCESS;
}

void operations(vector<Prof>& profs, list<Etudiant>& etudiants, int& state, bool& loop){
    displayMenu(states[state]);
    cout << "Que voulez vous faire ? ";
    int choice;
    cin >> choice;
    cin.ignore();
    switch(choice){
        case 0:
            state = (state + 1)%2;
            break;
        case 1:
            if(!state){
                askElements<Etudiant, list<Etudiant>>(etudiants, states[state]);
                display<list<Etudiant>>(etudiants);
            }else{
                askElements<Prof, vector<Prof>>(profs, states[state]);
                display<vector<Prof>>(profs);
            }
            break;
        case 2:
            {
                int index;
                cout << "Quel est l'index que vous voulez supprimer ? ";
                cin >> index;
                cin.ignore();
                if(!state){
                    deleteIndex<list<Etudiant>>(etudiants, index);
                    display<list<Etudiant>>(etudiants);
                }else{
                    deleteIndex<vector<Prof>>(profs, index);
                    display<vector<Prof>>(profs);
                }
                break;
            }
        case 3:
            {
                Direction d;
                d.setName("aaaaa");
                d.setService("Direction");
                d.setTitle("Doyenne");
                for(list<Etudiant>::iterator it = etudiants.begin(); it!= etudiants.end(); it++){
                    it->setMoyenne(d.calculateMoyenne(*it));
                }
                display<list<Etudiant>>(etudiants);
                break;        
            }
        case 4:
            {
                cout << "Quel est le nom du " << states[state] << " que vous cherchez ? ";
                string name;
                getline(cin, name);
                if(!state){
                    list<Etudiant>::iterator it = find_if(etudiants.begin(), etudiants.end(), [name](Etudiant e){return e.getName() == name;});
                    cout << (it != etudiants.end() ? "L'étudiant existe !": "L'étudiant n'existe pas !") << endl;
                }else{
                    vector<Prof>::iterator it = find_if(profs.begin(), profs.end(), [name](Prof e){return e.getName() == name;});
                    cout << (it != profs.end() ? "Le prof existe !": "Le prof n'existe pas !") << endl;

                }
                break;
            }
        case 5:
            if(!state){
                etudiants.sort();
                display<list<Etudiant>>(etudiants);
            }else{
                sort(profs.begin(), profs.end());
                display<vector<Prof>>(profs);
            }
            break;
        case 6:
            etudiants.sort(Etudiant::complexSort);
            display<list<Etudiant>>(etudiants);
            break;
        case 7:
            {
                cout << "Quel est le nom du fichier contenant les " << states[state] << "s ? ";
                string filename;
                cin >> filename;
                cin.ignore();
                if(!state){
                    readFile<Etudiant, list<Etudiant>>(etudiants, filename);
                    display<list<Etudiant>>(etudiants);
                }else{
                    readFile<Prof, vector<Prof>>(profs, filename);
                    display<vector<Prof>>(profs);
                }
                break;
            }
        case 8:
            loop = false;
            break;
        default:
            cout << "Veuillez entrer un nombre entre 0 et 8 ! ";
    }
}

//Methods
void displayMenu(string current_state){
    cout <<"Actuellement en train de travailler avec les " << current_state << "s." << endl;
    cout << "0. Inverse entre etudiant et prof" << endl;
    cout << "1. Saisie et afficher un tableau de " << current_state << endl;
    cout << "2. Supprimer un " << current_state << " à la position P" << endl;
    cout << "3. Doyen membre de Direction Calcule la Moyenne de chaque étudiant + Affichage" << endl;
    cout << "4. Chercher si un " << current_state << " existe" << endl; 
    cout << "5. Trier selon NOM par ordre croissant et afficher (" << current_state << ")" << endl;
    cout << "6. Afficher la liste des étudiants par année scolaire et par ordre décroissant de leur moyenne" << endl;
    cout << "7. Lire depuis un fichier (" << current_state << ")" << endl;
    cout << "8. Quitter" << endl;
}

template<typename Type, typename LV>
void addElement(LV &array, int index, Type element){
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
    for(int i = 0; i < amount; i++){
        Type t;
        t.saisie();
        addElement<Type, LV>(array, 0, t);
    }
}

template<typename LV>
void display(LV& array){
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
    array.erase(a);
}


template<typename Type, typename LV>
void readFile(LV &array, string filename){
    ifstream lecture;
    lecture.open(filename);
    if(lecture){
        int amount;
        lecture >> amount;
        lecture.ignore();
        for(int i =0; i < amount; i++){
            Type temp;
            lecture >> temp;
            array.push_back(temp);
        }
        lecture.close();
    }else{
        cout << "Le fichier " << filename << " n'existe pas ! " << endl;
    }
}

//Implémentation Personne
void Personne::saisie(){
    cout << "Veuillez renseigner le nom : ";
    getline(cin, this->name);
}

void Personne::affichage(){
    cout << className << ":\n\tId : " << this->id << "\n\tNom : " << this->name << endl; 
}

//Implémentations Prof
Prof::Prof(){
    this->className = "Prof";
}
Prof::~Prof(){
    //cout << "Le prof avec l'id : " << this->id << ", le nom : " << this->name << " et le service : "<< this->service << " a été détruit " << endl;
}

void Prof::saisie(){
    Personne::saisie();
    cout << "Veuillez renseigner le service : ";
    getline(cin, this->service);
}

void Prof::affichage(){
    Personne::affichage();
    cout << "\tService : " << this->service << "\n";
}

//Implémentation étudiant
Etudiant::Etudiant(){
    this->className = "Etudiant";
}
        
Etudiant::~Etudiant(){
    //cout << "L'etudiant avec l'id : " << this->id << " et le nom : " << this->name << " a été détruit " << endl;
}

void Etudiant::saisie(){
    Personne::saisie();
    cout << "Quelle est l'année scolaire : ";
    getline(cin, this->year);
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
    Personne::affichage();
    if(noteAmount)
        cout << "\tNotes : ";
        for(int i = 0; i < this->noteAmount; i++){
        cout << "Note " << (i+1) << " : " << notes[i];
    }
    cout << "\n";
    if(this->moyenne != -1){
        cout << "\tMoyenne : " << this->moyenne << "\n";
    }
}

Direction::Direction(){
    this->className = "Direction";
}

void Direction::saisie(){
    Prof::saisie();
    cout << "Veuillez renseigner le titre : ";
    getline(cin, this->title);
}

void Direction::affichage(){
    Prof::affichage();
    cout << "\tTitre : " << this->title << "\n";
}

float Direction::calculateMoyenne(Etudiant e){
    float m = 0;
    for(int i = 0; i < e.noteAmount; i++){
        m += e.notes[i];
    }
    m/=e.noteAmount;
    return e.noteAmount != 0 ? m : -1;
}

ostream & operator<<(ostream& stream, Personne &personne){
    return stream << personne.getClassName() << ":\n\tId : " << personne.getId() << "\n\tNom : " << personne.getName(); 
}

ostream & operator<<(ostream& stream, Prof &prof){
    Personne p = (Personne)prof;
    return stream << p << "\n\tService : " << prof.getService();
}

ostream & operator<<(ostream& stream, Etudiant& etudiant){
    Personne p = (Personne) etudiant;
    stream << p << "\n\tAnnée d'étude : " << etudiant.getYear();
    if(etudiant.noteAmount){
        stream << "\n\tNotes : ";
        for(int i = 0; i < etudiant.noteAmount; i++){
            stream << "\n\t\tNote " << (i+1) << " : " <<etudiant.notes[i];
        }
    }
    if(etudiant.getMoyenne() != -1){
        stream << "\n\tMoyenne : " << etudiant.getMoyenne();
    }
    return stream;
}

ifstream & operator>>(ifstream & stream, Prof& prof){
    string temp;
    getline(stream, temp, ';');
    prof.setName(temp);
    getline(stream, temp);
    prof.setService(temp);
    return stream;
}

ifstream & operator>>(ifstream& stream, Etudiant& etudiant){
    string temp;
    getline(stream, temp);
    istringstream tempStream(temp); //allows us to handle string with eof :)
    getline(tempStream, temp, ';');
    etudiant.setName(temp);
    if(tempStream.eof()){
        cout << "Missing school year for student : " << etudiant.getName() << endl;
        return stream;
    }
    getline(tempStream, temp, ';');
    etudiant.setYear(temp);
    int tempNote;
    while(!tempStream.eof()){
        tempStream>>tempNote;
        tempStream.ignore();
        etudiant.addNote(tempNote);
    }
    return stream;
}
