/*****************************************************
File Name	: HighPressure.cpp

Author		: YYZ

Description	: Main entry file for HighPressure program.
******************************************************/
#include "CommandLineParser.hpp"

void PrintVersion()
{
    
}

void PrintHelp()
{

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
        PrintHelp();
    }
}