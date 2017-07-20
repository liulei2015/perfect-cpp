#ifndef INCL_STRUCT_OBJECT_H
#define INCL_STRUCT_OBJECT_H

#include <string.h>

template <typename STRUCT_OBJECT>
struct StructObject : STRUCT_OBJECT
{
	StructObject()
	{
		reset();
	}

	void reset()
	{
		memset((void*)this, 0x00, sizeof(STRUCT_OBJECT));
	}

    STRUCT_OBJECT& operator*()
    {
        return *this;
    }

    const STRUCT_OBJECT& operator*() const
    {
        return *this;
    }

    STRUCT_OBJECT* operator->()
    {
        return this;
    }

    const STRUCT_OBJECT* operator->() const
    {
        return this;
    }

    STRUCT_OBJECT* getPointer()
    {
        return this;
    }

    const STRUCT_OBJECT* getPointer() const
    {
        return this;
    }
};

#endif

