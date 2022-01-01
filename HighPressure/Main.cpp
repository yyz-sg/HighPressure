/*****************************************************
File Name	: Main.cpp

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

void PrintHelp()
{
    std::cout << "Usage : HighPressure [-v] [-r] [Input Directory] [Output file name]\n" \
        "  [Input Directory]   The directory to compress\n" \
        "  [Output file name]  [Output file name].zip that will be created in one directory up of [Input Directory]\n" \
        "  -v                  Print version and quit (even if there are other argument)\n" \
        "  -r (optional)       Recursively compress files and directory in the [Input Directory]\n"
        << std::endl;
}

int main(int argc, char *argv[])
{
    printf("Success!\n");
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
        std::cout << clp.GetError() << std::endl;
        PrintHelp();
    }
}