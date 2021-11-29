#include<iostream>
#include<string>
#include<iomanip>
#include<algorithm>
#include<map>
#include<fstream>

using namespace std;

void loadFile(map<string, int>&, string);

int main(){
    map<string, int> occurences;    
    loadFile(occurences, "pg100_small.txt");
    cout << "Taille de la Map : " << occurences.size() << endl;
    bool loop = true;
    do{
        string word;
        cout << "Quel est le mot que vous cherchez (q8 pour quitter) ? ";
        cin >> word;
        if(word == "q8"){
            break;
        }
        for_each(word.begin(), word.end(), [](char &c){c = tolower(c);});
        
        map<string, int>::iterator it = occurences.begin();
        for(; it != occurences.end(); it++){
            int found = it->first.rfind(word);
            if(found != -1){
                cout << it->first << "-->" << it->second << endl;
            }
        }
    }while(loop);
    return EXIT_SUCCESS;
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
        input.close();
    }else{
        cout << "Fichier non trouvé ! ";
    }
}
