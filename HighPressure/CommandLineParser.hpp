/*****************************************************
File Name	: CommandLineParser.hpp

Author		: YYZ

Description	: Header file for command line parsing object.
			  Parse command line arguments during constructor.
			  Expose function to get parsed arguments and parsing
			  status.
******************************************************/

#ifndef COMMAND_LINE_PARSER_HPP
#define COMMAND_LINE_PARSER_HPP

#include <boost/algorithm/string.hpp>

enum class CommandLineParseStatus
{
	NotParsed = 0,
	ParsedVersion = 1,
	ParsedPaths = 2,
	ParsingError = 3
};

class CommandLineParser
{
	bool m_boRecursive;
	bool m_boPrintVersion;
	std::string m_strInputDirectory;
	std::string m_strOutputFileName;
	std::string m_strError;
	CommandLineParseStatus m_enStatus;

public:
	CommandLineParser(int argc, char* argv[]);

	const CommandLineParseStatus GetParseStatus() { return m_enStatus; }

	const std::string GetInputDirectory() { return m_strInputDirectory; }

	const std::string GetOutputFileName() { return m_strOutputFileName; }

	const bool GetRecursive() { return m_boRecursive; }

	const bool GetPrintVersion() { return m_boPrintVersion; }
};

#endif