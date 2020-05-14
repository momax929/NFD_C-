#include "stdafx.h"
#include "HSDataType.h"
#include "HSStruct.h"
#include "HSTradeApi.h"
#include "public.h"
#include<iomanip>
#include <fstream> 
#include <string>
#include <map>

#pragma once

// 自定义类CTradeSpi，通过继承（实现）CHSTradeSpi，来自定义各种事件（包括连接成功、
// 连接断开、发送完成、收到数据等）发生时的回调方法

class CMyTradeSpi : public CHSTradeSpi
{

public:

	CMyTradeSpi(CHSTradeApi* lpObj)
	{
		lpUserApi = lpObj;
		bStopDealBusiness = false;
		iRequestId = 0;
	}
	/// Description: 当客户端与交易后台开始建立通信连接，连接成功后此方法被回调。
	void OnFrontConnected();

	/// Description:当客户端与交易后台通信连接异常时，该方法被调用。
	/// Others     :通过GetApiErrorMsg(nResult)获取详细错误信息。
	void OnFrontDisconnected(int nResult);

	bool IsErrorRspInfo(CHSRspInfoField *pRspInfo);
	//336800客户登录
	void  OnRspUserLogin(CHSRspUserLoginField *pRspUserLogin, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336801密码更改
	void  OnRspUserPasswordUpdate(CHSRspUserPasswordUpdateField *pRspUserPasswordUpdate, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336812报单录入
	void  OnRspErrorOrderInsert(CHSRspOrderInsertField *pRspOrderInsert, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336813撤单
	void  OnRspOrderAction(CHSRspOrderActionField *pRspOrderAction, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336814行权录入
	void  OnRspErrorExerciseOrderInsert(CHSRspExerciseOrderInsertField *pRspExerciseOrderInsert, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336815行权撤单
	void  OnRspExerciseOrderAction(CHSRspExerciseOrderActionField *pRspExerciseOrderAction, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336913锁定录入
	void  OnRspErrorLockInsert(CHSRspLockInsertField *pRspLockInsert, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336817询价录入
	void  OnRspForQuoteInsert(CHSRspForQuoteInsertField *pRspForQuoteInsert, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336818申请组合录入
	void  OnRspErrorCombActionInsert(CHSRspCombActionInsertField *pRspCombActionInsert, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336810最大报单数量获取
	void  OnRspQueryMaxOrderVolume(CHSRspQueryMaxOrderVolumeField *pRspQueryMaxOrderVolume, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336912可锁定数量获取
	void  OnRspQueryLockVolume(CHSRspQueryLockVolumeField *pRspQueryLockVolume, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336819可行权数量获取
	void  OnRspQueryExerciseVolume(CHSRspQueryExerciseVolumeField *pRspQueryExerciseVolume, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336851持仓汇总查询
	void  OnRspQryPosition(CHSRspQryPositionField *pRspQryPosition, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336850资金账户查询
	void  OnRspQryTradingAccount(CHSRspQryTradingAccountField *pRspQryTradingAccount, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336853报单查询
	void  OnRspQryOrder(CHSOrderField *pRspQryOrder, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336854成交查询
	void  OnRspQryTrade(CHSTradeField *pRspQryTrade, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336855行权查询
	void  OnRspQryExercise(CHSExerciseField *pRspQryExercise, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336856锁定查询
	void  OnRspQryLock(CHSLockField *pRspQryLock, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336857申请组合查询
	void  OnRspQryCombAction(CHSCombActionField *pRspQryCombAction, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336852组合持仓明细查询
	void  OnRspQryPositionCombineDetail(CHSRspQryPositionCombineDetailField *pRspQryPositionCombineDetail, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336858合约信息查询
	void  OnRspQryInstrument(CHSRspQryInstrumentField *pRspQryInstrument, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336910备兑缺口查询
	void  OnRspQryCoveredShort(CHSRspQryCoveredShortField *pRspQryCoveredShort, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336911行权指派查询
	void  OnRspQryExerciseAssign(CHSRspQryExerciseAssignField *pRspQryExerciseAssign, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336900银行转账
	void  OnRspTransfer(CHSRspTransferField *pRspTransfer, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336901银行转账查询
	void  OnRspQryTransfer(CHSRspQryTransferField *pRspQryTransfer, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336902银行余额查询
	void  OnRspQueryBankBalance(CHSRspQueryBankBalanceField *pRspQueryBankBalance, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336903银行账户查询
	void  OnRspQueryBankAccount(CHSRspQueryBankAccountField *pRspQueryBankAccount, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	//336990客户账单查询
	void  OnRspQueryBillContent(CHSRspQueryBillContentField *pRspQueryBillContent, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336991客户账单确认
	void  OnRspBillConfirm(CHSRspBillConfirmField *pRspBillConfirm, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336860保证金查询
	void  OnRspQryMargin(CHSRspQryMarginField *pRspQryMargin, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336861手续费查询
	void  OnRspQryCommission(CHSRspQryCommissionField *pRspQryCommission, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336863持仓明细查询
	void  OnRspQryPositionDetail(CHSRspQryPositionDetailField *pRspQryPositionDetail, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336865汇率查询
	void  OnRspQryExchangeRate(CHSRspQryExchangeRateField *pRspQryExchangeRate, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336862经纪公司配置参数查询
	void  OnRspQrySysConfig(CHSRspQrySysConfigField *pRspQrySysConfig, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	/// Description:行情查询
	void OnRspQryDepthMarketData(CHSDepthMarketDataField *pRspQryDepthMarketData, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	/// Description: 主推-成交回报
	void OnRtnTrade(CHSTradeField *pRtnTrade) ;

	/// Description: 主推-报单回报
	void OnRtnOrder(CHSOrderField *pRtnOrder) ;

	/// Description: 主推-行权
	void OnRtnExercise(CHSExerciseField *pRtnExercise) ;

	/// Description: 主推-申请组合
	void OnRtnCombAction(CHSCombActionField *pRtnCombAction) ;

	/// Description: 主推-锁定
	void OnRtnLock(CHSLockField *pRtnLock) ;

private:
	CHSTradeApi* lpUserApi;
	CThread DealBusinessTrd;//处理业务线程句柄
	static void DealBusiness(void* lpvoid);//处理业务线程
	volatile bool bStopDealBusiness;//是否停止处理业务线程
	int iRequestId;//请求ID
	HSSessionID sessionID = 0;
	CString sOrderRef = "";
	//CMyTradeSpi *lpTradeSpi;
public:
	map<CString, CString> mapStockCode;
	void login();
	void queryFund();
	void queryPosition();
	void queryStockCode();
	int sendOrder(CString code, double price, HSDirection direction, HSOffsetFlag offset);
	void withdraw();
};