// Tic-Tac-Toe.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <random>
#include <cstdlib>
#include <vector>

void print(const char arr[]); // Fürs Anzeigen des Boards
bool double_indice(std::vector<int> vec, int index); // Zum checken wenn beide Spieler das gleiche Index ausgewählt haben
void zeile_pruefen(char arr[], int index, char c1, char c2, bool& res_p1, bool& res_p2);
void spalte_pruefen(char arr[], int index, char c1, char c2, bool& res_p1, bool& res_p2);
bool diagonal_pruefen(char arr[], char c);
bool game_end(char arr[], int size);
int possibilities(char arr[]); // Für das Spiel des Computers
bool Board_leer(char arr[], int size);
char list[9] = {}; // Das Board
void titel(void);

struct condition {
	int positions[3];
	int returnValue;
};

int main()
{
	char c = 'z';


	while (c != 'n' && c != 'N')
	{
		int choice = 0; // Für die Wahl des Spielers
		bool game_win = false; // Damit möchte ich checken, ob jemand bereits das Spiel gewonnen hat
		bool result_p1 = false; // Das ist zum Speichern das Ergebnis des Players 1, über ob er schon gewonnen hat oder nicht
		bool result_p2 = false; // Das ist zum Speichern das Ergebnis des Players 2, über ob er schon gewonnen hat oder nicht
		bool start = false; // Das nutze ich um zu gucken, ob das Spiel bereits begonnen hat. Besonders wenn ich frage, wer fängt an
		std::vector<int> indices; // Ich speiche hier die Wahl alle Spieler, damit sie nicht die gleiche Index auswählen
		int spieler1 = 0; // Spieler1 zum checken, wer beginnt. Das Computer oder der Mensch
		int index_list = 0; // Für die Wahl des Computers
		int i = 0;

		system("cls");

		for (int i = 0; i < 9; i++) // Ich fülle zuerst mein Board mit Leerzeichen
		{
			list[i] = ' ';
		}


		srand((unsigned)time(NULL)); // Für zufällige Zahlen 
		std::cout << std::endl;
		std::cout << "\tTic-Tac-Toe" << std::endl;
		std::cout << "\t============" << std::endl << std::endl;
		std::cout << "Player 1 - [X]          Player 2 - [O]" << std::endl << std::endl;

		char list_bsp[] = { '0','1','2','3','4','5','6','7','8' };

		std::cout << "Diese Tabelle stellt den Index fuer jedes Feld des Spiels dar." << std::endl;
		print(list_bsp);
		std::cout << std::endl << std::endl;

		if (start == false)
		{
			std::cout << "Wollen Sie als erste anfangen? 1 - [Ja] und 0 - [Nein] >> ";
			std::cin >> spieler1;
			std::cin.ignore();
			start = true;
		}

		if (spieler1 != 1) // Hier fängt der Mensch an
			i = 1;

		while (true)
		{
			if (i % 2 == 0) // In diesem Fall fängt der Mensch an
			{
				system("cls");
				std::cout << std::endl;
				std::cout << "\tTic-Tac-Toe" << std::endl;
				std::cout << "\t============" << std::endl << std::endl;
				std::cout << "Player 1 - [X]          Player 2 - [O]" << std::endl << std::endl;

				char list_bsp[] = { '0','1','2','3','4','5','6','7','8' };

				std::cout << "Diese Tabelle stellt den Index fuer jedes Feld des Spiels dar." << std::endl;
				print(list_bsp);
				std::cout << std::endl << std::endl;

				print(list);

				do
				{
					std::cout << "Dein Wahl >> ";
					std::cin >> choice;
				} while (double_indice(indices, choice) && (choice >= 0 && choice < 9));

				indices.push_back(choice);
				list[choice] = 'X';
				std::cin.ignore();
				i++;
			}
			else	// Oder das Computer
			{
				system("cls");
				srand((unsigned)time(NULL)); // Für zufällige Zahlen 
				std::cout << std::endl;
				std::cout << "\tTic-Tac-Toe" << std::endl;
				std::cout << "\t============" << std::endl << std::endl;
				std::cout << "Player 1 - [X]          Player 2 - [O]" << std::endl << std::endl;

				char list_bsp[] = { '0','1','2','3','4','5','6','7','8' };

				std::cout << "Diese Tabelle stellt den Index fuer jedes Feld des Spiels dar." << std::endl;
				print(list_bsp);
				std::cout << std::endl << std::endl;
				print(list);
				do
				{
					index_list = possibilities(list);
				} while (index_list > 8 || double_indice(indices, index_list));

				indices.push_back(index_list);
				if (index_list >= 0 && index_list < 9)
					list[index_list] = 'O';
				i++;
			}


			// Hier überprüfe ich, ob ein Spieler schon gewonnen hat. 
			// Ich fange mit den Zeilen an.
			//===============================================================================================

			for (int index = 0; index < 3; index++)
			{
				zeile_pruefen(list, index, 'X', 'O', result_p1, result_p2);
				if (result_p1 == true)
				{
					titel();
					std::cout << std::endl << "Spieler 1 hat gewonnen" << std::endl;
					game_win = true;
					break;
				}

				if (result_p2 == true)
				{
					titel();
					std::cout << std::endl << "Das Computer hat gewonnen" << std::endl;
					game_win = true;
					break;
				}
			}

			if (game_win == true)
			{
				break;
			}

			// Hier mache ich weiter mit den Spalten
			// Erst Player 1: Der Mensch

			for (int index = 0; index < 3; index++)
			{
				spalte_pruefen(list, index, 'X', 'O', result_p1, result_p2);
				if (result_p1 == true)
				{
					titel();
					std::cout << std::endl << "Spieler 1 hat gewonnen" << std::endl;
					game_win = true;
					break;
				}

				if (result_p2 == true)
				{
					titel();
					std::cout << std::endl << "Das Computer hat gewonnen" << std::endl;
					game_win = true;
					break;
				}
			}

			if (game_win == true)
			{
				break;
			}

			// Hier überprüfe ich die Diagonalen
			// Erst Player 1: Der Mensch

			result_p1 = diagonal_pruefen(list, 'X');

			if (result_p1 == true)
			{
				titel();
				std::cout << std::endl << "Spieler 1 hat gewonnen" << std::endl;
				game_win = true;
				break;
			}

			// Dann Player 2: Das Computer

			result_p2 = diagonal_pruefen(list, 'O');

			if (result_p2 == true)
			{
				titel();
				std::cout << std::endl << "Das Computer hat gewonnen" << std::endl;
				game_win = true;
				break;
			}

			// Hier überprüfe ich ob das Board des Spiels schon vollständig gefüllt ist. Wenn ja nehme ich einfach an, dass das Spiel zu Ende ist

			if (game_end(list, 9)) // Wenn die max. Anzahl von Touren erreicht wurde und das Spiel wurde noch nicht beendet.
			{
				titel();
				std::cout << std::endl << "Niemand hat gewonnen" << std::endl;
				game_win = true;
				break;
			}

			if (game_win == true)
			{
				break;
			}

			system("cls");
		}

		std::cout << std::endl << std::endl << "Wollen Sie weiterspielen ? J - [Ja] und N - [Nein] >> ";
		std::cin >> c;
	}
	std::cout << std::endl << "Auf Wiedersehen!!! Tschuessssssssssy :-)" << std::endl;
	return 0;
}

void print(const char arr[]) {
	int index = 0;

	for (int i = 0; i < 3; i++)
	{
		std::cout << "\t\t-------------" << std::endl;
		std::cout << "\t\t|";
		for (int j = 0; j < 3; j++) {
			std::cout << " " << arr[index] << " |";
			index++;
		}
		std::cout << std::endl;
	}
	std::cout << "\t\t-------------" << std::endl;
}

bool double_indice(std::vector<int> vec, int index)
{
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i] == index)
			return true;
	}
	return false;
}

void zeile_pruefen(char arr[], int index, char c1, char c2, bool& res_p1, bool& res_p2)
{
	int check = 0;

	if (c1 == 'X')
	{
		for (int j = index * 3; j < (index * 3) + 3; j++)
		{
			if (arr[j] == c1)
				check++;
		}

		if (check == 3)
			res_p1 = true;
		else
			res_p1 = false;
	}

	if (c2 == 'O')
	{
		check = 0;
		for (int j = index * 3; j < (index * 3) + 3; j++)
		{
			if (arr[j] == c2)
				check++;
		}

		if (check == 3)
			res_p2 = true;
		else
			res_p2 = false;
	}
}

void spalte_pruefen(char arr[], int index, char c1, char c2, bool& res_p1, bool& res_p2)
{
	int check = 0;
	if (c1 == 'X')
	{
		for (int j = index; j <= index + 6; j = j + 3)
		{
			if (arr[j] == c1)
				check++;
		}

		if (check == 3)
			res_p1 = true;
		else
			res_p1 = false;
	}

	if (c2 == 'O')
	{
		check = 0;
		for (int j = index; j <= index + 6; j = j + 3)
		{
			if (arr[j] == c2)
				check++;
		}

		if (check == 3)
			res_p2 = true;
		else
			res_p2 = false;
	}


}

bool diagonal_pruefen(char arr[], char c)
{
	int check = 0;
	bool result = false;

	// Diagonal 1
	for (int i = 0; i < 9; i = i + 4)
	{
		if (arr[i] == c)
			check++;
	}
	if (check == 3)
		return true;

	check = 0;

	// Diagonal 2
	for (int i = 2; i < 7; i = i + 2)
	{
		if (arr[i] == c)
			check++;
	}
	if (check == 3)
		return true;

	return false;

}

bool Board_leer(char arr[], int size)
{
	int check = 0;
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == 'O' || arr[i] == 'X')
			check++;
	}

	if (check == 0)
		return true;
	else
		return false;
}

void titel(void)
{
	system("cls");
	std::cout << std::endl;
	std::cout << "\tTic-Tac-Toe" << std::endl;
	std::cout << "\t============" << std::endl << std::endl;
	std::cout << "Player 1 - [X]          Player 2 - [O]" << std::endl << std::endl;

	char list_bsp[] = { '0','1','2','3','4','5','6','7','8' };

	std::cout << "Diese Tabelle stellt den Index fuer jedes Feld des Spiels dar." << std::endl;
	print(list_bsp);
	std::cout << std::endl << std::endl;
	print(list);
}

bool game_end(char arr[], int size)
{
	int check = 0;
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == 'O' || arr[i] == 'X')
			check++;
	}

	if (check == 9)
		return true;
	else
		return false;
}

int possibilities(char arr[]) {
	// Helper function to check if two characters in the array match 'ch' and one is empty.
	auto isPotentialMove = [&](int a, int b, int c, char ch) {
		return arr[a] == ch && arr[b] == ch && arr[c] == ' ';
		};

	char players[2] = { 'O', 'X' }; // Define the players
	int positions[8][3] = {
		{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Rows
		{0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columns
		{0, 4, 8}, {2, 4, 6}             // Diagonals
	};

	if (Board_leer(list, 9)) return 4;

	// Check for winning or blocking moves for each player.
	for (char player : players) {
		for (auto& position : positions) {
			for (int i = 0; i < 3; i++) {
				if (isPotentialMove(position[i], position[(i + 1) % 3], position[(i + 2) % 3], player)) {
					return position[(i + 2) % 3];
				}
			}
		}
	}

	if (game_end(list, 9)) return -1;

	return rand() % 10;
}