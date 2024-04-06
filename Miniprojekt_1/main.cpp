#include <iostream>
#include <chrono>
#include "Public/DataStructure.h"
#include "Public/ArrayList.h"
#include "Public/SinglyLinkedList.h"
#include "Public/SinglyLinkedListHeadTail.h"
#include "Public/DoublyLinkedList.h"
#include "Public/DataGenerator.h"

using namespace std;

// Pomiar czasu wykonywania
static long long MeasureTime(const chrono::steady_clock::time_point Start, const chrono::steady_clock::time_point End)
{
	auto Duration = chrono::duration_cast<chrono::microseconds>(End - Start);
	return Duration.count();
}

int main()
{
	setlocale(LC_ALL, "pl_PL"); // Ustawienie języka polskiego

	char DataStructureType; // Opcja menu głownego
	char StructureOption;	// Opcja menu funkcji
	unsigned int Capacity = 0; // Domyślna pojemność ArrayList

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
				cout << "Wybierz operację:\n0. Wygeneruj dane\n1. Wyświetl rozmiar\n2. Dodaj element na początku\n3. Dodaj element na końcu\n4. Dodaj element w wybranym miejscu\n5. Usuń element z przodu\n6. Usuń element na końcu\n7. Usuń element w wybranym miejscu\n8. Wyszukaj element w strukturze\n9. Cofnij\n";
				if (PickedDataStructure->IsEmpty())
				{
					cout << "Brak elementów!\n";
				}
				cin >> StructureOption;
			} while (StructureOption != '0' && StructureOption != '1' && StructureOption != '2' && StructureOption != '3' && StructureOption != '4' && StructureOption != '5' && StructureOption != '6' && StructureOption != '7' && StructureOption != '8' && StructureOption != '9');

			switch (StructureOption)
			{
			case '0':
				unsigned int NumOfData;
				int MinData;
				int MaxData;
				do
				{
					cout << "Ile danych wygenerować?: ";
					cin >> NumOfData;
					cout << "Podaj najmniejszą możliwą liczbę do wygenerowania: ";
					cin >> MinData;
					cout << "Podaj największą możliwą liczbę do wygenerowania: ";
					cin >> MaxData;
				} while (NumOfData <= 0 || MinData < -2147483647 || MinData > 2147483647 || MaxData > 2147483647 || MaxData < -2147483647 || MinData > MaxData);

				for (unsigned int i = 0; i < NumOfData; i++)
				{
					PickedDataStructure->PushBack(GenerateRandomNumber(MinData, MaxData));
				}
				continue;

			case '1':
				cout << "Rozmiar: " << PickedDataStructure->GetSize() << endl;
				system("pause");
				continue;

			case '2':
			{
				int Element;
				chrono::steady_clock::time_point OperationStart;
				chrono::steady_clock::time_point OperationEnd;

				char InitializationType; // Wybór rodzaju wprowadzenia liczby
				do
				{
					cout << "Wybierz sposób wprowadzenia danych (1 - wprowadź ręcznie, 2 - wygeneruj losowo (zakres int)): ";
					cin >> InitializationType;
				} while (InitializationType != '1' && InitializationType != '2');

				switch (InitializationType)
				{
				case '1':
					cout << "Podaj element: ";
					cin >> Element;
					break;

				case '2':
					Element = GenerateRandomNumber(-2147483647, 2147483647);
					break;
				}

				{
					// Kopia do prowadzenia badań
					DataStructure<int>* Copy = PickedDataStructure->Clone();

					// Prowadzenie badań
					OperationStart = chrono::high_resolution_clock::now();
					for (unsigned int i = 0; i < NumOfIterations; i++)
					{
						Copy->PushFront(Element);
					}
					OperationEnd = chrono::high_resolution_clock::now();
					delete Copy;

					PickedDataStructure->PushFront(Element);

					system("cls");
					cout << "Czas wykonywania: " << MeasureTime(OperationStart, OperationEnd) << " mikrosekund\n";
					system("pause");
					continue;
				}
			}

			case '3':
			{
				int Element;
				chrono::steady_clock::time_point OperationStart;
				chrono::steady_clock::time_point OperationEnd;

				char InitializationType; // Wybór rodzaju wprowadzenia liczby
				do
				{
					cout << "Wybierz sposób wprowadzenia danych (1 - wprowadź ręcznie, 2 - wygeneruj losowo (zakres int)): ";
					cin >> InitializationType;
				} while (InitializationType != '1' && InitializationType != '2');

				switch (InitializationType)
				{
				case '1':
					cout << "Podaj element: ";
					cin >> Element;
					break;

				case '2':
					Element = GenerateRandomNumber(-2147483647, 2147483647);
					break;
				}

				// Kopia do prowadzenia badań
				DataStructure<int>* Copy = PickedDataStructure->Clone();

				if (SinglyLinkedList<int>* SLL = dynamic_cast<SinglyLinkedList<int>*>(PickedDataStructure))
				{
					NumOfIterations = 10000;
				}

				OperationStart = chrono::high_resolution_clock::now();
				for (unsigned int i = 0; i < NumOfIterations; i++)
				{
					Copy->PushBack(Element);
				}
				OperationEnd = chrono::high_resolution_clock::now();
				delete Copy;

				PickedDataStructure->PushBack(Element);

				//system("cls");
				cout << "Czas wykonywania: " << MeasureTime(OperationStart, OperationEnd) << " mikrosekund\n";
				system("pause");
				continue;
			}

			case '4': // Generator liczb potrzebny do pomiarów
			{
				int Element;
				unsigned int Index;
				chrono::steady_clock::time_point OperationStart;
				chrono::steady_clock::time_point OperationEnd;

				char InitializationType; // Wybór rodzaju wprowadzenia liczby
				do
				{
					cout << "Wybierz sposób wprowadzenia danych (1 - wprowadź ręcznie, 2 - wygeneruj losowo): ";
					cin >> InitializationType;
				} while (InitializationType != '1' && InitializationType != '2');

				switch (InitializationType)
				{
				case '1':
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
						OperationStart = chrono::high_resolution_clock::now();
						PickedDataStructure->PushFront(Element);
						OperationEnd = chrono::high_resolution_clock::now();
					}

				case '2':
					Element = GenerateRandomNumber();
					Index = GenerateRandomNumber(0, PickedDataStructure->GetSize() - 1);
					break;
				}

				if (Index < PickedDataStructure->GetSize())
				{
					OperationStart = chrono::high_resolution_clock::now();
					PickedDataStructure->Insert(Element, Index);
					OperationEnd = chrono::high_resolution_clock::now();
				}
				else
				{
					OperationStart = chrono::high_resolution_clock::now();
					PickedDataStructure->PushBack(Element);
					OperationEnd = chrono::high_resolution_clock::now();
				}
				
				system("cls");
				cout << "Czas wykonywania: " << MeasureTime(OperationStart, OperationEnd) << " mikrosekund\n";
				system("pause");
				continue;
			}

			case '5':
			{
				chrono::steady_clock::time_point OperationStart;
				chrono::steady_clock::time_point OperationEnd;

				if (!PickedDataStructure->IsEmpty())
				{
					// Kopia do prowadzenia badań
					DataStructure<int>* Copy = PickedDataStructure->Clone();

					// Prowadzenie badań
					OperationStart = chrono::high_resolution_clock::now();
					for (unsigned int i = 0; i < NumOfIterations; i++)
					{
						Copy->PopFront();
					}
					OperationEnd = chrono::high_resolution_clock::now();
					delete Copy;

					PickedDataStructure->PopFront();

					system("cls");
					cout << "Czas wykonywania: " << MeasureTime(OperationStart, OperationEnd) << " mikrosekund\n";
					system("pause");
				}
				continue;
			}

			case '6':
			{
				chrono::steady_clock::time_point OperationStart;
				chrono::steady_clock::time_point OperationEnd;

				if (!PickedDataStructure->IsEmpty())
				{
					// Kopia do prowadzenia badań
					DataStructure<int>* Copy = PickedDataStructure->Clone();

					// Prowadzenie badań
					OperationStart = chrono::high_resolution_clock::now();
					for (unsigned int i = 0; i < NumOfIterations; i++)
					{
						Copy->PopBack();
					}
					OperationEnd = chrono::high_resolution_clock::now();
					delete Copy;

					PickedDataStructure->PopBack();

					system("cls");
					cout << "Czas wykonywania: " << MeasureTime(OperationStart, OperationEnd) << " mikrosekund\n";
					system("pause");
				}
				continue;
			}

			case '7': // Generator liczb potrzebny do badań
			{
				unsigned int Index;
				chrono::steady_clock::time_point OperationStart;
				chrono::steady_clock::time_point OperationEnd;

				char InitializationType; // Wybór rodzaju wprowadzenia liczby
				do
				{
					cout << "Wybierz sposób wprowadzenia danych (1 - wprowadź ręcznie, 2 - wygeneruj losowo): ";
					cin >> InitializationType;
				} while (InitializationType != '1' && InitializationType != '2');

				switch (InitializationType)
				{
				case '1':
					cout << "Podaj element: ";
					cin >> Index;
					break;

				case '2':
					Index = GenerateRandomNumber(0, PickedDataStructure->GetSize() - 1);
					break;
				}
				
				if (!PickedDataStructure->IsEmpty())
				{
					do
					{
						cout << "Podaj indeks (0 - " << PickedDataStructure->GetSize() - 1 << ") : ";
						cin >> Index;
					} while (Index < 0 || Index >= PickedDataStructure->GetSize());

					OperationStart = chrono::high_resolution_clock::now();
					PickedDataStructure->RemoveAt(Index);
					OperationEnd = chrono::high_resolution_clock::now();
				}
				// Po dodaniu generatora liczb
				system("cls");
				cout << "Czas wykonywania: " << MeasureTime(OperationStart, OperationEnd) << " mikrosekund\n";
				system("pause");
				continue;
			}

			case '8':
			{
				int Element; // Szukany element
				unsigned int NumOfInstances; // Liczba wystąpień szukanego elementu
				chrono::steady_clock::time_point OperationStart;
				chrono::steady_clock::time_point OperationEnd;

				char InitializationType; // Wybór rodzaju wprowadzenia liczby
				do
				{
					cout << "Wybierz sposób wprowadzenia danych (1 - wprowadź ręcznie, 2 - wygeneruj losowo): ";
					cin >> InitializationType;
				} while (InitializationType != '1' && InitializationType != '2');

				switch (InitializationType)
				{
				case '1':
					cout << "Podaj element: ";
					cin >> Element;
					break;

				case '2':
					Element = GenerateRandomNumber(-2147483647, 2147483647);
					break;
				}

				if (DoublyLinkedList<int>* DLL = dynamic_cast<DoublyLinkedList<int>*>(PickedDataStructure))
				{
					char Choice;
					do
					{
						cout << "Wybierz kierunek przeszukiwania (1 - od początku do końca, 2 - od końca do początku): ";
						cin >> Choice;
					} while (Choice != '1' && Choice != '2');

					system("cls");
					cout << "Szukam \"" << Element << "\" w strukturze...\n";
					switch (Choice)
					{
					case '1':
					{
						// Prowadzenie badań
						OperationStart = chrono::high_resolution_clock::now();
						NumOfInstances = DLL->SearchForElementForward(Element);
						OperationEnd = chrono::high_resolution_clock::now();
						break;
					}

					case '2':
					{
						// Prowadzenie badań
						OperationStart = chrono::high_resolution_clock::now();
						NumOfInstances = DLL->SearchForElementBackward(Element);
						OperationEnd = chrono::high_resolution_clock::now();
						break;
					}
					}
				}
				else
				{
					system("cls");
					cout << "Szukam \"" << Element << "\" w strukturze...\n";

					// Prowadzenie badań
					OperationStart = chrono::high_resolution_clock::now();
					NumOfIterations = PickedDataStructure->SearchForElementForward(Element);
					OperationEnd = chrono::high_resolution_clock::now();
				}
				system("cls");
				cout << "Znaleziono " << NumOfInstances << " wystąpienie/wystąpień \"" << Element << "\" w strukturze\n";
				cout << "Czas wykonywania: " << MeasureTime(OperationStart, OperationEnd) << " mikrosekund\n";
				system("pause");

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

