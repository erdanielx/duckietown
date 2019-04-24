#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <iostream>
#include "iterator.h"

//Doubly Linked List Node class definition
template<class T>
class DLL_Node{
    private:
        DLL_Node<T> *prev;
        DLL_Node<T> *next;
        T val;
    public:
        DLL_Node();
        DLL_Node(T);
        DLL_Node(T, DLL_Node<T> *, DLL_Node<T> *);
        DLL_Node(const DLL_Node<T> &);
        ~DLL_Node(){};
        void setPointrs(DLL_Node<T> *, DLL_Node<T> *);
        void setPrev(DLL_Node<T> *);
        void setNext(DLL_Node<T> *);
        T getVal();
        DLL_Node<T>* getPrev();
        DLL_Node<T>* getNext();
};

//Constructors
template<class T> DLL_Node<T>::DLL_Node(){
    this->prev = NULL;
    this->next = NULL;
    this->val = T();
}

template<class T> DLL_Node<T>::DLL_Node(T val){
    this->prev = NULL;
    this->next = NULL;
    this->val = val;
}

template<class T> DLL_Node<T>::DLL_Node(T val, DLL_Node<T> *prev, DLL_Node<T> *next){
    this->prev = prev;
    this->next = next;
    this->val = val;
}

//Copy constructor
template<class T> DLL_Node<T>::DLL_Node(const DLL_Node<T> &dln){
    this->val = dln.val;
    this->prev = NULL;
    this->next = NULL;
}

//Setters
template<class T> void DLL_Node<T>::setPointrs(DLL_Node<T> *prev,DLL_Node<T> *next) {
    this->prev = prev;
    this->next = next;
}

template<class T> void DLL_Node<T>::setPrev(DLL_Node<T> *prev) {
    this->prev = prev;
}

template<class T> void DLL_Node<T>::setNext(DLL_Node<T> *next) {
    this->next = next;
}

//Getters
template<class T>T DLL_Node<T>::getVal() {
    return this->val;
}

template<class T> DLL_Node<T>* DLL_Node<T>::getPrev() {
    return this->prev;
}

template<class T> DLL_Node<T>* DLL_Node<T>::getNext() {
    return this->next;
}

template<class T>
class DLL_Iterator : public virtual Iterator<T> {
    private:
        DLinkedList<T> *lst;
        DLL_Node<T> *next_node;
    public:
        DLL_Iterator();
        DLL_Iterator(const DLL_Iterator<T> &);
        DLL_Iterator(DLinkedList<T>*);
        ~DLL_Iterator(){};
        bool hasNext();
        T getNext();
};

//Doubly Linked List class definition
template<class T>
class DLinkedList : public virtual Iterable<T>{
    protected:
        DLL_Node<T> *head;
        DLL_Node<T> *tail;
        int len;
    public:
        DLinkedList();
        DLinkedList(const DLinkedList<T> &);
        DLinkedList(DLL_Node<T> *);
        DLinkedList(T, int);
        ~DLinkedList();
        DLL_Node<T>* getHead();
        DLL_Node<T>* getTail();
        void prepend(T);
        void append(T);
        void insrt(T, int);
        DLL_Node<T>* getNd(int);
        T getEl(int);
        void del(int);
        int length();
        void swp(int, int);
        void print();
        void swapNodes(DLL_Node<T> *, DLL_Node<T> *);
        template<class F> friend std::ostream& operator<<(std::ostream &, const DLinkedList<F> &);
        DLL_Iterator<T>* iterator();
};

template<class T> DLL_Iterator<T>::DLL_Iterator() {
    this->lst = NULL;
    this->next_node = NULL;
}

template<class T> DLL_Iterator<T>::DLL_Iterator(const DLL_Iterator<T> &dit)  {
    this->lst = dit.lst;
    this->next_node = dit.next_node;
}

template<class T> DLL_Iterator<T>::DLL_Iterator(DLinkedList<T> *lst) {
    this->lst = lst;
    if(this->lst != NULL) {
        this->next_node = this->lst->getHead();
    } else {
        this->next_node = NULL;
    }
}

template<class T> bool DLL_Iterator<T>::hasNext() {
    return (this->next_node != NULL);
}

template<class T> T DLL_Iterator<T>::getNext() {
    if(this->hasNext()) {
        DLL_Node<T> *nd = this->next_node;
        this->next_node = nd->getNext();
        return nd->getVal();
    } else {
        return T();
    }
}

//Empty constructor
template<class T> DLinkedList<T>::DLinkedList() {
    this->head = NULL;
    this->tail = NULL;
    this->len = 0;
}

//Copy constructor
template<class T> DLinkedList<T>::DLinkedList(const DLinkedList<T> &dl) {
    DLL_Node<T> *nd;
    DLL_Node<T> *curr;
    DLL_Node<T> *prev;
    int i = 0;
    //Copy each node into a new one and set pointers to previous and next nodes
    for(nd = dl.head; nd != NULL; nd = nd->getNext()) {
        curr = new DLL_Node<T>(*nd);
        if(nd == dl.head) {
            this->head = curr;
            curr->setPrev(NULL);
        } else {
            prev->setNext(curr);
            curr->setPrev(prev);
        }
        if(nd == dl.tail) {
            this->tail = curr;
            curr->setNext(NULL);
        }
        prev = curr;
        i++;
    }
    this->len = i;
    if(i == 0) {
        this->head = NULL;
        this->tail = NULL;
    }
}

//More constructors
template<class T> DLinkedList<T>::DLinkedList(DLL_Node<T> *nd) {
    this->head = nd;
    if(nd->getPrev() != NULL) {
        nd->setPrev(NULL);
    }
    DLL_Node<T> *n;
    int i = 0;
    for(n = nd; n->getNext() != NULL; n = n->getNext()) {
        i++;
    }
    this->tail = n;
    this->len = i;
}

template<class T> DLinkedList<T>::DLinkedList(T val, int siz) {
    int i;
    DLL_Node<T> *curr;
    DLL_Node<T> *prev;
    for(i = 0; i < siz; i++) {
        curr = new DLL_Node<T>(val);
        if(i != 0) {
            prev->setNext(curr);
            curr->setPrev(prev);
        } else {
            this->head = curr;
            curr->setPrev(NULL);
        }
        prev = curr;
        if(i+1 == siz) {
            this->tail = curr;
            curr->setNext(NULL);
        }
    }
    this->len = siz;
}

//Destructor
template<class T> DLinkedList<T>::~DLinkedList() {
    DLL_Node<T> *curr = this->head;
    DLL_Node<T> *tmp;
    //Free memory for all nodes
    while(curr != NULL) {
        tmp = curr;
        curr = curr->getNext();
        delete tmp;
    }
}

//Getters
template<class T> DLL_Node<T>* DLinkedList<T>::getHead() {
    return this->head;
}

template<class T> DLL_Node<T>* DLinkedList<T>::getTail() {
    return this->tail;
}

//Prepend a value to the list
template<class T> void DLinkedList<T>::prepend(T val) {
    DLL_Node<T> *nd = new DLL_Node<T>(val);
    DLL_Node<T> *tmp;
    if(this->head == NULL) {
        this->tail = nd;
        nd->setNext(NULL);
    } else {
        tmp = this->head;
        nd->setNext(tmp);
        tmp->setPrev(nd);
    }
    this->head = nd;
    nd->setPrev(NULL);
    this->len++;
}

//Append a value to the list
template<class T> void DLinkedList<T>::append(T val) {
    if(this->head == NULL) {
        this->prepend(val);
    } else {
        DLL_Node<T> *nd = new DLL_Node<T>(val);
        DLL_Node<T> *prev_tl = this->tail;
        nd->setPrev(prev_tl);
        prev_tl->setNext(nd);
        nd->setNext(NULL);
        this->tail = nd;
    }
    this->len++;
}

//Insert a value at a position
template<class T> void DLinkedList<T>::insrt(T val, int pos) {
    if(pos < 0 || pos > this->len) {
        return;
    }
    if(pos == 0) {
        this->prepend(val);
    } else if (pos == this->len) {
        this->append(val);
    } else {
        DLL_Node<T> *prev;
        DLL_Node<T> *aft;
        DLL_Node<T> *nd;
        //Move to position depending on if it is closer to the end or to the beginning
        if(pos <= this->len/2) {
            int i = 0;
            for(prev = this->head; i < pos - 1; prev = prev->getNext()) {
                i++;
            }
            aft = prev->getNext();
        } else {
            int i = this->len - 1;
            for(aft = this->tail; i > pos + 1; aft = aft->getPrev()) {
                i--;
            }
            prev = aft->getPrev();
        }
        //Create node holding the value and insert it in the position
        nd = new DLL_Node<T>(val);
        prev->setNext(nd);
        nd->setPrev(prev);
        aft->setPrev(nd);
        nd->setNext(aft);
    }
}

//Return a node pointer to the node at a given position
template<class T> DLL_Node<T>* DLinkedList<T>::getNd(int pos) {
    if(pos < 0 || pos > this->len) {
        return NULL;
    }
    if(pos == 0) {
        return this->head;
    } else if(pos == this->len - 1) {
        return this->tail;
    } else {
        DLL_Node<T> *curr;
        //Move to position depending on if it is closer to the end or to the beginning
        if(pos <= this->len/2) {
            int i = 0;
            for(curr = this->head; i < pos; curr = curr->getNext()) {
                i++;
            }
        } else {
            int i = this->len - 1;
            for(curr = this->tail; i > pos + 1; curr = curr->getPrev()) {
                i--;
            }
        }
        return curr;
    }
}

//Return the value at a certain position of the list
template<class T> T DLinkedList<T>::getEl(int pos) {
    return this->getNd(pos)->getVal();
}

//Delete a node at a certain position in the list
template<class T> void DLinkedList<T>::del(int pos) {
    if(pos < 0 || pos > this->len - 1) {
        return;
    }
    DLL_Node<T> *curr;
    if(pos == 0) {
        curr = this->head;
        this->head = curr->getNext();
        if(this->head != NULL) {
            this->head->setPrev(NULL);
        }
    } else if(pos == this->len - 1) {
        curr = this->tail;
        this->tail = curr->getPrev();
        if(this->tail != NULL) {
            this->tail->setNext(NULL);
        }

    } else {
        //Move to position depending on if it is closer to the end or to the beginning
        if(pos <= this->len/2) {
            int i = 0;
            for(curr = this->head; i < pos; curr = curr->getNext()) {
                i++;
            }
        } else {
            int i = this->len - 1;
            for(curr = this->tail; i > pos; curr = curr->getPrev()) {
                i--;
            }
        }
        DLL_Node<T> *prev = curr->getPrev();
        DLL_Node<T> *next = curr->getNext();
        prev->setNext(next);
        next->setPrev(prev);
        delete curr;
    }
}

//Get the  length of the list
template<class T> int DLinkedList<T>::length() {
    return this->len;
}

//Swap two nodes given their position
template<class T> void DLinkedList<T>::swp(int pos1, int pos2) {
    if(pos1 == pos2){
        return;
    }
    if(pos1 < 0 || pos2 < 0 || pos1 > this->len - 1 || pos2 > this->len - 1) {
        return;
    }
    DLL_Node<T> *nd1 = this->getNd(pos1);
    DLL_Node<T> *nd2 = this->getNd(pos2);
    swapNodes(nd1, nd2);
}

//Print the list to the standard output with spaces in-between elements
template<class T> void DLinkedList<T>::print() {
    DLL_Node<T> *nd;
    for(nd = this->head; nd != NULL; nd = nd->getNext()) {
        std::cout << nd->getVal() << " ";
    }
}

//Swap two nodes given pointers to them, faster than swp
template<class T> void DLinkedList<T>::swapNodes(DLL_Node<T> *nd1, DLL_Node<T> *nd2) {
    if(nd1 == nd2 || nd1 == NULL || nd2 == NULL) {
        return;
    }
    if(this->head == nd1) {
        this->head = nd2;
    } else if (this->head == nd2) {
        this->head = nd1;
    }
    if(this->tail == nd1) {
        this->tail = nd2;
    } else if (this->tail == nd2) {
        this->tail = nd1;
    }
    //Set pointers accordingly
    DLL_Node<T> *nd1_prev = nd1->getPrev();
    DLL_Node<T> *nd1_aft = nd1->getNext();
    DLL_Node<T> *nd2_prev = nd2->getPrev();
    DLL_Node<T> *nd2_aft = nd2->getNext();
    if(nd1_prev == nd2) {
        nd1->setNext(nd2);
        nd2->setPrev(nd1);
    } else {
        if(nd1_prev != NULL) {
            nd1_prev->setNext(nd2);
            nd2->setPrev(nd1_prev);
        } else {
            nd2->setPrev(NULL);
        }
        if(nd2_aft != NULL) {
            nd2_aft->setPrev(nd1);
            nd1->setNext(nd2_aft);
        } else {
            nd1->setNext(NULL);
        }
    }
    if(nd1_aft == nd2) {
        nd2->setNext(nd1);
        nd1->setPrev(nd2);
    } else {
        if(nd1_aft != NULL) {
            nd1_aft->setPrev(nd2);
            nd2->setNext(nd1_aft);
        } else {
            nd2->setNext(NULL);
        }
        if(nd2_prev != NULL) {
            nd2_prev->setNext(nd1);
            nd1->setPrev(nd2_prev);
        } else {
            nd1->setPrev(NULL);
        }
    }
}

//Overloaded << operator for printing
template<class T>
std::ostream& operator<<(std::ostream &out, const DLinkedList<T> &dll) {
    DLL_Node<T> *nd;
    for(nd = dll.head; nd != NULL; nd = nd->getNext()) {
        out << nd->getVal() << " ";
    }
    out << std::endl;
    return out;
}

template<class T> DLL_Iterator<T>* DLinkedList<T>::iterator() {
    DLL_Iterator<T> *it = new DLL_Iterator<T>(this);
    return it;
}

#endif // DOUBLY_LINKED_LIST_H
