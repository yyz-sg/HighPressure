/*****************************************************
File Name	: CommandLineParser.cpp

Author		: YYZ

Description	: Source file for command line parsing object.
			  Parse command line arguments during constructor.
			  Expose function to get parsed arguments and parsing
			  status.
******************************************************/

#include "CommandLineParser.hpp"
#include <boost/program_options.hpp>

namespace po = boost::program_options;

CommandLineParser::CommandLineParser(int argc, char* argv[])
{
	/**** Initialize Member Variables ****/
	m_enStatus = CommandLineParseStatus::NotParsed;
	m_boRecursive = false;
	m_boPrintVersion = false;
	m_strInputDirectory = "";
	m_strOutputFileName = "";
	m_strError = "";
	/**** Initialize Member Variables ****/

	/**** Try Parse Command Line ****/
	po::options_description cmdline_options("Command line input");
	cmdline_options.add_options()
		("input-directory", "directory to be compressed")
		("output-file-name", "output zip file name")
		("version,v", "print version string")
		("recursive,r", "recursively compress files in sub-directories")
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
	catch (std::exception /*e*/)
	{
		//Parse Error, update status and error code
		m_strError = "Too many argument or wrong argument provided.";
		m_enStatus = CommandLineParseStatus::ParsingError;
	}
	/**** Try Parse Command Line ****/

	/**** Store Parsing Result ****/
	if (cmdline_map.count("version"))
	{
		m_boPrintVersion = true;
		m_enStatus = CommandLineParseStatus::ParsedVersion;
	}
	//If both directory and output file name are specified
	else if(cmdline_map.count("input-directory") && cmdline_map.count("output-file-name"))
	{
		//Get all 3 parameters
		m_boRecursive = (bool)cmdline_map.count("recursive");
		m_strInputDirectory = cmdline_map["input-directory"].as<std::string>();
		m_strOutputFileName = cmdline_map["output-file-name"].as<std::string>();

		//Update Status
		m_enStatus = CommandLineParseStatus::ParsedPaths;
	}
	//Only 1 directory input
	else if(m_enStatus == CommandLineParseStatus::NotParsed)
	{
		m_strError = "Too little argument.";
		m_enStatus = CommandLineParseStatus::ParsingError;
	}
	/**** Store Parsing Result ****/
}