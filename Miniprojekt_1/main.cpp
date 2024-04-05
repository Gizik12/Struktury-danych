#include <iostream>
#include <chrono>
#include "Public/DataStructure.h"
#include "Public/ArrayList.h"
#include "Public/SinglyLinkedList.h"
#include "Public/SinglyLinkedListHeadTail.h"
#include "Public/DoublyLinkedList.h"

static long long MeasureTime(const chrono::steady_clock::time_point Start, const chrono::steady_clock::time_point End)
{
	auto Duration = chrono::duration_cast<chrono::milliseconds>(End - Start);
	return Duration.count();
}

int main()
{
	setlocale(LC_ALL, "pl_PL");

	unsigned int Capacity = 0;
	char DataStructureType;
	char Option;

	while (true)
	{
		do
		{
			system("cls");
			cout << "Pojemność ArrayList: " << Capacity << endl;
			if (Capacity <= 0)
			{
				cout << "Musisz podać pojemność dla ArrayList\n";
			}
			cout << "\nWybierz strukturę danych:\n1. ArrayList\n2. Singly Linked List (head)\n3. Singly Linked List (head & tail)\n4. Doubly Linked List\n5. Nowy rozmiar\n6. Wyjdź\n";
			cin >> DataStructureType;
		} while (DataStructureType != '1' && DataStructureType != '2' && DataStructureType != '3' && DataStructureType != '4' && DataStructureType != '5' && DataStructureType != '6');

		DataStructure<int>* PickedDataStructure; // Badania prowadzone są na typie int

		switch (DataStructureType)
		{
		case '1':
		{
			if (Capacity <= 0)
			{
				continue;
			}
			else
			{
				ArrayList<int>* ArrList = new ArrayList<int>(Capacity);
				PickedDataStructure = ArrList;
				break;
			}
		}

		/*case '2':
			Miejsce na klasę SinglyLinkedList
			break;

		case '3':
			// Miejsce na klasę SinglyLinkedListHeadTail
			break;*/

		case '4':
		{
			DoublyLinkedList<int>* DLL = new DoublyLinkedList<int>();
			PickedDataStructure = DLL;
			break;
		}

		case '5':
			do
			{
				cout << "Podaj pojemność ArrayList: ";
				cin >> Capacity;
			} while (Capacity <= 0);
			continue;

		case '6':
			return 0;

		default:
			system("cls");
			cout << "Unknown error has occured";
			return 1;
		}

		while (true)
		{
			do
			{
				system("cls");
				if (PickedDataStructure->IsEmpty())
				{
					cout << "Brak elementów\n";
				}
				cout << "\nWybierz operację:\n1. Wyświetl rozmiar\n2. Dodaj element na początku\n3. Dodaj element na końcu\n4. Dodaj element w wybranym miejscu\n5. Usuń element z przodu\n6. Usuń element na końcu\n7. Usuń element w wybranym miejscu\n8. Cofnij\n";
				cin >> Option;
			} while (Option != '1' && Option != '2' && Option != '3' && Option != '4' && Option != '5' && Option != '6' && Option != '7' && Option != '8');

			switch (Option)
			{
			case '1':
				cout << "Rozmiar: " << PickedDataStructure->GetSize() << endl;
				system("pause");
				continue;

			case '2':
			{
				int Element;

				cout << "Dodaj element na początek: ";
				cin >> Element;

				PickedDataStructure->PushFront(Element);
				continue;
			}

			case '3':
			{
				int Element;

				cout << "Dodaj element na koniec: ";
				cin >> Element;

				PickedDataStructure->PushBack(Element);
				continue;
			}

			case '4':
			{
				int Element;
				unsigned int Index;

				cout << "Dodaj element: ";
				cin >> Element;

				if (PickedDataStructure->GetSize() > 1)
				{
					cout << "Podaj indeks (0 - " << PickedDataStructure->GetSize() - 1 << "): ";
				}
				else
				{
					PickedDataStructure->PushFront(Element);
					continue;
				}
				cin >> Index;

				PickedDataStructure->Insert(Element, Index);
				continue;
			}

			case '5':
				PickedDataStructure->PopFront();
				continue;

			case '6':
				PickedDataStructure->PopBack();
				continue;

			case '7':
			{
				unsigned int Index;
				
				if (PickedDataStructure->GetSize() > 1)
				{
					cout << "Podaj indeks (0 - " << PickedDataStructure->GetSize() - 1 << ") : ";
					cin >> Index;

					PickedDataStructure->RemoveAt(Index);
					continue;
				}
				else
				{
					PickedDataStructure->PopFront();
					continue;
				}
			}

			case '8':
				break;

			default:
				cout << "Unknown error has occured\n";
				return 1;
			}
			delete PickedDataStructure;
			break;
		}
	}

	return 0;
}

