#include "Database.h"
#include "sqlite3.h"

void Database::CreateTypesTable()
{
	sqlite3_stmt * MyStatement;
	string sql = "CREATE TABLE IF NOT EXISTS Types (typeid INTEGER PRIMARY KEY, name TEXT)";

	int statusofprep = sqlite3_prepare_v2(db, sql.c_str(), -1, &MyStatement, NULL);

	if (statusofprep == SQLITE_OK)
	{

		int statusofstep = sqlite3_step(MyStatement);

		sqlite3_finalize(MyStatement);
	}
	else
	{
		cout << "Failed prep (Type table)" << endl;
	}
}

void Database::CreateFociTable()
{
	sqlite3_stmt * MyStatement;
	string sql = "CREATE TABLE IF NOT EXISTS Foci (focusid INTEGER PRIMARY KEY, name TEXT)";

	int statusofprep = sqlite3_prepare_v2(db, sql.c_str(), -1, &MyStatement, NULL);

	if (statusofprep == SQLITE_OK)
	{

		int statusofstep = sqlite3_step(MyStatement);

		sqlite3_finalize(MyStatement);
	}
	else
	{
		cout << "Failed prep (Focus Table)" << endl;
	}
}

void Database::CreateCataliTable()
{
	sqlite3_stmt * MyStatement;
	string sql = "CREATE TABLE IF NOT EXISTS Catali (catalystid INTEGER PRIMARY KEY, name TEXT)";

	int statusofprep = sqlite3_prepare_v2(db, sql.c_str(), -1, &MyStatement, NULL);

	if (statusofprep == SQLITE_OK)
	{

		int statusofstep = sqlite3_step(MyStatement);

		sqlite3_finalize(MyStatement);
	}
	else
	{
		cout << "Failed prep (Catalyst Table)" << endl;
	}
}

void Database::CreateWLRTable()
{
	sqlite3_stmt * MyStatement;
	string sql = "CREATE TABLE IF NOT EXISTS WLR (id INTEGER PRIMARY KEY, win INTEGER)";

	int statusofprep = sqlite3_prepare_v2(db, sql.c_str(), -1, &MyStatement, NULL);

	if (statusofprep == SQLITE_OK)
	{

		int statusofstep = sqlite3_step(MyStatement);

		sqlite3_finalize(MyStatement);
	}
	else
	{
		cout << "Failed prep (WLR Table)" << endl;
	}
}

void Database::InsertWin()
{
	sqlite3_stmt * MyStatement;
	string sql = "INSERT INTO WLR (win) VALUES (1)";

	int statusofprep = sqlite3_prepare_v2(db, sql.c_str(), -1, &MyStatement, NULL);

	if (statusofprep == SQLITE_OK)
	{

		int statusofstep = sqlite3_step(MyStatement);

		sqlite3_finalize(MyStatement);
	}
	else
	{
		cout << "Failed prep (Spell Data)" << endl;
	}
}

void Database::InsertLoss()
{
	sqlite3_stmt * MyStatement;
	string sql = "INSERT INTO WLR (win) VALUES (0)";

	int statusofprep = sqlite3_prepare_v2(db, sql.c_str(), -1, &MyStatement, NULL);

	if (statusofprep == SQLITE_OK)
	{

		int statusofstep = sqlite3_step(MyStatement);

		sqlite3_finalize(MyStatement);
	}
	else
	{
		cout << "Failed prep (Spell Data)" << endl;
	}
}

double Database::GetWLR()
{
	double retval = 0;
	sqlite3_stmt * MyStatement;
	string sql = "WITH Wins AS(SELECT COUNT(*) AS numwin FROM WLR WHERE WLR.win = 1), Losses AS(SELECT COUNT(*) AS numlos FROM WLR WHERE WLR.win = 0) SELECT(Wins.numwin / Losses.numlos) FROM Wins, Losses";

	int statusofprep = sqlite3_prepare_v2(db, sql.c_str(), -1, &MyStatement, NULL);

	if (statusofprep == SQLITE_OK)
	{

		int statusofstep = sqlite3_step(MyStatement);

		while (statusofstep == SQLITE_ROW)
		{
			retval = sqlite3_column_double(MyStatement, 0);

			statusofstep = sqlite3_step(MyStatement);
		}

		sqlite3_finalize(MyStatement);
	}
	return retval;
}

void Database::InsertTypeData(string data)
{
	sqlite3_stmt * MyStatement;
	string sql = "INSERT INTO Types (name) VALUES (?)";

	int statusofprep = sqlite3_prepare_v2(db, sql.c_str(), -1, &MyStatement, NULL);

	if (statusofprep == SQLITE_OK)
	{
		sqlite3_bind_text(MyStatement, 1, data.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(MyStatement, 2, data.c_str(), -1, SQLITE_STATIC);

		int statusofstep = sqlite3_step(MyStatement);

		sqlite3_finalize(MyStatement);
	}
	else
	{
		cout << "Failed prep (Type data)" << endl;
	}
}

void Database::InsertFocusData(string data)
{
	sqlite3_stmt * MyStatement;
	string sql = "INSERT INTO Foci (name) VALUES (?)";

	int statusofprep = sqlite3_prepare_v2(db, sql.c_str(), -1, &MyStatement, NULL);

	if (statusofprep == SQLITE_OK)
	{
		sqlite3_bind_text(MyStatement, 1, data.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(MyStatement, 2, data.c_str(), -1, SQLITE_STATIC);

		int statusofstep = sqlite3_step(MyStatement);

		sqlite3_finalize(MyStatement);
	}
	else
	{
		cout << "Failed prep (Focus data)" << endl;
	}
}

void Database::InsertCatalystData(string data)
{
	sqlite3_stmt * MyStatement;
	string sql = "INSERT INTO Catali (name) VALUES (?)";

	int statusofprep = sqlite3_prepare_v2(db, sql.c_str(), -1, &MyStatement, NULL);

	if (statusofprep == SQLITE_OK)
	{
		sqlite3_bind_text(MyStatement, 1, data.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(MyStatement, 2, data.c_str(), -1, SQLITE_STATIC);

		int statusofstep = sqlite3_step(MyStatement);

		sqlite3_finalize(MyStatement);
	}
	else
	{
		cout << "Failed prep (Catalyst Data)" << endl;
	}
}

void Database::CreateSpellTable()
{
	sqlite3_stmt * MyStatement;
	string sql = "CREATE TABLE IF NOT EXISTS Spells (spellid INTEGER PRIMARY KEY, name TEXT, power INTEGER, typeid INTEGER, focusid INTEGER, catalystid INTEGER, FOREIGN KEY(focusid) REFERENCES Foci(focusid), FOREIGN KEY(catalystid) REFERENCES Catali(catalystid), FOREIGN KEY(typeid) REFERENCES Types(typeid));";

	int statusofprep = sqlite3_prepare_v2(db, sql.c_str(), -1, &MyStatement, NULL);

	if (statusofprep == SQLITE_OK)
	{
		int statusofstep = sqlite3_step(MyStatement);

		sqlite3_finalize(MyStatement);
	}
	else
	{
		cout << "Failed prep (Spell Table)" << endl;
	}
}

void Database::InsertSpellData(string name, int power, int type, int focus, int catalyst)
{
	sqlite3_stmt * MyStatement;
	string sql = "INSERT INTO Spells (name, power, typeid, focusid, catalystid) VALUES (?, ?, ?, ?, ?)";

	int statusofprep = sqlite3_prepare_v2(db, sql.c_str(), -1, &MyStatement, NULL);

	if (statusofprep == SQLITE_OK)
	{
		sqlite3_bind_text(MyStatement, 1, name.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(MyStatement, 2, power);
		sqlite3_bind_int(MyStatement, 3, type);
		sqlite3_bind_int(MyStatement, 4, focus);
		sqlite3_bind_int(MyStatement, 5, catalyst);

		int statusofstep = sqlite3_step(MyStatement);

		sqlite3_finalize(MyStatement);
	}
	else
	{
		cout << "Failed prep (Spell Data)" << endl;
	}
}

void Database::PopulateDB()
{
	CreateTypesTable();
	CreateFociTable();
	CreateCataliTable();
	CreateSpellTable();

	for (int i = 0; i < (int)types.size(); i++)
	{
		InsertTypeData(types.at(i));
	}
	for (int i = 0; i < (int)foci.size(); i++)
	{
		InsertFocusData(foci.at(i));
	}
	for (int i = 0; i < (int)catali.size(); i++)
	{
		InsertCatalystData(catali.at(i));
	}
		
	cout << "Moving on to spell data" << endl;

	InsertSpellData("OctoCat", 50, 3, 4, 5);
	InsertSpellData("Ignition", 40, 2, 1, 2);
	InsertSpellData("DarkWall", 40, 11, 2, 3);
	InsertSpellData("Skellybob", 30, 8, 4, 4);
	InsertSpellData("IceBlock", 20, 6, 3, 2);
	InsertSpellData("Earthquake", 35, 4, 1, 1);
	InsertSpellData("MadHacks", 30, 12, 1, 5);
	InsertSpellData("Gunpowder", 20, 7, 1, 1);
	InsertSpellData("Sap", 15, 5, 2, 3);
	InsertSpellData("ChaosBolt", 25, 8, 1, 3);
	InsertSpellData("Sprout", 25, 4, 3, 4);
	InsertSpellData("FlameBody", 35, 2, 2, 1);
	InsertSpellData("Guitarist", 25, 5, 4, 5);
	InsertSpellData("Void", 40, 1, 1, 3);

}

void Database::SelectTypes()
{
	sqlite3_stmt * MyStatement;
	string sql = "SELECT * FROM Types";

	int statusofprep = sqlite3_prepare_v2(db, sql.c_str(), -1, &MyStatement, NULL);

	if (statusofprep == SQLITE_OK)
	{

		int statusofstep = sqlite3_step(MyStatement);

		while (statusofstep == SQLITE_ROW)
		{
			int id = sqlite3_column_int(MyStatement, 0);
			string name = (char*)sqlite3_column_text(MyStatement, 1);

			cout << id << " - " << name << endl;

			statusofstep = sqlite3_step(MyStatement);
		}

		sqlite3_finalize(MyStatement);
	}
}

void Database::SelectFoci()
{
	sqlite3_stmt * MyStatement;
	string sql = "SELECT * FROM Foci";

	int statusofprep = sqlite3_prepare_v2(db, sql.c_str(), -1, &MyStatement, NULL);

	if (statusofprep == SQLITE_OK)
	{
		int statusofstep = sqlite3_step(MyStatement);

		while (statusofstep == SQLITE_ROW)
		{
			int id = sqlite3_column_int(MyStatement, 0);
			string name = (char*)sqlite3_column_text(MyStatement, 1);

			cout << id << " - " << name << endl;

			statusofstep = sqlite3_step(MyStatement);
		}

		sqlite3_finalize(MyStatement);
	}
	else
	{
		cout << "Select foci prep failed" << endl;
	}
}

void Database::SelectCatali()
{
	sqlite3_stmt * MyStatement;
	string sql = "SELECT * FROM Catali";

	int statusofprep = sqlite3_prepare_v2(db, sql.c_str(), -1, &MyStatement, NULL);

	if (statusofprep == SQLITE_OK)
	{

		int statusofstep = sqlite3_step(MyStatement);

		while (statusofstep == SQLITE_ROW)
		{
			int id = sqlite3_column_int(MyStatement, 0);
			string name = (char*)sqlite3_column_text(MyStatement, 1);

			cout << id << " - " << name << endl;

			statusofstep = sqlite3_step(MyStatement);
		}

		sqlite3_finalize(MyStatement);
	}
}

Spell Database::SelectSpell(int type, int focus, int catalyst)
{
	Spell temp{0, "Failed Spell", focus};
	sqlite3_stmt * MyStatement;
	string sql = "SELECT Spells.name, Spells.power FROM Spells WHERE Spells.typeid = ? AND Spells.focusid = ? AND Spells.catalystid = ?";

	int statusofprep = sqlite3_prepare_v2(db, sql.c_str(), -1, &MyStatement, NULL);

	if (statusofprep == SQLITE_OK)
	{

		sqlite3_bind_int(MyStatement, 1, type);
		sqlite3_bind_int(MyStatement, 2, focus);
		sqlite3_bind_int(MyStatement, 3, catalyst);

		int statusofstep = sqlite3_step(MyStatement);

		int power = 0;
		string name = "Failed Spell";

		while (statusofstep == SQLITE_ROW)
		{
			name = (char*)sqlite3_column_text(MyStatement, 0);
			power = sqlite3_column_int(MyStatement, 1);

			temp.effect = focus;
			temp.name = name;
			temp.power = power;

			statusofstep = sqlite3_step(MyStatement);
		}

		sqlite3_finalize(MyStatement);

	}
	return temp;
}

