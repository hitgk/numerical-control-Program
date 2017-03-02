// 0422Dlg.h : header file
//

#if !defined(AFX_0422DLG_H__C12E47E3_F818_48DC_AFE5_D725B67927A6__INCLUDED_)
#define AFX_0422DLG_H__C12E47E3_F818_48DC_AFE5_D725B67927A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMy0422Dlg dialog

class CMy0422Dlg : public CDialog
{
// Construction
public:
	CMy0422Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMy0422Dlg)
	enum { IDD = IDD_MY0422_DIALOG };
	CString	m_edit;
	CString	m_edit1;
	CString	m_edit2;
	long	m_Xpos;
	CString	m_Ypos;
	CString	m_Zpos;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy0422Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMy0422Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRead1();
	afx_msg void OnCheak1();
	afx_msg void OnDone1();
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnChangeedit();
	afx_msg void OnChangeEdit1();
	afx_msg void OnChangeEdit2();
	afx_msg void OnButtonEstop();
	afx_msg void OnButtonCancel();
	afx_msg void OnButtonReset();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_0422DLG_H__C12E47E3_F818_48DC_AFE5_D725B67927A6__INCLUDED_)
