/*
	Scotland White - Madhacks 2018
	Magic Generator
*/

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include "Database.h"

using namespace std;

int GAMEMODE = 0;
int DIFFICULTY = 0;
bool RUNNING = true;

void Randomizer()
{
	srand(unsigned int(ctime_s));
}

class Player
{
public:
	int health;
	int armor;
	int num;
	string name;
	void ReduceHealth(int amnt);
	void GainHealth(int amnt);
	void GainArmor(int amnt);
	void ReduceArmor(int amnt);

	Player()
	{
		health = 100;
		armor = 20;
	}

};

int SinglePlayer(Database dbms)
{
	int callorder = (rand() % 2) + 1;
	Player player;
	Player ai;
	int counter = 0;

	while (RUNNING)
	{
		counter++;

		cout << "You >-< Health: " << player.health << ", Armor: " << player.armor << endl;
		cout << "Opp >-< Health: " << player.health << ", Armor: " << player.armor << endl;
		cout << endl;

		//Player's Turn
		int type;
		dbms.SelectTypes();
		cout << "What type of Spell would you like to cast?: ";
		cin >> type;
		cout << endl;

		int focus;
		dbms.SelectFoci();
		cout << "What Focus would you like to use?: ";
		cin >> focus;
		cout << endl;

		cout << "--!_!--" << endl;

		int catalyst;
		dbms.SelectCatali();
		cout << "What kind of Catalyst would you like to add?: ";
		cin >> catalyst;
		cout << endl;
		
		Spell ps = dbms.SelectSpell(type, focus, catalyst);

		//AI's turn
		type = (rand() % 12) + 1;
		focus = (rand() % 4) + 1;
		catalyst = (rand() % 5) + 1;

		Spell qs = dbms.SelectSpell(type, focus, catalyst);

		//Alternate who's spell resolves first
		switch (callorder)
		{
		case 1: // Player resolves first
			cout << "You cast " << ps.name << endl;
			switch (ps.effect)
			{
			case 1: //Damage
				ai.ReduceArmor(ps.power);

				if (ai.health <= 0)
				{
					dbms.InsertWin();
					GAMEMODE = 0;
				}
				break;
			case 2: //Armor up
				player.GainArmor(ps.power);
				break;
			case 3: //Heal
				player.GainHealth(ps.power);
				break;
			case 4: //Damage
				ai.ReduceArmor(ps.power);

				if (ai.health <= 0)
				{
					dbms.InsertWin();
					GAMEMODE = 0;
				}
				break;
			}
			// Opponent's turn
			cout << "Opponent casts " << qs.name << endl;
			switch (qs.effect)
			{
			case 1: //Damage
				player.ReduceArmor(ps.power);

				if (player.health <= 0)
				{
					dbms.InsertLoss();
					GAMEMODE = 0;
				}
				break;
			case 2: //Armor up
				ai.GainArmor(ps.power);
				break;
			case 3: //Heal
				ai.GainHealth(ps.power);
				break;
			case 4: //Damage
				player.ReduceArmor(ps.power);

				if (player.health <= 0)
				{
					dbms.InsertLoss();
					GAMEMODE = 0;
				}
				break;
			}
			break;
		case 2: // Opponent's turn is first
			cout << "Opponent casts " << qs.name << endl;
			switch (qs.effect)
			{
			case 1: //Damage
				player.ReduceArmor(ps.power);

				if (player.health <= 0)
				{
					dbms.InsertLoss();
					GAMEMODE = 0;
				}
				break;
			case 2: //Armor up
				ai.GainArmor(ps.power);
				break;
			case 3: //Heal
				ai.GainHealth(ps.power);
				break;
			case 4: //Damage
				player.ReduceArmor(ps.power);

				if (player.health <= 0)
				{
					dbms.InsertLoss();
					GAMEMODE = 0;
				}
				break;
			}
			//Player's turn
			cout << "You cast " << ps.name << endl;
			switch (ps.effect)
			{
			case 1: //Damage
				ai.ReduceArmor(ps.power);

				if (ai.health <= 0)
				{
					dbms.InsertWin();
					GAMEMODE = 0;
				}
				break;
			case 2: //Armor up
				player.GainArmor(ps.power);
				break;
			case 3: //Heal
				player.GainHealth(ps.power);
				break;
			case 4: //Damage
				ai.ReduceArmor(ps.power);

				if (ai.health <= 0)
				{
					dbms.InsertWin();
					GAMEMODE = 0;
				}
				break;
			}
			break;
		}

		if (GAMEMODE == 0)
		{
			return 0;
		}

		cout << "End of turn " << counter << endl;
		system("pause");

	}
	return 1;
}

void WinLose(Database dbms);

int main()
{
	string menuinput;
	Randomizer();
	cout << "Where would you like to store the game file?" << endl;
	cin >> menuinput;
	Database dbms(menuinput);
	cout << endl;

	while (true)
	{

		cout << "     /|\\                     /|\\" << endl;
		cout << "    /_-_\\                   /_-_\\" << endl;
		cout << "   /__||_\\        *        /_||__\\" << endl;
		cout << "  \\ \\______      * * *    ______/ /" << endl;
		cout << "  |\\_______=====*** *=====_______/|" << endl;
		cout << "   \\-_-_-/     *  * **     \\-_-_-/" << endl;
		cout << "     |_|_                   _|_|" << endl;
		cout << endl;

		cout << "    MAGIC GENERATOR WIZARD BATTLE" << endl;
		cout << endl;
		cout << endl;

		cout << "1 - Start the game" << endl;
		cout << "2 - W/L ratio (per session)" << endl;
		cout << "3 - Quit" << endl;
		cout << endl;

		while (true)
		{
			cin >> menuinput;
			if (stoi(menuinput) == 1)
			{
				break;
			}
			else if (stoi(menuinput) == 2)
			{
				WinLose(dbms);
				continue;
			}
			else if (stoi(menuinput) == 3)
			{
				exit(0);
			}

			cout << endl;

		}

		while (true)
		{
			cout << "How many players are there? (1-2): ";
			cin >> menuinput;
			if (stoi(menuinput) == 1)
			{
				GAMEMODE = 1;
				break;
			}
			else if (stoi(menuinput) == 2)
			{
				cout << "Unfortunately, there is no multiplayer yet..." << endl;
				continue;
			}
		}

		cout << endl;

		if (GAMEMODE == 1)
		{
			cout << "What difficulty would you prefer?" << endl;
			cout << "1 - Easy" << endl;
			cout << "4 - Medium" << endl;
			cout << "7 - Hard" << endl;
			cout << "10 - Dark Souls" << endl;
			cout << endl;

			cout << "Input: ";
			cin >> menuinput;

			switch (stoi(menuinput))
			{
			case 1:
				DIFFICULTY = 1;
				break;
			case 4:
				DIFFICULTY = 4;
				break;
			case 7:
				DIFFICULTY = 7;
				break;
			case 10:
				DIFFICULTY = 10;
				break;
			}
			SinglePlayer(dbms);
		}
		else
		{
			//Go to multiplayer format
		}
	}

}

void Player::GainHealth(int amnt)
{
	health += amnt;
	cout << amnt << " hitpoint heal." << endl;
}

void Player::GainArmor(int amnt)
{
	armor += amnt;
	cout << amnt << " armor gained." << endl;
}

void Player::ReduceHealth(int amnt)
{
	health -= amnt;
	cout << amnt << " damage taken." << endl;
}

void Player::ReduceArmor(int amnt)
{
	if (amnt > armor)
	{
		ReduceHealth(amnt - armor);
		cout << "No armor remaining." << endl;
	}
	else
	{
		armor -= amnt;
		cout << amnt << " armor lost" << endl;
	}
}

void WinLose(Database dbms)
{
	cout << "Your Win/Loss Ratio this session is: " << dbms.GetWLR() << endl;
}
