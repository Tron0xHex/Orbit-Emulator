#pragma once

// ReSharper disable CppInconsistentNaming
namespace mg::orbitclient
// ReSharper restore CppInconsistentNaming
{
	class IGetLoginDetailsListener
	{
	public:
		typedef int (__thiscall * CallBackPtrType)(void*, unsigned int requestId, const char* accountId,
		                                      const char* userName, const char* password);
		void (**CallBackPtr)(unsigned int requestId, const char* accountId, const char* userName,
		                     const char* password);
	};
}
