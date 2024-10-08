#pragma once
#include "BaseController.h"
#include "AddUserOption.h"
#include "ChangeUserOption.h"
#include "UserListOption.h"
#include "DeleteUserOption.h"
#include "AddLvlsToUserOption.h"

namespace Commands
{
	class UsersOptionsLoader final
	{
	public:
		static BaseController Load(ICore& core)
		{
			BaseController controller;
			controller.add_option("adduser", std::make_unique<AddUserOption>(core));
			controller.add_option("userlist", std::make_unique<UserListOption>(core));
			controller.add_option("changeuser", std::make_unique<ChangeUserOption>(core));
			controller.add_option("deleteuser", std::make_unique<DeleteUserOption>(core));
			controller.add_option("addlvls", std::make_unique<AddLvlsToUserOption>(core));
			return controller;
		}
	};
}
