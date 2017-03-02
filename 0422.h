// 0422.h : main header file for the 0422 application
//

#if !defined(AFX_0422_H__5CC3F0CD_7E1C_447C_B591_AD93C6D9D84C__INCLUDED_)
#define AFX_0422_H__5CC3F0CD_7E1C_447C_B591_AD93C6D9D84C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMy0422App:
// See 0422.cpp for the implementation of this class
//

class CMy0422App : public CWinApp
{
public:
	CMy0422App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy0422App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMy0422App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_0422_H__5CC3F0CD_7E1C_447C_B591_AD93C6D9D84C__INCLUDED_)
