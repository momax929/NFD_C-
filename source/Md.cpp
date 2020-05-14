#include "stdafx.h"
#include "Md.h"

bool CMdSpi::IsErrorRspInfo(CHSRspInfoField *pRspInfo)
{
	bool ret = ((pRspInfo) && (pRspInfo->ErrorID != 0));
	if (ret)
	{
		printf("IsErrorRspInfo\n");
		cerr<<" 响应 | "<<pRspInfo->ErrorMsg<<endl;
	}
	return ret;
}

void  CMdSpi::OnFrontConnected()	
{
	/* 当连接建立成功后，在这里启动子线程 */
	addInfo("行情连接成功\r\n");
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

///620001_33330 订阅-期权单腿行情应答
void CMdSpi::OnRspDepthMarketDataSubscribe(CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if (pRspInfo->ErrorID == 0)
	{
		addInfo("订阅行情成功");
	}
	else
	{
		addInfo(pRspInfo->ErrorMsg);
	}
	return;
}

///620002_33330 订阅取消-期权单腿行情应答
void CMdSpi::OnRspDepthMarketDataCancel(CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if (pRspInfo->ErrorID == 0)
	{
		printf("取消订阅行情成功\n");
	}
	else
	{
		printf(pRspInfo->ErrorMsg);
	}
	return;
}

///620003_33330 主推-期权单腿行情应答
void CMdSpi::OnRtnDepthMarketData(CHSDepthMarketDataField *pDepthMarketData)
{

	CString str;
	str.Format("收到行情[%s]=[%.4f %.4f]", pDepthMarketData->InstrumentID, pDepthMarketData->BidPrice1, pDepthMarketData->AskPrice1);
	//addInfo(str);
	mainDlg->updatePrice(pDepthMarketData->InstrumentID, pDepthMarketData->BidPrice1, pDepthMarketData->AskPrice1);

	cout<<"交易日: "<<pDepthMarketData->TradingDay<<endl;
	cout<<"合约代码: "<<pDepthMarketData->InstrumentID<<endl;
	cout<<"交易所代码: "<<pDepthMarketData->ExchangeID<<endl;
	cout<<"最新价: "<<pDepthMarketData->LastPrice<<endl;
	cout<<"昨结算价: "<<pDepthMarketData->PreSettlementPrice<<endl;
	cout<<"昨收盘价: "<<pDepthMarketData->PreClosePrice<<endl;
	cout<<"开盘价: "<<pDepthMarketData->OpenPrice<<endl;
	cout<<"最高价: "<<pDepthMarketData->HighestPrice<<endl;
	cout<<"最低价: "<<pDepthMarketData->LowestPrice<<endl;
	cout<<"成交数量: "<<pDepthMarketData->TradeVolume<<endl;
	cout<<"成交金额: "<<pDepthMarketData->TradeBalance<<endl;
	cout<<"总持量: "<<pDepthMarketData->OpenInterest<<endl;
	cout<<"收盘价: "<<pDepthMarketData->ClosePrice<<endl;
	cout<<"结算价: "<<pDepthMarketData->SettlementPrice<<endl;
	cout<<"涨停板价: "<<pDepthMarketData->UpperLimitPrice<<endl;
	cout<<"跌停板价: "<<pDepthMarketData->LowerLimitPrice<<endl;
	cout<<"昨虚实度: "<<pDepthMarketData->PreDelta<<endl;
	cout<<"今虚实度: "<<pDepthMarketData->CurrDelta<<endl;
	cout<<"最后冻结更新时间: "<<pDepthMarketData->UpdateTime<<endl;
	cout<<"申买价一: "<<pDepthMarketData->BidPrice1<<endl;
	cout<<"申买量一: "<<pDepthMarketData->BidVolume1<<endl;
	cout<<"申卖价一: "<<pDepthMarketData->AskPrice1<<endl;
	cout<<"申卖量一: "<<pDepthMarketData->AskVolume1<<endl;
	cout<<"申买价二: "<<pDepthMarketData->BidPrice2<<endl;
	cout<<"申买量二: "<<pDepthMarketData->BidVolume2<<endl;
	cout<<"申卖价二: "<<pDepthMarketData->AskPrice2<<endl;
	cout<<"申卖量二: "<<pDepthMarketData->AskVolume2<<endl;
	cout<<"申买价三: "<<pDepthMarketData->BidPrice3<<endl;
	cout<<"申买量三: "<<pDepthMarketData->BidVolume3<<endl;
	cout<<"申卖价三: "<<pDepthMarketData->AskPrice3<<endl;
	cout<<"申卖量三: "<<pDepthMarketData->AskVolume3<<endl;
	cout<<"申买价四: "<<pDepthMarketData->BidPrice4<<endl;
	cout<<"申买量四: "<<pDepthMarketData->BidVolume4<<endl;
	cout<<"申卖价四: "<<pDepthMarketData->AskPrice4<<endl;
	cout<<"申卖量四: "<<pDepthMarketData->AskVolume4<<endl;
	cout<<"申买价五: "<<pDepthMarketData->BidPrice5<<endl;
	cout<<"申买量五: "<<pDepthMarketData->BidVolume5<<endl;
	cout<<"申卖价五: "<<pDepthMarketData->AskPrice5<<endl;
	cout<<"申卖量五: "<<pDepthMarketData->AskVolume5<<endl;
	cout<<"平均价格: "<<pDepthMarketData->AveragePrice<<endl;
	cout<<"昨持仓量: "<<pDepthMarketData->PreOpenInterest<<endl;
	cout<<"合约交易状态: "<<pDepthMarketData->InstrumentTradeStatus<<endl;
	cout<<"合约实时开仓限制: "<<pDepthMarketData->OpenRestriction<<endl;
}

void  CMdSpi:: DealBusiness(void* lpvoid)
{
	CMdSpi *lpMdSpi = (CMdSpi*)lpvoid;

	while(false == lpMdSpi->bStopDealBusiness)
	{

		cerr<<"------------------------------------------------"<<endl;
		cerr<<" [1] 订阅单腿行情                               "<<endl;
		cerr<<" [2] 取消订阅单腿行情                           "<<endl;
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
						printf("Please input ExchangeID （若想传空直接回车【Enter】）:");
						cin.clear();
						cin.ignore();
						cin.get(szTemp,260,'\n');
						if (szTemp[0] == 10)
							strcpy(stHSReqSingleMarket[0].ExchangeID,"" );
						else
							hs_strncpy(stHSReqSingleMarket[0].ExchangeID,szTemp,sizeof(stHSReqSingleMarket[0].ExchangeID));
						printf("Please input InstrumentID （若想传空直接回车【Enter】）:");
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
						printf("Please input ExchangeID （若想传空直接回车【Enter】）:");
						cin.clear();
						cin.ignore();
						cin.get(szTemp,260,'\n');
						if (szTemp[0] == 10)
							strcpy(stHSReqSingleMarket[0].ExchangeID,"" );
						else
							hs_strncpy(stHSReqSingleMarket[0].ExchangeID,szTemp,sizeof(stHSReqSingleMarket[0].ExchangeID));
						printf("Please input InstrumentID （若想传空直接回车【Enter】）:");
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
