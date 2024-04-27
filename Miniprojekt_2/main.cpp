#include <iostream>
#include <chrono>

#include "Public/PriorityQueue_Heap.h"
#include "Public/PriorityQueue_LinkedList.h"
#include "../DataGenerator/DataGenerator.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "pl_PL"); // Ustawienie języka polskiego.
	
	PriorityQueue* priorityQueue = nullptr; // Wskaźnik na wybrany typ kolejki.
	char priorityQueue_type;				// Wybrany typ kolejki.
	char priorityQueue_op;					// Wybrana operacja kolejki.

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
				cin >> priorityQueue_op;
			} while (priorityQueue_type != '1' && priorityQueue_type != '2' && priorityQueue_type != '3' && priorityQueue_type != '4' && priorityQueue_type != '5' && priorityQueue_type != 'q');
		
			switch (priorityQueue_op)
			{
			case '1':
				OperationStart = chrono::steady_clock::now();
				for (int i = 0; i < 100; i++)
				{
					priorityQueue->insert();
				}
				OperationEnd = chrono::steady_clock::now();
				break;
				
			case '2':
				OperationStart = chrono::steady_clock::now();
				for (int i = 0; i < 100; i++)
				{
					priorityQueue->extractMax();
				}
				OperationEnd = chrono::steady_clock::now();
				break;
				
			case '3':
				OperationStart = chrono::steady_clock::now();
				for (int i = 0; i < 100; i++)
				{
					priorityQueue->peek();
				}
				OperationEnd = chrono::steady_clock::now();
				break;
				
			case '4':
				OperationStart = chrono::steady_clock::now();
				for (int i = 0; i < 100; i++)
				{
					priorityQueue->modifyKey();
				}
				OperationEnd = chrono::steady_clock::now();
				break;
				
			case '5':
				OperationStart = chrono::steady_clock::now();
				for (int i = 0; i < 100; i++)
				{
					priorityQueue->returnSize();
				}
				OperationEnd = chrono::steady_clock::now();
				break;
				
			case 'q':
				break;

			default:
				cout << "Unknown error has occured.";
				return 1;
			}
			if (priorityQueue_op == 'q')
			{
				break;
			}
			else
			{
				TotalOperationTime = chrono::duration_cast<chrono::nanoseconds>(OperationEnd - OperationStart);
				cout << "Całkowity czas wykonywania operacji: " << TotalOperationTime.count() / 100 << " ns\n";
				system("pause");
				continue;
			}
		}
	}
	return 0;
}