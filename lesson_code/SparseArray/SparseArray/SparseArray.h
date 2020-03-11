#pragma once
template <class T>
class SparseArray
{
private;
	T nullElem;
	int size;



public:
	template <class T> SparseArray();
	template <class T> SparseArray(int size);

	template <class T> get(int k);
	void set(int k);
	void insert(T elem, int beforeK);
	void remove(int k);
	int getSize();
	

};

