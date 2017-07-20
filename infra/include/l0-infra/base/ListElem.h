#ifndef INCL_USI_BASE_LIST_ELEM_H
#define INCL_USI_BASE_LIST_ELEM_H

#include "l0-infra/base/apr_ring.h"

template <typename T> struct List;

template <typename T>
struct ListElem
{
   ListElem()
   {
      link.prev = 0;
      link.next = 0;
   }

   friend struct List<T>;

   APR_RING_ENTRY(T) link;
};

#endif

