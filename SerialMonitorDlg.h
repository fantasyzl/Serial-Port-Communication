
// SerialMonitorDlg.h : header file
//

#pragma once
#include "Serial.h"
#include "afxwin.h"
#include "afxcmn.h"

// CSerialMonitorDlg dialog
class CSerialMonitorDlg : public CDialogEx
{
// Construction
public:
	CSerialMonitorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SERIALMONITOR_DIALOG };
	CString UTF8Convert(CString &str, int sourceCodepage, int targetCodepage);
	void MainLoop();
	int get_crc16(unsigned char *bufData, int buflen);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	void Process(float deltaT);
	int CSerialMonitorDlg::AppendToLogAndScroll(char* str, COLORREF color);
	int CSerialMonitorDlg::GetNumVisibleLines(CRichEditCtrl* pCtrl);


// Implementation
protected:
	HICON m_hIcon;
	bool m_loop;
	CSerial m_Serial;
	bool m_isConnect;
	bool m_isFastMode;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	afx_msg void OnDestroy();
	CComboBox m_PortCombobox;
	CComboBox m_BaudrateCombobox;
	afx_msg void OnBnClickedButtonConnect();
	CButton m_ConnectButton;
	CButton m_DisconnectButton;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheckAutoscroll();
	CRichEditCtrl m_Editor;
	afx_msg void OnBnClickedButtonDisconnect();

	CButton m_AutoScrollButton;
	afx_msg void OnBnClickedButtonClear();
	CStatic m_FastReceiveText;
	CButton m_NormalModeButton;
	int m_FastModeButton;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonstart();
	afx_msg void OnBnClickedButtonstart2();
	afx_msg void OnBnClickedButtonzxing();
	afx_msg void OnBnClickedButtonzbar();
	afx_msg void OnBnClickedButtonzxing2();
	afx_msg void OnCbnSelchangeComboPort();
	CComboBox m_scan;
	CComboBox m_decode;
	CComboBox m_communicate;
	afx_msg void OnCbnSelchangeComboScan();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonquickstart();
//	BOOL mAZTEC;
	BOOL m_AZTEC;
	BOOL m_CODABAR;
	BOOL m_CODE_128;
	BOOL m_CODE_39;
	BOOL m_CODE_93;
	BOOL m_DATA_MATRIX;
	BOOL m_EAN_13;
	BOOL m_EAN_8;
	BOOL m_ITF;
	BOOL m_MAXICODE;
	BOOL m_PDF_417;
	BOOL m_QR_CODE;
	BOOL m_RSS_14;
	BOOL m_RSS_EXPANDED;
//	BOOL m_UPC_A;
	BOOL m_UPC_A;
	BOOL m_UPC_E;
	BOOL m_UPC_EAN_EXTENSION;
	afx_msg void OnClickedButtonsetting();
};
