
// NFDDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "NFD.h"
#include "NFDDlg.h"
#include "afxdialogex.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNFDDlg 对话框



CNFDDlg::CNFDDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_NFD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNFDDlg::addInfo(CString str)
{
	lbMsg.InsertString(0, str);
}


void CNFDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, lbMsg);
	DDX_Control(pDX, IDC_EDIT1, mStockCode);
	DDX_Control(pDX, IDC_EDIT3, edtBid);
	DDX_Control(pDX, IDC_EDIT2, edtAsk);



}

BEGIN_MESSAGE_MAP(CNFDDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CNFDDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CNFDDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CNFDDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON8, &CNFDDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CNFDDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON2, &CNFDDlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT1, &CNFDDlg::OnChangeEdit1)
	ON_EN_UPDATE(IDC_EDIT1, &CNFDDlg::OnUpdateEdit1)
	ON_BN_CLICKED(IDC_BUTTON3, &CNFDDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CNFDDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CNFDDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON7, &CNFDDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON6, &CNFDDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON10, &CNFDDlg::OnBnClickedButton10)
END_MESSAGE_MAP()


// CNFDDlg 消息处理程序

BOOL CNFDDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	static CFont font;
	font.DeleteObject();
	font.CreatePointFont(220, _T("新宋体"));
	mStockCode.SetFont(&font);//设置字体
	mStockCode.SetWindowText(_T(""));

	static CFont font2;
	font2.DeleteObject();
	font2.CreatePointFont(120, _T("新宋体"));
	edtAsk.SetFont(&font2);
	edtBid.SetFont(&font2);
	edtAsk.SetWindowText("无行情");
	edtBid.SetWindowText("无行情");
	//edtText.SetWindowText("未成交委托10s后自动撤单");

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CNFDDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CNFDDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNFDDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	// CDialogEx::OnOK();

	addInfo("开始读取NFD.ini的配置信息");
	
	
	CString path = AfxGetApp()->m_pszHelpFilePath;
	CString fn = AfxGetApp()->m_pszExeName;
	path = path.Left(path.GetLength() - fn.GetLength() - 4);	
	fn = path + "\\NFD.ini";
	
	//WritePrivateProfileString("INFO", "test", "Man", fn);
	
	GetPrivateProfileString("INFO", "account_id", "", account_id.GetBuffer(255), 255, fn);
	GetPrivateProfileString("INFO", "password", "", password.GetBuffer(255), 255, fn);
	GetPrivateProfileString("INFO", "address", "", address.GetBuffer(255), 255, fn);
	CString str;
	str.Format("account=[%s] address=[%s]", account_id, address);
	addInfo(str);

	str.Format("该接口的版本是[%s]", GetMdApiVersion());
	addInfo(str);

	addInfo("连接行情");
	lpMdApi = NewMdApi("./log/");
	lpMdSpi = new CMdSpi(lpMdApi);
	lpMdApi->RegisterSpi(lpMdSpi);
	lpMdApi->RegisterFront(address);
	int iRet = lpMdApi->Init(path+"\\license.dat");
	if (iRet != SDK_OK)
	{
		addInfo(lpMdApi->GetApiErrorMsg(iRet));
	}
	

	addInfo("连接交易");
	lpTradeApi = NewTradeApi("./log/");
	lpTradeSpi = new CMyTradeSpi(lpTradeApi);
	lpTradeApi->RegisterSpi(lpTradeSpi);
	lpTradeApi->RegisterFront(address);
	iRet = lpTradeApi->Init(path + "\\license.dat");
	if (iRet != SDK_OK)
	{
		printf(lpTradeApi->GetApiErrorMsg(iRet));
	}


	
}


void CNFDDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
	CDialogEx::OnCancel();
}


void CNFDDlg::OnBnClickedButton1()
{
	mStockCode.GetWindowTextA(code);
	CString exchange = lpTradeSpi->mapStockCode[code];
	if (exchange == "") {
		addInfo("代码["+code+"]不存在,请确认！");
	}
	
	lpMdSpi->subCode(code, exchange);
}


void CNFDDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	lpTradeSpi->queryFund();
}


void CNFDDlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	lpTradeSpi->queryPosition();
}


void CNFDDlg::OnBnClickedButton2()
{

	if (lpTradeSpi->mapStockCode[code] == "") {
		addInfo("代码不存在，或者无法获取代码信息，无法委托！");
		return;
	}
	
	if (bid < 0.0001 || ask < 0.0001) {
		addInfo("行情未获取，无法委托");
		return;
	}
	//买开	
	lpTradeSpi->sendOrder(code, ask, HS_D_Buy, HS_OF_Open);
	// TODO: 在此添加控件通知处理程序代码
}


void CNFDDlg::OnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

}


void CNFDDlg::OnUpdateEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数，以将 EM_SETEVENTMASK 消息发送到该控件，
	// 同时将 ENM_UPDATE 标志“或”运算到 lParam 掩码中。

	// TODO:  在此添加控件通知处理程序代码

}

void CNFDDlg::updatePrice(CString sCode, double dBid, double dAsk)
{

	if (code != sCode) {
		return;
	}

	if (bid != dBid || ask != dAsk) {
		CString str;
		str.Format("行情变化[%s]=[%.4f %.4f]", code, dBid, dAsk);
		addInfo(str);
	}

	if (sCode == code) {
		bid = dBid;
		ask = dAsk;
	}

	CString tmp, text;
	tmp.Format("%.4f", ask);
	edtAsk.SetWindowTextA(tmp);

	tmp.Format("%.4f", bid);
	edtBid.SetWindowTextA(tmp);


}


void CNFDDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	if (lpTradeSpi->mapStockCode[code] == "") {
		addInfo("代码不存在，或者无法获取代码信息，无法委托！");
		return;
	}

	if (bid < 0.0001 || ask < 0.0001) {
		addInfo("行情未获取，无法委托");
		return;
	}
	//买平今	
	lpTradeSpi->sendOrder(code, ask, HS_D_Buy, HS_OF_CloseToday);
}


void CNFDDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	if (lpTradeSpi->mapStockCode[code] == "") {
		addInfo("代码不存在，或者无法获取代码信息，无法委托！");
		return;
	}

	if (bid < 0.0001 || ask < 0.0001) {
		addInfo("行情未获取，无法委托");
		return;
	}
	//买平	
	lpTradeSpi->sendOrder(code, ask, HS_D_Buy, HS_OF_Close);
}


void CNFDDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	if (lpTradeSpi->mapStockCode[code] == "") {
		addInfo("代码不存在，或者无法获取代码信息，无法委托！");
		return;
	}

	if (bid < 0.0001 || ask < 0.0001) {
		addInfo("行情未获取，无法委托");
		return;
	}
	//卖开
	lpTradeSpi->sendOrder(code, bid, HS_D_Sell, HS_OF_Open);
}


void CNFDDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	if (lpTradeSpi->mapStockCode[code] == "") {
		addInfo("代码不存在，或者无法获取代码信息，无法委托！");
		return;
	}

	if (bid < 0.0001 || ask < 0.0001) {
		addInfo("行情未获取，无法委托");
		return;
	}
	//卖平
	lpTradeSpi->sendOrder(code, bid, HS_D_Sell, HS_OF_Close);
}


void CNFDDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	if (lpTradeSpi->mapStockCode[code] == "") {
		addInfo("代码不存在，或者无法获取代码信息，无法委托！");
		return;
	}

	if (bid < 0.0001 || ask < 0.0001) {
		addInfo("行情未获取，无法委托");
		return;
	}
	//卖平昨天
	lpTradeSpi->sendOrder(code, bid, HS_D_Sell, HS_OF_CloseToday);
}


void CNFDDlg::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	lpTradeSpi->withdraw();
}
