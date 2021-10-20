#include<iostream>
#include<string>
#include<iomanip>
#include<algorithm>

using namespace std;

struct Etudiant{
    private:
        static int currentId;
        int Id;
        string nom;
    public:
        Etudiant();
        void affiche();
        void saisie();
        string getName(){
            return nom;
        }
        int getId(){
            return Id;
        }
};

class Prof{
    private:
        static int currentId;
        int Id;
        string nom;
    public:
        Prof();
        ~Prof();
        void saisie();
        void affiche();
        string getName(){
            return nom;
        }
        int getId(){
            return Id;
        }
};


template<typename T>
void addElement(T** &array, int &N, int index, T* element);

template<typename T>
void gestion(T** &array, int& N, string current_type);

template<typename T>
void display(T** array, int N);

void displayMenu(string current_type);

template<typename T>
void deleteElement(T** &array, int& N, int index);


template<typename T>
void addElement(T** &array, int &N, string current_type);

template<typename T>
void getNameFromId(T** array, int N, string current_type);

int main(){
    Prof** profs = (Prof**)malloc(sizeof(Prof*));
    Etudiant** etudiants = (Etudiant**)malloc(sizeof(Etudiant*));
    int NProf = 0, NEtudiant = 0;
    bool loop = true;
    char c;
    do{
        cout << "Que voulez vous faire ? " << endl;
        cout << "Gérer les (E)tudiant ou les (p)rofs ou (q)uitter" << endl;
        cin >> c;
        cin.ignore();
        switch(tolower(c)){
            case 'e':
                gestion(etudiants, NEtudiant, "etudiant");
                break;
            case 'p':
                gestion(profs, NProf, "prof");
                break;
            case 'q':
                loop = false;
                break;
            default:
                cout << "Veuillez entrer soit e,p,q" << endl;
        }
    }while(loop);
    cout << "Au revoir" << endl;
    return EXIT_SUCCESS;
}


/*declare everything for class Prof*/

//Id that will get incremented each time a new Object is created
int Prof::currentId = 1;

Prof::~Prof(){
    cout<< "Une instance de l'objet prof vient d'être détruite : " << endl;
    cout << "Nom du prof : " << this->nom << endl;
    cout << "Id du prof : " << this->Id << endl;
}

Prof::Prof(){
    this->Id = currentId;
    this->currentId++;
}

void Prof::saisie(){
    cout << "Veuillez renseigner le nom du prof : " <<endl;
    string value;
    getline(cin, value);
    this->nom = value;
}

void Prof::affiche(){
    cout << "Prof :\n\tId : " << this->Id << "\n\tNom : " << this->nom << endl;
}


//declare everything for struct Etudiant
//

int Etudiant::currentId = 1;

Etudiant::Etudiant(){
    this->Id = currentId;
    this->currentId++;
    cout << "New etudiant" << endl;
}

void Etudiant::saisie(){
    cout << "Veuillez entrer le nom de l'etudiant : " << endl;
    string value;
    getline(cin, value);
    this->nom = value;
}

void Etudiant::affiche(){
    cout << "Etudiant :\n\tId : " << this->Id << "\n\tNom : " << this->nom << endl;
}


//autres fonctions
template<typename T>
void gestion(T** &array, int &N, string current_type){
    int choix;
    bool loop;
    do{
        loop = false;
        displayMenu(current_type);
        cin >> choix;
        cin.ignore();
        switch(choix){
            case 1:
                addElement(array, N, current_type);
                display(array, N);
                break;
            case 2:
                deleteElement(array, N, 0);
                display(array, N);
                break;
            case 3:
                getNameFromId(array, N, current_type);
                break;
            case 4:
                cout << current_type << " : location : " << array[0] << '\n' << "Is in the array at starting index " << &(array[0]) << " and end index " << &(array[N])  << endl; 
                sort(&(array[0]), &(array[N]), [](T* a, T* b){return a->getName() < b->getName();});
                display(array, N);
                break;
            default:
                loop = true;
                break;
        }

    }while(loop);
}

template<typename T>
void display(T** array, int N){
    for(int i = 0; i < N; i++)
        array[i]->affiche();
}

template<typename T>
void deleteElement(T** &array, int &N, int index){
    if(index >= N || index < 0)
        return;
    delete array[index];
    for(int i = index; i < N - 1; i++){
        array[i] = array[i+1];
    }
    N--;
    array = (T**)realloc(array, sizeof(T*) * N);
}


template<typename T>
void addElement(T** &array, int &N, int index, T* element){
    array = (T**)realloc(array, (N+1)*sizeof(T*));
    for(int i = N; i > index; i--){
        array[i] = array[i-1];
    }
    array[index] = element;
    N++;
}

template<typename T>
void addElement(T** &array, int &N, string current_type){
    bool loop;
    char c;
    T* t = new T();
    t->saisie();
    do{
        loop = false;
        cout << "Ou voulez vous ajouter un " << current_type << "(D)ébut ou (f)in" <<endl;
        cin >> c;
        cin.ignore();
        switch(tolower(c)){
            case 'd':
                addElement(array, N, 0, t);
                break;
            case 'f':
                addElement(array, N, N, t);
                break;
            default:
                cout << "Veuillez entrer un d ou un f" <<endl;
                loop = true;
                break;
        }
    }while(loop);
}

void displayMenu(string current_type){
    cout << "Que voulez vous faire ? " << endl;
    cout << "1. Ajoutez au (début ou fin) et Affichage de tous les " << current_type << "s" << endl;;
    cout << "2. Supprimer le début et affichage du tableau" << endl;
    cout << "3. Chercher un " << current_type << " selon son Id" << endl;
    cout << "4. Tri selon NOM et Affichage du tableau" << endl;
}


template<typename T>
void getNameFromId(T** array, int N, string current_type){
    cout << "Quel est l'id de " << current_type << " que vous recherchez ? " << endl;
    int id;
    cin >> id;
    cin.ignore();
    for(int i = 0; i < N; i++){
        if(array[i]->getId() == id){
            cout << "Le nom de " << current_type << " que vous cherchez est : " << array[i]->getName() << endl;
            return;
        }
    }
    cout << "Impossible de trouve un " << current_type << " avec cet id " << endl;
}

