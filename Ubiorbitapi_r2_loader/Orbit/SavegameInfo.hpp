#pragma once

#include "../stdafx.h"

// ReSharper disable CppInconsistentNaming
namespace mg::orbitclient
// ReSharper restore CppInconsistentNaming
{
	class UPLAY_API SavegameInfo
	{
		wstring name;
		unsigned int id;
		unsigned long size;
		unsigned long productId;
	public:
		SavegameInfo(unsigned int, unsigned int, unsigned long, const wstring&);
		unsigned int GetSavegameId();
		unsigned int GetSize();
		unsigned short const* GetName();
	};
}

//------------------------------------------------------------------------------
inline mg::orbitclient::SavegameInfo::SavegameInfo(const unsigned int id, const unsigned int productId,
                                                   const unsigned long size, const wstring& name)
{
	this->id = id;
	this->size = size;
	this->name = name;
	this->productId = productId;
}

//------------------------------------------------------------------------------
// ReSharper disable CppMemberFunctionMayBeConst
inline unsigned int mg::orbitclient::SavegameInfo::GetSavegameId()
// ReSharper restore CppMemberFunctionMayBeConst
{
	return id;
}

//------------------------------------------------------------------------------
// ReSharper disable CppMemberFunctionMayBeConst
inline unsigned int mg::orbitclient::SavegameInfo::GetSize()
// ReSharper restore CppMemberFunctionMayBeConst
{
	return size;
}

//------------------------------------------------------------------------------
// ReSharper disable CppMemberFunctionMayBeConst
inline unsigned short const* mg::orbitclient::SavegameInfo::GetName()
// ReSharper restore CppMemberFunctionMayBeConst
{
	return reinterpret_cast<const unsigned short*>(&name.c_str()[0]);
}
