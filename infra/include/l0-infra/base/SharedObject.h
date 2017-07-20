#ifndef INCL_SharedObject_201389202515_H
#define INCL_SharedObject_201389202515_H

struct SharedObject
{
    SharedObject();
    virtual ~SharedObject();
    
    void addRef();
    void subRef();

    unsigned int getRefCount() const;

    bool onlyThisRef() const;

private:
    unsigned int count;
};

#endif
