
// SerialMonitorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SerialMonitor.h"
#include "SerialMonitorDlg.h"
#include "afxdialogex.h"
#include <MMSystem.h>
#include <fstream>
#include "Serial.h"
#include <string>
#include "atlbase.h"
#include "atlconv.h"
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CSerialMonitorDlg dialog
CSerialMonitorDlg::CSerialMonitorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSerialMonitorDlg::IDD, pParent)
	, m_FastModeButton(0)
	, m_AZTEC(1)
	, m_CODABAR(1)
	, m_CODE_39(1)
	, m_CODE_93(1)
	, m_CODE_128(1)
	, m_DATA_MATRIX(1)
	, m_EAN_8(1)
	, m_EAN_13(1)
	, m_ITF(1)
	, m_MAXICODE(1)
	, m_PDF_417(1)
	, m_QR_CODE(1)
	, m_RSS_14(1)
	, m_RSS_EXPANDED(1)
	, m_UPC_A(1)
	, m_UPC_E(1)
	, m_UPC_EAN_EXTENSION(1)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_loop = true;
	m_isConnect = false;
	m_isFastMode = false;
}

void CSerialMonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PORT, m_PortCombobox);
	DDX_Control(pDX, IDC_COMBO_BAUDRATE, m_BaudrateCombobox);
	DDX_Control(pDX, IDC_BUTTON_CONNECT, m_ConnectButton);
	DDX_Control(pDX, ID_EDIT_SERIAL, m_Editor);
	DDX_Control(pDX, IDC_BUTTON_DISCONNECT, m_DisconnectButton);
	DDX_Control(pDX, IDC_CHECK_AUTOSCROLL, m_AutoScrollButton);
	DDX_Control(pDX, IDC_STATIC_FAST_TEXT, m_FastReceiveText);
	DDX_Control(pDX, IDC_RADIO1, m_NormalModeButton);
	DDX_Control(pDX, IDC_COMBO_SCAN, m_scan);
	DDX_Control(pDX, IDC_COMBO_DECODE, m_decode);
	DDX_Control(pDX, IDC_COMBO_COMMUNICATE, m_communicate);
	/*码制选择复选框*/
	DDX_Check(pDX, IDC_CHECKAZTEC, m_AZTEC);
	DDX_Check(pDX, IDC_CHECKCODABAR, m_CODABAR);
	DDX_Check(pDX, IDC_CHECKCODE_39, m_CODE_39);
	DDX_Check(pDX, IDC_CHECKCODE_93, m_CODE_93);
	DDX_Check(pDX, IDC_CHECKCODE_128, m_CODE_128);
	DDX_Check(pDX, IDC_CHECKDATA_MATRIX, m_DATA_MATRIX);
	DDX_Check(pDX, IDC_CHECKEAN_8, m_EAN_8);
	DDX_Check(pDX, IDC_CHECKEAN_13, m_EAN_13);
	DDX_Check(pDX, IDC_CHECKITF, m_ITF);
	DDX_Check(pDX, IDC_CHECKMAXICODE, m_MAXICODE);
	DDX_Check(pDX, IDC_CHECKPDF_417, m_PDF_417);
	DDX_Check(pDX, IDC_CHECKQR_CODE, m_QR_CODE);
	DDX_Check(pDX, IDC_CHECKRSS_14, m_RSS_14);
	DDX_Check(pDX, IDC_CHECKRSS_EXPANDED, m_RSS_EXPANDED);
	DDX_Check(pDX, IDC_CHECKUPC_A, m_UPC_A);
	DDX_Check(pDX, IDC_CHECKUPC_E, m_UPC_E);
	DDX_Check(pDX, IDC_CHECKUPC_EAN_EXTENSION, m_UPC_EAN_EXTENSION);
}

BEGIN_MESSAGE_MAP(CSerialMonitorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CSerialMonitorDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CSerialMonitorDlg::OnBnClickedCancel)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CSerialMonitorDlg::OnBnClickedButtonConnect)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_CHECK_AUTOSCROLL, &CSerialMonitorDlg::OnBnClickedCheckAutoscroll)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, &CSerialMonitorDlg::OnBnClickedButtonDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CSerialMonitorDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_RADIO1, &CSerialMonitorDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CSerialMonitorDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_BUTTONZbar4, &CSerialMonitorDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTONquickstart, &CSerialMonitorDlg::OnBnClickedButtonquickstart)
	ON_BN_CLICKED(IDC_BUTTONSETTING, &CSerialMonitorDlg::OnClickedButtonsetting)
END_MESSAGE_MAP()


// CSerialMonitorDlg message handlers

BOOL CSerialMonitorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_DisconnectButton.EnableWindow(FALSE);
	m_AutoScrollButton.SetCheck(1);
	m_NormalModeButton.SetCheck(1);
	
	for (int i = 0; i < 20; ++i)
	{
		TCHAR comName[32];
		wsprintf(comName, L"COM %d", i + 1);
		m_PortCombobox.InsertString(m_PortCombobox.GetCount(), comName);
	}
	m_PortCombobox.SetCurSel(0);

	int baudRate[] = {9600, 14400, 19200, 38400, 56000, 57600, 115200,3072000};
	for (int i = 0; i < ARRAYSIZE(baudRate); ++i)
	{
		TCHAR brateName[32];
		wsprintf(brateName, L"%d", baudRate[i]);
		m_BaudrateCombobox.InsertString(m_BaudrateCombobox.GetCount(), brateName);
	}
	m_BaudrateCombobox.SetCurSel(0);
	m_scan.SetCurSel(0);
	m_decode.SetCurSel(0);
	m_communicate.SetCurSel(0);

	// 券版汲沥 颇老捞 乐栏搁 佬绢柯促.
	// portnumber, baudrate甫 历厘茄促.
	std::ifstream iif("serialmonitor_conf.txt");
	if (iif.is_open())
	{
		int portNumberIndex, baudRateIndex;
		iif >> portNumberIndex;
		iif >> baudRateIndex;
		m_PortCombobox.SetCurSel(portNumberIndex);
		m_BaudrateCombobox.SetCurSel(baudRateIndex);
	}


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSerialMonitorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSerialMonitorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSerialMonitorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSerialMonitorDlg::OnBnClickedOk()
{
//	CDialogEx::OnOK();
}


void CSerialMonitorDlg::OnBnClickedCancel()
{
	m_loop = false;
	CDialogEx::OnCancel();
}


BOOL CSerialMonitorDlg::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	return CDialogEx::OnWndMsg(message, wParam, lParam, pResult);
}



void CSerialMonitorDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
}


// WindowProcedure MainLoop
void CSerialMonitorDlg::MainLoop()
{
	while (m_loop)
	{
		MSG msg;
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage(&msg, NULL, 0, 0))
			{
				break;
			}
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}

		const int curT = timeGetTime();
		static int oldT = curT;
		const int elapseT = curT - oldT;
		const float t = elapseT * 0.001f;
		oldT = curT;

		Process(t);

		Sleep(0);
	}
}
char* EncodeToUTF8(const char* mbcsStr)
{
	wchar_t* wideStr;
	char* utf8Str;
	int charLen;
	charLen = MultiByteToWideChar(CP_UTF8, 0, mbcsStr, -1, NULL, 0);
	wideStr = (wchar_t*)malloc(sizeof(wchar_t)*charLen);
	MultiByteToWideChar(CP_ACP, 0, mbcsStr, -1, wideStr, charLen);
	charLen = WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, NULL, 0, NULL, NULL);
	utf8Str = (char*)malloc(charLen);
	WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, utf8Str, charLen, NULL, NULL);
	free(wideStr);
	return utf8Str;
}
char* UTF8ToEncode(const char* mbcsStr)
{
	wchar_t*  wideStr;
	char* unicodeStr;
	int charLen;
	charLen = MultiByteToWideChar(CP_UTF8, 0, mbcsStr, -1, NULL, 0);
	wideStr = (wchar_t*)malloc(sizeof(wchar_t)*charLen);
	MultiByteToWideChar(CP_UTF8, 0, mbcsStr, -1, wideStr, charLen);
	charLen = WideCharToMultiByte(CP_ACP, 0, wideStr, -1, NULL, 0, NULL, NULL);
	unicodeStr = (char*)malloc(charLen);
	WideCharToMultiByte(CP_ACP, 0, wideStr, -1, unicodeStr, charLen, NULL, NULL);
	free(wideStr);
	return unicodeStr;
}

int CSerialMonitorDlg::AppendToLogAndScroll(char *str, COLORREF color)
{
	long nVisible = 0;
	long nInsertionPoint = 0;
	CHARFORMAT cf;

	// Initialize character format structure
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = CFM_COLOR;
	cf.dwEffects = 0; // To disable CFE_AUTOCOLOR
	cf.crTextColor = color;
	

	// Set insertion point to end of text
	nInsertionPoint = m_Editor.GetWindowTextLength();
	m_Editor.SetSel(nInsertionPoint, -1);

	// Set the character format
	m_Editor.SetSelectionCharFormat(cf);



	CString csunicode = NULL;
	//USES_CONVERSION;
	//char *utf8str = T2A(str);
	char *unicode = UTF8ToEncode(str);
	csunicode += unicode;
	m_Editor.ReplaceSel(csunicode);


	
	// Get number of currently visible lines or maximum number of visible lines
	// (We must call GetNumVisibleLines() before the first call to LineScroll()!)
	nVisible = GetNumVisibleLines(&m_Editor);

	// Now this is the fix of CRichEditCtrl's abnormal behaviour when used
	// in an application not based on dialogs. Checking the focus prevents
	// us from scrolling when the CRichEditCtrl does so automatically,
	// even though ES_AUTOxSCROLL style is NOT set.
	if (m_AutoScrollButton.GetCheck() && &m_Editor != m_Editor.GetFocus())
	{
		m_Editor.LineScroll(INT_MAX);
		m_Editor.LineScroll(1 - nVisible);
	}

	const int maximumLine = 100;
	if (m_Editor.GetLineCount() > maximumLine)
	{
		long nFirstChar = m_Editor.CharFromPos(CPoint(0, 0));
		m_Editor.SetSel(0, nFirstChar);
		m_Editor.ReplaceSel(L"");
	}

	return 0;
}


//http://www.codeproject.com/Articles/12093/Using-RichEditCtrl-to-Display-Formatted-Logs
int CSerialMonitorDlg::GetNumVisibleLines(CRichEditCtrl* pCtrl)
{
	CRect rect;
	long nFirstChar, nLastChar;
	long nFirstLine, nLastLine;

	// Get client rect of rich edit control
	pCtrl->GetClientRect(rect);

	// Get character index close to upper left corner
	nFirstChar = pCtrl->CharFromPos(CPoint(0, 0));

	// Get character index close to lower right corner
	nLastChar = pCtrl->CharFromPos(CPoint(rect.right, rect.bottom));
	if (nLastChar < 0)
	{
		nLastChar = pCtrl->GetTextLength();
	}

	// Convert to lines
	nFirstLine = pCtrl->LineFromChar(nFirstChar);
	nLastLine = pCtrl->LineFromChar(nLastChar);

	return (nLastLine - nFirstLine);
}


// Serial Transmitt/Receive Process
void CSerialMonitorDlg::Process(float deltaT)
{
	if (!m_isConnect) return;
	char data [1025];
	int len = m_Serial.ReadData(&data, 1024);
	if (0 >= len) return;

	/*if (m_isFastMode)
	{
		static CString str;
		str += data;
		// CR Return 老 锭父 诀单捞飘 等促.
		if (data == '\n')
		{
			m_FastReceiveText.SetWindowTextW(str);
			str = "";
		}
	}*/
	else
	{
		data[len] = '\0';
		AppendToLogAndScroll(data, RGB(0,0,0));
	}

}


// Connect Serial port
void CSerialMonitorDlg::OnBnClickedButtonConnect()
{
	if (m_isConnect)
		return;

	CString port;
	m_PortCombobox.GetWindowTextW(port);
	CString baudRate;
	m_BaudrateCombobox.GetWindowTextW(baudRate);

	int portNumber = 0;
	const int spaceIdx = port.Find(L" ");
	if (spaceIdx > 0)
		portNumber = _wtoi(&port.GetBuffer()[spaceIdx]);

	// Open Serial Port
	if (m_Serial.Open(portNumber, _wtoi(baudRate)))
	{
		m_isConnect = true;
		m_ConnectButton.EnableWindow(FALSE);
		m_DisconnectButton.EnableWindow(TRUE);

		// portnumber, baudrate甫 历厘茄促.
		std::ofstream of("serialmonitor_conf.txt");
		if (of.is_open())
		{
			of << m_PortCombobox.GetCurSel() << std::endl << m_BaudrateCombobox.GetCurSel();
		}
	}
	else
	{
		AfxMessageBox(L"Connect Error!! [" + port + L"]");
	}
}


void CSerialMonitorDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	
}


void CSerialMonitorDlg::OnBnClickedCheckAutoscroll()
{

}


void CSerialMonitorDlg::OnBnClickedButtonDisconnect()
{
	if (m_isConnect)
	{
		m_isConnect = false;
		m_Serial.Close();
		m_ConnectButton.EnableWindow(TRUE);
		m_DisconnectButton.EnableWindow(FALSE);
	}
}


void CSerialMonitorDlg::OnBnClickedButtonClear()
{
	m_Editor.SetSel(0, m_Editor.GetTextLength());
	m_Editor.ReplaceSel(L"");
}


void CSerialMonitorDlg::OnBnClickedRadio1()
{
	m_isFastMode = false;
}


void CSerialMonitorDlg::OnBnClickedRadio2()
{
	m_isFastMode = true;
}

int CSerialMonitorDlg::get_crc16( unsigned char *bufData,  int buflen)
{
	int ret = 0;
	unsigned short CRC = 0xffff;
	unsigned short POLYNOMIAL = 0xa001;
	int i, j;


	if (bufData == NULL )
	{
		return -1;
	}

	if (buflen == 0)
	{
		return ret;
	}
	for (i = 0; i < buflen; i++)
	{
		CRC ^= bufData[i];
		for (j = 0; j < 8; j++)
		{
			if ((CRC & 0x0001) != 0)
			{
				CRC >>= 1;
				CRC ^= POLYNOMIAL;
			}
			else
			{
				CRC >>= 1;
			}
		}
	}
	//	unsigned char *tmp = (unsigned char*)&CRC;
	//	bufData[buflen] = *tmp;
	//	bufData[buflen + 1] = *(tmp + 1);
	//bufData[buflen] = (unsigned char)&CRC;
	bufData[buflen] = (unsigned char)(CRC & 0x00ff);
	bufData[buflen+1] = (unsigned char)(CRC >> 8);
	return ret;
}


void CSerialMonitorDlg::OnBnClickedButtonStop()
{
	unsigned char sendpackage[10];
	sendpackage[0] = 0x02;
	sendpackage[1] = 0x03;
	sendpackage[2] = 0x00;
	sendpackage[3] = 0x00;
	sendpackage[4] = 0x00;
	sendpackage[5] = 0x00;
	sendpackage[6] = 0x00;
	sendpackage[7] = 0x00;
	get_crc16(sendpackage, 8);
	unsigned char *send = sendpackage;// 等价于send = &sendpackage[0]
	m_Serial.SendData(send, 10);// TODO: 在此添加控件通知处理程序代码
}


void CSerialMonitorDlg::OnBnClickedButtonquickstart()
{
	unsigned char sendpackage[10];
	sendpackage[0] = 0x02;
	sendpackage[1] = 0x00;
	sendpackage[2] = 0x00;
	sendpackage[3] = 0x00;
	sendpackage[4] = 0x00;
	sendpackage[5] = 0x00;
	sendpackage[6] = 0x00;
	sendpackage[7] = 0x00;
	CString scanmode;
	m_scan.GetWindowTextW(scanmode);
	if (scanmode == "ONCE") {
		sendpackage[2] = 0x01;
	}
	if (scanmode == "CONTINUE") {
		sendpackage[2] = 0x02;
	}
	get_crc16(sendpackage, 8);
	unsigned char *send = sendpackage;// 等价于send = &sendpackage[0]
	m_Serial.SendData(send, 10);// TODO: 在此添加控件通知处理程序代码
}

void BitToByte(unsigned char*Out, bool*In, int bits)//////位到字节的转换函数
{
	int i;
	for (i = 0; i < (bits / 8); i++) Out[i] = 0;
	for (i = 0; i < bits; i++) 
		Out[i / 8] = Out[i / 8] | (In[i] << (7-(i % 8)));
}
void CSerialMonitorDlg::OnClickedButtonsetting()
{
	UpdateData(TRUE);
	unsigned char out[5];
	bool in[32] = { m_AZTEC,m_CODABAR,m_CODE_39,m_CODE_93,m_CODE_128,m_DATA_MATRIX,m_EAN_8,m_EAN_13,
		m_ITF,m_MAXICODE, m_PDF_417 ,m_QR_CODE ,m_RSS_14 ,m_RSS_EXPANDED ,m_UPC_A ,m_UPC_E ,m_UPC_EAN_EXTENSION };
	BitToByte(out, in, 32);
	unsigned char sendpackage[10];
	sendpackage[0] = 0x02;
	sendpackage[1] = 0x01;
	sendpackage[2] = out[0];
	sendpackage[3] = out[1];
	sendpackage[4] = out[2];
	sendpackage[5] = out[3];
	sendpackage[6] = 0x00;
	sendpackage[7] = 0x00;
	CString decodemode;
	m_decode.GetWindowTextW(decodemode);
	if (decodemode == "ZXing") {
		sendpackage[6] = 0x01;
	}
	if (decodemode == "Zbar") {
		sendpackage[6] = 0x02;
	}
	CString communication;
	m_communicate.GetWindowTextW(communication);
	if (communication == "USB") {
		sendpackage[7] = 0x01;
	}
	if (communication == "UART") {
		sendpackage[7] = 0x02;
	}
	get_crc16(sendpackage, 8);
	unsigned char *send = sendpackage;// 等价于send = &sendpackage[0]
	m_Serial.SendData(send, 10);
	// TODO: 在此添加控件通知处理程序代码
}
