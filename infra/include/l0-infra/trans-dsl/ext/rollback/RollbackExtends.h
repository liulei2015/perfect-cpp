#ifndef INCL_USI_RollbackExtends_H_
#define INCL_USI_RollbackExtends_H_

namespace details
{
    __def(Rollback, __params(__action(ROLLBACK))) __as
      ( __sequential
          ( ROLLBACK
          , __throw(USI_NOTHING_CHANGED))
      );
}

#define __rollback(...) __apply(::details::Rollback, __with(__VA_ARGS__))

#endif
