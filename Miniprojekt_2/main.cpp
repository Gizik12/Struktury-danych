#include <iostream>
#include <chrono>

#include "Public/PriorityQueue_Heap.h"
#include "Public/PriorityQueue_LinkedList.h"
#include "DataGenerator/DataGenerator.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "pl_PL"); // Ustawienie języka polskiego.

	int w;
	PriorityQueue* priorityQueue;			// Wskaźnik na wybrany typ kolejki.
	PriorityQueue* priorityQueueH;			// Wskaźnik na wybrany typ kolejki pomocniczy.
	char priorityQueue_type;				// Wybrany typ kolejki.
	char priorityQueue_opt;					// Wybrana operacja kolejki.
	char dataAmt_type;						// Wybrana ilość danych.
	int dataAmt;							// Ilość danych do prowadzonego badania.
	short priorityMultiplier = 5;			// Mnożnik maksymalnej wartości wygenerowanego priorytetu (krotność ilości danych).
	double totalDuration;
	int e, p = 0;

	chrono::steady_clock::time_point operationStart;	// Czas rozpoczęcia operacji.
	chrono::steady_clock::time_point operationEnd;		// Czas zakończenia operacji.

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
			priorityQueueH = new PriorityQueue_Heap;
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
				cout << "Wybierz ilość danych:\n1. 5 000\n2. 8 000\n3. 10 000\n4. 16 000\n5. 20 000\n6. 40 000\n7. 60 000\n8. 100 000\n9. Dowolna\n";
				cin >> dataAmt_type;
			} while (dataAmt_type != '1' && dataAmt_type != '2' && dataAmt_type != '3' && dataAmt_type != '4' && dataAmt_type != '5' && dataAmt_type != '6' && dataAmt_type != '7' && dataAmt_type != '8' && dataAmt_type != '9');

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

			case '9':
				cout << "Podaj wartosc" << endl;
				cin >> w;
				dataAmt = w;
				break;
				

			default:
				cout << "Unknown error has occured.";
				return 1;
			}

			int maxPriority = dataAmt * priorityMultiplier;
			totalDuration = 0.0;
			switch (priorityQueue_opt)
			{
			case '1':
			/* //KOPIEC
			 * 	//BEST-CASE
			 *  	p = 1;
			 *		for (int i = 0; i < dataAmt; i++)
			 *		{
			 *			priorityQueue->insert(GenerateRandomNumber(-2147483647, 2147483647), GenerateRandomNumber(2, maxPriority);
			 *		}
			 *  //WORST-CASE
			 *    	p = maxPriority;
			 * 		for (int i = 0; i < dataAmt; i++)
			 *		{
			 *			priorityQueue->insert(GenerateRandomNumber(-2147483647, 2147483647), GenerateRandomNumber(1, maxPriority - 1);
			 *		}
			 * 
			 * //LISTA
			 *	//BEST-CASE
			 *		p = maxPriority;
			 *		for (int i = 0; i < dataAmt; i++)
			 *		{
			 *			priorityQueue->insert(GenerateRandomNumber(-2147483647, 2147483647), GenerateRandomNumber(1, maxPriority - 1));
			 *		}
			 *	//WORST-CASE
			 *		p = 1;
			 *		for (int i = 0; i < dataAmt; i++)
			 *		{
			 *			priorityQueue->insert(GenerateRandomNumber(-2147483647, 2147483647), GenerateRandomNumber(2, maxPriority));
			 *		}
			*/
				e = GenerateRandomNumber(-2147483647, 2147483647);
				p = GenerateRandomNumber(1, maxPriority);
				for (int i = 0; i < dataAmt; i++)
				{
					priorityQueue->insert(GenerateRandomNumber(-2147483647, 2147483647), GenerateRandomNumber(2, maxPriority));
				}
				for (int i = 0; i < 100; i++)
				{
					priorityQueueH = priorityQueue->copy();
					operationStart = chrono::steady_clock::now();
					priorityQueueH->insert(e, p);
					operationEnd = chrono::steady_clock::now();
					auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(operationEnd - operationStart).count();
					totalDuration += duration;
				}
				break;

			case '2':
				cout << "Generowanie losowej kolejki...\n";
				for (int i = 0; i < dataAmt; i++)
				{
					priorityQueue->insert(GenerateRandomNumber(-2147483647, 2147483647), GenerateRandomNumber(1, maxPriority));
				}
				for (int i = 0; i < 100; i++)
				{
					priorityQueueH = priorityQueue->copy();
					operationStart = chrono::steady_clock::now();
					priorityQueueH->extractMax();
					operationEnd = chrono::steady_clock::now();
					auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(operationEnd - operationStart).count();
					totalDuration += duration;
				}
				break;

			case '3':
				cout << "Generowanie losowej kolejki...\n";
				for (int i = 0; i < dataAmt; i++)
				{
					priorityQueue->insert(GenerateRandomNumber(-2147483647, 2147483647), GenerateRandomNumber(1, maxPriority));
				}
				for (int i = 0; i < 100; i++)
				{
					priorityQueueH = priorityQueue->copy();
					operationStart = chrono::steady_clock::now();
					priorityQueueH->peek();
					operationEnd = chrono::steady_clock::now();
					auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(operationEnd - operationStart).count();
					totalDuration += duration;
				}
				break;

			case '4':
			/* //KOPIEC
			 * 	//BEST-CASE
			 *		for (int i = 0; i < dataAmt - 1; i++)
			 *		{
			 *			priorityQueue->insert(GenerateRandomNumber(-2147483647, 2147483646), GenerateRandomNumber(1, maxPriority - 2));
			 *		}
			 *		priorityQueue->insert(2147483647, maxPriority - 1);
			 *		e = 2147483647;
			 *		p = maxPriority;
			 *
			 *  //WORST-CASE
			 * 		for (int i = 0; i < dataAmt - 1; i++)
			 *		{
			 *			priorityQueue->insert(GenerateRandomNumber(-2147483647, 2147483646), GenerateRandomNumber(2, maxPriority - 1));
			 *		}
			 *		priorityQueue->insert(2147483647, 1);
			 *		e = 2147483647;
			 *		p = maxPriority;
			 *
			 * //LISTA
			 *	//BEST-CASE
			 *		for (int i = 0; i < dataAmt - 1; i++)
			 *		{
			 *			priorityQueue->insert(GenerateRandomNumber(-2147483647, 2147483646), GenerateRandomNumber(1, maxPriority - 2));
			 *		}
			 *		priorityQueue->insert(2147483647, maxPriority - 1);
			 *		e = 2147483647;
			 *		p = maxPriority;
			 *
			 *	//WORST-CASE
			 *		for (int i = 0; i < dataAmt - 1; i++)
			 *		{
			 *			priorityQueue->insert(GenerateRandomNumber(-2147483647, 2147483646), GenerateRandomNumber(3, maxPriority));
			 *		}
			 *		priorityQueue->insert(2147483647, 2);
			 *		e = 2147483647;
			 *		p = 1;
			*/
				cout << "Generowanie losowej kolejki...\n";
				for (int i = 0; i < dataAmt; i++)
				{
					priorityQueue->insert(GenerateRandomNumber(-2147483647, 2147483646), GenerateRandomNumber(1, maxPriority));
				}
				e = GenerateRandomNumber(-2147483647, 2147483646);
				p = GenerateRandomNumber(1, maxPriority);
				for (int i = 0; i < 100; i++)
				{
					priorityQueueH = priorityQueue->copy();
					operationStart = chrono::steady_clock::now();
					priorityQueueH->modifyKey(e, p);
					operationEnd = chrono::steady_clock::now();
					auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(operationEnd - operationStart).count();
					totalDuration += duration;
				}
				break;

			case '5':
				cout << "Generowanie losowej kolejki...\n";
				for (int i = 0; i < dataAmt; i++)
				{
					priorityQueue->insert(GenerateRandomNumber(-2147483647, 2147483647), GenerateRandomNumber(1, maxPriority));
				}
				for (int i = 0; i < 100; i++)
				{
					priorityQueueH = priorityQueue->copy();
					operationStart = chrono::steady_clock::now();
					priorityQueueH->returnSize();
					operationEnd = chrono::steady_clock::now();
					auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(operationEnd - operationStart).count();
					totalDuration += duration;
				}
				break;

			default:
				cout << "Unknown error has occured.";
				return 1;
			}
			delete priorityQueue;
			delete priorityQueueH;
			double average = totalDuration / static_cast<double>(100);
			cout << "Średni całkowity czas wykonywania operacji z 100 prób: " << average << " ns\n";
			system("pause");
			break;
		}
	}
	return 0;
}