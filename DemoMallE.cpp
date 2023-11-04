//#define	_SKIP_SCENE_1
//#define	_SKIP_SCENE_2
//#define	_SKIP_SCENE_3
//#define	_SKIP_SCENE_L
//#define	_SKIP_SCENE_4
//#define	_SKIP_SCENE_5
//#define	_SKIP_SCENE_6
//#define	_SKIP_SCENE_7
//#define	_SKIP_SCENE_8
//#define	_SKIP_SCENE_9

/*
0010mall;
0020mall;
0030mall;
0010lqad;
0030mall;
0040mall;
0010smin;
0020smin;
0030smin;
0040smin;
*/
//#include "DlgPDA.h"
//#include "DlgAni.h"

#define	WAITFOR(n)		Wait(dwDU*n);		if (!IsDemo())	break;

#define CREATE_THIS_ACTOR(nID)	\
		m_pStage->CreateActor(nID, CPoint(0,0), TRUE, AS_STAND | DA_FL, TRUE);	\
		pActor[0] = m_pStage->GetThisActor();	\
		ASSERT(pActor[0]);	\
		pActor[0]->m_mi.SetBubbleKind(2);	\
		WAITFOR(1);

#define CREATE_ACTOR(n, nID, x, y, direction)	\
		pActor[n] = m_pStage->CreateActor(nID, CPoint(x, y), FALSE,	\
							 AS_STAND | direction);	\
		Wait(dwDU/2);		if (!IsDemo())	break;	\

#define CHANGE_DIRECTION(n, dir)	\
		pActor[n]->SetState(AS_STAND | dir);	\
		WAITFOR(1);
		
#define	MOVEF(n)	\
	{	\
		for (int i = 0; i < n; i++)	\
		{	\
			SendMoveCommand(CMD_MOVEF);	\
			Wait(dwDU/2);		if (!IsDemo())	break;	\
		}	\
	}

#define	MOVEF_ACTOR(id, n)	\
	{	\
		for (int i = 0; i < n; i++)	\
		{	\
			m_pStage->ActorMove(pActor[id], TRUE);	\
			Wait(dwDU/2);		if (!IsDemo())	break;	\
		}	\
	}

#define	SAY(who, text, sound, delay)	\
		strText = text;	\
		pActor[who]->Chat(strText);	\
		PlayWaveFile(sound);	\
		DisplayText(strText);	\
		WAITFOR(delay);

#define	SAYNS(who, text, delay)	\
		strText = text;	\
		pActor[who]->Chat(strText);	\
		DisplayText(strText);	\
		WAITFOR(delay);

////////////////////////////////////////////////////////////////////
	DWORD dwDU = 1300;
//	CUC2View* pView = GetUC2View();
	CString strText;
	CActor* pActor[10];

#ifndef	_SKIP_SCENE_1
/////// Scene 1
	LoadStage("0010mall");
	WAITFOR(1);
	CREATE_THIS_ACTOR(20);

	pActor[0]->Act(CMD_HELLO);
	WAITFOR(1);

	SAY(0, "Guide: Welcome to quarterview's  next generation Internet online chat and commerce demonstration.",
		"01guid01.wav", 5);
	MOVEF(1);

	SAY(0, "Guide: We call our chat and commerce community, quarterview's world of wonder or WOW!",
		"01guid02.wav", 4);
	MOVEF(1);

	SAY(0, "Guide: WOW includes 3D animation and graphics, so it is exciting and easy to use.",
		"01guid03.wav", 4);
	MOVEF(1);

	SAY(0, "Guide: Wow allows users to chat with one another and to conduct other online activities "
			"such as shopping, banking, looking for a job, or whatever the need.",
		"01guid04.wav", 7);

	SAY(0, "Guide: Users navigate our virtual world using avatars, "
			"the graphical characters you see here, they can select from a number of characters "
			"and personalize by selecting their own colors.",
		"01guid05.wav", 8);
	MOVEF(1);

	CREATE_ACTOR(1, 0, 92, 262, DA_FL);
	CREATE_ACTOR(2, 5, 456, 291, DA_FL);
	CREATE_ACTOR(3, 7, 557, 245, DA_FR);

	SAY(0, "Guide: The avatars also carry personal profile information easily accessible by others.",
		"01guid06.wav", 5);

	{
		CDlgAni	ani("profile.bmp", NULL);
		ani.SetAutoDestroy(TRUE);
		ani.SetTimeAttr(1000, 4000);
		ani.SetRelPosition(557, 245);
		ani.DoModal();
	}

	CHANGE_DIRECTION(0, DA_BR);

	SAY(0, "Guide: Users will also be able to build their own homepages also linked to their characters.",
		"01guid07.wav", 4);
#endif

#ifndef	_SKIP_SCENE_2
/////// Scene 2
	LoadStage("0020mall");
	WAITFOR(1);
	CREATE_THIS_ACTOR(20);
	CHANGE_DIRECTION(0, DA_BR);

	CREATE_ACTOR(1, 0, 448, 273, DA_FL);
	CREATE_ACTOR(2, 5, 490, 321, DA_FL);
	CREATE_ACTOR(3, 7, 569, 284, DA_FR);

	SAY(0, "Guide: Third parties can easily create online stores in our environment and be linked "
			"to our world through storefronts or additional geography.",
		"02guid01.wav", 6);
	MOVEF_ACTOR(2, 1);

	SAY(0, "Guide: They can also advertise their products through banner ads on our billboards.",
		"02guid02.wav", 4);

	SAY(0, "Guide: Also, when you click the billboard ad, the web site is automatically launched "
			"on your web browser.",
		"02guid03.wav", 5);

	CMainFrame* pMF = (CMainFrame*)AfxGetMainWnd();
	CString strPath(*gResMan.GetResPath());
	CString strFile(strPath + "lasite.htm");
	pMF->ShellBrowseURL(strFile);	//"http://www.samsung.co.kr/");
	WAITFOR(7);
	pMF->SetActiveWindow();
#endif

#ifndef	_SKIP_SCENE_3
/////// Scene 3
	LoadStage("0030mall");
	WAITFOR(1);
	CREATE_THIS_ACTOR(20);

	CHANGE_DIRECTION(0, DA_FR);

	SAY(0, "Guide: Using our WoW MapEditor third parties can create their own storefronts.",
		"03guid01.wav", 4);

	SAY(0, "Guide: The liquid audio store you see is an example "
			"of one of our online quarterview enhanced stores.",
		"03guid02.wav", 4);
#endif

#ifndef	_SKIP_SCENE_L
/////// Liquid Audio store
// (store showing different types of music, a liquid audio pda is launched and scrolled through.
//	A song is selected and a player shows up. A song is briefly played.)
	LoadStage("0010lqad");
	WAITFOR(1);
	CREATE_THIS_ACTOR(20);
	CHANGE_DIRECTION(0, DA_FR);

	MOVEF(1);

	SAY(0, "Guide: In this liquid audio store a user can browse music "
		"and can purchase the music through our enhanced storefront.",
		"0Lguid01.wav", 5);

	CREATE_ACTOR(1, 0, 267, 263, DA_BR);
	CREATE_ACTOR(2, 5, 359, 215, DA_FR);
	CREATE_ACTOR(3, 7, 206, 163, DA_BL);

	SAY(0, "Guide: Welcome to the liquid audio store. You can browse music "
		"and purchase music you like here.",
		"0Lguid02.wav", 4);

	if (m_pStage)
		m_pStage->StopBGM();
	SAY(1, "Ed: Hey Bill, have you seen the latest top 10 music list?",
		"0Lusr101.wav", 3);
	SAY(2, "Bill: No not yet. Can you pull it up?",
		"0Lusr201.wav", 2);
	SAY(1, "Ed: Sure!",
		"0Lusr102.wav", 1);

	{
		CDlgPDA pda("MPAniUM.bmp", "MPAniLM.bmp", 4);
		pda.SetMode(TRUE, TRUE);
		pda.SetDuration(1500, 1500*4);
		pda.DoModal();
	}

	SAY(2, "Bill: Check out #3 Celine Dion. I've heard that's good. Let's listen...",
		"0Lusr202.wav", 5);
	ShowTitanicDemo();
	WAITFOR(2);
#endif

#ifndef	_SKIP_SCENE_4
/////// Scene 4
	LoadStage("0030mall");
	WAITFOR(1);
	CREATE_THIS_ACTOR(20);
	CHANGE_DIRECTION(0, DA_FR);
	MOVEF(1);

	SAY(0, "Guide: In fact, quarterview enhanced storefronts can enable users to talk "
			"with other users as they do their online shopping and exchange information.",
		"04guid01.wav", 7);

	SAY(0, "Guide: Also, users will be able to directly speak "
			"with customer service representatives from those stores.",
		"04guid02.wav", 6);

	CREATE_ACTOR(1, 0, 276, 177, DA_FL);
	CREATE_ACTOR(2, 5, 406, 155, DA_FR);
	CREATE_ACTOR(3, 7, 459, 293, DA_BL);

	SAY(1, "User 1: Where can I buy a good modem at a reasonable price?",
		"04usr101.wav", 3);
	SAY(2, "User 2: Go to Computer World on the 4th floor in this building.",
		"04usr201.wav", 3);
	SAY(1, "User 1: Thanks",
		"04usr102.wav", 3);
#endif

#ifndef	_SKIP_SCENE_5
/////// Scene 5
	LoadStage("0040mall");
	WAITFOR(1);
	CREATE_THIS_ACTOR(20);
	CHANGE_DIRECTION(0, DA_BR);

	CREATE_ACTOR(1, 0, 365, 289, DA_FL);
	CREATE_ACTOR(2, 5, 74, 325, DA_FL);
	CREATE_ACTOR(3, 7, 580, 230, DA_BL);

	CHANGE_DIRECTION(1, DA_BL);

	SAY(1, "User 3: Is that a Nissan online dealer?",
		"05usr301.wav", 3);

	CHANGE_DIRECTION(0, DA_BL);

	SAY(0, "Guide: Yes, it is.",
		"05guid01.wav", 2);

	SAY(0, "Guide: Would you like to visit Nissan Auto Station?",
		"05guid02.wav", 3);

	strText = "Users: Sure!";
	pActor[1]->Chat(strText);
	pActor[2]->Chat(strText);
	pActor[3]->Chat(strText);
	PlayWaveFile("05usr101.wav");
	WAITFOR(2);

	SAY(0, "Guide: Please, follow me.",
		"05guid03.wav", 3);

	MOVEF(7);
#endif

#ifndef	_SKIP_SCENE_6
/////// Scene 6
	LoadStage("0010smin");
	WAITFOR(1);
	CREATE_THIS_ACTOR(18);
	CHANGE_DIRECTION(0, DA_BR);

	CREATE_ACTOR(1, 0, 115, 188, DA_FL);
	CREATE_ACTOR(2, 5, 73, 251, DA_FL);
	CREATE_ACTOR(3, 7, 299, 289, DA_BL);
	CREATE_ACTOR(4, 2, 78, 319, DA_BL);

	MOVEF(2);

	CHANGE_DIRECTION(0, DA_FR);

	SAY(0, "Sales Guide: Welcome to the Nissan Auto Station.",
		"06sgud01.wav", 3);

	SAY(0, "Sales Guide: The Nissan Auto Station provides the total services "
			"from purchasing the product to all the A/S services through Internet "
			"for 365 days, 24 hours a day.",
		"06sgud02.wav", 8);

	SAY(3, "User3: Can I purchase this model here?",
		"06usr301.wav", 2);

	SAY(0, "Sales Guide: Yes, I'd like to introduce Mr. Kim.",
		"06sgud03.wav", 3);

	CREATE_ACTOR(5, 19, 235, 190, DA_FR);
	CHANGE_DIRECTION(0, DA_BR);

	SAY(5, "Mr. Kim: Hi, how can I help you?",
		"06kim_01.wav", 2);

	SAY(3, "User3: I want to know the price and major features for the Nissan Maxima.",
		"06usr302.wav", 4);

	SAY(5, "Mr. Kim: Please, click the Nissan Maxima icon.",
		"06kim_02.wav", 3);

	{
		CDlgPDA pda("MPAniU.bmp", "MPAniL.bmp", 6);
		pda.SetMode(TRUE, TRUE);
		pda.SetDuration(1500, 1500*5);
		pda.DoModal();
	}

	SAY(5, "Mr. Kim: Now, I would like to tell you about optional pricing "
			"and monthly payment options.",
		"06kim_03.wav", 5);

	SAY(5, "Mr. Kim: Please, follow me.",
		"06kim_04.wav", 3);

	CHANGE_DIRECTION(5, DA_BR);
	MOVEF_ACTOR(5, 3);
#endif

#ifndef	_SKIP_SCENE_7
/////// Scene 7
	LoadStage("0020smin");
	WAITFOR(1);
	CREATE_THIS_ACTOR(18);
	CHANGE_DIRECTION(0, DA_BR);

	CREATE_ACTOR(5, 19, 290, 170, DA_FL);
	CREATE_ACTOR(1, 0, 300, 305, DA_BL);
	CREATE_ACTOR(2, 5, 124, 218, DA_FL);
	CREATE_ACTOR(3, 7, 67, 270, DA_BL);
	CREATE_ACTOR(4, 2, 95, 170, DA_FL);

	SAY(5, "Mr. Kim: This is our manager, Mr. Lee in finance department.",
		"07kim_01.wav", 3);

	CREATE_ACTOR(6, 19, 315, 197, DA_FL);
	CHANGE_DIRECTION(6, DA_FR);
	MOVEF_ACTOR(6, 1);

	SAY(6, "Mr. Lee: Hi, how can I help you?",
		"07Lee_01.wav", 2);

	SAY(2, "User3: Can I get the price and monthly payment options for the Nissan Maxima?",
		"07usr301.wav", 4);

	SAY(6, "Mr. Lee: I will send you an email with the documents that you requested.",
		"07Lee_02.wav", 3);

	{
		CDlgPDA pda("MPAniU.bmp", "MPAniL.bmp", 6);
		pda.SetMode(TRUE, FALSE);
		pda.SetPage(5);
		pda.SetDuration(1500, 1500*5);
		pda.DoModal();
	}

	SAY(6, "Mr. Lee: Do you have any other questions?",
		"07Lee_03.wav", 2);
	
	SAY(4, "User4: Oh, yes I do. I have a Nissan Maxima SE. What kind of "
			"after sale service support can I get and how long can I get those services?",
		"07usr401.wav", 7);

	SAY(5, "Mr. Kim: A customer service agent in our online service center can explain.",
		"07kim_02.wav", 4);

	SAY(5, "Mr. Kim: Please, follow me.",
		"07kim_03.wav", 3);

	CHANGE_DIRECTION(5, DA_BR);
	MOVEF_ACTOR(5, 3);
#endif

#ifndef	_SKIP_SCENE_8
/////// Scene 8
	LoadStage("0040smin");
	WAITFOR(1);
	CREATE_THIS_ACTOR(18);
	CHANGE_DIRECTION(0, DA_BR);

	CREATE_ACTOR(5, 19, 255, 172, DA_FL);
	CREATE_ACTOR(1, 0, 371, 259, DA_BL);
	CREATE_ACTOR(2, 5, 210, 245, DA_BR);
	CREATE_ACTOR(3, 7, 255, 270, DA_BR);
	CREATE_ACTOR(4, 2, 170, 223, DA_FL);

	SAY(5, "Mr. Kim: This is Mr. Johnson our online service center manager.",
		"08kim_01.wav", 3);

	CREATE_ACTOR(6, 21, 326, 220, DA_FL);

	SAY(6, "Mr. Johnson: Hi, How can I help you?",
		"08Choi01.wav", 2);

	SAY(4, "User2: I want to know about your after sale services and the period "
			"that I can get those services.",
		"08usr201.wav", 4);

	SAY(6, "Mr. Johnson: General parts will be covered up to 3 years and 60000km "
			"and transmission will be covered up to 5 years.",
		"08Choi02.wav", 5);

	SAY(3, "User 2: Oh, I see.",
		"08usr202.wav", 2);

//	SAY(1, "User1: Can I get something to drink?",
//		"08usr101.wav", 3);
//	SAY(5, "Mr. Kim: There is a cyber café. Please, follow me.",
//		"08kim_02.wav", 3);

//	CHANGE_DIRECTION(5, DA_BL);

//	m_pStage->ActorMove(pActor[5], FALSE);	// Backward
//	WAITFOR(1);
//	m_pStage->ActorMove(pActor[5], FALSE);	// Backward
//	WAITFOR(1);
#endif

#ifndef	_SKIP_SCENE_9
/////// Scene 9

	LoadStage("0030smin");
	WAITFOR(1);
	CREATE_THIS_ACTOR(18);
/*
	CHANGE_DIRECTION(DA_FL);
	CREATE_ACTOR(5, 19, 243, 145, DA_FL);
	CREATE_ACTOR(1, 0, 309, 267, DA_FL);
	CREATE_ACTOR(2, 5, 107, 307, DA_FL);
	CREATE_ACTOR(3, 7, 36, 141, DA_BL);
	CREATE_ACTOR(4, 2, 528, 312, DA_BL);

//	SAY(5, "Mr. Kim: These people are all our customers.",
//		"09kim_01.wav", 5);
//	SAY(1, "User 1: Then we can get more information from them.",
//		"09usr101.wav", 5);
//	SAY(5, "Mr. Kim: Yes",
//		"09kim_02.wav", 3);

	strText = "~~) @@ ^^;";
	pActor[1]->Chat(strText);
	pActor[2]->Chat(strText);
	pActor[3]->Chat(strText);
	pActor[4]->Chat(strText);
	DisplayText(strText);
	WAITFOR(1);
*/
	SAY(0, "Guide: The final feature we would like to show is our integration "
			"with instant messaging.",
		"08guid01.wav", 5);
	MOVEF(1);

	SAY(0, "Guide: Users will be able to use our instant messaging system "
			"to keep track of their friends or other associates.",
		"08guid02.wav", 1);
	ShowIMDemo();
	MOVEF(1);

	SAY(0, "Guide: The instant messaging system is integrated into our chat system "
			"so that users within the same chat room will have their names highlighted "
			"and users on the IM list can be invited into the same room.",
		"08guid03.wav", 1);
	ShowMapDemo();

	SAY(0, "Guide: Also, we will fully support Microsoft Presence Information Protocol "
			"so that our users will be able to message and interact with users "
			"of other Instant Messaging  systems.",
		"08guid04.wav", 9);
	CHANGE_DIRECTION(0, DA_FR);

	SAY(0, "Guide: As you have seen so far Quarterview WOW provides an exciting "
			"and easy interactive online chat and commerce services for all kinds of users.",
		"08guid05.wav", 8);
#endif
	ClearHistory();
	
	OnBtnQuit();
/*
#undef	_SKIP_SCENE_1
#undef	_SKIP_SCENE_2
#undef	_SKIP_SCENE_3
#undef	_SKIP_SCENE_L
#undef	_SKIP_SCENE_4
#undef	_SKIP_SCENE_5
#undef	_SKIP_SCENE_6
#undef	_SKIP_SCENE_7
#undef	_SKIP_SCENE_8
*/