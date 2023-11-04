		DWORD dwDU = 1500;
//		CUC2View* pView = GetUC2View();
		CString strText;

		LoadStage("0001demo");
		m_pStage->CreateActor(0, CPoint(5,11), TRUE, AS_STAND | DA_FR, TRUE);
		CActor* pActor[10];
		pActor[0] = m_pStage->GetThisActor();
		ASSERT(pActor[0]);

		pActor[1] = m_pStage->CreateActor(10, CPoint(318,254), FALSE, AS_STAND | DA_FR);
		Wait(dwDU);		if (!IsDemo())	break;
	//	pActor->Act(CMD_HELLO);
		strText.LoadString(IDS_DEMO_1);
		pActor[1]->Chat(strText);
		DisplayText(strText);
		Wait(dwDU*2);		if (!IsDemo())	break;

		pActor[0]->SetState(AS_STAND | DA_BR);
		SendMoveCommand(CMD_MOVEF);
		Wait(dwDU*2);		if (!IsDemo())	break;
		strText.LoadString(IDS_DEMO_2); 
		SendText(strText);
		Wait(dwDU*4);		if (!IsDemo())	break;

		pActor[2] = m_pStage->CreateActor(15, CPoint(195,127), FALSE, AS_STAND | DA_FL);
		Wait(dwDU);		if (!IsDemo())	break;
		strText.LoadString(IDS_DEMO_3);
		pActor[2]->Chat(strText);
		DisplayText(strText);
		Wait(dwDU*3);		if (!IsDemo())	break;
		pActor[2]->Act(CMD_SMILE);

		SendMoveCommand(CMD_MOVEF);

		pActor[3] = m_pStage->CreateActor(7, CPoint(411,109), FALSE, AS_STAND | DA_FR);
		Wait(dwDU);		if (!IsDemo())	break;
		strText = "Hi, Everybody! This is cool!";
		pActor[3]->Chat(strText);
		DisplayText(strText);
		Wait(dwDU*2);		if (!IsDemo())	break;

		SendMoveCommand(CMD_MOVEF);
		Wait(dwDU);		if (!IsDemo())	break;

		pActor[0]->SetDA(DA_FL, FALSE);
		strText.LoadString(IDS_DEMO_4);
		SendText(strText);
		Wait(dwDU*2);		if (!IsDemo())	break;
		SendCommand(CMD_MORPH);
		Wait(dwDU);		if (!IsDemo())	break;
		pActor[0]->SetDA(DA_FR, FALSE);
		Wait(dwDU);		if (!IsDemo())	break;
		SendMoveCommand(CMD_MOVEF);

		strText.LoadString(IDS_DEMO_5);
		SendText(strText);
		SendMoveCommand(CMD_MOVEF);

		strText.LoadString(IDS_DEMO_6);
		pActor[1]->Chat(strText);
		DisplayText(strText);

		OnBtnHistory();
		Wait(dwDU*5);		if (!IsDemo())	break;
//		pView->ScrollToPosition(CPoint(80, 0));
		Wait(dwDU*2);		if (!IsDemo())	break;
		OnBtnHistory();
		Wait(dwDU);		if (!IsDemo())	break;

		SendMoveCommand(CMD_MOVEF);
		Wait(dwDU);		if (!IsDemo())	break;

		////////////////////////////////////////////////////
		LoadStage("0002demo");
		m_pStage->CreateActor(0, CPoint(5,11), TRUE, m_wSavedState, TRUE);
		pActor[0] = m_pStage->GetThisActor();
		Wait(dwDU*4);		if (!IsDemo())	break;

		SendCommand(CMD_STAND);
		strText.LoadString(IDS_DEMO_7);
		SendText(strText);
		SendMoveCommand(CMD_MOVEF);
		Wait(dwDU);		if (!IsDemo())	break;

		pActor[1] = m_pStage->CreateActor(17, CPoint(225,113), FALSE, AS_STAND | DA_FL);
		Wait(dwDU);		if (!IsDemo())	break;

		SendMoveCommand(CMD_MOVEF);

		strText.LoadString(IDS_DEMO_8);
		pActor[1]->Chat(strText);
		DisplayText(strText);
		Wait(dwDU*4);		if (!IsDemo())	break;

		pActor[0]->SetState(AS_STAND | DA_FL);
		SendMoveCommand(CMD_MOVEF);

		pActor[1]->Act(CMD_MORPH);
		Wait(dwDU*3);		if (!IsDemo())	break;
		SendMoveCommand(CMD_MOVEF);
		pActor[1]->Act(CMD_STAND);

		pActor[2] = m_pStage->CreateActor(9, CPoint(355,334), FALSE);
		strText.LoadString(IDS_DEMO_9);
		pActor[2]->Chat(strText);
		DisplayText(strText);
		SendMoveCommand(CMD_MOVEF);
		Wait(dwDU*3);		if (!IsDemo())	break;

		pActor[0]->SetState(AS_STAND | DA_FR);
		SendMoveCommand(CMD_MOVEF);
		Wait(dwDU);		if (!IsDemo())	break;

		pActor[3] = m_pStage->CreateActor(11, CPoint(128,254), FALSE, AS_STAND | DA_FL);
		Wait(dwDU);		if (!IsDemo())	break;
		strText.LoadString(IDS_DEMO_10);
		pActor[3]->Chat(strText);
		DisplayText(strText);
		SendMoveCommand(CMD_MOVEF);
		Wait(dwDU*3);		if (!IsDemo())	break;

		SendMoveCommand(CMD_MOVEF);
		pActor[3]->Act(CMD_CRY);
		Wait(dwDU);		if (!IsDemo())	break;
		SendMoveCommand(CMD_MOVEF);
		Wait(dwDU);		if (!IsDemo())	break;
		pActor[3]->Act(CMD_MORPH);
		SendMoveCommand(CMD_MOVEF);
		Wait(dwDU);		if (!IsDemo())	break;
		strText.LoadString(IDS_DEMO_11);
		pActor[3]->Chat(strText);
		Wait(dwDU);		if (!IsDemo())	break;
		SendMoveCommand(CMD_MOVEF);
		Wait(dwDU);		if (!IsDemo())	break;
		SendMoveCommand(CMD_MOVEF);
		Wait(dwDU);		if (!IsDemo())	break;
		SendMoveCommand(CMD_MOVEF);
		Wait(dwDU);		if (!IsDemo())	break;

		////////////////////////////////////////////////////
		LoadStage("0003demo");
		m_pStage->CreateActor(0, CPoint(5,11), TRUE, m_wSavedState, TRUE);
		pActor[0] = m_pStage->GetThisActor();
		Wait(dwDU*4);		if (!IsDemo())	break;

		SendMoveCommand(CMD_MOVEF);
		Wait(dwDU);		if (!IsDemo())	break;

		pActor[1] = m_pStage->CreateActor(12, CPoint(253,289), FALSE);
		Wait(dwDU);		if (!IsDemo())	break;
		strText.LoadString(IDS_DEMO_12);
		pActor[1]->Chat(strText);
		DisplayText(strText);
		SendMoveCommand(CMD_MOVEF);
		Wait(dwDU*8);		if (!IsDemo())	break;

		strText.LoadString(IDS_DEMO_13);
		SendText(strText);
		SendMoveCommand(CMD_MOVEF);
		Wait(dwDU);		if (!IsDemo())	break;

		CMainFrame* pMF = (CMainFrame*)AfxGetMainWnd();
		CString strURL;
		strURL.LoadString(IDS_UNICHAT_HOMEURL);
		pMF->ShellBrowseURL(strURL);
		Wait(dwDU*8);		if (!IsDemo())	break;
		pMF->SetActiveWindow();

		SendMoveCommand(CMD_MOVEF);
		Wait(dwDU);		if (!IsDemo())	break;

		SendMoveCommand(CMD_MOVEF);
		Wait(dwDU);		if (!IsDemo())	break;

		////////////////////////////////////////////////////
		LoadStage("0001ctrm");
		m_pStage->CreateActor(0, CPoint(5,11), TRUE, m_wSavedState, TRUE);
		pActor[0] = m_pStage->GetThisActor();
		Wait(dwDU*4);		if (!IsDemo())	break;

		pActor[0]->SetState(AS_STAND | DA_BR);
		SendMoveCommand(CMD_MOVEF);
		Wait(dwDU);		if (!IsDemo())	break;
		SendMoveCommand(CMD_MOVEF);
		Wait(dwDU);		if (!IsDemo())	break;
		SendMoveCommand(CMD_MOVEF);
		Wait(dwDU);		if (!IsDemo())	break;
		SendMoveCommand(CMD_MOVEF);
		Wait(dwDU);		if (!IsDemo())	break;

		strText.LoadString(IDS_DEMO_14);
		SendText(strText);
		SendMoveCommand(CMD_MOVEF);
		Wait(dwDU);		if (!IsDemo())	break;

		ClearHistory();
