/**
@file
@brief:
*/

#ifndef __WORLD_ENGINE_GENERATOR_CMDARGPARSER_HPP
#define __WORLD_ENGINE_GENERATOR_CMDARGPARSER_HPP

#include <cstdint>
#include <string>//test publiczniści kodu
#include <map>


// debug mode on, comment next line to turn off.
//#define __WORLD_ENGINE_GENERATOR_DEBUG_MODE




enum class CmdArgumentMode
{
    REQUIRED,
    OPTIONAL
};



enum class CmdArgumentType
{
    INTEGER,
    STRING,
};



struct CmdArgumentDesc
{
    CmdArgumentType type;
    CmdArgumentMode mode;
    std::string option;
    std::string defaultVal;
};



struct CmdArgument
{
    CmdArgumentType type;
    struct
    {
        std::string strv;
        int intv;
    };
};



class CmdArgParser
{
public:
    CmdArgParser( std::string );

    bool parse(int&, char**&);
    void register_argument(std::string, CmdArgumentDesc);
    std::string get_usage_message();

    inline std::string appname()
    { 
        return args[kAppNameArg].strv; 
    }
    inline CmdArgument operator[](const std::string name)
    { 
        std::string opt = argnames[name];
        return args[opt];
    }
    inline bool contains(std::string name)
    {
        auto pos = args.find(name);
        return pos != args.end();
    }

    inline int size() 
    {
        return args.size(); 
    }

#ifdef __WORLD_ENGINE_GENERATOR_DEBUG_MODE
    void print_args();
#endif

private:
    CmdArgument parse_arg(std::string, std::string);
    CmdArgumentDesc get_description(std::string);
    bool validate();

    typedef std::map<std::string, CmdArgumentDesc> ArgsDescMap;
    typedef std::map<std::string, CmdArgument> ArgsMap;
    typedef std::map<std::string, std::string> ArgsNamesMap;
    
    ArgsNamesMap argnames;
    ArgsDescMap registered;
    ArgsMap args;

    const std::string kAppNameArg = "__app_name__";
};



#endif // __WORLD_ENGINE_GENERATOR_CMDARGPARSER_HPP
