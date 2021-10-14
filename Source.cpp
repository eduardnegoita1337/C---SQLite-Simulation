//IdComanda identifica tipul de comanda introdus
//clasa Tabela are toate atributele unei tabele
//clasa Coloana are ca atribute int nrColoane, string denumire, tipDate(int char float; ma gandeam sa fie enum) , int dimensiune, defaultValue 

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>



using namespace std;


class Coloana
{
private:
	char* denumireColoana;
	char* dimensiune;
	char* tipDate;
	char* defaultValue;
	
public:
	
	Coloana() {
		this->denumireColoana = new char[25];
		this->dimensiune = new char[25];
		this->tipDate = new char[25];
		this->defaultValue = new char[25];
	}
	~Coloana() {
		if(this->dimensiune!=NULL)
			delete this->dimensiune;
		if (this->defaultValue != NULL)
			delete this->defaultValue;
		if (this->tipDate!= NULL)
			delete this->tipDate;
		if (this->denumireColoana != NULL)
			delete this->denumireColoana;
	}
	char* getTip(){
		return this->tipDate;
	}
	char* getDenumire() {
		return this->denumireColoana;
	}
	char* getDimensiune() {
		return this->dimensiune;
	}
	void setDimensiune(char* d) {
		if (this->dimensiune != NULL)
			delete this->dimensiune;
		this->dimensiune= new char[(strlen(d)) + 1];
		strcpy(this->dimensiune, d);
	}
	char* getDefaultValue() {
		return this->defaultValue;
	}
	void setDenumire(char* name)  {
		if (this->denumireColoana != NULL)
			delete this->denumireColoana;
		this->denumireColoana = new char[(strlen(name)) + 1];
		strcpy(this->denumireColoana, name);
	
	}
	void setTip(char* name)
	{
		if (this->tipDate != NULL)
			delete this->tipDate;
		this->tipDate = new char[(strlen(name)) + 1];
		strcpy(this->tipDate, name);
		
	}
	void setDefaultValue(char* name) {
		if (this->defaultValue != NULL)
			delete this->defaultValue;
		this->defaultValue = new char[(strlen(name)) + 1];
		strcpy(this->defaultValue, name);
	}
	Coloana& operator=(const Coloana& c) {
		if (this->denumireColoana != NULL)
			delete this->denumireColoana;
		this->denumireColoana = new char[25];
		strcpy(this->denumireColoana, c.denumireColoana);
		if (this->defaultValue != NULL)
			delete this->defaultValue;
		this->defaultValue = new char[25];
		strcpy(this->defaultValue, c.defaultValue);
		if (this->tipDate != NULL)
			delete this->tipDate;
		this->tipDate = new char[25];
		strcpy(this->tipDate, c.tipDate);
		if (this->dimensiune != NULL)
			delete this->dimensiune;
		this->dimensiune = new char[25];
		strcpy(this->dimensiune, c.dimensiune);
		return *this;
	}
};
class Tabela
{
private:
	string nume;
	static int nrTabele;
	const int IDTabela;
	int nrColoane;
	Coloana coloane[5];
public:
	Tabela(char comanda[]):IDTabela(nrTabele+1) { 
		nrTabele++;
		char comandaCpy[100];
		strcpy(comandaCpy, comanda);
		char* name;
		char sep[] = " ";
		name = strtok(comandaCpy, sep);
		int i = 1;
		while (name && i<3)
		{
			name = strtok(NULL, sep);
			i++;
		}
		this->nume = name; 
		this->nrColoane = 0;
		char sep2[] = " ,()";  
		name = strtok(NULL, sep2);
		while (name) {
			this->nrColoane++;
			this->coloane[nrColoane].setDenumire(name);
			name = strtok(NULL, sep2);
			this->coloane[nrColoane].setTip(name);
			name = strtok(NULL, sep2);
			this->coloane[nrColoane].setDimensiune(name);
			name = strtok(NULL, sep2);
			this->coloane[nrColoane].setDefaultValue(name);
			name = strtok(NULL, sep2);
			if (name == NULL)
				break;
		}
		delete name;
	}
	Tabela& operator=(const Tabela& t)
	{
		this->nume = t.nume;
		this->nrColoane = t.nrColoane;
		for (int i = 1; i <= this->nrColoane; i++)
			this->coloane[i] = t.coloane[i];
		return *this;
	}

	~Tabela() {

	}
	void afisare()
	{
		for (int i = 1; i <= this->nrColoane; i++)
		{	
			cout << "Denumire: " << this->coloane[i].getDenumire() << endl;
			cout << "Dimensiune: " << this->coloane[i].getDimensiune() << endl;
			cout << "Tip date: " << this->coloane[i].getTip() << endl;
			cout << "Default value: " << this->coloane[i].getDefaultValue() << endl;
		}
	}
	Tabela() :IDTabela(nrTabele+1){
	}
	void inserare(char comanda[], char* numeTabela) // se insereaza date intr-un fisier
	{
		char comandaCpy[100];
		char* name;
		char sep[] = " ,()";
		char* nume;
		nume = strcat(numeTabela, ".bin");
		strcpy(comandaCpy, comanda);
		name = strtok(comandaCpy, sep);
		name = strtok(NULL, sep);
		name = strtok(NULL, sep);
		strcpy(numeTabela, name);
		name = strtok(NULL, sep);
		FILE* f;
		f = fopen(nume, "wb+");
		while (name) {
			
			name = strtok(NULL, sep);
			if (name == NULL)
				break;
			fwrite(&name,sizeof(char*),5,f);
		}
		fclose(f);

		cout << "Rows inserted" << endl;
		delete name;
	}
	string getNumeTabela() {
		return this->nume;
	}
	int getNrColoane() {
		return this->nrColoane;
	}
	
};
int Tabela::nrTabele = 0;

class Controller {
private:
	Tabela tabel[5];
	static int numarTabele;
	string tableNames[5];
public:
	void IdComanda(char comanda[])
	{
		char cpyComanda[100];
		strcpy(cpyComanda, comanda);
		char* firstWord;
		char* secondWord;
		char* tableName;
		char* thirdWord;
		char sep[] = " ,()";
		firstWord = strtok(cpyComanda, sep);
		secondWord = strtok(NULL, sep);
		tableName = strtok(NULL, sep);
		thirdWord = strtok(NULL, sep);
		if(strcmp("CREATE", firstWord) == 0 && strcmp("TABLE", secondWord) == 0)
			for(int i=1;i<=this->numarTabele;i++)
				if (tableName == this->tableNames[i]) {
					cout << "Tabela " << tableName << " exista deja." << endl;
					return;
				}
		if (strcmp("CREATE", firstWord) == 0 && strcmp("TABLE", secondWord) == 0) {
			this->numarTabele++;
			this->tabel[numarTabele] = Tabela(comanda);
			ofstream g("structuraTabele.txt", std::ios::app);
			//scriem in g cate coloane are tabela noastra si numele acesteia
			g << this->tabel[numarTabele].getNumeTabela() << ": ";
			g << this->tabel[numarTabele].getNrColoane();
			g << endl;
			g.close();
			this->tableNames[numarTabele] = tableName;
			cout << "Table " << this->tableNames[numarTabele] << " created." << endl;
		}
		else if (strcmp("DROP", firstWord) == 0 && strcmp("TABLE", secondWord) == 0) {
			bool gasit = false;
			for (int i = 1; i <= this->numarTabele; i++) {
				if (this->tableNames[i] == tableName)
				{
					gasit = true;
					cout << "Table " << tableName << " dropped." << endl;
					for (int j = i; j < this->numarTabele; j++)
						this->tabel[j] = this->tabel[j + 1];
					this->numarTabele--;
				}
			}
			if (gasit == false) cout << "Tabela " << tableName << " nu exista." << endl;
		}
		else if (strcmp("DISPLAY", firstWord) == 0 && strcmp("TABLE", secondWord) == 0) {
			for (int i = 1; i <= this->numarTabele; i++) {
				if (strcmp(this->tableNames[i].c_str(), tableName)==0)
				{
					this->tabel[i].afisare();
				}

			}
		}
		else if (strcmp("INSERT", firstWord) == 0 && strcmp("INTO", secondWord) == 0 && strcmp("VALUES", thirdWord) == 0) {
			bool gasit = false;
			for (int i = 1; i <= this->numarTabele; i++)
			{
				if (this->tableNames[i] == tableName) {
					gasit = true;
					this->tabel[i].inserare(comanda,tableName);
				}
			}
			if (gasit == false) cout << "Tabela " << tableName << " nu exista." << endl;
		}
		else cout << "Comanda trebuie sa fie de tipul CREATE TABLE, DROP TABLE, DISPLAY TABLE, INSERT INTO table_name VALUES";
			
	}
		Controller() {
			
		}
		~Controller() {
			
		}
};
int Controller::numarTabele = 0;

int main()
{
	cout << "------------------------------------------------------------------------" << endl;
	cout << "Bun venit la baza de date SQLite!" << endl;
	cout << "Comenzile acceptate sunt: CREATE, DROP, DISPLAY, INSERT" << endl;
	cout << "Sintaxe comenzi: ";
	cout << "-create: CREATE TABLE nume_tabel ((nume_coloana_1, tip, dimensiune, valoare_implicita)," << endl<<" (nume_coloana_2, tip, dimensiune, valoare_implicita), ...)" << endl;
	cout << "-drop: DROP TABLE nume_tabel" << endl;
	cout << "-display: DISPLAY TABLE nume_tabel" << endl;
	cout << "-insert: INSERT INTO nume_tabel VALUES(...); valorile se introduc in ordinea coloanelor date prin CREATE" << endl;
	cout << "------------------------------------------------------------------------" << endl;
	cout << endl << endl;
	/*
		cout << "Dati comanda: ";
		char comanda[100];
		cin.getline(comanda, 100);*/
		Controller controller;
		/*controller.IdComanda(comanda);
		cout << endl;*/
		ifstream ifs("comanda.txt");
		string cmdd;
		char cmd[100];
		while (getline(ifs, cmdd)) {
			strcpy(cmd, cmdd.c_str());
			controller.IdComanda(cmd);
		}
		ifs.close();
		return 0;
}