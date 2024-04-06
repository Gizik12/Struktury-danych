#include "DataStructure.h"
#ifndef ARRAY_LIST
#define ARRAY_LIST

template<typename DataType>
class ArrayList final : public DataStructure<DataType>
{
public:
	// Konstruktor.
	ArrayList(unsigned int Capacity);

	// Destruktor.
	~ArrayList();

	// Dodaje element na początku tablicy.
	virtual void PushFront(DataType Element) override;

	// Dodaje element na końcu tablicy.
	virtual void PushBack(DataType Element) override;

	// Usuwa element na początku tablicy.
	virtual void PopFront() override;

	// Usuwa element na końcu tablicy.
	virtual void PopBack() override;

	// Dodaje element w wybrane miejsce tablicy.
	virtual void Insert(DataType Element, unsigned int Index) override;

	// Usuwa element w wybranym miejscu tablicy.
	virtual void RemoveAt(unsigned int Index) override;

	// Przeszukuje strukturę od początku do końca w celu znalezienia wybranego elementu w strukturze i zwraca liczbę jego wystąpień
	virtual unsigned int SearchForElementForward(DataType Element) override;

	// Tworzy kopie struktury (stosowane w badaniach)
	virtual DataStructure<DataType>* Clone() const override { return new ArrayList(m_Capacity); }

	// Zwraca maksymalną pojemność tablicy.
	unsigned int GetCapacity() const { return m_Capacity; }

	// Zwraca wartość elementu tablicy o wybranym indeksie.
	DataType GetElementOfIndex(int Index) const { return m_Elements[Index]; }

private:
	unsigned int m_Capacity;	// Maksymalna pojemność tablicy.
	DataType* m_Elements;		// Wskaźnik na pierwszy element tablicy.

	// Dwukrotnie zwiększa pojemność tablicy.
	void DoubleTheCapacity();

	// Dwukrotnie zmniejsza pojemność tablicy.
	void HalveTheCapacity();
};


template<typename DataType>
ArrayList<DataType>::ArrayList(unsigned int Capacity)
	: m_Capacity(Capacity), m_Elements(nullptr)
{
	if (m_Capacity > 0)
	{
		m_Elements = new DataType[m_Capacity];
	}
}

template<typename DataType>
ArrayList<DataType>::~ArrayList()
{
	if (m_Elements != nullptr)
	{
		delete[] m_Elements;
	}
}

template<typename DataType>
void ArrayList<DataType>::PushFront(DataType Element)
{
	if (DataStructure<DataType>::m_Size >= m_Capacity) // Jeśli tablica jest zapełniona.
	{
		DoubleTheCapacity(); // Dwukrotnie zwiększ pojemność.
	}
	for (unsigned int i = DataStructure<DataType>::m_Size; i > 0; i--)
	{
		m_Elements[i] = m_Elements[i - 1]; // Przesunięcie wszystkich elementów w prawo.
	}
	m_Elements[0] = Element;
	++DataStructure<DataType>::m_Size;
}

template<typename DataType>
void ArrayList<DataType>::PushBack(DataType Element)
{
	if (DataStructure<DataType>::m_Size >= m_Capacity) // Jeśli tablica jest zapełniona.
	{
		DoubleTheCapacity(); // Dwukrotnie zwiększ pojemność.
	}
	m_Elements[DataStructure<DataType>::m_Size] = Element;
	++DataStructure<DataType>::m_Size;
}

template<typename DataType>
void ArrayList<DataType>::PopFront()
{
	if (!ArrayList<DataType>::IsEmpty())
	{
		DataType* ResizedArray = new DataType[m_Capacity]; // Utworzenie tablicy pomocniczej.
		for (unsigned int i = 0; i < DataStructure<DataType>::m_Size - 1; i++)
		{
			ResizedArray[i] = m_Elements[i + 1];
		}
		m_Elements = ResizedArray;	// Zastąpienie starej tablicy nową tablicą bez elementu na początku.
		--DataStructure<DataType>::m_Size;

		if (DataStructure<DataType>::m_Size <= m_Capacity / 2) // Jeśli tablica jest w połowie pusta.
		{
			HalveTheCapacity(); // Dwukrotnie zmniejsz pojemność.
		}
	}
}

template<typename DataType>
void ArrayList<DataType>::PopBack()
{
	if (!ArrayList<DataType>::IsEmpty())
	{
		DataType* ResizedArray = new DataType[m_Capacity]; // Utworzenie tablicy pomocniczej.
		for (unsigned int i = 0; i < DataStructure<DataType>::m_Size - 1; i++)
		{
			ResizedArray[i] = m_Elements[i];
		}
		m_Elements = ResizedArray;	// Zastąpienie starej tablicy nową tablicą bez elementu na końcu.
		--DataStructure<DataType>::m_Size;

		if (DataStructure<DataType>::m_Size <= m_Capacity / 2) // Jeśli tablica jest w połowie pusta.
		{
			HalveTheCapacity(); // Dwukrotnie zmniejsz pojemność.
		}
	}
}

template<typename DataType>
void ArrayList<DataType>::Insert(DataType Element, unsigned int Index)
{
	if (Index < DataStructure<DataType>::m_Size)
	{
		if (DataStructure<DataType>::m_Size >= m_Capacity) // Jeśli tablica jest zapełniona.
		{
			DoubleTheCapacity(); // Dwukrotnie zwiększ pojemność.
		}
		for (unsigned int i = DataStructure<DataType>::m_Size; i > Index; i--)
		{
			m_Elements[i] = m_Elements[i - 1]; // Przesunięcie elementów o indeksie większym lub równym od podanego w prawo.
		}
		m_Elements[Index] = Element;
		++DataStructure<DataType>::m_Size;
	}
}

template<typename DataType>
void ArrayList<DataType>::RemoveAt(unsigned int Index)
{
	if (!ArrayList<DataType>::IsEmpty() && Index < DataStructure<DataType>::m_Size)
	{
		for (unsigned int i = Index; i < DataStructure<DataType>::m_Size; i++)
		{
			m_Elements[i] = m_Elements[i + 1]; // Przesunięcie elementów o indeksie większym lub równym od podanego w lewo.
		}
		--DataStructure<DataType>::m_Size;

		if (DataStructure<DataType>::m_Size <= m_Capacity / 2) // Jeśli tablica jest w połowie pusta.
		{
			HalveTheCapacity(); // Dwukrotnie zmniejsz pojemność.
		}
	}
}

template<typename DataType>
unsigned int ArrayList<DataType>::SearchForElementForward(DataType Element)
{
	unsigned int NumOfInstances = 0; // Licznik wystąpień elementu

	for (unsigned int i = 0; i < DataStructure<DataType>::m_Size; i++)
	{
		if (m_Elements[i] == Element)
		{
			NumOfInstances++; // Zwiększa liczbę wystąpień
		}
	}

	return NumOfInstances; // Zwraca liczbę wystąpień elementu w strukturze
}

template<typename DataType>
void ArrayList<DataType>::DoubleTheCapacity()
{
	m_Capacity *= 2;
	DataType* ResizedArray = new DataType[m_Capacity]; // Utworzenie tablicy pomocniczej.
	for (unsigned int i = 0; i < DataStructure<DataType>::m_Size; i++)
	{
		ResizedArray[i] = m_Elements[i];
	}
	m_Elements = ResizedArray;	// Zastąpienie starej tablicy nową tablicą o dwukronie większej pojemności.
}

template<typename DataType>
void ArrayList<DataType>::HalveTheCapacity()
{
	m_Capacity /= 2;
	DataType* ResizedArray = new DataType[m_Capacity]; // Utworzenie tablicy pomocniczej.
	for (unsigned int i = 0; i < DataStructure<DataType>::m_Size; i++)
	{
		ResizedArray[i] = m_Elements[i];
	}
	m_Elements = ResizedArray;	// Zastąpienie starej tablicy nową tablicą o dwukronie mniejszej pojemności.
}


#endif // ARRAY_LIST