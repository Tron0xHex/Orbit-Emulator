#pragma once

#include "../SavegameReader.hpp"

// ReSharper disable CppInconsistentNaming
namespace mg::orbitclient
// ReSharper restore CppInconsistentNaming
{
	class IGetSavegameReaderListener
	{
	public:
		typedef void (__thiscall *CallBackPtr)(void*, unsigned int requestUniqueId, int unk,
		                                       SavegameReader* saveGameReader);
		void (**callBackPtr)(unsigned int requestUniqueId, int unk, SavegameReader* saveGameReader);
	};
}
