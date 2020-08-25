
// mfc_demoDlg.h : ͷ�ļ�
//

#pragma once


 #define _use_my_udp_

#ifdef _use_my_udp_
#include "my_udp.h"
#endif // 
#include <memory>
#include <new> // std::nothrow



// Cmfc_demoDlg �Ի���
class Cmfc_demoDlg : public CDialogEx
{
// ����
public:
	Cmfc_demoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_DEMO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��



private:
	UINT_PTR		_timer = 0;

	char			_arr_send[16] = { 0 };

	bool			_is_open = false;
#ifdef _use_my_udp_
	std::unique_ptr<my_udp>	_pudp = nullptr;
#endif // 

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
};
