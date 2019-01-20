#pragma once

#include "../SavegameInfo.hpp"

namespace mg::orbitclient {
	class IGetSavegameListListener
	{
	public:
		typedef void(__thiscall *CallBackPtr)(void*, unsigned int requestUniqueId, SavegameInfo * saveGameInfoList, unsigned int listSize);
		void(**callBackPtr)(unsigned int requestUniqueId, SavegameInfo * saveGameInfoList, unsigned int listSize);
	};
}