#include "BeanUndef.h"

#include "json.hpp"
#include <string>
#include "string.h"
#include <exception>
#include "l0-infra/log/UsfLog.h"
#include <sys/time.h>  

using json = nlohmann::json;
using std::exception;

#define BEAN_SUCCESS 0
#define BEAN_FAIL -1
#define BEAN_STOP -2
#define BEAN_INVALID_INDEX 0xFFFF

#ifndef ERR_LOG
#define ERR_LOG printf
#endif

#ifndef WARN_LOG
#define WARN_LOG printf
#endif

#ifndef DBG_LOG
#define DBG_LOG(..)
#endif

#ifndef INFO_LOG
#define INFO_LOG(..)
#endif

#define MO_TRANS_STRUCT_BEGIN(STRUCT_NAME, FLAG, ...)    inline void structTrans_##STRUCT_NAME##_##FLAG(const json& msg, STRUCT_NAME& out) {
#define MO_TRANS_STRUCT_END }

namespace Bean
{

    inline long getCurrentTime(bool isBegin)
    {
        struct timeval tv;  
        gettimeofday(&tv,NULL); 
        long t = tv.tv_sec * 1000000 + tv.tv_usec;

        DBG_LOG("bean debug : current time : %l, %s\n" ,  t ,  (isBegin ? "begin" : "end") );
        return t;  
    }

    inline int getIntValue(const json& v)
    {
        if(v == nullptr)
            return 0;

        if(v.is_number())
        {
            return v;
        }
        else if(v.is_string())
        {
            std::string str = v;
            return atoi(str.c_str());
        } 
        else if(v.is_boolean())
        {
            //std::cout << "is_boolean " << v << " : " <<  (v == true) << " \n";
            return (v == true) ? 1 : 0;
        }
        else
        {
            //std::cout << "unable convert " << v << " to int long \n";
            std::string s("unable convert ");
            s += v;
            throw  s + "to int long ";
        }

        return 0;
    }

    inline int pushPath(char* pointer, const char* path, int arrayIndex)
    {
        if(path[0] == '\0') {
            return BEAN_SUCCESS;
        }

        const char* s = path;
        char* d = pointer + strlen(pointer);

        auto incr = [&](){ s++; d++;};
        auto trim = [&](){ if((d-1)[0] == '/') { d--; d[0] = '\0';} };
        auto split = [&](){ trim(); *d = '/';};
        
        if(*s != '[' && *s != '.')
        {
            *d = '/';
            d++;
        }

        while( *s != '\0')
        {
            if(*s == '.' || *s == '[')
            {
                split();
            }
            else if(*s == '?')
            {
                if(arrayIndex == BEAN_INVALID_INDEX)
                {
                    trim();
                    return BEAN_STOP;
                }
                
                sprintf(d, "%d", arrayIndex);
                d += strlen(d)-1;
            }
            else if(*s == '$')
            {
                trim();
                return BEAN_STOP;
            }
            else if(*s == ']')
            {
                s++;
                continue;
            }
            else
            {
                *d = *s;
            }

            incr();
        }

        trim();
        d[0] = '\0';
        return BEAN_SUCCESS;
    }

#define BEAN_TIME_BEGIN
    //auto begin = Bean::getCurrentTime(true);
#define BEAN_TIME_END(...)
    //auto paytime = Bean::getCurrentTime(false) - begin; \
                            if(paytime > 50) std::cout << __VA_ARGS__ << " paytime " << paytime << "\n";

    inline bool isNodeNull(const nlohmann::json& j)
    {
        return ((char)j.type() > 7) || j.is_null();
    }

    inline const nlohmann::json& getNodeByPointer(const nlohmann::json& v, const char* pointer)
    {
        char currentPath[100] = {'\0'};
        const char* splitPosition = pointer+1;
        int currentPathIndex = 0;
        const nlohmann::json* j =  &v;

        while(true)
        {
            if(*splitPosition != '/' && *splitPosition != '\0')
            {
                currentPath[currentPathIndex] = *splitPosition;
                currentPathIndex++;
                splitPosition++;
                currentPath[currentPathIndex] = '\0';
            }
            else
            {
                if(j->is_array())
                {
                    int i = atoi(currentPath);
                    if( i >= (*j).size())
                    {
                        throw std::out_of_range("array out of range");
                    }
                    const json& temp = (*j)[i];
                    j = &temp;
                }
                else if(isNodeNull(*j))
                {
                    break;
                }
                else
                {
                    const json& temp = (*j)[currentPath];
                    j = &temp;
                }

                if(*splitPosition != '\0')
                {
                    splitPosition++;
                    currentPathIndex=0;
                }
                else
                    break;
            }
        }

        return *j;
    }

    inline int getValue(const nlohmann::json** v, const nlohmann::json& j, std::string key, const char* path, const char* name, bool isNullable = false, int arrayIndex = BEAN_INVALID_INDEX)
    {
        //BEAN_TIME_BEGIN
        char pointer[200] = {0};
        strcpy(pointer, "/");

        if(key.length() > 0) 
        {
            //has key
            strcat(pointer, key.c_str());
            if( j.find(key) == j.end())
            {
            	ERR_LOG("not found the key: %s in json  \n", key.c_str());
                return BEAN_FAIL;
            }
            //when array size equal 0 , get the first item at first, has index
            //(NAME, KEY, [?].MOREPATH, ...)
            if(path[1] != '?' && path[1] != '$')
            {
                strcat(pointer, "/0");
            }
        }

        if(pushPath(pointer, path, arrayIndex) != BEAN_STOP)
            pushPath(pointer, name, arrayIndex);

        //std::cout<<"(name:" << name <<  ")"<< "\n";
        if(pointer[1] != 0)
        {
            try
            {
                //std::cout<<"(patch:" << pointer <<  ")"<< "\n";
                const json& c= getNodeByPointer(j, pointer);
                *v = &c;
                //std::cout<<"(node value:" << c <<  ")"<< "\n";
                if(isNodeNull(c))
                {
                    if(isNullable == false)
                    {
                    	ERR_LOG("key:%s, path:%s, name:%s, (patch:%s) is null or empty \n", key.c_str(), path, name, pointer);
                        return BEAN_FAIL;
                    }
                }
            }
            catch (std::out_of_range& ex)
            {
                if(arrayIndex != BEAN_INVALID_INDEX)
                {
                	WARN_LOG("key:%s, path:%s, name:%s, index %d out of range\n", key.c_str(), path, name, arrayIndex);
                    return BEAN_STOP;
                }
                else
                {
                    throw ex;
                }
            }
        }

        return BEAN_SUCCESS;
    }

    inline int indexOfChar(const char* str, char c)
    {
        const char* cc = str;

        for(; *cc != '\0'; cc++)
        {
            if(*cc == c)
            {
                return cc - str;
            }
        }
        return -1;
    }

    template<typename array_t>
    inline int copyJson2Array(const nlohmann::json& v, array_t* array, const char* path)
    {
        int i = 0;
        bool usePath = path[0] != '\0';

        if(usePath)
        {
            char pointer[100] = {0};
            pushPath(pointer, path, BEAN_INVALID_INDEX);
            for( const json& p : v)
            {
                array[i] = getIntValue(getNodeByPointer(p, pointer));
                i++;
            }
        }
        else
        {
            for( const json& p : v)
            {
                array[i] = getIntValue(p);
                i++;
            }
        }

        return 0;
    }

    template<typename array_t>
    inline int safetyCopyJson2Array(const nlohmann::json& v, array_t* array, int maxSize, const char* path = "")
    {
        if(!v.is_array())
        {
            std::string err = v;
            err += " is not an array";
            std::cout << err << "\n";
            throw std::domain_error(err);
            return BEAN_FAIL;
        }

        memset(array, 0xFF, sizeof(array[0]) * maxSize);

        if(v.size() == 0) 
        {
        	WARN_LOG("warn : array is empty\n");
            return BEAN_SUCCESS;
        }

        if(v.size() > maxSize)
        {
        	ERR_LOG(" the array size is too large :%s\n", path);
            throw std::domain_error("the array size is too large");
            return BEAN_FAIL;
        }

        copyJson2Array(v, array, path);

        return BEAN_SUCCESS;

    }

    inline BYTE hasItemInArray(const json& v, const char* item)
    {
        if(v == nullptr || !v.is_array())
        {
            return 0;
        }

        for( const json& p : v)
        {
            if(p == item)
            {
                return 1;
            }
        }

        return 0;
    }

};

#define BEAN_BASE(KEY, PATH, MONAME, ...) do\
{\
    try{\
    	ret = #KEY[0] == '\0' ? Bean::getValue(&v, j, "", #PATH, #MONAME, false, arrayIndex) : Bean::getValue(&v, j, KEY, #PATH, #MONAME, false, arrayIndex);\
        if( ret != BEAN_SUCCESS)\
        {\
            return ret;\
        } \
        else\
        {\
            __VA_ARGS__ \
        }\
    } catch(exception& ex){\
    	ERR_LOG("get KEY(%s), PATH(%s), MONAME(%s) Value failed: exception is \"%s\"",\
                KEY, #PATH, #MONAME, ex.what());\
        return BEAN_FAIL;\
    }\
}while(0)

#define BEAN_BASE_WITH(KEY1, PATH1, MONAME1, KEY2, PATH2, MONAME2, ...) do\
{\
    try{\
        if((ret = Bean::getValue(&v, j, KEY1, #PATH1, #MONAME1, false, arrayIndex)) != BEAN_SUCCESS \
            || (ret = Bean::getValue(&v2, j, KEY2, #PATH2, #MONAME2, false, arrayIndex)) != BEAN_SUCCESS)\
        {\
            return ret;\
        } \
        else\
        {\
            __VA_ARGS__ \
        }\
    } catch(exception& ex){\
    	ERR_LOG("get KEY1(%s), PATH1(%s), MONAME1(%s), KEY2(%s), PATH2(%s), MONAME2(%s) Value failed: exception is \"%s\"",\
                std::string(KEY1).c_str(), #PATH1, #MONAME1, KEY2, #PATH2, #MONAME2, ex.what());\
        return BEAN_FAIL;\
    }\
}while(0)


////////////////////////BEAN API////////////////////////
#define BEAN_BYTE(NAME, KEY, PATH, MONAME, ...)  BEAN_BASE(KEY, PATH, MONAME, NAME = Bean::getIntValue(*v);)
#define BEAN_WORD16 BEAN_BYTE
#define BEAN_WORD32 BEAN_BYTE

#define BEAN_BYTE_ARRAY(NAME, SIZE, KEY, PATH, MONAME, ...) \
        BEAN_BASE(KEY, PATH, MONAME, int maxSize = sizeof(NAME)/sizeof(NAME[0]);if(Bean::indexOfChar(#PATH, '$') > -1) \
        {\
            if(Bean::safetyCopyJson2Array<>(*v, NAME, maxSize, #MONAME) != BEAN_SUCCESS) {\
            	ERR_LOG("safetyCopyJson2Array fail");return BEAN_FAIL;\
            }\
        } \
        else \
        { \
            if(Bean::safetyCopyJson2Array<>(*v, NAME, maxSize, "") != BEAN_SUCCESS) {\
            	ERR_LOG("safetyCopyJson2Array fail");return BEAN_FAIL;\
            }\
        }\
        )
#define BEAN_WORD16_ARRAY BEAN_BYTE_ARRAY
#define BEAN_WORD32_ARRAY BEAN_BYTE_ARRAY

#define BEAN_BYTE_TRANS(NAME, KEY, PATH, MONAME, ...) BEAN_BASE(KEY, PATH, MONAME,tableTrans_##MONAME(*v, NAME);)
#define BEAN_WORD16_TRANS BEAN_BYTE_TRANS
#define BEAN_WORD32_TRANS BEAN_BYTE_TRANS


#define BEAN_BYTE_ARRAY_TRANS(NAME, SIZE, KEY, PATH, MONAME, ...) \
        BEAN_BASE(KEY, PATH, MONAME, tableTrans_##MONAME(*v, NAME);)
#define BEAN_WORD16_ARRAY_TRANS BEAN_BYTE_ARRAY_TRANS
#define BEAN_WORD32_ARRAY_TRANS BEAN_BYTE_ARRAY_TRANS


#define BEAN_BYTE_ARRAY_ALIAS(NAME, SIZE, KEY, PATH, ALIAS, ...) \
        BEAN_BASE(KEY, PATH, , tableTrans_##ALIAS(*v, NAME);)
#define BEAN_WORD16_ARRAY_ALIAS BEAN_BYTE_ARRAY_ALIAS
#define BEAN_WORD32_ARRAY_ALIAS BEAN_BYTE_ARRAY_ALIAS

#define BEAN_BYTE_TRANS_WITH(NAME, KEY, PATH, MONAME1, MONAME2) \
        BEAN_BASE_WITH(KEY, PATH, MONAME1, KEY, PATH, MONAME2, moTrans_##MONAME1##_with_##MONAME2(*v, *v2, NAME);)
#define BEAN_WORD16_TRANS_WITH BEAN_BYTE_TRANS_WITH
#define BEAN_WORD32_TRANS_WITH BEAN_BYTE_TRANS_WITH

#define BEAN_BYTE_SIZE(NAME, KEY, PATH,...) BEAN_BASE(KEY, PATH, , NAME = v == nullptr ? 0 : v->size();INFO_LOG("array size:%d\n", v->size());)
#define BEAN_WORD16_SIZE BEAN_BYTE_SIZE
#define BEAN_WORD32_SIZE BEAN_BYTE_SIZE

#define BEAN_BYTE_ALIAS(NAME, KEY, PATH, ALIAS, ...) BEAN_BASE(KEY, PATH, ,tableTrans_##ALIAS(*v, NAME);)
#define BEAN_WORD16_ALIAS BEAN_BYTE_ALIAS
#define BEAN_WORD32_ALIAS BEAN_BYTE_ALIAS

#define BEAN_BYTE_MULT_NODES(NAME, KEY1, PATH1, MONAME1, KEY2, ...) \
        BEAN_BASE_WITH(std::string(KEY1), PATH1, MONAME1, KEY2, , , moTrans_for_##NAME(*v, NAME, *v2);)
#define BEAN_WORD16_MULT_NODES BEAN_BYTE_MULT_NODES
#define BEAN_WORD32_MULT_NODES BEAN_BYTE_MULT_NODES

#define BEAN_WORD32_NOTFOUND(...) 
#define BEAN_WORD16_NOTFOUND(...)
#define BEAN_BYTE_NOTFOUND(...)
#define BEAN_WORD32_NOTSURE(...)
#define BEAN_WORD16_NOTSURE(...)
#define BEAN_BYTE_NOTSURE(...)

#define BEAN_IF_HAS_ITEM(NAME, KEY, PATH, ITEM) BEAN_BASE(KEY, PATH, , NAME = Bean::hasItemInArray(*v, #ITEM);)

#define BEAN_STRUCT(STRUCT, NAME) do{if(NAME.setProperties(j) != BEAN_SUCCESS) return BEAN_FAIL;}while(0)
#define BEAN_STRUCT_ARRAY(STRUCT, NAME, SIZE) for(size = (sizeof(NAME) / sizeof(STRUCT)),i = 0; i < size; i++){\
        ret = NAME[i].setProperties(j, i);\
        if(ret == BEAN_FAIL)\
            return BEAN_FAIL;\
        else if(ret == BEAN_STOP)\
        {\
            break;\
        }\
     }

#define BEAN_STRUCT_ALIAS(STRUCT, NAME, KEY, PATH, ALIAS) \
        BEAN_BASE(KEY, PATH, , structTrans_##STRUCT##_##ALIAS(*v, NAME);)

#define BEAN_DEF(NAME, ...) template<> int NAME::setProperties<json>(const json& j, int arrayIndex) {\
		INFO_LOG("%s\n",#NAME);const json* v = nullptr;\
        const json* v2 = nullptr;\
        int ret = 0, size = 0, i = 0;BEAN_TIME_BEGIN
#define BEAN_DEF_END BEAN_TIME_END("setProperties") return BEAN_SUCCESS;}
#define BEAN_USE(...)
#define BEAN_HAS_KEY(KEY)
#define BEAN_REALIZE(...) __VA_ARGS__

#define BEAN_INIT(NAME, ...) void NAME::init( __VA_ARGS__ ) {
#define BEAN_USE_KEY(PARAM_NAME) this->PARAM_NAME = PARAM_NAME;
#define BEAN_SUB_USE_KEY(STRUCT_NAME, ...) STRUCT_NAME.init(__VA_ARGS__);
#define BEAN_SUB_ARRAY_USE_KEY(STRUCT_NAME, SIZE, ...) for(int i = 0; i < SIZE; i++){ STRUCT_NAME[i].init(__VA_ARGS__);}
#define BEAN_INIT_END }
#define BEAN_USE_KEY_WITH_INIT(NAME, KEY) BEAN_INIT(NAME, const char* KEY)\
        BEAN_USE_KEY(KEY)\
   BEAN_INIT_END

#define BEAN_DEF_WITH(NAME, INIT, ...) BEAN_DEF(NAME, ...)
#define BEAN_DEF_END_WITH(...) BEAN_DEF_END __VA_ARGS__
#define BEAN_DEF_END_WITH_INIT(NAME, KEY, ...) BEAN_DEF_END BEAN_USE_KEY_WITH_INIT(NAME, KEY) __VA_ARGS__

#define BEAM_EXTEND(NAME, PARENT_NAME, ...) BEAN_DEF(NAME)  __VA_ARGS__  BEAN_DEF_END

