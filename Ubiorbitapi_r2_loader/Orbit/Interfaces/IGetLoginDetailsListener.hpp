#pragma once

namespace mg::orbitclient
{
	class IGetLoginDetailsListener
	{
	public:
		typedef int (__thiscall *CallBackPtr)(void*, unsigned int requestUniqueId, const char* accountId,
		                                      const char* userName, const char* password);
		void (**callBackPtr)(unsigned int requestUniqueId, const char* accountId, const char* userName,
		                     const char* password);
	};
}
