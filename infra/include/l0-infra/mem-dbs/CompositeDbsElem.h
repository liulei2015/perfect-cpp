#ifndef INCL_USI_Dbs_CompositeAccessor_H_
#define INCL_USI_Dbs_CompositeAccessor_H_

#include "l0-infra/mem-dbs/DbsElem.h"
#include "l0-infra/trans-dsl/utils/ActionMacroHelper.h"
#include "l0-infra/base/Assertions.h"

////////////////////////////////////////////////////////////////
#define __COMP_DBS_ELEM_MEMBER_DEF(n)  ACTION ## n  m ## n;
#define DECL_COMP_DBS_ELEMS_MEMBERS(n) SIMPLE_REPEAT(n, __COMP_DBS_ELEM_MEMBER_DEF)

//////////////////////////////////////////////////////////////////////////
#define __COMP_DBS_ELEM_ACCESS(n)       m ## n.access(eventId, req, ack)
#define __COMP_DBS_ELEM_ACCESSES(n)      __COMP_DBS_ELEM_ACCESS(n) ||

#define DECL_SMART_DBS_ELEM_ACCESSES(n)  REPEAT(n, __COMP_DBS_ELEM_ACCESSES, __COMP_DBS_ELEM_ACCESS)

//////////////////////////////////////////////////////////////////////////
#define __COMP_DBS_ELEM_LOAD(n)       USI_ASSERT_SUCC_CALL(m ## n.load(param));

#define DECL_SMART_DBS_ELEM_LOADS(n)  SIMPLE_REPEAT(n, __COMP_DBS_ELEM_LOAD)

//////////////////////////////////////////////////////////////////////////
#define __COMP_DBS_ELEM_DUMP(n)       m ## n.dump();

#define DECL_SMART_DBS_ELEM_DUMPS(n)  SIMPLE_REPEAT(n, __COMP_DBS_ELEM_DUMP)

//////////////////////////////////////////////////////////////////////////

#define __COMP_DBS_ELEM_PARTIAL_COLLECTION(n)                               \
namespace details {                                                         \
    template < DECL_TEMPLATE_ARGS(n)>                                       \
    struct __CompositeDbsElem __PARTIAL_20_##n(ACTION_ARGS, DUMMY_ARGS)     \
    : DbsElem                                                               \
    {                                                                       \
        bool access(WORD16 eventId, void* req, void* ack) const             \
        {                                                                   \
            return DECL_SMART_DBS_ELEM_ACCESSES(n);                         \
        }                                                                   \
                                                                            \
        Status load(void* param = 0)                                        \
        {                                                                   \
            DECL_SMART_DBS_ELEM_LOADS(n);                                   \
            return USI_SUCCESS;                                             \
        }                                                                   \
                                                                            \
        void dump() const                                                   \
        {                                                                   \
            DECL_SMART_DBS_ELEM_DUMPS(n);                                   \
        }                                                                   \
                                                                            \
    private:                                                                \
        DECL_COMP_DBS_ELEMS_MEMBERS(n);                                     \
    };                                                                      \
}

__COMP_DBS_ELEM_PARTIAL_COLLECTION(20)
__COMP_DBS_ELEM_PARTIAL_COLLECTION(19)
__COMP_DBS_ELEM_PARTIAL_COLLECTION(18)
__COMP_DBS_ELEM_PARTIAL_COLLECTION(17)
__COMP_DBS_ELEM_PARTIAL_COLLECTION(16)
__COMP_DBS_ELEM_PARTIAL_COLLECTION(15)
__COMP_DBS_ELEM_PARTIAL_COLLECTION(14)
__COMP_DBS_ELEM_PARTIAL_COLLECTION(13)
__COMP_DBS_ELEM_PARTIAL_COLLECTION(12)
__COMP_DBS_ELEM_PARTIAL_COLLECTION(11)
__COMP_DBS_ELEM_PARTIAL_COLLECTION(10)
__COMP_DBS_ELEM_PARTIAL_COLLECTION(9)
__COMP_DBS_ELEM_PARTIAL_COLLECTION(8)
__COMP_DBS_ELEM_PARTIAL_COLLECTION(7)
__COMP_DBS_ELEM_PARTIAL_COLLECTION(6)
__COMP_DBS_ELEM_PARTIAL_COLLECTION(5)
__COMP_DBS_ELEM_PARTIAL_COLLECTION(4)
__COMP_DBS_ELEM_PARTIAL_COLLECTION(3)
__COMP_DBS_ELEM_PARTIAL_COLLECTION(2)
__COMP_DBS_ELEM_PARTIAL_COLLECTION(1)

//////////////////////////////////////////////////////////////////////////

#define __DEF_GENERIC_COMP_DBS_ELEM(n)          \
namespace details {                                     \
    template <DECL_DUMMY_DEFAULT(n)>                    \
    struct COMP_DBS_ELEM__                              \
        : __CompositeDbsElem<DECL_ALL_ARGS(n)>         \
    {                                                   \
    };                                                  \
}

/////////////////////////////////////////////////////////////////////////////////
__DEF_GENERIC_COMP_DBS_ELEM(20);

#define __comp_dbs_elem(...)    ::details::COMP_DBS_ELEM__< __VA_ARGS__ >

#endif

