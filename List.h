#ifndef List_h
#define List_h
#include "Element.h"
#include "iCollection.h"
template<class T>
class List : public iCollection<T>
{
    Element<T>* current;
    Element<T>* nextToCurrent;
public:
    List<T>()
    {
        this->first = nullptr;
        this->last = nullptr;
    }
    List<T> take(int count, int index = 0) {
        List<T> newList;
        for (int i = 0; i < count; i++) {
            newList.add(get(index));
            index++;
        }
        return newList;
    }
    List<T> orderBy(bool increase = true) {
        List<T> newList;
        int leng = len() + 1;
        int max = 0;
        current = this->first;
        for (int i = 0; i < leng; i++) {
            if (max < current->value && increase == false) {
                max = current->value;
            }
            if (max > current->value && increase == true) {
                max = current->value;
            }
            current = current->next;
        }
        int level;
        if (increase) {
            level = max - 1;
        }
        else {
            level = max + 1;
        }
        for (int j = 0; j < leng - 1; j++) {
            int counter = 1;
            current = this->first;
            int number;
            bool indicator = true;
            for (int i = 0; i < leng; i++) {
                if (indicator) {
                    if (increase && current->value > level) {
                        max = current->value;
                        indicator = false;
                    }
                    if (!increase && current->value < level) {
                        max = current->value;
                        indicator = false;
                    }
                }
                else if (max == current->value) {
                    counter++;
                }
                if (current->value < level && current->value > max && increase == false) {
                    counter = 1;
                    max = current->value;
                }
                if (current->value > level && current->value < max && increase == true) {
                    counter = 1;
                    max = current->value;
                }
                current = current->next;
            }
            for (int q = 0; q < counter; q++) {
                newList.add(max);
            }
            if (increase) {
                level = max + 1;
            }
            else {
                level = max - 1;
            }
        }
        return newList;

    }


    void reassign(T data, int index)
    {
        current = this->first;
        if (index == 0)
        {
            this->first->value = data;
            return;
        }
        for (int i = 0; i < index - 1; i++)
        {
            current = current->next;
        }
        nextToCurrent = current->next;
        Element<T>* item = new Element<T>;
        item->next = nextToCurrent->next;
        item->value = data;
        this->first->value = data;
    }


    void remove(int index)
    {

        nextToCurrent = this->first;
        current = this->first;
        if (index == 0)
        {
            nextToCurrent = this->first->next;
            this->first->value = nextToCurrent->value;
            this->first->next = nextToCurrent->next;

        }
        else
        {
            for (int i = 0; i < index; i++)
            {
                current = current->next;
            }
            nextToCurrent = current->next;

            current->value = nextToCurrent->value;
            current->next = nextToCurrent->next;
        }

    }
    int len() {
        int count = 0;
        if (this->first != nullptr)
        {
            count++;
        }
        Element<T>* current = this->first->next;
        while (current != nullptr)
        {
            count++;
            current = current->next;
        }
        return count;
    }
    void remove(Element<T>* element) {
        int leng = len();
        current = this->first;
        for (int i = 0; i < leng; i++) {
            if (current->next == element->next && current->value == element->value) {
                remove(i);
                return;
            }
            current = current->next;
        }
    }
    void add(T data) override
    {
        if (!this->first)
        {
            this->first = new Element<T>;
            this->first->value = data;
            this->first->next = nullptr;
            this->last = this->first;
        }
        else
        {
            if (this->first == this->last)
            {
                this->last = new Element<T>;
                this->last->value = data;
                this->last->next = nullptr;
                this->first->next = this->last;
            }
            else
            {
                Element<T>* item = new Element<T>;
                item->value = data;
                item->next = nullptr;
                this->last->next = item;
                this->last = item;
            }
        }
    }
    Element<T>* getElement(int index)
    {
        if (index == 0)
        {
            return this->first;
        }
        else
        {
            current = this->first;
            for (int i = 0; i < index; i++)
            {
                current = current->next;
            }
            return current;
        }
    }
    T operator [](int index) override
    {
        return get(index);
    }
private:
    T get(int index) override
    {
        if (index == 0)
        {
            return this->first->value;
        }
        else
        {
            current = this->first;
            for (int i = 0; i < index; i++)
            {
                current = current->next;
            }
            return current->value;
        }
    }
};
#endif