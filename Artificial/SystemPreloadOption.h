#pragma once
#include "CommandExceptions.h"
#include "Core.h"

namespace Commands
{
	// preload
	class SystemPreloadOption final : public AbstractControllerOption
	{
	public:
		SystemPreloadOption(ICore& _core)
			: AbstractControllerOption(_core) {}

		virtual void execute(const ICommand& _command, const User& sender) override
		{
			auto ptr = m_core.gui().get_terminal_ptr();

			if (_command.has("::help"))
			{
				ptr->print_main("255 permission lvl needed\n");
				ptr->print_main("Restarts some system classes.\n");

				return;
			}

			if (!sender.system())
				throw PermissionException("(SystemPreloadOption) Sender has low permission lvl");

			using namespace Memory;

			auto& maindisk = m_core.memory().get_disk(m_core.memory_info().get_main_disk_info().mark);
			if (!maindisk.is_exists(DiskPath("\\system")))
				maindisk.create(DiskPath("\\system"), Permissions(true, 255, 255, 255, 0), FileT::DIR, true);
			
			if (maindisk.is_exists(DiskPath("\\system\\.colours")))
			{
				DataQueue data = maindisk.read(DiskPath("\\system\\.colours"), true);
				std::string colours = std::string(data.get_data(), data.size());

				Command command_mk("\"" + _command.get("path") + "\"" + " changecolours " + colours);
				m_core.execute(command_mk, sender);
			}
			if (maindisk.is_exists(DiskPath("\\system\\.textcolours")))
			{
				DataQueue data = maindisk.read(DiskPath("\\system\\.textcolours"), true);
				std::string colours = std::string(data.get_data(), data.size());

				Command command_mk("\"" + _command.get("path") + "\"" + " changetextcolours " + colours);
				m_core.execute(command_mk, sender);
			}
		}
	};
}
