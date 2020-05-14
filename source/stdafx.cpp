
// stdafx.cpp : 只包括标准包含文件的源文件
// NFD.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

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
