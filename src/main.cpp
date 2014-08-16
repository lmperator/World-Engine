/**
@file
@brief: World Engine - Michal Michalski, Lukasz Wojdanowicz
*/
#include <iostream>
#include <string>


int main( int argc, char* argv[] )
{
	const std::string kDefaultInputFileName = "spec.cfg";
	const std::string kDefaultOutputFileName = "planet.pmd";

	std::string inputFileName = kDefaultInputFileName;
	std::string outputFileName = kDefaultOutputFileName;
	switch (argc)
	{
	case 1:
		std::cout << "Using default file names." << std::endl;
		break;
	case 2:
		inputFileName = argv[1];
		std::cout << "Using default output file name." << std::endl;
		break;
	case 3:
		inputFileName = argv[1];
		outputFileName = argv[2];
		break;
	default:
		std::cout << "Usage: worldgen <<input>> <<output>>" << std::endl;
		return -1;
	}
	std::cout << "Input file: " << inputFileName << std::endl;
	std::cout << "Output file: " << outputFileName << std::endl;
	return 0;
}
