#ifndef Foundation_ArgParser_INCLUDED
#define Foundation_ArgParser_INCLUDED


#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <map>
#include "Percipio/Foundation.h"


namespace Percipio {

struct ArgFlag {
    enum value_type{
        VALUE_BOOL  = 0x1001,
        VALUE_INT32,
        VALUE_INT64,
        VALUE_FLOAT,
        VALUE_DOUBLE,
        VALUE_PCHAR,
    };
#ifdef WIN32
	template<typename T>
	/*enum*/ value_type _typeID();
#else
	template<typename T>
	enum value_type _typeID();
#endif // WIN32

    const char*     name;
    enum value_type valueType;
    const char*     infoStr;
    bool            needValue;      // some optional arguments need no value

    union{
        bool        b;
        int32_t     i32;
        int64_t     i64;
        float       f;
        double      d;
        const char* s;
    }data;

    bool            isDefault;
    void*           validator;

    template<typename T>
    ArgFlag(const char* _name, const char* c, bool(*_valid)(T val), bool _needValue, T defVal)
            : name(_name), infoStr(c), needValue(_needValue),
              isDefault(true), validator((void*)_valid)
        {
            valueType = _typeID<T>();
            *((T*)&data) = defVal;
        }

    template<typename T>
    bool setVal(T val) {
            if( valueType != _typeID<T>() ){
                // fprintf(stderr, "ArgFlag: %s setVal type(%s) not matched(%s)!\n", name, typeToStr(_typeID<T>()), typeStr());
                return false;
            }
            if( validator ){
                bool (*_f) (T) = (bool(*)(T)) validator;
                if( !_f(val) ){
                    // fprintf(stderr, "ArgFlag: %s setVal argument invalidate!\n", name);
                    return false;
                }
            }

            *((T*)&data) = val;

            isDefault = false;
            return true;
        }

    template<typename T>
    T getVal() {
            if( valueType != _typeID<T>() ){
                // fprintf(stderr, "ArgFlag: %s getVal type(%s) not matched(%s)!\n", name, typeToStr(_typeID<T>()), typeStr());
                return *(T*)0;
            }
            return *((T*)&data);
        }

    std::string getStringVal() {
            std::ostringstream os;
            switch( valueType ){
                case VALUE_BOOL:   os << data.b;
                case VALUE_INT32:  os << data.i32;
                case VALUE_INT64:  os << data.i64;
                case VALUE_FLOAT:  os << data.f;
                case VALUE_DOUBLE: os << data.d;
                case VALUE_PCHAR:  os << data.s;
                default: return "ERROR";
            }
            return os.str();
        }

    static const char* typeToStr(enum value_type _type) {
        switch( _type ){
            case VALUE_BOOL:    return "bool";
            case VALUE_INT32:   return "int32";
            case VALUE_INT64:   return "int64";
            case VALUE_FLOAT:   return "float";
            case VALUE_DOUBLE:  return "double";
            case VALUE_PCHAR:   return "string";
            default: return NULL;
        }
    }

    inline const char* typeStr() {
        return typeToStr(valueType);
    }
};

#ifdef WIN32
template<> inline /*enum*/ ArgFlag::value_type ArgFlag::_typeID<bool>()         { return VALUE_BOOL; }
template<> inline /*enum*/ ArgFlag::value_type ArgFlag::_typeID<int32_t>()      { return VALUE_INT32; }
template<> inline /*enum*/ ArgFlag::value_type ArgFlag::_typeID<int64_t>()      {return VALUE_INT64;}
template<> inline /*enum*/ ArgFlag::value_type ArgFlag::_typeID<float>()        {return VALUE_FLOAT;}
template<> inline /*enum*/ ArgFlag::value_type ArgFlag::_typeID<double>()       {return VALUE_DOUBLE;}
template<> inline /*enum*/ ArgFlag::value_type ArgFlag::_typeID<const char*>()  { return VALUE_PCHAR; }
#else
template<> inline enum ArgFlag::value_type ArgFlag::_typeID<bool>()         {return VALUE_BOOL;}
template<> inline enum ArgFlag::value_type ArgFlag::_typeID<int32_t>()      {return VALUE_INT32;}
template<> inline enum ArgFlag::value_type ArgFlag::_typeID<int64_t>()      { return VALUE_INT64; }
template<> inline enum ArgFlag::value_type ArgFlag::_typeID<float>()        { return VALUE_FLOAT; }
template<> inline enum ArgFlag::value_type ArgFlag::_typeID<double>()       { return VALUE_DOUBLE; }
template<> inline enum ArgFlag::value_type ArgFlag::_typeID<const char*>()  { return VALUE_PCHAR; }
#endif // WIN32


/////////////////////////////////////////////////////////////
//
//  Example:
//      ArgParser  ap;
//      DEFINE_ARG(ap, name, type, defaultVal, infoStr, validator);
//
//
/////////////////////////////////////////////////////////////

class ArgParser {
public:
    ArgParser() : mBinName(NULL) {}
    ArgParser(const char* _binName) : mBinName(_binName) {}

    // if "optional" is false, "needValue" must be true, actually we ignore it
    template<typename T>
    int defineOpt(const char* name, const char* infoStr = "", bool(*validator)(T val) = NULL
            , bool optional = false, bool needValue = true, T defaultVal = T());

    template<typename T>
    int defineTarget(const char* name, const char* infoStr = "", bool(*validator)(T val) = NULL);

    ArgFlag* getInfo(const char* name) {
            std::map<std::string, ArgFlag>::iterator iter;
            if( findArg(name, iter) ){
                return &iter->second;
            }

            fprintf(stderr, "ArgParser: Cant get info of key (%s)\n", name);
            return NULL;
        }

    template<typename T>
    T getVal(const char* name) {
            ArgFlag* af = getInfo(name);
            // if not found, segment fault
            return af->getVal<T>();
        }

    inline bool         getBool(const char* name)   {return getVal<bool>(name);}
    inline int32_t      getInt32(const char* name)  {return getVal<int32_t>(name);}
    inline int64_t      getInt64(const char* name)  {return getVal<int64_t>(name);}
    inline double       getDouble(const char* name) {return getVal<double>(name);}
    inline const char*  getStr(const char* name)    {return getVal<const char*>(name);}
    inline bool         getSwitch(const char* name) {return getVal<bool>(name);}

    bool parseArgs(int argc, const char** argv);

    void printHelp(const char* pre = NULL, const char* suf = NULL);
    /// @param all true to dump with args not in command line
    void dumpArgs(bool all);

private:
    const char*                     mBinName;
    std::map<std::string, ArgFlag>  mOptMap;
    std::map<std::string, ArgFlag>  mOptionalOptMap;
    std::map<std::string, ArgFlag>  mTargetMap;

    void printUsage();
    bool findArg(const char* name, std::map<std::string, ArgFlag>::iterator&);
};

template<typename T>
int ArgParser::defineOpt(const char* name, const char* infoStr, bool(*validator)(T val)
        , bool optional, bool needValue, T defaultVal)
{
    if( optional ){
        ArgFlag _f(name, infoStr, validator, needValue, defaultVal);
        mOptionalOptMap.insert(std::map<std::string, ArgFlag>::value_type(name, _f));
    } else {
        ArgFlag _f(name, infoStr, validator, true, defaultVal);
        mOptMap.insert(std::map<std::string, ArgFlag>::value_type(name, _f));
    }
    return 0;
}

template<typename T>
int ArgParser::defineTarget(const char* name, const char* infoStr, bool(*validator)(T val))
{
    ArgFlag _f(name, infoStr, validator, true, T());
    mTargetMap.insert(std::map<std::string, ArgFlag>::value_type(name, _f));
    return 0;
}

#define DEFINE_ARG_OPT_(type, ap, args,...)      ap.defineOpt<type>(args,##__VA_ARGS__)

#define DEFINE_ARG_CONPULSORY(type, ap, name, infoStr, validator)      \
            DEFINE_ARG_OPT_(type, ap, name, infoStr, validator)

#define DEFINE_ARG_OPTIONAL(type, ap, name, infoStr, validator, need_value, default_value) \
            DEFINE_ARG_OPT_(type, ap, name, infoStr, validator, 1, need_value, default_value)

#define DEFINE_ARG_SWITCH(ap, name, infoStr) \
            DEFINE_ARG_OPT_(bool, ap, name, infoStr, NULL, 1, 0, false)

#define DEFINE_ARG_CONPULSORY_bool(ap, name, infoStr, validator)       DEFINE_ARG_CONPULSORY(bool, ap, name, infoStr, validator)
#define DEFINE_ARG_CONPULSORY_int32(ap, name, infoStr, validator)      DEFINE_ARG_CONPULSORY(int32_t, ap, name, infoStr, validator)
#define DEFINE_ARG_CONPULSORY_int64(ap, name, infoStr, validator)      DEFINE_ARG_CONPULSORY(int64_t, ap, name, infoStr, validator)
#define DEFINE_ARG_CONPULSORY_float(ap, name, infoStr, validator)      DEFINE_ARG_CONPULSORY(float, ap, name, infoStr, validator)
#define DEFINE_ARG_CONPULSORY_double(ap, name, infoStr, validator)     DEFINE_ARG_CONPULSORY(double, ap, name, infoStr, validator)
#define DEFINE_ARG_CONPULSORY_string(ap, name, infoStr, validator)     DEFINE_ARG_CONPULSORY(const char*, ap, name, infoStr, validator)

#define DEFINE_ARG_OPTIONAL_bool(ap, name, infoStr, validator, need_value, default_value)    DEFINE_ARG_OPTIONAL(bool, ap, name, infoStr, validator, need_value, default_value)
#define DEFINE_ARG_OPTIONAL_int32(ap, name, infoStr, validator, need_value, default_value)   DEFINE_ARG_OPTIONAL(int32_t, ap, name, infoStr, validator, need_value, default_value)
#define DEFINE_ARG_OPTIONAL_int64(ap, name, infoStr, validator, need_value, default_value)   DEFINE_ARG_OPTIONAL(int64_t, ap, name, infoStr, validator, need_value, default_value)
#define DEFINE_ARG_OPTIONAL_float(ap, name, infoStr, validator, need_value, default_value)   DEFINE_ARG_OPTIONAL(float, ap, name, infoStr, validator, need_value, default_value)
#define DEFINE_ARG_OPTIONAL_double(ap, name, infoStr, validator, need_value, default_value)  DEFINE_ARG_OPTIONAL(double, ap, name, infoStr, validator, need_value, default_value)
#define DEFINE_ARG_OPTIONAL_string(ap, name, infoStr, validator, need_value, default_value)  DEFINE_ARG_OPTIONAL(const char*, ap, name, infoStr, validator, need_value, default_value)

#define GET_ARG_bool(ap, name)      (ap.getVal<bool>(name))
#define GET_ARG_int32(ap, name)     (ap.getVal<int32_t>(name))
#define GET_ARG_int64(ap, name)     (ap.getVal<int64_t>(name))
#define GET_ARG_float(ap, name)     (ap.getVal<float>(name))
#define GET_ARG_double(ap, name)    (ap.getVal<double>(name))
#define GET_ARG_string(ap, name)    (ap.getVal<const char*>(name))

#define GET_ARG_SWITCH(ap, name)    GET_ARG_bool(ap, name)

#define DEFINE_ARG_CONPULSORY_int   DEFINE_ARG_CONPULSORY_int32
#define DEFINE_ARG_OPTIONAL_int     DEFINE_ARG_OPTIONAL_int32
#define GET_ARG_int                 GET_ARG_int32

}

#endif
