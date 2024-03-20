#ifndef ARRAY_LIST
#define ARRAY_LIST

template<typename DataType, unsigned int Capacity>
class ArrayList
{
public:
	// Konstruktor.
	ArrayList();

	// Destruktor.
	~ArrayList();

	// Dodaje element na początku tablicy.
	void PushFront(DataType Element);

	// Dodaje element na końcu tablicy.
	void PushBack(DataType Element);

	// Usuwa element na początku tablicy.
	void PopFront();

	// Usuwa element na końcu tablicy.
	void PopBack();

	// Dodaje element w wybrane miejsce tablicy.
	void Insert(DataType Element, unsigned int Index);

	// Usuwa element w wybranym miejscu tablicy.
	void RemoveAt(unsigned int Index);

	// Szuka podanego elementu w tablicy i zwraca indeks jego pierwszej instancji.
	int SearchForFirstInstance(DataType Element);

	// Sprawdza czy tablica jest pusta.
	bool IsEmpty() { return m_Size ? false : true; }

	// Zwraca liczbę elementów w tablicy.
	unsigned int GetSize() const { return m_Size; }

	// Zwraca maksymalną pojemność tablicy.
	unsigned int GetCapacity() const { return m_Capacity; }

	// Zwraca wartość elementu tablicy o wybranym indeksie.
	DataType GetElementOfIndex(int Index) const { return m_Elements[Index]; }

private:
	unsigned int m_Size;		// Liczba elementów w tablicy.
	unsigned int m_Capacity;	// Maksymalna pojemność tablicy.
	DataType* m_Elements;		// Wskaźnik na pierwszy element tablicy.

	// Dwukrotnie zwiększa pojemność tablicy.
	void DoubleTheCapacity();

	// Dwukrotnie zmniejsza pojemność tablicy.
	void HalveTheCapacity();
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
void ArrayList<DataType, Capacity>::PushFront(DataType Element)
{
	if (m_Size == m_Capacity) // Jeśli tablica jest zapełniona.
	{
		DoubleTheCapacity(); // Dwukrotnie zwiększ pojemność.
	}
	for (unsigned int i = m_Size; i > 0; i--)
	{
		m_Elements[i] = m_Elements[i - 1]; // Przesunięcie wszystkich elementów w prawo.
	}
	m_Elements[0] = Element;
	++m_Size;
}

template<typename DataType, unsigned int Capacity>
void ArrayList<DataType, Capacity>::PushBack(DataType Element)
{
	if (m_Size == m_Capacity) // Jeśli tablica jest zapełniona.
	{
		DoubleTheCapacity(); // Dwukrotnie zwiększ pojemność.
	}
	m_Elements[m_Size] = Element;
	++m_Size;
}
// TODO: Naprawić -> Ostatni element zostaje na końcu tablicy
template<typename DataType, unsigned int Capacity>
void ArrayList<DataType, Capacity>::PopFront()
{
	if (!IsEmpty())
	{
		DataType* ResizedArray = new DataType[m_Capacity]; // Utworzenie tablicy pomocniczej.
		for (unsigned int i = 0; i < m_Size - 1; i++)
		{
			ResizedArray[i] = m_Elements[i + 1];
		}
		m_Elements = ResizedArray;	// Zastąpienie starej tablicy nową tablicą bez elementu na początku.
		--m_Size;

		if (m_Size == m_Capacity / 2) // Jeśli tablica jest w połowie pusta.
		{
			HalveTheCapacity(); // Dwukrotnie zmniejsz pojemność.
		}
	}
}

template<typename DataType, unsigned int Capacity>
void ArrayList<DataType, Capacity>::PopBack()
{
	if (!IsEmpty())
	{
		DataType* ResizedArray = new DataType[m_Capacity]; // Utworzenie tablicy pomocniczej.
		for (unsigned int i = 0; i < m_Size - 1; i++)
		{
			ResizedArray[i] = m_Elements[i];
		}
		m_Elements = ResizedArray;	// Zastąpienie starej tablicy nową tablicą bez elementu na końcu.
		--m_Size;

		if (m_Size == m_Capacity / 2) // Jeśli tablica jest w połowie pusta.
		{
			HalveTheCapacity(); // Dwukrotnie zmniejsz pojemność.
		}
	}
}

template<typename DataType, unsigned int Capacity>
void ArrayList<DataType, Capacity>::Insert(DataType Element, unsigned int Index)
{
	if (Index < m_Size)
	{
		if (m_Size == m_Capacity) // Jeśli tablica jest zapełniona.
		{
			DoubleTheCapacity(); // Dwukrotnie zwiększ pojemność.
		}
		for (unsigned int i = m_Size; i > Index; i--)
		{
			m_Elements[i] = m_Elements[i - 1]; // Przesunięcie elementów o indeksie większym lub równym od podanego w prawo.
		}
		m_Elements[Index] = Element;
		++m_Size;
	}
}

template<typename DataType, unsigned int Capacity>
void ArrayList<DataType, Capacity>::RemoveAt(unsigned int Index)
{
	if (!IsEmpty() && Index < m_Size)
	{
		for (unsigned int i = Index; i < m_Size; i++)
		{
			m_Elements[i] = m_Elements[i + 1]; // Przesunięcie elementów o indeksie większym lub równym od podanego w lewo.
		}
		--m_Size;

		if (m_Size == m_Capacity / 2) // Jeśli tablica jest w połowie pusta.
		{
			HalveTheCapacity(); // Dwukrotnie zmniejsz pojemność.
		}
	}
}

template<typename DataType, unsigned int Capacity>
int ArrayList<DataType, Capacity>::SearchForFirstInstance(DataType Element)
{
	for (unsigned int i = 0; i < m_Size; i++)
	{
		if (m_Elements[i] == Element)
		{
			return i; // Zwraca indeks pierwszej instancji szukanego elementu.
		}
	}

	return -1; // Zwraca błąd./Brak podanego elementu w tablicy.
}

template<typename DataType, unsigned int Capacity>
void ArrayList<DataType, Capacity>::DoubleTheCapacity()
{
	m_Capacity *= 2;
	DataType* ResizedArray = new DataType[m_Capacity]; // Utworzenie tablicy pomocniczej.
	for (unsigned int i = 0; i < m_Size; i++)
	{
		ResizedArray[i] = m_Elements[i];
	}
	m_Elements = ResizedArray;	// Zastąpienie starej tablicy nową tablicą o dwukronie większej pojemności.
}

template<typename DataType, unsigned int Capacity>
void ArrayList<DataType, Capacity>::HalveTheCapacity()
{
	m_Capacity /= 2;
	DataType* ResizedArray = new DataType[m_Capacity]; // Utworzenie tablicy pomocniczej.
	for (unsigned int i = 0; i < m_Size; i++)
	{
		ResizedArray[i] = m_Elements[i];
	}
	m_Elements = ResizedArray;	// Zastąpienie starej tablicy nową tablicą o dwukronie mniejszej pojemności.
}


#endif