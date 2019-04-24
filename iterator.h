#ifndef ITERATOR_H
#define ITERATOR_H

//Abstract base class for iterators
template<class T>
class Iterator{
    public:
        //Pure virtual methods and non-virtual destructor
        virtual ~Iterator(){};
        virtual bool hasNext() = 0;
        virtual T getNext() = 0;
};
//Abstract base class for iterables
template<class T>
class Iterable{
    public:
        //Pure virtual methods and non-virtual destructor
        virtual ~Iterable(){};
        virtual Iterator<T>* iterator() = 0;
};

template<class T> void foreach(Iterator<T> *it, void (*func) (T)) {
    while(it->hasNext()) {
        func(it->getNext());
    }
    delete it;
}

#endif // ITERATOR_H
