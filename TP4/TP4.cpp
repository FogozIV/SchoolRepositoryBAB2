#include<iostream>
#include<string>
#include<iomanip>
#include<algorithm>
#include<map>
#include<fstream>

using namespace std;

void loadFile(map<string, int>&, string);

void operations(map<string, int>&, bool&);

void displayMenu();

int main(){
    map<string, int> occurences;
    bool loop = true;
    do{
        operations(occurences, loop);
    }while(loop);
    return EXIT_SUCCESS;
}

void displayMenu(){
    cout << "1. Lire fichier" << endl;
    cout << "2. Afficher le taille" << endl;
    cout << "3. Nombre d'occurence d'un mot" << endl;
    cout << "4. Chercher le mot le plus reccurent" << endl;
    cout << "5. Chercher les occurences des mots de la meme famille " << endl;   
    cout << "6. Quiiter" << endl;
}

void operations(map<string, int>& occurences, bool& loop){
    cout << "Que voulez vous faire ?" << endl;
    displayMenu();
    int choice;
    cin >> choice;
    switch(choice){
        case 1:
            {
                string filename;
                cout << "Quel est le nom du fichier ? ";
                cin >> filename;
                loadFile(occurences, filename);
                break;
            }
        case 2:
            cout << "Il y a " << occurences.size() << " mots dans le fichier" << endl;
            break;
        case 3:
            {
                string word;
                cout << "Quel est le mot que vous cherchez ? ";
                cin >> word;
                int amount = occurences[word];
                if(amount){
                    cout << word << "-->" << amount << endl;
                }
                break;
            }
        case 4:
            {
                string word = occurences.begin()->first;
                int number = occurences.begin()->second;
                for_each(++(occurences.begin()), occurences.end(), [&word, &number](pair<string, int> a){
                    if(number < a.second){
                        word = a.first;
                        number = a.second;
                    }
                });
                cout << word << "-->" << number << endl;
                break;
            }
        case 5:
            {
                string word;
                cout << "Quel est le mot que vous cherchez ? ";
                cin >> word;
                for_each(word.begin(), word.end(), [](char &c){c = tolower(c);});
                map<string, int>::iterator it = occurences.begin();
                for(; it != occurences.end(); it++){
                    int found = it->first.rfind(word);
                    if(found != -1){
                        cout << it->first << "-->" << it->second << endl;
                    }
                }
                break;
            }
        case 6:
            loop = false;
            break;
        default:
            cout << "Veuillez entrer une opérations une operations valide" << endl;
    }
}


void loadFile(map<string, int>& occurences, string filename){
    ifstream input(filename);
    if(input){
        string word;
        int count = 0;
        while(!input.eof()){
            count++;
            input >> word;
            for_each(word.begin(), word.end(), [](char& c){c = tolower(c);});
            occurences[word]++;
            if(!(count % 1000))
                cout << count << "...."; 
        }
        cout << endl;
        input.close();
    }else{
        cout << "Fichier non trouvé ! ";
    }
}
