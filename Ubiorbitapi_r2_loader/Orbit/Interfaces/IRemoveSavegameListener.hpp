#pragma once

// ReSharper disable CppInconsistentNaming
namespace mg::orbitclient
// ReSharper restore CppInconsistentNaming
{
	class IRemoveSavegameListener
	{
	public:
		typedef void (__thiscall *CallBackPtr)(void*, unsigned int requestUniqueId, bool deleted);
		void (**callBackPtr)(unsigned int requestUniqueId, bool deleted);
	};
}
