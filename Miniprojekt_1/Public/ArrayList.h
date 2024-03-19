#ifndef ARRAY_LIST
#define ARRAY_LIST

template<typename DataType, unsigned int Capacity>
class ArrayList
{
public:
	// Konstruktor
	ArrayList();
	
	// Destruktor
	~ArrayList();

	// Dodaje element na końcu tablicy.
	void Add(DataType Element);

	// Dodaje element na początku tablicy.
	void AddInFront(DataType Element);

	// Dodaje element w wybrane miejsce tablicy.
	void AddToIndex(DataType Element, int Index);

	// Szuka podanego elementu w tablicy i zwraca indeks jego pierwszej instancji.
	int SearchForFirstInstance(DataType Element);

	// Zwraca liczbę elementów w tablicy.
	int GetSize() const { return m_Size; }

	// Zwraca maksymalną pojemność tablicy.
	int GetCapacity() const { return m_Capacity; }

	// Zwraca wartość elementu tablicy o podanym indeksie.
	DataType GetElementOfIndex(int Index) const { return m_Elements[Index]; }

private:
	unsigned int m_Size;		// Liczba elementów w tablicy.
	unsigned int  m_Capacity;	// Maksymalna pojemność tablicy.
	DataType* m_Elements;		// Wskaźnik na pierwszy element tablicy.

	// Dwukrotnie zwiększa pojemność tablicy.
	void DoubleTheCapacity();
};


template<typename DataType, unsigned int Capacity>
ArrayList<DataType, Capacity>::ArrayList()
	: m_Size(0), m_Capacity(Capacity), m_Elements(nullptr)
{
	m_Elements = new DataType[m_Capacity];
}

template<typename DataType, unsigned int Capacity>
ArrayList<DataType, Capacity>::~ArrayList()
{
	if (m_Elements != nullptr)
	{
		delete[] m_Elements;
	}
}

template<typename DataType, unsigned int Capacity>
void ArrayList<DataType, Capacity>::Add(DataType Element)
{
	if (m_Size == m_Capacity) // Jeśli tablica jest zapełniona.
	{
		DoubleTheCapacity(); // Dwukrotnie zwiększa pojemność.
	}
	m_Elements[m_Size] = Element;
	++m_Size;
}

template<typename DataType, unsigned int Capacity>
void ArrayList<DataType, Capacity>::AddInFront(DataType Element)
{
	if (m_Size == m_Capacity) // Jeśli tablica jest zapełniona.
	{
		DoubleTheCapacity(); // Dwukrotnie zwiększ pojemność.
	}
	for (int i = m_Size; i > 0; i--)
	{
		m_Elements[i] = m_Elements[i - 1]; // Przesunięcie wszystkich elementów w prawo.
	}
	m_Elements[0] = Element;
	++m_Size;
}

template<typename DataType, unsigned int Capacity>
void ArrayList<DataType, Capacity>::AddToIndex(DataType Element, int Index)
{
	if (m_Size == m_Capacity) // Jeśli tablica jest zapełniona.
	{
		DoubleTheCapacity(); // Dwukrotnie zwiększ pojemność.
	}
	for (int i = m_Size; i > Index; i--)
	{
		m_Elements[i] = m_Elements[i - 1]; // Przesunięcie elementów o indeksie większym lub równym od podanego w prawo.
	}
	m_Elements[Index] = Element;
	++m_Size;
}

template<typename DataType, unsigned int Capacity>
int ArrayList<DataType, Capacity>::SearchForFirstInstance(DataType Element)
{
	for (int i = 0; i < m_Size; i++)
	{
		if (m_Elements[i] == Element)
		{
			return i; // Zwraca indeks pierwszej instancji szukanego elementu.
		}
	}

	return -1; // Zwraca błąd/Brak podanego elementu w tablicy.
}

template<typename DataType, unsigned int Capacity>
void ArrayList<DataType, Capacity>::DoubleTheCapacity()
{
	m_Capacity *= 2;
	DataType* ResizedArray = new DataType[m_Capacity]; // Utworzenie tablicy pomocniczej.
	for (int i = 0; i < m_Size; i++)
	{
		ResizedArray[i] = m_Elements[i];
	}
	m_Elements = ResizedArray;	// Zastąpienie starej tablicy nową tablicą o dwukronie większej pojemności.
}


#endif