#ifndef INCL_USI_BASE_REF_PAYLOAD_H
#define INCL_USI_BASE_REF_PAYLOAD_H

#define BEGIN_REF_PAYLOAD(NewType, BaseType) \
struct NewType { \
    NewType(BaseType& config); \
private: \
    BaseType& config; \
public:

#define END_REF_PAYLOAD() };

#define REF_PAYLOAD_CONS(NewType, BaseType) \
    NewType::NewType(BaseType& config) : config(config)

#define DEFAULT_REF_PAYLOAD_CONS(NewType, BaseType) \
    REF_PAYLOAD_CONS(NewType, BaseType) {}

#endif

