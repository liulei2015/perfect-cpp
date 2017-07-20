#ifndef INCL_USI_FragmentGnu_20140311154058_H__
#define INCL_USI_FragmentGnu_20140311154058_H__

#define __def(name, ...)  __VA_ARGS__ struct name
#define __params(...) template< __VA_ARGS__ >

#define __as(...)  : __VA_ARGS__ {}

//////////////////////////////////////////////////////////////
#define __apply(name, ...) name __VA_ARGS__
#define __with(...) <__VA_ARGS__ >

#define __fragment(frag)   typename frag
#endif

