#include <iostream>
#include <chrono>
#include "Public/DataStructure.h"
#include "Public/ArrayList.h"
#include "Public/SinglyLinkedList.h"
#include "Public/SinglyLinkedListHeadTail.h"
#include "Public/DoublyLinkedList.h"

using namespace std;

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

	// Menu główne
	while (true)
	{
		do
		{
			system("cls");
			cout << "Pojemność ArrayList: " << Capacity << endl;
			if (Capacity <= 0)
			{
				cout << "Musisz podać pojemność dla ArrayList!\n";
			}
			cout << "\nWybierz strukturę danych:\n1. ArrayList\n2. Singly Linked List (head)\n3. Singly Linked List (head & tail)\n4. Doubly Linked List\n5. Nowa pojemność\n6. Wyjdź\n";
			cin >> DataStructureType;
		} while (DataStructureType != '1' && DataStructureType != '2' && DataStructureType != '3' && DataStructureType != '4' && DataStructureType != '5' && DataStructureType != '6');

		DataStructure<int>* PickedDataStructure = nullptr; // Badania prowadzone są na typie int

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
				
				PickedDataStructure = new ArrayList<int>(Capacity);
				break;
			}
		}

		case '2':
			PickedDataStructure = new SinglyLinkedList<int>();
			break;

		case '3':
			PickedDataStructure = new SinglyLinkedList_HeadTail<int>();
			break;

		case '4':
		{
			PickedDataStructure = new DoublyLinkedList<int>();
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

		// Menu operacji
		while (true)
		{
			unsigned int NumOfIterations = 1000000; // Badania krótkich operacji powtórzone są NumOfIterations razy

			do
			{
				system("cls");
				cout << "Wybierz operację:\n1. Wyświetl rozmiar\n2. Dodaj element na początku\n3. Dodaj element na końcu\n4. Dodaj element w wybranym miejscu\n5. Usuń element z przodu\n6. Usuń element na końcu\n7. Usuń element w wybranym miejscu\n8. Wyszukaj element w strukturze\n9. Cofnij\n";
				if (PickedDataStructure->IsEmpty())
				{
					cout << "Brak elementów!\n";
				}
				cin >> Option;
			} while (Option != '1' && Option != '2' && Option != '3' && Option != '4' && Option != '5' && Option != '6' && Option != '7' && Option != '8' && Option != '9');

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

				{
					// Kopia do prowadzenia badań
					DataStructure<int>* Copy = PickedDataStructure->Clone();

					auto OperationStart = chrono::high_resolution_clock::now();
					for (unsigned int i = 0; i < NumOfIterations; i++)
					{
						Copy->PushFront(Element);
					}
					auto OperationEnd = chrono::high_resolution_clock::now();
					delete Copy;

					PickedDataStructure->PushFront(Element);

					system("cls");
					cout << "Czas wykonywania: " << MeasureTime(OperationStart, OperationEnd) << " ms\n";
					system("pause");
					continue;
				}
			}

			case '3':
			{
				int Element;

				cout << "Dodaj element na koniec: ";
				cin >> Element;

				// Kopia do prowadzenia badań
				DataStructure<int>* Copy = PickedDataStructure->Clone();

				if (SinglyLinkedList<int>* SLL = dynamic_cast<SinglyLinkedList<int>*>(PickedDataStructure))
				{
					NumOfIterations = 10000;
				}

				auto OperationStart = chrono::high_resolution_clock::now();
				for (unsigned int i = 0; i < NumOfIterations; i++)
				{
					Copy->PushBack(Element);
				}
				auto OperationEnd = chrono::high_resolution_clock::now();
				cout << Copy->GetSize();
				delete Copy;

				PickedDataStructure->PushBack(Element);

				//system("cls");
				cout << "Czas wykonywania: " << MeasureTime(OperationStart, OperationEnd) << " ms\n";
				system("pause");
				continue;
			}

			case '4': // Generator liczb potrzebny do pomiarów
			{
				int Element;
				unsigned int Index;

				cout << "Dodaj element: ";
				cin >> Element;

				if (!PickedDataStructure->IsEmpty())
				{
					do
					{
						cout << "Podaj indeks (0 - " << PickedDataStructure->GetSize() << "): ";
						cin >> Index;
					} while (Index < 0 || Index > PickedDataStructure->GetSize());
				}
				else
				{
					PickedDataStructure->PushFront(Element);
					continue;
				}

				
				if (Index < PickedDataStructure->GetSize())
				{
					PickedDataStructure->Insert(Element, Index);
				}
				else
				{
					PickedDataStructure->PushBack(Element);
				}
				// Po dodaniu generatora liczb
				/*system("cls");
				cout << "Czas wykonywania: " << MeasureTime(OperationStart, OperationEnd) << " ms\n";
				system("pause");*/
				continue;
			}

			case '5':
			{
				if (!PickedDataStructure->IsEmpty())
				{
					// Kopia do prowadzenia badań
					DataStructure<int>* Copy = PickedDataStructure->Clone();

					auto OperationStart = chrono::high_resolution_clock::now();
					for (unsigned int i = 0; i < NumOfIterations; i++)
					{
						Copy->PopFront();
					}
					auto OperationEnd = chrono::high_resolution_clock::now();
					delete Copy;

					PickedDataStructure->PopFront();

					system("cls");
					cout << "Czas wykonywania: " << MeasureTime(OperationStart, OperationEnd) << " ms\n";
					system("pause");
				}
				continue;
			}

			case '6':
			{
				if (!PickedDataStructure->IsEmpty())
				{
					// Kopia do prowadzenia badań
					DataStructure<int>* Copy = PickedDataStructure->Clone();

					auto OperationStart = chrono::high_resolution_clock::now();
					for (unsigned int i = 0; i < NumOfIterations; i++)
					{
						Copy->PopBack();
					}
					auto OperationEnd = chrono::high_resolution_clock::now();
					delete Copy;

					PickedDataStructure->PopBack();

					system("cls");
					cout << "Czas wykonywania: " << MeasureTime(OperationStart, OperationEnd) << " ms\n";
					system("pause");
				}
				continue;
			}

			case '7': // Generator liczb potrzebny do badań
			{
				unsigned int Index;
				
				if (!PickedDataStructure->IsEmpty())
				{
					do
					{
						cout << "Podaj indeks (0 - " << PickedDataStructure->GetSize() - 1 << ") : ";
						cin >> Index;
					} while (Index < 0 || Index >= PickedDataStructure->GetSize());

					PickedDataStructure->RemoveAt(Index);
				}
				// Po dodaniu generatora liczb
				/*system("cls");
				cout << "Czas wykonywania: " << MeasureTime(OperationStart, OperationEnd) << " ms\n";
				system("pause");*/
				continue;
			}

			case '8':
			{
				if (DoublyLinkedList<int>* DLL = dynamic_cast<DoublyLinkedList<int>*>(PickedDataStructure))
				{
					char Choice;
					do
					{
						cout << "Wybierz kierunek przeszukiwania (1 - od początku do końca, 2 - od końca do początku): ";
						cin >> Choice;
					} while (Choice != '1' && Choice != '2');

					int Element;

					cout << "Podaj element: ";
					cin >> Element;

					system("cls");
					cout << "Szukam \"" << Element << "\" w strukturze...\n";
					switch (Choice)
					{
					case '1':
					{
						auto OperationStart = chrono::high_resolution_clock::now();
						NumOfIterations = DLL->SearchForElementForward(Element);
						auto OperationEnd = chrono::high_resolution_clock::now();

						system("cls");
						cout << "Znaleziono " << NumOfIterations << " wystąpienie/wystąpień \"" << Element << "\" w strukturze\n";
						cout << "Czas wykonywania: " << MeasureTime(OperationStart, OperationEnd) << " ms\n";
						system("pause");
						break;
					}

					case '2':
					{
						auto OperationStart = chrono::high_resolution_clock::now();
						NumOfIterations = DLL->SearchForElementBackward(Element);
						auto OperationEnd = chrono::high_resolution_clock::now();

						system("cls");
						cout << "Znaleziono " << NumOfIterations << " wystąpienie/wystąpień \"" << Element << "\" w strukturze\n";
						cout << "Czas wykonywania: " << MeasureTime(OperationStart, OperationEnd) << " ms\n";
						system("pause");
						break;
					}
					}
				}
				else
				{
					int Element;

					cout << "Podaj element: ";
					cin >> Element;

					system("cls");
					cout << "Szukam \"" << Element << "\" w strukturze...\n";

					// Prowadzenie badań
					auto OperationStart = chrono::high_resolution_clock::now();
					NumOfIterations = PickedDataStructure->SearchForElementForward(Element);
					auto OperationEnd = chrono::high_resolution_clock::now();

					system("cls");
					cout << "Znaleziono " << NumOfIterations << " wystąpienie/wystąpień \"" << Element << "\" w strukturze\n";
					cout << "Czas wykonywania: " << MeasureTime(OperationStart, OperationEnd) << " ms\n";
					system("pause");
				}
				continue;
			}

			case '9':
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

