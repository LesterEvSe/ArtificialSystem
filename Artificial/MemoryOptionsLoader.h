#pragma once
#include "ICore.h"
#include "BaseController.h"
#include "GUIHandler.h"
#include "MemoryCreateOption.h"
#include "ShowFileListOption.h"
#include "ChangeDirectoryOption.h"
#include "MemoryDeleteOption.h"
#include "MemoryWriteOption.h"
#include "RenameFileOption.h"
#include "MoveFileOption.h"
#include "CopyFileOption.h"
#include "ChangeModificatorsOption.h"

namespace Commands
{
	class MemoryOptionsLoader final
	{
	public:
		static BaseController Load(ICore& core)
		{
			BaseController controller;
			controller.add_option("mk", std::make_unique<MemoryCreateOption>(core));
			controller.add_option("ls", std::make_unique<ShowFileListOption>(core));
			controller.add_option("cd", std::make_unique<ChangeDirectoryOption>(core));
			controller.add_option("rm", std::make_unique<MemoryDeleteOption>(core));
			controller.add_option("write", std::make_unique<MemoryWriteOption>(core));
			controller.add_option("rename", std::make_unique<RenameFileOption>(core));
			controller.add_option("move", std::make_unique<MoveFileOption>(core));
			controller.add_option("copy", std::make_unique<CopyFileOption>(core));
			controller.add_option("chmod", std::make_unique<ChangeModificatorsOption>(core));
			return controller;
		}
	};
}