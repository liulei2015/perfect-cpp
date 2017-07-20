/*
 * ListBasedRole.h
 *
 *  Created on: Apr 13, 2013
 *      Author: arthur
 */

#ifndef LISTBASEDROLE_H_
#define LISTBASEDROLE_H_

#include <l0-infra/dci/Role.h>
#include <l0-infra/base/ListElem.h>

#define DEFINE_LIST_BASED_ROLE(role) \
    struct role : ListElem<role> , ::details::Role

#endif /* LISTBASEDROLE_H_ */

