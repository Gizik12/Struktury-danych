#include <iostream>
#include <chrono>

#include "Public/HashTable_List.h"
#include "Public/HashTable_RedBlackTree.h"
#include "Public/HashTable_CuckooHashing.h"
#include "DataGenerator.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "pl_PL");

	HashTable* hashTable;	// Wskaźnik na wybrany wariant tablicy mieszającej.
	HashTable* hashTableH;	// Pomocnicza tablica mieszająca.
	
	int dataAmt;			// Ilość danych.
	double totalDuration;	// Całkowity czas wykonywania operacji.
	int key, value = 0;		// Losowo generowana para klucz-wartość wykorzystywana w pomiarach insert(key,value) i remove(key,value).
	int reps = 100;			// Liczba powtórzeń pomiaru.

	char hashTable_type;	// Wybrany przez użytkownika typ tablicy mieszającej.
	string hashTable_name;	// Nazwa wybranego wariantu kolejki.
	char hashTable_opt;		// Wybrana przez użytkownika operacja tablicy mieszającej.

	chrono::steady_clock::time_point optStart;	// Początek wykonywania pomiaru.
	chrono::steady_clock::time_point optEnd;	// Koniec wykonywania pomiaru.

	while (true)
	{
		do
		{
			system("cls");
			cout << "Podaj ilość danych: ";
			cin >> dataAmt;
		} while (dataAmt < 0);

		do
		{
			system("cls");
			cout << "Wybrana ilość danych: " << dataAmt << endl;
			cout << "\nWybierz wariant tablicy mieszającej: \n0 - kubełki z listą, \n1 - adresowanie otwarte plus kubełki ze zbalansowanym BST, \n2 - Cuckoo hashing \n";
			cin >> hashTable_type;
		} while (hashTable_type != '0' && hashTable_type != '1' && hashTable_type != '2');

		switch (hashTable_type)
		{
		case '0':
			hashTable = new HashTable_List;
			hashTable_name = "kubełki z listą";
			break;

		case '1':
			hashTable = new HashTable_RB(dataAmt);
			hashTable_name = "adresowanie otwarte plus kubełki ze zbalansowanym BST";
			break;

		case '2':
			hashTable = new HashTable_CuckooHashing(dataAmt);
			hashTable_name = "cuckoo hashing";
			break;
		
		default:
			system("cls");
			cout << "Unknown error has occured\n";
			return 1;
		}

		do
		{
			system("cls");
			cout << "Wybrana ilość danych: " << dataAmt << endl;
			cout << "Wybrany wariant tablicy mieszającej: " + hashTable_name << endl;
			cout << "\nWybierz operację: \n 0 - insert, \n 1 - remove\n";
			cin >> hashTable_opt;
		} while (hashTable_opt != '0' && hashTable_opt != '1');

		totalDuration = 0.0;
		switch (hashTable_opt)
		{
		case '0':
			key = GenerateRandomNumber(0, 2147483647);
			value = GenerateRandomNumber(0, 2147483647);

			for (int i = 0; i < dataAmt; i++)
			{
				hashTable->insert(GenerateRandomNumber(0, 2147483647), GenerateRandomNumber(0, 2147483647));
			}

			for (int i = 0; i < reps; i++)
			{
				hashTableH = hashTable->copy();
				optStart = chrono::steady_clock::now();
				hashTableH->insert(key, value);
				optEnd = chrono::steady_clock::now();
				auto duration = chrono::duration_cast<chrono::nanoseconds>(optEnd - optStart).count();
				totalDuration += duration;
			}
			break;

		case '1':
			key = GenerateRandomNumber(0, 2147483647);

			for (int i = 0; i < dataAmt; i++)
			{
				hashTable->insert(GenerateRandomNumber(0, 2147483647), GenerateRandomNumber(0, 2147483647));
			}

			for (int i = 0; i < reps; i++)
			{
				hashTableH = hashTable->copy();
				optStart = chrono::steady_clock::now();
				hashTableH->remove(key);
				optEnd = chrono::steady_clock::now();
				auto duration = chrono::duration_cast<chrono::nanoseconds>(optEnd - optStart).count();
				totalDuration += duration;
			}
			break;

		default:
			system("cls");
			cout << "Unknown error has occured\n";
			return 1;
		}

		delete hashTable;

		double averageTime = totalDuration / static_cast<double>(reps);

		system("cls");
		cout << "Wybrana ilość danych: " << dataAmt << endl;
		cout << "Wybrany wariant tablicy mieszającej: " + hashTable_name << endl;
		cout << "Średni czas wykonywania operacji z " << reps << " prób: " << averageTime << "ns\n";
		system("pause");
	}

	return 0;
}
