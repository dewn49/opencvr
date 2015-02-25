//------------------------------------------------------------------------------
// File: minterfacemgrimpl.hpp
//
// Desc: Interface manager for Data Mining.
//
// Copyright (c) 2014-2018. veyesys.com All rights reserved.
//------------------------------------------------------------------------------
#ifndef __M_INTERFACE_MGR_IMPL_HPP__
#define __M_INTERFACE_MGR_IMPL_HPP__

inline MiningInterfaceMgr::MiningInterfaceMgr(u32 id, 
			Factory &pFactory, MiningInterface * pDevice)
:m_id(id), m_pDevice(pDevice), m_pFactory(pFactory)
{
	Init();
}
inline MiningInterfaceMgr::~MiningInterfaceMgr()
{
}

inline BOOL MiningInterfaceMgr::Init()
{
	/* Reg the data callback from factory */
	MMReqStream type = MM_STREAM_LAST;
	m_pDevice->GetReqStream( type);
	/* Current we only use sub raw stream */
	if (type == MM_STREAM_SUB_RAW)
	{
		m_pFactory.RegSubRawCallback(m_id, 
			(DeviceRawCallbackFunctionPtr)MiningInterfaceMgr::RawHandler, 
				(void *)this);
	}
	return TRUE;
}

inline void MiningInterfaceMgr::RawHandler1(RawFrame& frame)
{
	m_pDevice->ProcessRaw(frame);
}

inline void MiningInterfaceMgr::RawHandler(RawFrame& frame, void * pParam)
{
    MiningInterfaceMgr *pMgr = static_cast<MiningInterfaceMgr *> (pParam);
    
    return pMgr->RawHandler1(frame);
}

#endif /* __M_INTERFACE_MGR_IMPL_HPP__ */
