/**
@file
@brief: World Engine - Michal Michalski, Lukasz Wojdanowicz
*/
#include <iostream>
#include <string>

#include "../include/cmdargparser.hpp"

using namespace std;



int main( int argc, char* argv[] )
try 
{
    cout << "Hello in World Engine - Generator" << endl;

    CmdArgParser parser(argv[0]);
    CmdArgumentDesc inputDesc, outputDesc;

    inputDesc.mode = CmdArgumentMode::REQUIRED;
    inputDesc.type = CmdArgumentType::STRING;
    inputDesc.option = "-i";
 
    outputDesc.mode = CmdArgumentMode::OPTIONAL;
    outputDesc.type = CmdArgumentType::STRING;
    outputDesc.option = "-o";
    outputDesc.defaultVal = "planet.pmd";

    parser.register_argument( "input", inputDesc );
    parser.register_argument( "output", outputDesc );
    
    parser.parse(argc, argv);
    cout << "input: " << parser["input"].strv << endl;
    cout << "output: " << parser["output"].strv << endl;

    return 0;
}
catch (string msg)
{
    cout << "Exception occured: " << msg << endl;
} 