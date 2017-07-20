#ifndef INCL_USI_NotHelper_H_
#define INCL_USI_NotHelper_H_

struct TransactionInfo;

namespace details
{
    template<typename PRED>
    struct NOT__
    {
        bool operator()(const TransactionInfo& trans)
        {
            return !pred(trans);
        }

    private:
        PRED pred;
    };
}

#define __not(pred) ::details::NOT__< pred >

#endif
