#pragma once

// ReSharper disable CppInconsistentNaming
namespace mg::orbitclient
// ReSharper restore CppInconsistentNaming
{
	class ISavegameReadListener
	{
	public:
		typedef void (__thiscall *CallBackPtr)(void*, unsigned int requestUniqueId, unsigned int bytesRead);
		void (**callBackPtr)(unsigned int requestId, unsigned int bytesRead);
	};
}
