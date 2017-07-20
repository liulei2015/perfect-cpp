#ifndef INCL_USI_StlAllocator_H__
#define INCL_USI_StlAllocator_H__

#include "l0-infra/base/BaseTypes.h"
#include "l0-infra/multi-thread/MultiThreadWrapper.h"
#include "l0-infra/allocator/StaticObjectAllocator.h"

template <typename T, WORD32 MAX_ELEM_NUM, WORD32 THREAD_NUM>
struct StlAllocator
{
    typedef size_t    size_type;
    typedef ptrdiff_t difference_type;
    typedef T*        pointer;
    typedef const T*  const_pointer;
    typedef T&        reference;
    typedef const T&  const_reference;
    typedef T         value_type;

    template <class U>
    struct rebind
    {
        typedef StlAllocator<U, MAX_ELEM_NUM, THREAD_NUM> other;
    };

    pointer address (reference value) const
    {
        return &value;
    }
    const_pointer address (const_reference value) const
    {
        return &value;
    }

    StlAllocator()
    {
        getAllocator();
    }

    StlAllocator(const StlAllocator&)
    {
        getAllocator();
    }

    template <class U>
    StlAllocator(const StlAllocator<U, MAX_ELEM_NUM, THREAD_NUM>&)
    {
        getAllocator();
    }

    pointer allocate(size_type size)
    {
        return (pointer)(getAllocator().alloc());
    }

    void deallocate(pointer p, size_type)
    {
        getAllocator().free(p);
    }

    void construct (pointer p, const T& value)
    {
        new((void*)p)T(value);
    }

    void destroy (pointer p)
    {
        p->~T();
    }

    size_type max_size() const
    {
        return MAX_ELEM_NUM + 1;
    }

private:
    typedef StaticObjectAllocator<T, MAX_ELEM_NUM+1> MapAllocator;
    static MapAllocator& getAllocator()
    {
        static MultiThreadWrapper<MapAllocator, THREAD_NUM> objectAllocator;
        return *objectAllocator;
    }
};

template <typename T, WORD32 MAX_ELEM_NUM>
struct SingleStlAllocator
{
    typedef size_t    size_type;
    typedef ptrdiff_t difference_type;
    typedef T*        pointer;
    typedef const T*  const_pointer;
    typedef T&        reference;
    typedef const T&  const_reference;
    typedef T         value_type;

    template <class U>
    struct rebind
    {
        typedef SingleStlAllocator<U, MAX_ELEM_NUM> other;
    };

    pointer address (reference value) const
    {
        return &value;
    }
    const_pointer address (const_reference value) const
    {
        return &value;
    }

    SingleStlAllocator()
    {
        getAllocator();
    }

    SingleStlAllocator(const SingleStlAllocator&)
    {
        getAllocator();
    }

    template <class U>
    SingleStlAllocator(const SingleStlAllocator<U, MAX_ELEM_NUM>&)
    {
        getAllocator();
    }

    pointer allocate(size_type size)
    {
        return (pointer)(getAllocator().alloc());
    }

    void deallocate(pointer p, size_type)
    {
        getAllocator().free(p);
    }

    void construct (pointer p, const T& value)
    {
        new((void*)p)T(value);
    }

    void destroy (pointer p)
    {
        p->~T();
    }

    size_type max_size() const
    {
        return MAX_ELEM_NUM + 1;
    }

private:
    typedef StaticObjectAllocator<T, MAX_ELEM_NUM+1> MapAllocator;
    static MapAllocator& getAllocator()
    {
        static MapAllocator objectAllocator;
        return objectAllocator;
    }
};

#endif

