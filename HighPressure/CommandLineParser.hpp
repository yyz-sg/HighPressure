#ifndef COMMAND_LINE_PARSER_HPP
#define COMMAND_LINE_PARSER_HPP

#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>
namespace po = boost::program_options;

class CommandLineParser
{
public:
	CommandLineParser(int argc, char* argv[]);

	std::string GetParseStatus();

	std::string GetInputDirectory();

	std::string GetOutputFileName();

	bool GetRecursive();
};

#endif