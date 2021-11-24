#include<iostream>
#include<string>
#include<iomanip>
#include<algorithm>
#include<fstream>
#include<list>
#include<vector>
using namespace std;


class Runner{
    char id;
    string name;
    public:
        Runner(char id='?', string name="?");
        char getId(){
            return this->id;
        }
        string getName(){
            return this->name;
        }
        void setId(char id){
            this->id = id;
        }
        void setName(string name){
            this->name = name;
        }
        bool operator<(Runner r){
            return this->id < r.id;
        }
};


ifstream & operator >> (ifstream & stream, Runner & runner){
    char id;
    string name;
    stream >> id;
    stream.ignore();
    getline(stream, name);

    runner.setId(id);
    runner.setName(name);
    return stream;
}


template<class LV, class Type>
void readFile(LV&, string);

template<class LV>
void affichage(LV);

void echange(list<Runner>& list, vector<Runner>& vector);

void operations(list<Runner>&, vector<Runner>&, bool&, list<Runner>&);

void displayMenu();

void fastPrint(list<Runner> list, vector<Runner> vector);

void readBothFile(list<Runner>& listR, vector<Runner>& vectorR);

void fusion(list<Runner>& listR, vector<Runner>& vectorR, list<Runner>& result);


int main(){
    list<Runner> listR;
    vector<Runner> vectorR;
    list<Runner> fusionList;
    bool loop = true;
    do{
        operations(listR, vectorR, loop, fusionList);
    }while(loop);
    return EXIT_SUCCESS;
}

void displayMenu(){
    cout << "Que voulez vous faire ? " << endl;
    cout << "1. Lire le vecteur et la liste dans un fichier" << endl;
    cout << "2. Echanger le contenu de la liste et du vecteur" << endl;
    cout << "3. Tri par id " << endl;
    cout << "4. Fusionner la liste et le vecteur" << endl;
    cout << "5. Afficher la liste et le vecteur" << endl;
    cout << "6. Quitter" << endl;

}

void fastPrint(list<Runner> list, vector<Runner> vector){
    cout << "Contenu de la liste : " << endl;
    affichage(list);
    cout << "Contenu du vecteur : " << endl;
    affichage(vector);
}

void readBothFile(list<Runner>& listR, vector<Runner>& vectorR){
    readFile<list<Runner>, Runner>(listR, "L.txt");
    readFile<vector<Runner>, Runner>(vectorR, "V.txt");
}

void fusion(list<Runner>& listR, vector<Runner>& vectorR, list<Runner>& result){
    auto listIt = listR.begin();
    auto vectorIt = vectorR.begin();
    while(listIt != listR.end() || vectorIt != vectorR.end()){
        if(listIt == listR.end()){
            result.push_back(*(vectorIt++));
        }else if (vectorIt == vectorR.end()){
            result.push_back(*(listIt++));
        }else if(listIt->getId() < vectorIt->getId()){
            result.push_back(*(listIt++));
        }else{
            result.push_back(*(vectorIt++));
        }
    }
}

void operations(list<Runner>& listR, vector<Runner>& vectorR, bool& loop, list<Runner>& fusionResult){
    displayMenu();
    int choix;
    cin >> choix;
    switch(choix){
        case 1:
            readBothFile(listR, vectorR);
            fastPrint(listR, vectorR);
            break;
        case 2:
            cout << "Echange du contenu du vecteur avec le contenu de la liste " << endl;
            echange(listR, vectorR);
            fastPrint(listR, vectorR);
            break;
        case 3:
            listR.sort();
            sort(vectorR.begin(), vectorR.end());
            fastPrint(listR, vectorR);
            break;
        case 4:
            fusion(listR, vectorR, fusionResult);
            affichage(fusionResult);
            break;
        case 5:
            fastPrint(listR, vectorR);
            break;
        case 6:
            cout << "Au revoir ! " << endl;
            loop = false;
            break;
        default:
            cout << "Veuillez entrer une opération valide !" << endl;
    }
}

template<class LV, class Type>
void readFile(LV& array, string filename){
    ifstream input(filename);
    if(input){
        int amount;
        input >> amount;
        for(int i = 0; i < amount; i++){
            Type r;
            input >> r;
            /*char c;
            input >> c;
            input.ignore();
            string name;
            getline(input, name);
            r.setName(name);
            r.setId(c);*/
            array.push_back(r);
        }
    }else{
        cout << "Le fichier n'existe pas !" << endl;
    }
}

template<class LV>
void affichage(LV array){
    for(auto a : array){
        cout << a << endl;
    }
}


Runner::Runner(char id, string name){
    this->id = id;
    this->name = name;
}

void echange(list<Runner>& list, vector<Runner>& vector){
    int listsize = list.size();
    int vectorsize = vector.size();

    for(int i = 0; i < vectorsize; i++){
        list.push_back(vector[i]); //à la fin de la liste on ajoute le premier element du vecteur 
    }
    vector.clear();

    for(int i = 0; i < listsize; i++){
        vector.push_back(*(list.begin()));
        list.erase(list.begin());
    }
}

ostream & operator<<(ostream& stream, Runner& runner){
    return stream << left << setw(2) << runner.getId()<< setw(20) << runner.getName(); 
}
