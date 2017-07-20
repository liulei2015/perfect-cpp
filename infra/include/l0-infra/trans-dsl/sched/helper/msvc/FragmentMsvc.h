#ifndef INCL_USI_FragmentMsvc_20140311154136_H__
#define INCL_USI_FragmentMsvc_20140311154136_H__

////////////////////////////////////////////////////
#define __DEF1(...) \
    template<bool _Dummy_N_, ##__VA_ARGS__ >

#define __def(name, ...) __DEF1(__VA_ARGS__) struct name
#define __params(...)      __VA_ARGS__
#define __as(...)  : __VA_ARGS__ {}


//////////////////////////////////////////////////////////////
#define __APPLY1(...) < true, ##__VA_ARGS__ >

#define __apply(name, ...) name __APPLY1(__VA_ARGS__)
#define __with(...) __VA_ARGS__

#define __fragment(frag)   template<bool __Dummy> class frag

#endif

