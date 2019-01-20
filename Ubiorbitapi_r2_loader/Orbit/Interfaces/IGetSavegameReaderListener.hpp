#pragma once

#include "../SavegameReader.hpp"

namespace mg::orbitclient {
	class IGetSavegameReaderListener {
	public:
		typedef void(__thiscall *CallBackPtr)(void*, unsigned int requestUniqueId, int unk, SavegameReader * saveGameReader);
		void (**callBackPtr)(unsigned int requestUniqueId, int unk, SavegameReader * saveGameReader);
	};
}