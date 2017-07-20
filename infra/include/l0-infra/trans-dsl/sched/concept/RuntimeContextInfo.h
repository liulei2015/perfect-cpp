/*
 * RuntimeContextInfo.h
 *
 * Created on: Apr 23, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef RUNTIMECONTEXTINFO_H_
#define RUNTIMECONTEXTINFO_H_

#include <l0-infra/dci/InterfaceDef.h>

struct RuntimeContext;

DEF_INTERFACE(RuntimeContextInfo, 304231933)
{
    RuntimeContextInfo()
               : runtimeContext(0)
                 {
                 }

    explicit RuntimeContextInfo(RuntimeContext& runtimeContext)
    : runtimeContext(&runtimeContext)
    {
    }

    void setRuntimeContext(RuntimeContext& context)
    {
        runtimeContext = &context;
    }

    RuntimeContext* getRuntimeContext() const
    {
        return runtimeContext;
    }

private:
    RuntimeContext* runtimeContext;
};

#endif /* RUNTIMECONTEXTINFO_H_ */

