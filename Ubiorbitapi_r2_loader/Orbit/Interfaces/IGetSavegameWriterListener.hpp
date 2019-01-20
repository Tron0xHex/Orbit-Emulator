#pragma once

#include "../SavegameWriter.hpp"

namespace mg::orbitclient {
	class IGetSavegameWriterListener {
	public:
		typedef void(__thiscall *CallBackPtr)(void*, unsigned int requestUniqueId, int unk, SavegameWriter * saveGameWriter);
		void (**callBackPtr)(unsigned int requestUniqueId, int unk, SavegameWriter * saveGameWriter);
	};
}