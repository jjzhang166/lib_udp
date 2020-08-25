
// mfc_demoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mfc_demo.h"
#include "mfc_demoDlg.h"
#include "afxdialogex.h"





#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)


END_MESSAGE_MAP()


// Cmfc_demoDlg �Ի���



Cmfc_demoDlg::Cmfc_demoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_DEMO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

#ifdef _use_my_udp_
#undef new
	_pudp = std::unique_ptr<my_udp>(new(std::nothrow) my_udp);
#endif // 
}

void Cmfc_demoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cmfc_demoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// Cmfc_demoDlg ��Ϣ�������

BOOL Cmfc_demoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

#ifdef _use_my_udp_
	// created failure
	if (!_pudp)
	{
		AfxMessageBox(L"udp����ʧ��");
		return TRUE;
	}


	//return TRUE;



	_timer = SetTimer(10086, 40, NULL);

	int index = 0;
	for (; index < 16; )
		_arr_send[index++] = 49 + index;

	udp_param param;

	// log file
	param._is_log_debug = true;
	// udp type
	param._cast_type = udp_multi_cast;

	// the port of destination
	param._port_dst = 12345;

	// Whether to receive messages from yourself
	param._recv_loop = true;

	// local IP4
	char arr[] = "10.1.1.5";
	// Target IP
	char arr_dst[] = "233.0.0.11";

	memcpy(param._pip4_dst, arr_dst, strlen(arr_dst));
	memcpy(param._pip4_local, arr, strlen(arr));


	// ��ʼ������
	int ret_val = _pudp->init_ip4(param);
	if (0 != ret_val)
	{
		AfxMessageBox(L"��ʼ��ʧ��");
		return TRUE;
	}

	// ��UDP
	ret_val = _pudp->open(10);
	if (0 != ret_val)
	{
		AfxMessageBox(L"OPENʧ��");
		CString str;
		str.Format(L"%d", ret_val);
		AfxMessageBox(str);
		return TRUE;
	}

	
	_is_open = true;


#endif // 

	// -------------------------------------------------------------------------------
	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void Cmfc_demoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Cmfc_demoDlg::OnPaint()
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
HCURSOR Cmfc_demoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/*
*	@brief:
*/
void Cmfc_demoDlg::OnTimer(UINT_PTR nIDEvent)
{
	CDialogEx::OnTimer(nIDEvent);

	static int index = 1;
	static int ret = 0;

	if (!_is_open)
		return;

#ifdef _use_my_udp_
	if (_pudp)
	{
		//ret = _pudp->send(_arr_send, 16);
		//TRACE("\n\n ��%d���ͣ����ͽ����%d\n\n", index++, ret);
	}
#endif // _use_my_udp_
}



void Cmfc_demoDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	_is_open = false;

	if (0 != _timer)
	{
		KillTimer(_timer);
		_timer = 0;
	}



	// TODO: �ڴ˴������Ϣ����������
#ifdef _use_my_udp_

	if (_pudp)
		_pudp->shutdown();
	
#endif // !


	

}
