#pragma once
#include <string>
#include <sstream>

namespace Commands
{
	static class Parser
	{
	public:

		template <typename T>
		static T from_string(const std::string& s)
		{
			std::stringstream ss(s);
			T t = T();
			ss >> t;
			return t;
		}

		template <typename T>
		static std::string to_string(T t)
		{
			std::stringstream ss;
			ss << t;
			return ss.str();
		}
	};
}
