#pragma once

#include "../SavegameInfo.hpp"

// ReSharper disable CppInconsistentNaming
namespace mg::orbitclient
// ReSharper restore CppInconsistentNaming
{
	class IGetSavegameListListener
	{
	public:
		typedef void (__thiscall *CallBackPtr)(void*, unsigned int requestUniqueId, SavegameInfo* saveGameInfoList,
		                                       unsigned int listSize);
		void (**callBackPtr)(unsigned int requestUniqueId, SavegameInfo* saveGameInfoList, unsigned int listSize);
	};
}
