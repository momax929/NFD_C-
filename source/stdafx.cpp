
// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// NFD.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"

CNFDDlg* mainDlg;
CString account_id;
CString password;
CString address;

CHSTradeApi* lpTradeApi;
CMyTradeSpi* lpTradeSpi;
void addInfo(CString str)
{
	mainDlg->addInfo(str);
}
