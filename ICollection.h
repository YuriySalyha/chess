#ifndef iCollection_h
#define iCollection_h

#include "Element.h"

template<class T>
class iCollection
{
public:
	Element<T>* first;
	Element<T>* last;
	iCollection<T>() {
		this->first = nullptr;
		this->last = nullptr;
	}
	virtual T get(int index) = 0;
	virtual void add(T data) = 0;
	virtual T operator [](int index) = 0;

};

#endif // iCollection

