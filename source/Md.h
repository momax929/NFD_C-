#include "stdafx.h"
#include "HSDataType.h"
#include "HSStruct.h"
#include "HSMdApi.h"
#include "public.h"

#pragma once

// �Զ�����CMdSpi��ͨ���̳У�ʵ�֣�CHSMdSpi�����Զ�������¼����������ӳɹ���
// ���ӶϿ���������ɡ��յ����ݵȣ�����ʱ�Ļص�����
class CMdSpi : public CHSMdSpi
{

public:

	CMdSpi(CHSMdApi* lpObj)
	{
		lpUserApi = lpObj;
		bStopDealBusiness = false;
		iRequestId = 0;
	}
	///��ȡ������Ϣ
	bool IsErrorRspInfo(CHSRspInfoField *pRspInfo);
	/// Description: ���ͻ����뽻�׺�̨��ʼ����ͨ�����ӣ����ӳɹ���˷������ص���
	void OnFrontConnected();

	/// Description:���ͻ����뽻�׺�̨ͨ�������쳣ʱ���÷��������á�
	/// Others     :ͨ��GetApiErrorMsg(nResult)��ȡ��ϸ������Ϣ��
	void OnFrontDisconnected(int nResult);

	///620001_33330 ����-��Ȩ��������Ӧ��
	void OnRspDepthMarketDataSubscribe(CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///620002_33330 ����ȡ��-��Ȩ��������Ӧ��
	void OnRspDepthMarketDataCancel(CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///620003_33330 ����-��Ȩ��������Ӧ��
	void OnRtnDepthMarketData(CHSDepthMarketDataField *pDepthMarketData) ;
private:
	CHSMdApi* lpUserApi;
	CThread DealBusinessTrd;//����ҵ���߳̾��
	static void DealBusiness(void* lpvoid);//����ҵ���߳�
	volatile bool bStopDealBusiness;//�Ƿ�ֹͣ����ҵ���߳�
	int iRequestId;//����ID
public:
	void subCode(CString code, CString exchange);

};

