/*****************************************************
File Name	: HighPressure.cpp

Author		: YYZ

Description	: Main entry file for HighPressure program.
******************************************************/

#include "CommandLineParser.hpp"

int main(int argc, char *argv[])
{
    CommandLineParser clp(argc, argv);

    if (clp.GetParseStatus() == CommandLineParseStatus::ParsedVersion)
    {
        //TODO : print version
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