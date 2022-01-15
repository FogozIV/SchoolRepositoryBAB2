#include<iostream>
#include<string>
#include<iomanip>
#include<algorithm>
#include<list>
#include<fstream>

using namespace std;


class DummyClass{
    string name;
    list<string> ingredients;
    public:
        void addIngredient(string ingredient){
            this->ingredients.insert(this->ingredients.begin(), ingredient);
        }

        ifstream& readFile(ifstream& stream);
        ostream& display(ostream& stream=cout);
};

template<template<class, class> class Container, class Type, class U>
void readFile(Container<Type, U>&, string, bool=true);


ostream& operator<<(ostream& stream, DummyClass d){
    return d.display(stream);
}
template<class Container>
void display(Container c){
    for(auto a : c){
        cout << a;
    }
}

int main(){
    list<DummyClass> dc;
    readFile(dc, "PIZZA_2.txt");
    display(dc);
    system("pause");
    return EXIT_SUCCESS;
}

template<template<class, class> class Container, class Type, class U>
void readFile(Container<Type, U>& c, string filename, bool end){
    ifstream stream(filename);
    if(stream){
        int sizeI;
        stream >> sizeI;
        stream.ignore();
        for(int i = 0; i < sizeI; i++){
            Type t;
            t.readFile(stream);
            c.insert(end ? c.end() : c.begin(), t);
        }
    }else{
        cout << "Mauvais fichier" << endl;
    }
}


ifstream& DummyClass::readFile(ifstream& stream){
    string tempS;
    int tempI;
    getline(stream, this->name, ';');
    stream >> tempI;
    stream.ignore();
    for(int i =0; i < tempI; i++){
        getline(stream, tempS, ';');
        addIngredient(tempS);
    }
    stream.ignore();
}


ostream& DummyClass::display(ostream& stream){
    cout << "Nom : " << this->name << endl;
    for(auto a : ingredients){
        cout << "Ingredient : " << a << endl;
    }
}
