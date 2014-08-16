/**
@file
@breif:
*/
#include <iostream>
#include <sstream>
#include "../include/cmdargparser.hpp"

using namespace std;



CmdArgParser::CmdArgParser( string progname )
{
    args[kAppNameArg].type = CmdArgumentType::STRING;
    args[kAppNameArg].strv = progname;
}



CmdArgument parse_string(string value)
{
    if (value.size() == 0)
    {
        throw string("CmdArgParser::parse_string() : NULL arguments");
    }
    CmdArgument arg;
    arg.type = CmdArgumentType::STRING;
    arg.strv = value;
    return arg;
}



CmdArgument parse_int(string value)
{
    CmdArgument arg = parse_string(value);
    istringstream iss(arg.strv);
    iss >> arg.intv;
    if (!iss)
    {
        throw string("CmdArgParser::parse_int() : invalid integer format.");
    }
    arg.type = CmdArgumentType::INTEGER;
    return arg;
}



CmdArgumentDesc CmdArgParser::get_description(string option)
{
    auto elem = registered.find(option);
    if (elem == registered.end())
    {
        cerr << get_usage_message() << endl;
        throw string("Unregistered cmd option passed as input.");
    }
    return elem->second;
}



CmdArgument CmdArgParser::parse_arg(string option, string value)
{
    auto desc = get_description(option);
    switch (desc.type)
    {
    case CmdArgumentType::STRING:
        return parse_string(value);
    case CmdArgumentType::INTEGER:
        return parse_int(value);
    }
}



bool CmdArgParser::validate()
{
    for (auto reg = registered.begin(); reg != registered.end(); reg++)
    {
        string option = reg->first;
        auto desc = reg->second;
        if (desc.mode == CmdArgumentMode::REQUIRED)
        {
            if (!contains(option))
            {
                cerr << get_usage_message() << endl;
                string msg = "Reguired argument is missing: " + option;
                throw msg;
            }
        }
    }
    return true;
}



bool CmdArgParser::parse(int& argc, char**& argv)
{
    for (int i = 2; i < argc; i+=2)
    {
        string opt = argv[i - 1];
        string val = argv[i];
        auto arg = parse_arg(opt, val);
        args[opt] = arg;
    }
    validate();
    return true;
}



void CmdArgParser::register_argument(string name, CmdArgumentDesc desc)
{
    string option = desc.option;
    argnames[name] = option;
    registered[option] = desc;
    if (desc.mode == CmdArgumentMode::OPTIONAL)
    {
        args[option] = parse_arg(option, desc.defaultVal);
    }
}



string CmdArgParser::get_usage_message()
{
    ostringstream oss;
    oss << "USAGE: " << appname() << " ";
    for (auto it = registered.begin(); it != registered.end(); it++)
    {
        switch (it->second.mode)
        {
        case CmdArgumentMode::REQUIRED:
            oss << it->second.option << " value ";
            break;
        case CmdArgumentMode::OPTIONAL:
            oss << "[ " << it->second.option << " value ] ";
            break;
        }
    }
    return oss.str();
}



#ifdef __WORLD_ENGINE_GENERATOR_DEBUG_MODE
void CmdArgParser::print_args()
{
    cout << "Arguments number: " << args.size() << endl;
    int index = 0;
    for (auto it = args.begin(); it != args.end(); it++)
    {
        cout << index++ << ": " << it->first << " = ";
        switch (it->second.type)
        {
        case CmdArgumentType::STRING: cout << it->second.strv << endl; break;
        case CmdArgumentType::INTEGER: cout << it->second.intv << endl; break;
        }
    }
}
#endif