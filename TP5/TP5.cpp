
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<algorithm>
#include<map>

using namespace std;

class Country{
	string region;
	string name;
	float population;
	float area;
	public:

		string getRegion(){
			return this->region;
		}

		string getName(){
			return this->name;
		}
		float getPopulation(){
			return this->population;
		}
		float getArea(){
			return this->area;
		}
		string getKey(){
			return this->region;
		}
		void setRegion(string region){
			this->region = region;
		}
		void setName(string name){
			this->name = name;
		}
		void setPopulation(float population){
			this->population = population;
		}
		void setArea(float area){
			this->area = area;
		}

};

class Entreprise{
	string name;
	string countryName;
	float marketValue;
	string sector;
	float turnover;
	float employees;
	int rank_2015;
	int rank_2014;
	public:
		string getName(){
			return this->name;
		}
		string getCountryName(){
			return this->countryName;
		}
		float getMarketValue(){
			return this->marketValue;
		}

		string getSector(){
			return this->sector;
		}

		float getTurnover(){
			return this->turnover;
		}

		float getEmployees(){
			return this->employees;
		}

		int getRank2015(){
			return this->rank_2015;
		}

		int getRank2014(){
			return this->rank_2014;
		}

		string getKey(){
			return this->name;
		}

		void setName(string name){
			this->name = name;
		}

		void setCountryName(string countryName){
			this->countryName = countryName;
		}

		void setMarketValue(float marketValue){
			this->marketValue = marketValue;
		}

		void setSector(string sector){
			this->sector = sector;
		}

		void setTurnover(float turnover){
			this->turnover = turnover;
		}

		void setEmployees(float employees){
			this->employees = employees;
		}

		void setRank2015(int rank){
			this->rank_2015 = rank;
		}

		void setRank2014(int rank){
			this->rank_2014 = rank;
		}

};
template<typename T> 
void printElement(T t, const int& width, ostream& stream=cout)
{
	stream << left << setw(width) << t;
}

istream& operator>>(istream& stream, Entreprise& e){
	string tempString;
	float tempFloat;
	int tempInt;
	getline(stream, tempString, ';');
	e.setName(tempString);
	getline(stream, tempString, ';');
	e.setCountryName(tempString);
	stream >> tempFloat;
	stream.ignore();
	e.setMarketValue(tempFloat);
	getline(stream, tempString, ';');
	e.setSector(tempString);
	stream >> tempFloat;
	stream.ignore();
	e.setTurnover(tempFloat); 

	stream >> tempFloat;
	stream.ignore();

	e.setEmployees(tempFloat);
	stream >> tempInt;
	stream.ignore();
	e.setRank2015(tempInt);
	stream >> tempInt;
	stream.ignore();
	e.setRank2014(tempInt);

}

ostream& operator<<(ostream& stream, Entreprise& e){
	const int nameWidth = 40;
	const int numWidth = 15;
	printElement(e.getName(), nameWidth, stream);
	printElement(e.getCountryName(), numWidth, stream);
	printElement(e.getMarketValue(), numWidth, stream);
	printElement(e.getSector(), nameWidth, stream);
	printElement(e.getTurnover(), numWidth, stream);
	printElement(e.getEmployees(), numWidth, stream);
	printElement(e.getRank2015(), numWidth, stream);
	printElement(e.getRank2014(), numWidth, stream);
	return stream;
}


istream& operator>>(istream& stream, Country& c){
	string tempString;
	float tempFloat;

	getline(stream, tempString, ';');
	c.setRegion(tempString);
	getline(stream, tempString, ';');
	c.setName(tempString);
	stream >> tempFloat;
	c.setPopulation(tempFloat);
	stream.ignore();
	stream >> tempFloat;
	c.setArea(tempFloat);
	stream.ignore();
	return stream;
}

ostream& operator<<(ostream& stream, Country& c){
	stream.precision(10);
	const int nameWidth = 40;
	const int numWidth = 20;
	
	printElement(c.getRegion(), nameWidth, stream);
	printElement(c.getName(), nameWidth, stream);
	printElement(c.getPopulation(), numWidth, stream);
	printElement(c.getArea(), numWidth, stream);
	return stream;
}


template<typename Container, typename Type>
void readFile(Container& container, string filename);

template<typename Container>
void display(Container container);

void displayMenu();
void operations(map<string, Entreprise>& entreprises, multimap<string, Country>& countries, bool& loop);

//calculate and display the turnover per employees and return the entreprise with the best ratio
Entreprise turnOverPerEmployee(map<string, Entreprise> entreprises);

pair<Entreprise, Entreprise> calculateBestAndWorst(map<string, Entreprise> entreprises);


typedef map<string, Entreprise>::iterator MapIt;
typedef multimap<string, Country>::iterator MultiMapIt;


template<typename Container>
void displayAllElementWithKey(Container container, string searchedKey){
	typedef typename Container::iterator Cit;
	pair<Cit, Cit> beginEnd = container.equal_range(searchedKey);
	for(Cit cit=beginEnd.first; cit != beginEnd.second; cit++)
		cout << cit->second << endl;
}


int main(){
	map<string, Entreprise> entreprises;
	multimap<string, Country> countries;
	bool loop = true;
	//lighter to read, allows us to use states, ...
	while(loop){
		operations(entreprises, countries, loop);
	}	
	system("pause");
	return EXIT_SUCCESS;
}


void displayMenu(){
	cout << "Que voulez-vous faire ?" << endl
        << "1. Charger les donnees " << endl
        << "2. Afficher la map et la multimap " << endl
        << "3. Chercher une entreprise avec son nom " << endl
        << "4. Chercher l'entreprise avec la meilleure progression et l'entreprise avec la pus grosse chute" << endl
        << "5. Calculer le Turnover/Employee, le chiffre d'affaire moyen genere par employe et trouver la meilleur" << endl
		<< "6. Pour un region donnee afficher tout les pays dans cette region" << endl
		<< "6. Quitter" << endl;
}

void operations(map<string, Entreprise>& entreprises, multimap<string, Country>& countries, bool& loop){
	int choix;
	displayMenu();
	cin >> choix;
	cin.ignore();
	switch(choix){
		case 1:{
				string tempString;
				cout << "Veuillez entrer le nom du fichier pour les entreprises : ";
				getline(cin, tempString);
				readFile<map<string, Entreprise>, Entreprise>(entreprises, tempString);
				display(entreprises);
				cout << "Veuillez entrer le nom du fichier pour les pays : ";
				getline(cin, tempString);
				readFile<multimap<string, Country>, Country>(countries, tempString);
				display(countries);
				break;
			}	
		case 2:
			display(entreprises);
			display(countries);
			break;
		case 3:
			{
				string tempString;
				cout << "Quel est l'entreprise que vous cherchez ? ";
				getline(cin, tempString);
				displayAllElementWithKey(entreprises, tempString);
				break;
			}
		case 4:
			{
				pair<Entreprise, Entreprise> bestWorst = calculateBestAndWorst(entreprises);
				cout << "La meilleure progression : " << endl;
				cout << bestWorst.first << endl << endl;
				cout << "La pire chute : " << endl;
				cout << bestWorst.second << endl << endl;
				break;
			}
		case 5:
			turnOverPerEmployee(entreprises);
			break;
		case 6:
			{
				string tempString;
				cout << "Quel est la region ? ";
				getline(cin, tempString);
				displayAllElementWithKey(countries, tempString);
				break;
			}
		case 7:
			loop = false;
			break;
	}
}

Entreprise turnOverPerEmployee(map<string, Entreprise> entreprises){
	float (*calculateRatio)(MapIt) = [](MapIt it){return it->second.getTurnover()/(it->second.getEmployees());};
	MapIt best = entreprises.begin();
	float bestRatio = calculateRatio(best);
	for(MapIt it= ++entreprises.begin(); it!= entreprises.end(); it++){
		float currentRatio = calculateRatio(it);
		if(currentRatio > bestRatio){
			best = it;
			bestRatio = currentRatio;
		}
		cout << it->second << setw(8) << currentRatio << endl;
	}
	cout << endl << endl << "La meilleur entreprise :" << endl;
	cout << best->second << setw(8) << bestRatio << endl;
	return best->second;
}

pair<Entreprise, Entreprise> calculateBestAndWorst(map<string, Entreprise> entreprises){
	int (*getter)(MapIt it) = [](MapIt it){return it->second.getRank2015() - it->second.getRank2014();};
	MapIt best = entreprises.begin();
	int bestInt = getter(best);
	MapIt worst = entreprises.begin();
	int worstInt = bestInt; //initial value is the same as best
	for(MapIt it=++entreprises.begin(); it!= entreprises.end(); it++){
		int current = getter(it);
		if(current > bestInt){
			best = it;
			bestInt = current;
		}else if(current < worstInt){
			worst = it;
			worstInt = current;
		}
	}
	return make_pair(best->second, worst->second);
}


template<typename Container, typename Type>
void readFile(Container& container, string filename){
	ifstream reading(filename);
	if(reading){
		while(!reading.eof()){
			Type blank;
			reading >> blank;
			container.insert(make_pair(blank.getKey(), blank));
		}
	}else{
		cout << "Wrong filename " << endl;
	}
	reading.close();
}
template<typename Container>
void display(Container container){
	for(auto it=container.begin(); it != container.end(); it++)
		cout << it->second << endl;
}