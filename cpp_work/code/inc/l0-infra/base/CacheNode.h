#ifndef INCL_SERVICE_HBADFCA42_7FF2_4BA4_A5DE_49EC593488B9
#define INCL_SERVICE_HBADFCA42_7FF2_4BA4_A5DE_49EC593488B9

#include "l0-infra/base/Service.h"
#include "l0-infra/base/BaseTypes.h"

#include "Type.h"

SERVICE_NS_BEGIN

struct CacheNode
{
	CacheNode(U32 id,
					     HOW_LONG_NOT_USE_MEASUREMENT measure,
						 U32 visitTimes) :
		id(id), measure(measure), visitTimes(visitTimes) {}

	U32 getId() const;
	HOW_LONG_NOT_USE_MEASUREMENT getMeasure() {return measure;}
	U32 getVisitTimes() {return visitTimes; }

	bool operator == (const CacheNode& rNode);
private:

private:
	U32 id;
	HOW_LONG_NOT_USE_MEASUREMENT measure;
	U32 visitTimes;

};


SERVICE_NS_END

#endif
