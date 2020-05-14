#include "stdafx.h"
#include "Md.h"

bool CMdSpi::IsErrorRspInfo(CHSRspInfoField *pRspInfo)
{
	bool ret = ((pRspInfo) && (pRspInfo->ErrorID != 0));
	if (ret)
	{
		printf("IsErrorRspInfo\n");
		cerr<<" ��Ӧ | "<<pRspInfo->ErrorMsg<<endl;
	}
	return ret;
}

void  CMdSpi::OnFrontConnected()	
{
	/* �����ӽ����ɹ����������������߳� */
	addInfo("�������ӳɹ�\r\n");
	if (false == DealBusinessTrd.IsRunning())
	{
		DealBusinessTrd.Start(DealBusiness, 0, this);
	}

	return;
}

void  CMdSpi::OnFrontDisconnected(int nReason)
{
	addInfo(lpUserApi->GetApiErrorMsg(nReason));
	printf("\r\n");
	return;
}

///620001_33330 ����-��Ȩ��������Ӧ��
void CMdSpi::OnRspDepthMarketDataSubscribe(CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if (pRspInfo->ErrorID == 0)
	{
		addInfo("��������ɹ�");
	}
	else
	{
		addInfo(pRspInfo->ErrorMsg);
	}
	return;
}

///620002_33330 ����ȡ��-��Ȩ��������Ӧ��
void CMdSpi::OnRspDepthMarketDataCancel(CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if (pRspInfo->ErrorID == 0)
	{
		printf("ȡ����������ɹ�\n");
	}
	else
	{
		printf(pRspInfo->ErrorMsg);
	}
	return;
}

///620003_33330 ����-��Ȩ��������Ӧ��
void CMdSpi::OnRtnDepthMarketData(CHSDepthMarketDataField *pDepthMarketData)
{

	CString str;
	str.Format("�յ�����[%s]=[%.4f %.4f]", pDepthMarketData->InstrumentID, pDepthMarketData->BidPrice1, pDepthMarketData->AskPrice1);
	//addInfo(str);
	mainDlg->updatePrice(pDepthMarketData->InstrumentID, pDepthMarketData->BidPrice1, pDepthMarketData->AskPrice1);

	cout<<"������: "<<pDepthMarketData->TradingDay<<endl;
	cout<<"��Լ����: "<<pDepthMarketData->InstrumentID<<endl;
	cout<<"����������: "<<pDepthMarketData->ExchangeID<<endl;
	cout<<"���¼�: "<<pDepthMarketData->LastPrice<<endl;
	cout<<"������: "<<pDepthMarketData->PreSettlementPrice<<endl;
	cout<<"�����̼�: "<<pDepthMarketData->PreClosePrice<<endl;
	cout<<"���̼�: "<<pDepthMarketData->OpenPrice<<endl;
	cout<<"��߼�: "<<pDepthMarketData->HighestPrice<<endl;
	cout<<"��ͼ�: "<<pDepthMarketData->LowestPrice<<endl;
	cout<<"�ɽ�����: "<<pDepthMarketData->TradeVolume<<endl;
	cout<<"�ɽ����: "<<pDepthMarketData->TradeBalance<<endl;
	cout<<"�ܳ���: "<<pDepthMarketData->OpenInterest<<endl;
	cout<<"���̼�: "<<pDepthMarketData->ClosePrice<<endl;
	cout<<"�����: "<<pDepthMarketData->SettlementPrice<<endl;
	cout<<"��ͣ���: "<<pDepthMarketData->UpperLimitPrice<<endl;
	cout<<"��ͣ���: "<<pDepthMarketData->LowerLimitPrice<<endl;
	cout<<"����ʵ��: "<<pDepthMarketData->PreDelta<<endl;
	cout<<"����ʵ��: "<<pDepthMarketData->CurrDelta<<endl;
	cout<<"��󶳽����ʱ��: "<<pDepthMarketData->UpdateTime<<endl;
	cout<<"�����һ: "<<pDepthMarketData->BidPrice1<<endl;
	cout<<"������һ: "<<pDepthMarketData->BidVolume1<<endl;
	cout<<"������һ: "<<pDepthMarketData->AskPrice1<<endl;
	cout<<"������һ: "<<pDepthMarketData->AskVolume1<<endl;
	cout<<"����۶�: "<<pDepthMarketData->BidPrice2<<endl;
	cout<<"��������: "<<pDepthMarketData->BidVolume2<<endl;
	cout<<"�����۶�: "<<pDepthMarketData->AskPrice2<<endl;
	cout<<"��������: "<<pDepthMarketData->AskVolume2<<endl;
	cout<<"�������: "<<pDepthMarketData->BidPrice3<<endl;
	cout<<"��������: "<<pDepthMarketData->BidVolume3<<endl;
	cout<<"��������: "<<pDepthMarketData->AskPrice3<<endl;
	cout<<"��������: "<<pDepthMarketData->AskVolume3<<endl;
	cout<<"�������: "<<pDepthMarketData->BidPrice4<<endl;
	cout<<"��������: "<<pDepthMarketData->BidVolume4<<endl;
	cout<<"��������: "<<pDepthMarketData->AskPrice4<<endl;
	cout<<"��������: "<<pDepthMarketData->AskVolume4<<endl;
	cout<<"�������: "<<pDepthMarketData->BidPrice5<<endl;
	cout<<"��������: "<<pDepthMarketData->BidVolume5<<endl;
	cout<<"��������: "<<pDepthMarketData->AskPrice5<<endl;
	cout<<"��������: "<<pDepthMarketData->AskVolume5<<endl;
	cout<<"ƽ���۸�: "<<pDepthMarketData->AveragePrice<<endl;
	cout<<"��ֲ���: "<<pDepthMarketData->PreOpenInterest<<endl;
	cout<<"��Լ����״̬: "<<pDepthMarketData->InstrumentTradeStatus<<endl;
	cout<<"��Լʵʱ��������: "<<pDepthMarketData->OpenRestriction<<endl;
}

void  CMdSpi:: DealBusiness(void* lpvoid)
{
	CMdSpi *lpMdSpi = (CMdSpi*)lpvoid;

	while(false == lpMdSpi->bStopDealBusiness)
	{

		cerr<<"------------------------------------------------"<<endl;
		cerr<<" [1] ���ĵ�������                               "<<endl;
		cerr<<" [2] ȡ�����ĵ�������                           "<<endl;
		cerr<<"------------------------------------------------"<<endl;
		
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
						CHSReqDepthMarketDataField stHSReqSingleMarket[1];
						memset(&stHSReqSingleMarket[0],0,sizeof(CHSReqDepthMarketDataField));

						char szTemp[260];
						printf("Please input ExchangeID �����봫��ֱ�ӻس���Enter����:");
						cin.clear();
						cin.ignore();
						cin.get(szTemp,260,'\n');
						if (szTemp[0] == 10)
							strcpy(stHSReqSingleMarket[0].ExchangeID,"" );
						else
							hs_strncpy(stHSReqSingleMarket[0].ExchangeID,szTemp,sizeof(stHSReqSingleMarket[0].ExchangeID));
						printf("Please input InstrumentID �����봫��ֱ�ӻس���Enter����:");
						cin.clear();
						cin.ignore();
						cin.get(szTemp,260,'\n');
						if (szTemp[0] == 10)
							strcpy(stHSReqSingleMarket[0].InstrumentID,"" );
						else
							hs_strncpy(stHSReqSingleMarket[0].InstrumentID,szTemp,sizeof(stHSReqSingleMarket[0].InstrumentID));
						int iRet = lpMdSpi->lpUserApi->ReqDepthMarketDataSubscribe(stHSReqSingleMarket,1,lpMdSpi->iRequestId++);
						if (iRet != SDK_OK)
						{
							printf(lpMdSpi->lpUserApi->GetApiErrorMsg(iRet));
						}
						break;
					}
				case 2:
					{
						CHSReqDepthMarketDataField stHSReqSingleMarket[1];
						memset(&stHSReqSingleMarket[0],0,sizeof(CHSReqDepthMarketDataField));
						char szTemp[260];
						printf("Please input ExchangeID �����봫��ֱ�ӻس���Enter����:");
						cin.clear();
						cin.ignore();
						cin.get(szTemp,260,'\n');
						if (szTemp[0] == 10)
							strcpy(stHSReqSingleMarket[0].ExchangeID,"" );
						else
							hs_strncpy(stHSReqSingleMarket[0].ExchangeID,szTemp,sizeof(stHSReqSingleMarket[0].ExchangeID));
						printf("Please input InstrumentID �����봫��ֱ�ӻس���Enter����:");
						cin.clear();
						cin.ignore();
						cin.get(szTemp,260,'\n');
						if (szTemp[0] == 10)
							strcpy(stHSReqSingleMarket[0].InstrumentID,"" );
						else
							hs_strncpy(stHSReqSingleMarket[0].InstrumentID,szTemp,sizeof(stHSReqSingleMarket[0].InstrumentID));
						int iRet = lpMdSpi->lpUserApi->ReqDepthMarketDataCancel(stHSReqSingleMarket,2,lpMdSpi->iRequestId++);
						if (iRet != SDK_OK)
						{
							printf(lpMdSpi->lpUserApi->GetApiErrorMsg(iRet));
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

void CMdSpi::subCode(CString code, CString exchange)
{
	CHSReqDepthMarketDataField field;
	memset(&field, 0, sizeof(CHSReqDepthMarketDataField));
	strncpy(field.ExchangeID, exchange, exchange.GetLength());
	strncpy(field.InstrumentID, code, code.GetLength()+1);
	lpUserApi->ReqDepthMarketDataSubscribe(&field, 1, iRequestId++);

}
