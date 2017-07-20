#ifndef INCL_USI_EqHelper_2013111201503_H__
#define INCL_USI_EqHelper_2013111201503_H__

//////////////////////////////////////////////////////////////
#define __DECL_EQUALS(cls)            \
bool operator==(const cls&) const;    \
bool operator!=(const cls&) const

//////////////////////////////////////////////////////////////
#define __FIELD_EQ(name) this->name == rhs.name

#define __NEED_OR_FILED_IS_PRESENT(name) this->name.isPresent()

//////////////////////////////////////////////////////////////
#define __DEF_EQUALS(cls)                                   \
bool cls::operator!=(const cls& rhs) const                  \
{                                                           \
    return !(*this == rhs);                                 \
}                                                           \
bool cls::operator==(const cls& rhs) const

#endif

