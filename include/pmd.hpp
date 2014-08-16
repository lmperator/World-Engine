/**
   @file
   @brief: World Engine - Generator - Michal Michalski, Lukasz Wojdanowicz
*/

#ifndef __WORLD_ENGINE_GENERATOR_PMD_HPP
#define __WORLD_ENGINE_GENERATOR_PMD_HPP

#include <fstream>
#include <string>


struct PlanetSector;
typedef unsigned int SectorId;


struct PmdHeader
{
    // file meta info
    std::string filename;

    // planet's meta info
    int radius;
};
std::ostream& operator<<(std::ostream&, const PmdHeader&);
std::istream& operator>>(std::istream&, PmdHeader&);



struct PmdFile
{
    PmdHeader* header;
    
    PlanetSector* load();
};

#endif // __WORLD_ENGINE_GENERATOR_PMD_HPP