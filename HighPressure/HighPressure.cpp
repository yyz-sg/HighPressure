#include <iostream>
#include <exception>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

int main(int argc, char *argv[])
{
    po::options_description cmdline_options("Command line input");
    cmdline_options.add_options()
        ("version,v", "print version string")
        ("recersive,r", "recursively compress files in sub-directories")
        ("input-directory", "directory to compress")
        ("output-file-name", "output zip file")
        ;
    po::positional_options_description p;
    p.add("input-directory", 1);
    p.add("output-file-name", 1);
    po::variables_map cmdline_map;
    try
    {
        po::store(po::command_line_parser(argc, argv).options(cmdline_options).positional(p).run(), cmdline_map);
        po::notify(cmdline_map);
    }
    catch (std::exception e)
    {
        std::cout << e.what() << std::endl;
    }
    bool recersive = false;
    if (cmdline_map.count("version"))
    {
        std::cout << "Version : High Pressure 1.0" << std::endl;
    }
    else
    {
        if (cmdline_map.count("recersive"))
        {
            recersive = true;
            std::cout << "Recersive set to true" << std::endl;
        }

    }
}