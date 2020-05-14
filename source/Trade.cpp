#include "stdafx.h"
#include "Trade.h"

//int _orderRef = 0;

bool CMyTradeSpi::IsErrorRspInfo(CHSRspInfoField *pRspInfo)
{
	bool ret = ((pRspInfo) && (pRspInfo->ErrorID != 0));
	if (ret)
	{
		CString str;
		str.Format("����ʧ�ܣ�error_no=[%d] error_info=[%s]", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
	}
	return ret;
}

void  CMyTradeSpi::OnFrontConnected()
{
	/* �����ӽ����ɹ����������������߳� */
	addInfo("�������ӳɹ�\r\n");
	if (false == DealBusinessTrd.IsRunning())
	{		
		DealBusinessTrd.Start(DealBusiness, 0, this);
	}
	login();	
	return;
}

void  CMyTradeSpi::OnFrontDisconnected(int nReason)
{
	addInfo(lpUserApi->GetApiErrorMsg(nReason));
	printf("\r\n");
	return;
}



void  CMyTradeSpi:: DealBusiness(void* lpvoid)
{
	CMyTradeSpi *lpTradeSpi = (CMyTradeSpi*)lpvoid;

	while(false == lpTradeSpi->bStopDealBusiness)
	{
		cerr<<"[1]�ͻ���¼                                  "<<endl;
		cerr<<"[2]�������                                  "<<endl;
		cerr<<"[3]����¼��                                  "<<endl;
		cerr<<"[4]����                                      "<<endl;
		cerr<<"[5]��Ȩ¼��                                  "<<endl;
		cerr<<"[6]��Ȩ����                                  "<<endl;
		cerr<<"[7]����¼��                                  "<<endl;
		cerr<<"[8]ѯ��¼��                                  "<<endl;
		cerr<<"[9]�������¼��                              "<<endl;
		cerr<<"[10]��󱨵�������ȡ                         "<<endl;
		cerr<<"[11]������������ȡ                           "<<endl;
		cerr<<"[12]����Ȩ������ȡ                           "<<endl;
		cerr<<"[13]�ֲֻ��ܲ�ѯ                             "<<endl;
		cerr<<"[14]�ʽ��˻���ѯ                             "<<endl;
		cerr<<"[15]������ѯ                                 "<<endl;
		cerr<<"[16]�ɽ���ѯ                                 "<<endl;
		cerr<<"[17]��Ȩ��ѯ                                 "<<endl;
		cerr<<"[18]������ѯ                                 "<<endl;
		cerr<<"[19]������ϲ�ѯ                             "<<endl;
		cerr<<"[20]��ϳֲ���ϸ��ѯ                         "<<endl;
		cerr<<"[21]��Լ��Ϣ��ѯ                             "<<endl;
		cerr<<"[22]����ȱ�ڲ�ѯ                             "<<endl;
		cerr<<"[23]��Ȩָ�ɲ�ѯ                             "<<endl;
		cerr<<"[24]����ת��                                 "<<endl;
		cerr<<"[25]����ת�˲�ѯ                             "<<endl;
		cerr<<"[26]��������ѯ                             "<<endl;
		cerr<<"[27]�����˻���ѯ                             "<<endl;
		cerr<<"[28]�ͻ��˵���ѯ                             "<<endl;
		cerr<<"[29]�ͻ��˵�ȷ��                             "<<endl;
		cerr<<"[30]��֤���ѯ                               "<<endl;
		cerr<<"[31]�����Ѳ�ѯ                               "<<endl;
		cerr<<"[32]�ֲ���ϸ��ѯ                             "<<endl;
		cerr<<"[33]���͹�˾���ò�����ѯ                     "<<endl;
		cerr<<"[34]�����ѯ                                 "<<endl;
		cerr<<"[35]���ʲ�ѯ                                 "<<endl;
		while(1)
		{
			int cmd;
			cin.clear();
			cin.sync();
			cin>>cmd;
			switch(cmd)
			{
			case 1:
				{

					CHSReqUserLoginField stHSReqUserLogin;
					memset(&stHSReqUserLogin,0,sizeof(CHSReqUserLoginField));
					char szTemp[260];
					printf("Please input AccountID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqUserLogin.AccountID,"" );
					else
						hs_strncpy(stHSReqUserLogin.AccountID,szTemp,sizeof(stHSReqUserLogin.AccountID));
					printf("Please input Password �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqUserLogin.Password,"" );
					else
						hs_strncpy(stHSReqUserLogin.Password,szTemp,sizeof(stHSReqUserLogin.Password));
					printf("Please input UserApplicationType�����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						stHSReqUserLogin.UserApplicationType = '\0';
					else
						stHSReqUserLogin.UserApplicationType = szTemp[0];
					printf("Please input UserApplicationInfo �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqUserLogin.UserApplicationInfo,"" );
					else
						hs_strncpy(stHSReqUserLogin.UserApplicationInfo,szTemp,sizeof(stHSReqUserLogin.UserApplicationInfo));
					printf("Please input MacAddress �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqUserLogin.MacAddress,"" );
					else
						hs_strncpy(stHSReqUserLogin.MacAddress,szTemp,sizeof(stHSReqUserLogin.MacAddress));
					printf("Please input IPAddress �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqUserLogin.IPAddress,"" );
					else
						hs_strncpy(stHSReqUserLogin.IPAddress,szTemp,sizeof(stHSReqUserLogin.IPAddress));
					int iRet = lpTradeSpi->lpUserApi->ReqUserLogin(&stHSReqUserLogin,lpTradeSpi->iRequestId++);
					if (iRet != SDK_OK)
					{
						printf("%s\r\n",lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));

					}
					break;
				}
			case 2:
				{
					
					CHSReqUserPasswordUpdateField stHSReqUserPasswordUpdate;
					memset(&stHSReqUserPasswordUpdate,0,sizeof(CHSReqUserPasswordUpdateField));
					char szTemp[260],pswd[18],newpswd[18];
					printf("Please input PasswordType�����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						stHSReqUserPasswordUpdate.PasswordType = '\0';
					else
						stHSReqUserPasswordUpdate.PasswordType = szTemp[0];
					printf("Please input Password �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqUserPasswordUpdate.Password,"" );
					else
						hs_strncpy(stHSReqUserPasswordUpdate.Password,szTemp,sizeof(stHSReqUserPasswordUpdate.Password));
					hs_strncpy(pswd,stHSReqUserPasswordUpdate.Password,sizeof(pswd));
					printf("Please input NewPassword �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqUserPasswordUpdate.NewPassword,"" );
					else
						hs_strncpy(stHSReqUserPasswordUpdate.NewPassword,szTemp,sizeof(stHSReqUserPasswordUpdate.NewPassword));
					hs_strncpy(newpswd,stHSReqUserPasswordUpdate.NewPassword,sizeof(newpswd));
					int iRet = lpTradeSpi->lpUserApi->ReqUserPasswordUpdate(&stHSReqUserPasswordUpdate,lpTradeSpi->iRequestId++);
					if (iRet != SDK_OK)
					{
						printf(lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
					}
					break;
				}
			case 3:
				{
					CHSReqOrderInsertField stHSReqOrderInsert;
					memset(&stHSReqOrderInsert,0,sizeof(CHSReqOrderInsertField));
					char szTemp[260];
					printf("Please input OrderRef �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqOrderInsert.OrderRef,"" );
					else
						hs_strncpy(stHSReqOrderInsert.OrderRef,szTemp,sizeof(stHSReqOrderInsert.OrderRef));
					printf("Please input ExchangeID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqOrderInsert.ExchangeID,"" );
					else
						hs_strncpy(stHSReqOrderInsert.ExchangeID,szTemp,sizeof(stHSReqOrderInsert.ExchangeID));
					printf("Please input InstrumentID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqOrderInsert.InstrumentID,"" );
					else
						hs_strncpy(stHSReqOrderInsert.InstrumentID,szTemp,sizeof(stHSReqOrderInsert.InstrumentID));
					printf("Please input Direction�����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						stHSReqOrderInsert.Direction = '\0';
					else
						stHSReqOrderInsert.Direction = szTemp[0];
					printf("Please input OffsetFlag�����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						stHSReqOrderInsert.OffsetFlag = '\0';
					else
						stHSReqOrderInsert.OffsetFlag = szTemp[0];
					printf("Please input HedgeType�����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						stHSReqOrderInsert.HedgeType = '\0';
					else
						stHSReqOrderInsert.HedgeType = szTemp[0];
					printf( "Please input OrderPrice:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					stHSReqOrderInsert.OrderPrice = atof(szTemp);
					printf( "Please input OrderVolume:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					stHSReqOrderInsert.OrderVolume = atof(szTemp);
					printf("Please input OrderCommand�����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqOrderInsert.OrderCommand,"" );
					else
						hs_strncpy(stHSReqOrderInsert.OrderCommand,szTemp ,sizeof(stHSReqOrderInsert.OrderCommand));
					printf( "Please input MinVolume:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					stHSReqOrderInsert.MinVolume = atof(szTemp);
					printf( "Please input SpringPrice:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					stHSReqOrderInsert.SpringPrice = atof(szTemp);
					printf("Please input SwapOrderFlag�����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						stHSReqOrderInsert.SwapOrderFlag = '\0';
					else
						stHSReqOrderInsert.SwapOrderFlag = szTemp[0];					
					int iRet = lpTradeSpi->lpUserApi->ReqOrderInsert(&stHSReqOrderInsert,lpTradeSpi->iRequestId++);
					if (iRet != SDK_OK)
					{
						printf(lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
					}
					break;
				}
			case 4:
				{
					CHSReqOrderActionField stHSReqOrderAction;
					memset(&stHSReqOrderAction,0,sizeof(CHSReqOrderActionField));
					char szTemp[260];
					printf("Please input OrderSysID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqOrderAction.OrderSysID,"" );
					else
						hs_strncpy(stHSReqOrderAction.OrderSysID,szTemp,sizeof(stHSReqOrderAction.OrderSysID));
					printf("Please input ExchangeID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqOrderAction.ExchangeID,"" );
					else
						hs_strncpy(stHSReqOrderAction.ExchangeID,szTemp,sizeof(stHSReqOrderAction.ExchangeID));
					printf("Please input SessionID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					stHSReqOrderAction.SessionID = atoi(szTemp);
					printf("Please input OrderRef �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqOrderAction.OrderRef,"" );
					else
						hs_strncpy(stHSReqOrderAction.OrderRef,szTemp,sizeof(stHSReqOrderAction.OrderRef));
					printf("Please input OrderActionRef �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqOrderAction.OrderActionRef,"" );
					else
						hs_strncpy(stHSReqOrderAction.OrderActionRef,szTemp,sizeof(stHSReqOrderAction.OrderActionRef));				
					int iRet = lpTradeSpi->lpUserApi->ReqOrderAction(&stHSReqOrderAction,lpTradeSpi->iRequestId++);
					if (iRet != SDK_OK)
					{
						printf(lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
					}
					break;
				}
			case 5:
				{
					CHSReqExerciseOrderInsertField stHSReqExerciseOrderInsert;
					memset(&stHSReqExerciseOrderInsert,0,sizeof(CHSReqExerciseOrderInsertField));
					char szTemp[260];
					printf("Please input ExerciseRef �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqExerciseOrderInsert.ExerciseRef,"" );
					else
						hs_strncpy(stHSReqExerciseOrderInsert.ExerciseRef,szTemp,sizeof(stHSReqExerciseOrderInsert.ExerciseRef));
					printf("Please input ExchangeID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqExerciseOrderInsert.ExchangeID,"" );
					else
						hs_strncpy(stHSReqExerciseOrderInsert.ExchangeID,szTemp,sizeof(stHSReqExerciseOrderInsert.ExchangeID));
					printf("Please input InstrumentID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqExerciseOrderInsert.InstrumentID,"" );
					else
						hs_strncpy(stHSReqExerciseOrderInsert.InstrumentID,szTemp,sizeof(stHSReqExerciseOrderInsert.InstrumentID));
					printf( "Please input OrderVolume:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					stHSReqExerciseOrderInsert.OrderVolume = atof(szTemp);
					printf("Please input ExerciseType�����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						stHSReqExerciseOrderInsert.ExerciseType = '\0';
					else
						stHSReqExerciseOrderInsert.ExerciseType = szTemp[0];
					printf("Please input HedgeType�����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						stHSReqExerciseOrderInsert.HedgeType = '\0';
					else
						stHSReqExerciseOrderInsert.HedgeType = szTemp[0];					
					int iRet = lpTradeSpi->lpUserApi->ReqExerciseOrderInsert(&stHSReqExerciseOrderInsert,lpTradeSpi->iRequestId++);
					if (iRet != SDK_OK)
					{
						printf(lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
					}
					break;
				}
			case 6:
				{
					CHSReqExerciseOrderActionField stHSReqExerciseOrderAction;
					memset(&stHSReqExerciseOrderAction,0,sizeof(CHSReqExerciseOrderActionField));
					char szTemp[260];
					printf("Please input ExchangeID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqExerciseOrderAction.ExchangeID,"" );
					else
						hs_strncpy(stHSReqExerciseOrderAction.ExchangeID,szTemp,sizeof(stHSReqExerciseOrderAction.ExchangeID));
					printf("Please input ExerciseOrderSysID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqExerciseOrderAction.ExerciseOrderSysID,"" );
					else
						hs_strncpy(stHSReqExerciseOrderAction.ExerciseOrderSysID,szTemp,sizeof(stHSReqExerciseOrderAction.ExerciseOrderSysID));
					printf("Please input ExerciseRef �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqExerciseOrderAction.ExerciseRef,"" );
					else
						hs_strncpy(stHSReqExerciseOrderAction.ExerciseRef,szTemp,sizeof(stHSReqExerciseOrderAction.ExerciseRef));
					printf("Please input SessionID �����봫��ֱ�ӻس���Enter����:");
					cin.ignore();
					cin.get(szTemp,260,'\n');
					stHSReqExerciseOrderAction.SessionID = atoi(szTemp);
					printf("Please input ExecOrderActionRef �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqExerciseOrderAction.ExecOrderActionRef,"" );
					else
						hs_strncpy(stHSReqExerciseOrderAction.ExecOrderActionRef,szTemp,sizeof(stHSReqExerciseOrderAction.ExecOrderActionRef));					
					int iRet = lpTradeSpi->lpUserApi->ReqExerciseOrderAction(&stHSReqExerciseOrderAction,lpTradeSpi->iRequestId++);
					if (iRet != SDK_OK)
					{
						printf(lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
					}
					break;
				}
			case 7:
				{
					CHSReqLockInsertField stHSReqLockInsert;
					memset(&stHSReqLockInsert,0,sizeof(CHSReqLockInsertField));
					char szTemp[260];
					printf("Please input ExchangeID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqLockInsert.ExchangeID,"" );
					else
						hs_strncpy(stHSReqLockInsert.ExchangeID,szTemp,sizeof(stHSReqLockInsert.ExchangeID));
					printf("Please input UnderlyingInstrID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqLockInsert.UnderlyingInstrID,"" );
					else
						hs_strncpy(stHSReqLockInsert.UnderlyingInstrID,szTemp,sizeof(stHSReqLockInsert.UnderlyingInstrID));
					printf("Please input LockType�����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						stHSReqLockInsert.LockType = '\0';
					else
						stHSReqLockInsert.LockType = szTemp[0];
					printf( "Please input LockVolume:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					stHSReqLockInsert.OrderVolume = atof(szTemp);					
					int iRet = lpTradeSpi->lpUserApi->ReqLockInsert(&stHSReqLockInsert,lpTradeSpi->iRequestId++);
					if (iRet != SDK_OK)
					{
						printf(lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
					}
					break;
				}
			case 8:
				{
					CHSReqForQuoteInsertField stHSReqForQuoteInsert;
					memset(&stHSReqForQuoteInsert,0,sizeof(CHSReqForQuoteInsertField));
					char szTemp[260];
					printf("Please input ExchangeID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqForQuoteInsert.ExchangeID,"" );
					else
						hs_strncpy(stHSReqForQuoteInsert.ExchangeID,szTemp,sizeof(stHSReqForQuoteInsert.ExchangeID));
					printf("Please input InstrumentID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqForQuoteInsert.InstrumentID,"" );
					else
						hs_strncpy(stHSReqForQuoteInsert.InstrumentID,szTemp,sizeof(stHSReqForQuoteInsert.InstrumentID));					
					int iRet = lpTradeSpi->lpUserApi->ReqForQuoteInsert(&stHSReqForQuoteInsert,lpTradeSpi->iRequestId++);
					if (iRet != SDK_OK)
					{
						printf(lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
					}
					break;
				}
			case 9:
				{
					CHSReqCombActionInsertField stHSReqCombActionInsert;
					memset(&stHSReqCombActionInsert,0,sizeof(CHSReqCombActionInsertField));
					char szTemp[260];
					printf("Please input ExchangeID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqCombActionInsert.ExchangeID,"" );
					else
						hs_strncpy(stHSReqCombActionInsert.ExchangeID,szTemp,sizeof(stHSReqCombActionInsert.ExchangeID));
					printf("Please input InstrumentID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqCombActionInsert.InstrumentID,"" );
					else
						hs_strncpy(stHSReqCombActionInsert.InstrumentID,szTemp,sizeof(stHSReqCombActionInsert.InstrumentID));
					printf("Please input CombStrategyID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqCombActionInsert.CombStrategyID,"" );
					else
						hs_strncpy(stHSReqCombActionInsert.CombStrategyID,szTemp,sizeof(stHSReqCombActionInsert.CombStrategyID));
					printf("Please input CombPositionID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqCombActionInsert.CombPositionID,"" );
					else
						hs_strncpy(stHSReqCombActionInsert.CombPositionID,szTemp,sizeof(stHSReqCombActionInsert.CombPositionID));
					printf("Please input CombDirection�����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						stHSReqCombActionInsert.CombDirection = '\0';
					else
						stHSReqCombActionInsert.CombDirection = szTemp[0];
					printf( "Please input OrderVolume:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					stHSReqCombActionInsert.OrderVolume = atof(szTemp);
					printf("Please input HedgeType�����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						stHSReqCombActionInsert.HedgeType = '\0';
					else
						stHSReqCombActionInsert.HedgeType = szTemp[0];
					printf("Please input Direction�����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						stHSReqCombActionInsert.Direction = '\0';
					else
						stHSReqCombActionInsert.Direction = szTemp[0];					
					int iRet = lpTradeSpi->lpUserApi->ReqCombActionInsert(&stHSReqCombActionInsert,lpTradeSpi->iRequestId++);
					if (iRet != SDK_OK)
					{
						printf(lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
					}
					break;
				}
			case 10:
				{
					CHSReqQueryMaxOrderVolumeField stHSReqQueryMaxOrderVolume;
					memset(&stHSReqQueryMaxOrderVolume,0,sizeof(CHSReqQueryMaxOrderVolumeField));
					char szTemp[260];
					printf("Please input ExchangeID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQueryMaxOrderVolume.ExchangeID,"" );
					else
						hs_strncpy(stHSReqQueryMaxOrderVolume.ExchangeID,szTemp,sizeof(stHSReqQueryMaxOrderVolume.ExchangeID));
					printf("Please input InstrumentID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQueryMaxOrderVolume.InstrumentID,"" );
					else
						hs_strncpy(stHSReqQueryMaxOrderVolume.InstrumentID,szTemp,sizeof(stHSReqQueryMaxOrderVolume.InstrumentID));
					printf("Please input OrderCommand�����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQueryMaxOrderVolume.OrderCommand,"" );
					else
						hs_strncpy(stHSReqQueryMaxOrderVolume.OrderCommand,szTemp ,sizeof(stHSReqQueryMaxOrderVolume.OrderCommand));
					printf("Please input Direction�����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						stHSReqQueryMaxOrderVolume.Direction = '\0';
					else
						stHSReqQueryMaxOrderVolume.Direction = szTemp[0];
					printf("Please input OffsetFlag�����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						stHSReqQueryMaxOrderVolume.OffsetFlag = '\0';
					else
						stHSReqQueryMaxOrderVolume.OffsetFlag = szTemp[0];
					printf("Please input HedgeType�����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						stHSReqQueryMaxOrderVolume.HedgeType = '\0';
					else
						stHSReqQueryMaxOrderVolume.HedgeType = szTemp[0];
					printf( "Please input OrderPrice:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					stHSReqQueryMaxOrderVolume.OrderPrice = atof(szTemp);					
					int iRet = lpTradeSpi->lpUserApi->ReqQueryMaxOrderVolume(&stHSReqQueryMaxOrderVolume,lpTradeSpi->iRequestId++);
					if (iRet != SDK_OK)
					{
						printf(lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
					}
					break;
				}
			case 11:
				{
					CHSReqQueryLockVolumeField stHSReqQueryLockVolume;
					memset(&stHSReqQueryLockVolume,0,sizeof(CHSReqQueryLockVolumeField));
					char szTemp[260];
					printf("Please input ExchangeID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQueryLockVolume.ExchangeID,"" );
					else
						hs_strncpy(stHSReqQueryLockVolume.ExchangeID,szTemp,sizeof(stHSReqQueryLockVolume.ExchangeID));
					printf("Please input UnderlyingInstrID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQueryLockVolume.UnderlyingInstrID,"" );
					else
						hs_strncpy(stHSReqQueryLockVolume.UnderlyingInstrID,szTemp,sizeof(stHSReqQueryLockVolume.UnderlyingInstrID));
					printf("Please input LockType�����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						stHSReqQueryLockVolume.LockType = '\0';
					else
						stHSReqQueryLockVolume.LockType = szTemp[0];					
					int iRet = lpTradeSpi->lpUserApi->ReqQueryLockVolume(&stHSReqQueryLockVolume,lpTradeSpi->iRequestId++);
					if (iRet != SDK_OK)
					{
						printf(lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
					}
					break;
				}
			case 12:
				{
					CHSReqQueryExerciseVolumeField stHSReqQueryExerciseVolume;
					memset(&stHSReqQueryExerciseVolume,0,sizeof(CHSReqQueryExerciseVolumeField));
					char szTemp[260];
					printf("Please input ExchangeID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQueryExerciseVolume.ExchangeID,"" );
					else
						strcpy(stHSReqQueryExerciseVolume.ExchangeID,szTemp);
					printf("Please input InstrumentID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQueryExerciseVolume.InstrumentID,"" );
					else
						strcpy(stHSReqQueryExerciseVolume.InstrumentID,szTemp);
					
						int iRet = lpTradeSpi->lpUserApi->ReqQueryExerciseVolume(&stHSReqQueryExerciseVolume,lpTradeSpi->iRequestId++);
					if (iRet != SDK_OK)
					{
						printf(lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
					}
					break;
					}
			case 13:
				{
					CHSReqQryPositionField stHSReqQryPosition;
					memset(&stHSReqQryPosition,0,sizeof(CHSReqQryPositionField));
					char szTemp[260];
					printf("Please input ExchangeID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQryPosition.ExchangeID,"" );
					else
						hs_strncpy(stHSReqQryPosition.ExchangeID,szTemp,sizeof(stHSReqQryPosition.ExchangeID));
					printf("Please input InstrumentID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQryPosition.InstrumentID,"" );
					else
						hs_strncpy(stHSReqQryPosition.InstrumentID,szTemp,sizeof(stHSReqQryPosition.InstrumentID));
					
					int iRet = lpTradeSpi->lpUserApi->ReqQryPosition(&stHSReqQryPosition,lpTradeSpi->iRequestId++);
					if (iRet != SDK_OK)
					{
						printf(lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
					}
					break;
				}
			case 14:
				{
					CHSReqQryTradingAccountField stHSReqQryTradingAccount;
					memset(&stHSReqQryTradingAccount,0,sizeof(CHSReqQryTradingAccountField));
					int iRet = lpTradeSpi->lpUserApi->ReqQryTradingAccount(&stHSReqQryTradingAccount,lpTradeSpi->iRequestId++);
					if (iRet != SDK_OK)
					{
						printf(lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
					}
					
					break;
				}
			case 15:
				{
					CHSReqQryOrderField stHSReqQryOrder;
					memset(&stHSReqQryOrder,0,sizeof(CHSReqQryOrderField));
					char szTemp[260];
					printf("Please input ExchangeID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQryOrder.ExchangeID,"" );
					else
						hs_strncpy(stHSReqQryOrder.ExchangeID,szTemp,sizeof(stHSReqQryOrder.ExchangeID));
					printf("Please input InstrumentID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQryOrder.InstrumentID,"" );
					else
						hs_strncpy(stHSReqQryOrder.InstrumentID,szTemp,sizeof(stHSReqQryOrder.InstrumentID));
					printf("Please input OrderSysID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQryOrder.OrderSysID,"" );
					else
						hs_strncpy(stHSReqQryOrder.OrderSysID,szTemp,sizeof(stHSReqQryOrder.OrderSysID));
					
					int iRet = lpTradeSpi->lpUserApi->ReqQryOrder(&stHSReqQryOrder,lpTradeSpi->iRequestId++);
					if (iRet != SDK_OK)
					{
						printf(lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
					}
					break;
				}
			case 16:
				{
					CHSReqQryTradeField stHSReqQryTrade;
					memset(&stHSReqQryTrade,0,sizeof(CHSReqQryTradeField));
					char szTemp[260];
					printf("Please input ExchangeID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQryTrade.ExchangeID,"" );
					else
						hs_strncpy(stHSReqQryTrade.ExchangeID,szTemp,sizeof(stHSReqQryTrade.ExchangeID));
					printf("Please input InstrumentID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQryTrade.InstrumentID,"" );
					else
						hs_strncpy(stHSReqQryTrade.InstrumentID,szTemp,sizeof(stHSReqQryTrade.InstrumentID));
					
					int iRet = lpTradeSpi->lpUserApi->ReqQryTrade(&stHSReqQryTrade,lpTradeSpi->iRequestId++);
					if (iRet != SDK_OK)
					{
						printf(lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
					}
					break;
				}
			case 17:
				{
					CHSReqQryExerciseField stHSReqQryExercise;
					memset(&stHSReqQryExercise,0,sizeof(CHSReqQryExerciseField));
					char szTemp[260];
					printf("Please input ExchangeID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQryExercise.ExchangeID,"" );
					else
						hs_strncpy(stHSReqQryExercise.ExchangeID,szTemp,sizeof(stHSReqQryExercise.ExchangeID));
					printf("Please input InstrumentID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQryExercise.InstrumentID,"" );
					else
						hs_strncpy(stHSReqQryExercise.InstrumentID,szTemp,sizeof(stHSReqQryExercise.InstrumentID));
					printf("Please input ExerciseOrderSysID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQryExercise.ExerciseOrderSysID,"" );
					else
						hs_strncpy(stHSReqQryExercise.ExerciseOrderSysID,szTemp,sizeof(stHSReqQryExercise.ExerciseOrderSysID));
					
					int iRet = lpTradeSpi->lpUserApi->ReqQryExercise(&stHSReqQryExercise,lpTradeSpi->iRequestId++);
					if (iRet != SDK_OK)
					{
						printf(lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
					}
					break;
				}
			case 18:
				{
					CHSReqQryLockField stHSReqQryLock;
					memset(&stHSReqQryLock,0,sizeof(CHSReqQryLockField));
					char szTemp[260];
					printf("Please input ExchangeID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQryLock.ExchangeID,"" );
					else
						hs_strncpy(stHSReqQryLock.ExchangeID,szTemp,sizeof(stHSReqQryLock.ExchangeID));
					printf("Please input UnderlyingInstrID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQryLock.UnderlyingInstrID,"" );
					else
						hs_strncpy(stHSReqQryLock.UnderlyingInstrID,szTemp,sizeof(stHSReqQryLock.UnderlyingInstrID));
					printf("Please input LockOrderSysID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQryLock.LockOrderSysID,"" );
					else
						hs_strncpy(stHSReqQryLock.LockOrderSysID,szTemp,sizeof(stHSReqQryLock.LockOrderSysID));
					
					int iRet = lpTradeSpi->lpUserApi->ReqQryLock(&stHSReqQryLock,lpTradeSpi->iRequestId++);
					if (iRet != SDK_OK)
					{
						printf(lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
					}
					break;
				}
			case 19:
				{
					CHSReqQryCombActionField stHSReqQryCombAction;
					memset(&stHSReqQryCombAction,0,sizeof(CHSReqQryCombActionField));
					char szTemp[260];
					printf("Please input CombOrderSysID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQryCombAction.CombOrderSysID,"" );
					else
						hs_strncpy(stHSReqQryCombAction.CombOrderSysID,szTemp,sizeof(stHSReqQryCombAction.CombOrderSysID));
					printf("Please input ExchangeID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQryCombAction.ExchangeID,"" );
					else
						hs_strncpy(stHSReqQryCombAction.ExchangeID,szTemp,sizeof(stHSReqQryCombAction.ExchangeID));
					printf("Please input InstrumentID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQryCombAction.InstrumentID,"" );
					else
						hs_strncpy(stHSReqQryCombAction.InstrumentID,szTemp,sizeof(stHSReqQryCombAction.InstrumentID));
					
					int iRet = lpTradeSpi->lpUserApi->ReqQryCombAction(&stHSReqQryCombAction,lpTradeSpi->iRequestId++);
					if (iRet != SDK_OK)
					{
						printf(lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
					}
					break;
				}
			case 20:
				{
					CHSReqQryPositionCombineDetailField stHSReqQryPositionCombineDetail;
					memset(&stHSReqQryPositionCombineDetail,0,sizeof(CHSReqQryPositionCombineDetailField));			
					int iRet = lpTradeSpi->lpUserApi->ReqQryPositionCombineDetail(&stHSReqQryPositionCombineDetail,lpTradeSpi->iRequestId++);
					if (iRet != SDK_OK)
					{
						printf(lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
					}
					break;
				}
			case 21:
				{
					CHSReqQryInstrumentField stHSReqQryInstrument;
					memset(&stHSReqQryInstrument,0,sizeof(CHSReqQryInstrumentField));
					char szTemp[260];
					printf("Please input ExchangeID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQryInstrument.ExchangeID,"" );
					else
						hs_strncpy(stHSReqQryInstrument.ExchangeID,szTemp,sizeof(stHSReqQryInstrument.ExchangeID));
					printf("Please input InstrumentID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQryInstrument.InstrumentID,"" );
					else
						hs_strncpy(stHSReqQryInstrument.InstrumentID,szTemp,sizeof(stHSReqQryInstrument.InstrumentID));					
					int iRet = lpTradeSpi->lpUserApi->ReqQryInstrument(&stHSReqQryInstrument,lpTradeSpi->iRequestId++);
					if (iRet != SDK_OK)
					{
						printf(lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
					}
					break;
				}
			case 22:
				{
					CHSReqQryCoveredShortField stHSReqQryCoveredShort;
					memset(&stHSReqQryCoveredShort,0,sizeof(CHSReqQryCoveredShortField));
					char szTemp[260];
					printf("Please input ExchangeID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQryCoveredShort.ExchangeID,"" );
					else
						hs_strncpy(stHSReqQryCoveredShort.ExchangeID,szTemp,sizeof(stHSReqQryCoveredShort.ExchangeID));
					
					int iRet = lpTradeSpi->lpUserApi->ReqQryCoveredShort(&stHSReqQryCoveredShort,lpTradeSpi->iRequestId++);
					if (iRet != SDK_OK)
					{
						printf(lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
					}
					break;
				}
			case 23:
				{
					CHSReqQryExerciseAssignField stHSReqQryExerciseAssign;
					memset(&stHSReqQryExerciseAssign,0,sizeof(CHSReqQryExerciseAssignField));
					char szTemp[260];
					printf("Please input ExchangeID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQryExerciseAssign.ExchangeID,"" );
					else
						hs_strncpy(stHSReqQryExerciseAssign.ExchangeID,szTemp,sizeof(stHSReqQryExerciseAssign.ExchangeID));
					printf("Please input InstrumentID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQryExerciseAssign.InstrumentID,"" );
					else
						hs_strncpy(stHSReqQryExerciseAssign.InstrumentID,szTemp,sizeof(stHSReqQryExerciseAssign.InstrumentID));
					printf("Please input PositionType�����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						stHSReqQryExerciseAssign.PositionType = '\0';
					else
						stHSReqQryExerciseAssign.PositionType = szTemp[0];					
					int iRet = lpTradeSpi->lpUserApi->ReqQryExerciseAssign(&stHSReqQryExerciseAssign,lpTradeSpi->iRequestId++);
					if (iRet != SDK_OK)
					{
						printf(lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
					}
					break;
				}
			case 24:
				{
					CHSReqTransferField stHSReqTransfer;
					memset(&stHSReqTransfer,0,sizeof(CHSReqTransferField));
					char szTemp[260];
					printf("Please input BankID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqTransfer.BankID,"" );
					else
						hs_strncpy(stHSReqTransfer.BankID,szTemp,sizeof(stHSReqTransfer.BankID));
					printf("Please input TransferType�����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						stHSReqTransfer.TransferType = '\0';
					else
						stHSReqTransfer.TransferType = szTemp[0];
					printf( "Please input OccurBalance:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					stHSReqTransfer.OccurBalance = atof(szTemp);
					printf("Please input FundPassword �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqTransfer.FundPassword,"" );
					else
						hs_strncpy(stHSReqTransfer.FundPassword,szTemp,sizeof(stHSReqTransfer.FundPassword));
					printf("Please input BankPassword �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqTransfer.BankPassword,"" );
					else
						hs_strncpy(stHSReqTransfer.BankPassword,szTemp,sizeof(stHSReqTransfer.BankPassword));
					printf("Please input CurrencyID�����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						stHSReqTransfer.CurrencyID = '\0';
					else
						stHSReqTransfer.CurrencyID = szTemp[0];
					printf("Please input TransferOccasion �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqTransfer.TransferOccasion,"" );
					else
						hs_strncpy(stHSReqTransfer.TransferOccasion,szTemp,sizeof(stHSReqTransfer.TransferOccasion));
					
					int iRet = lpTradeSpi->lpUserApi->ReqTransfer(&stHSReqTransfer,lpTradeSpi->iRequestId++);
					if (iRet != SDK_OK)
					{
						printf(lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
					}
					break;
				}
			case 25:
				{
					CHSReqQryTransferField stHSReqQryTransfer;
					memset(&stHSReqQryTransfer,0,sizeof(CHSReqQryTransferField));
					char szTemp[260];
					printf("Please input BankID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQryTransfer.BankID,"" );
					else
						hs_strncpy(stHSReqQryTransfer.BankID,szTemp,sizeof(stHSReqQryTransfer.BankID));
					printf( "Please input TransferSerialID:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					stHSReqQryTransfer.TransferSerialID = atoi(szTemp);;
					
					int iRet = lpTradeSpi->lpUserApi->ReqQryTransfer(&stHSReqQryTransfer,lpTradeSpi->iRequestId++);
					if (iRet != SDK_OK)
					{
						printf(lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
					}
					break;
				}
			case 26:
				{
					CHSReqQueryBankBalanceField stHSReqQueryBankBalance;
					memset(&stHSReqQueryBankBalance,0,sizeof(CHSReqQueryBankBalanceField));
					char szTemp[260];
					printf("Please input BankID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQueryBankBalance.BankID,"" );
					else
						hs_strncpy(stHSReqQueryBankBalance.BankID,szTemp,sizeof(stHSReqQueryBankBalance.BankID));
					printf("Please input FundPassword �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQueryBankBalance.FundPassword,"" );
					else
						hs_strncpy(stHSReqQueryBankBalance.FundPassword,szTemp,sizeof(stHSReqQueryBankBalance.FundPassword));
					printf("Please input BankPassword �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQueryBankBalance.BankPassword,"" );
					else
						hs_strncpy(stHSReqQueryBankBalance.BankPassword,szTemp,sizeof(stHSReqQueryBankBalance.BankPassword));
					printf("Please input CurrencyID�����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						stHSReqQueryBankBalance.CurrencyID = '\0';
					else
						stHSReqQueryBankBalance.CurrencyID = szTemp[0];
					
					int iRet = lpTradeSpi->lpUserApi->ReqQueryBankBalance(&stHSReqQueryBankBalance,lpTradeSpi->iRequestId++);
					if (iRet != SDK_OK)
					{
						printf(lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
					}
					break;
				}
			case 27:
				{
					CHSReqQueryBankAccountField stHSReqQueryBankAccount;
					memset(&stHSReqQueryBankAccount,0,sizeof(CHSReqQueryBankAccountField));
					char szTemp[260];
					printf("Please input BankID �����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQueryBankAccount.BankID,"" );
					else
						hs_strncpy(stHSReqQueryBankAccount.BankID,szTemp,sizeof(stHSReqQueryBankAccount.BankID));
					printf("Please input CurrencyID�����봫��ֱ�ӻس���Enter����:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						stHSReqQueryBankAccount.CurrencyID = '\0';
					else
						stHSReqQueryBankAccount.CurrencyID = szTemp[0];					
					int iRet = lpTradeSpi->lpUserApi->ReqQueryBankAccount(&stHSReqQueryBankAccount,lpTradeSpi->iRequestId++);
					if (iRet != SDK_OK)
					{
						printf(lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
					}
					break;
				}
				case 28:
					{
						CHSReqQueryBillContentField stHSReqQueryBillContent;
						memset(&stHSReqQueryBillContent,0,sizeof(CHSReqQueryBillContentField));
						char szTemp[260];
						printf( "Please input BeginDate:");
						cin.clear();
						cin.ignore();
						cin.get(szTemp,260,'\n');
						stHSReqQueryBillContent.BeginDate = atoi(szTemp);
						printf( "Please input EndDate:");
						cin.clear();
						cin.ignore();
						cin.get(szTemp,260,'\n');
						stHSReqQueryBillContent.EndDate = atoi(szTemp);						
						int iRet = lpTradeSpi->lpUserApi->ReqQueryBillContent(&stHSReqQueryBillContent,lpTradeSpi->iRequestId++);
						if (iRet != SDK_OK)
						{
							printf(lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
						}
					break;
					}
				case 29:
					{
						CHSReqBillConfirmField stHSReqBillConfirm;
						memset(&stHSReqBillConfirm,0,sizeof(CHSReqBillConfirmField));
						int iRet = lpTradeSpi->lpUserApi->ReqBillConfirm(&stHSReqBillConfirm,lpTradeSpi->iRequestId++);
						if (iRet != SDK_OK)
						{
							printf(lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
						}
						break;
					}
				case 30:
					{
						CHSReqQryMarginField stHSReqQryMargin;
						memset(&stHSReqQryMargin,0,sizeof(CHSReqQryMarginField));
						char szTemp[260];
						printf("Please input ExchangeID�����봫��ֱ�ӻس���Enter����:");
						cin.clear();
						cin.ignore();
						cin.get(szTemp,260,'\n');
						if (szTemp[0] == 10)
							strcpy(stHSReqQryMargin.ExchangeID,"" );
						else
							hs_strncpy(stHSReqQryMargin.ExchangeID,szTemp,sizeof(stHSReqQryMargin.ExchangeID));
						printf("Please input InstrumentID�����봫��ֱ�ӻس���Enter����:");
						cin.clear();
						cin.ignore();
						cin.get(szTemp,260,'\n');
						if (szTemp[0] == 10)
							strcpy(stHSReqQryMargin.InstrumentID,"" );
						else
							hs_strncpy(stHSReqQryMargin.InstrumentID,szTemp,sizeof(stHSReqQryMargin.InstrumentID));
						printf("Please input UnderlyingInstrID�����봫��ֱ�ӻس���Enter����:");
						cin.clear();
						cin.ignore();
						cin.get(szTemp,260,'\n');
						if (szTemp[0] == 10)
							strcpy(stHSReqQryMargin.UnderlyingInstrID,"" );
						else
							hs_strncpy(stHSReqQryMargin.UnderlyingInstrID,szTemp,sizeof(stHSReqQryMargin.UnderlyingInstrID));
						printf("Please input HedgeType�����봫��ֱ�ӻس���Enter����:");
						cin.clear();
						cin.ignore();
						cin.get(szTemp,260,'\n');
						if (szTemp[0] == 10)
							stHSReqQryMargin.HedgeType = '\0';
						else
							stHSReqQryMargin.HedgeType = szTemp[0];					
						int iRet = lpTradeSpi->lpUserApi->ReqQryMargin(&stHSReqQryMargin,lpTradeSpi->iRequestId++);
						if (iRet != SDK_OK)
						{
							printf(lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
						}
						break;
					}
				case 31:
					{
						CHSReqQryCommissionField stHSReqQryCommission;
						memset(&stHSReqQryCommission,0,sizeof(CHSReqQryCommissionField));
						char szTemp[260];
						printf("Please input ProductType�����봫��ֱ�ӻس���Enter����:");
						cin.clear();
						cin.ignore();
						cin.get(szTemp,260,'\n');
						if (szTemp[0] == 10)
							stHSReqQryCommission.ProductType = '\0';
						else
							stHSReqQryCommission.ProductType = szTemp[0];
						printf("Please input InstrumentID�����봫��ֱ�ӻس���Enter����:");
						cin.clear();
						cin.ignore();
						cin.get(szTemp,260,'\n');
						if (szTemp[0] == 10)
							strcpy(stHSReqQryCommission.InstrumentID,"" );
						else
							hs_strncpy(stHSReqQryCommission.InstrumentID,szTemp,sizeof(stHSReqQryCommission.InstrumentID));
						printf("Please input UnderlyingInstrID�����봫��ֱ�ӻس���Enter����:");
						cin.clear();
						cin.ignore();
						cin.get(szTemp,260,'\n');
						if (szTemp[0] == 10)
							strcpy(stHSReqQryCommission.UnderlyingInstrID,"" );
						else
							hs_strncpy(stHSReqQryCommission.UnderlyingInstrID,szTemp,sizeof(stHSReqQryCommission.UnderlyingInstrID));
						printf("Please input ExchangeID�����봫��ֱ�ӻس���Enter����:");
						cin.clear();
						cin.ignore();
						cin.get(szTemp,260,'\n');
						if (szTemp[0] == 10)
							strcpy(stHSReqQryCommission.ExchangeID,"" );
						else
							hs_strncpy(stHSReqQryCommission.ExchangeID,szTemp,sizeof(stHSReqQryCommission.ExchangeID));				
						int iRet = lpTradeSpi->lpUserApi->ReqQryCommission(&stHSReqQryCommission,lpTradeSpi->iRequestId++);
						if (iRet != SDK_OK)
						{
							printf(lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
						}
						break;
					}
				case 32:
					{
						CHSReqQryPositionDetailField stHSReqQryPositionDetail;
						memset(&stHSReqQryPositionDetail,0,sizeof(CHSReqQryPositionDetailField));						
						int iRet = lpTradeSpi->lpUserApi->ReqQryPositionDetail(&stHSReqQryPositionDetail,lpTradeSpi->iRequestId++);
						if (iRet != SDK_OK)
						{
							printf(lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
						}
						break;
					}
				case 33:
					{
						CHSReqQrySysConfigField stHSReqQrySysConfig;
						memset(&stHSReqQrySysConfig,0,sizeof(CHSReqQrySysConfigField));
						int iRet = lpTradeSpi->lpUserApi->ReqQrySysConfig(&stHSReqQrySysConfig,lpTradeSpi->iRequestId++);
						if (iRet != SDK_OK)
						{
							printf(lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
						}
						break;
					}
				case 34:
					{
						CHSReqQryDepthMarketDataField stHSReqQryDepthMarketData;
						memset(&stHSReqQryDepthMarketData,0,sizeof(CHSReqQryDepthMarketDataField));
						char szTemp[260];
						printf("Please input ExchangeID�����봫��ֱ�ӻس���Enter����:");
						cin.clear();
						cin.ignore();
						cin.get(szTemp,260,'\n');
						if (szTemp[0] == 10)
							strcpy(stHSReqQryDepthMarketData.ExchangeID,"" );
						else
							hs_strncpy(stHSReqQryDepthMarketData.ExchangeID,szTemp,sizeof(stHSReqQryDepthMarketData.ExchangeID));
						printf("Please input InstrumentID�����봫��ֱ�ӻس���Enter����:");
						cin.clear();
						cin.ignore();
						cin.get(szTemp,260,'\n');
						if (szTemp[0] == 10)
							strcpy(stHSReqQryDepthMarketData.InstrumentID,"" );
						else
							hs_strncpy(stHSReqQryDepthMarketData.InstrumentID,szTemp,sizeof(stHSReqQryDepthMarketData.InstrumentID));
						int iRet = lpTradeSpi->lpUserApi->ReqQryDepthMarketData(&stHSReqQryDepthMarketData,lpTradeSpi->iRequestId++);
						if (iRet != SDK_OK)
						{
							printf(lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
						}
						break;
					}
				case 35:
					{
						CHSReqQryExchangeRateField stHSReqQryExchangeRate;
						memset(&stHSReqQryExchangeRate,0,sizeof(CHSReqQryExchangeRateField));
						char szTemp[260];
						printf("Please input FromCurrencyID�����봫��ֱ�ӻس���Enter����:");
						cin.clear();
						cin.ignore();
						cin.get(szTemp,260,'\n');
						if (szTemp[0] == 10)
							stHSReqQryExchangeRate.FromCurrencyID = '\0';
						else
							stHSReqQryExchangeRate.FromCurrencyID = szTemp[0];
						printf("Please input ToCurrencyID�����봫��ֱ�ӻس���Enter����:");
						cin.clear();
						cin.ignore();
						cin.get(szTemp,260,'\n');
						if (szTemp[0] == 10)
							stHSReqQryExchangeRate.ToCurrencyID = '\0';
						else
							stHSReqQryExchangeRate.ToCurrencyID = szTemp[0];						
						int iRet = lpTradeSpi->lpUserApi->ReqQryExchangeRate(&stHSReqQryExchangeRate,lpTradeSpi->iRequestId++);
						if (iRet != SDK_OK)
						{
							printf(lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
						}
					break;
				}
				default:
				{
					break;
				}  
			}

		}
		return;
	}
}

void CMyTradeSpi::login()
{
	addInfo("��½�����˻�");
	CHSReqUserLoginField stHSReqUserLogin;
	memset(&stHSReqUserLogin, 0, sizeof(CHSReqUserLoginField));
	strcpy(stHSReqUserLogin.AccountID, account_id);
	strcpy(stHSReqUserLogin.Password, password);
	stHSReqUserLogin.UserApplicationType = '7';

//		strcpy(stHSReqUserLogin.UserApplicationInfo, "");
	//	strcpy(stHSReqUserLogin.MacAddress, "");
	//	strcpy(stHSReqUserLogin.IPAddress, "");
	
	int iRet = lpTradeApi->ReqUserLogin(&stHSReqUserLogin, lpTradeSpi->iRequestId++);
	if (iRet != SDK_OK)
	{	
		CString str;
		str.Format("��½ʧ�� [%s]", lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
		addInfo(str);
	}
}


void CMyTradeSpi::queryFund()
{
	addInfo("��ѯ�ʽ���Ϣ");
	CHSReqQryTradingAccountField stHSReqQryTradingAccount;
	memset(&stHSReqQryTradingAccount, 0, sizeof(CHSReqQryTradingAccountField));
	int iRet = lpTradeSpi->lpUserApi->ReqQryTradingAccount(&stHSReqQryTradingAccount, lpTradeSpi->iRequestId++);
	if (iRet != SDK_OK)
	{
		addInfo(lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
	}
}

void CMyTradeSpi::queryPosition()
{
	addInfo("��ѯ�˻��ֲ�");
	CHSReqQryPositionField stHSReqQryPosition;
	memset(&stHSReqQryPosition, 0, sizeof(CHSReqQryPositionField));
	strcpy(stHSReqQryPosition.ExchangeID, "");
	strcpy(stHSReqQryPosition.InstrumentID, "");
	int iRet = lpTradeSpi->lpUserApi->ReqQryPosition(&stHSReqQryPosition, lpTradeSpi->iRequestId++);
	if (iRet != SDK_OK)
	{
		addInfo(lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
	}
}

void CMyTradeSpi::queryStockCode()
{
	CHSReqQryInstrumentField stHSReqQryInstrument;
	memset(&stHSReqQryInstrument, 0, sizeof(CHSReqQryInstrumentField));
	strcpy(stHSReqQryInstrument.ExchangeID, "");
	strcpy(stHSReqQryInstrument.InstrumentID, "");
	int iRet = lpTradeSpi->lpUserApi->ReqQryInstrument(&stHSReqQryInstrument, lpTradeSpi->iRequestId++);
	if (iRet != SDK_OK)
	{
		addInfo(lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
	}
}

int CMyTradeSpi::sendOrder(CString code, double price, HSDirection direction, HSOffsetFlag offset)
{
	int orderRef = iRequestId++;
	sOrderRef.Format("%d", orderRef);
	CHSReqOrderInsertField stHSReqOrderInsert;
	memset(&stHSReqOrderInsert, 0, sizeof(CHSReqOrderInsertField));
	strcpy(stHSReqOrderInsert.OrderRef, sOrderRef);
	strcpy(stHSReqOrderInsert.ExchangeID, mapStockCode[code]);
	strcpy(stHSReqOrderInsert.InstrumentID, code);
	stHSReqOrderInsert.Direction = direction;
	stHSReqOrderInsert.OffsetFlag = offset;
	stHSReqOrderInsert.HedgeType = HS_HT_Speculation;
	stHSReqOrderInsert.OrderPrice = price;
	stHSReqOrderInsert.OrderVolume = 1;
	strcpy(stHSReqOrderInsert.OrderCommand, HS_CT_Limit);
	stHSReqOrderInsert.MinVolume = 1;
	stHSReqOrderInsert.SpringPrice = 0;
	stHSReqOrderInsert.SwapOrderFlag = '\0';
	int iRet = lpTradeSpi->lpUserApi->ReqOrderInsert(&stHSReqOrderInsert, lpTradeSpi->iRequestId++);
	if (iRet != SDK_OK)
	{
		addInfo(lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
	}
	else
	{
		CString str,sDirection,sOffset;
		if (direction == HS_D_Buy) {
			sDirection = "��";
		}
		else {
			sDirection = "��";
		}
		if (offset == HS_OF_Open) {
			sOffset = "��";
		}
		else if (offset == HS_OF_CloseToday) {
			sOffset = "ƽ��";
		}
		else {
			sOffset = "ƽ��";
		}

		str.Format("ί�гɹ�,���[%d]��[%s %.4f %s %s]", orderRef, code, price, sDirection, sOffset);
		addInfo(str);
	}

	return 0;
}


void CMyTradeSpi::withdraw()
{
	CHSReqOrderActionField stHSReqOrderAction;
	memset(&stHSReqOrderAction, 0, sizeof(CHSReqOrderActionField));
	strcpy(stHSReqOrderAction.OrderSysID, "");
	strcpy(stHSReqOrderAction.ExchangeID, "");
	stHSReqOrderAction.SessionID = sessionID;
	strcpy(stHSReqOrderAction.OrderRef, sOrderRef);
	strcpy(stHSReqOrderAction.OrderActionRef, "");
	int iRet = lpTradeSpi->lpUserApi->ReqOrderAction(&stHSReqOrderAction, lpTradeSpi->iRequestId++);
	if (iRet != SDK_OK)
	{
		addInfo(lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
	}
	else {
		addInfo("���𳷵� id=["+ sOrderRef+"]");
	}

}

//336800�ͻ���¼
void  CMyTradeSpi::OnRspUserLogin(CHSRspUserLoginField *pRspUserLogin, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (IsErrorRspInfo(pRspInfo)==false) {
		addInfo("��¼�����˻��ɹ�");
		sessionID = pRspUserLogin->SessionID;
		queryFund();
		queryPosition();
		queryStockCode();
	}


    if(! pRspUserLogin && bIsLast == true )
    {
        cout<<"Ӧ�����!"<<endl;
    }
    else
    {
        cout<<"************************�ͻ���¼Ӧ��!*************************"<<endl;
        printf("\t%30s = %35d\r\n","BranchID:",pRspUserLogin->BranchID);
        printf("\t%30s = %35s\r\n","AccountID:",pRspUserLogin->AccountID);
        printf("\t%30s = %35s\r\n","UserName:",pRspUserLogin->UserName);
        printf("\t%30s = %35d\r\n","TradingDay:",pRspUserLogin->TradingDay);
        printf("\t%30s = %35d\r\n","PreTradingDay:",pRspUserLogin->PreTradingDay);
        printf("\t%30s = %35c\r\n","BillConfirmFlag:",pRspUserLogin->BillConfirmFlag);
        printf("\t%30s = %35d\r\n","SessionID:",pRspUserLogin->SessionID);
        printf("\t%30s = %35c\r\n","UserApplicationType:",pRspUserLogin->UserApplicationType);
        printf("\t%30s = %35s\r\n","UserApplicationInfo:",pRspUserLogin->UserApplicationInfo);
        printf("\t%30s = %35s\r\n","RiskLevel:",pRspUserLogin->RiskLevel);
        printf("\t%30s = %35s\r\n","LastMacAddress:",pRspUserLogin->LastMacAddress);
        printf("\t%30s = %35s\r\n","LastIPAddress:",pRspUserLogin->LastIPAddress);
        printf("\t%30s = %35d\r\n","LastLoginTime:",pRspUserLogin->LastLoginTime);
        printf("\t%30s = %35d\r\n","CZCETime:",pRspUserLogin->CZCETime);
        printf("\t%30s = %35d\r\n","DCETime:",pRspUserLogin->DCETime);
        printf("\t%30s = %35d\r\n","SHFETime:",pRspUserLogin->SHFETime);
        printf("\t%30s = %35d\r\n","CFFEXTime:",pRspUserLogin->CFFEXTime);
        printf("\t%30s = %35d\r\n","INETime:",pRspUserLogin->INETime);
    }
}

//336801�������
void  CMyTradeSpi::OnRspUserPasswordUpdate(CHSRspUserPasswordUpdateField *pRspUserPasswordUpdate, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspUserPasswordUpdate && bIsLast == true )
    {
        cout<<"Ӧ�����!"<<endl;
    }
    else
    {
        cout<<"************************�������Ӧ��!*************************"<<endl;
    }
	if (pRspInfo->ErrorID == 0)
	{
		cout<<"�����޸ĳɹ�"<<endl;
	}
}
//336812����¼��
void  CMyTradeSpi::OnRspErrorOrderInsert(CHSRspOrderInsertField *pRspOrderInsert, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspOrderInsert && bIsLast == true )
    {
        cout<<"Ӧ�����!"<<endl;
    }
    else
    {
		CString str;
		str.Format("ί��ʧ�ܣ�[id=%s msg=[%s]]", pRspOrderInsert->OrderRef,pRspInfo->ErrorMsg);
		addInfo(str);

        cout<<"************************����¼��Ӧ��!*************************"<<endl;
        printf("\t%30s = %35s\r\n","AccountID:",pRspOrderInsert->AccountID);
        printf("\t%30s = %35s\r\n","OrderSysID:",pRspOrderInsert->OrderSysID);
        printf("\t%30s = %35s\r\n","BrokerOrderID:",pRspOrderInsert->BrokerOrderID);
        printf("\t%30s = %35d\r\n","SessionID:",pRspOrderInsert->SessionID);
        printf("\t%30s = %35s\r\n","OrderRef:",pRspOrderInsert->OrderRef);
        printf("\t%30s = %35s\r\n","InstrumentID:",pRspOrderInsert->InstrumentID);
        printf("\t%30s = %35s\r\n","ExchangeID:",pRspOrderInsert->ExchangeID);
        printf("\t%30s = %35c\r\n","Direction:",pRspOrderInsert->Direction);
        printf("\t%30s = %35c\r\n","OffsetFlag:",pRspOrderInsert->OffsetFlag);
        printf("\t%30s = %35c\r\n","HedgeType:",pRspOrderInsert->HedgeType);
        printf("\t%30s = %35f\r\n","OrderPrice:",pRspOrderInsert->OrderPrice);
        printf("\t%30s = %35f\r\n","OrderVolume:",pRspOrderInsert->OrderVolume);
        printf("\t%30s = %35c\r\n","OrderStatus:",pRspOrderInsert->OrderStatus);
        printf("\t%30s = %35s\r\n","OrderCommand:",pRspOrderInsert->OrderCommand);
        printf("\t%30s = %35d\r\n","InsertTime:",pRspOrderInsert->InsertTime);
        printf("\t%30s = %35f\r\n","MinVolume:",pRspOrderInsert->MinVolume);
        printf("\t%30s = %35f\r\n","SpringPrice:",pRspOrderInsert->SpringPrice);
        printf("\t%30s = %35c\r\n","SwapOrderFlag:",pRspOrderInsert->SwapOrderFlag);
    }
}
//336813����
void  CMyTradeSpi::OnRspOrderAction(CHSRspOrderActionField *pRspOrderAction, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspOrderAction && bIsLast == true )
    {
        cout<<"Ӧ�����!"<<endl;
    }
    else
    {
		CString str;
		str.Format("�����Ѿ����� id = [%s]", pRspOrderAction->OrderRef );
		addInfo(str);
		
		cout<<"************************����Ӧ��!*************************"<<endl;
        printf("\t%30s = %35s\r\n","AccountID:",pRspOrderAction->AccountID);
        printf("\t%30s = %35s\r\n","OrderSysID:",pRspOrderAction->OrderSysID);
        printf("\t%30s = %35s\r\n","ExchangeID:",pRspOrderAction->ExchangeID);
        printf("\t%30s = %35d\r\n","SessionID:",pRspOrderAction->SessionID);
        printf("\t%30s = %35s\r\n","OrderRef:",pRspOrderAction->OrderRef);
        printf("\t%30s = %35c\r\n","OrderStatus:",pRspOrderAction->OrderStatus);
        printf("\t%30s = %35d\r\n","InsertTime:",pRspOrderAction->InsertTime);
        printf("\t%30s = %35s\r\n","OrderActionRef:",pRspOrderAction->OrderActionRef);
    }
}
//336814��Ȩ¼��
void  CMyTradeSpi::OnRspErrorExerciseOrderInsert(CHSRspExerciseOrderInsertField *pRspExerciseOrderInsert, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspExerciseOrderInsert && bIsLast == true )
    {
        cout<<"Ӧ�����!"<<endl;
    }
    else
    {
        cout<<"************************��Ȩ¼��Ӧ��!*************************"<<endl;
        printf("\t%30s = %35s\r\n","AccountID:",pRspExerciseOrderInsert->AccountID);
        printf("\t%30s = %35d\r\n","SessionID:",pRspExerciseOrderInsert->SessionID);
        printf("\t%30s = %35s\r\n","ExerciseOrderSysID:",pRspExerciseOrderInsert->ExerciseOrderSysID);
        printf("\t%30s = %35s\r\n","ExerciseRef:",pRspExerciseOrderInsert->ExerciseRef);
        printf("\t%30s = %35s\r\n","ExchangeID:",pRspExerciseOrderInsert->ExchangeID);
        printf("\t%30s = %35s\r\n","InstrumentID:",pRspExerciseOrderInsert->InstrumentID);
        printf("\t%30s = %35f\r\n","OrderVolume:",pRspExerciseOrderInsert->OrderVolume);
        printf("\t%30s = %35c\r\n","ExerciseType:",pRspExerciseOrderInsert->ExerciseType);
        printf("\t%30s = %35c\r\n","HedgeType:",pRspExerciseOrderInsert->HedgeType);
        printf("\t%30s = %35c\r\n","OrderStatus:",pRspExerciseOrderInsert->OrderStatus);
        printf("\t%30s = %35d\r\n","InsertTime:",pRspExerciseOrderInsert->InsertTime);
    }
}
//336815��Ȩ����
void  CMyTradeSpi::OnRspExerciseOrderAction(CHSRspExerciseOrderActionField *pRspExerciseOrderAction, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspExerciseOrderAction && bIsLast == true )
    {
        cout<<"Ӧ�����!"<<endl;
    }
    else
    {
        cout<<"************************��Ȩ����Ӧ��!*************************"<<endl;
        printf("\t%30s = %35s\r\n","AccountID:",pRspExerciseOrderAction->AccountID);
        printf("\t%30s = %35s\r\n","ExchangeID:",pRspExerciseOrderAction->ExchangeID);
        printf("\t%30s = %35s\r\n","ExerciseOrderSysID:",pRspExerciseOrderAction->ExerciseOrderSysID);
        printf("\t%30s = %35s\r\n","ExerciseRef:",pRspExerciseOrderAction->ExerciseRef);
        printf("\t%30s = %35d\r\n","SessionID:",pRspExerciseOrderAction->SessionID);
        printf("\t%30s = %35c\r\n","OrderStatus:",pRspExerciseOrderAction->OrderStatus);
        printf("\t%30s = %35s\r\n","ExecOrderActionRef:",pRspExerciseOrderAction->ExecOrderActionRef);
    }
}
//336913����¼��
void  CMyTradeSpi::OnRspErrorLockInsert(CHSRspLockInsertField *pRspLockInsert, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspLockInsert && bIsLast == true )
    {
        cout<<"Ӧ�����!"<<endl;
    }
    else
    {
        cout<<"************************����¼��Ӧ��!*************************"<<endl;
        printf("\t%30s = %35s\r\n","AccountID:",pRspLockInsert->AccountID);
        printf("\t%30s = %35s\r\n","LockOrderSysID:",pRspLockInsert->LockOrderSysID);
        printf("\t%30s = %35s\r\n","ExchangeID:",pRspLockInsert->ExchangeID);
        printf("\t%30s = %35s\r\n","UnderlyingInstrID:",pRspLockInsert->UnderlyingInstrID);
        printf("\t%30s = %35c\r\n","LockType:",pRspLockInsert->LockType);
        printf("\t%30s = %35f\r\n","OrderVolume:",pRspLockInsert->OrderVolume);
        printf("\t%30s = %35s\r\n","UnderlyingAccountID:",pRspLockInsert->UnderlyingAccountID);
        printf("\t%30s = %35c\r\n","OrderStatus:",pRspLockInsert->OrderStatus);
        printf("\t%30s = %35d\r\n","InsertTime:",pRspLockInsert->InsertTime);
    }
}
//336817ѯ��¼��
void  CMyTradeSpi::OnRspForQuoteInsert(CHSRspForQuoteInsertField *pRspForQuoteInsert, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspForQuoteInsert && bIsLast == true )
    {
        cout<<"Ӧ�����!"<<endl;
    }
    else
    {
        cout<<"************************ѯ��¼��Ӧ��!*************************"<<endl;
        printf("\t%30s = %35s\r\n","AccountID:",pRspForQuoteInsert->AccountID);
        printf("\t%30s = %35s\r\n","ExchangeID:",pRspForQuoteInsert->ExchangeID);
        printf("\t%30s = %35s\r\n","InstrumentID:",pRspForQuoteInsert->InstrumentID);
        printf("\t%30s = %35c\r\n","OrderStatus:",pRspForQuoteInsert->OrderStatus);
    }
}
//336818�������¼��
void  CMyTradeSpi::OnRspErrorCombActionInsert(CHSRspCombActionInsertField *pRspCombActionInsert, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspCombActionInsert && bIsLast == true )
    {
        cout<<"Ӧ�����!"<<endl;
    }
    else
    {
        cout<<"************************�������¼��Ӧ��!*************************"<<endl;
        printf("\t%30s = %35s\r\n","AccountID:",pRspCombActionInsert->AccountID);
        printf("\t%30s = %35s\r\n","CombOrderSysID:",pRspCombActionInsert->CombOrderSysID);
        printf("\t%30s = %35s\r\n","ExchangeID:",pRspCombActionInsert->ExchangeID);
        printf("\t%30s = %35s\r\n","InstrumentID:",pRspCombActionInsert->InstrumentID);
        printf("\t%30s = %35s\r\n","CombStrategyID:",pRspCombActionInsert->CombStrategyID);
        printf("\t%30s = %35s\r\n","CombPositionID:",pRspCombActionInsert->CombPositionID);
        printf("\t%30s = %35c\r\n","CombDirection:",pRspCombActionInsert->CombDirection);
        printf("\t%30s = %35f\r\n","OrderVolume:",pRspCombActionInsert->OrderVolume);
        printf("\t%30s = %35c\r\n","HedgeType:",pRspCombActionInsert->HedgeType);
        printf("\t%30s = %35c\r\n","OrderStatus:",pRspCombActionInsert->OrderStatus);
        printf("\t%30s = %35d\r\n","InsertTime:",pRspCombActionInsert->InsertTime);
        printf("\t%30s = %35c\r\n","Direction:",pRspCombActionInsert->Direction);
    }
}
//336810��󱨵�������ȡ
void  CMyTradeSpi::OnRspQueryMaxOrderVolume(CHSRspQueryMaxOrderVolumeField *pRspQueryMaxOrderVolume, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQueryMaxOrderVolume && bIsLast == true )
    {
        cout<<"Ӧ�����!"<<endl;
    }
    else
    {
        cout<<"************************��󱨵�������ȡӦ��!*************************"<<endl;
        printf("\t%30s = %35s\r\n","AccountID:",pRspQueryMaxOrderVolume->AccountID);
        printf("\t%30s = %35f\r\n","MaxOrderVolume:",pRspQueryMaxOrderVolume->MaxOrderVolume);
        printf("\t%30s = %35f\r\n","MaxOrderVolumeUnit:",pRspQueryMaxOrderVolume->MaxOrderVolumeUnit);
        printf("\t%30s = %35s\r\n","ExchangeID:",pRspQueryMaxOrderVolume->ExchangeID);
        printf("\t%30s = %35s\r\n","InstrumentID:",pRspQueryMaxOrderVolume->InstrumentID);
        printf("\t%30s = %35s\r\n","OrderCommand:",pRspQueryMaxOrderVolume->OrderCommand);
        printf("\t%30s = %35c\r\n","Direction:",pRspQueryMaxOrderVolume->Direction);
        printf("\t%30s = %35c\r\n","OffsetFlag:",pRspQueryMaxOrderVolume->OffsetFlag);
        printf("\t%30s = %35c\r\n","HedgeType:",pRspQueryMaxOrderVolume->HedgeType);
        printf("\t%30s = %35f\r\n","OrderPrice:",pRspQueryMaxOrderVolume->OrderPrice);
    }
}
//336912������������ȡ
void  CMyTradeSpi::OnRspQueryLockVolume(CHSRspQueryLockVolumeField *pRspQueryLockVolume, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQueryLockVolume && bIsLast == true )
    {
        cout<<"Ӧ�����!"<<endl;
    }
    else
    {
        cout<<"************************������������ȡӦ��!*************************"<<endl;
        printf("\t%30s = %35s\r\n","AccountID:",pRspQueryLockVolume->AccountID);
        printf("\t%30s = %35s\r\n","ExchangeID:",pRspQueryLockVolume->ExchangeID);
        printf("\t%30s = %35s\r\n","UnderlyingInstrID:",pRspQueryLockVolume->UnderlyingInstrID);
        printf("\t%30s = %35c\r\n","LockType:",pRspQueryLockVolume->LockType);
        printf("\t%30s = %35f\r\n","AvailablePositionVolume:",pRspQueryLockVolume->AvailablePositionVolume);
    }
}
//336819����Ȩ������ȡ
void  CMyTradeSpi::OnRspQueryExerciseVolume(CHSRspQueryExerciseVolumeField *pRspQueryExerciseVolume, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQueryExerciseVolume && bIsLast == true )
    {
        cout<<"Ӧ�����!"<<endl;
    }
    else
    {
        cout<<"************************����Ȩ������ȡӦ��!*************************"<<endl;
        printf("\t%30s = %35s\r\n","AccountID:",pRspQueryExerciseVolume->AccountID);
        printf("\t%30s = %35f\r\n","MaxOrderVolumeUnit:",pRspQueryExerciseVolume->MaxOrderVolumeUnit);
        printf("\t%30s = %35s\r\n","ExchangeID:",pRspQueryExerciseVolume->ExchangeID);
        printf("\t%30s = %35s\r\n","InstrumentID:",pRspQueryExerciseVolume->InstrumentID);
    }
}
//336851�ֲֻ��ܲ�ѯ
void  CMyTradeSpi::OnRspQryPosition(CHSRspQryPositionField *pRspQryPosition, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQryPosition && bIsLast == true )
    {
        cout<<"Ӧ�����!"<<endl;
    }
    else
    {
		CString str;
		CString str_d = "��ͷ";
		if(pRspQryPosition->Direction== HS_D_Sell)
			str_d = "��ͷ";
		str.Format("����=[%s] ����=[%s] �ܲ�λ=[%.0f] ", pRspQryPosition->InstrumentID, str_d, pRspQryPosition->PositionVolume);
		addInfo(str);
		mainDlg->mStockCode.GetWindowTextA(str);
		if (str == "") {
			mainDlg->mStockCode.SetWindowTextA(pRspQryPosition->InstrumentID);
		}
        cout<<"************************�ֲֻ��ܲ�ѯӦ��!*************************"<<endl;
        printf("\t%30s = %35s\r\n","AccountID:",pRspQryPosition->AccountID);
        printf("\t%30s = %35s\r\n","ExchangeID:",pRspQryPosition->ExchangeID);
        printf("\t%30s = %35s\r\n","InstrumentID:",pRspQryPosition->InstrumentID);
        printf("\t%30s = %35c\r\n","Direction:",pRspQryPosition->Direction);
        printf("\t%30s = %35c\r\n","HedgeType:",pRspQryPosition->HedgeType);
        printf("\t%30s = %35f\r\n","YdPositionVolume:",pRspQryPosition->YdPositionVolume);
        printf("\t%30s = %35f\r\n","PositionVolume:",pRspQryPosition->PositionVolume);
        printf("\t%30s = %35f\r\n","TodayPositionVolume:",pRspQryPosition->TodayPositionVolume);
        printf("\t%30s = %35f\r\n","AvailablePositionVolume:",pRspQryPosition->AvailablePositionVolume);
        printf("\t%30s = %35f\r\n","TodayAvailablePositionVolume:",pRspQryPosition->TodayAvailablePositionVolume);
        printf("\t%30s = %35f\r\n","PositionMargin:",pRspQryPosition->PositionMargin);
        printf("\t%30s = %35f\r\n","Premium:",pRspQryPosition->Premium);
        printf("\t%30s = %35f\r\n","Commission:",pRspQryPosition->Commission);
        printf("\t%30s = %35f\r\n","OpenFrozenVolume:",pRspQryPosition->OpenFrozenVolume);
        printf("\t%30s = %35f\r\n","CloseFrozenVolume:",pRspQryPosition->CloseFrozenVolume);
        printf("\t%30s = %35f\r\n","CombVolume:",pRspQryPosition->CombVolume);
        printf("\t%30s = %35f\r\n","ExerciseFrozenVolume:",pRspQryPosition->ExerciseFrozenVolume);
        printf("\t%30s = %35f\r\n","FrozenMargin:",pRspQryPosition->FrozenMargin);
        printf("\t%30s = %35f\r\n","ExerciseFrozenMargin:",pRspQryPosition->ExerciseFrozenMargin);
        printf("\t%30s = %35f\r\n","FrozenPremium:",pRspQryPosition->FrozenPremium);
        printf("\t%30s = %35f\r\n","FrozenCommission:",pRspQryPosition->FrozenCommission);
        printf("\t%30s = %35f\r\n","OpenVolume:",pRspQryPosition->OpenVolume);
        printf("\t%30s = %35f\r\n","CloseVolume:",pRspQryPosition->CloseVolume);
        printf("\t%30s = %35f\r\n","OpenBalance:",pRspQryPosition->OpenBalance);
        printf("\t%30s = %35f\r\n","CloseBalance:",pRspQryPosition->CloseBalance);
        printf("\t%30s = %35f\r\n","OpenCost:",pRspQryPosition->OpenCost);
        printf("\t%30s = %35f\r\n","PositionCost:",pRspQryPosition->PositionCost);
        printf("\t%30s = %35f\r\n","PositionProfit:",pRspQryPosition->PositionProfit);
        printf("\t%30s = %35f\r\n","CloseProfit:",pRspQryPosition->CloseProfit);
        printf("\t%30s = %35f\r\n","OptionsMarketValue:",pRspQryPosition->OptionsMarketValue);
        printf("\t%30s = %35s\r\n","UnderlyingInstrID:",pRspQryPosition->UnderlyingInstrID);
    }
}
//336850�ʽ��˻���ѯ
void  CMyTradeSpi::OnRspQryTradingAccount(CHSRspQryTradingAccountField *pRspQryTradingAccount, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQryTradingAccount && bIsLast == true )
    {
        cout<<"Ӧ�����!"<<endl;
    }
    else
    {

		CString str;
		str.Format("��Ȩ��=[%.2f] �����ʽ�=[%.2f]", pRspQryTradingAccount->Equity, pRspQryTradingAccount->AvailableBalance);
		addInfo(str);

        cout<<"************************�ʽ��˻���ѯӦ��!*************************"<<endl;
        printf("\t%30s = %35s\r\n","AccountID:",pRspQryTradingAccount->AccountID);
        printf("\t%30s = %35f\r\n","YdBalance:",pRspQryTradingAccount->YdBalance);
        printf("\t%30s = %35f\r\n","YdPositionMargin:",pRspQryTradingAccount->YdPositionMargin);
        printf("\t%30s = %35f\r\n","YdFundEquity:",pRspQryTradingAccount->YdFundEquity);
        printf("\t%30s = %35f\r\n","FundEquity:",pRspQryTradingAccount->FundEquity);
        printf("\t%30s = %35f\r\n","OptionsMarketValue:",pRspQryTradingAccount->OptionsMarketValue);
        printf("\t%30s = %35f\r\n","Equity:",pRspQryTradingAccount->Equity);
        printf("\t%30s = %35f\r\n","AvailableBalance:",pRspQryTradingAccount->AvailableBalance);
        printf("\t%30s = %35f\r\n","WithdrawBalance:",pRspQryTradingAccount->WithdrawBalance);
        printf("\t%30s = %35f\r\n","Margin:",pRspQryTradingAccount->Margin);
        printf("\t%30s = %35f\r\n","FrozenMargin:",pRspQryTradingAccount->FrozenMargin);
        printf("\t%30s = %35f\r\n","ExerciseFrozenMargin:",pRspQryTradingAccount->ExerciseFrozenMargin);
        printf("\t%30s = %35f\r\n","RiskDegree:",pRspQryTradingAccount->RiskDegree);
        printf("\t%30s = %35f\r\n","Premium:",pRspQryTradingAccount->Premium);
        printf("\t%30s = %35f\r\n","FrozenPremium:",pRspQryTradingAccount->FrozenPremium);
        printf("\t%30s = %35f\r\n","Commission:",pRspQryTradingAccount->Commission);
        printf("\t%30s = %35f\r\n","FrozenCommission:",pRspQryTradingAccount->FrozenCommission);
        printf("\t%30s = %35f\r\n","CloseProfit:",pRspQryTradingAccount->CloseProfit);
        printf("\t%30s = %35f\r\n","PositionProfit:",pRspQryTradingAccount->PositionProfit);
        printf("\t%30s = %35f\r\n","CloseProfitByDate:",pRspQryTradingAccount->CloseProfitByDate);
        printf("\t%30s = %35f\r\n","PositionProfitByDate:",pRspQryTradingAccount->PositionProfitByDate);
        printf("\t%30s = %35f\r\n","Deposit:",pRspQryTradingAccount->Deposit);
        printf("\t%30s = %35f\r\n","Withdraw:",pRspQryTradingAccount->Withdraw);
        printf("\t%30s = %35f\r\n","FundMortgage:",pRspQryTradingAccount->FundMortgage);
        printf("\t%30s = %35f\r\n","WarrantMortgage:",pRspQryTradingAccount->WarrantMortgage);
        printf("\t%30s = %35f\r\n","FrozenBalance:",pRspQryTradingAccount->FrozenBalance);
        printf("\t%30s = %35f\r\n","UnFrozenBalance:",pRspQryTradingAccount->UnFrozenBalance);
        printf("\t%30s = %35c\r\n","CurrencyID:",pRspQryTradingAccount->CurrencyID);
    }
}
//336853������ѯ
void  CMyTradeSpi::OnRspQryOrder(CHSOrderField *pRspQryOrder, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQryOrder && bIsLast == true )
    {
        cout<<"Ӧ�����!"<<endl;
    }
    else
    {
        cout<<"************************������ѯӦ��!*************************"<<endl;
        printf("\t%30s = %35s\r\n","AccountID:",pRspQryOrder->AccountID);
        printf("\t%30s = %35s\r\n","OrderSysID:",pRspQryOrder->OrderSysID);
        printf("\t%30s = %35s\r\n","BrokerOrderID:",pRspQryOrder->BrokerOrderID);
        printf("\t%30s = %35d\r\n","SessionID:",pRspQryOrder->SessionID);
        printf("\t%30s = %35s\r\n","OrderRef:",pRspQryOrder->OrderRef);
        printf("\t%30s = %35s\r\n","ExchangeID:",pRspQryOrder->ExchangeID);
        printf("\t%30s = %35s\r\n","InstrumentID:",pRspQryOrder->InstrumentID);
        printf("\t%30s = %35c\r\n","Direction:",pRspQryOrder->Direction);
        printf("\t%30s = %35c\r\n","OffsetFlag:",pRspQryOrder->OffsetFlag);
        printf("\t%30s = %35c\r\n","HedgeType:",pRspQryOrder->HedgeType);
        printf("\t%30s = %35f\r\n","OrderPrice:",pRspQryOrder->OrderPrice);
        printf("\t%30s = %35f\r\n","OrderVolume:",pRspQryOrder->OrderVolume);
        printf("\t%30s = %35c\r\n","OrderStatus:",pRspQryOrder->OrderStatus);
        printf("\t%30s = %35f\r\n","TradeVolume:",pRspQryOrder->TradeVolume);
        printf("\t%30s = %35f\r\n","CancelVolume:",pRspQryOrder->CancelVolume);
        printf("\t%30s = %35f\r\n","TradePrice:",pRspQryOrder->TradePrice);
        printf("\t%30s = %35d\r\n","TradingDay:",pRspQryOrder->TradingDay);
        printf("\t%30s = %35d\r\n","InsertDate:",pRspQryOrder->InsertDate);
        printf("\t%30s = %35d\r\n","InsertTime:",pRspQryOrder->InsertTime);
        printf("\t%30s = %35d\r\n","ReportTime:",pRspQryOrder->ReportTime);
        printf("\t%30s = %35s\r\n","OrderCommand:",pRspQryOrder->OrderCommand);
        printf("\t%30s = %35f\r\n","MinVolume:",pRspQryOrder->MinVolume);
        printf("\t%30s = %35f\r\n","SpringPrice:",pRspQryOrder->SpringPrice);
        printf("\t%30s = %35c\r\n","SwapOrderFlag:",pRspQryOrder->SwapOrderFlag);
        printf("\t%30s = %35c\r\n","ForceCloseReason:",pRspQryOrder->ForceCloseReason);
        printf("\t%30s = %35s\r\n","ErrorMsg:",pRspQryOrder->ErrorMsg);
        printf("\t%30s = %35s\r\n","UnderlyingInstrID:",pRspQryOrder->UnderlyingInstrID);
        printf("\t%30s = %35c\r\n","OrderSource:",pRspQryOrder->OrderSource);
    }
}
//336854�ɽ���ѯ
void  CMyTradeSpi::OnRspQryTrade(CHSTradeField *pRspQryTrade, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQryTrade && bIsLast == true )
    {
        cout<<"Ӧ�����!"<<endl;
    }
    else
    {
        cout<<"************************�ɽ���ѯӦ��!*************************"<<endl;
        printf("\t%30s = %35s\r\n","AccountID:",pRspQryTrade->AccountID);
        printf("\t%30s = %35s\r\n","TradeID:",pRspQryTrade->TradeID);
        printf("\t%30s = %35s\r\n","OrderSysID:",pRspQryTrade->OrderSysID);
        printf("\t%30s = %35s\r\n","BrokerOrderID:",pRspQryTrade->BrokerOrderID);
        printf("\t%30s = %35d\r\n","SessionID:",pRspQryTrade->SessionID);
        printf("\t%30s = %35s\r\n","OrderRef:",pRspQryTrade->OrderRef);
        printf("\t%30s = %35s\r\n","ExchangeID:",pRspQryTrade->ExchangeID);
        printf("\t%30s = %35s\r\n","InstrumentID:",pRspQryTrade->InstrumentID);
        printf("\t%30s = %35c\r\n","Direction:",pRspQryTrade->Direction);
        printf("\t%30s = %35c\r\n","OffsetFlag:",pRspQryTrade->OffsetFlag);
        printf("\t%30s = %35c\r\n","HedgeType:",pRspQryTrade->HedgeType);
        printf("\t%30s = %35f\r\n","TradeVolume:",pRspQryTrade->TradeVolume);
        printf("\t%30s = %35f\r\n","TradePrice:",pRspQryTrade->TradePrice);
        printf("\t%30s = %35d\r\n","TradingDay:",pRspQryTrade->TradingDay);
        printf("\t%30s = %35d\r\n","TradeTime:",pRspQryTrade->TradeTime);
        printf("\t%30s = %35s\r\n","UnderlyingInstrID:",pRspQryTrade->UnderlyingInstrID);
    }
}
//336855��Ȩ��ѯ
void  CMyTradeSpi::OnRspQryExercise(CHSExerciseField *pRspQryExercise, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQryExercise && bIsLast == true )
    {
        cout<<"Ӧ�����!"<<endl;
    }
    else
    {
        cout<<"************************��Ȩ��ѯӦ��!*************************"<<endl;
        printf("\t%30s = %35s\r\n","AccountID:",pRspQryExercise->AccountID);
        printf("\t%30s = %35s\r\n","ExerciseOrderSysID:",pRspQryExercise->ExerciseOrderSysID);
        printf("\t%30s = %35d\r\n","SessionID:",pRspQryExercise->SessionID);
        printf("\t%30s = %35s\r\n","ExerciseRef:",pRspQryExercise->ExerciseRef);
        printf("\t%30s = %35s\r\n","ExchangeID:",pRspQryExercise->ExchangeID);
        printf("\t%30s = %35s\r\n","InstrumentID:",pRspQryExercise->InstrumentID);
        printf("\t%30s = %35c\r\n","HedgeType:",pRspQryExercise->HedgeType);
        printf("\t%30s = %35c\r\n","ExerciseType:",pRspQryExercise->ExerciseType);
        printf("\t%30s = %35f\r\n","OrderVolume:",pRspQryExercise->OrderVolume);
        printf("\t%30s = %35c\r\n","OrderStatus:",pRspQryExercise->OrderStatus);
        printf("\t%30s = %35d\r\n","InsertDate:",pRspQryExercise->InsertDate);
        printf("\t%30s = %35d\r\n","InsertTime:",pRspQryExercise->InsertTime);
        printf("\t%30s = %35s\r\n","ErrorMsg:",pRspQryExercise->ErrorMsg);
        printf("\t%30s = %35s\r\n","UnderlyingInstrID:",pRspQryExercise->UnderlyingInstrID);
        printf("\t%30s = %35c\r\n","OrderSource:",pRspQryExercise->OrderSource);
        printf("\t%30s = %35c\r\n","CloseFlag:",pRspQryExercise->CloseFlag);
        printf("\t%30s = %35c\r\n","OffsetFlag:",pRspQryExercise->OffsetFlag);
    }
}
//336856������ѯ
void  CMyTradeSpi::OnRspQryLock(CHSLockField *pRspQryLock, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQryLock && bIsLast == true )
    {
        cout<<"Ӧ�����!"<<endl;
    }
    else
    {
        cout<<"************************������ѯӦ��!*************************"<<endl;
        printf("\t%30s = %35s\r\n","AccountID:",pRspQryLock->AccountID);
        printf("\t%30s = %35s\r\n","LockOrderSysID:",pRspQryLock->LockOrderSysID);
        printf("\t%30s = %35s\r\n","ExchangeID:",pRspQryLock->ExchangeID);
        printf("\t%30s = %35s\r\n","UnderlyingInstrID:",pRspQryLock->UnderlyingInstrID);
        printf("\t%30s = %35c\r\n","LockType:",pRspQryLock->LockType);
        printf("\t%30s = %35f\r\n","OrderVolume:",pRspQryLock->OrderVolume);
        printf("\t%30s = %35c\r\n","OrderStatus:",pRspQryLock->OrderStatus);
        printf("\t%30s = %35d\r\n","TradingDay:",pRspQryLock->TradingDay);
        printf("\t%30s = %35d\r\n","InsertTime:",pRspQryLock->InsertTime);
        printf("\t%30s = %35s\r\n","ErrorMsg:",pRspQryLock->ErrorMsg);
        printf("\t%30s = %35c\r\n","OrderSource:",pRspQryLock->OrderSource);
    }
}
//336857������ϲ�ѯ
void  CMyTradeSpi::OnRspQryCombAction(CHSCombActionField *pRspQryCombAction, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQryCombAction && bIsLast == true )
    {
        cout<<"Ӧ�����!"<<endl;
    }
    else
    {
        cout<<"************************������ϲ�ѯӦ��!*************************"<<endl;
        printf("\t%30s = %35s\r\n","AccountID:",pRspQryCombAction->AccountID);
        printf("\t%30s = %35s\r\n","CombOrderSysID:",pRspQryCombAction->CombOrderSysID);
        printf("\t%30s = %35s\r\n","CombPositionID:",pRspQryCombAction->CombPositionID);
        printf("\t%30s = %35s\r\n","ExchangeID:",pRspQryCombAction->ExchangeID);
        printf("\t%30s = %35s\r\n","InstrumentID:",pRspQryCombAction->InstrumentID);
        printf("\t%30s = %35s\r\n","CombStrategyID:",pRspQryCombAction->CombStrategyID);
        printf("\t%30s = %35c\r\n","Direction:",pRspQryCombAction->Direction);
        printf("\t%30s = %35c\r\n","CombDirection:",pRspQryCombAction->CombDirection);
        printf("\t%30s = %35c\r\n","HedgeType:",pRspQryCombAction->HedgeType);
        printf("\t%30s = %35f\r\n","OrderVolume:",pRspQryCombAction->OrderVolume);
        printf("\t%30s = %35c\r\n","OrderStatus:",pRspQryCombAction->OrderStatus);
        printf("\t%30s = %35d\r\n","TradingDay:",pRspQryCombAction->TradingDay);
        printf("\t%30s = %35d\r\n","InsertDate:",pRspQryCombAction->InsertDate);
        printf("\t%30s = %35d\r\n","InsertTime:",pRspQryCombAction->InsertTime);
        printf("\t%30s = %35s\r\n","ErrorMsg:",pRspQryCombAction->ErrorMsg);
        printf("\t%30s = %35c\r\n","OrderSource:",pRspQryCombAction->OrderSource);
    }
}
//336852��ϳֲ���ϸ��ѯ
void  CMyTradeSpi::OnRspQryPositionCombineDetail(CHSRspQryPositionCombineDetailField *pRspQryPositionCombineDetail, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQryPositionCombineDetail && bIsLast == true )
    {
        cout<<"Ӧ�����!"<<endl;
    }
    else
    {
        cout<<"************************��ϳֲ���ϸ��ѯӦ��!*************************"<<endl;
        printf("\t%30s = %35s\r\n","AccountID:",pRspQryPositionCombineDetail->AccountID);
        printf("\t%30s = %35s\r\n","CombPositionID:",pRspQryPositionCombineDetail->CombPositionID);
        printf("\t%30s = %35s\r\n","ExchangeID:",pRspQryPositionCombineDetail->ExchangeID);
        printf("\t%30s = %35s\r\n","InstrumentID:",pRspQryPositionCombineDetail->InstrumentID);
        printf("\t%30s = %35s\r\n","CombStrategyID:",pRspQryPositionCombineDetail->CombStrategyID);
        printf("\t%30s = %35c\r\n","HedgeType:",pRspQryPositionCombineDetail->HedgeType);
        printf("\t%30s = %35c\r\n","Direction:",pRspQryPositionCombineDetail->Direction);
        printf("\t%30s = %35f\r\n","YdPositionVolume:",pRspQryPositionCombineDetail->YdPositionVolume);
        printf("\t%30s = %35f\r\n","AvailablePositionVolume:",pRspQryPositionCombineDetail->AvailablePositionVolume);
        printf("\t%30s = %35f\r\n","TotalCombVolume:",pRspQryPositionCombineDetail->TotalCombVolume);
        printf("\t%30s = %35f\r\n","TotalSplitVolume:",pRspQryPositionCombineDetail->TotalSplitVolume);
        printf("\t%30s = %35f\r\n","PositionMargin:",pRspQryPositionCombineDetail->PositionMargin);
        printf("\t%30s = %35d\r\n","OpenDate:",pRspQryPositionCombineDetail->OpenDate);
    }
}
//336858��Լ��Ϣ��ѯ
void  CMyTradeSpi::OnRspQryInstrument(CHSRspQryInstrumentField *pRspQryInstrument, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQryInstrument && bIsLast == true )
    {
        cout<<"Ӧ�����!"<<endl;
    }
    else
    {
		//addInfo(pRspQryInstrument->InstrumentID);
		mapStockCode[pRspQryInstrument->InstrumentID] = pRspQryInstrument->ExchangeID;
		//mapStockCode.insert(pRspQryInstrument->InstrumentID, pRspQryInstrument->ExchangeID);

        cout<<"************************��Լ��Ϣ��ѯӦ��!*************************"<<endl;
        printf("\t%30s = %35s\r\n","ExchangeID:",pRspQryInstrument->ExchangeID);
        printf("\t%30s = %35s\r\n","InstrumentID:",pRspQryInstrument->InstrumentID);
        printf("\t%30s = %35s\r\n","InstrumentName:",pRspQryInstrument->InstrumentName);
        printf("\t%30s = %35s\r\n","InstrumentEngName:",pRspQryInstrument->InstrumentEngName);
        printf("\t%30s = %35s\r\n","ProductID:",pRspQryInstrument->ProductID);
        printf("\t%30s = %35c\r\n","ProductType:",pRspQryInstrument->ProductType);
        printf("\t%30s = %35f\r\n","MaxMarketOrderVolume:",pRspQryInstrument->MaxMarketOrderVolume);
        printf("\t%30s = %35f\r\n","MinMarketOrderVolume:",pRspQryInstrument->MinMarketOrderVolume);
        printf("\t%30s = %35f\r\n","MaxLimitOrderVolume:",pRspQryInstrument->MaxLimitOrderVolume);
        printf("\t%30s = %35f\r\n","MinLimitOrderVolume:",pRspQryInstrument->MinLimitOrderVolume);
        printf("\t%30s = %35f\r\n","VolumeMultiple:",pRspQryInstrument->VolumeMultiple);
        printf("\t%30s = %35f\r\n","PriceTick:",pRspQryInstrument->PriceTick);
        printf("\t%30s = %35s\r\n","UnderlyingInstrID:",pRspQryInstrument->UnderlyingInstrID);
        printf("\t%30s = %35f\r\n","ExercisePrice:",pRspQryInstrument->ExercisePrice);
        printf("\t%30s = %35c\r\n","OptionsType:",pRspQryInstrument->OptionsType);
        printf("\t%30s = %35c\r\n","TradingFlag:",pRspQryInstrument->TradingFlag);
        printf("\t%30s = %35d\r\n","MarketDate:",pRspQryInstrument->MarketDate);
        printf("\t%30s = %35d\r\n","ExpireDate:",pRspQryInstrument->ExpireDate);
        printf("\t%30s = %35d\r\n","BeginExerciseDate:",pRspQryInstrument->BeginExerciseDate);
        printf("\t%30s = %35d\r\n","EndExerciseDate:",pRspQryInstrument->EndExerciseDate);
        printf("\t%30s = %35d\r\n","BeginDeliveryDate:",pRspQryInstrument->BeginDeliveryDate);
        printf("\t%30s = %35d\r\n","EndDeliveryDate:",pRspQryInstrument->EndDeliveryDate);
        printf("\t%30s = %35c\r\n","CurrencyID:",pRspQryInstrument->CurrencyID);
        printf("\t%30s = %35c\r\n","CombType:",pRspQryInstrument->CombType);
    }
}
//336910����ȱ�ڲ�ѯ
void  CMyTradeSpi::OnRspQryCoveredShort(CHSRspQryCoveredShortField *pRspQryCoveredShort, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQryCoveredShort && bIsLast == true )
    {
        cout<<"Ӧ�����!"<<endl;
    }
    else
    {
        cout<<"************************����ȱ�ڲ�ѯӦ��!*************************"<<endl;
        printf("\t%30s = %35s\r\n","AccountID:",pRspQryCoveredShort->AccountID);
        printf("\t%30s = %35s\r\n","ExchangeID:",pRspQryCoveredShort->ExchangeID);
        printf("\t%30s = %35s\r\n","UnderlyingInstrID:",pRspQryCoveredShort->UnderlyingInstrID);
        printf("\t%30s = %35f\r\n","CoveredLockVolume:",pRspQryCoveredShort->CoveredLockVolume);
        printf("\t%30s = %35f\r\n","CoveredShortVolume:",pRspQryCoveredShort->CoveredShortVolume);
        printf("\t%30s = %35f\r\n","CoveredEstimateShortVolume:",pRspQryCoveredShort->CoveredEstimateShortVolume);
        printf("\t%30s = %35s\r\n","MsgContent:",pRspQryCoveredShort->MsgContent);
    }
}
//336911��Ȩָ�ɲ�ѯ
void  CMyTradeSpi::OnRspQryExerciseAssign(CHSRspQryExerciseAssignField *pRspQryExerciseAssign, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQryExerciseAssign && bIsLast == true )
    {
        cout<<"Ӧ�����!"<<endl;
    }
    else
    {
        cout<<"************************��Ȩָ�ɲ�ѯӦ��!*************************"<<endl;
        printf("\t%30s = %35s\r\n","AccountID:",pRspQryExerciseAssign->AccountID);
        printf("\t%30s = %35s\r\n","ExchangeID:",pRspQryExerciseAssign->ExchangeID);
        printf("\t%30s = %35s\r\n","UnderlyingInstrID:",pRspQryExerciseAssign->UnderlyingInstrID);
        printf("\t%30s = %35s\r\n","InstrumentID:",pRspQryExerciseAssign->InstrumentID);
        printf("\t%30s = %35c\r\n","PositionType:",pRspQryExerciseAssign->PositionType);
        printf("\t%30s = %35c\r\n","OptionsType:",pRspQryExerciseAssign->OptionsType);
        printf("\t%30s = %35f\r\n","ExercisePrice:",pRspQryExerciseAssign->ExercisePrice);
        printf("\t%30s = %35f\r\n","ExerciseVolume:",pRspQryExerciseAssign->ExerciseVolume);
        printf("\t%30s = %35f\r\n","DeliveryVolume:",pRspQryExerciseAssign->DeliveryVolume);
        printf("\t%30s = %35f\r\n","ExerciseFrozenBalance:",pRspQryExerciseAssign->ExerciseFrozenBalance);
        printf("\t%30s = %35f\r\n","SettlementBalance:",pRspQryExerciseAssign->SettlementBalance);
    }
}
//336900����ת��
void  CMyTradeSpi::OnRspTransfer(CHSRspTransferField *pRspTransfer, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspTransfer && bIsLast == true )
    {
        cout<<"Ӧ�����!"<<endl;
    }
    else
    {
        cout<<"************************����ת��Ӧ��!*************************"<<endl;
        printf("\t%30s = %35d\r\n","TransferSerialID:",pRspTransfer->TransferSerialID);
        printf("\t%30s = %35s\r\n","BankID:",pRspTransfer->BankID);
        printf("\t%30s = %35c\r\n","TransferType:",pRspTransfer->TransferType);
        printf("\t%30s = %35f\r\n","OccurBalance:",pRspTransfer->OccurBalance);
        printf("\t%30s = %35c\r\n","CurrencyID:",pRspTransfer->CurrencyID);
        printf("\t%30s = %35s\r\n","TransferOccasion:",pRspTransfer->TransferOccasion);
    }
}
//336901����ת�˲�ѯ
void  CMyTradeSpi::OnRspQryTransfer(CHSRspQryTransferField *pRspQryTransfer, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQryTransfer && bIsLast == true )
    {
        cout<<"Ӧ�����!"<<endl;
    }
    else
    {
        cout<<"************************����ת�˲�ѯӦ��!*************************"<<endl;
        printf("\t%30s = %35d\r\n","TransferSerialID:",pRspQryTransfer->TransferSerialID);
        printf("\t%30s = %35s\r\n","BankID:",pRspQryTransfer->BankID);
        printf("\t%30s = %35s\r\n","BankName:",pRspQryTransfer->BankName);
        printf("\t%30s = %35s\r\n","BusinessName:",pRspQryTransfer->BusinessName);
        printf("\t%30s = %35f\r\n","OccurBalance:",pRspQryTransfer->OccurBalance);
        printf("\t%30s = %35f\r\n","PostBalance:",pRspQryTransfer->PostBalance);
        printf("\t%30s = %35d\r\n","TransferTime:",pRspQryTransfer->TransferTime);
        printf("\t%30s = %35c\r\n","TransferStatus:",pRspQryTransfer->TransferStatus);
        printf("\t%30s = %35c\r\n","TransferSource:",pRspQryTransfer->TransferSource);
        printf("\t%30s = %35s\r\n","Remarks:",pRspQryTransfer->Remarks);
        printf("\t%30s = %35c\r\n","CurrencyID:",pRspQryTransfer->CurrencyID);
        printf("\t%30s = %35d\r\n","OrderSourceDate:",pRspQryTransfer->OrderSourceDate);
        printf("\t%30s = %35d\r\n","TradingDay:",pRspQryTransfer->TradingDay);
        printf("\t%30s = %35s\r\n","TransferOccasion:",pRspQryTransfer->TransferOccasion);
    }
}
//336902��������ѯ
void  CMyTradeSpi::OnRspQueryBankBalance(CHSRspQueryBankBalanceField *pRspQueryBankBalance, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQueryBankBalance && bIsLast == true )
    {
        cout<<"Ӧ�����!"<<endl;
    }
    else
    {
        cout<<"************************��������ѯӦ��!*************************"<<endl;
        printf("\t%30s = %35d\r\n","TransferSerialID:",pRspQueryBankBalance->TransferSerialID);
    }
}
//336903�����˻���ѯ
void  CMyTradeSpi::OnRspQueryBankAccount(CHSRspQueryBankAccountField *pRspQueryBankAccount, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQueryBankAccount && bIsLast == true )
    {
        cout<<"Ӧ�����!"<<endl;
    }
    else
    {
        cout<<"************************�����˻���ѯӦ��!*************************"<<endl;
        printf("\t%30s = %35s\r\n","BankID:",pRspQueryBankAccount->BankID);
        printf("\t%30s = %35s\r\n","BankName:",pRspQueryBankAccount->BankName);
        printf("\t%30s = %35s\r\n","BankAccountID:",pRspQueryBankAccount->BankAccountID);
        printf("\t%30s = %35c\r\n","CurrencyID:",pRspQueryBankAccount->CurrencyID);
    }
}
//336990�ͻ��˵���ѯ
void  CMyTradeSpi::OnRspQueryBillContent(CHSRspQueryBillContentField *pRspQueryBillContent, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQueryBillContent && bIsLast == true )
    {
        cout<<"Ӧ�����!"<<endl;
    }
    else
    {
        cout<<"************************�ͻ��˵���ѯӦ��!*************************"<<endl;
        printf("\t%30s = %35s\r\n","BillContent:",pRspQueryBillContent->BillContent);
    }
}
//336991�ͻ��˵�ȷ��
void  CMyTradeSpi::OnRspBillConfirm(CHSRspBillConfirmField *pRspBillConfirm, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspBillConfirm && bIsLast == true )
    {
        cout<<"Ӧ�����!"<<endl;
    }
    else
    {
        cout<<"************************�ͻ��˵�ȷ��Ӧ��!*************************"<<endl;
        printf("\t%30s = %35s\r\n","AccountID:",pRspBillConfirm->AccountID);
        printf("\t%30s = %35c\r\n","BillConfirmStatus:",pRspBillConfirm->BillConfirmStatus);
        printf("\t%30s = %35d\r\n","ConfirmDate:",pRspBillConfirm->ConfirmDate);
        printf("\t%30s = %35d\r\n","ConfirmTime:",pRspBillConfirm->ConfirmTime);
    }
}
//336860��֤���ѯ
void  CMyTradeSpi::OnRspQryMargin(CHSRspQryMarginField *pRspQryMargin, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQryMargin && bIsLast == true )
    {
        cout<<"Ӧ�����!"<<endl;
    }
    else
    {
        cout<<"************************��֤���ѯӦ��!*************************"<<endl;
        printf("\t%30s = %35s\r\n","AccountID:",pRspQryMargin->AccountID);
        printf("\t%30s = %35s\r\n","ExchangeID:",pRspQryMargin->ExchangeID);
        printf("\t%30s = %35s\r\n","InstrumentID:",pRspQryMargin->InstrumentID);
        printf("\t%30s = %35s\r\n","UnderlyingInstrID:",pRspQryMargin->UnderlyingInstrID);
        printf("\t%30s = %35c\r\n","HedgeType:",pRspQryMargin->HedgeType);
        printf("\t%30s = %35f\r\n","LongMarginRatio:",pRspQryMargin->LongMarginRatio);
        printf("\t%30s = %35f\r\n","LongMargin:",pRspQryMargin->LongMargin);
        printf("\t%30s = %35f\r\n","ShortMarginRatio:",pRspQryMargin->ShortMarginRatio);
        printf("\t%30s = %35f\r\n","ShortMargin:",pRspQryMargin->ShortMargin);
    }
}
//336861�����Ѳ�ѯ
void  CMyTradeSpi::OnRspQryCommission(CHSRspQryCommissionField *pRspQryCommission, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQryCommission && bIsLast == true )
    {
        cout<<"Ӧ�����!"<<endl;
    }
    else
    {
        cout<<"************************�����Ѳ�ѯӦ��!*************************"<<endl;
        printf("\t%30s = %35s\r\n","AccountID:",pRspQryCommission->AccountID);
        printf("\t%30s = %35s\r\n","ExchangeID:",pRspQryCommission->ExchangeID);
        printf("\t%30s = %35c\r\n","ProductType:",pRspQryCommission->ProductType);
        printf("\t%30s = %35s\r\n","InstrumentID:",pRspQryCommission->InstrumentID);
        printf("\t%30s = %35s\r\n","UnderlyingInstrID:",pRspQryCommission->UnderlyingInstrID);
        printf("\t%30s = %35f\r\n","LongOpenCommissionRatio:",pRspQryCommission->LongOpenCommissionRatio);
        printf("\t%30s = %35f\r\n","LongOpenCommission:",pRspQryCommission->LongOpenCommission);
        printf("\t%30s = %35f\r\n","LongCloseCommissionRatio:",pRspQryCommission->LongCloseCommissionRatio);
        printf("\t%30s = %35f\r\n","LongCloseCommission:",pRspQryCommission->LongCloseCommission);
        printf("\t%30s = %35f\r\n","LongCloseTodayCommissionRatio:",pRspQryCommission->LongCloseTodayCommissionRatio);
        printf("\t%30s = %35f\r\n","LongCloseTodayCommission:",pRspQryCommission->LongCloseTodayCommission);
        printf("\t%30s = %35f\r\n","ShortOpenCommissionRatio:",pRspQryCommission->ShortOpenCommissionRatio);
        printf("\t%30s = %35f\r\n","ShortOpenCommission:",pRspQryCommission->ShortOpenCommission);
        printf("\t%30s = %35f\r\n","ShortCloseCommissionRatio:",pRspQryCommission->ShortCloseCommissionRatio);
        printf("\t%30s = %35f\r\n","ShortCloseCommission:",pRspQryCommission->ShortCloseCommission);
        printf("\t%30s = %35f\r\n","ShortCloseTodayCommissionRatio:",pRspQryCommission->ShortCloseTodayCommissionRatio);
        printf("\t%30s = %35f\r\n","ShortCloseTodayCommission:",pRspQryCommission->ShortCloseTodayCommission);
        printf("\t%30s = %35f\r\n","ExerciseCommissionRatio:",pRspQryCommission->ExerciseCommissionRatio);
        printf("\t%30s = %35f\r\n","ExerciseCommission:",pRspQryCommission->ExerciseCommission);
        printf("\t%30s = %35f\r\n","TradeValueRatio:",pRspQryCommission->TradeValueRatio);
        printf("\t%30s = %35f\r\n","StockValue:",pRspQryCommission->StockValue);
    }
}
//336865���ʲ�ѯ
void  CMyTradeSpi::OnRspQryExchangeRate(CHSRspQryExchangeRateField *pRspQryExchangeRate, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQryExchangeRate && bIsLast == true )
    {
        cout<<"Ӧ�����!"<<endl;
    }
    else
    {
        cout<<"************************���ʲ�ѯӦ��!*************************"<<endl;
        printf("\t%30s = %35c\r\n","FromCurrencyID:",pRspQryExchangeRate->FromCurrencyID);
        printf("\t%30s = %35c\r\n","ToCurrencyID:",pRspQryExchangeRate->ToCurrencyID);
        printf("\t%30s = %35f\r\n","ExchangeRate:",pRspQryExchangeRate->ExchangeRate);
        printf("\t%30s = %35f\r\n","FromCurrencyUnit:",pRspQryExchangeRate->FromCurrencyUnit);
    }
}
//336863�ֲ���ϸ��ѯ
void  CMyTradeSpi::OnRspQryPositionDetail(CHSRspQryPositionDetailField *pRspQryPositionDetail, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQryPositionDetail && bIsLast == true )
    {
        cout<<"Ӧ�����!"<<endl;
    }
    else
    {
        cout<<"************************�ֲ���ϸ��ѯӦ��!*************************"<<endl;
        printf("\t%30s = %35s\r\n","AccountID:",pRspQryPositionDetail->AccountID);
        printf("\t%30s = %35s\r\n","TradeID:",pRspQryPositionDetail->TradeID);
        printf("\t%30s = %35d\r\n","OpenDate:",pRspQryPositionDetail->OpenDate);
        printf("\t%30s = %35s\r\n","ExchangeID:",pRspQryPositionDetail->ExchangeID);
        printf("\t%30s = %35s\r\n","InstrumentID:",pRspQryPositionDetail->InstrumentID);
        printf("\t%30s = %35c\r\n","Direction:",pRspQryPositionDetail->Direction);
        printf("\t%30s = %35c\r\n","HedgeType:",pRspQryPositionDetail->HedgeType);
        printf("\t%30s = %35f\r\n","TradeVolume:",pRspQryPositionDetail->TradeVolume);
        printf("\t%30s = %35f\r\n","PositionPrice:",pRspQryPositionDetail->PositionPrice);
        printf("\t%30s = %35f\r\n","TodayCloseVolume:",pRspQryPositionDetail->TodayCloseVolume);
        printf("\t%30s = %35s\r\n","ArbitragePositionID:",pRspQryPositionDetail->ArbitragePositionID);
        printf("\t%30s = %35f\r\n","LegID:",pRspQryPositionDetail->LegID);
        printf("\t%30s = %35c\r\n","TradeType:",pRspQryPositionDetail->TradeType);
        printf("\t%30s = %35f\r\n","PositionMargin:",pRspQryPositionDetail->PositionMargin);
        printf("\t%30s = %35s\r\n","CombInstrumentID:",pRspQryPositionDetail->CombInstrumentID);
    }
}
//336862���͹�˾���ò�����ѯ
void  CMyTradeSpi::OnRspQrySysConfig(CHSRspQrySysConfigField *pRspQrySysConfig, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQrySysConfig && bIsLast == true )
    {
        cout<<"Ӧ�����!"<<endl;
    }
    else
    {
        cout<<"************************���͹�˾���ò�����ѯӦ��!*************************"<<endl;
        printf("\t%30s = %35f\r\n","ConfigNo:",pRspQrySysConfig->ConfigNo);
        printf("\t%30s = %35s\r\n","ConfigValue:",pRspQrySysConfig->ConfigValue);
    }
}
//336864�����ѯ
void  CMyTradeSpi::OnRspQryDepthMarketData(CHSDepthMarketDataField *pRspQryDepthMarketData, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (IsErrorRspInfo(pRspInfo))
	{
		return;
	}
	if(! pRspQryDepthMarketData && bIsLast == true )
	{
		cout<<"Ӧ�����!"<<endl;
	}
	else
	{
		cout<<"************************�����ѯӦ��!*************************"<<endl;
		printf("\t%30s = %35d\r\n","TradingDay:",pRspQryDepthMarketData->TradingDay);
		printf("\t%30s = %35s\r\n","InstrumentID:",pRspQryDepthMarketData->InstrumentID);
		printf("\t%30s = %35s\r\n","ExchangeID:",pRspQryDepthMarketData->ExchangeID);
		printf("\t%30s = %35f\r\n","LastPrice:",pRspQryDepthMarketData->LastPrice);
		printf("\t%30s = %35f\r\n","PreSettlementPrice:",pRspQryDepthMarketData->PreSettlementPrice);
		printf("\t%30s = %35f\r\n","PreClosePrice:",pRspQryDepthMarketData->PreClosePrice);
		printf("\t%30s = %35f\r\n","OpenPrice:",pRspQryDepthMarketData->OpenPrice);
		printf("\t%30s = %35f\r\n","HighestPrice:",pRspQryDepthMarketData->HighestPrice);
		printf("\t%30s = %35f\r\n","LowestPrice:",pRspQryDepthMarketData->LowestPrice);
		printf("\t%30s = %35f\r\n","TradeVolume:",pRspQryDepthMarketData->TradeVolume);
		printf("\t%30s = %35f\r\n","TradeBalance:",pRspQryDepthMarketData->TradeBalance);
		printf("\t%30s = %35f\r\n","OpenInterest:",pRspQryDepthMarketData->OpenInterest);
		printf("\t%30s = %35f\r\n","ClosePrice:",pRspQryDepthMarketData->ClosePrice);
		printf("\t%30s = %35f\r\n","SettlementPrice:",pRspQryDepthMarketData->SettlementPrice);
		printf("\t%30s = %35f\r\n","UpperLimitPrice:",pRspQryDepthMarketData->UpperLimitPrice);
		printf("\t%30s = %35f\r\n","LowerLimitPrice:",pRspQryDepthMarketData->LowerLimitPrice);
		printf("\t%30s = %35f\r\n","PreDelta:",pRspQryDepthMarketData->PreDelta);
		printf("\t%30s = %35f\r\n","CurrDelta:",pRspQryDepthMarketData->CurrDelta);
		printf("\t%30s = %35d\r\n","UpdateTime:",pRspQryDepthMarketData->UpdateTime);
		printf("\t%30s = %35f\r\n","BidPrice1:",pRspQryDepthMarketData->BidPrice1);
		printf("\t%30s = %35f\r\n","BidVolume1:",pRspQryDepthMarketData->BidVolume1);
		printf("\t%30s = %35f\r\n","AskPrice1:",pRspQryDepthMarketData->AskPrice1);
		printf("\t%30s = %35f\r\n","AskVolume1:",pRspQryDepthMarketData->AskVolume1);
		printf("\t%30s = %35f\r\n","BidPrice2:",pRspQryDepthMarketData->BidPrice2);
		printf("\t%30s = %35f\r\n","BidVolume2:",pRspQryDepthMarketData->BidVolume2);
		printf("\t%30s = %35f\r\n","AskPrice2:",pRspQryDepthMarketData->AskPrice2);
		printf("\t%30s = %35f\r\n","AskVolume2:",pRspQryDepthMarketData->AskVolume2);
		printf("\t%30s = %35f\r\n","BidPrice3:",pRspQryDepthMarketData->BidPrice3);
		printf("\t%30s = %35f\r\n","BidVolume3:",pRspQryDepthMarketData->BidVolume3);
		printf("\t%30s = %35f\r\n","AskPrice3:",pRspQryDepthMarketData->AskPrice3);
		printf("\t%30s = %35f\r\n","AskVolume3:",pRspQryDepthMarketData->AskVolume3);
		printf("\t%30s = %35f\r\n","BidPrice4:",pRspQryDepthMarketData->BidPrice4);
		printf("\t%30s = %35f\r\n","BidVolume4:",pRspQryDepthMarketData->BidVolume4);
		printf("\t%30s = %35f\r\n","AskPrice4:",pRspQryDepthMarketData->AskPrice4);
		printf("\t%30s = %35f\r\n","AskVolume4:",pRspQryDepthMarketData->AskVolume4);
		printf("\t%30s = %35f\r\n","BidPrice5:",pRspQryDepthMarketData->BidPrice5);
		printf("\t%30s = %35f\r\n","BidVolume5:",pRspQryDepthMarketData->BidVolume5);
		printf("\t%30s = %35f\r\n","AskPrice5:",pRspQryDepthMarketData->AskPrice5);
		printf("\t%30s = %35f\r\n","AskVolume5:",pRspQryDepthMarketData->AskVolume5);
		printf("\t%30s = %35f\r\n","AveragePrice:",pRspQryDepthMarketData->AveragePrice);
		printf("\t%30s = %35f\r\n","PreOpenInterest:",pRspQryDepthMarketData->PreOpenInterest);
		printf("\t%30s = %35c\r\n","InstrumentTradeStatus:",pRspQryDepthMarketData->InstrumentTradeStatus);
		printf("\t%30s = %35s\r\n","OpenRestriction:",pRspQryDepthMarketData->OpenRestriction);
	}
}


CString getStatus(HSOrderStatus os) {
	CString str;
	switch (os)
	{
	case HS_OS_NotReported:str = "δ��"; break;
	case HS_OS_ToBeReported:str = "����"; break;
	case HS_OS_Reported:str = "�ѱ�"; break;
	case HS_OS_ReportedToBeCancel:str = "�ѱ�����"; break;
	case HS_OS_PartsTradedToBeCancel:str = "���ɴ���"; break;
	case HS_OS_CanceledWithPartsTraded:str = "����"; break;

	case HS_OS_Canceled:str = "�ѳ�"; break;
	case HS_OS_PartsTraded:str = "����"; break;
	case HS_OS_Traded:str = "�ѳ�"; break;
	case HS_OS_Abandoned:str = "�ϵ�"; break;
	case HS_OS_CancelFailed:str = "����"; break;
	case HS_OS_Confirmed:str = "��ȷ�ϣ�ѯ������"; break;
	case HS_OS_ToBeConfirmed:str = "��ȷ��"; break;



	default:
		break;
	}
	return str;
}

/// Description: ����-�ɽ��ر�
void CMyTradeSpi::OnRtnTrade(CHSTradeField *pRtnTrade)
{
	CString str;
	str.Format("�ɽ��ر�[id=%s, �ɽ�����=[%.0f] ]", pRtnTrade->OrderRef, pRtnTrade->TradeVolume);
	addInfo(str);

	cout<<"**************************�յ��ɽ��ر����ݣ�**************************"<<endl;
	printf("\t%30s = %35s\r\n","AccountID:",pRtnTrade->AccountID);
	printf("\t%30s = %35s\r\n","TradeID:",pRtnTrade->TradeID);
	printf("\t%30s = %35s\r\n","OrderSysID:",pRtnTrade->OrderSysID);
	printf("\t%30s = %35s\r\n","BrokerOrderID:",pRtnTrade->BrokerOrderID);
	printf("\t%30s = %35d\r\n","SessionID:",pRtnTrade->SessionID);
	printf("\t%30s = %35s\r\n","OrderRef:",pRtnTrade->OrderRef);
	printf("\t%30s = %35s\r\n","ExchangeID:",pRtnTrade->ExchangeID);
	printf("\t%30s = %35s\r\n","InstrumentID:",pRtnTrade->InstrumentID);
	printf("\t%30s = %35c\r\n","Direction:",pRtnTrade->Direction);
	printf("\t%30s = %35c\r\n","OffsetFlag:",pRtnTrade->OffsetFlag);
	printf("\t%30s = %35c\r\n","HedgeType:",pRtnTrade->HedgeType);
	printf("\t%30s = %35f\r\n","TradeVolume:",pRtnTrade->TradeVolume);
	printf("\t%30s = %35f\r\n","TradePrice:",pRtnTrade->TradePrice);
	printf("\t%30s = %35d\r\n","TradingDay:",pRtnTrade->TradingDay);
	printf("\t%30s = %35d\r\n","TradeTime:",pRtnTrade->TradeTime);
	printf("\t%30s = %35s\r\n","UnderlyingInstrID:",pRtnTrade->UnderlyingInstrID);
}



/// Description: ����-�����ر�
void CMyTradeSpi::OnRtnOrder(CHSOrderField *pRtnOrder) 
{
	CString str;
	str.Format("ί�лر�[id=%s, ί��״̬=[%s], ��Ϣ=[%s] ]", pRtnOrder->OrderRef,getStatus(pRtnOrder->OrderStatus), pRtnOrder->ErrorMsg);
	addInfo(str);

	cout<<"***********************�յ������ر����ݣ�*********************"<<endl;
	printf("\t%30s = %35s\r\n","AccountID:",pRtnOrder->AccountID);
	printf("\t%30s = %35s\r\n","OrderSysID:",pRtnOrder->OrderSysID);
	printf("\t%30s = %35s\r\n","BrokerOrderID:",pRtnOrder->BrokerOrderID);
	printf("\t%30s = %35d\r\n","SessionID:",pRtnOrder->SessionID);
	printf("\t%30s = %35s\r\n","OrderRef:",pRtnOrder->OrderRef);
	printf("\t%30s = %35s\r\n","ExchangeID:",pRtnOrder->ExchangeID);
	printf("\t%30s = %35s\r\n","InstrumentID:",pRtnOrder->InstrumentID);
	printf("\t%30s = %35c\r\n","Direction:",pRtnOrder->Direction);
	printf("\t%30s = %35c\r\n","OffsetFlag:",pRtnOrder->OffsetFlag);
	printf("\t%30s = %35c\r\n","HedgeType:",pRtnOrder->HedgeType);
	printf("\t%30s = %35f\r\n","OrderPrice:",pRtnOrder->OrderPrice);
	printf("\t%30s = %35f\r\n","OrderVolume:",pRtnOrder->OrderVolume);
	printf("\t%30s = %35c\r\n","OrderStatus:",pRtnOrder->OrderStatus);
	printf("\t%30s = %35f\r\n","TradeVolume:",pRtnOrder->TradeVolume);
	printf("\t%30s = %35f\r\n","CancelVolume:",pRtnOrder->CancelVolume);
	printf("\t%30s = %35f\r\n","TradePrice:",pRtnOrder->TradePrice);
	printf("\t%30s = %35d\r\n","TradingDay:",pRtnOrder->TradingDay);
	printf("\t%30s = %35d\r\n","InsertDate:", pRtnOrder->InsertDate);
	printf("\t%30s = %35d\r\n","InsertTime:",pRtnOrder->InsertTime);
	printf("\t%30s = %35d\r\n","ReportTime:",pRtnOrder->ReportTime);
	printf("\t%30s = %35s\r\n","OrderCommand:",pRtnOrder->OrderCommand);
	printf("\t%30s = %35f\r\n","MinVolume:",pRtnOrder->MinVolume);
	printf("\t%30s = %35f\r\n","SpringPrice:",pRtnOrder->SpringPrice);
	printf("\t%30s = %35c\r\n","SwapOrderFlag:",pRtnOrder->SwapOrderFlag);
	printf("\t%30s = %35c\r\n","ForceCloseReason:",pRtnOrder->ForceCloseReason);
	printf("\t%30s = %35s\r\n","ErrorMsg:",pRtnOrder->ErrorMsg);
	printf("\t%30s = %35s\r\n","UnderlyingInstrID:",pRtnOrder->UnderlyingInstrID);
	printf("\t%30s = %35c\r\n","OrderSource:",pRtnOrder->OrderSource);
}

/// Description: ����-��Ȩ
void CMyTradeSpi::OnRtnExercise(CHSExerciseField *pRtnExercise) 
{
	cout<<"************************�յ���Ȩ�������ݣ�**************************"<<endl;
	printf("\t%30s = %35s\r\n","AccountID:",pRtnExercise->AccountID);
	printf("\t%30s = %35s\r\n","ExerciseOrderSysID:",pRtnExercise->ExerciseOrderSysID);
	printf("\t%30s = %35d\r\n","SessionID:",pRtnExercise->SessionID);
	printf("\t%30s = %35s\r\n","ExerciseRef:",pRtnExercise->ExerciseRef);
	printf("\t%30s = %35s\r\n","ExchangeID:",pRtnExercise->ExchangeID);
	printf("\t%30s = %35s\r\n","InstrumentID:",pRtnExercise->InstrumentID);
	printf("\t%30s = %35c\r\n","HedgeType:",pRtnExercise->HedgeType);
	printf("\t%30s = %35c\r\n","ExerciseType:",pRtnExercise->ExerciseType);
	printf("\t%30s = %35f\r\n","OrderVolume:",pRtnExercise->OrderVolume);
	printf("\t%30s = %35c\r\n","OrderStatus:",pRtnExercise->OrderStatus);
	printf("\t%30s = %35d\r\n","InsertDate:",pRtnExercise->InsertDate);
	printf("\t%30s = %35d\r\n","InsertTime:",pRtnExercise->InsertTime);
	printf("\t%30s = %35s\r\n","ErrorMsg:",pRtnExercise->ErrorMsg);
	printf("\t%30s = %35s\r\n","UnderlyingInstrID:",pRtnExercise->UnderlyingInstrID);
	printf("\t%30s = %35c\r\n","OrderSource:",pRtnExercise->OrderSource);
}

/// Description: ����-�������
void CMyTradeSpi::OnRtnCombAction(CHSCombActionField *pRtnCombAction) 
{
	cout<<"**********************�յ���������������ݣ�*********************"<<endl;
	printf("\t%30s = %35s\r\n","AccountID:",pRtnCombAction->AccountID);
	printf("\t%30s = %35s\r\n","CombOrderSysID:",pRtnCombAction->CombOrderSysID);
	printf("\t%30s = %35s\r\n","CombPositionID:",pRtnCombAction->CombPositionID);
	printf("\t%30s = %35s\r\n","ExchangeID:",pRtnCombAction->ExchangeID);
	printf("\t%30s = %35s\r\n","InstrumentID:",pRtnCombAction->InstrumentID);
	printf("\t%30s = %35s\r\n","CombStrategyID:",pRtnCombAction->CombStrategyID);
	printf("\t%30s = %35c\r\n","Direction:",pRtnCombAction->Direction);
	printf("\t%30s = %35c\r\n","CombDirection:",pRtnCombAction->CombDirection);
	printf("\t%30s = %35c\r\n","HedgeType:",pRtnCombAction->HedgeType);
	printf("\t%30s = %35f\r\n","OrderVolume:",pRtnCombAction->OrderVolume);
	printf("\t%30s = %35c\r\n","OrderStatus:",pRtnCombAction->OrderStatus);
	printf("\t%30s = %35d\r\n","TradingDay:",pRtnCombAction->TradingDay);
	printf("\t%30s = %35d\r\n","InsertDate:",pRtnCombAction->InsertDate);
	printf("\t%30s = %35d\r\n","InsertTime:",pRtnCombAction->InsertTime);
	printf("\t%30s = %35s\r\n","ErrorMsg:",pRtnCombAction->ErrorMsg);
	printf("\t%30s = %35c\r\n","OrderSource:",pRtnCombAction->OrderSource);
}

/// Description: ����-����
void CMyTradeSpi::OnRtnLock(CHSLockField *pRtnLock) 
{
	cout<<"**********************�յ������������ݣ�***********************"<<endl;
	printf("\t%30s = %35s\r\n","AccountID:",pRtnLock->AccountID);
	printf("\t%30s = %35s\r\n","LockOrderSysID:",pRtnLock->LockOrderSysID);
	printf("\t%30s = %35s\r\n","ExchangeID:",pRtnLock->ExchangeID);
	printf("\t%30s = %35s\r\n","UnderlyingInstrID:",pRtnLock->UnderlyingInstrID);
	printf("\t%30s = %35c\r\n","LockType:",pRtnLock->LockType);
	printf("\t%30s = %35f\r\n","OrderVolume:",pRtnLock->OrderVolume);
	printf("\t%30s = %35c\r\n","OrderStatus:",pRtnLock->OrderStatus);
	printf("\t%30s = %35d\r\n","TradingDay:",pRtnLock->TradingDay);
	printf("\t%30s = %35d\r\n","InsertTime:",pRtnLock->InsertTime);
	printf("\t%30s = %35s\r\n","ErrorMsg:",pRtnLock->ErrorMsg);
	printf("\t%30s = %35c\r\n","OrderSource:",pRtnLock->OrderSource);
}