//+-------------------------------------------------------------------------------------------
//
//  Copyright (C) Microsoft Corporation, 1996.  All Rights Reserved.
//
//  Project:    Microsoft Internet Chat (MIC)
//
//  Include:    Channel Service Interfaces (MicSvc.h)
//
//  Notes:      See MicSvc.doc for documentation.
//
//--------------------------------------------------------------------------------------------

#if !defined(__MICSVC_H_)
#define __MICSVC_H_


interface IMicChannel;
interface IMicMember;
interface IMicService;

typedef IMicChannel * PMICCHANNEL;
typedef IMicMember * PMICMEMBER;
typedef IMicService * PMICSERVICE;

interface IMicChannel
{
    STDMETHOD_(MICERR, SendTextA)(PMICMEMBER pMicMember, MIC_MODE * pModeMask, PCSTR pTextA, ULONG cText = (ULONG)-1) PURE;
    STDMETHOD_(MICERR, SendTextW)(PMICMEMBER pMicMember, MIC_MODE * pModeMask, PCWSTR pTextW, ULONG cText = (ULONG)-1) PURE;
    STDMETHOD_(MICERR, SendData)(PMICMEMBER pMicMember, MIC_MODE * pModeMask, PVOID pData, ULONG cData) PURE;
    STDMETHOD_(MICERR, Broadcast)(PMICMEMBER pMicMember, MIC_MODE * pModeMask, PVOID pData, ULONG cData) PURE;
    STDMETHOD_(MICERR, SendWhisperTextA)(PMICMEMBER pMicMember, PMICMEMBER * pMembers, ULONG cMembers, PCSTR pTextA, ULONG cText = (ULONG)-1) PURE;
    STDMETHOD_(MICERR, SendWhisperTextW)(PMICMEMBER pMicMember, PMICMEMBER * pMembers, ULONG cMembers, PCWSTR pTextW, ULONG cText = (ULONG)-1) PURE;
    STDMETHOD_(MICERR, SendWhisperData)(PMICMEMBER pMicMember, PMICMEMBER * pMembers, ULONG cMembers, PVOID pData, ULONG cData) PURE;
    STDMETHOD_(MICERR, GetName)(PCWSTR * ppName, UINT * pcName) PURE;
    STDMETHOD_(MICERR, SetTopic)(PCWSTR pTopic, UINT cTopic = ~0) PURE;
    STDMETHOD_(MICERR, GetTopic)(PCWSTR * ppTopic, UINT * pcTopic) PURE;
    STDMETHOD_(MICERR, GetServiceValue)(PCWSTR pName, PWSTR pValue, ULONG * pcValue) PURE;
    STDMETHOD_(MICERR, GetValue)(PCWSTR pName, PWSTR pValue, ULONG * pcValue) PURE;
};

interface IMicMember
{
    STDMETHOD_(MICERR, SendTextA)(PMICMEMBER pMicMember, PCSTR pTextA, ULONG cText = (ULONG)-1) PURE;
    STDMETHOD_(MICERR, SendTextW)(PMICMEMBER pMicMember, PCWSTR pTextW, ULONG cText = (ULONG)-1) PURE;
    STDMETHOD_(MICERR, SendData)(PMICMEMBER pMicMember, PVOID pData, ULONG cData) PURE;
    STDMETHOD_(MICERR, Broadcast)(PMICMEMBER pMicMember, PVOID pData, ULONG cData) PURE;
    STDMETHOD_(MICERR, GetUserId)(MIC_ID * pUid) PURE;
    STDMETHOD_(MICERR, GetMemberId)(MIC_ID * pMid) PURE;
    STDMETHOD_(MICERR, GetMemberMode)(MIC_MODE * pMode) PURE;
    STDMETHOD_(MICERR, SetMemberMode)(MIC_MODE Mode, MIC_MODE Mask) PURE;
    STDMETHOD_(MICERR, GetAlias)(PCWSTR * ppAlias) PURE;
    STDMETHOD_(MICERR, GetUserParam)(DWORD * pdwParam) PURE;
    STDMETHOD_(MICERR, SetUserParam)(DWORD dwParam) PURE;
    STDMETHOD_(MICERR, Kick)(PCWSTR pReason) PURE;
};

interface IMicService
{
    STDMETHOD_(MICERR, SetChannel)(PMICCHANNEL pMicChannel) PURE;
    STDMETHOD_(MICERR, AddMember)(PMICMEMBER pMicMember) PURE;
    STDMETHOD_(MICERR, DelMember)(PMICMEMBER pMicMember) PURE;
    STDMETHOD_(MICERR, RecvTextA)(PMICMEMBER pMicMember, PCSTR pTextA, ULONG cText) PURE;
    STDMETHOD_(MICERR, RecvTextW)(PMICMEMBER pMicMember, PCWSTR pTextW, ULONG cText) PURE;
    STDMETHOD_(MICERR, RecvData)(PMICMEMBER pMicMember, PVOID pData, ULONG cData) PURE;
    STDMETHOD_(MICERR, RecvBroadcast)(PMICMEMBER pMicMember, PVOID pData, ULONG cData) PURE;
};

extern "C" PMICSERVICE MicCreateService(REFIID riid);

typedef PMICSERVICE STDAPICALLTYPE FnMicCreateService(REFIID riid);

#endif
