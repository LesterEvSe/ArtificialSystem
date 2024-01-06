#pragma once
#include <unordered_map>
#include "Hash.h"
#include <string>

namespace Commands
{
	struct NetData final
	{
		std::string b64data = "";
		hash_t password_hash = 0;
		uint8_t lvl = 0;
	};

	class NetContainer final
	{
	public:
		void add_new(const std::string& address, const NetData& data);
		bool has(const std::string& address);
		const NetData& get(const std::string& address);

	private:
		std::unordered_map<std::string, NetData> m_data;
	};
}