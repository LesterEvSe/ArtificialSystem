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
#include "EndingChooser.h"
#include <filesystem>

namespace Commands
{
	// choosecore
	class ChooseCoreOption final : public AbstractControllerOption
	{
	public:
		ChooseCoreOption(ICore& _core)
			: AbstractControllerOption(_core) {}

		virtual void execute(const ICommand& _command, const User& sender) override
		{
			auto ptr = m_core.gui().get_terminal_ptr();

			if (_command.has("::help"))
			{
				ptr->print_main("255 permission lvl needed\n");
				ptr->print_main("Starts last chapter\n");
				return;
			}

			using namespace Memory;
			using namespace Story;

			auto& info = m_core.memory_info().get_main_disk_info().mark;
			auto& maindisk = m_core.memory().get_disk(info);

			Endings ending = EndingChooser::calculate_ending();

			std::string path = "CORE:\\.scripts\\chapter3\\" + s_scripts[ending];

			Command cmd("\"" + ptr->get_path().full_path_str() + "\" run \"" + path + "\"");
			m_core.execute(cmd, User("amogus", true, 255));

			return;
		}

	private:
		std::unordered_map<Story::Endings, std::string> s_scripts = {
			{ Story::Endings::Base, "base.txt" },
			{ Story::Endings::BaseFriend, "basefriend.txt" },
			{ Story::Endings::NaN, "nan.txt" },
			{ Story::Endings::NaNFriend, "nanfriend.txt" },
			{ Story::Endings::NaNKilled, "nankilled.txt" },
			{ Story::Endings::NaNKilledPlus, "nankilledplus.txt" },
			{ Story::Endings::Zero, "zero.txt" },
		};
	};
}