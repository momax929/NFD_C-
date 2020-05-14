#include "stdafx.h"
#include "HSDataType.h"
#include "HSStruct.h"
#include "HSMdApi.h"
#include "public.h"

#pragma once

// 自定义类CMdSpi，通过继承（实现）CHSMdSpi，来自定义各种事件（包括连接成功、
// 连接断开、发送完成、收到数据等）发生时的回调方法
class CMdSpi : public CHSMdSpi
{

public:

	CMdSpi(CHSMdApi* lpObj)
	{
		lpUserApi = lpObj;
		bStopDealBusiness = false;
		iRequestId = 0;
	}
	///获取错误信息
	bool IsErrorRspInfo(CHSRspInfoField *pRspInfo);
	/// Description: 当客户端与交易后台开始建立通信连接，连接成功后此方法被回调。
	void OnFrontConnected();

	/// Description:当客户端与交易后台通信连接异常时，该方法被调用。
	/// Others     :通过GetApiErrorMsg(nResult)获取详细错误信息。
	void OnFrontDisconnected(int nResult);

	///620001_33330 订阅-期权单腿行情应答
	void OnRspDepthMarketDataSubscribe(CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///620002_33330 订阅取消-期权单腿行情应答
	void OnRspDepthMarketDataCancel(CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///620003_33330 主推-期权单腿行情应答
	void OnRtnDepthMarketData(CHSDepthMarketDataField *pDepthMarketData) ;
private:
	CHSMdApi* lpUserApi;
	CThread DealBusinessTrd;//处理业务线程句柄
	static void DealBusiness(void* lpvoid);//处理业务线程
	volatile bool bStopDealBusiness;//是否停止处理业务线程
	int iRequestId;//请求ID
public:
	void subCode(CString code, CString exchange);

};

