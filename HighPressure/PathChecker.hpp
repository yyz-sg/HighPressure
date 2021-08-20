#ifndef PATH_CHECKER_HPP
#define PATH_CHECKER_HPP

#include <boost/algorithm/string.hpp>

namespace PATHCHECK {

	enum PathType : uint8_t
	{
		Not_Path = 0,
		Directory = 1,
		Regular_File = 2,
		Others = 3
	};

	class PathChecker
	{
	public:
		PathType CheckPath(std::string Path);
	};
}
#endif