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

// �Զ�����CTradeSpi��ͨ���̳У�ʵ�֣�CHSTradeSpi�����Զ�������¼����������ӳɹ���
// ���ӶϿ���������ɡ��յ����ݵȣ�����ʱ�Ļص�����

class CMyTradeSpi : public CHSTradeSpi
{

public:

	CMyTradeSpi(CHSTradeApi* lpObj)
	{
		lpUserApi = lpObj;
		bStopDealBusiness = false;
		iRequestId = 0;
	}
	/// Description: ���ͻ����뽻�׺�̨��ʼ����ͨ�����ӣ����ӳɹ���˷������ص���
	void OnFrontConnected();

	/// Description:���ͻ����뽻�׺�̨ͨ�������쳣ʱ���÷��������á�
	/// Others     :ͨ��GetApiErrorMsg(nResult)��ȡ��ϸ������Ϣ��
	void OnFrontDisconnected(int nResult);

	bool IsErrorRspInfo(CHSRspInfoField *pRspInfo);
	//336800�ͻ���¼
	void  OnRspUserLogin(CHSRspUserLoginField *pRspUserLogin, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336801�������
	void  OnRspUserPasswordUpdate(CHSRspUserPasswordUpdateField *pRspUserPasswordUpdate, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336812����¼��
	void  OnRspErrorOrderInsert(CHSRspOrderInsertField *pRspOrderInsert, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336813����
	void  OnRspOrderAction(CHSRspOrderActionField *pRspOrderAction, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336814��Ȩ¼��
	void  OnRspErrorExerciseOrderInsert(CHSRspExerciseOrderInsertField *pRspExerciseOrderInsert, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336815��Ȩ����
	void  OnRspExerciseOrderAction(CHSRspExerciseOrderActionField *pRspExerciseOrderAction, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336913����¼��
	void  OnRspErrorLockInsert(CHSRspLockInsertField *pRspLockInsert, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336817ѯ��¼��
	void  OnRspForQuoteInsert(CHSRspForQuoteInsertField *pRspForQuoteInsert, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336818�������¼��
	void  OnRspErrorCombActionInsert(CHSRspCombActionInsertField *pRspCombActionInsert, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336810��󱨵�������ȡ
	void  OnRspQueryMaxOrderVolume(CHSRspQueryMaxOrderVolumeField *pRspQueryMaxOrderVolume, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336912������������ȡ
	void  OnRspQueryLockVolume(CHSRspQueryLockVolumeField *pRspQueryLockVolume, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336819����Ȩ������ȡ
	void  OnRspQueryExerciseVolume(CHSRspQueryExerciseVolumeField *pRspQueryExerciseVolume, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336851�ֲֻ��ܲ�ѯ
	void  OnRspQryPosition(CHSRspQryPositionField *pRspQryPosition, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336850�ʽ��˻���ѯ
	void  OnRspQryTradingAccount(CHSRspQryTradingAccountField *pRspQryTradingAccount, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336853������ѯ
	void  OnRspQryOrder(CHSOrderField *pRspQryOrder, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336854�ɽ���ѯ
	void  OnRspQryTrade(CHSTradeField *pRspQryTrade, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336855��Ȩ��ѯ
	void  OnRspQryExercise(CHSExerciseField *pRspQryExercise, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336856������ѯ
	void  OnRspQryLock(CHSLockField *pRspQryLock, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336857������ϲ�ѯ
	void  OnRspQryCombAction(CHSCombActionField *pRspQryCombAction, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336852��ϳֲ���ϸ��ѯ
	void  OnRspQryPositionCombineDetail(CHSRspQryPositionCombineDetailField *pRspQryPositionCombineDetail, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336858��Լ��Ϣ��ѯ
	void  OnRspQryInstrument(CHSRspQryInstrumentField *pRspQryInstrument, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336910����ȱ�ڲ�ѯ
	void  OnRspQryCoveredShort(CHSRspQryCoveredShortField *pRspQryCoveredShort, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336911��Ȩָ�ɲ�ѯ
	void  OnRspQryExerciseAssign(CHSRspQryExerciseAssignField *pRspQryExerciseAssign, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336900����ת��
	void  OnRspTransfer(CHSRspTransferField *pRspTransfer, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336901����ת�˲�ѯ
	void  OnRspQryTransfer(CHSRspQryTransferField *pRspQryTransfer, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336902��������ѯ
	void  OnRspQueryBankBalance(CHSRspQueryBankBalanceField *pRspQueryBankBalance, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336903�����˻���ѯ
	void  OnRspQueryBankAccount(CHSRspQueryBankAccountField *pRspQueryBankAccount, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	//336990�ͻ��˵���ѯ
	void  OnRspQueryBillContent(CHSRspQueryBillContentField *pRspQueryBillContent, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336991�ͻ��˵�ȷ��
	void  OnRspBillConfirm(CHSRspBillConfirmField *pRspBillConfirm, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336860��֤���ѯ
	void  OnRspQryMargin(CHSRspQryMarginField *pRspQryMargin, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336861�����Ѳ�ѯ
	void  OnRspQryCommission(CHSRspQryCommissionField *pRspQryCommission, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336863�ֲ���ϸ��ѯ
	void  OnRspQryPositionDetail(CHSRspQryPositionDetailField *pRspQryPositionDetail, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336865���ʲ�ѯ
	void  OnRspQryExchangeRate(CHSRspQryExchangeRateField *pRspQryExchangeRate, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//336862���͹�˾���ò�����ѯ
	void  OnRspQrySysConfig(CHSRspQrySysConfigField *pRspQrySysConfig, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	/// Description:�����ѯ
	void OnRspQryDepthMarketData(CHSDepthMarketDataField *pRspQryDepthMarketData, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	/// Description: ����-�ɽ��ر�
	void OnRtnTrade(CHSTradeField *pRtnTrade) ;

	/// Description: ����-�����ر�
	void OnRtnOrder(CHSOrderField *pRtnOrder) ;

	/// Description: ����-��Ȩ
	void OnRtnExercise(CHSExerciseField *pRtnExercise) ;

	/// Description: ����-�������
	void OnRtnCombAction(CHSCombActionField *pRtnCombAction) ;

	/// Description: ����-����
	void OnRtnLock(CHSLockField *pRtnLock) ;

private:
	CHSTradeApi* lpUserApi;
	CThread DealBusinessTrd;//����ҵ���߳̾��
	static void DealBusiness(void* lpvoid);//����ҵ���߳�
	volatile bool bStopDealBusiness;//�Ƿ�ֹͣ����ҵ���߳�
	int iRequestId;//����ID
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