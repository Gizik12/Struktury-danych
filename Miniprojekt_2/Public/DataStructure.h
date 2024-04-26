#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

class DataStructure
{
public:
    virtual void insert(int e, int p) = 0;
    virtual void extract_max() = 0;
    virtual void peek() = 0;
    virtual void modify_key(int e, int p) = 0;
    virtual void return_size();
protected:
	
};
#endif