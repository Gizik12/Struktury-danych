#ifndef DATA_STRUCTURE
#define DATA_STRUCTURE

template<typename DataType>
class DataStructure
{
public:
	// Konstruktor.
	DataStructure();

	// Dodaje element na początku struktury.
	virtual void PushFront(DataType Element) = 0;

	// Dodaje element na końcu struktury.
	virtual void PushBack(DataType Element) = 0;

	// Usuwa element na początku struktury.
	virtual void PopFront() = 0;

	// Usuwa element na końcu struktury.
	virtual void PopBack() = 0;

	// Dodaje element w wybrane miejsce struktury.
	virtual void Insert(DataType Element, unsigned int Index) = 0;

	// Usuwa element w wybranym miejscu struktury.
	virtual void RemoveAt(unsigned int Index) = 0;

	int GetSize() const { return m_Size; }
	
	bool IsEmpty() const { return m_Size ? false : true; }

protected:
	unsigned int m_Size; // Liczba elementów w strukturze.
};

template<typename DataType>
DataStructure<DataType>::DataStructure()
	: m_Size(0) { }

#endif // !DATA_STRUCTURE
