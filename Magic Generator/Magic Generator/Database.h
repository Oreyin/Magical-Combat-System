#pragma once
#include "sqlite3.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Spell
{
	int power;
	string name;
	int effect = 0; // 1=attack 2=armor 3=heal 4=attack
};

class Database
{
public:
	sqlite3 * db;
	string filepath;

	vector<string> types{ "Air", "Fire", "Water", "Earth", "Sound", "Ice", "Electricity", "Chaos", "Light", "Dragon", "Psi", "Code" };
	vector<string> foci{ "Destruction", "Protection", "Healing", "Minion" };
	vector<string> catali{ "Coal Dust", "Fairy Tears", "Nightshade", "Bone Meal", "Soylent" };

	Database(string filepath = "C:\\")
	{
		filepath += "\\Spells.db";
		int StatofOpen = sqlite3_open(filepath.c_str(), &db);
		if (StatofOpen == SQLITE_OK)
		{
			cout << "--#Database is running fine#--" << endl;
			PopulateDB();
		}
		else
		{
			cout << "--#Failed to initialize game files >< Exiting#--" << endl;
		}
	}

	~Database()
	{
		remove(filepath.c_str());
	}

	void SelectTypes();
	void SelectFoci();
	void SelectCatali();
	double GetWLR();
	Spell SelectSpell(int type, int focus, int catalyst);
	void InsertWin();
	void InsertLoss();

private:
	void CreateWLRTable();
	void CreateTypesTable();
	void CreateFociTable();
	void CreateCataliTable();
	void InsertTypeData(string data);
	void InsertFocusData(string data);
	void InsertCatalystData(string data);
	void CreateSpellTable();
	void InsertSpellData(string name, int power, int type, int focus, int catalyst);
	void PopulateDB();
};