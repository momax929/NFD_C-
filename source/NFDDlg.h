
// NFDDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "Md.h"
#include "Trade.h"

// CNFDDlg �Ի���
class CNFDDlg : public CDialogEx
{
// ����
public:
	CNFDDlg(CWnd* pParent = NULL);	// ��׼���캯��
	

	void addInfo(CString str);
	
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NFD_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CListBox lbMsg;

	afx_msg void OnBnClickedCancel();

	CHSMdApi* lpMdApi;
	CMdSpi* lpMdSpi;

	CEdit mStockCode;
	afx_msg void OnBnClickedButton1();
	CEdit edtBid;
	CEdit edtAsk;
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	//CEdit edtText;
	afx_msg void OnBnClickedButton2();

	CString code;
	double ask;
	double bid;
	afx_msg void OnChangeEdit1();
	afx_msg void OnUpdateEdit1();
	void updatePrice(CString sCode, double dBid, double dAsk);
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton10();
};
