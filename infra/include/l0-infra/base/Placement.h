#ifndef INCL_BASE_PLACEMENT_H
#define INCL_BASE_PLACEMENT_H

#include <string.h>
#include <new>

template <typename T>
struct Placement
{
    Placement& operator=(const T& rhs)
    {
        assignBy(rhs);
        return *this;
    }

    void* alloc()
    {
        //memset(u.buff, 0, sizeof(u));
        return (void*)u.buff;
    }

    T* operator->() const
    {
        return (T*)u.buff;
    }

    T& operator*() const
    {
        return *(T*)u.buff;
    }

    T* getObject() const
    {
        return (T*)u.buff;
    }

    T& getRef() const
    {
        return *(T*)u.buff;
    }

    void destroy()
    {
        getObject()->~T();
    }

private:
    void assignBy(const T& rhs)
    {
        T* p = (T*)alloc();
        *p = rhs;
    }
private:
    union
    {
        char   c;
        short  s;
        int    i;
        long   l;
        float  f;
        double d;
        void*  p;

        char buff[sizeof(T)];
    }u;
};

template <typename T>
struct DefaultPlacement : Placement<T>
{
    T* init()
    {
        return new(Placement<T>::alloc()) T();
    }
};

#endif

