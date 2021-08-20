/*****************************************************
File Name	: HighPressure.cpp

Author		: YYZ

Description	: Main entry file for HighPressure program.
******************************************************/

#include <iostream>
#include "Version.h"
#include "CommandLineParser.hpp"

void PrintVersion()
{
    std::cout <<
        "HighPressure version : " 
        + std::to_string(HIGHPRESSURE_MAJOR_VERSION_NUMBER) + "."
        + std::to_string(HIGHPRESSURE_MINOR_VERSION_NUMBER) + "."
        + std::to_string(HIGHPRESSURE_PATCH_NUMBER)
        << std::endl;
}

int main(int argc, char *argv[])
{
    CommandLineParser clp(argc, argv);

    if (clp.GetParseStatus() == CommandLineParseStatus::ParsedVersion)
    {
        PrintVersion();
    }
    else if (clp.GetParseStatus() == CommandLineParseStatus::ParsedPaths)
    {
        //TODO : Check path and continue with compression
    }
    else if (clp.GetParseStatus() == CommandLineParseStatus::ParsingError)
    {
        //TODO : print help maybe?
    }
}