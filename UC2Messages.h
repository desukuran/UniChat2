//
//	UniChat: UniChat 2 Messages Definition
//
//	(C) Programmed by Kim, Soomin, Feb 1998
//	SDS Media Lab
//	Information Technology Institue
//	Samsung Data Systems, Co., Seoul, South Korea

#ifndef __UC2MESSAGES_H
#define __UC2MESSAGES_H

#include <csface.h>

////////////////////////////////////////////////////////////////////////////////////////////
// See resource.h
//	where #define _APS_NEXT_COMMAND_VALUE         32798	// 0x8000
// this message should be in the range WM_USER(0x0400) to 0x7fff
#define BASE	(WM_USER + 200)
const UINT	CS_CMD_START				= BASE;
const UINT	CSMSG_CMD_ERROR				= BASE + CSMSG_TYPE_ERROR;
const UINT	CSMSG_CMD_LOGIN				= BASE + CSMSG_TYPE_LOGIN;
const UINT	CSMSG_CMD_TEXT_A			= BASE + CSMSG_TYPE_TEXT_A;
const UINT	CSMSG_CMD_TEXT_W			= BASE + CSMSG_TYPE_TEXT_W;
const UINT	CSMSG_CMD_DATA				= BASE + CSMSG_TYPE_DATA;
const UINT	CSMSG_CMD_ADDCHANNEL		= BASE + CSMSG_TYPE_ADDCHANNEL;
const UINT	CSMSG_CMD_ADDMEMBER			= BASE + CSMSG_TYPE_ADDMEMBER;
const UINT	CSMSG_CMD_GOTMEMLIST		= BASE + CSMSG_TYPE_GOTMEMLIST;
const UINT	CSMSG_CMD_DELMEMBER			= BASE + CSMSG_TYPE_DELMEMBER;
const UINT	CSMSG_CMD_DELCHANNEL		= BASE + CSMSG_TYPE_DELCHANNEL;
const UINT	CSMSG_CMD_MODEMEMBER		= BASE + CSMSG_TYPE_MODEMEMBER;
const UINT	CSMSG_CMD_MODECHANNEL		= BASE + CSMSG_TYPE_MODECHANNEL;
const UINT	CSMSG_CMD_WHISPERTEXT_A		= BASE + CSMSG_TYPE_WHISPERTEXT_A;
const UINT	CSMSG_CMD_WHISPERTEXT_W		= BASE + CSMSG_TYPE_WHISPERTEXT_W;
const UINT	CSMSG_CMD_WHISPERDATA		= BASE + CSMSG_TYPE_WHISPERDATA;
const UINT	CSMSG_CMD_NEWTOPIC			= BASE + CSMSG_TYPE_NEWTOPIC;
const UINT	CSMSG_CMD_PROPERTYDATA		= BASE + CSMSG_TYPE_PROPERTYDATA;
const UINT	CSMSG_CMD_QUERYDATA			= BASE + CSMSG_TYPE_QUERYDATA;
const UINT	CSMSG_CMD_PRIVATEMSG		= BASE + CSMSG_TYPE_PRIVATEMSG;
const UINT	CSMSG_CMD_NEWNICK			= BASE + CSMSG_TYPE_NEWNICK;
const UINT	CSMSG_CMD_INVITE			= BASE + CSMSG_TYPE_INVITE;
const UINT	CSMSG_CMD_SERVERMSG_TEXT_A	= BASE + CSMSG_TYPE_SERVERMSG_TEXT_A;
const UINT	CSMSG_CMD_SERVERMSG_TEXT_W	= BASE + CSMSG_TYPE_SERVERMSG_TEXT_W;
#undef BASE

#define BASE	(CSMSG_CMD_SERVERMSG_TEXT_W + 10)
const UINT	CMD_CONNECT_CONNECTING		= BASE;
const UINT	CMD_CONNECT_LOGIN			= BASE + 1;
const UINT	CMD_CONNECT_BACKUPID		= BASE + 2;
const UINT	CMD_CONNECT_FAILURE			= BASE + 3;

const UINT	CMD_QUERY_ERROR				= BASE + 10;
const UINT	CMD_QUERY_NOMATCHES			= BASE + 11;
const UINT	CMD_QUERY_CHANNELS			= BASE + 12;
const UINT	CMD_QUERY_CHANNELS_END		= BASE + 13;
const UINT	CMD_QUERY_MEMBERS			= BASE + 14;
const UINT	CMD_QUERY_MEMBERS_END		= BASE + 15;
const UINT	CMD_QUERY_GET_REALNAME		= BASE + 16;

const UINT	CMD_CHANNELFULL_RETRY		= BASE + 17;	// Retry

const UINT	CS_CMD_END					= CMD_QUERY_GET_REALNAME;
#undef BASE

enum ACTOR_COMMANDS
{	// Command Enumerators
	CMD_BEGIN = 0,
// Management
	CMD_MEMBER_INFO,	// X`nCmd`nVersion`nCharID`nBubbleKind`strHandle`strRealName`strProfile`ptTID`wState
	CMD_MEMBER_ACTOR,	// X`nCmd`nCharID`nBubbleKind	(changed his Actor)
	CMD_NEWS,			// X`nCmd`message
// Position Move
CMD_MOVE,
	CMD_MOVEF,			// X`nCmd`ptTID`wState
	CMD_MOVEB,
	CMD_RES_MOVE,
// State Change
CMD_STATE,
	CMD_STAND,			// State
	CMD_MORPH,
	CMD_DOZE,
	CMD_TURNL,
	CMD_TURNR,
	CMD_RES_STATE,		// reserved
// Actions				// CMD_ACTION is for Just repositioning message
CMD_ACTION,				// Y`nCmd`ptTID`wState` (to verify synchronization)
	CMD_CHAT,
	CMD_ENTER,
	CMD_EXIT,
	CMD_SMILE,
	CMD_MAD,
	CMD_HELLO,
	CMD_CRY,
	CMD_SCRATCH,
	CMD_PICK,
	CMD_SPECIAL,
	CMD_PUNCH,			// Y`nCmd`ptTID`wState`NickTo`
	CMD_BEATEN,
	CMD_RES_ACTION,
	CMD_END
};

//	BL			[BR]
//			C
//	[FR]		FL
enum ACTOR_STATES
{
	// for directions, use DIRECTION_ATTRIBUTES in TileMap.h
	AS_STAND	= 0x0100,
	AS_MORPH	= 0x0200,
	AS_DOZE		= 0x0400,
	AS_MASK		= 0x0F00	// States Mask
};

enum DIRECTION_ATTRIBUTES
{
	DA_FR		= 0x0001,	// Forward Right
	DA_FL		= 0x0002,
	DA_BR		= 0x0004,	// Backward
	DA_BL		= 0x0008,
	DA_OPEN		= 0x000F,	// open tile
	DA_CLOSED	= 0x0000,	// closed tile (can't go any direction)
	DA_MASK		= 0x00FF,
	DA_FORWARD	= DA_FR | DA_FL,
	DA_RIGHT	= DA_FR | DA_BR
};

const char UC2_SIGN_CHAR = 'Y';		// 'X' for UniChat 1.1
const char UC2TOKEN	= '`';	// token for parsing

// 2.00 Beta2, 2.03 Beta3, 2.1l (Aug 1, 1998)...
#ifdef _MALL
const int CLIENT_VERSION = 220;
#else
const int CLIENT_VERSION = 221;	// 211 was the last version for UNITEL
#endif

const int MAX_MEMBERS_IN_CHANNEL = 15;

#define UC2PASSWORD		_T("soomin")
#define UC2MUD_TOPIC	_T("UniChat MUD");

#endif	// __UC2MESSAGES_H

///////////////////////////////////////////////////////////////////////////////
// On ADDCHANNEL
//	- Broadcast (HrSendData) CMD_MEMBER_INFO in the channel
//
//	or
//
// On ADDMEMBER
//	if (me)
//		HrSendData (CMD_MEMBER_INFO) to this channel
//	else
//		HrSendPrivMsg (CMD_MEMBER_INFO) to the member
//
