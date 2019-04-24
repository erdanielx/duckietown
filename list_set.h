#ifndef LIST_SET_H
#define LIST_SET_H

#include "doubly_linked_list.h"

template<class T>
class listSet : public DLinkedList<T> {
    public:
        listSet();
        listSet(const listSet<T> &);
        ~listSet(){};
        void prepend(T);
        void append(T);
        void insrt(T, int);
        void insrt(T);
        int exists(T);
};

template<class T> listSet<T>::listSet() : DLinkedList<T>(){}

template<class T> listSet<T>::listSet(const listSet<T> &ls) : DLinkedList<T>(ls){}

template<class T> int listSet<T>::exists(T val) {
    DLL_Node<T> *nd;
    for(nd = this->head; nd != NULL; nd = nd->getNext()) {
        if(val == nd->getVal()) {
            return 1;
        }
    }
    return 0;
}

template<class T> void prepend(T val) {
    if(!this->exists(val)) {
        DLinkedList<T>::prepend(val);
    }
}

template<class T> void append(T val) {
    if(!this->exists(val)) {
        DLinkedList<T>::append(val);
    }
}

template<class T> void insrt(T val, int pos) {
    if(!this->exists(val)) {
        DLinkedList<T>::insrt(val, pos);
    }
}

template<class T> void listSet<T>::insrt(T val) {
    this->prepend(val);
}

#endif // LIST_SET_H
