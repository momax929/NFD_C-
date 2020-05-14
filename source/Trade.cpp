#include "stdafx.h"
#include "Trade.h"

//int _orderRef = 0;

bool CMyTradeSpi::IsErrorRspInfo(CHSRspInfoField *pRspInfo)
{
	bool ret = ((pRspInfo) && (pRspInfo->ErrorID != 0));
	if (ret)
	{
		CString str;
		str.Format("请求失败！error_no=[%d] error_info=[%s]", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
	}
	return ret;
}

void  CMyTradeSpi::OnFrontConnected()
{
	/* 当连接建立成功后，在这里启动子线程 */
	addInfo("交易连接成功\r\n");
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
		cerr<<"[1]客户登录                                  "<<endl;
		cerr<<"[2]密码更改                                  "<<endl;
		cerr<<"[3]报单录入                                  "<<endl;
		cerr<<"[4]撤单                                      "<<endl;
		cerr<<"[5]行权录入                                  "<<endl;
		cerr<<"[6]行权撤单                                  "<<endl;
		cerr<<"[7]锁定录入                                  "<<endl;
		cerr<<"[8]询价录入                                  "<<endl;
		cerr<<"[9]申请组合录入                              "<<endl;
		cerr<<"[10]最大报单数量获取                         "<<endl;
		cerr<<"[11]可锁定数量获取                           "<<endl;
		cerr<<"[12]可行权数量获取                           "<<endl;
		cerr<<"[13]持仓汇总查询                             "<<endl;
		cerr<<"[14]资金账户查询                             "<<endl;
		cerr<<"[15]报单查询                                 "<<endl;
		cerr<<"[16]成交查询                                 "<<endl;
		cerr<<"[17]行权查询                                 "<<endl;
		cerr<<"[18]锁定查询                                 "<<endl;
		cerr<<"[19]申请组合查询                             "<<endl;
		cerr<<"[20]组合持仓明细查询                         "<<endl;
		cerr<<"[21]合约信息查询                             "<<endl;
		cerr<<"[22]备兑缺口查询                             "<<endl;
		cerr<<"[23]行权指派查询                             "<<endl;
		cerr<<"[24]银行转账                                 "<<endl;
		cerr<<"[25]银行转账查询                             "<<endl;
		cerr<<"[26]银行余额查询                             "<<endl;
		cerr<<"[27]银行账户查询                             "<<endl;
		cerr<<"[28]客户账单查询                             "<<endl;
		cerr<<"[29]客户账单确认                             "<<endl;
		cerr<<"[30]保证金查询                               "<<endl;
		cerr<<"[31]手续费查询                               "<<endl;
		cerr<<"[32]持仓明细查询                             "<<endl;
		cerr<<"[33]经纪公司配置参数查询                     "<<endl;
		cerr<<"[34]行情查询                                 "<<endl;
		cerr<<"[35]汇率查询                                 "<<endl;
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
					printf("Please input AccountID （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqUserLogin.AccountID,"" );
					else
						hs_strncpy(stHSReqUserLogin.AccountID,szTemp,sizeof(stHSReqUserLogin.AccountID));
					printf("Please input Password （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqUserLogin.Password,"" );
					else
						hs_strncpy(stHSReqUserLogin.Password,szTemp,sizeof(stHSReqUserLogin.Password));
					printf("Please input UserApplicationType（若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						stHSReqUserLogin.UserApplicationType = '\0';
					else
						stHSReqUserLogin.UserApplicationType = szTemp[0];
					printf("Please input UserApplicationInfo （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqUserLogin.UserApplicationInfo,"" );
					else
						hs_strncpy(stHSReqUserLogin.UserApplicationInfo,szTemp,sizeof(stHSReqUserLogin.UserApplicationInfo));
					printf("Please input MacAddress （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqUserLogin.MacAddress,"" );
					else
						hs_strncpy(stHSReqUserLogin.MacAddress,szTemp,sizeof(stHSReqUserLogin.MacAddress));
					printf("Please input IPAddress （若想传空直接回车【Enter】）:");
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
					printf("Please input PasswordType（若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						stHSReqUserPasswordUpdate.PasswordType = '\0';
					else
						stHSReqUserPasswordUpdate.PasswordType = szTemp[0];
					printf("Please input Password （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqUserPasswordUpdate.Password,"" );
					else
						hs_strncpy(stHSReqUserPasswordUpdate.Password,szTemp,sizeof(stHSReqUserPasswordUpdate.Password));
					hs_strncpy(pswd,stHSReqUserPasswordUpdate.Password,sizeof(pswd));
					printf("Please input NewPassword （若想传空直接回车【Enter】）:");
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
					printf("Please input OrderRef （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqOrderInsert.OrderRef,"" );
					else
						hs_strncpy(stHSReqOrderInsert.OrderRef,szTemp,sizeof(stHSReqOrderInsert.OrderRef));
					printf("Please input ExchangeID （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqOrderInsert.ExchangeID,"" );
					else
						hs_strncpy(stHSReqOrderInsert.ExchangeID,szTemp,sizeof(stHSReqOrderInsert.ExchangeID));
					printf("Please input InstrumentID （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqOrderInsert.InstrumentID,"" );
					else
						hs_strncpy(stHSReqOrderInsert.InstrumentID,szTemp,sizeof(stHSReqOrderInsert.InstrumentID));
					printf("Please input Direction（若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						stHSReqOrderInsert.Direction = '\0';
					else
						stHSReqOrderInsert.Direction = szTemp[0];
					printf("Please input OffsetFlag（若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						stHSReqOrderInsert.OffsetFlag = '\0';
					else
						stHSReqOrderInsert.OffsetFlag = szTemp[0];
					printf("Please input HedgeType（若想传空直接回车【Enter】）:");
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
					printf("Please input OrderCommand（若想传空直接回车【Enter】）:");
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
					printf("Please input SwapOrderFlag（若想传空直接回车【Enter】）:");
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
					printf("Please input OrderSysID （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqOrderAction.OrderSysID,"" );
					else
						hs_strncpy(stHSReqOrderAction.OrderSysID,szTemp,sizeof(stHSReqOrderAction.OrderSysID));
					printf("Please input ExchangeID （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqOrderAction.ExchangeID,"" );
					else
						hs_strncpy(stHSReqOrderAction.ExchangeID,szTemp,sizeof(stHSReqOrderAction.ExchangeID));
					printf("Please input SessionID （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					stHSReqOrderAction.SessionID = atoi(szTemp);
					printf("Please input OrderRef （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqOrderAction.OrderRef,"" );
					else
						hs_strncpy(stHSReqOrderAction.OrderRef,szTemp,sizeof(stHSReqOrderAction.OrderRef));
					printf("Please input OrderActionRef （若想传空直接回车【Enter】）:");
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
					printf("Please input ExerciseRef （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqExerciseOrderInsert.ExerciseRef,"" );
					else
						hs_strncpy(stHSReqExerciseOrderInsert.ExerciseRef,szTemp,sizeof(stHSReqExerciseOrderInsert.ExerciseRef));
					printf("Please input ExchangeID （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqExerciseOrderInsert.ExchangeID,"" );
					else
						hs_strncpy(stHSReqExerciseOrderInsert.ExchangeID,szTemp,sizeof(stHSReqExerciseOrderInsert.ExchangeID));
					printf("Please input InstrumentID （若想传空直接回车【Enter】）:");
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
					printf("Please input ExerciseType（若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						stHSReqExerciseOrderInsert.ExerciseType = '\0';
					else
						stHSReqExerciseOrderInsert.ExerciseType = szTemp[0];
					printf("Please input HedgeType（若想传空直接回车【Enter】）:");
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
					printf("Please input ExchangeID （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqExerciseOrderAction.ExchangeID,"" );
					else
						hs_strncpy(stHSReqExerciseOrderAction.ExchangeID,szTemp,sizeof(stHSReqExerciseOrderAction.ExchangeID));
					printf("Please input ExerciseOrderSysID （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqExerciseOrderAction.ExerciseOrderSysID,"" );
					else
						hs_strncpy(stHSReqExerciseOrderAction.ExerciseOrderSysID,szTemp,sizeof(stHSReqExerciseOrderAction.ExerciseOrderSysID));
					printf("Please input ExerciseRef （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqExerciseOrderAction.ExerciseRef,"" );
					else
						hs_strncpy(stHSReqExerciseOrderAction.ExerciseRef,szTemp,sizeof(stHSReqExerciseOrderAction.ExerciseRef));
					printf("Please input SessionID （若想传空直接回车【Enter】）:");
					cin.ignore();
					cin.get(szTemp,260,'\n');
					stHSReqExerciseOrderAction.SessionID = atoi(szTemp);
					printf("Please input ExecOrderActionRef （若想传空直接回车【Enter】）:");
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
					printf("Please input ExchangeID （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqLockInsert.ExchangeID,"" );
					else
						hs_strncpy(stHSReqLockInsert.ExchangeID,szTemp,sizeof(stHSReqLockInsert.ExchangeID));
					printf("Please input UnderlyingInstrID （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqLockInsert.UnderlyingInstrID,"" );
					else
						hs_strncpy(stHSReqLockInsert.UnderlyingInstrID,szTemp,sizeof(stHSReqLockInsert.UnderlyingInstrID));
					printf("Please input LockType（若想传空直接回车【Enter】）:");
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
					printf("Please input ExchangeID （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqForQuoteInsert.ExchangeID,"" );
					else
						hs_strncpy(stHSReqForQuoteInsert.ExchangeID,szTemp,sizeof(stHSReqForQuoteInsert.ExchangeID));
					printf("Please input InstrumentID （若想传空直接回车【Enter】）:");
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
					printf("Please input ExchangeID （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqCombActionInsert.ExchangeID,"" );
					else
						hs_strncpy(stHSReqCombActionInsert.ExchangeID,szTemp,sizeof(stHSReqCombActionInsert.ExchangeID));
					printf("Please input InstrumentID （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqCombActionInsert.InstrumentID,"" );
					else
						hs_strncpy(stHSReqCombActionInsert.InstrumentID,szTemp,sizeof(stHSReqCombActionInsert.InstrumentID));
					printf("Please input CombStrategyID （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqCombActionInsert.CombStrategyID,"" );
					else
						hs_strncpy(stHSReqCombActionInsert.CombStrategyID,szTemp,sizeof(stHSReqCombActionInsert.CombStrategyID));
					printf("Please input CombPositionID （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqCombActionInsert.CombPositionID,"" );
					else
						hs_strncpy(stHSReqCombActionInsert.CombPositionID,szTemp,sizeof(stHSReqCombActionInsert.CombPositionID));
					printf("Please input CombDirection（若想传空直接回车【Enter】）:");
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
					printf("Please input HedgeType（若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						stHSReqCombActionInsert.HedgeType = '\0';
					else
						stHSReqCombActionInsert.HedgeType = szTemp[0];
					printf("Please input Direction（若想传空直接回车【Enter】）:");
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
					printf("Please input ExchangeID （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQueryMaxOrderVolume.ExchangeID,"" );
					else
						hs_strncpy(stHSReqQueryMaxOrderVolume.ExchangeID,szTemp,sizeof(stHSReqQueryMaxOrderVolume.ExchangeID));
					printf("Please input InstrumentID （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQueryMaxOrderVolume.InstrumentID,"" );
					else
						hs_strncpy(stHSReqQueryMaxOrderVolume.InstrumentID,szTemp,sizeof(stHSReqQueryMaxOrderVolume.InstrumentID));
					printf("Please input OrderCommand（若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQueryMaxOrderVolume.OrderCommand,"" );
					else
						hs_strncpy(stHSReqQueryMaxOrderVolume.OrderCommand,szTemp ,sizeof(stHSReqQueryMaxOrderVolume.OrderCommand));
					printf("Please input Direction（若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						stHSReqQueryMaxOrderVolume.Direction = '\0';
					else
						stHSReqQueryMaxOrderVolume.Direction = szTemp[0];
					printf("Please input OffsetFlag（若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						stHSReqQueryMaxOrderVolume.OffsetFlag = '\0';
					else
						stHSReqQueryMaxOrderVolume.OffsetFlag = szTemp[0];
					printf("Please input HedgeType（若想传空直接回车【Enter】）:");
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
					printf("Please input ExchangeID （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQueryLockVolume.ExchangeID,"" );
					else
						hs_strncpy(stHSReqQueryLockVolume.ExchangeID,szTemp,sizeof(stHSReqQueryLockVolume.ExchangeID));
					printf("Please input UnderlyingInstrID （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQueryLockVolume.UnderlyingInstrID,"" );
					else
						hs_strncpy(stHSReqQueryLockVolume.UnderlyingInstrID,szTemp,sizeof(stHSReqQueryLockVolume.UnderlyingInstrID));
					printf("Please input LockType（若想传空直接回车【Enter】）:");
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
					printf("Please input ExchangeID （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQueryExerciseVolume.ExchangeID,"" );
					else
						strcpy(stHSReqQueryExerciseVolume.ExchangeID,szTemp);
					printf("Please input InstrumentID （若想传空直接回车【Enter】）:");
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
					printf("Please input ExchangeID （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQryPosition.ExchangeID,"" );
					else
						hs_strncpy(stHSReqQryPosition.ExchangeID,szTemp,sizeof(stHSReqQryPosition.ExchangeID));
					printf("Please input InstrumentID （若想传空直接回车【Enter】）:");
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
					printf("Please input ExchangeID （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQryOrder.ExchangeID,"" );
					else
						hs_strncpy(stHSReqQryOrder.ExchangeID,szTemp,sizeof(stHSReqQryOrder.ExchangeID));
					printf("Please input InstrumentID （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQryOrder.InstrumentID,"" );
					else
						hs_strncpy(stHSReqQryOrder.InstrumentID,szTemp,sizeof(stHSReqQryOrder.InstrumentID));
					printf("Please input OrderSysID （若想传空直接回车【Enter】）:");
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
					printf("Please input ExchangeID （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQryTrade.ExchangeID,"" );
					else
						hs_strncpy(stHSReqQryTrade.ExchangeID,szTemp,sizeof(stHSReqQryTrade.ExchangeID));
					printf("Please input InstrumentID （若想传空直接回车【Enter】）:");
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
					printf("Please input ExchangeID （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQryExercise.ExchangeID,"" );
					else
						hs_strncpy(stHSReqQryExercise.ExchangeID,szTemp,sizeof(stHSReqQryExercise.ExchangeID));
					printf("Please input InstrumentID （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQryExercise.InstrumentID,"" );
					else
						hs_strncpy(stHSReqQryExercise.InstrumentID,szTemp,sizeof(stHSReqQryExercise.InstrumentID));
					printf("Please input ExerciseOrderSysID （若想传空直接回车【Enter】）:");
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
					printf("Please input ExchangeID （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQryLock.ExchangeID,"" );
					else
						hs_strncpy(stHSReqQryLock.ExchangeID,szTemp,sizeof(stHSReqQryLock.ExchangeID));
					printf("Please input UnderlyingInstrID （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQryLock.UnderlyingInstrID,"" );
					else
						hs_strncpy(stHSReqQryLock.UnderlyingInstrID,szTemp,sizeof(stHSReqQryLock.UnderlyingInstrID));
					printf("Please input LockOrderSysID （若想传空直接回车【Enter】）:");
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
					printf("Please input CombOrderSysID （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQryCombAction.CombOrderSysID,"" );
					else
						hs_strncpy(stHSReqQryCombAction.CombOrderSysID,szTemp,sizeof(stHSReqQryCombAction.CombOrderSysID));
					printf("Please input ExchangeID （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQryCombAction.ExchangeID,"" );
					else
						hs_strncpy(stHSReqQryCombAction.ExchangeID,szTemp,sizeof(stHSReqQryCombAction.ExchangeID));
					printf("Please input InstrumentID （若想传空直接回车【Enter】）:");
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
					printf("Please input ExchangeID （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQryInstrument.ExchangeID,"" );
					else
						hs_strncpy(stHSReqQryInstrument.ExchangeID,szTemp,sizeof(stHSReqQryInstrument.ExchangeID));
					printf("Please input InstrumentID （若想传空直接回车【Enter】）:");
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
					printf("Please input ExchangeID （若想传空直接回车【Enter】）:");
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
					printf("Please input ExchangeID （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQryExerciseAssign.ExchangeID,"" );
					else
						hs_strncpy(stHSReqQryExerciseAssign.ExchangeID,szTemp,sizeof(stHSReqQryExerciseAssign.ExchangeID));
					printf("Please input InstrumentID （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQryExerciseAssign.InstrumentID,"" );
					else
						hs_strncpy(stHSReqQryExerciseAssign.InstrumentID,szTemp,sizeof(stHSReqQryExerciseAssign.InstrumentID));
					printf("Please input PositionType（若想传空直接回车【Enter】）:");
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
					printf("Please input BankID （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqTransfer.BankID,"" );
					else
						hs_strncpy(stHSReqTransfer.BankID,szTemp,sizeof(stHSReqTransfer.BankID));
					printf("Please input TransferType（若想传空直接回车【Enter】）:");
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
					printf("Please input FundPassword （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqTransfer.FundPassword,"" );
					else
						hs_strncpy(stHSReqTransfer.FundPassword,szTemp,sizeof(stHSReqTransfer.FundPassword));
					printf("Please input BankPassword （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqTransfer.BankPassword,"" );
					else
						hs_strncpy(stHSReqTransfer.BankPassword,szTemp,sizeof(stHSReqTransfer.BankPassword));
					printf("Please input CurrencyID（若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						stHSReqTransfer.CurrencyID = '\0';
					else
						stHSReqTransfer.CurrencyID = szTemp[0];
					printf("Please input TransferOccasion （若想传空直接回车【Enter】）:");
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
					printf("Please input BankID （若想传空直接回车【Enter】）:");
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
					printf("Please input BankID （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQueryBankBalance.BankID,"" );
					else
						hs_strncpy(stHSReqQueryBankBalance.BankID,szTemp,sizeof(stHSReqQueryBankBalance.BankID));
					printf("Please input FundPassword （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQueryBankBalance.FundPassword,"" );
					else
						hs_strncpy(stHSReqQueryBankBalance.FundPassword,szTemp,sizeof(stHSReqQueryBankBalance.FundPassword));
					printf("Please input BankPassword （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQueryBankBalance.BankPassword,"" );
					else
						hs_strncpy(stHSReqQueryBankBalance.BankPassword,szTemp,sizeof(stHSReqQueryBankBalance.BankPassword));
					printf("Please input CurrencyID（若想传空直接回车【Enter】）:");
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
					printf("Please input BankID （若想传空直接回车【Enter】）:");
					cin.clear();
					cin.ignore();
					cin.get(szTemp,260,'\n');
					if (szTemp[0] == 10)
						strcpy(stHSReqQueryBankAccount.BankID,"" );
					else
						hs_strncpy(stHSReqQueryBankAccount.BankID,szTemp,sizeof(stHSReqQueryBankAccount.BankID));
					printf("Please input CurrencyID（若想传空直接回车【Enter】）:");
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
						printf("Please input ExchangeID（若想传空直接回车【Enter】）:");
						cin.clear();
						cin.ignore();
						cin.get(szTemp,260,'\n');
						if (szTemp[0] == 10)
							strcpy(stHSReqQryMargin.ExchangeID,"" );
						else
							hs_strncpy(stHSReqQryMargin.ExchangeID,szTemp,sizeof(stHSReqQryMargin.ExchangeID));
						printf("Please input InstrumentID（若想传空直接回车【Enter】）:");
						cin.clear();
						cin.ignore();
						cin.get(szTemp,260,'\n');
						if (szTemp[0] == 10)
							strcpy(stHSReqQryMargin.InstrumentID,"" );
						else
							hs_strncpy(stHSReqQryMargin.InstrumentID,szTemp,sizeof(stHSReqQryMargin.InstrumentID));
						printf("Please input UnderlyingInstrID（若想传空直接回车【Enter】）:");
						cin.clear();
						cin.ignore();
						cin.get(szTemp,260,'\n');
						if (szTemp[0] == 10)
							strcpy(stHSReqQryMargin.UnderlyingInstrID,"" );
						else
							hs_strncpy(stHSReqQryMargin.UnderlyingInstrID,szTemp,sizeof(stHSReqQryMargin.UnderlyingInstrID));
						printf("Please input HedgeType（若想传空直接回车【Enter】）:");
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
						printf("Please input ProductType（若想传空直接回车【Enter】）:");
						cin.clear();
						cin.ignore();
						cin.get(szTemp,260,'\n');
						if (szTemp[0] == 10)
							stHSReqQryCommission.ProductType = '\0';
						else
							stHSReqQryCommission.ProductType = szTemp[0];
						printf("Please input InstrumentID（若想传空直接回车【Enter】）:");
						cin.clear();
						cin.ignore();
						cin.get(szTemp,260,'\n');
						if (szTemp[0] == 10)
							strcpy(stHSReqQryCommission.InstrumentID,"" );
						else
							hs_strncpy(stHSReqQryCommission.InstrumentID,szTemp,sizeof(stHSReqQryCommission.InstrumentID));
						printf("Please input UnderlyingInstrID（若想传空直接回车【Enter】）:");
						cin.clear();
						cin.ignore();
						cin.get(szTemp,260,'\n');
						if (szTemp[0] == 10)
							strcpy(stHSReqQryCommission.UnderlyingInstrID,"" );
						else
							hs_strncpy(stHSReqQryCommission.UnderlyingInstrID,szTemp,sizeof(stHSReqQryCommission.UnderlyingInstrID));
						printf("Please input ExchangeID（若想传空直接回车【Enter】）:");
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
						printf("Please input ExchangeID（若想传空直接回车【Enter】）:");
						cin.clear();
						cin.ignore();
						cin.get(szTemp,260,'\n');
						if (szTemp[0] == 10)
							strcpy(stHSReqQryDepthMarketData.ExchangeID,"" );
						else
							hs_strncpy(stHSReqQryDepthMarketData.ExchangeID,szTemp,sizeof(stHSReqQryDepthMarketData.ExchangeID));
						printf("Please input InstrumentID（若想传空直接回车【Enter】）:");
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
						printf("Please input FromCurrencyID（若想传空直接回车【Enter】）:");
						cin.clear();
						cin.ignore();
						cin.get(szTemp,260,'\n');
						if (szTemp[0] == 10)
							stHSReqQryExchangeRate.FromCurrencyID = '\0';
						else
							stHSReqQryExchangeRate.FromCurrencyID = szTemp[0];
						printf("Please input ToCurrencyID（若想传空直接回车【Enter】）:");
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
	addInfo("登陆交易账户");
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
		str.Format("登陆失败 [%s]", lpTradeSpi->lpUserApi->GetApiErrorMsg(iRet));
		addInfo(str);
	}
}


void CMyTradeSpi::queryFund()
{
	addInfo("查询资金信息");
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
	addInfo("查询账户持仓");
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
			sDirection = "买";
		}
		else {
			sDirection = "卖";
		}
		if (offset == HS_OF_Open) {
			sOffset = "开";
		}
		else if (offset == HS_OF_CloseToday) {
			sOffset = "平今";
		}
		else {
			sOffset = "平昨";
		}

		str.Format("委托成功,编号[%d]，[%s %.4f %s %s]", orderRef, code, price, sDirection, sOffset);
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
		addInfo("发起撤单 id=["+ sOrderRef+"]");
	}

}

//336800客户登录
void  CMyTradeSpi::OnRspUserLogin(CHSRspUserLoginField *pRspUserLogin, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (IsErrorRspInfo(pRspInfo)==false) {
		addInfo("登录交易账户成功");
		sessionID = pRspUserLogin->SessionID;
		queryFund();
		queryPosition();
		queryStockCode();
	}


    if(! pRspUserLogin && bIsLast == true )
    {
        cout<<"应答结束!"<<endl;
    }
    else
    {
        cout<<"************************客户登录应答!*************************"<<endl;
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

//336801密码更改
void  CMyTradeSpi::OnRspUserPasswordUpdate(CHSRspUserPasswordUpdateField *pRspUserPasswordUpdate, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspUserPasswordUpdate && bIsLast == true )
    {
        cout<<"应答结束!"<<endl;
    }
    else
    {
        cout<<"************************密码更改应答!*************************"<<endl;
    }
	if (pRspInfo->ErrorID == 0)
	{
		cout<<"密码修改成功"<<endl;
	}
}
//336812报单录入
void  CMyTradeSpi::OnRspErrorOrderInsert(CHSRspOrderInsertField *pRspOrderInsert, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspOrderInsert && bIsLast == true )
    {
        cout<<"应答结束!"<<endl;
    }
    else
    {
		CString str;
		str.Format("委托失败！[id=%s msg=[%s]]", pRspOrderInsert->OrderRef,pRspInfo->ErrorMsg);
		addInfo(str);

        cout<<"************************报单录入应答!*************************"<<endl;
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
//336813撤单
void  CMyTradeSpi::OnRspOrderAction(CHSRspOrderActionField *pRspOrderAction, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspOrderAction && bIsLast == true )
    {
        cout<<"应答结束!"<<endl;
    }
    else
    {
		CString str;
		str.Format("撤单已经发送 id = [%s]", pRspOrderAction->OrderRef );
		addInfo(str);
		
		cout<<"************************撤单应答!*************************"<<endl;
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
//336814行权录入
void  CMyTradeSpi::OnRspErrorExerciseOrderInsert(CHSRspExerciseOrderInsertField *pRspExerciseOrderInsert, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspExerciseOrderInsert && bIsLast == true )
    {
        cout<<"应答结束!"<<endl;
    }
    else
    {
        cout<<"************************行权录入应答!*************************"<<endl;
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
//336815行权撤单
void  CMyTradeSpi::OnRspExerciseOrderAction(CHSRspExerciseOrderActionField *pRspExerciseOrderAction, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspExerciseOrderAction && bIsLast == true )
    {
        cout<<"应答结束!"<<endl;
    }
    else
    {
        cout<<"************************行权撤单应答!*************************"<<endl;
        printf("\t%30s = %35s\r\n","AccountID:",pRspExerciseOrderAction->AccountID);
        printf("\t%30s = %35s\r\n","ExchangeID:",pRspExerciseOrderAction->ExchangeID);
        printf("\t%30s = %35s\r\n","ExerciseOrderSysID:",pRspExerciseOrderAction->ExerciseOrderSysID);
        printf("\t%30s = %35s\r\n","ExerciseRef:",pRspExerciseOrderAction->ExerciseRef);
        printf("\t%30s = %35d\r\n","SessionID:",pRspExerciseOrderAction->SessionID);
        printf("\t%30s = %35c\r\n","OrderStatus:",pRspExerciseOrderAction->OrderStatus);
        printf("\t%30s = %35s\r\n","ExecOrderActionRef:",pRspExerciseOrderAction->ExecOrderActionRef);
    }
}
//336913锁定录入
void  CMyTradeSpi::OnRspErrorLockInsert(CHSRspLockInsertField *pRspLockInsert, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspLockInsert && bIsLast == true )
    {
        cout<<"应答结束!"<<endl;
    }
    else
    {
        cout<<"************************锁定录入应答!*************************"<<endl;
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
//336817询价录入
void  CMyTradeSpi::OnRspForQuoteInsert(CHSRspForQuoteInsertField *pRspForQuoteInsert, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspForQuoteInsert && bIsLast == true )
    {
        cout<<"应答结束!"<<endl;
    }
    else
    {
        cout<<"************************询价录入应答!*************************"<<endl;
        printf("\t%30s = %35s\r\n","AccountID:",pRspForQuoteInsert->AccountID);
        printf("\t%30s = %35s\r\n","ExchangeID:",pRspForQuoteInsert->ExchangeID);
        printf("\t%30s = %35s\r\n","InstrumentID:",pRspForQuoteInsert->InstrumentID);
        printf("\t%30s = %35c\r\n","OrderStatus:",pRspForQuoteInsert->OrderStatus);
    }
}
//336818申请组合录入
void  CMyTradeSpi::OnRspErrorCombActionInsert(CHSRspCombActionInsertField *pRspCombActionInsert, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspCombActionInsert && bIsLast == true )
    {
        cout<<"应答结束!"<<endl;
    }
    else
    {
        cout<<"************************申请组合录入应答!*************************"<<endl;
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
//336810最大报单数量获取
void  CMyTradeSpi::OnRspQueryMaxOrderVolume(CHSRspQueryMaxOrderVolumeField *pRspQueryMaxOrderVolume, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQueryMaxOrderVolume && bIsLast == true )
    {
        cout<<"应答结束!"<<endl;
    }
    else
    {
        cout<<"************************最大报单数量获取应答!*************************"<<endl;
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
//336912可锁定数量获取
void  CMyTradeSpi::OnRspQueryLockVolume(CHSRspQueryLockVolumeField *pRspQueryLockVolume, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQueryLockVolume && bIsLast == true )
    {
        cout<<"应答结束!"<<endl;
    }
    else
    {
        cout<<"************************可锁定数量获取应答!*************************"<<endl;
        printf("\t%30s = %35s\r\n","AccountID:",pRspQueryLockVolume->AccountID);
        printf("\t%30s = %35s\r\n","ExchangeID:",pRspQueryLockVolume->ExchangeID);
        printf("\t%30s = %35s\r\n","UnderlyingInstrID:",pRspQueryLockVolume->UnderlyingInstrID);
        printf("\t%30s = %35c\r\n","LockType:",pRspQueryLockVolume->LockType);
        printf("\t%30s = %35f\r\n","AvailablePositionVolume:",pRspQueryLockVolume->AvailablePositionVolume);
    }
}
//336819可行权数量获取
void  CMyTradeSpi::OnRspQueryExerciseVolume(CHSRspQueryExerciseVolumeField *pRspQueryExerciseVolume, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQueryExerciseVolume && bIsLast == true )
    {
        cout<<"应答结束!"<<endl;
    }
    else
    {
        cout<<"************************可行权数量获取应答!*************************"<<endl;
        printf("\t%30s = %35s\r\n","AccountID:",pRspQueryExerciseVolume->AccountID);
        printf("\t%30s = %35f\r\n","MaxOrderVolumeUnit:",pRspQueryExerciseVolume->MaxOrderVolumeUnit);
        printf("\t%30s = %35s\r\n","ExchangeID:",pRspQueryExerciseVolume->ExchangeID);
        printf("\t%30s = %35s\r\n","InstrumentID:",pRspQueryExerciseVolume->InstrumentID);
    }
}
//336851持仓汇总查询
void  CMyTradeSpi::OnRspQryPosition(CHSRspQryPositionField *pRspQryPosition, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQryPosition && bIsLast == true )
    {
        cout<<"应答结束!"<<endl;
    }
    else
    {
		CString str;
		CString str_d = "多头";
		if(pRspQryPosition->Direction== HS_D_Sell)
			str_d = "空头";
		str.Format("代码=[%s] 方向=[%s] 总仓位=[%.0f] ", pRspQryPosition->InstrumentID, str_d, pRspQryPosition->PositionVolume);
		addInfo(str);
		mainDlg->mStockCode.GetWindowTextA(str);
		if (str == "") {
			mainDlg->mStockCode.SetWindowTextA(pRspQryPosition->InstrumentID);
		}
        cout<<"************************持仓汇总查询应答!*************************"<<endl;
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
//336850资金账户查询
void  CMyTradeSpi::OnRspQryTradingAccount(CHSRspQryTradingAccountField *pRspQryTradingAccount, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQryTradingAccount && bIsLast == true )
    {
        cout<<"应答结束!"<<endl;
    }
    else
    {

		CString str;
		str.Format("总权益=[%.2f] 可用资金=[%.2f]", pRspQryTradingAccount->Equity, pRspQryTradingAccount->AvailableBalance);
		addInfo(str);

        cout<<"************************资金账户查询应答!*************************"<<endl;
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
//336853报单查询
void  CMyTradeSpi::OnRspQryOrder(CHSOrderField *pRspQryOrder, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQryOrder && bIsLast == true )
    {
        cout<<"应答结束!"<<endl;
    }
    else
    {
        cout<<"************************报单查询应答!*************************"<<endl;
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
//336854成交查询
void  CMyTradeSpi::OnRspQryTrade(CHSTradeField *pRspQryTrade, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQryTrade && bIsLast == true )
    {
        cout<<"应答结束!"<<endl;
    }
    else
    {
        cout<<"************************成交查询应答!*************************"<<endl;
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
//336855行权查询
void  CMyTradeSpi::OnRspQryExercise(CHSExerciseField *pRspQryExercise, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQryExercise && bIsLast == true )
    {
        cout<<"应答结束!"<<endl;
    }
    else
    {
        cout<<"************************行权查询应答!*************************"<<endl;
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
//336856锁定查询
void  CMyTradeSpi::OnRspQryLock(CHSLockField *pRspQryLock, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQryLock && bIsLast == true )
    {
        cout<<"应答结束!"<<endl;
    }
    else
    {
        cout<<"************************锁定查询应答!*************************"<<endl;
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
//336857申请组合查询
void  CMyTradeSpi::OnRspQryCombAction(CHSCombActionField *pRspQryCombAction, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQryCombAction && bIsLast == true )
    {
        cout<<"应答结束!"<<endl;
    }
    else
    {
        cout<<"************************申请组合查询应答!*************************"<<endl;
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
//336852组合持仓明细查询
void  CMyTradeSpi::OnRspQryPositionCombineDetail(CHSRspQryPositionCombineDetailField *pRspQryPositionCombineDetail, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQryPositionCombineDetail && bIsLast == true )
    {
        cout<<"应答结束!"<<endl;
    }
    else
    {
        cout<<"************************组合持仓明细查询应答!*************************"<<endl;
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
//336858合约信息查询
void  CMyTradeSpi::OnRspQryInstrument(CHSRspQryInstrumentField *pRspQryInstrument, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQryInstrument && bIsLast == true )
    {
        cout<<"应答结束!"<<endl;
    }
    else
    {
		//addInfo(pRspQryInstrument->InstrumentID);
		mapStockCode[pRspQryInstrument->InstrumentID] = pRspQryInstrument->ExchangeID;
		//mapStockCode.insert(pRspQryInstrument->InstrumentID, pRspQryInstrument->ExchangeID);

        cout<<"************************合约信息查询应答!*************************"<<endl;
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
//336910备兑缺口查询
void  CMyTradeSpi::OnRspQryCoveredShort(CHSRspQryCoveredShortField *pRspQryCoveredShort, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQryCoveredShort && bIsLast == true )
    {
        cout<<"应答结束!"<<endl;
    }
    else
    {
        cout<<"************************备兑缺口查询应答!*************************"<<endl;
        printf("\t%30s = %35s\r\n","AccountID:",pRspQryCoveredShort->AccountID);
        printf("\t%30s = %35s\r\n","ExchangeID:",pRspQryCoveredShort->ExchangeID);
        printf("\t%30s = %35s\r\n","UnderlyingInstrID:",pRspQryCoveredShort->UnderlyingInstrID);
        printf("\t%30s = %35f\r\n","CoveredLockVolume:",pRspQryCoveredShort->CoveredLockVolume);
        printf("\t%30s = %35f\r\n","CoveredShortVolume:",pRspQryCoveredShort->CoveredShortVolume);
        printf("\t%30s = %35f\r\n","CoveredEstimateShortVolume:",pRspQryCoveredShort->CoveredEstimateShortVolume);
        printf("\t%30s = %35s\r\n","MsgContent:",pRspQryCoveredShort->MsgContent);
    }
}
//336911行权指派查询
void  CMyTradeSpi::OnRspQryExerciseAssign(CHSRspQryExerciseAssignField *pRspQryExerciseAssign, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQryExerciseAssign && bIsLast == true )
    {
        cout<<"应答结束!"<<endl;
    }
    else
    {
        cout<<"************************行权指派查询应答!*************************"<<endl;
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
//336900银行转账
void  CMyTradeSpi::OnRspTransfer(CHSRspTransferField *pRspTransfer, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspTransfer && bIsLast == true )
    {
        cout<<"应答结束!"<<endl;
    }
    else
    {
        cout<<"************************银行转账应答!*************************"<<endl;
        printf("\t%30s = %35d\r\n","TransferSerialID:",pRspTransfer->TransferSerialID);
        printf("\t%30s = %35s\r\n","BankID:",pRspTransfer->BankID);
        printf("\t%30s = %35c\r\n","TransferType:",pRspTransfer->TransferType);
        printf("\t%30s = %35f\r\n","OccurBalance:",pRspTransfer->OccurBalance);
        printf("\t%30s = %35c\r\n","CurrencyID:",pRspTransfer->CurrencyID);
        printf("\t%30s = %35s\r\n","TransferOccasion:",pRspTransfer->TransferOccasion);
    }
}
//336901银行转账查询
void  CMyTradeSpi::OnRspQryTransfer(CHSRspQryTransferField *pRspQryTransfer, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQryTransfer && bIsLast == true )
    {
        cout<<"应答结束!"<<endl;
    }
    else
    {
        cout<<"************************银行转账查询应答!*************************"<<endl;
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
//336902银行余额查询
void  CMyTradeSpi::OnRspQueryBankBalance(CHSRspQueryBankBalanceField *pRspQueryBankBalance, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQueryBankBalance && bIsLast == true )
    {
        cout<<"应答结束!"<<endl;
    }
    else
    {
        cout<<"************************银行余额查询应答!*************************"<<endl;
        printf("\t%30s = %35d\r\n","TransferSerialID:",pRspQueryBankBalance->TransferSerialID);
    }
}
//336903银行账户查询
void  CMyTradeSpi::OnRspQueryBankAccount(CHSRspQueryBankAccountField *pRspQueryBankAccount, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQueryBankAccount && bIsLast == true )
    {
        cout<<"应答结束!"<<endl;
    }
    else
    {
        cout<<"************************银行账户查询应答!*************************"<<endl;
        printf("\t%30s = %35s\r\n","BankID:",pRspQueryBankAccount->BankID);
        printf("\t%30s = %35s\r\n","BankName:",pRspQueryBankAccount->BankName);
        printf("\t%30s = %35s\r\n","BankAccountID:",pRspQueryBankAccount->BankAccountID);
        printf("\t%30s = %35c\r\n","CurrencyID:",pRspQueryBankAccount->CurrencyID);
    }
}
//336990客户账单查询
void  CMyTradeSpi::OnRspQueryBillContent(CHSRspQueryBillContentField *pRspQueryBillContent, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQueryBillContent && bIsLast == true )
    {
        cout<<"应答结束!"<<endl;
    }
    else
    {
        cout<<"************************客户账单查询应答!*************************"<<endl;
        printf("\t%30s = %35s\r\n","BillContent:",pRspQueryBillContent->BillContent);
    }
}
//336991客户账单确认
void  CMyTradeSpi::OnRspBillConfirm(CHSRspBillConfirmField *pRspBillConfirm, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspBillConfirm && bIsLast == true )
    {
        cout<<"应答结束!"<<endl;
    }
    else
    {
        cout<<"************************客户账单确认应答!*************************"<<endl;
        printf("\t%30s = %35s\r\n","AccountID:",pRspBillConfirm->AccountID);
        printf("\t%30s = %35c\r\n","BillConfirmStatus:",pRspBillConfirm->BillConfirmStatus);
        printf("\t%30s = %35d\r\n","ConfirmDate:",pRspBillConfirm->ConfirmDate);
        printf("\t%30s = %35d\r\n","ConfirmTime:",pRspBillConfirm->ConfirmTime);
    }
}
//336860保证金查询
void  CMyTradeSpi::OnRspQryMargin(CHSRspQryMarginField *pRspQryMargin, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQryMargin && bIsLast == true )
    {
        cout<<"应答结束!"<<endl;
    }
    else
    {
        cout<<"************************保证金查询应答!*************************"<<endl;
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
//336861手续费查询
void  CMyTradeSpi::OnRspQryCommission(CHSRspQryCommissionField *pRspQryCommission, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQryCommission && bIsLast == true )
    {
        cout<<"应答结束!"<<endl;
    }
    else
    {
        cout<<"************************手续费查询应答!*************************"<<endl;
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
//336865汇率查询
void  CMyTradeSpi::OnRspQryExchangeRate(CHSRspQryExchangeRateField *pRspQryExchangeRate, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQryExchangeRate && bIsLast == true )
    {
        cout<<"应答结束!"<<endl;
    }
    else
    {
        cout<<"************************汇率查询应答!*************************"<<endl;
        printf("\t%30s = %35c\r\n","FromCurrencyID:",pRspQryExchangeRate->FromCurrencyID);
        printf("\t%30s = %35c\r\n","ToCurrencyID:",pRspQryExchangeRate->ToCurrencyID);
        printf("\t%30s = %35f\r\n","ExchangeRate:",pRspQryExchangeRate->ExchangeRate);
        printf("\t%30s = %35f\r\n","FromCurrencyUnit:",pRspQryExchangeRate->FromCurrencyUnit);
    }
}
//336863持仓明细查询
void  CMyTradeSpi::OnRspQryPositionDetail(CHSRspQryPositionDetailField *pRspQryPositionDetail, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQryPositionDetail && bIsLast == true )
    {
        cout<<"应答结束!"<<endl;
    }
    else
    {
        cout<<"************************持仓明细查询应答!*************************"<<endl;
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
//336862经纪公司配置参数查询
void  CMyTradeSpi::OnRspQrySysConfig(CHSRspQrySysConfigField *pRspQrySysConfig, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(! pRspQrySysConfig && bIsLast == true )
    {
        cout<<"应答结束!"<<endl;
    }
    else
    {
        cout<<"************************经纪公司配置参数查询应答!*************************"<<endl;
        printf("\t%30s = %35f\r\n","ConfigNo:",pRspQrySysConfig->ConfigNo);
        printf("\t%30s = %35s\r\n","ConfigValue:",pRspQrySysConfig->ConfigValue);
    }
}
//336864行情查询
void  CMyTradeSpi::OnRspQryDepthMarketData(CHSDepthMarketDataField *pRspQryDepthMarketData, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (IsErrorRspInfo(pRspInfo))
	{
		return;
	}
	if(! pRspQryDepthMarketData && bIsLast == true )
	{
		cout<<"应答结束!"<<endl;
	}
	else
	{
		cout<<"************************行情查询应答!*************************"<<endl;
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
	case HS_OS_NotReported:str = "未报"; break;
	case HS_OS_ToBeReported:str = "待报"; break;
	case HS_OS_Reported:str = "已报"; break;
	case HS_OS_ReportedToBeCancel:str = "已报待撤"; break;
	case HS_OS_PartsTradedToBeCancel:str = "部成待撤"; break;
	case HS_OS_CanceledWithPartsTraded:str = "部撤"; break;

	case HS_OS_Canceled:str = "已撤"; break;
	case HS_OS_PartsTraded:str = "部成"; break;
	case HS_OS_Traded:str = "已成"; break;
	case HS_OS_Abandoned:str = "废单"; break;
	case HS_OS_CancelFailed:str = "撤废"; break;
	case HS_OS_Confirmed:str = "已确认（询价请求）"; break;
	case HS_OS_ToBeConfirmed:str = "待确认"; break;



	default:
		break;
	}
	return str;
}

/// Description: 主推-成交回报
void CMyTradeSpi::OnRtnTrade(CHSTradeField *pRtnTrade)
{
	CString str;
	str.Format("成交回报[id=%s, 成交数量=[%.0f] ]", pRtnTrade->OrderRef, pRtnTrade->TradeVolume);
	addInfo(str);

	cout<<"**************************收到成交回报数据：**************************"<<endl;
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



/// Description: 主推-报单回报
void CMyTradeSpi::OnRtnOrder(CHSOrderField *pRtnOrder) 
{
	CString str;
	str.Format("委托回报[id=%s, 委托状态=[%s], 信息=[%s] ]", pRtnOrder->OrderRef,getStatus(pRtnOrder->OrderStatus), pRtnOrder->ErrorMsg);
	addInfo(str);

	cout<<"***********************收到报单回报数据：*********************"<<endl;
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

/// Description: 主推-行权
void CMyTradeSpi::OnRtnExercise(CHSExerciseField *pRtnExercise) 
{
	cout<<"************************收到行权主推数据：**************************"<<endl;
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

/// Description: 主推-申请组合
void CMyTradeSpi::OnRtnCombAction(CHSCombActionField *pRtnCombAction) 
{
	cout<<"**********************收到申请组合主推数据：*********************"<<endl;
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

/// Description: 主推-锁定
void CMyTradeSpi::OnRtnLock(CHSLockField *pRtnLock) 
{
	cout<<"**********************收到锁定主推数据：***********************"<<endl;
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