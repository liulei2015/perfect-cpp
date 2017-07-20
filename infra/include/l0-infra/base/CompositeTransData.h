#ifndef INCL_USI_CompositeTransData_2013118214305_H__
#define INCL_USI_CompositeTransData_2013118214305_H__

#include "l0-infra/trans-dsl/utils/ActionMacroHelper.h"

////////////////////////////////////////////////////////////////
#define __COMP_TRANS_MEMBER_DEF(n)  ACTION ## n  m ## n;
#define DECL_COMP_TRANS_MEMBERS(n) SIMPLE_REPEAT(n, __COMP_TRANS_MEMBER_DEF)

//////////////////////////////////////////////////////////////////////////
#define __COMP_TRANS_ISCHANGED(n)       m ## n.isChanged(restart)
#define __COMP_TRANS_ISCHANGEDS(n)      __COMP_TRANS_ISCHANGED(n) ||

#define DECL_SMART_STRUCT_ISCHANGEDS(n) REPEAT(n, __COMP_TRANS_ISCHANGEDS, __COMP_TRANS_ISCHANGED)

//////////////////////////////////////////////////////////////////////////
#define __COMP_TRANS_ISSTABLE(n)       m ## n.isStable()
#define __COMP_TRANS_ISSTABLES(n)      __COMP_TRANS_ISSTABLE(n) &&

#define DECL_SMART_STRUCT_ISSTABLES(n) REPEAT(n, __COMP_TRANS_ISSTABLES, __COMP_TRANS_ISSTABLE) 

//////////////////////////////////////////////////////////////////////////
#define __COMP_TRANS_ISVALID(n)         m ## n.isValid()
#define __COMP_TRANS_ISVALIDS(n)      __COMP_TRANS_ISVALID(n) ||

#define DECL_COMP_TRANS_ISVALIDS(n) REPEAT(n, __COMP_TRANS_ISVALIDS, __COMP_TRANS_ISVALID)

//////////////////////////////////////////////////////////////////////////
#define __COMP_TRANS_ISPRESENT(n)       m ## n.isPresent()
#define __COMP_TRANS_ISPRESENTS(n)      __COMP_TRANS_ISPRESENT(n) ||

#define DECL_COMP_TRANS_ISPRESENTS(n) REPEAT(n, __COMP_TRANS_ISPRESENTS, __COMP_TRANS_ISPRESENT)

////////////////////////////////////////////////////////////////
#define __COMP_TRANS_CONFIRM(n)      m ## n.confirm();
#define COMP_TRANS_CONFIRM(n) SIMPLE_REPEAT(n, __COMP_TRANS_CONFIRM)

////////////////////////////////////////////////////////////////
#define __COMP_TRANS_REVERT(n)       m ## n.revert();
#define COMP_TRANS_REVERT(n) SIMPLE_REPEAT(n, __COMP_TRANS_REVERT)

////////////////////////////////////////////////////////////////
#define __COMP_TRANS_RESET(n)     m ## n.reset();
#define COMP_TRANS_RESET(n) SIMPLE_REPEAT(n, __COMP_TRANS_RESET)

////////////////////////////////////////////////////////////////
#define __COMP_TRANS_TOUCH(n)     m ## n.touch();
#define COMP_TRANS_TOUCH(n) SIMPLE_REPEAT(n, __COMP_TRANS_TOUCH)

////////////////////////////////////////////////////////////////
#define __COMP_TRANS_RELEASE(n)     m ## n.release();
#define COMP_TRANS_RELEASE(n) SIMPLE_REPEAT(n, __COMP_TRANS_RELEASE)

////////////////////////////////////////////////////////////////
#define __COMP_TRANS_PARTIAL_COLLECTION(n)                                \
    namespace details {                                                   \
    template < DECL_TEMPLATE_ARGS(n)>                                     \
    struct __CompositeTransData __PARTIAL_30_##n(ACTION_ARGS, DUMMY_ARGS) \
    {                                                                     \
        bool isChanged(bool restart = false)                              \
        {                                                                 \
            return DECL_SMART_STRUCT_ISCHANGEDS(n);                       \
        }                                                                 \
                                                                          \
        void confirm()                                                    \
        {                                                                 \
            COMP_TRANS_CONFIRM(n)                                         \
        }                                                                 \
                                                                          \
        void revert()                                                     \
        {                                                                 \
            COMP_TRANS_REVERT(n)                                          \
        }                                                                 \
                                                                          \
        void reset()                                                      \
        {                                                                 \
            COMP_TRANS_RESET(n)                                           \
        }                                                                 \
                                                                          \
        void release()                                                    \
        {                                                                 \
            COMP_TRANS_RELEASE(n)                                         \
        }                                                                 \
                                                                          \
        void touch()                                                      \
        {                                                                 \
            COMP_TRANS_TOUCH(n)                                           \
        }                                                                 \
                                                                          \
        bool isValid() const                                              \
        {                                                                 \
            return DECL_COMP_TRANS_ISVALIDS(n);                           \
        }                                                                 \
                                                                          \
        bool isPresent() const                                            \
        {                                                                 \
            return DECL_COMP_TRANS_ISPRESENTS(n);                         \
        }                                                                 \
                                                                          \
        bool isChanged(bool restart = false) const                        \
        {                                                                 \
            return DECL_SMART_STRUCT_ISCHANGEDS(n);                       \
        }                                                                 \
                                                                          \
        bool isStable() const                                             \
        {                                                                 \
            return DECL_SMART_STRUCT_ISSTABLES(n);                        \
        }                                                                 \
    private:                                                              \
        DECL_COMP_TRANS_MEMBERS(n)                                        \
    };                                                                    \
    }

__COMP_TRANS_PARTIAL_COLLECTION(30)
__COMP_TRANS_PARTIAL_COLLECTION(29)
__COMP_TRANS_PARTIAL_COLLECTION(28)
__COMP_TRANS_PARTIAL_COLLECTION(27)
__COMP_TRANS_PARTIAL_COLLECTION(26)
__COMP_TRANS_PARTIAL_COLLECTION(25)
__COMP_TRANS_PARTIAL_COLLECTION(24)
__COMP_TRANS_PARTIAL_COLLECTION(23)
__COMP_TRANS_PARTIAL_COLLECTION(22)
__COMP_TRANS_PARTIAL_COLLECTION(21)
__COMP_TRANS_PARTIAL_COLLECTION(20)
__COMP_TRANS_PARTIAL_COLLECTION(19)
__COMP_TRANS_PARTIAL_COLLECTION(18)
__COMP_TRANS_PARTIAL_COLLECTION(17)
__COMP_TRANS_PARTIAL_COLLECTION(16)
__COMP_TRANS_PARTIAL_COLLECTION(15)
__COMP_TRANS_PARTIAL_COLLECTION(14)
__COMP_TRANS_PARTIAL_COLLECTION(13)
__COMP_TRANS_PARTIAL_COLLECTION(12)
__COMP_TRANS_PARTIAL_COLLECTION(11)
__COMP_TRANS_PARTIAL_COLLECTION(10)
__COMP_TRANS_PARTIAL_COLLECTION(9)
__COMP_TRANS_PARTIAL_COLLECTION(8)
__COMP_TRANS_PARTIAL_COLLECTION(7)
__COMP_TRANS_PARTIAL_COLLECTION(6)
__COMP_TRANS_PARTIAL_COLLECTION(5)
__COMP_TRANS_PARTIAL_COLLECTION(4)
__COMP_TRANS_PARTIAL_COLLECTION(3)
__COMP_TRANS_PARTIAL_COLLECTION(2)
__COMP_TRANS_PARTIAL_COLLECTION(1)


#define __DEF_COMPOISTE_TRANS_DATA(n)                        \
    template < DECL_DUMMY_DEFAULT(n) >                       \
struct CompositeTransData                                    \
{                                                            \
    void confirm()                                           \
    { data.confirm(); }                                      \
                                                             \
    void revert()                                            \
    { data.revert(); }                                       \
                                                             \
    void touch()                                             \
    { data.touch(); }                                        \
                                                             \
    void release()                                           \
    { data.release(); }                                      \
                                                             \
    void reset()                                             \
    { data.reset(); }                                        \
                                                             \
    bool isChanged(bool restart = false) const               \
    { return data.isChanged(restart); }                      \
                                                             \
    bool isPresent() const                                   \
    { return data.isPresent(); }                             \
                                                             \
    bool isValid() const                                     \
    { return data.isValid(); }                               \
                                                             \
    bool isStable() const                                    \
    { return data.isStable(); }                              \
                                                             \
private:                                                     \
    ::details::__CompositeTransData<DECL_ALL_ARGS(n)> data;  \
}

//////////////////////////////////////////////////////////////////////////
USI_NS_BEGIN

__DEF_COMPOISTE_TRANS_DATA(30);

template <typename COMP_TRANS_DATA>
struct AutoCompositeTransData
{
    void confirm()                                       
    {
        reinterpret_cast<COMP_TRANS_DATA&>(*this).confirm();
    }

    void revert()
    {
        reinterpret_cast<COMP_TRANS_DATA&>(*this).revert();
    }

    void reset()
    {
        reinterpret_cast<COMP_TRANS_DATA&>(*this).reset();
    }

    void release()
    {
        reinterpret_cast<COMP_TRANS_DATA&>(*this).release();
    }

    void touch()
    {
        reinterpret_cast<COMP_TRANS_DATA&>(*this).touch();
    }

    bool isChanged(bool restart = false) const
    {
        return reinterpret_cast<const COMP_TRANS_DATA&>(*this).isChanged(restart);
    }

    bool isPresent() const
    {
        return reinterpret_cast<const COMP_TRANS_DATA&>(*this).isPresent();
    }

    bool isStable() const
    {
        return reinterpret_cast<const COMP_TRANS_DATA&>(*this).isStable();
    }
};

USI_NS_END

#endif

