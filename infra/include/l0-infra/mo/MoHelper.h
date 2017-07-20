#ifndef INCL_DCM_HB6D94534_F443_4566_915E_484011D8529B
#define INCL_DCM_HB6D94534_F443_4566_915E_484011D8529B

#include "l0-infra/mo/MoNode.h"
#include "json.hpp"
#include <sstream>
#include <string>

using std::string;
using nlohmann::json;
using std::stringstream;

struct Event;

////////////////////////////////////////////////////////////////////////////////////
#define TO_CELL_NODE(para, cellNode)                                 \
do{                                                                  \
    stringstream _node;                                              \
    _node << CELL_NODE << "[CellId=" << *(WORD16*)para << "]";       \
    _node >> cellNode;                                               \
}while(0)

////////////////////////////////////////////////////////////////////////////////////
struct MoHelper
{
    static json getMoResult(const Event& event);

    template<typename...Nodes>
    static void buildReqByNodes(string& req, Nodes&... nodes)
    {
        stringstream _req;
        _req << "{" << "\"get\"" << ":" << "[";
        addNodes(_req, nodes...);
        _req << "]" << "}";
        _req >> req;
    }

private:
    template<typename Node>
    static void addNodes(stringstream& ss, const Node& node)
    {
        ss << "\"" << node << "\"";
    }

    template<typename Node, typename... Nodes>
    static void addNodes(stringstream& ss, const Node& node, Nodes&... nodes)
    {
        addNodes(ss, node);
        ss << ",";
        addNodes(ss, nodes...);
    }
};


#define RESET_INDEX_BY_ID(ITEM_CLASS, MAX_SIZE, REAL_SIZE, SRC_POINT, ID_NAME) \
		static ITEM_CLASS ITEM_CLASS##_TEMP[MAX_SIZE];\
		for(int ITEM_CLASS##_I = 0; ITEM_CLASS##_I < REAL_SIZE; ITEM_CLASS##_I++)\
		{\
				ITEM_CLASS* current = &SRC_POINT[ITEM_CLASS##_I];\
				memcpy(&ITEM_CLASS ## _TEMP[current->ID_NAME], current, sizeof(ITEM_CLASS));\
		}\
		memcpy(SRC_POINT, ITEM_CLASS##_TEMP, sizeof(ITEM_CLASS)*MAX_SIZE);


#endif
