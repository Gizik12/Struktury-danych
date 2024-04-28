#include <iostream>
#include <chrono>

#include "Public/PriorityQueue_Heap.h"
#include "Public/PriorityQueue_LinkedList.h"
#include "../DataGenerator/DataGenerator.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "pl_PL"); // Ustawienie języka polskiego.

	PriorityQueue* priorityQueue;			// Wskaźnik na wybrany typ kolejki.
	char priorityQueue_type;				// Wybrany typ kolejki.
	char priorityQueue_opt;					// Wybrana operacja kolejki.
	char dataAmt_type;						// Wybrana ilość danych.
	int dataAmt;							// Ilość danych do prowadzonego badania.
	short priorityMultiplier = 5;			// Mnożnik maksymalnej wartości wygenerowanego priorytetu (krotność ilości danych).

	chrono::steady_clock::time_point OperationStart;	// Czas rozpoczęcia operacji.
	chrono::steady_clock::time_point OperationEnd;		// Czas zakończenia operacji.
	chrono::nanoseconds TotalOperationTime;				// Całkowity czas wykonywania operacji.

	while (true) // Menu wyboru typu kolejki.
	{
		do
		{
			system("cls");
			cout << "Wybierz typ kolejki:\n1. Kopiec\n2. Lista wiązana\nq. Wyjdź\n";
			cin >> priorityQueue_type;
		} while (priorityQueue_type != '1' && priorityQueue_type != '2' && priorityQueue_type != 'q');

		priorityQueue = nullptr;
		switch (priorityQueue_type)
		{
		case '1':
			priorityQueue = new PriorityQueue_Heap;
			break;

		case '2':
			priorityQueue = new PriorityQueue_LinkedList;
			break;

		case 'q':
			return 0;

		default:
			cout << "Unknown error has occured.\n";
			return 1;
		}

		while (true) // Menu wyboru operacji.
		{
			do
			{
				system("cls");
				cout << "Wybierz operację:\n1. insert\n2. extractMax\n3. peek\n4. modifyKey\n5. returnSize\nq. Cofnij\n";
				cin >> priorityQueue_opt;
			} while (priorityQueue_type != '1' && priorityQueue_type != '2' && priorityQueue_type != '3' && priorityQueue_type != '4' && priorityQueue_type != '5' && priorityQueue_type != 'q');
			
			if (priorityQueue_opt == 'q')
			{
				break;
			}

			do
			{
				system("cls");
				cout << "Wybierz ilość danych:\n1. 5 000\n2. 8 000\n3. 10 000\n4. 16 000\n5. 20 000\n6. 40 000\n7. 60 000\n8. 100 000\n";
				cin >> dataAmt_type;
			} while (dataAmt_type != '1' && dataAmt_type != '2' && dataAmt_type != '3' && dataAmt_type != '4' && dataAmt_type != '5' && dataAmt_type != '6' && dataAmt_type != '7' && dataAmt_type != '8');

			switch (dataAmt_type)
			{
			case '1':
				dataAmt = 5000;
				break;
				
			case '2':
				dataAmt = 8000;
				break;
				
			case '3':
				dataAmt = 10000;
				break;
				
			case '4':
				dataAmt = 16000;
				break;
				
			case '5':
				dataAmt = 20000;
				break;
				
			case '6':
				dataAmt = 40000;
				break;
				
			case '7':
				dataAmt = 60000;
				break;
				
			case '8':
				dataAmt = 100000;
				break;

			default:
				cout << "Unknown error has occured.";
				return 1;
			}

			int maxPriority = dataAmt * priorityMultiplier;
			switch (priorityQueue_opt)
			{
			case '1':
				OperationStart = chrono::steady_clock::now();
				for (int i = 0; i < dataAmt; i++)
				{
					priorityQueue->insert(GenerateRandomNumber(), GenerateRandomNumber(0, maxPriority));
				}
				OperationEnd = chrono::steady_clock::now();
				break;

			case '2':
				cout << "Generowanie losowej kolejki...\n";
				for (int i = 0; i < dataAmt; i++)
				{
					priorityQueue->insert(GenerateRandomNumber(), GenerateRandomNumber(0, maxPriority));
				}
				OperationStart = chrono::steady_clock::now();
				for (int i = 0; i < dataAmt; i++)
				{
					priorityQueue->extractMax();
				}
				OperationEnd = chrono::steady_clock::now();
				break;

			case '3':
				cout << "Generowanie losowej kolejki...\n";
				for (int i = 0; i < dataAmt; i++)
				{
					priorityQueue->insert(GenerateRandomNumber(), GenerateRandomNumber(0, maxPriority));
				}
				OperationStart = chrono::steady_clock::now();
				for (int i = 0; i < dataAmt; i++)
				{
					priorityQueue->peek();
				}
				OperationEnd = chrono::steady_clock::now();
				break;

			case '4':
				cout << "Generowanie losowej kolejki...\n";
				for (int i = 0; i < dataAmt; i++)
				{
					priorityQueue->insert(GenerateRandomNumber(), GenerateRandomNumber(0, maxPriority));
				}
				OperationStart = chrono::steady_clock::now();
				for (int i = 0; i < dataAmt; i++)
				{
					priorityQueue->modifyKey(GenerateRandomNumber(), GenerateRandomNumber(0, maxPriority));
				}
				OperationEnd = chrono::steady_clock::now();
				break;

			case '5':
				cout << "Generowanie losowej kolejki...\n";
				for (int i = 0; i < dataAmt; i++)
				{
					priorityQueue->insert(GenerateRandomNumber(), GenerateRandomNumber(0, maxPriority));
				}
				OperationStart = chrono::steady_clock::now();
				for (int i = 0; i < dataAmt; i++)
				{
					priorityQueue->returnSize();
				}
				OperationEnd = chrono::steady_clock::now();
				break;

			default:
				cout << "Unknown error has occured.";
				return 1;
			}
			delete priorityQueue;
			TotalOperationTime = chrono::duration_cast<chrono::nanoseconds>(OperationEnd - OperationStart);
			cout << "Całkowity czas wykonywania operacji: " << TotalOperationTime.count() << " ns\n";
			system("pause");
			break;
		}
	}
	return 0;
}