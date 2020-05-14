
// NFDDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NFD.h"
#include "NFDDlg.h"
#include "afxdialogex.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNFDDlg �Ի���



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


// CNFDDlg ��Ϣ�������

BOOL CNFDDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	static CFont font;
	font.DeleteObject();
	font.CreatePointFont(220, _T("������"));
	mStockCode.SetFont(&font);//��������
	mStockCode.SetWindowText(_T(""));

	static CFont font2;
	font2.DeleteObject();
	font2.CreatePointFont(120, _T("������"));
	edtAsk.SetFont(&font2);
	edtBid.SetFont(&font2);
	edtAsk.SetWindowText("������");
	edtBid.SetWindowText("������");
	//edtText.SetWindowText("δ�ɽ�ί��10s���Զ�����");

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CNFDDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CNFDDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNFDDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// CDialogEx::OnOK();

	addInfo("��ʼ��ȡNFD.ini��������Ϣ");
	
	
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

	str.Format("�ýӿڵİ汾��[%s]", GetMdApiVersion());
	addInfo(str);

	addInfo("��������");
	lpMdApi = NewMdApi("./log/");
	lpMdSpi = new CMdSpi(lpMdApi);
	lpMdApi->RegisterSpi(lpMdSpi);
	lpMdApi->RegisterFront(address);
	int iRet = lpMdApi->Init(path+"\\license.dat");
	if (iRet != SDK_OK)
	{
		addInfo(lpMdApi->GetApiErrorMsg(iRet));
	}
	

	addInfo("���ӽ���");
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	exit(0);
	CDialogEx::OnCancel();
}


void CNFDDlg::OnBnClickedButton1()
{
	mStockCode.GetWindowTextA(code);
	CString exchange = lpTradeSpi->mapStockCode[code];
	if (exchange == "") {
		addInfo("����["+code+"]������,��ȷ�ϣ�");
	}
	
	lpMdSpi->subCode(code, exchange);
}


void CNFDDlg::OnBnClickedButton8()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	lpTradeSpi->queryFund();
}


void CNFDDlg::OnBnClickedButton9()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	lpTradeSpi->queryPosition();
}


void CNFDDlg::OnBnClickedButton2()
{

	if (lpTradeSpi->mapStockCode[code] == "") {
		addInfo("���벻���ڣ������޷���ȡ������Ϣ���޷�ί�У�");
		return;
	}
	
	if (bid < 0.0001 || ask < 0.0001) {
		addInfo("����δ��ȡ���޷�ί��");
		return;
	}
	//��	
	lpTradeSpi->sendOrder(code, ask, HS_D_Buy, HS_OF_Open);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CNFDDlg::OnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������

}


void CNFDDlg::OnUpdateEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// �������Խ� EM_SETEVENTMASK ��Ϣ���͵��ÿؼ���
	// ͬʱ�� ENM_UPDATE ��־�������㵽 lParam �����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������

}

void CNFDDlg::updatePrice(CString sCode, double dBid, double dAsk)
{

	if (code != sCode) {
		return;
	}

	if (bid != dBid || ask != dAsk) {
		CString str;
		str.Format("����仯[%s]=[%.4f %.4f]", code, dBid, dAsk);
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (lpTradeSpi->mapStockCode[code] == "") {
		addInfo("���벻���ڣ������޷���ȡ������Ϣ���޷�ί�У�");
		return;
	}

	if (bid < 0.0001 || ask < 0.0001) {
		addInfo("����δ��ȡ���޷�ί��");
		return;
	}
	//��ƽ��	
	lpTradeSpi->sendOrder(code, ask, HS_D_Buy, HS_OF_CloseToday);
}


void CNFDDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (lpTradeSpi->mapStockCode[code] == "") {
		addInfo("���벻���ڣ������޷���ȡ������Ϣ���޷�ί�У�");
		return;
	}

	if (bid < 0.0001 || ask < 0.0001) {
		addInfo("����δ��ȡ���޷�ί��");
		return;
	}
	//��ƽ	
	lpTradeSpi->sendOrder(code, ask, HS_D_Buy, HS_OF_Close);
}


void CNFDDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (lpTradeSpi->mapStockCode[code] == "") {
		addInfo("���벻���ڣ������޷���ȡ������Ϣ���޷�ί�У�");
		return;
	}

	if (bid < 0.0001 || ask < 0.0001) {
		addInfo("����δ��ȡ���޷�ί��");
		return;
	}
	//����
	lpTradeSpi->sendOrder(code, bid, HS_D_Sell, HS_OF_Open);
}


void CNFDDlg::OnBnClickedButton7()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (lpTradeSpi->mapStockCode[code] == "") {
		addInfo("���벻���ڣ������޷���ȡ������Ϣ���޷�ί�У�");
		return;
	}

	if (bid < 0.0001 || ask < 0.0001) {
		addInfo("����δ��ȡ���޷�ί��");
		return;
	}
	//��ƽ
	lpTradeSpi->sendOrder(code, bid, HS_D_Sell, HS_OF_Close);
}


void CNFDDlg::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (lpTradeSpi->mapStockCode[code] == "") {
		addInfo("���벻���ڣ������޷���ȡ������Ϣ���޷�ί�У�");
		return;
	}

	if (bid < 0.0001 || ask < 0.0001) {
		addInfo("����δ��ȡ���޷�ί��");
		return;
	}
	//��ƽ����
	lpTradeSpi->sendOrder(code, bid, HS_D_Sell, HS_OF_CloseToday);
}


void CNFDDlg::OnBnClickedButton10()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	lpTradeSpi->withdraw();
}
