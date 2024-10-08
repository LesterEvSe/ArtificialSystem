#pragma once
#include "ICore.h"
#include "BaseController.h"
#include "GUIHandler.h"
#include "SpawnNovaOption.h"
#include "GoNovaOption.h"
#include "CreateItemOption.h"
#include "PickItemOption.h"
#include "ShowInventoryOption.h"
#include "UseItemOption.h"
#include "DialogLineOption.h"
#include "SetNewDialogOption.h"
#include "TalkToOption.h"
#include "DialogChoiceOption.h"
#include "LookAroundOption.h"
#include "SpawnPackmiOption.h"
#include "SetPathPairOption.h"
#include "CallForHerOption.h"
#include "ShowStatsOption.h"
#include "ChooseCoreOption.h"
#include "KillCoreOption.h"
#include "CreateSavesFileOption.h"

namespace Commands
{
	class StoryOptionsLoader final
	{
	public:
		static BaseController Load(ICore& core)
		{
			BaseController controller;
			controller.add_option("go", std::make_unique<GoNovaOption>(core));
			controller.add_option("mkitem", std::make_unique<CreateItemOption>(core));
			controller.add_option("pick", std::make_unique<PickItemOption>(core));
			controller.add_option("inv", std::make_unique<ShowInventoryOption>(core));
			controller.add_option("useitem", std::make_unique<UseItemOption>(core));
			controller.add_option("d", std::make_unique<DialogLineOption>(core));
			controller.add_option("setnewdialog", std::make_unique<SetNewDialogOption>(core));
			controller.add_option("talkto", std::make_unique<TalkToOption>(core));
			controller.add_option("choice", std::make_unique<DialogChoiceOption>(core));
			controller.add_option("lookaround", std::make_unique<LookAroundOption>(core));
			controller.add_option("spawnnova", std::make_unique<SpawnNovaOption>(core));
			controller.add_option("setnewpath", std::make_unique<SetPathPairOption>(core));
			controller.add_option("callnova", std::make_unique<CallForHerOption>(core));
			controller.add_option("showstats", std::make_unique<ShowStatsOption>(core));
			controller.add_option("choosecore", std::make_unique<ChooseCoreOption>(core));
			controller.add_option("killcore", std::make_unique<KillCoreOption>(core));
			controller.add_option("createsavesfile", std::make_unique<CreateSavesFileOption>(core));
			return controller;
		}
	};
}