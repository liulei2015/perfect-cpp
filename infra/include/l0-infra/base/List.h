#ifndef INCL_USI_BASE_LIST_H
#define INCL_USI_BASE_LIST_H

#include <stdio.h>
#include "l0-infra/base/apr_ring.h"

template<typename T>
struct List
{
    struct Iterator
    {
        Iterator() : elem(0), next(0)
        {
        }

        Iterator(T* elem) : elem(elem), next(getNext(elem))
        {
        }

        Iterator(const Iterator& rhs) :
            elem(rhs.elem), next(rhs.next)
        {
        }

        Iterator& operator=(const Iterator& rhs)
        {
            elem = rhs.elem;
            next = rhs.next;

            return *this;
        }

        bool operator==(const Iterator& rhs) const
        {
            return elem == rhs.elem;
        }

        bool operator!=(const Iterator& rhs) const
        {
            return !(*this == rhs);
        }

        operator T*()
        {
            return elem;
        }

        void reset()
        {
            elem = 0;
            next = 0;
        }

        bool isNull() const
        {
            return elem == 0;
        }

        T* operator->()
        {
            return elem;
        }

        T& operator*()
        {
            return *elem;
        }

        Iterator operator++(int)
        {
            Iterator i = *this;

            elem = next;
            next = getNext(elem);

            return i;
        }

        Iterator& operator++()
        {
            elem = next;
            next = getNext(elem);

            return *this;
        }

    private:
        static T* getNext(T* elem)
        {
            return elem == 0 ? 0 : List<T>::getNext(elem);
        }
    private:
        T* elem;
        T* next;
    };

    List() : num(0)
    {
        APR_RING_INIT(&head, T, link);
    }

    void pushBack(T& elem)
    {
        APR_RING_INSERT_TAIL(&head, &elem, T, link);
        num++;
    }

    void pushBack(Iterator elem)
    {
        APR_RING_INSERT_TAIL(&head, &(*elem), T, link);
        num++;
    }

    void pushFront(T& elem)
    {
        APR_RING_INSERT_HEAD(&head, &elem, T, link);
        num++;
    }

    void pushFront(Iterator elem)
    {
        APR_RING_INSERT_HEAD(&head, &(*elem), T, link);
        num++;
    }

    void concat(List& another)
    {
        if(another.num == 0) return;

        APR_RING_CONCAT(&head, &another.head, T, link);
        num += another.num;
        another.num = 0;
    }

    Iterator begin() const
    {
        return APR_RING_FIRST(&head);
    }

    Iterator end() const
    {
        return APR_RING_SENTINEL(&head, T, link);
    }

    T* first() const
    {
        return APR_RING_FIRST(&head);
    }

    T* getFirst() const
    {
        return num == 0 ? 0 : APR_RING_FIRST(&head);
    }

    bool isNull(const T* value)
    {
        return value == 0 || value == APR_RING_SENTINEL(&head, T, link);
    }

    T* popFront()
    {
        Iterator i = begin();
        if (i == end())
        {
            return 0;
        }

        erase(i);

        return &(*i);
    }

    void erase(Iterator elem)
    {
        if(elem.isNull()) return;

        APR_RING_REMOVE(&(*elem), link);

        num--;
    }

    void erase(T& elem)
    {
        APR_RING_REMOVE(&elem, link);

        num--;
    }

    bool isEmpty() const
    {
        return APR_RING_EMPTY(&head, T, link);
    }

    void clear()
    {
        while(popFront() != 0);
    }

    unsigned short getSize() const
    {
        return num;
    }

    void reset()
    {
        T* p = 0;

        while(num!=0 && (p = popFront()) != 0)
        {
            delete p;
        }
    }

    struct Visitor
    {
        virtual void visit(T&) = 0;
        virtual ~Visitor() {}
    };

    void visitAll(Visitor& visitor)
    {
        T* end = APR_RING_SENTINEL(&head, T, link);
        for(T* i = first(); i != end; i = i->link.next)
        {
            visitor.visit(*i);
        }
    }


    static T* getNext(T* elem)
    {
        return elem->link.next;
    }

private:
    APR_RING_HEAD(T) head;
    unsigned short num;
};

/////////////////////////////////////////////////////////////
#define LIST_FOREACH_FROM(type, i, from, items) \
    for(List<type>::Iterator i=from; i != items.end(); ++i)

#define LIST_FOREACH(type, i, items) \
   /*lint -e666 */LIST_FOREACH_FROM(type, i, items.begin(), items)

#endif

