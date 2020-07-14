#pragma once

#include "../SavegameWriter.hpp"

// ReSharper disable CppInconsistentNaming
namespace mg::orbitclient
// ReSharper restore CppInconsistentNaming
{
	class IGetSavegameWriterListener
	{
	public:
		typedef void (__thiscall *CallBackPtr)(void*, unsigned int requestUniqueId, int unk,
		                                       SavegameWriter* saveGameWriter);
		void (**callBackPtr)(unsigned int requestUniqueId, int unk, SavegameWriter* saveGameWriter);
	};
}
