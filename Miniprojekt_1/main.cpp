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
	unsigned int NumOfGeneratedData = 0; // Domyślna liczba wygenerowanych danych
	int* GeneratedDateTable;

	system("cls");
	do
	{
		cout << "Podaj ilość wygenerowanych danych: ";
		cin >> NumOfGeneratedData;
	} while (NumOfGeneratedData <= 0);
	GeneratedDateTable = new int[NumOfGeneratedData];
	for (unsigned int i = 0; i < NumOfGeneratedData; i++)
	{
		GeneratedDateTable[i] = GenerateRandomNumber();
	}

	// Menu główne
	while (true)
	{
		do
		{
			system("cls");
			cout << "Liczba wygenerowanych danych: " << NumOfGeneratedData << endl;
			cout << "\nWybierz strukturę danych:\n1. ArrayList\n2. Singly Linked List (head)\n3. Singly Linked List (head & tail)\n4. Doubly Linked List\nq. Wyjdź\n";
			cin >> DataStructureType;
		} while (DataStructureType != '1' && DataStructureType != '2' && DataStructureType != '3' && DataStructureType != '4'&& DataStructureType != 'q');

		DataStructure<int>* PickedDataStructure = nullptr; // Badania prowadzone są na typie int

		if (NumOfGeneratedData <= 0)
		{
			continue;
		}

		switch (DataStructureType)
		{

		case '1':
		{
			PickedDataStructure = new ArrayList<int>(NumOfGeneratedData);
			for (unsigned int i = 0; i < NumOfGeneratedData; i++)
			{
				PickedDataStructure->PushBack(GeneratedDateTable[i]);
			}
			break;
		}

		case '2':
			PickedDataStructure = new SinglyLinkedList<int>();
			for (unsigned int i = 0; i < NumOfGeneratedData; i++)
			{
				PickedDataStructure->PushBack(GeneratedDateTable[i]);
			}
			break;

		case '3':
			PickedDataStructure = new SinglyLinkedList_HeadTail<int>();
			for (unsigned int i = 0; i < NumOfGeneratedData; i++)
			{
				PickedDataStructure->PushBack(GeneratedDateTable[i]);
			}
			break;

		case '4':
		{
			PickedDataStructure = new DoublyLinkedList<int>();
			for (unsigned int i = 0; i < NumOfGeneratedData; i++)
			{
				PickedDataStructure->PushBack(GeneratedDateTable[i]);
			}
			break;
		}

		case 'q':
			return 0;

		default:
			system("cls");
			cout << "Unknown error has occured";
			return 1;
		}

		// Menu operacji
		while (true)
		{
			do
			{
				system("cls");
				cout << "Wybierz operację:\n1. Wyświetl rozmiar\n2. Dodaj element na początku\n3. Dodaj element na końcu\n4. Dodaj element w wybranym miejscu\n5. Usuń element z przodu\n6. Usuń element na końcu\n7. Usuń element w wybranym miejscu\n8. Wyszukaj element w strukturze\n9. Wypisz elementy tablicy\nq. Cofnij\n";
				if (PickedDataStructure->IsEmpty())
				{
					cout << "Brak elementów!\n";
				}
				cin >> StructureOption;
			} while (StructureOption != '0' && StructureOption != '1' && StructureOption != '2' && StructureOption != '3' && StructureOption != '4' && StructureOption != '5' && StructureOption != '6' && StructureOption != '7' && StructureOption != '8' && StructureOption != '9' && StructureOption != 'q');

			switch (StructureOption)
			{
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
				
				system("cls");
				cout << "Pomiar przeprowadzono dla: " << PickedDataStructure->GetSize() << " elementów\n";

				// Prowadzenie badań
				OperationStart = chrono::high_resolution_clock::now();
				PickedDataStructure->PushFront(Element);
				OperationEnd = chrono::high_resolution_clock::now();
				cout << "Czas wykonywania: " << MeasureTime(OperationStart, OperationEnd) << " mikrosekund\n";
				system("pause");
				continue;
				
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

				system("cls");
				cout << "Pomiar przeprowadzono dla: " << PickedDataStructure->GetSize() << " elementów\n";

				// Prowadzenie badań
				OperationStart = chrono::high_resolution_clock::now();
				PickedDataStructure->PushBack(Element);
				OperationEnd = chrono::high_resolution_clock::now();
				cout << "Czas wykonywania: " << MeasureTime(OperationStart, OperationEnd) << " mikrosekund\n";
				system("pause");
				continue;
			}

			case '4':
			{
				int Element;
				unsigned int Index = 0;
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
						// Prowadzenie badań
						OperationStart = chrono::high_resolution_clock::now();
						PickedDataStructure->PushFront(Element);
						OperationEnd = chrono::high_resolution_clock::now();
					}
					break;

				case '2':
					Element = GenerateRandomNumber();
					Index = GenerateRandomNumber(0, PickedDataStructure->GetSize() - 1);
					break;
				}

				if (Index < PickedDataStructure->GetSize())
				{
					// Prowadzenie badań
					OperationStart = chrono::high_resolution_clock::now();
					PickedDataStructure->Insert(Element, Index);
					OperationEnd = chrono::high_resolution_clock::now();
				}
				else
				{
					// Prowadzenie badań
					OperationStart = chrono::high_resolution_clock::now();
					PickedDataStructure->PushBack(Element);
					OperationEnd = chrono::high_resolution_clock::now();
				}

				system("cls");
				cout << "Pomiary dokonano dla " << PickedDataStructure->GetSize() - 1 << " elementów\n";
				cout << "Dodano \n" << Element << "\n w miejscu " << Index << " struktury\n";
				cout << "Czas wykonywania: " << MeasureTime(OperationStart, OperationEnd) << " mikrosekund\n";
				system("pause");
				continue;
			}

			case '5':
			{
				if (!PickedDataStructure->IsEmpty())
				{
					chrono::steady_clock::time_point OperationStart;
					chrono::steady_clock::time_point OperationEnd;

					// Prowadzenie badań
					system("cls");
					cout << "Pomiar dokonano dla: " << PickedDataStructure->GetSize() << " elementów\n";

					OperationStart = chrono::high_resolution_clock::now();
					PickedDataStructure->PopFront();
					OperationEnd = chrono::high_resolution_clock::now();

					cout << "Czas wykonywania: " << MeasureTime(OperationStart, OperationEnd) << " mikrosekund\n";
					system("pause");
				}
				continue;
			}

			case '6':
			{
				if (!PickedDataStructure->IsEmpty())
				{
					chrono::steady_clock::time_point OperationStart;
					chrono::steady_clock::time_point OperationEnd;

					system("cls");
					cout << "Pomiar dokonano dla " << PickedDataStructure->GetSize() << " elementów\n";

					// Prowadzenie badań
					OperationStart = chrono::high_resolution_clock::now();
					PickedDataStructure->PopBack();
					OperationEnd = chrono::high_resolution_clock::now();

					cout << "Czas wykonywania: " << MeasureTime(OperationStart, OperationEnd) << " mikrosekund\n";
					system("pause");
				}
				continue;
			}

			case '7':
			{
				unsigned int Index;
				chrono::steady_clock::time_point OperationStart;
				chrono::steady_clock::time_point OperationEnd;

				char InitializationType; // Wybór rodzaju wprowadzenia liczby
				do
				{
					cout << "Wybierz sposób usuwania danych (1 - wprowadź ręcznie, 2 - wygeneruj losowo): ";
					cin >> InitializationType;
				} while (InitializationType != '1' && InitializationType != '2');

				switch (InitializationType)
				{
				case '1':
					if (!PickedDataStructure->IsEmpty())
					{
						do
						{
							cout << "Podaj indeks (0 - " << PickedDataStructure->GetSize() - 1 << ") : ";
							cin >> Index;
						} while (Index < 0 || Index >= PickedDataStructure->GetSize());
					}
					break;

				case '2':
					Index = GenerateRandomNumber(0, PickedDataStructure->GetSize() - 1);
					break;
				}

				unsigned int NumOfElements = PickedDataStructure->GetSize();

				// Prowadzenie badań
				OperationStart = chrono::high_resolution_clock::now();
				PickedDataStructure->RemoveAt(Index);
				OperationEnd = chrono::high_resolution_clock::now();

				system("cls");
				cout << "Pomiar dokonano dla " << NumOfElements << " elementów\n";
				cout << "Usunięto w miejscu " << Index << " struktury\n";
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
					NumOfInstances = PickedDataStructure->SearchForElementForward(Element);
					OperationEnd = chrono::high_resolution_clock::now();
				}
				system("cls");
				cout << "Znaleziono " << NumOfInstances << " wystąpienie/wystąpień \"" << Element << "\" w strukturze\n";
				cout << "Czas wykonywania: " << MeasureTime(OperationStart, OperationEnd) << " mikrosekund\n";
				system("pause");

				continue;
			}

			case '9':
				system("cls");
				PickedDataStructure->PrintData();
				system("pause");
				continue;

			case 'q':
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

