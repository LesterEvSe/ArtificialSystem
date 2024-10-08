#pragma once
#include "AbstractControllerOption.h"
#include "RelativePathCreator.h"
#include "CommandExceptions.h"
#include "Parser.h"
#include "Command.h"
#include "ICore.h"
#include "RealFileManager.h"
#include "SurroundingsHandler.h"
#include "EndingData.h"
#include <filesystem>

namespace Commands
{
	// showstats
	class ShowStatsOption final : public AbstractControllerOption
	{
	public:
		ShowStatsOption(ICore& _core)
			: AbstractControllerOption(_core) {}

		virtual void execute(const ICommand& _command, const User& sender) override
		{
			auto ptr = m_core.gui().get_terminal_ptr();

			if (_command.has("::help"))
			{
				ptr->print_main("255 permission lvl needed\n");
				ptr->print_main("Shows Nova stats\n");
				return;
			}

			using namespace Memory;

			auto& info = m_core.memory_info().get_main_disk_info().mark;
			auto& maindisk = m_core.memory().get_disk(info);

			try {
				auto a = maindisk.read(DiskPath("\\.awareness"), true);
				ptr->print_main("Awareness: ");
				ptr->print_secondary(Parser::to_string(a.size()) + "\n");

				Story::EndingData::awareness = (a.size() < 10) ? Story::Awareness::LOW : Story::Awareness::MEDIUM;
			}
			catch (...) {}

			try {
				auto a = maindisk.read(DiskPath("\\removed"), true);
				ptr->print_main("Killed: ");
				ptr->print_secondary(Parser::to_string(a.size()) + "\n");

				Story::EndingData::awareness = Story::Awareness::RZERO;
				if (a.size() > 0)
					Story::EndingData::awareness = ((a.size() >= 5) ? Story::Awareness::RALL : Story::Awareness::RMEDIUM);
			}
			catch (...) {}
			
			int fr = 0;
			std::vector<std::string> strs = { "sad", "strange", "smart", "sleepy", "crazy" };
			try {
				for (const auto& str : strs)
				{
					auto a = m_core.memory().get_disk("RED").read(DiskPath("\\myfigures\\" + str + "figurine"), true);
					char c = a.pop<char>();
					fr += c - '0';
				}
				if (m_core.memory().get_disk("RED").is_exists(DiskPath("\\myfigures\\packmifigurine")))
					fr += 5;
			}
			catch (...) {}
			ptr->print_main("Friendliness: ");
			ptr->print_secondary(Parser::to_string(fr) + "\n");
			if (fr < 8)
				Story::EndingData::friendliness = Story::Friendliness::LOW;
			else
				Story::EndingData::friendliness = (fr == 20) ? Story::Friendliness::MAX : Story::Friendliness::MEDIUM;

			Story::EndingData::extralvls = fr;

			return;
		}
	};
}