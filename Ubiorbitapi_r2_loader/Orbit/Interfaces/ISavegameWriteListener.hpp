#pragma once

namespace mg::orbitclient
{
	class ISavegameWriteListener
	{
	public:
		typedef void (__thiscall *CallBackPtr)(void*, unsigned int requestId, unsigned int bytesWritten);
		void (**callBackPtr)(unsigned int requestId, unsigned int bytesWritten);
	};
}
