// 0422Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "0422.h"
#include "0422Dlg.h"
#include<stdio.h>
#include<stdlib.h>
#include<conio.h> 
#include<string.h>
#include<math.h>
#include "DMC5480.h"    //��ӵ�
//#include<time.h>        //��ӵ�

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

FILE  *fp;
	char  gcr[80];          //gcrΪG�����ȡ��д
	char  gca[100][100];    //gcaΪG����洢��д,���ڴ洢Դ����
	char  ngca[100][100];   //���ڴ洢ȥ��������Ϣ֮���G����
	char  lc[80];           //���ڴ洢ԴG�����ÿһ�е�����
	char  nlc[80];          //���ڴ洢���з�ǰ���G��������
	int   hhf[100];         //���ڱ�ǲ����ڻ��з�������
	int   nc[100]={0};      //���ڱ�۴��ڲ���ʶ�����ĸ���,�����Ӧ
	int   i=0,j=0,a=0,b=0,b1=0,b2=0,c=0,d=0,e=0,e1=0,e2=0,f=0,length=0,n=0,n1=0,n2=0,n3=0,AC;
	int   nw[100]={0};      //���ڱ�ǳ���ζκ�λ����Ϣ
	int   N[100]={0};       //���ڴ洢ת�������ֵ�N�ֶ���Ϣ
	int   G[100][3]={0};    //���ڴ洢׼��������G��Ϣ,G[][2]����������ڵ���
	float X[100][2]={0.0};     //���ڴ洢��ַ��ΪX��������Ϣ,X[][0]�洢���꣬X[][1]������ڵ���
	float X1[100]={0.0};
    float X2[100]={0.0};
    float Y[100][2]={0.0};     //���ڴ洢��ַ��ΪY��������Ϣ
	float Y1[100]={0.0};
    float Y2[100]={0.0};
    float Z[100][2]={0.0};     //���ڴ洢��ַ��ΪZ��������Ϣ
	float Z1[100]={0.0};
    float Z2[100]={0.0};
	float I[100][2]={0.0};     //���ڴ洢��ַ��ΪI��������Ϣ
	float I1[100]={0.0};
    float I2[100]={0.0};
	float J[100][2]={0.0};     //���ڴ洢��ַ��ΪJ��������Ϣ
	float J1[100]={0.0};
    float J2[100]={0.0};
    float R[100][2]={0.0};     //���ڴ洢��ַ��ΪR��������Ϣ
	float R1[100]={0.0};
    float R2[100]={0.0};
    float F[100]={0.0};     //���ڴ洢����������F��Ϣ
	float F1[100]={0.0};
    float F2[100]={0.0};
    float S[100]={0.0};     //��������ת�ٹ�����S��Ϣ
	float S1[100]={0.0};
    float S2[100]={0.0};
    float T[100]={0.0};     //���ڵ��߹�����T��Ϣ
	float T1[100]={0.0};
    float T2[100]={0.0};
    float M[100][2]={0.0};     //���ڸ���������M��Ϣ,M[][1]���ڱ�����ڵ���
	float M1[100]={0.0};
    float M2[100]={0.0};
	CString s0,s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,s13,s14,s15,s16,s17,s18,s19,s20,s21,s22,s23,s24,s25,s26,s27,s28,s29,s30,s31,s32,s33,s34,s35,s36,s37,s38,s39,s40,s41,s42,s43,s44,s45,s46,s47,s48;
    long  XL,YL,ZL,IL,JL,RL;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy0422Dlg dialog

CMy0422Dlg::CMy0422Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy0422Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMy0422Dlg)
	m_edit = _T("");
	m_edit1 = _T("");
	m_edit2 = _T("");
	m_Xpos = 0;
	m_Ypos = _T("");
	m_Zpos = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy0422Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMy0422Dlg)
	DDX_Text(pDX, IDC_edit, m_edit);
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	DDX_Text(pDX, IDC_EDIT2, m_edit2);
	DDX_Text(pDX, IDC_EDIT3, m_Xpos);
	DDX_Text(pDX, IDC_EDIT4, m_Ypos);
	DDX_Text(pDX, IDC_EDIT5, m_Zpos);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMy0422Dlg, CDialog)
	//{{AFX_MSG_MAP(CMy0422Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_READ1, OnRead1)
	ON_BN_CLICKED(IDC_CHEAK1, OnCheak1)
	ON_BN_CLICKED(IDC_DONE1, OnDone1)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_EN_CHANGE(IDC_edit, OnChangeedit)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON1, OnButtonEstop)
	ON_BN_CLICKED(IDC_BUTTON2, OnButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON3, OnButtonReset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy0422Dlg message handlers

BOOL CMy0422Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
	if(d5480_board_init()<=0)//���ƿ��ĳ�ʼ������
		MessageBox("��ʼ��DMC5480��ʧ�ܣ�","����");
    
	//SetTimer(IDC_TIMER,100,NULL);//SetTimer�������ö�ʱ��������Ϊ ��ʱ��ID,���ʱ�䣬��λΪ���룬��Ӧ������ÿ�����ʱ�����һ��OnTimer������KillTimer�������߶�ʱ��
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMy0422Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMy0422Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMy0422Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMy0422Dlg::OnRead1()     //ִ��Դ����Ķ�ȡ
{
    
	if((fp=fopen("shukong.txt","rt"))==NULL)  //�ļ�����������ȡ
    {
        MessageBox("Cannot open file!\n");
        getch();
        exit(1);
    }
	MessageBox("�ļ�����������");
    
    while(fgets(gcr,80,fp))     //������������ȡ�������
	{
		c++;                    //���������������ڼ����
		//printf("��%d�еĳ������Ϊ��\n",i);
		//m_edit.Format("%s",gcr);
        
		s0.Format("%s\r\n",gcr); //Դ���밴�����������
        m_edit+=s0;


		
		
	    


        while(gcr[j]!='\0')    //��ÿһ��G����ĳ���
		{        
			j++;        
			length++;
		}
		lc[i]=length;        //�洢ÿһ�е�����
		//printf("�ó���εĳ���Ϊ%d\n",length);
     
        for(a=0;a<=length;a++)
		{
		 b=i;
         gca[b][a]=gcr[a];   //��G���밴�д浽gca���鵱��
		}
        //printf("%s\n",gca[b]); //gca���������G���밴�����
        s1.Format("%s\r\n",gca[b]); //Դ���밴�����������
        m_edit1+=s1;

        j=0;                 //���¸�ֵ��ѭ��
        length=0;
		i++;
	     
	}
    UpdateData(FALSE);	
   
    
}

void CMy0422Dlg::OnCheak1() 
{
	// TODO: Add your control notification handler code here
    //*2 ʵ�ֹ��ܣ�G������*//
	//*2.1 ʵ�ֹ��ܣ��ж�ÿһ��G�����Ƿ��л��з�*//
	a=0;
	b=0;
    for(i=0;i<=c;i++)
	{
        for(j=0;j<=lc[i];j++)
	  {
			if(gca[i][j]==59)
			{
				if(i==a)
				{
				//printf("��%d���л��з�\n",i);
                nlc[i]=j;     //�洢�л��з�����ǰ������
				}
				else
				{
					//printf("��%d��û�л��з�\n",a);
					hhf[b]=a; //���ڱ��û�л��з�����
					a=a+1;    //��ĳһ��û�л��з�ʱ��iҪ��a��ѭ��һ�Σ�Ϊ�˱�֤����˳�����Ӧ��֤a=i
					b++;
					d++;      //���ڱ��û�л��з�������	
				}
                a++;
			}	
		}	
	}

    
	if(d!=0)     //����û�л��з�������������ʾ������������
	{
		for(i=0;i<d;i++)
		{
			s2.Format("��⵽��%d��û�л��з�������ϻ��з�\r\n",hhf[i]);
            m_edit2+=s2;
		}
		//exit(0);
        
	}
    //*2.2ʵ�ֹ��ܣ��ж�ÿһ��G���뻻�з�ǰ�Ƿ�����޷�ʶ��Ĵ���*//
	a=0;
	b=0;
	e=0;
    for(i=0;i<c;i++)   //��Ҫ�ӵȺ�
	{
        for(j=0;j<=nlc[i];j++)
		{
        if(gca[i][j]!=59)
		{
          n=gca[i][j];
          if(((n>=65)&&(n<=90))||((n>=48)&&(n<=57))||(n==43)||(n==45)||(n==46)||(n==61)||(n==59)||(n==32))
		  {
			 // printf("��%d�д����ʶ��",i);
			  if((i==(c-1))&&(j==nlc[i]-1)&&(b==0))
			  {
				  s3.Format("����β������޷�ʶ��Ĵ���!\r\n");
                  m_edit2+=s3;
				  //printf("%d\n%d\n",i,j);
			  }
		  }
		  else
		  {
			  //m_edit2.Format("��%d�д�����ڲ���ʶ�����\n",i);
              e++;        //���ڱ�Ǹ����޷�ʶ��Ĵ������
			  nc[i]=e;    //���ڴ洢�����޷�ʶ�����ĸ���	
			  a=i;        //���ڱ�۴����޷�ʶ������������� 
			  b++;        //�����ж�����������Ƿ�����޷�ʶ��Ĵ���
		  }   
		}
        else
		{
		break;
		}
		}
		e=0;     //e���㣬ִ����һ�м��
	}

	for(i=0;i<100;i++)     //���ڴ����޷�ʶ����������������ʾ������������
	{
		if(nc[i]!=0)
		{
			s4.Format("��⵽��%d�д���%d���޷�ʶ�����\r\n",i,nc[i]);
            m_edit2+=s4;

			//if(i==a)       //����������Ϊ�����޷�ʶ���������һ��ʱ��������������
		//	{
            // exit(0);
             //  break;
		//	}
		}
	}
    //*3 ʵ�ֹ��ܣ�G������Ϣ����洢*//
	//*3.1���о���G����*//
    a=0;
	b=0;
	for(i=0;i<c;i++)        //���о���
	{
      for(j=0;j<=nlc[i];j++)
	  {
		  n=gca[i][j];
          if(((n>=65)&&(n<=90))||((n>=48)&&(n<=57))||(n==43)||(n==45)||(n==46)||(n==61)||(n==59))//ȥ�������ַ����������ġ��ո�
		  {
			  if(n==59)    //����⵽����ν�����ʱ������ǰѭ����ִ����һ��ѭ��
			  {
				  break;
			  }
			  else 
			  {

             // printf("��%d�е�%d�е�ASC��ֵΪ%d\n",i,j,n);
			  s5.Format("%c",gca[i][j]);   //��������Ĵ���
              m_edit2+=s5;
              ngca[a][b]=gca[i][j];
			  }
		  }
		  
	  b++;  
	  }
	  b=0;
	  a++;
	  s6.Format("\r\n");  //���ڴ���Ļ���
      m_edit2+=s6;
	  
	}
    //*3.2�洢G�����N�ֶ���Ϣ*//
	//*3.2.1�ж�ÿһ�еĳ�����ɼ�λ������ɲ��浽һά����n*//
    a=0;
	b=0;
	d=0;
	e=0;
	n=0;
    
    for(i=0;i<c;i++)
	{
      if(ngca[i][0]==78)   //�ж�ÿһ�д��������ĸ�Ƿ�ΪN
	  {
		  for(j=1;j<=5;j++)     //���ж�ÿһ�еĳ�����ɼ�λ�������
		  {
            // printf("ac=%d,i=%d\n",c,i);
			 if((j==5)&&((ngca[i][j]>=48)&&(ngca[i][j]<=57)))      //�������λ��Ϊ�����ַ�������ж϶κų�������ֵ
			  {
				  s7.Format("��%d�г���γ����������ֵ���뱣֤����ζκ�����λ�����ڣ�\r\n",i);
                  m_edit2+=s7;
				  a++;
			  }
			  if((j==1)&&((ngca[i][j]<48)||(ngca[i][j]>57)))      //�����һλΪ�������ַ�������ж϶κŸ���û�г���ζκ�
			  {
				  s8.Format("��%d��û�г���ζκţ�\r\n",i);
				  m_edit2+=s8;
				  b++;
			  }
			  if((ngca[i][j]>=48)&&(ngca[i][j]<=57))     
			  {
				  e++;
				  nw[i]=e;      //��ÿһ�е�λ����Ϣ���ݸ�����n
				  //printf("c=%d,i=%d\n",c,i);
			  }
			else      //�������������ַ�ʱ��������ǰѭ����ִ����һ��
				break;
		  }
	  }
      if(ngca[i][0]!=78)
	  {
       d++;
       s9.Format("��%d��û�г���ζκ�N\n",i);
	   m_edit2+=s9;
	  }
	  e=0;
	}

	if((a!=0)||(b!=0)||(d!=0))
	{
    
	if(a!=0)
    s10.Format("����%d�г���γ����������ֵ���뱣֤����ζκ�����λ�����ڣ�\r\n",a);
	m_edit2+=s10;
    if(b!=0)
    s11.Format("����%d��û�г���ζκţ�\r\n",b);
    m_edit2+=s11;
	if(d!=0)
	s12.Format("����%d��û�г���ζκ�N\r\n",d);
    m_edit2+=s12;
	//exit(0);
	}
    //*3.2.2��N�ֶε��ַ���Ϣת��������Ϣ���浽һά����N*//
	a=0;
	b=0;
	e=0;
	n=0;
    for(i=0;i<c;i++)
	{
        for(j=1;j<=nw[i];j++)     
		{
			if((ngca[i][j]>=48)&&(ngca[i][j]<=57))
			{
				if(i==a)      //�в���
				{
					n=(gca[i][j]-48)*pow(10,(nw[i]-j))+n;  //���ַ���Ϣת��������Ϣ
					N[i]=n;        //�������N��������Ϣ��ֵ������N[]
					s13.Format("��%d�еĳ���ζκ�Ϊ%d\r\n",i,N[i]);
                    m_edit2+=s13;

				}
			}
		}
	   n=0;
       a++;
	}
	//*3.3�洢G�����׼��������G�ֶ���Ϣ���洢������G[100][3]*//
    a=0;
	b=0;
    for(i=0;i<c;i++)
	{
		for(j=3;j<=nlc[i];j++) 
		{
			if(ngca[i][j]==71)
			{
			    if(((ngca[i][j+1]<=57)&&(ngca[i][j+1]>=48))&&((ngca[i][j+2]<=57)&&(ngca[i][j+2]>=48))&&((ngca[i][j+3]>57)||(ngca[i][j+3]<48)))            //��׼��������G����Ϊ��λ����ʱִ��ѭ��
				{    
					 G[i][1]=-1;        //��ֹG[][1]Ĭ�ϵ���0�����ж�
				     G[i][a]=(ngca[i][j+1]-48)*10+(ngca[i][j+2]-48);  //��׼�������ֵ��ַ���Ϣת����������Ϣ
					 G[i][2]=1;       //������ڵ���
					 s14.Format("��%d��׼��������Ϊ%d\r\n",i,G[i][a]);
					 m_edit2+=s14;
                     a++;
				}
                else if(((ngca[i][j+1]<=57)&&(ngca[i][j+1]>=48))&&((ngca[i][j+2]>57)||(ngca[i][j+2]<48)))            //��׼��������G����Ϊһλ����ʱִ��ѭ��
				{   
                     G[i][1]=-1;        //��ֹG[][1]Ĭ�ϵ���0�����ж�
				     G[i][a]=ngca[i][j+1]-48;                        //��׼�������ֵ��ַ���Ϣת����������Ϣ
                     G[i][2]=1;       //������ڵ���
                     s14.Format("��%d��׼��������Ϊ%d\r\n",i,G[i][a]);
                     m_edit2+=s14;
                     a++;
				}
			    else
				{
					s14.Format("��%d�е�׼���������޷�ʶ��\r\n",i);
                    m_edit2+=s14;
					b++;
				}
			}
		}
		a=0;
	}
	if(b!=0)
	{
		s15.Format("����%d����׼���������޷�ʶ�������¼����룡\r\n",b);
		m_edit2+=s15;
		//exit(0);
	}
    if(b==0)
	{
		s15.Format("׼�������ֿ���ʶ��\n");
		m_edit2+=s15;
	}
	//*3.4�洢G�����������X,Y,Z,R�ֶ���Ϣ*//
    a=0;
	b=0;
	d=0;
	e=0;
	f=0;
	n=0;
	n1=0;
	n2=0;
	b1=0;
	e1=0;
	b2=0;
	e2=0;
    for(i=0;i<c;i++)
	{
		for(j=0;j<=nlc[i];j++) 
		{
			//*�洢X�ֶ���Ϣ*//
			if((ngca[i][j]==88)&&(ngca[i][j+1]==43))     //�ж��������Ƿ�ΪX�Һ�һλΪ��+����
			{				
				for(b=1;(ngca[i][j+1+b]>=48)&&(ngca[i][j+1+b]<=57);b++)   //bΪ����λ��
				{
				     printf("b=%d\n",b);
                     if(ngca[i][j+2+b]==46)  //����С���㣬��С��������λ��
					 {
						for(e=1;(ngca[i][j+2+b+e]>=48)&&(ngca[i][j+2+b+e]<=57);e++)  //eΪС������λ��
						{
							s16.Format("e=%d\r\n",e);
							m_edit2+=s16;
						
						}
					}
				     
				} 
                for(d=1;d<b;d++)     //�����������֣����ۼ�
				{
			     X1[i]=(ngca[i][j+1+d]-48)*pow(10,b-d-1)+X1[i];
                 s17.Format("��%d�е�X������Ϊ%f\r\n",i,X1[i]);
				 m_edit2+=s17;
				}
				if(e>=1)
				{
	               for(f=1;f<e;f++)    //����С�����֣����ۼ�
				   {
                    X2[i]=(ngca[i][j+1+b+f]-48)*pow(10,-f)+X2[i];
                    s18.Format("��%d�е�X������Ϊ%f\r\n",i,X2[i]);
					m_edit2+=s18;	
				   }
				}
				X[i][0]=X1[i]+X2[i];
				X[i][1]=1;            //������ڵ���
	 	        s19.Format("��%d�е�X������Ϊ%f\r\n",i,X[i][0]); 
				m_edit2+=s19;
			}
            else if((ngca[i][j]==88)&&(ngca[i][j+1]==45))     //�ж��������Ƿ�ΪX�Һ�һλΪ��-����
            {				
				for(b1=1;(ngca[i][j+1+b1]>=48)&&(ngca[i][j+1+b1]<=57);b1++)   //bΪ����λ��
				{
				     s20.Format("b1=%d\r\n",b1);
					 m_edit2+=s20;
                     if(ngca[i][j+2+b1]==46)  //����С���㣬��С��������λ��
					 {
						for(e1=1;(ngca[i][j+2+b1+e1]>=48)&&(ngca[i][j+2+b1+e1]<=57);e1++)  //eΪС������λ��
						{
							s21.Format("e1=%d\r\n",e1);
							m_edit2+=s21;
						
						}
					}
				     
				} 
                for(d=1;d<b1;d++)     //�����������֣����ۼ�
				{
			     X1[i]=(ngca[i][j+1+d]-48)*pow(10,b1-d-1)+X1[i];
                 s22.Format("��%d�е�X������Ϊ%f\r\n",i,X1[i]);
				 m_edit2+=s22;
				}
				if(e1>=1)
				{
	               for(f=1;f<e1;f++)    //����С�����֣����ۼ�
				   {
                    X2[i]=(ngca[i][j+1+b1+f]-48)*pow(10,-f)+X2[i];
                    s23.Format("��%d�е�Xa������Ϊ%f\r\n",i,X2[i]);
					m_edit2+=s23;
				   }
				}
				X[i][0]=-(X1[i]+X2[i]);
                X[i][1]=1;            //������ڵ���
	 	        s24.Format("��%d�е�X������Ϊ%f\r\n",i,X[i][1]);
				m_edit2+=s24;
			}
            else if((ngca[i][j]==88)&&(ngca[i][j+1]>=48)&&(ngca[i][j+1]<=57))     //�ж��������Ƿ�ΪX�Һ�һλΪ����
            {				
				for(b2=1;(ngca[i][j+b2]>=48)&&(ngca[i][j+b2]<=57);b2++)   //bΪ����λ��
				{
				     s25.Format("b2=%d\r\n",b2);
					 m_edit2+=s25;
                     if(ngca[i][j+1+b2]==46)  //����С���㣬��С��������λ��
					 {
						for(e2=1;(ngca[i][j+1+b2+e2]>=48)&&(ngca[i][j+1+b2+e2]<=57);e2++)  //eΪС������λ��
						{
							s26.Format("e2=%d\r\n",e2);
							m_edit2+=s26;
						
						}
					}
				     
				} 
                for(d=1;d<b2;d++)     //�����������֣����ۼ�
				{
			     X1[i]=(ngca[i][j+d]-48)*pow(10,b2-d-1)+X1[i];
                 s27.Format("��%d�е�X������Ϊ%f\r\n",i,X1[i]);
				 m_edit2+=s27;
				}
				if(e2>=1)
				{
	               for(f=1;f<e2;f++)    //����С�����֣����ۼ�
				   {
                    X2[i]=(ngca[i][j+b2+f]-48)*pow(10,-f)+X2[i];
                    s28.Format("��%d�е�Xa������Ϊ%f\r\n",i,X2[i]);
					m_edit2+=s28;
				   }
				}
				X[i][0]=X1[i]+X2[i];
                X[i][1]=1;            //������ڵ���
	 	        s29.Format("��%d�е�X������Ϊ%f\r\n",i,X[i][0]);
				m_edit2+=s29;
			}
			else if((ngca[i][j]==88)&&((ngca[i][j+1]<48)||(ngca[i][j+1]>57))&&(ngca[i][j+1]!=43)&&(ngca[i][j+1]!=45))
			{
				s30.Format("��%d��X����Ĵ����޷�ʶ�����飡\r\n",i);
				m_edit2+=s30;
				n++;
			}


            //*�洢Y�ֶ���Ϣ*//
	        if((ngca[i][j]==89)&&(ngca[i][j+1]==43))     //�ж��������Ƿ�ΪY�Һ�һλΪ��+����
			{				
				for(b=1;(ngca[i][j+1+b]>=48)&&(ngca[i][j+1+b]<=57);b++)   //bΪ����λ��
				{
				     //printf("b=%d\n",b);
                     if(ngca[i][j+2+b]==46)  //����С���㣬��С��������λ��
					 {
						for(e=1;(ngca[i][j+2+b+e]>=48)&&(ngca[i][j+2+b+e]<=57);e++)  //eΪС������λ��
						{
						//	printf("e=%d\n",e);
						
						}
					}
				     
				} 
                for(d=1;d<b;d++)     //�����������֣����ۼ�
				{
			     Y1[i]=(ngca[i][j+1+d]-48)*pow(10,b-d-1)+Y1[i];
                // printf("��%d�е�Y������Ϊ%f\n",i,Y1[i]);
				}
				if(e>=1)
				{
	               for(f=1;f<e;f++)    //����С�����֣����ۼ�
				   {
                    Y2[i]=(ngca[i][j+1+b+f]-48)*pow(10,-f)+Y2[i];
                    //printf("��%d�е�Y������Ϊ%f\n",i,Y2[i]);
				   }
				}
				Y[i][0]=Y1[i]+Y2[i];
                Y[i][1]=1;            //������ڵ���
	 	       // printf("��%d�е�Y������Ϊ%f\n",i,Y[i][0]);  
			}
            else if((ngca[i][j]==89)&&(ngca[i][j+1]==45))     //�ж��������Ƿ�ΪY�Һ�һλΪ��-����
            {				
				for(b1=1;(ngca[i][j+1+b1]>=48)&&(ngca[i][j+1+b1]<=57);b1++)   //bΪ����λ��
				{
				     //printf("b1=%d\n",b1);
                     if(ngca[i][j+2+b1]==46)  //����С���㣬��С��������λ��
					 {
						for(e1=1;(ngca[i][j+2+b1+e1]>=48)&&(ngca[i][j+2+b1+e1]<=57);e1++)  //eΪС������λ��
						{
						//	printf("e1=%d\n",e1);
						
						}
					}
				     
				} 
                for(d=1;d<b1;d++)     //�����������֣����ۼ�
				{
			     Y1[i]=(ngca[i][j+1+d]-48)*pow(10,b1-d-1)+Y1[i];
                 //printf("��%d�е�Y������Ϊ%f\n",i,Y1[i]);
				}
				if(e1>=1)
				{
	               for(f=1;f<e1;f++)    //����С�����֣����ۼ�
				   {
                    Y2[i]=(ngca[i][j+1+b1+f]-48)*pow(10,-f)+Y2[i];
                    //printf("��%d�е�Y������Ϊ%f\n",i,Y2[i]);
				   }
				}
				Y[i][0]=-(Y1[i]+Y2[i]);
                Y[i][1]=1;            //������ڵ���
	 	        //printf("��%d�е�Y������Ϊ%f\n",i,Y[i][0]);  
			}
            else if((ngca[i][j]==89)&&(ngca[i][j+1]>=48)&&(ngca[i][j+1]<=57))     //�ж��������Ƿ�ΪY�Һ�һλΪ����
            {				
				for(b2=1;(ngca[i][j+b2]>=48)&&(ngca[i][j+b2]<=57);b2++)   //bΪ����λ��
				{
				     //printf("b2=%d\n",b2);
                     if(ngca[i][j+1+b2]==46)  //����С���㣬��С��������λ��
					 {
						for(e2=1;(ngca[i][j+1+b2+e2]>=48)&&(ngca[i][j+1+b2+e2]<=57);e2++)  //eΪС������λ��
						{
						//	printf("e2=%d\n",e2);
						
						}
					}
				     
				} 
                for(d=1;d<b2;d++)     //�����������֣����ۼ�
				{
			     Y1[i]=(ngca[i][j+d]-48)*pow(10,b2-d-1)+Y1[i];
                 //printf("��%d�е�Y������Ϊ%f\n",i,Y1[i]);
				}
				if(e2>=1)
				{
	               for(f=1;f<e2;f++)    //����С�����֣����ۼ�
				   {
                    Y2[i]=(ngca[i][j+b2+f]-48)*pow(10,-f)+Y2[i];
                    //printf("��%d�е�Y������Ϊ%f\n",i,Y2[i]);
				   }
				}
				Y[i][0]=Y1[i]+Y2[i];
                Y[i][1]=1;            //������ڵ���
	 	        //printf("��%d�е�Y������Ϊ%f\n",i,Y[i][0]);  
			}
			else if((ngca[i][j]==89)&&((ngca[i][j+1]<48)||(ngca[i][j+1]>57))&&(ngca[i][j+1]!=43)&&(ngca[i][j+1]!=45))
			{
			//	printf("��%d��Y����Ĵ����޷�ʶ�����飡\n",i);
				n1++;
			}

            
            //*�洢Z�ֶ���Ϣ*//
	        if((ngca[i][j]==90)&&(ngca[i][j+1]==43))     //�ж��������Ƿ�ΪZ�Һ�һλΪ��+����
			{				
				for(b=1;(ngca[i][j+1+b]>=48)&&(ngca[i][j+1+b]<=57);b++)   //bΪ����λ��
				{
				    // printf("b=%d\n",b);
                     if(ngca[i][j+2+b]==46)  //����С���㣬��С��������λ��
					 {
						for(e=1;(ngca[i][j+2+b+e]>=48)&&(ngca[i][j+2+b+e]<=57);e++)  //eΪС������λ��
						{
						//	printf("e=%d\n",e);
						
						}
					}
				     
				} 
                for(d=1;d<b;d++)     //�����������֣����ۼ�
				{
			     Z1[i]=(ngca[i][j+1+d]-48)*pow(10,b-d-1)+Z1[i];
                 //printf("��%d�е�Z������Ϊ%f\n",i,Z1[i]);
				}
				if(e>=1)
				{
	               for(f=1;f<e;f++)    //����С�����֣����ۼ�
				   {
                    Z2[i]=(ngca[i][j+1+b+f]-48)*pow(10,-f)+Z2[i];
                   // printf("��%d�е�Z������Ϊ%f\n",i,Z2[i]);
				   }
				}
				Z[i][0]=Z1[i]+Z2[i];
                Z[i][1]=1;            //������ڵ���
	 	        //printf("��%d�е�Z������Ϊ%f\n",i,Z[i][0]);  
			}
            else if((ngca[i][j]==90)&&(ngca[i][j+1]==45))     //�ж��������Ƿ�ΪZ�Һ�һλΪ��-����
            {				
				for(b1=1;(ngca[i][j+1+b1]>=48)&&(ngca[i][j+1+b1]<=57);b1++)   //bΪ����λ��
				{
				     //printf("b1=%d\n",b1);
                     if(ngca[i][j+2+b1]==46)  //����С���㣬��С��������λ��
					 {
						for(e1=1;(ngca[i][j+2+b1+e1]>=48)&&(ngca[i][j+2+b1+e1]<=57);e1++)  //eΪС������λ��
						{
						//	printf("e1=%d\n",e1);
						
						}
					}
				     
				} 
                for(d=1;d<b1;d++)     //�����������֣����ۼ�
				{
			     Z1[i]=(ngca[i][j+1+d]-48)*pow(10,b1-d-1)+Z1[i];
                 //printf("��%d�е�Z������Ϊ%f\n",i,Z1[i]);
				}
				if(e1>=1)
				{
	               for(f=1;f<e1;f++)    //����С�����֣����ۼ�
				   {
                    Z2[i]=(ngca[i][j+1+b1+f]-48)*pow(10,-f)+Z2[i];
                   // printf("��%d�е�Z������Ϊ%f\n",i,Z2[i]);
				   }
				}
				Z[i][0]=-(Z1[i]+Z2[i]);
                Z[i][1]=1;            //������ڵ���
	 	       // printf("��%d�е�Z������Ϊ%f\n",i,Z[i][0]);  
			}
            else if((ngca[i][j]==90)&&(ngca[i][j+1]>=48)&&(ngca[i][j+1]<=57))     //�ж��������Ƿ�ΪZ�Һ�һλΪ����
            {				
				for(b2=1;(ngca[i][j+b2]>=48)&&(ngca[i][j+b2]<=57);b2++)   //bΪ����λ��
				{
				     printf("b2=%d\n",b2);
                     if(ngca[i][j+1+b2]==46)  //����С���㣬��С��������λ��
					 {
						for(e2=1;(ngca[i][j+1+b2+e2]>=48)&&(ngca[i][j+1+b2+e2]<=57);e2++)  //eΪС������λ��
						{
						//	printf("e2=%d\n",e2);
						
						}
					}
				     
				} 
                for(d=1;d<b2;d++)     //�����������֣����ۼ�
				{
			     Z1[i]=(ngca[i][j+d]-48)*pow(10,b2-d-1)+Z1[i];
                // printf("��%d�е�Z������Ϊ%f\n",i,Z1[i]);
				}
				if(e2>=1)
				{
	               for(f=1;f<e2;f++)    //����С�����֣����ۼ�
				   {
                    Z2[i]=(ngca[i][j+b2+f]-48)*pow(10,-f)+Z2[i];
                  // printf("��%d�е�Z������Ϊ%f\n",i,Z2[i]);
				   }
				}
				Z[i][0]=Z1[i]+Z2[i];
                Z[i][1]=1;            //������ڵ���
	 	       // printf("��%d�е�Z������Ϊ%f\n",i,Z[i][0]);  
			}
			else if((ngca[i][j]==90)&&((ngca[i][j+1]<48)||(ngca[i][j+1]>57))&&(ngca[i][j+1]!=43)&&(ngca[i][j+1]!=45))
			{
			//	printf("��%d��Z����Ĵ����޷�ʶ�����飡\n",i);
				n2++;
			}

            //*�洢I�ֶ���Ϣ*//
	        if((ngca[i][j]==73)&&(ngca[i][j+1]==43))     //�ж��������Ƿ�ΪZ�Һ�һλΪ��+����
			{				
				for(b=1;(ngca[i][j+1+b]>=48)&&(ngca[i][j+1+b]<=57);b++)   //bΪ����λ��
				{
				    // printf("b=%d\n",b);
                     if(ngca[i][j+2+b]==46)  //����С���㣬��С��������λ��
					 {
						for(e=1;(ngca[i][j+2+b+e]>=48)&&(ngca[i][j+2+b+e]<=57);e++)  //eΪС������λ��
						{
						//	printf("e=%d\n",e);
						
						}
					}
				     
				} 
                for(d=1;d<b;d++)     //�����������֣����ۼ�
				{
			     I1[i]=(ngca[i][j+1+d]-48)*pow(10,b-d-1)+I1[i];
                 //printf("��%d�е�I������Ϊ%f\n",i,I1[i]);
				}
				if(e>=1)
				{
	               for(f=1;f<e;f++)    //����С�����֣����ۼ�
				   {
                    I2[i]=(ngca[i][j+1+b+f]-48)*pow(10,-f)+I2[i];
                   // printf("��%d�е�I������Ϊ%f\n",i,I2[i]);
				   }
				}
				I[i][0]=I1[i]+I2[i];
                I[i][1]=1;            //������ڵ���
	 	        //printf("��%d�е�I������Ϊ%f\n",i,I[i][0]);  
			}
            else if((ngca[i][j]==73)&&(ngca[i][j+1]==45))     //�ж��������Ƿ�ΪZ�Һ�һλΪ��-����
            {				
				for(b1=1;(ngca[i][j+1+b1]>=48)&&(ngca[i][j+1+b1]<=57);b1++)   //bΪ����λ��
				{
				     //printf("b1=%d\n",b1);
                     if(ngca[i][j+2+b1]==46)  //����С���㣬��С��������λ��
					 {
						for(e1=1;(ngca[i][j+2+b1+e1]>=48)&&(ngca[i][j+2+b1+e1]<=57);e1++)  //eΪС������λ��
						{
						//	printf("e1=%d\n",e1);
						
						}
					}
				     
				} 
                for(d=1;d<b1;d++)     //�����������֣����ۼ�
				{
			     I1[i]=(ngca[i][j+1+d]-48)*pow(10,b1-d-1)+I1[i];
                 //printf("��%d�е�I������Ϊ%f\n",i,I1[i]);
				}
				if(e1>=1)
				{
	               for(f=1;f<e1;f++)    //����С�����֣����ۼ�
				   {
                    I2[i]=(ngca[i][j+1+b1+f]-48)*pow(10,-f)+I2[i];
                   // printf("��%d�е�I������Ϊ%f\n",i,I2[i]);
				   }
				}
				I[i][0]=-(I1[i]+I2[i]);
                I[i][1]=1;            //������ڵ���
	 	       // printf("��%d�е�I������Ϊ%f\n",i,I[i][0]);  
			}
            else if((ngca[i][j]==73)&&(ngca[i][j+1]>=48)&&(ngca[i][j+1]<=57))     //�ж��������Ƿ�ΪZ�Һ�һλΪ����
            {				
				for(b2=1;(ngca[i][j+b2]>=48)&&(ngca[i][j+b2]<=57);b2++)   //bΪ����λ��
				{
				     printf("b2=%d\n",b2);
                     if(ngca[i][j+1+b2]==46)  //����С���㣬��С��������λ��
					 {
						for(e2=1;(ngca[i][j+1+b2+e2]>=48)&&(ngca[i][j+1+b2+e2]<=57);e2++)  //eΪС������λ��
						{
						//	printf("e2=%d\n",e2);
						
						}
					}
				     
				} 
                for(d=1;d<b2;d++)     //�����������֣����ۼ�
				{
			     Z1[i]=(ngca[i][j+d]-48)*pow(10,b2-d-1)+Z1[i];
                // printf("��%d�е�Z������Ϊ%f\n",i,Z1[i]);
				}
				if(e2>=1)
				{
	               for(f=1;f<e2;f++)    //����С�����֣����ۼ�
				   {
                    I2[i]=(ngca[i][j+b2+f]-48)*pow(10,-f)+I2[i];
                  // printf("��%d�е�I������Ϊ%f\n",i,I2[i]);
				   }
				}
				I[i][0]=I1[i]+I2[i];
                I[i][1]=1;            //������ڵ���
	 	       // printf("��%d�е�I������Ϊ%f\n",i,I[i][0]);  
			}
			else if((ngca[i][j]==73)&&((ngca[i][j+1]<48)||(ngca[i][j+1]>57))&&(ngca[i][j+1]!=43)&&(ngca[i][j+1]!=45))
			{
			//	printf("��%d��I����Ĵ����޷�ʶ�����飡\n",i);
				n2++;
			}

			//*�洢J�ֶ���Ϣ*//
	        if((ngca[i][j]==74)&&(ngca[i][j+1]==43))     //�ж��������Ƿ�ΪZ�Һ�һλΪ��+����
			{				
				for(b=1;(ngca[i][j+1+b]>=48)&&(ngca[i][j+1+b]<=57);b++)   //bΪ����λ��
				{
				    // printf("b=%d\n",b);
                     if(ngca[i][j+2+b]==46)  //����С���㣬��С��������λ��
					 {
						for(e=1;(ngca[i][j+2+b+e]>=48)&&(ngca[i][j+2+b+e]<=57);e++)  //eΪС������λ��
						{
						//	printf("e=%d\n",e);
						
						}
					}
				     
				} 
                for(d=1;d<b;d++)     //�����������֣����ۼ�
				{
			     J1[i]=(ngca[i][j+1+d]-48)*pow(10,b-d-1)+J1[i];
                 //printf("��%d�е�J������Ϊ%f\n",i,J1[i]);
				}
				if(e>=1)
				{
	               for(f=1;f<e;f++)    //����С�����֣����ۼ�
				   {
                    J2[i]=(ngca[i][j+1+b+f]-48)*pow(10,-f)+J2[i];
                   // printf("��%d�е�J������Ϊ%f\n",i,J2[i]);
				   }
				}
				J[i][0]=J1[i]+J2[i];
                J[i][1]=1;            //������ڵ���
	 	        //printf("��%d�е�J������Ϊ%f\n",i,J[i][0]);  
			}
            else if((ngca[i][j]==74)&&(ngca[i][j+1]==45))     //�ж��������Ƿ�ΪZ�Һ�һλΪ��-����
            {				
				for(b1=1;(ngca[i][j+1+b1]>=48)&&(ngca[i][j+1+b1]<=57);b1++)   //bΪ����λ��
				{
				     //printf("b1=%d\n",b1);
                     if(ngca[i][j+2+b1]==46)  //����С���㣬��С��������λ��
					 {
						for(e1=1;(ngca[i][j+2+b1+e1]>=48)&&(ngca[i][j+2+b1+e1]<=57);e1++)  //eΪС������λ��
						{
						//	printf("e1=%d\n",e1);
						
						}
					}
				     
				} 
                for(d=1;d<b1;d++)     //�����������֣����ۼ�
				{
			     J1[i]=(ngca[i][j+1+d]-48)*pow(10,b1-d-1)+J1[i];
                 //printf("��%d�е�J������Ϊ%f\n",i,J1[i]);
				}
				if(e1>=1)
				{
	               for(f=1;f<e1;f++)    //����С�����֣����ۼ�
				   {
                    J2[i]=(ngca[i][j+1+b1+f]-48)*pow(10,-f)+J2[i];
                   // printf("��%d�е�J������Ϊ%f\n",i,J2[i]);
				   }
				}
				J[i][0]=-(J1[i]+J2[i]);
                J[i][1]=1;            //������ڵ���
	 	       // printf("��%d�е�J������Ϊ%f\n",i,J[i][0]);  
			}
            else if((ngca[i][j]==74)&&(ngca[i][j+1]>=48)&&(ngca[i][j+1]<=57))     //�ж��������Ƿ�ΪZ�Һ�һλΪ����
            {				
				for(b2=1;(ngca[i][j+b2]>=48)&&(ngca[i][j+b2]<=57);b2++)   //bΪ����λ��
				{
				     printf("b2=%d\n",b2);
                     if(ngca[i][j+1+b2]==46)  //����С���㣬��С��������λ��
					 {
						for(e2=1;(ngca[i][j+1+b2+e2]>=48)&&(ngca[i][j+1+b2+e2]<=57);e2++)  //eΪС������λ��
						{
						//	printf("e2=%d\n",e2);
						
						}
					}
				     
				} 
                for(d=1;d<b2;d++)     //�����������֣����ۼ�
				{
			     J1[i]=(ngca[i][j+d]-48)*pow(10,b2-d-1)+J1[i];
                // printf("��%d�е�J������Ϊ%f\n",i,J1[i]);
				}
				if(e2>=1)
				{
	               for(f=1;f<e2;f++)    //����С�����֣����ۼ�
				   {
                    J2[i]=(ngca[i][j+b2+f]-48)*pow(10,-f)+J2[i];
                  // printf("��%d�е�J������Ϊ%f\n",i,J2[i]);
				   }
				}
				J[i][0]=J1[i]+J2[i];
                J[i][1]=1;            //������ڵ���
	 	       // printf("��%d�е�J������Ϊ%f\n",i,J[i][0]);  
			}
			else if((ngca[i][j]==74)&&((ngca[i][j+1]<48)||(ngca[i][j+1]>57))&&(ngca[i][j+1]!=43)&&(ngca[i][j+1]!=45))
			{
			//	printf("��%d��J����Ĵ����޷�ʶ�����飡\n",i);
				n2++;
			}
            //*�洢R�ֶ���Ϣ*//
	        if((ngca[i][j]==82)&&(ngca[i][j+1]==43))     //�ж��������Ƿ�ΪR�Һ�һλΪ��+����
			{				
				for(b=1;(ngca[i][j+1+b]>=48)&&(ngca[i][j+1+b]<=57);b++)   //bΪ����λ��
				{
				    // printf("b=%d\n",b);
                     if(ngca[i][j+2+b]==46)  //����С���㣬��С��������λ��
					 {
						for(e=1;(ngca[i][j+2+b+e]>=48)&&(ngca[i][j+2+b+e]<=57);e++)  //eΪС������λ��
						{
						//	printf("e=%d\n",e);
						
						}
					}
				     
				} 
                for(d=1;d<b;d++)     //�����������֣����ۼ�
				{
			     R1[i]=(ngca[i][j+1+d]-48)*pow(10,b-d-1)+R1[i];
                // printf("��%d�е�R������Ϊ%f\n",i,R1[i]);
				}
				if(e>=1)
				{
	               for(f=1;f<e;f++)    //����С�����֣����ۼ�
				   {
                    R2[i]=(ngca[i][j+1+b+f]-48)*pow(10,-f)+R2[i];
                  //  printf("��%d�е�R������Ϊ%f\n",i,R2[i]);
				   }
				}
				R[i][0]=R1[i]+R2[i];
                R[i][1]=1;            //������ڵ���
	 	       // printf("��%d�е�R������Ϊ%f\n",i,R[i][0]);  
			}
            else if((ngca[i][j]==82)&&(ngca[i][j+1]==45))     //�ж��������Ƿ�ΪR�Һ�һλΪ��-����
            {				
				for(b1=1;(ngca[i][j+1+b1]>=48)&&(ngca[i][j+1+b1]<=57);b1++)   //bΪ����λ��
				{
				   //  printf("b1=%d\n",b1);
                     if(ngca[i][j+2+b1]==46)  //����С���㣬��С��������λ��
					 {
						for(e1=1;(ngca[i][j+2+b1+e1]>=48)&&(ngca[i][j+2+b1+e1]<=57);e1++)  //eΪС������λ��
						{
					//		printf("e1=%d\n",e1);
						
						}
					}
				     
				} 
                for(d=1;d<b1;d++)     //�����������֣����ۼ�
				{
			     R1[i]=(ngca[i][j+1+d]-48)*pow(10,b1-d-1)+R1[i];
                // printf("��%d�е�R������Ϊ%f\n",i,R1[i]);
				}
				if(e1>=1)
				{
	               for(f=1;f<e1;f++)    //����С�����֣����ۼ�
				   {
                    R2[i]=(ngca[i][j+1+b1+f]-48)*pow(10,-f)+R2[i];
                  //  printf("��%d�е�R������Ϊ%f\n",i,R2[i]);
				   }
				}
				R[i][0]=-(R1[i]+R2[i]);
                R[i][1]=1;            //������ڵ���
	 	       // printf("��%d�е�R������Ϊ%f\n",i,R[i][0]);  
			}
            else if((ngca[i][j]==82)&&(ngca[i][j+1]>=48)&&(ngca[i][j+1]<=57))     //�ж��������Ƿ�ΪR�Һ�һλΪ����
            {				
				for(b2=1;(ngca[i][j+b2]>=48)&&(ngca[i][j+b2]<=57);b2++)   //bΪ����λ��
				{
				     printf("b2=%d\n",b2);
                     if(ngca[i][j+1+b2]==46)  //����С���㣬��С��������λ��
					 {
						for(e2=1;(ngca[i][j+1+b2+e2]>=48)&&(ngca[i][j+1+b2+e2]<=57);e2++)  //eΪС������λ��
						{
						//	printf("e2=%d\n",e2);
						
						}
					}
				     
				} 
                for(d=1;d<b2;d++)     //�����������֣����ۼ�
				{
			     R1[i]=(ngca[i][j+d]-48)*pow(10,b2-d-1)+R1[i];
                // printf("��%d�е�R������Ϊ%f\n",i,R1[i]);
				}
				if(e2>=1)
				{
	               for(f=1;f<e2;f++)    //����С�����֣����ۼ�
				   {
                    R2[i]=(ngca[i][j+b2+f]-48)*pow(10,-f)+R2[i];
                    //printf("��%d�е�R������Ϊ%f\n",i,R2[i]);
				   }
				}
				R[i][0]=R1[i]+R2[i];
                R[i][1]=1;            //������ڵ���
	 	       // printf("��%d�е�R������Ϊ%f\n",i,R[i][0]);  
			}
			else if((ngca[i][j]==82)&&((ngca[i][j+1]<48)||(ngca[i][j+1]>57))&&(ngca[i][j+1]!=43)&&(ngca[i][j+1]!=45))
			{
			//	printf("��%d��R����Ĵ����޷�ʶ�����飡\n",i);
				n3++;
			}

		}
        
		b=0;
		e=0;
		b1=0;
		e1=0;
		b2=0;
		e2=0;
	}
	if((n!=0)||(n1!=0)||(n2!=0)||(n3!=0))
	{
		if(n!=0)
		{
          // printf("����%d��X����Ĵ����޷�ʶ�����飡\n",n);
		}
        if(n1!=0)
		{
          // printf("����%d��Y����Ĵ����޷�ʶ�����飡\n",n1);
		}
        if(n2!=0)
		{
         //  printf("����%d��Z����Ĵ����޷�ʶ�����飡\n",n2);
		}
		if(n3!=0)
		{
           //printf("����%d��R����Ĵ����޷�ʶ�����飡\n",n3);
		}
		//exit(0);
	}
    //*3.5�洢����������F�ֶ���Ϣ*//
	a=0;
	b=0;
	d=0;
	e=0;
	f=0;
	n=0;
    for(i=0;i<c;i++)
	{
		for(j=3;j<=nlc[i];j++) 
		{
			if((ngca[i][j]==70)&&(ngca[i][j+1]>=48)&&(ngca[i][j+1]<=57))  
			{
				for(b=1;(ngca[i][j+b]>=48)&&(ngca[i][j+b]<=57);b++)   //bΪ����λ��
				{
                    //printf("b=%d\n",b);
                    if(ngca[i][j+1+b]==46)  //����С���㣬��С��������λ��
					 {
						for(e=1;(ngca[i][j+1+b+e]>=48)&&(ngca[i][j+1+b+e2]<=57);e++)  //eΪС������λ��
						{
						//	printf("e=%d\n",e);
						
						}
					}
				}
			    for(d=1;d<b;d++)     //���������֣����ۼ�
				{
			     F1[i]=(ngca[i][j+d]-48)*pow(10,b-d-1)+F1[i];
                // printf("��%d�еĽ���������F1Ϊ%f\n",i,F1[i]);
				 
				}
				if(e>=1)
				{
	               for(f=1;f<e;f++)    //��С�����֣����ۼ�
				   {
                    F2[i]=(ngca[i][j+b+f]-48)*pow(10,-f)+F2[i];
                  //  printf("��%d�еĽ���������F2Ϊ%f\n",i,F2[i]);
				   }
				}
				F[i]=F1[i]+F2[i];
	 	        s31.Format("��%d�еĽ���������FΪ%f\r\n",i,F[i]);
				m_edit2+=s31;

			}
			else if((ngca[i][j]==70)&&((ngca[i][j+1]<48)||(ngca[i][j+1]>57)))
			{
				s32.Format("��%d��F����Ĵ����޷�ʶ�����飡\r\n",i);
				m_edit2+=s32;
				n++;
			}
		}
		b=0;
		e=0;
	}
    if(n!=0)
	{
       s33.Format("����%d��F����Ĵ����޷�ʶ�����飡\r\n",n);
       m_edit2+=s33;
	   //exit(0);
	}
	//*3.6�洢����ת�ٹ�����S�ֶ���Ϣ*//
	a=0;
	b=0;
	d=0;
	e=0;
	f=0;
	n=0;
    for(i=0;i<c;i++)
	{
		for(j=3;j<=nlc[i];j++) 
		{
			if((ngca[i][j]==83)&&(ngca[i][j+1]>=48)&&(ngca[i][j+1]<=57))  
			{
				for(b=1;(ngca[i][j+b]>=48)&&(ngca[i][j+b]<=57);b++)   //bΪ����λ��
				{
                    //printf("b=%d\n",b);
                    if(ngca[i][j+1+b]==46)  //����С���㣬��С��������λ��
					 {
						for(e=1;(ngca[i][j+1+b+e]>=48)&&(ngca[i][j+1+b+e2]<=57);e++)  //eΪС������λ��
						{
						//	printf("e=%d\n",e);
						
						}
					}
				}
			    for(d=1;d<b;d++)     //���������֣����ۼ�
				{
			     S1[i]=(ngca[i][j+d]-48)*pow(10,b-d-1)+S1[i];
                 //printf("��%d�е�����ת�ٹ�����S1Ϊ%f\n",i,S1[i]);
				}
				if(e>=1)
				{
	               for(f=1;f<e;f++)    //��С�����֣����ۼ�
				   {
                    S2[i]=(ngca[i][j+b+f]-48)*pow(10,-f)+S2[i];
                  //  printf("��%d�е�����ת�ٹ�����S2Ϊ%f\n",i,S2[i]);
				   }
				}
				S[i]=S1[i]+S2[i];
	 	        s34.Format("��%d�е�����ת�ٹ�����SΪ%f\r\n",i,S[i]);
				m_edit2+=s34;

			}
			else if((ngca[i][j]==70)&&((ngca[i][j+1]<48)||(ngca[i][j+1]>57)))
			{
				s35.Format("��%d��S����Ĵ����޷�ʶ�����飡\r\n",i);
				m_edit2+=s35;
				n++;
			}
		}
		b=0;
		e=0;
	}
    if(n!=0)
	{
       s36.Format("����%d��S����Ĵ����޷�ʶ�����飡\r\n",n);
	   m_edit2+=s36;
	   //exit(0);
	}
    //*3.7�洢���߹�����T�ֶ���Ϣ*//
    a=0;
	b=0;
	d=0;
	e=0;
	f=0;
	n=0;
    for(i=0;i<c;i++)
	{
		for(j=3;j<=nlc[i];j++) 
		{
			if((ngca[i][j]=='T')&&(ngca[i][j+1]>=48)&&(ngca[i][j+1]<=57))  
			{
				for(b=1;(ngca[i][j+b]>=48)&&(ngca[i][j+b]<=57);b++)   //bΪ����λ��
				{
                   // printf("b=%d\n",b);
                    if(ngca[i][j+1+b]==46)  //����С���㣬��С��������λ��
					 {
						for(e=1;(ngca[i][j+1+b+e]>=48)&&(ngca[i][j+1+b+e2]<=57);e++)  //eΪС������λ��
						{
						//	printf("e=%d\n",e);
						
						}
					}
				}
			    for(d=1;d<b;d++)     //���������֣����ۼ�
				{
			     T1[i]=(ngca[i][j+d]-48)*pow(10,b-d-1)+T1[i];
                // printf("��%d�еĵ��߹�����T1Ϊ%f\n",i,T1[i]);
				}
				if(e>=1)
				{
	               for(f=1;f<e;f++)    //��С�����֣����ۼ�
				   {
                    T2[i]=(ngca[i][j+b+f]-48)*pow(10,-f)+T2[i];
                  //  printf("��%d�еĵ��߹�����T2Ϊ%f\n",i,T2[i]);
				   }
				}
				T[i]=T1[i]+T2[i];
	 	        s37.Format("��%d�еĵ��߹�����TΪ%f\r\n",i,T[i]);
				m_edit2+=s37;

			}
			else if((ngca[i][j]==70)&&((ngca[i][j+1]<48)||(ngca[i][j+1]>57)))
			{
				s38.Format("��%d��T����Ĵ����޷�ʶ�����飡\r\n",i);
			    m_edit2+=s38;
				n++;
			}
		}
		b=0;
		e=0;
	}
    if(n!=0)
	{ 
       s39.Format("����%d��T����Ĵ����޷�ʶ�����飡\r\n",n);
       m_edit2+=s39;
	  // exit(0);
	}
    if(f>1)
	{ 
      s40.Format("���ߺ�ӦΪ���������飡\r\n");
      m_edit2+=s40;
	  // exit(0);
	}
    //*3.7�洢����������M�ֶ���Ϣ*//
    a=0;
	b=0;
	d=0;
	e=0;
	f=0;
	n=0;
    for(i=0;i<c;i++)
	{
		for(j=3;j<=nlc[i];j++) 
		{
			if((ngca[i][j]=='M')&&(ngca[i][j+1]>=48)&&(ngca[i][j+1]<=57))  
			{
				for(b=1;(ngca[i][j+b]>=48)&&(ngca[i][j+b]<=57);b++)   //bΪ����λ��
				{
                    //printf("b=%d\n",b);
                    if(ngca[i][j+1+b]==46)  //����С���㣬��С��������λ��
					 {
						for(e=1;(ngca[i][j+1+b+e]>=48)&&(ngca[i][j+1+b+e2]<=57);e++)  //eΪС������λ��
						{
						//	printf("e=%d\n",e);
						
						}
					}
				}
			    for(d=1;d<b;d++)     //���������֣����ۼ�
				{
			     M1[i]=(ngca[i][j+d]-48)*pow(10,b-d-1)+M1[i];
                // printf("��%d�еĸ���������M1Ϊ%f\n",i,M1[i]);
				}
				if(e>=1)
				{
	               for(f=1;f<e;f++)    //��С�����֣����ۼ�
				   {
                    M2[i]=(ngca[i][j+b+f]-48)*pow(10,-f)+M2[i];
                  //  printf("��%d�еĸ���������M2Ϊ%f\n",i,M2[i]);
				   }
				}
				M[i][0]=M1[i]+M2[i];
				M[i][1]=1;
	 	        s41.Format("��%d�еĸ���������MΪ%f\r\n",i,M[i][0]);
				m_edit2+=s41;
				if(M[i][0]<0||M[i][0]>99)   //�жϸ����������Ƿ�Ϊ��λ��
				{
					s42.Format("��%d�и��������ֲ��ڿ�ʶ��Χ�ڣ��뱣֤0<=M<=99!\r\n",i);
					m_edit2+=s42;
				}

			}
			else if((ngca[i][j]==70)&&((ngca[i][j+1]<48)||(ngca[i][j+1]>57)))
			{
				s43.Format("��%d��M����Ĵ����޷�ʶ�����飡\r\n",i);
				m_edit2+=s43;
				n++;
			}
		}
		b=0;
		e=0;
	}
    if(n!=0)
	{ 
       s44.Format("����%d��M����Ĵ����޷�ʶ�����飡\r\n",n);
	   m_edit2+=s44;
	   //exit(0);
	}
    if(f>1)
	{ 
       s45.Format("����������ӦΪ���������飡\r\n");
	   m_edit2+=s45;
	   //exit(0);
	}
    UpdateData(FALSE);	


	
}

void CMy0422Dlg::OnDone1()     //ִ�г���
{
	// TODO: Add your control notification handler code here
	for(i=0;i<=2;i++)
	{
        d5480_set_pulse_outmode(i,4);        //��������ģʽ��0��1��2���ᣨ�ֱ����X,Y,Z���򣩵����������������
	}
    d5480_write_SEVON_PIN(0,0);        //���SEVON�źţ����ڿ����ŷ��綯��������
	for(i=0;i<c;i++)
	{
		for(j=0;j<2;j++)        //G[i][2]�Ĺ�����ȷ��׼��������ȷʵ�����ڸ��У���ΪĬ�ϵ�����G[][]�ĳ�ֵ����Ϊ0�������������������0
		{
			if((G[i][j]==90||G[i][j+1]==90)&&j==0)   //�˶�ģʽΪ�����˶�����
			{
				AC=1;      //���ƿ���1Ϊ�����˶�
				if(G[i+1][0]!=91&&G[i+1][1]!=91)   //���ģ̬����
				{
					if(G[i+1][2]==0)    //�����һ��û��G����
					{
                        G[i+1][0]=90;
					    G[i+1][1]=-1;
					    G[i+1][2]=1;
					}
					if(G[i+1][2]==1)    //�����һ����G����
					{
					    G[i+1][1]=90;
					}
				}
			}
			if((G[i][j]==91||G[i][j+1]==91)&&j==0)   //�˶�ģʽΪ����˶�����
			{
				AC=0;      //���ƿ���0Ϊ����˶�
				if(G[i+1][0]!=90&&G[i+1][1]!=90)   //���ģ̬����
				{
					if(G[i+1][2]==0)    //�����һ��û��G����
					{
                        G[i+1][0]=91;
					    G[i+1][1]=-1;
					    G[i+1][2]=1;
					}
					if(G[i+1][2]==1)    //�����һ����G����
					{
					    G[i+1][1]=91;
					}
				}
			}
			if(G[i][j]==0&&G[i][2]==1)            //ִ�п��ٽ����˶�,��λ���ƺ�������ô��ʼ����ô�������˶��������������Ļ���
			{
				if(G[i+1][0]!=1&&G[i+1][1]!=1||G[i+1][0]!=2&&G[i+1][1]!=2&&G[i+1][0]!=3&&G[i+1][1]!=3) //���ģ̬���⣬����һ��û��ͬ��G����ʱ����һ���Զ���ֵΪ��ͬ����
				{
					if(G[i+1][2]==0)
					{
                        G[i+1][0]=0;
					    G[i+1][1]=-1;
					    G[i+1][2]=1;
					}
					if(G[i+1][2]==1)
					{
						G[i+1][1]=0;
					}
				}
				if(X[i][1]==1)            //G00������X����
				{
                    XL=-X[i][0]*2500;      //���������
					d5480_pmove(0,XL,AC);      //������ţ��˶����루�軻��������������˶�ģʽ�����0������1��
				}
				if(Y[i][1]==1)            //G00������Y����
				{
                    YL=Y[i][0]*2500;      //���������
					d5480_pmove(0,YL,AC);      //������ţ��˶����루�軻��������������˶�ģʽ�����0������1��
				}
				if(Z[i][1]==1)            //G00������Z����
				{
					ZL=-Z[i][0]*2500;      //���������
					d5480_pmove(0,ZL,AC);      //������ţ��˶����루�軻��������������˶�ģʽ�����0������1��
				}
			}
            if(G[i][j]==1&&G[i][2]==1)            //ִ��ֱ���˶�,����ֱ�߲岹��������ô��ʼ����ô�������˶��������������Ļ���
			{
				if(G[i+1][0]!=0&&G[i+1][1]!=0||G[i+1][0]!=2&&G[i+1][1]!=2&&G[i+1][0]!=3&&G[i+1][1]!=3) //���ģ̬���⣬����һ��û��ͬ��G����ʱ����һ���Զ���ֵΪ��ͬ����
				{
					if(G[i+1][2]==0)
					{
                        G[i+1][0]=1;
					    G[i+1][1]=-1;
					    G[i+1][2]=1;
					}
					if(G[i+1][2]==1)
					{
						G[i+1][1]=1;
					}
				}
				XL=-X[i][0]*2500;      //���������
                YL=Y[i][0]*2500;      //���������
				d5480_line2(0,XL,1,YL,AC);      //������ţ��˶����루�軻���������������ţ����������˶�ģʽ�����0������1��
			}
			if(G[i][j]==2&&G[i][2]==1)            //ִ��˳ʱ�뷽��Բ���岹
			{
				if(G[i+1][0]!=1&&G[i+1][1]!=1||G[i+1][0]!=0&&G[i+1][1]!=0&&G[i+1][0]!=3&&G[i+1][1]!=3) //���ģ̬���⣬����һ��û��ͬ��G����ʱ����һ���Զ���ֵΪ��ͬ����
				{
					if(G[i+1][2]==0)
					{
                        G[i+1][0]=2;
					    G[i+1][1]=-1;
					    G[i+1][2]=1;
					}
					if(G[i+1][2]==1)
					{
						G[i+1][1]=2;
					}
				}
			    
				if(G[i][0]==90||G[i][1]==90)//��������
				{
					XL=-X[i][0]*2500;      //�յ����꣬���������
                    YL=Y[i][0]*2500;      //���������
					IL=-I[i][0]*2500;      //Բ�����꣬���������
					JL=J[i][0]*2500;
					
					WORD xy[2]={0,1};
					long xy_pos[2]={XL,YL};
					long ij_pos[2]={IL,JL};
					d5480_arc_move(xy,xy_pos,ij_pos,0);   //�岹�ᣬ�յ㣬Բ�ģ�˳ʱ��/��ʱ��
				}
			}
			if(G[i][j]==3&&G[i][2]==1)            //ִ����ʱ�뷽��Բ���岹
			{
				if(G[i+1][0]!=1&&G[i+1][1]!=1||G[i+1][0]!=2&&G[i+1][1]!=2&&G[i+1][0]!=0&&G[i+1][1]!=0) //���ģ̬���⣬����һ��û��ͬ��G����ʱ����һ���Զ���ֵΪ��ͬ����
				{
					if(G[i+1][2]==0)
					{
                        G[i+1][0]=3;
					    G[i+1][1]=-1;
					    G[i+1][2]=1;
					}
					if(G[i+1][2]==1)
					{
						G[i+1][1]=3;
					}
				}
				if(G[i][0]==90||G[i][1]==90)//��������
				{
					XL=-X[i][0]*2500;      //�յ����꣬���������
                    YL=Y[i][0]*2500;      //���������
					IL=-I[i][0]*2500;      //Բ�����꣬���������
					JL=J[i][0]*2500;
					
					WORD xy[2]={0,1};
					long xy_pos[2]={XL,YL};
					long ij_pos[2]={IL,JL};
					d5480_arc_move(xy,xy_pos,ij_pos,1);   //�岹�ᣬ�յ㣬Բ�ģ�˳ʱ��/��ʱ��
				}
			}
		}
	}
}
			
			
			
	

void CMy0422Dlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}
void CMy0422Dlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnClose();
}
void CMy0422Dlg::OnChangeedit() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}
void CMy0422Dlg::OnChangeEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}
void CMy0422Dlg::OnChangeEdit2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}
void CMy0422Dlg::OnButtonEstop()    //����ֹͣ
{
	// TODO: Add your control notification handler code here
	d5480_emg_stop();
}
void CMy0422Dlg::OnButtonCancel()  //�˳�
{
	// TODO: Add your control notification handler code here
	d5480_board_close();
//	KillTimer( IDC_TIMER );
	CDialog::OnCancel();
}
void CMy0422Dlg::OnButtonReset()   //λ������
{
	// TODO: Add your control notification handler code here
	for (int i=0;i<3;i++)
	{
		d5480_set_position(i,0);
	}	
	
}
//void CAboutDlg::OnTimer(UINT nIDEvent) 
//{
	// TODO: Add your message handler code here and/or call default
	
//	CDialog::OnTimer(nIDEvent);
//}

//void CMy0422Dlg::OnTimer(UINT nIDEvent) //ʵʱ�����˶�����
//{
	// TODO: Add your message handler code here and/or call default
	//status=d5480_check_done(m_nAxis);
	//GetDlgItem( IDC_EDIT1 )->SetWindowText( status?"��ֹ":"�˶���");

//	CString Xpos;
//CString Ypos;
	//CString Zpos;
	//CString Upos;

//	m_nXpos=d5480_get_position(0);
//	m_nYpos=d5480_get_position(1);
	//m_nZpos=d5480_get_position(2);
	//m_nUpos=d5480_get_position(3);
	
	//Xpos.Format("%d",m_nXpos);
	//Ypos.Format("%d",m_nYpos);
//	Zpos.Format("%d",m_nZpos);
	//Upos.Format("%d",m_nUpos);

	//GetDlgItem( IDC_EDIT_XPOS )->SetWindowText( Xpos );     //SetWindowText�����ı�ָ�����ڵı��������ı����ݣ���������б������������ָ��������һ���ؼ�����ı�ؼ����ı����ݡ�Ȼ����SetWindowText�������ı�����Ӧ�ó����еĿؼ����ı����ݡ�[1] 
	//GetDlgItem( IDC_EDIT_YPOS )->SetWindowText( Ypos );
	//GetDlgItem( IDC_EDIT_ZPOS )->SetWindowText( Zpos );
	//GetDlgItem( IDC_EDIT_UPOS )->SetWindowText( Upos );

	//TRACE("X���ٶȣ�%d",d5480_read_vector_speed(0));
//	CDialog::OnTimer(nIDEvent);
//}