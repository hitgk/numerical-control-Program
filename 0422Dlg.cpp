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
#include "DMC5480.h"    //添加的
//#include<time.h>        //添加的

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

FILE  *fp;
	char  gcr[80];          //gcr为G代码读取缩写
	char  gca[100][100];    //gca为G代码存储缩写,用于存储源代码
	char  ngca[100][100];   //用于存储去除无用信息之后的G代码
	char  lc[80];           //用于存储源G代码的每一行的列数
	char  nlc[80];          //用于存储换行符前面的G代码列数
	int   hhf[100];         //用于标记不存在换行符的行数
	int   nc[100]={0};      //用于标价存在不可识别代码的个数,行相对应
	int   i=0,j=0,a=0,b=0,b1=0,b2=0,c=0,d=0,e=0,e1=0,e2=0,f=0,length=0,n=0,n1=0,n2=0,n3=0,AC;
	int   nw[100]={0};      //用于标记程序段段号位数信息
	int   N[100]={0};       //用于存储转化成数字的N字段信息
	int   G[100][3]={0};    //用于存储准备功能字G信息,G[][2]用来标记所在的行
	float X[100][2]={0.0};     //用于存储地址符为X的坐标信息,X[][0]存储坐标，X[][1]标记所在的行
	float X1[100]={0.0};
    float X2[100]={0.0};
    float Y[100][2]={0.0};     //用于存储地址符为Y的坐标信息
	float Y1[100]={0.0};
    float Y2[100]={0.0};
    float Z[100][2]={0.0};     //用于存储地址符为Z的坐标信息
	float Z1[100]={0.0};
    float Z2[100]={0.0};
	float I[100][2]={0.0};     //用于存储地址符为I的坐标信息
	float I1[100]={0.0};
    float I2[100]={0.0};
	float J[100][2]={0.0};     //用于存储地址符为J的坐标信息
	float J1[100]={0.0};
    float J2[100]={0.0};
    float R[100][2]={0.0};     //用于存储地址符为R的坐标信息
	float R1[100]={0.0};
    float R2[100]={0.0};
    float F[100]={0.0};     //用于存储进给功能字F信息
	float F1[100]={0.0};
    float F2[100]={0.0};
    float S[100]={0.0};     //用于主轴转速功能字S信息
	float S1[100]={0.0};
    float S2[100]={0.0};
    float T[100]={0.0};     //用于刀具功能字T信息
	float T1[100]={0.0};
    float T2[100]={0.0};
    float M[100][2]={0.0};     //用于辅助功能字M信息,M[][1]用于标记所在的行
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
	if(d5480_board_init()<=0)//控制卡的初始化操作
		MessageBox("初始化DMC5480卡失败！","出错");
    
	//SetTimer(IDC_TIMER,100,NULL);//SetTimer就是设置定时器，参数为 定时器ID,间隔时间，单位为毫秒，响应函数。每个间隔时间调用一次OnTimer函数。KillTimer就是移走定时器
	
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

void CMy0422Dlg::OnRead1()     //执行源代码的读取
{
    
	if((fp=fopen("shukong.txt","rt"))==NULL)  //文件不能正常读取
    {
        MessageBox("Cannot open file!\n");
        getch();
        exit(1);
    }
	MessageBox("文件的内容如下");
    
    while(fgets(gcr,80,fp))     //条件：整个读取代码结束
	{
		c++;                    //求代码的行数，用于检错用
		//printf("第%d行的程序代码为：\n",i);
		//m_edit.Format("%s",gcr);
        
		s0.Format("%s\r\n",gcr); //源代码按行输出并换行
        m_edit+=s0;


		
		
	    


        while(gcr[j]!='\0')    //求每一行G代码的长度
		{        
			j++;        
			length++;
		}
		lc[i]=length;        //存储每一行的列数
		//printf("该程序段的长度为%d\n",length);
     
        for(a=0;a<=length;a++)
		{
		 b=i;
         gca[b][a]=gcr[a];   //将G代码按行存到gca数组当中
		}
        //printf("%s\n",gca[b]); //gca数组里面的G代码按行输出
        s1.Format("%s\r\n",gca[b]); //源代码按行输出并换行
        m_edit1+=s1;

        j=0;                 //重新赋值再循环
        length=0;
		i++;
	     
	}
    UpdateData(FALSE);	
   
    
}

void CMy0422Dlg::OnCheak1() 
{
	// TODO: Add your control notification handler code here
    //*2 实现功能：G代码检错*//
	//*2.1 实现功能：判断每一行G代码是否都有换行符*//
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
				//printf("第%d行有换行符\n",i);
                nlc[i]=j;     //存储有换行符代码前的列数
				}
				else
				{
					//printf("第%d行没有换行符\n",a);
					hhf[b]=a; //用于标记没有换行符的行
					a=a+1;    //当某一行没有换行符时则i要比a多循环一次，为了保证后面顺利检测应保证a=i
					b++;
					d++;      //用于标记没有换行符的行数	
				}
                a++;
			}	
		}	
	}

    
	if(d!=0)     //对于没有换行符的行数进行提示，并结束程序
	{
		for(i=0;i<d;i++)
		{
			s2.Format("检测到第%d行没有换行符，请加上换行符\r\n",hhf[i]);
            m_edit2+=s2;
		}
		//exit(0);
        
	}
    //*2.2实现功能：判断每一行G代码换行符前是否存在无法识别的代码*//
	a=0;
	b=0;
	e=0;
    for(i=0;i<c;i++)   //不要加等号
	{
        for(j=0;j<=nlc[i];j++)
		{
        if(gca[i][j]!=59)
		{
          n=gca[i][j];
          if(((n>=65)&&(n<=90))||((n>=48)&&(n<=57))||(n==43)||(n==45)||(n==46)||(n==61)||(n==59)||(n==32))
		  {
			 // printf("第%d行代码可识别",i);
			  if((i==(c-1))&&(j==nlc[i]-1)&&(b==0))
			  {
				  s3.Format("程序段不存在无法识别的代码!\r\n");
                  m_edit2+=s3;
				  //printf("%d\n%d\n",i,j);
			  }
		  }
		  else
		  {
			  //m_edit2.Format("第%d行代码存在不可识别代码\n",i);
              e++;        //用于标记该行无法识别的代码个数
			  nc[i]=e;    //用于存储该行无法识别代码的个数	
			  a=i;        //用于标价存在无法识别代码的最大行数 
			  b++;        //用于判断整个程序段是否存在无法识别的代码
		  }   
		}
        else
		{
		break;
		}
		}
		e=0;     //e清零，执行下一行检测
	}

	for(i=0;i<100;i++)     //对于存在无法识别代码的行数进行提示，并结束程序
	{
		if(nc[i]!=0)
		{
			s4.Format("检测到第%d行存在%d个无法识别代码\r\n",i,nc[i]);
            m_edit2+=s4;

			//if(i==a)       //当检测的行数为出现无法识别代码的最后一行时，结束整个程序
		//	{
            // exit(0);
             //  break;
		//	}
		}
	}
    //*3 实现功能：G代码信息分类存储*//
	//*3.1按行精简G代码*//
    a=0;
	b=0;
	for(i=0;i<c;i++)        //按行精简
	{
      for(j=0;j<=nlc[i];j++)
	  {
		  n=gca[i][j];
          if(((n>=65)&&(n<=90))||((n>=48)&&(n<=57))||(n==43)||(n==45)||(n==46)||(n==61)||(n==59))//去除无用字符，包括中文、空格
		  {
			  if(n==59)    //当检测到程序段结束符时跳出当前循环，执行下一个循环
			  {
				  break;
			  }
			  else 
			  {

             // printf("第%d行第%d列的ASC码值为%d\n",i,j,n);
			  s5.Format("%c",gca[i][j]);   //输出精简后的代码
              m_edit2+=s5;
              ngca[a][b]=gca[i][j];
			  }
		  }
		  
	  b++;  
	  }
	  b=0;
	  a++;
	  s6.Format("\r\n");  //用于代码的换行
      m_edit2+=s6;
	  
	}
    //*3.2存储G代码的N字段信息*//
	//*3.2.1判断每一行的程序段由几位数字组成并存到一维数组n*//
    a=0;
	b=0;
	d=0;
	e=0;
	n=0;
    
    for(i=0;i<c;i++)
	{
      if(ngca[i][0]==78)   //判断每一行代码的首字母是否为N
	  {
		  for(j=1;j<=5;j++)     //先判断每一行的程序段由几位数字组成
		  {
            // printf("ac=%d,i=%d\n",c,i);
			 if((j==5)&&((ngca[i][j]>=48)&&(ngca[i][j]<=57)))      //如果第五位仍为数字字符，则可判断段号超过允许值
			  {
				  s7.Format("第%d行程序段超过最大允许值，请保证程序段段号在四位数以内！\r\n",i);
                  m_edit2+=s7;
				  a++;
			  }
			  if((j==1)&&((ngca[i][j]<48)||(ngca[i][j]>57)))      //如果第一位为非数字字符，则可判断段号该行没有程序段段号
			  {
				  s8.Format("第%d行没有程序段段号！\r\n",i);
				  m_edit2+=s8;
				  b++;
			  }
			  if((ngca[i][j]>=48)&&(ngca[i][j]<=57))     
			  {
				  e++;
				  nw[i]=e;      //将每一行的位数信息出递给数组n
				  //printf("c=%d,i=%d\n",c,i);
			  }
			else      //当遇到非数字字符时，结束当前循环，执行下一行
				break;
		  }
	  }
      if(ngca[i][0]!=78)
	  {
       d++;
       s9.Format("第%d行没有程序段段号N\n",i);
	   m_edit2+=s9;
	  }
	  e=0;
	}

	if((a!=0)||(b!=0)||(d!=0))
	{
    
	if(a!=0)
    s10.Format("共有%d行程序段超过最大允许值，请保证程序段段号在四位数以内！\r\n",a);
	m_edit2+=s10;
    if(b!=0)
    s11.Format("共有%d行没有程序段段号！\r\n",b);
    m_edit2+=s11;
	if(d!=0)
	s12.Format("共有%d行没有程序段段号N\r\n",d);
    m_edit2+=s12;
	//exit(0);
	}
    //*3.2.2将N字段的字符信息转成数字信息并存到一维数组N*//
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
				if(i==a)      //行不变
				{
					n=(gca[i][j]-48)*pow(10,(nw[i]-j))+n;  //将字符信息转成数字信息
					N[i]=n;        //将程序段N的数字信息赋值给数组N[]
					s13.Format("第%d行的程序段段号为%d\r\n",i,N[i]);
                    m_edit2+=s13;

				}
			}
		}
	   n=0;
       a++;
	}
	//*3.3存储G代码的准备功能字G字段信息并存储到数组G[100][3]*//
    a=0;
	b=0;
    for(i=0;i<c;i++)
	{
		for(j=3;j<=nlc[i];j++) 
		{
			if(ngca[i][j]==71)
			{
			    if(((ngca[i][j+1]<=57)&&(ngca[i][j+1]>=48))&&((ngca[i][j+2]<=57)&&(ngca[i][j+2]>=48))&&((ngca[i][j+3]>57)||(ngca[i][j+3]<48)))            //当准备功能字G后面为两位数字时执行循环
				{    
					 G[i][1]=-1;        //防止G[][1]默认等于0扰乱判断
				     G[i][a]=(ngca[i][j+1]-48)*10+(ngca[i][j+2]-48);  //将准备功能字的字符信息转换成数字信息
					 G[i][2]=1;       //标记所在的行
					 s14.Format("第%d行准备功能字为%d\r\n",i,G[i][a]);
					 m_edit2+=s14;
                     a++;
				}
                else if(((ngca[i][j+1]<=57)&&(ngca[i][j+1]>=48))&&((ngca[i][j+2]>57)||(ngca[i][j+2]<48)))            //当准备功能字G后面为一位数字时执行循环
				{   
                     G[i][1]=-1;        //防止G[][1]默认等于0扰乱判断
				     G[i][a]=ngca[i][j+1]-48;                        //将准备功能字的字符信息转换成数字信息
                     G[i][2]=1;       //标记所在的行
                     s14.Format("第%d行准备功能字为%d\r\n",i,G[i][a]);
                     m_edit2+=s14;
                     a++;
				}
			    else
				{
					s14.Format("第%d行的准备功能字无法识别\r\n",i);
                    m_edit2+=s14;
					b++;
				}
			}
		}
		a=0;
	}
	if(b!=0)
	{
		s15.Format("共有%d处的准备功能字无法识别，请重新检查代码！\r\n",b);
		m_edit2+=s15;
		//exit(0);
	}
    if(b==0)
	{
		s15.Format("准备功能字可以识别\n");
		m_edit2+=s15;
	}
	//*3.4存储G代码的坐标字X,Y,Z,R字段信息*//
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
			//*存储X字段信息*//
			if((ngca[i][j]==88)&&(ngca[i][j+1]==43))     //判断坐标字是否为X且后一位为“+”号
			{				
				for(b=1;(ngca[i][j+1+b]>=48)&&(ngca[i][j+1+b]<=57);b++)   //b为整数位数
				{
				     printf("b=%d\n",b);
                     if(ngca[i][j+2+b]==46)  //存在小数点，求小数点后面的位数
					 {
						for(e=1;(ngca[i][j+2+b+e]>=48)&&(ngca[i][j+2+b+e]<=57);e++)  //e为小数点后的位数
						{
							s16.Format("e=%d\r\n",e);
							m_edit2+=s16;
						
						}
					}
				     
				} 
                for(d=1;d<b;d++)     //先求整数部分，并累加
				{
			     X1[i]=(ngca[i][j+1+d]-48)*pow(10,b-d-1)+X1[i];
                 s17.Format("第%d行的X坐标字为%f\r\n",i,X1[i]);
				 m_edit2+=s17;
				}
				if(e>=1)
				{
	               for(f=1;f<e;f++)    //再求小数部分，并累加
				   {
                    X2[i]=(ngca[i][j+1+b+f]-48)*pow(10,-f)+X2[i];
                    s18.Format("第%d行的X坐标字为%f\r\n",i,X2[i]);
					m_edit2+=s18;	
				   }
				}
				X[i][0]=X1[i]+X2[i];
				X[i][1]=1;            //标记所在的行
	 	        s19.Format("第%d行的X坐标字为%f\r\n",i,X[i][0]); 
				m_edit2+=s19;
			}
            else if((ngca[i][j]==88)&&(ngca[i][j+1]==45))     //判断坐标字是否为X且后一位为“-”号
            {				
				for(b1=1;(ngca[i][j+1+b1]>=48)&&(ngca[i][j+1+b1]<=57);b1++)   //b为整数位数
				{
				     s20.Format("b1=%d\r\n",b1);
					 m_edit2+=s20;
                     if(ngca[i][j+2+b1]==46)  //存在小数点，求小数点后面的位数
					 {
						for(e1=1;(ngca[i][j+2+b1+e1]>=48)&&(ngca[i][j+2+b1+e1]<=57);e1++)  //e为小数点后的位数
						{
							s21.Format("e1=%d\r\n",e1);
							m_edit2+=s21;
						
						}
					}
				     
				} 
                for(d=1;d<b1;d++)     //先求整数部分，并累加
				{
			     X1[i]=(ngca[i][j+1+d]-48)*pow(10,b1-d-1)+X1[i];
                 s22.Format("第%d行的X坐标字为%f\r\n",i,X1[i]);
				 m_edit2+=s22;
				}
				if(e1>=1)
				{
	               for(f=1;f<e1;f++)    //再求小数部分，并累加
				   {
                    X2[i]=(ngca[i][j+1+b1+f]-48)*pow(10,-f)+X2[i];
                    s23.Format("第%d行的Xa坐标字为%f\r\n",i,X2[i]);
					m_edit2+=s23;
				   }
				}
				X[i][0]=-(X1[i]+X2[i]);
                X[i][1]=1;            //标记所在的行
	 	        s24.Format("第%d行的X坐标字为%f\r\n",i,X[i][1]);
				m_edit2+=s24;
			}
            else if((ngca[i][j]==88)&&(ngca[i][j+1]>=48)&&(ngca[i][j+1]<=57))     //判断坐标字是否为X且后一位为整数
            {				
				for(b2=1;(ngca[i][j+b2]>=48)&&(ngca[i][j+b2]<=57);b2++)   //b为整数位数
				{
				     s25.Format("b2=%d\r\n",b2);
					 m_edit2+=s25;
                     if(ngca[i][j+1+b2]==46)  //存在小数点，求小数点后面的位数
					 {
						for(e2=1;(ngca[i][j+1+b2+e2]>=48)&&(ngca[i][j+1+b2+e2]<=57);e2++)  //e为小数点后的位数
						{
							s26.Format("e2=%d\r\n",e2);
							m_edit2+=s26;
						
						}
					}
				     
				} 
                for(d=1;d<b2;d++)     //先求整数部分，并累加
				{
			     X1[i]=(ngca[i][j+d]-48)*pow(10,b2-d-1)+X1[i];
                 s27.Format("第%d行的X坐标字为%f\r\n",i,X1[i]);
				 m_edit2+=s27;
				}
				if(e2>=1)
				{
	               for(f=1;f<e2;f++)    //再求小数部分，并累加
				   {
                    X2[i]=(ngca[i][j+b2+f]-48)*pow(10,-f)+X2[i];
                    s28.Format("第%d行的Xa坐标字为%f\r\n",i,X2[i]);
					m_edit2+=s28;
				   }
				}
				X[i][0]=X1[i]+X2[i];
                X[i][1]=1;            //标记所在的行
	 	        s29.Format("第%d行的X坐标字为%f\r\n",i,X[i][0]);
				m_edit2+=s29;
			}
			else if((ngca[i][j]==88)&&((ngca[i][j+1]<48)||(ngca[i][j+1]>57))&&(ngca[i][j+1]!=43)&&(ngca[i][j+1]!=45))
			{
				s30.Format("第%d行X后面的代码无法识别，请检查！\r\n",i);
				m_edit2+=s30;
				n++;
			}


            //*存储Y字段信息*//
	        if((ngca[i][j]==89)&&(ngca[i][j+1]==43))     //判断坐标字是否为Y且后一位为“+”号
			{				
				for(b=1;(ngca[i][j+1+b]>=48)&&(ngca[i][j+1+b]<=57);b++)   //b为整数位数
				{
				     //printf("b=%d\n",b);
                     if(ngca[i][j+2+b]==46)  //存在小数点，求小数点后面的位数
					 {
						for(e=1;(ngca[i][j+2+b+e]>=48)&&(ngca[i][j+2+b+e]<=57);e++)  //e为小数点后的位数
						{
						//	printf("e=%d\n",e);
						
						}
					}
				     
				} 
                for(d=1;d<b;d++)     //先求整数部分，并累加
				{
			     Y1[i]=(ngca[i][j+1+d]-48)*pow(10,b-d-1)+Y1[i];
                // printf("第%d行的Y坐标字为%f\n",i,Y1[i]);
				}
				if(e>=1)
				{
	               for(f=1;f<e;f++)    //再求小数部分，并累加
				   {
                    Y2[i]=(ngca[i][j+1+b+f]-48)*pow(10,-f)+Y2[i];
                    //printf("第%d行的Y坐标字为%f\n",i,Y2[i]);
				   }
				}
				Y[i][0]=Y1[i]+Y2[i];
                Y[i][1]=1;            //标记所在的行
	 	       // printf("第%d行的Y坐标字为%f\n",i,Y[i][0]);  
			}
            else if((ngca[i][j]==89)&&(ngca[i][j+1]==45))     //判断坐标字是否为Y且后一位为“-”号
            {				
				for(b1=1;(ngca[i][j+1+b1]>=48)&&(ngca[i][j+1+b1]<=57);b1++)   //b为整数位数
				{
				     //printf("b1=%d\n",b1);
                     if(ngca[i][j+2+b1]==46)  //存在小数点，求小数点后面的位数
					 {
						for(e1=1;(ngca[i][j+2+b1+e1]>=48)&&(ngca[i][j+2+b1+e1]<=57);e1++)  //e为小数点后的位数
						{
						//	printf("e1=%d\n",e1);
						
						}
					}
				     
				} 
                for(d=1;d<b1;d++)     //先求整数部分，并累加
				{
			     Y1[i]=(ngca[i][j+1+d]-48)*pow(10,b1-d-1)+Y1[i];
                 //printf("第%d行的Y坐标字为%f\n",i,Y1[i]);
				}
				if(e1>=1)
				{
	               for(f=1;f<e1;f++)    //再求小数部分，并累加
				   {
                    Y2[i]=(ngca[i][j+1+b1+f]-48)*pow(10,-f)+Y2[i];
                    //printf("第%d行的Y坐标字为%f\n",i,Y2[i]);
				   }
				}
				Y[i][0]=-(Y1[i]+Y2[i]);
                Y[i][1]=1;            //标记所在的行
	 	        //printf("第%d行的Y坐标字为%f\n",i,Y[i][0]);  
			}
            else if((ngca[i][j]==89)&&(ngca[i][j+1]>=48)&&(ngca[i][j+1]<=57))     //判断坐标字是否为Y且后一位为整数
            {				
				for(b2=1;(ngca[i][j+b2]>=48)&&(ngca[i][j+b2]<=57);b2++)   //b为整数位数
				{
				     //printf("b2=%d\n",b2);
                     if(ngca[i][j+1+b2]==46)  //存在小数点，求小数点后面的位数
					 {
						for(e2=1;(ngca[i][j+1+b2+e2]>=48)&&(ngca[i][j+1+b2+e2]<=57);e2++)  //e为小数点后的位数
						{
						//	printf("e2=%d\n",e2);
						
						}
					}
				     
				} 
                for(d=1;d<b2;d++)     //先求整数部分，并累加
				{
			     Y1[i]=(ngca[i][j+d]-48)*pow(10,b2-d-1)+Y1[i];
                 //printf("第%d行的Y坐标字为%f\n",i,Y1[i]);
				}
				if(e2>=1)
				{
	               for(f=1;f<e2;f++)    //再求小数部分，并累加
				   {
                    Y2[i]=(ngca[i][j+b2+f]-48)*pow(10,-f)+Y2[i];
                    //printf("第%d行的Y坐标字为%f\n",i,Y2[i]);
				   }
				}
				Y[i][0]=Y1[i]+Y2[i];
                Y[i][1]=1;            //标记所在的行
	 	        //printf("第%d行的Y坐标字为%f\n",i,Y[i][0]);  
			}
			else if((ngca[i][j]==89)&&((ngca[i][j+1]<48)||(ngca[i][j+1]>57))&&(ngca[i][j+1]!=43)&&(ngca[i][j+1]!=45))
			{
			//	printf("第%d行Y后面的代码无法识别，请检查！\n",i);
				n1++;
			}

            
            //*存储Z字段信息*//
	        if((ngca[i][j]==90)&&(ngca[i][j+1]==43))     //判断坐标字是否为Z且后一位为“+”号
			{				
				for(b=1;(ngca[i][j+1+b]>=48)&&(ngca[i][j+1+b]<=57);b++)   //b为整数位数
				{
				    // printf("b=%d\n",b);
                     if(ngca[i][j+2+b]==46)  //存在小数点，求小数点后面的位数
					 {
						for(e=1;(ngca[i][j+2+b+e]>=48)&&(ngca[i][j+2+b+e]<=57);e++)  //e为小数点后的位数
						{
						//	printf("e=%d\n",e);
						
						}
					}
				     
				} 
                for(d=1;d<b;d++)     //先求整数部分，并累加
				{
			     Z1[i]=(ngca[i][j+1+d]-48)*pow(10,b-d-1)+Z1[i];
                 //printf("第%d行的Z坐标字为%f\n",i,Z1[i]);
				}
				if(e>=1)
				{
	               for(f=1;f<e;f++)    //再求小数部分，并累加
				   {
                    Z2[i]=(ngca[i][j+1+b+f]-48)*pow(10,-f)+Z2[i];
                   // printf("第%d行的Z坐标字为%f\n",i,Z2[i]);
				   }
				}
				Z[i][0]=Z1[i]+Z2[i];
                Z[i][1]=1;            //标记所在的行
	 	        //printf("第%d行的Z坐标字为%f\n",i,Z[i][0]);  
			}
            else if((ngca[i][j]==90)&&(ngca[i][j+1]==45))     //判断坐标字是否为Z且后一位为“-”号
            {				
				for(b1=1;(ngca[i][j+1+b1]>=48)&&(ngca[i][j+1+b1]<=57);b1++)   //b为整数位数
				{
				     //printf("b1=%d\n",b1);
                     if(ngca[i][j+2+b1]==46)  //存在小数点，求小数点后面的位数
					 {
						for(e1=1;(ngca[i][j+2+b1+e1]>=48)&&(ngca[i][j+2+b1+e1]<=57);e1++)  //e为小数点后的位数
						{
						//	printf("e1=%d\n",e1);
						
						}
					}
				     
				} 
                for(d=1;d<b1;d++)     //先求整数部分，并累加
				{
			     Z1[i]=(ngca[i][j+1+d]-48)*pow(10,b1-d-1)+Z1[i];
                 //printf("第%d行的Z坐标字为%f\n",i,Z1[i]);
				}
				if(e1>=1)
				{
	               for(f=1;f<e1;f++)    //再求小数部分，并累加
				   {
                    Z2[i]=(ngca[i][j+1+b1+f]-48)*pow(10,-f)+Z2[i];
                   // printf("第%d行的Z坐标字为%f\n",i,Z2[i]);
				   }
				}
				Z[i][0]=-(Z1[i]+Z2[i]);
                Z[i][1]=1;            //标记所在的行
	 	       // printf("第%d行的Z坐标字为%f\n",i,Z[i][0]);  
			}
            else if((ngca[i][j]==90)&&(ngca[i][j+1]>=48)&&(ngca[i][j+1]<=57))     //判断坐标字是否为Z且后一位为整数
            {				
				for(b2=1;(ngca[i][j+b2]>=48)&&(ngca[i][j+b2]<=57);b2++)   //b为整数位数
				{
				     printf("b2=%d\n",b2);
                     if(ngca[i][j+1+b2]==46)  //存在小数点，求小数点后面的位数
					 {
						for(e2=1;(ngca[i][j+1+b2+e2]>=48)&&(ngca[i][j+1+b2+e2]<=57);e2++)  //e为小数点后的位数
						{
						//	printf("e2=%d\n",e2);
						
						}
					}
				     
				} 
                for(d=1;d<b2;d++)     //先求整数部分，并累加
				{
			     Z1[i]=(ngca[i][j+d]-48)*pow(10,b2-d-1)+Z1[i];
                // printf("第%d行的Z坐标字为%f\n",i,Z1[i]);
				}
				if(e2>=1)
				{
	               for(f=1;f<e2;f++)    //再求小数部分，并累加
				   {
                    Z2[i]=(ngca[i][j+b2+f]-48)*pow(10,-f)+Z2[i];
                  // printf("第%d行的Z坐标字为%f\n",i,Z2[i]);
				   }
				}
				Z[i][0]=Z1[i]+Z2[i];
                Z[i][1]=1;            //标记所在的行
	 	       // printf("第%d行的Z坐标字为%f\n",i,Z[i][0]);  
			}
			else if((ngca[i][j]==90)&&((ngca[i][j+1]<48)||(ngca[i][j+1]>57))&&(ngca[i][j+1]!=43)&&(ngca[i][j+1]!=45))
			{
			//	printf("第%d行Z后面的代码无法识别，请检查！\n",i);
				n2++;
			}

            //*存储I字段信息*//
	        if((ngca[i][j]==73)&&(ngca[i][j+1]==43))     //判断坐标字是否为Z且后一位为“+”号
			{				
				for(b=1;(ngca[i][j+1+b]>=48)&&(ngca[i][j+1+b]<=57);b++)   //b为整数位数
				{
				    // printf("b=%d\n",b);
                     if(ngca[i][j+2+b]==46)  //存在小数点，求小数点后面的位数
					 {
						for(e=1;(ngca[i][j+2+b+e]>=48)&&(ngca[i][j+2+b+e]<=57);e++)  //e为小数点后的位数
						{
						//	printf("e=%d\n",e);
						
						}
					}
				     
				} 
                for(d=1;d<b;d++)     //先求整数部分，并累加
				{
			     I1[i]=(ngca[i][j+1+d]-48)*pow(10,b-d-1)+I1[i];
                 //printf("第%d行的I坐标字为%f\n",i,I1[i]);
				}
				if(e>=1)
				{
	               for(f=1;f<e;f++)    //再求小数部分，并累加
				   {
                    I2[i]=(ngca[i][j+1+b+f]-48)*pow(10,-f)+I2[i];
                   // printf("第%d行的I坐标字为%f\n",i,I2[i]);
				   }
				}
				I[i][0]=I1[i]+I2[i];
                I[i][1]=1;            //标记所在的行
	 	        //printf("第%d行的I坐标字为%f\n",i,I[i][0]);  
			}
            else if((ngca[i][j]==73)&&(ngca[i][j+1]==45))     //判断坐标字是否为Z且后一位为“-”号
            {				
				for(b1=1;(ngca[i][j+1+b1]>=48)&&(ngca[i][j+1+b1]<=57);b1++)   //b为整数位数
				{
				     //printf("b1=%d\n",b1);
                     if(ngca[i][j+2+b1]==46)  //存在小数点，求小数点后面的位数
					 {
						for(e1=1;(ngca[i][j+2+b1+e1]>=48)&&(ngca[i][j+2+b1+e1]<=57);e1++)  //e为小数点后的位数
						{
						//	printf("e1=%d\n",e1);
						
						}
					}
				     
				} 
                for(d=1;d<b1;d++)     //先求整数部分，并累加
				{
			     I1[i]=(ngca[i][j+1+d]-48)*pow(10,b1-d-1)+I1[i];
                 //printf("第%d行的I坐标字为%f\n",i,I1[i]);
				}
				if(e1>=1)
				{
	               for(f=1;f<e1;f++)    //再求小数部分，并累加
				   {
                    I2[i]=(ngca[i][j+1+b1+f]-48)*pow(10,-f)+I2[i];
                   // printf("第%d行的I坐标字为%f\n",i,I2[i]);
				   }
				}
				I[i][0]=-(I1[i]+I2[i]);
                I[i][1]=1;            //标记所在的行
	 	       // printf("第%d行的I坐标字为%f\n",i,I[i][0]);  
			}
            else if((ngca[i][j]==73)&&(ngca[i][j+1]>=48)&&(ngca[i][j+1]<=57))     //判断坐标字是否为Z且后一位为整数
            {				
				for(b2=1;(ngca[i][j+b2]>=48)&&(ngca[i][j+b2]<=57);b2++)   //b为整数位数
				{
				     printf("b2=%d\n",b2);
                     if(ngca[i][j+1+b2]==46)  //存在小数点，求小数点后面的位数
					 {
						for(e2=1;(ngca[i][j+1+b2+e2]>=48)&&(ngca[i][j+1+b2+e2]<=57);e2++)  //e为小数点后的位数
						{
						//	printf("e2=%d\n",e2);
						
						}
					}
				     
				} 
                for(d=1;d<b2;d++)     //先求整数部分，并累加
				{
			     Z1[i]=(ngca[i][j+d]-48)*pow(10,b2-d-1)+Z1[i];
                // printf("第%d行的Z坐标字为%f\n",i,Z1[i]);
				}
				if(e2>=1)
				{
	               for(f=1;f<e2;f++)    //再求小数部分，并累加
				   {
                    I2[i]=(ngca[i][j+b2+f]-48)*pow(10,-f)+I2[i];
                  // printf("第%d行的I坐标字为%f\n",i,I2[i]);
				   }
				}
				I[i][0]=I1[i]+I2[i];
                I[i][1]=1;            //标记所在的行
	 	       // printf("第%d行的I坐标字为%f\n",i,I[i][0]);  
			}
			else if((ngca[i][j]==73)&&((ngca[i][j+1]<48)||(ngca[i][j+1]>57))&&(ngca[i][j+1]!=43)&&(ngca[i][j+1]!=45))
			{
			//	printf("第%d行I后面的代码无法识别，请检查！\n",i);
				n2++;
			}

			//*存储J字段信息*//
	        if((ngca[i][j]==74)&&(ngca[i][j+1]==43))     //判断坐标字是否为Z且后一位为“+”号
			{				
				for(b=1;(ngca[i][j+1+b]>=48)&&(ngca[i][j+1+b]<=57);b++)   //b为整数位数
				{
				    // printf("b=%d\n",b);
                     if(ngca[i][j+2+b]==46)  //存在小数点，求小数点后面的位数
					 {
						for(e=1;(ngca[i][j+2+b+e]>=48)&&(ngca[i][j+2+b+e]<=57);e++)  //e为小数点后的位数
						{
						//	printf("e=%d\n",e);
						
						}
					}
				     
				} 
                for(d=1;d<b;d++)     //先求整数部分，并累加
				{
			     J1[i]=(ngca[i][j+1+d]-48)*pow(10,b-d-1)+J1[i];
                 //printf("第%d行的J坐标字为%f\n",i,J1[i]);
				}
				if(e>=1)
				{
	               for(f=1;f<e;f++)    //再求小数部分，并累加
				   {
                    J2[i]=(ngca[i][j+1+b+f]-48)*pow(10,-f)+J2[i];
                   // printf("第%d行的J坐标字为%f\n",i,J2[i]);
				   }
				}
				J[i][0]=J1[i]+J2[i];
                J[i][1]=1;            //标记所在的行
	 	        //printf("第%d行的J坐标字为%f\n",i,J[i][0]);  
			}
            else if((ngca[i][j]==74)&&(ngca[i][j+1]==45))     //判断坐标字是否为Z且后一位为“-”号
            {				
				for(b1=1;(ngca[i][j+1+b1]>=48)&&(ngca[i][j+1+b1]<=57);b1++)   //b为整数位数
				{
				     //printf("b1=%d\n",b1);
                     if(ngca[i][j+2+b1]==46)  //存在小数点，求小数点后面的位数
					 {
						for(e1=1;(ngca[i][j+2+b1+e1]>=48)&&(ngca[i][j+2+b1+e1]<=57);e1++)  //e为小数点后的位数
						{
						//	printf("e1=%d\n",e1);
						
						}
					}
				     
				} 
                for(d=1;d<b1;d++)     //先求整数部分，并累加
				{
			     J1[i]=(ngca[i][j+1+d]-48)*pow(10,b1-d-1)+J1[i];
                 //printf("第%d行的J坐标字为%f\n",i,J1[i]);
				}
				if(e1>=1)
				{
	               for(f=1;f<e1;f++)    //再求小数部分，并累加
				   {
                    J2[i]=(ngca[i][j+1+b1+f]-48)*pow(10,-f)+J2[i];
                   // printf("第%d行的J坐标字为%f\n",i,J2[i]);
				   }
				}
				J[i][0]=-(J1[i]+J2[i]);
                J[i][1]=1;            //标记所在的行
	 	       // printf("第%d行的J坐标字为%f\n",i,J[i][0]);  
			}
            else if((ngca[i][j]==74)&&(ngca[i][j+1]>=48)&&(ngca[i][j+1]<=57))     //判断坐标字是否为Z且后一位为整数
            {				
				for(b2=1;(ngca[i][j+b2]>=48)&&(ngca[i][j+b2]<=57);b2++)   //b为整数位数
				{
				     printf("b2=%d\n",b2);
                     if(ngca[i][j+1+b2]==46)  //存在小数点，求小数点后面的位数
					 {
						for(e2=1;(ngca[i][j+1+b2+e2]>=48)&&(ngca[i][j+1+b2+e2]<=57);e2++)  //e为小数点后的位数
						{
						//	printf("e2=%d\n",e2);
						
						}
					}
				     
				} 
                for(d=1;d<b2;d++)     //先求整数部分，并累加
				{
			     J1[i]=(ngca[i][j+d]-48)*pow(10,b2-d-1)+J1[i];
                // printf("第%d行的J坐标字为%f\n",i,J1[i]);
				}
				if(e2>=1)
				{
	               for(f=1;f<e2;f++)    //再求小数部分，并累加
				   {
                    J2[i]=(ngca[i][j+b2+f]-48)*pow(10,-f)+J2[i];
                  // printf("第%d行的J坐标字为%f\n",i,J2[i]);
				   }
				}
				J[i][0]=J1[i]+J2[i];
                J[i][1]=1;            //标记所在的行
	 	       // printf("第%d行的J坐标字为%f\n",i,J[i][0]);  
			}
			else if((ngca[i][j]==74)&&((ngca[i][j+1]<48)||(ngca[i][j+1]>57))&&(ngca[i][j+1]!=43)&&(ngca[i][j+1]!=45))
			{
			//	printf("第%d行J后面的代码无法识别，请检查！\n",i);
				n2++;
			}
            //*存储R字段信息*//
	        if((ngca[i][j]==82)&&(ngca[i][j+1]==43))     //判断坐标字是否为R且后一位为“+”号
			{				
				for(b=1;(ngca[i][j+1+b]>=48)&&(ngca[i][j+1+b]<=57);b++)   //b为整数位数
				{
				    // printf("b=%d\n",b);
                     if(ngca[i][j+2+b]==46)  //存在小数点，求小数点后面的位数
					 {
						for(e=1;(ngca[i][j+2+b+e]>=48)&&(ngca[i][j+2+b+e]<=57);e++)  //e为小数点后的位数
						{
						//	printf("e=%d\n",e);
						
						}
					}
				     
				} 
                for(d=1;d<b;d++)     //先求整数部分，并累加
				{
			     R1[i]=(ngca[i][j+1+d]-48)*pow(10,b-d-1)+R1[i];
                // printf("第%d行的R坐标字为%f\n",i,R1[i]);
				}
				if(e>=1)
				{
	               for(f=1;f<e;f++)    //再求小数部分，并累加
				   {
                    R2[i]=(ngca[i][j+1+b+f]-48)*pow(10,-f)+R2[i];
                  //  printf("第%d行的R坐标字为%f\n",i,R2[i]);
				   }
				}
				R[i][0]=R1[i]+R2[i];
                R[i][1]=1;            //标记所在的行
	 	       // printf("第%d行的R坐标字为%f\n",i,R[i][0]);  
			}
            else if((ngca[i][j]==82)&&(ngca[i][j+1]==45))     //判断坐标字是否为R且后一位为“-”号
            {				
				for(b1=1;(ngca[i][j+1+b1]>=48)&&(ngca[i][j+1+b1]<=57);b1++)   //b为整数位数
				{
				   //  printf("b1=%d\n",b1);
                     if(ngca[i][j+2+b1]==46)  //存在小数点，求小数点后面的位数
					 {
						for(e1=1;(ngca[i][j+2+b1+e1]>=48)&&(ngca[i][j+2+b1+e1]<=57);e1++)  //e为小数点后的位数
						{
					//		printf("e1=%d\n",e1);
						
						}
					}
				     
				} 
                for(d=1;d<b1;d++)     //先求整数部分，并累加
				{
			     R1[i]=(ngca[i][j+1+d]-48)*pow(10,b1-d-1)+R1[i];
                // printf("第%d行的R坐标字为%f\n",i,R1[i]);
				}
				if(e1>=1)
				{
	               for(f=1;f<e1;f++)    //再求小数部分，并累加
				   {
                    R2[i]=(ngca[i][j+1+b1+f]-48)*pow(10,-f)+R2[i];
                  //  printf("第%d行的R坐标字为%f\n",i,R2[i]);
				   }
				}
				R[i][0]=-(R1[i]+R2[i]);
                R[i][1]=1;            //标记所在的行
	 	       // printf("第%d行的R坐标字为%f\n",i,R[i][0]);  
			}
            else if((ngca[i][j]==82)&&(ngca[i][j+1]>=48)&&(ngca[i][j+1]<=57))     //判断坐标字是否为R且后一位为整数
            {				
				for(b2=1;(ngca[i][j+b2]>=48)&&(ngca[i][j+b2]<=57);b2++)   //b为整数位数
				{
				     printf("b2=%d\n",b2);
                     if(ngca[i][j+1+b2]==46)  //存在小数点，求小数点后面的位数
					 {
						for(e2=1;(ngca[i][j+1+b2+e2]>=48)&&(ngca[i][j+1+b2+e2]<=57);e2++)  //e为小数点后的位数
						{
						//	printf("e2=%d\n",e2);
						
						}
					}
				     
				} 
                for(d=1;d<b2;d++)     //先求整数部分，并累加
				{
			     R1[i]=(ngca[i][j+d]-48)*pow(10,b2-d-1)+R1[i];
                // printf("第%d行的R坐标字为%f\n",i,R1[i]);
				}
				if(e2>=1)
				{
	               for(f=1;f<e2;f++)    //再求小数部分，并累加
				   {
                    R2[i]=(ngca[i][j+b2+f]-48)*pow(10,-f)+R2[i];
                    //printf("第%d行的R坐标字为%f\n",i,R2[i]);
				   }
				}
				R[i][0]=R1[i]+R2[i];
                R[i][1]=1;            //标记所在的行
	 	       // printf("第%d行的R坐标字为%f\n",i,R[i][0]);  
			}
			else if((ngca[i][j]==82)&&((ngca[i][j+1]<48)||(ngca[i][j+1]>57))&&(ngca[i][j+1]!=43)&&(ngca[i][j+1]!=45))
			{
			//	printf("第%d行R后面的代码无法识别，请检查！\n",i);
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
          // printf("共有%d行X后面的代码无法识别，请检查！\n",n);
		}
        if(n1!=0)
		{
          // printf("共有%d行Y后面的代码无法识别，请检查！\n",n1);
		}
        if(n2!=0)
		{
         //  printf("共有%d行Z后面的代码无法识别，请检查！\n",n2);
		}
		if(n3!=0)
		{
           //printf("共有%d行R后面的代码无法识别，请检查！\n",n3);
		}
		//exit(0);
	}
    //*3.5存储进给功能字F字段信息*//
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
				for(b=1;(ngca[i][j+b]>=48)&&(ngca[i][j+b]<=57);b++)   //b为整数位数
				{
                    //printf("b=%d\n",b);
                    if(ngca[i][j+1+b]==46)  //存在小数点，求小数点后面的位数
					 {
						for(e=1;(ngca[i][j+1+b+e]>=48)&&(ngca[i][j+1+b+e2]<=57);e++)  //e为小数点后的位数
						{
						//	printf("e=%d\n",e);
						
						}
					}
				}
			    for(d=1;d<b;d++)     //求整数部分，并累加
				{
			     F1[i]=(ngca[i][j+d]-48)*pow(10,b-d-1)+F1[i];
                // printf("第%d行的进给功能字F1为%f\n",i,F1[i]);
				 
				}
				if(e>=1)
				{
	               for(f=1;f<e;f++)    //求小数部分，并累加
				   {
                    F2[i]=(ngca[i][j+b+f]-48)*pow(10,-f)+F2[i];
                  //  printf("第%d行的进给功能字F2为%f\n",i,F2[i]);
				   }
				}
				F[i]=F1[i]+F2[i];
	 	        s31.Format("第%d行的进给功能字F为%f\r\n",i,F[i]);
				m_edit2+=s31;

			}
			else if((ngca[i][j]==70)&&((ngca[i][j+1]<48)||(ngca[i][j+1]>57)))
			{
				s32.Format("第%d行F后面的代码无法识别，请检查！\r\n",i);
				m_edit2+=s32;
				n++;
			}
		}
		b=0;
		e=0;
	}
    if(n!=0)
	{
       s33.Format("共有%d行F后面的代码无法识别，请检查！\r\n",n);
       m_edit2+=s33;
	   //exit(0);
	}
	//*3.6存储主轴转速功能字S字段信息*//
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
				for(b=1;(ngca[i][j+b]>=48)&&(ngca[i][j+b]<=57);b++)   //b为整数位数
				{
                    //printf("b=%d\n",b);
                    if(ngca[i][j+1+b]==46)  //存在小数点，求小数点后面的位数
					 {
						for(e=1;(ngca[i][j+1+b+e]>=48)&&(ngca[i][j+1+b+e2]<=57);e++)  //e为小数点后的位数
						{
						//	printf("e=%d\n",e);
						
						}
					}
				}
			    for(d=1;d<b;d++)     //求整数部分，并累加
				{
			     S1[i]=(ngca[i][j+d]-48)*pow(10,b-d-1)+S1[i];
                 //printf("第%d行的主轴转速功能字S1为%f\n",i,S1[i]);
				}
				if(e>=1)
				{
	               for(f=1;f<e;f++)    //求小数部分，并累加
				   {
                    S2[i]=(ngca[i][j+b+f]-48)*pow(10,-f)+S2[i];
                  //  printf("第%d行的主轴转速功能字S2为%f\n",i,S2[i]);
				   }
				}
				S[i]=S1[i]+S2[i];
	 	        s34.Format("第%d行的主轴转速功能字S为%f\r\n",i,S[i]);
				m_edit2+=s34;

			}
			else if((ngca[i][j]==70)&&((ngca[i][j+1]<48)||(ngca[i][j+1]>57)))
			{
				s35.Format("第%d行S后面的代码无法识别，请检查！\r\n",i);
				m_edit2+=s35;
				n++;
			}
		}
		b=0;
		e=0;
	}
    if(n!=0)
	{
       s36.Format("共有%d行S后面的代码无法识别，请检查！\r\n",n);
	   m_edit2+=s36;
	   //exit(0);
	}
    //*3.7存储刀具功能字T字段信息*//
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
				for(b=1;(ngca[i][j+b]>=48)&&(ngca[i][j+b]<=57);b++)   //b为整数位数
				{
                   // printf("b=%d\n",b);
                    if(ngca[i][j+1+b]==46)  //存在小数点，求小数点后面的位数
					 {
						for(e=1;(ngca[i][j+1+b+e]>=48)&&(ngca[i][j+1+b+e2]<=57);e++)  //e为小数点后的位数
						{
						//	printf("e=%d\n",e);
						
						}
					}
				}
			    for(d=1;d<b;d++)     //求整数部分，并累加
				{
			     T1[i]=(ngca[i][j+d]-48)*pow(10,b-d-1)+T1[i];
                // printf("第%d行的刀具功能字T1为%f\n",i,T1[i]);
				}
				if(e>=1)
				{
	               for(f=1;f<e;f++)    //求小数部分，并累加
				   {
                    T2[i]=(ngca[i][j+b+f]-48)*pow(10,-f)+T2[i];
                  //  printf("第%d行的刀具功能字T2为%f\n",i,T2[i]);
				   }
				}
				T[i]=T1[i]+T2[i];
	 	        s37.Format("第%d行的刀具功能字T为%f\r\n",i,T[i]);
				m_edit2+=s37;

			}
			else if((ngca[i][j]==70)&&((ngca[i][j+1]<48)||(ngca[i][j+1]>57)))
			{
				s38.Format("第%d行T后面的代码无法识别，请检查！\r\n",i);
			    m_edit2+=s38;
				n++;
			}
		}
		b=0;
		e=0;
	}
    if(n!=0)
	{ 
       s39.Format("共有%d行T后面的代码无法识别，请检查！\r\n",n);
       m_edit2+=s39;
	  // exit(0);
	}
    if(f>1)
	{ 
      s40.Format("刀具号应为整数，请检查！\r\n");
      m_edit2+=s40;
	  // exit(0);
	}
    //*3.7存储辅助功能字M字段信息*//
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
				for(b=1;(ngca[i][j+b]>=48)&&(ngca[i][j+b]<=57);b++)   //b为整数位数
				{
                    //printf("b=%d\n",b);
                    if(ngca[i][j+1+b]==46)  //存在小数点，求小数点后面的位数
					 {
						for(e=1;(ngca[i][j+1+b+e]>=48)&&(ngca[i][j+1+b+e2]<=57);e++)  //e为小数点后的位数
						{
						//	printf("e=%d\n",e);
						
						}
					}
				}
			    for(d=1;d<b;d++)     //求整数部分，并累加
				{
			     M1[i]=(ngca[i][j+d]-48)*pow(10,b-d-1)+M1[i];
                // printf("第%d行的辅助功能字M1为%f\n",i,M1[i]);
				}
				if(e>=1)
				{
	               for(f=1;f<e;f++)    //求小数部分，并累加
				   {
                    M2[i]=(ngca[i][j+b+f]-48)*pow(10,-f)+M2[i];
                  //  printf("第%d行的辅助功能字M2为%f\n",i,M2[i]);
				   }
				}
				M[i][0]=M1[i]+M2[i];
				M[i][1]=1;
	 	        s41.Format("第%d行的辅助功能字M为%f\r\n",i,M[i][0]);
				m_edit2+=s41;
				if(M[i][0]<0||M[i][0]>99)   //判断辅助功能字是否为两位数
				{
					s42.Format("第%d行辅助功能字不在可识别范围内，请保证0<=M<=99!\r\n",i);
					m_edit2+=s42;
				}

			}
			else if((ngca[i][j]==70)&&((ngca[i][j+1]<48)||(ngca[i][j+1]>57)))
			{
				s43.Format("第%d行M后面的代码无法识别，请检查！\r\n",i);
				m_edit2+=s43;
				n++;
			}
		}
		b=0;
		e=0;
	}
    if(n!=0)
	{ 
       s44.Format("共有%d行M后面的代码无法识别，请检查！\r\n",n);
	   m_edit2+=s44;
	   //exit(0);
	}
    if(f>1)
	{ 
       s45.Format("辅助功能字应为整数，请检查！\r\n");
	   m_edit2+=s45;
	   //exit(0);
	}
    UpdateData(FALSE);	


	
}

void CMy0422Dlg::OnDone1()     //执行程序
{
	// TODO: Add your control notification handler code here
	for(i=0;i<=2;i++)
	{
        d5480_set_pulse_outmode(i,4);        //设置脉冲模式，0，1，2号轴（分别代表X,Y,Z方向）第四种脉冲输出类型
	}
    d5480_write_SEVON_PIN(0,0);        //输出SEVON信号，用于控制伺服电动机驱动器
	for(i=0;i<c;i++)
	{
		for(j=0;j<2;j++)        //G[i][2]的功能是确保准备功能字确实出现在该行，因为默认的数组G[][]的初值都附为0，用于区别功能字里面的0
		{
			if((G[i][j]==90||G[i][j+1]==90)&&j==0)   //运动模式为绝对运动距离
			{
				AC=1;      //控制卡中1为绝对运动
				if(G[i+1][0]!=91&&G[i+1][1]!=91)   //解决模态问题
				{
					if(G[i+1][2]==0)    //如果下一行没有G代码
					{
                        G[i+1][0]=90;
					    G[i+1][1]=-1;
					    G[i+1][2]=1;
					}
					if(G[i+1][2]==1)    //如果下一行有G代码
					{
					    G[i+1][1]=90;
					}
				}
			}
			if((G[i][j]==91||G[i][j+1]==91)&&j==0)   //运动模式为相对运动距离
			{
				AC=0;      //控制卡中0为相对运动
				if(G[i+1][0]!=90&&G[i+1][1]!=90)   //解决模态问题
				{
					if(G[i+1][2]==0)    //如果下一行没有G代码
					{
                        G[i+1][0]=91;
					    G[i+1][1]=-1;
					    G[i+1][2]=1;
					}
					if(G[i+1][2]==1)    //如果下一行有G代码
					{
					    G[i+1][1]=91;
					}
				}
			}
			if(G[i][j]==0&&G[i][2]==1)            //执行快速进给运动,点位控制函数，怎么开始？怎么结束？运动距离与脉冲数的换算
			{
				if(G[i+1][0]!=1&&G[i+1][1]!=1||G[i+1][0]!=2&&G[i+1][1]!=2&&G[i+1][0]!=3&&G[i+1][1]!=3) //解决模态问题，当下一行没有同组G代码时，下一行自动赋值为相同代码
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
				if(X[i][1]==1)            //G00后面有X坐标
				{
                    XL=-X[i][0]*2500;      //换算成脉冲
					d5480_pmove(0,XL,AC);      //设置轴号，运动距离（需换算成脉冲数），运动模式（相对0，绝对1）
				}
				if(Y[i][1]==1)            //G00后面有Y坐标
				{
                    YL=Y[i][0]*2500;      //换算成脉冲
					d5480_pmove(0,YL,AC);      //设置轴号，运动距离（需换算成脉冲数），运动模式（相对0，绝对1）
				}
				if(Z[i][1]==1)            //G00后面有Z坐标
				{
					ZL=-Z[i][0]*2500;      //换算成脉冲
					d5480_pmove(0,ZL,AC);      //设置轴号，运动距离（需换算成脉冲数），运动模式（相对0，绝对1）
				}
			}
            if(G[i][j]==1&&G[i][2]==1)            //执行直线运动,两轴直线插补函数，怎么开始？怎么结束？运动距离与脉冲数的换算
			{
				if(G[i+1][0]!=0&&G[i+1][1]!=0||G[i+1][0]!=2&&G[i+1][1]!=2&&G[i+1][0]!=3&&G[i+1][1]!=3) //解决模态问题，当下一行没有同组G代码时，下一行自动赋值为相同代码
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
				XL=-X[i][0]*2500;      //换算成脉冲
                YL=Y[i][0]*2500;      //换算成脉冲
				d5480_line2(0,XL,1,YL,AC);      //设置轴号，运动距离（需换算成脉冲数），轴号，脉冲数，运动模式（相对0，绝对1）
			}
			if(G[i][j]==2&&G[i][2]==1)            //执行顺时针方向圆弧插补
			{
				if(G[i+1][0]!=1&&G[i+1][1]!=1||G[i+1][0]!=0&&G[i+1][1]!=0&&G[i+1][0]!=3&&G[i+1][1]!=3) //解决模态问题，当下一行没有同组G代码时，下一行自动赋值为相同代码
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
			    
				if(G[i][0]==90||G[i][1]==90)//绝对坐标
				{
					XL=-X[i][0]*2500;      //终点坐标，换算成脉冲
                    YL=Y[i][0]*2500;      //换算成脉冲
					IL=-I[i][0]*2500;      //圆心坐标，换算成脉冲
					JL=J[i][0]*2500;
					
					WORD xy[2]={0,1};
					long xy_pos[2]={XL,YL};
					long ij_pos[2]={IL,JL};
					d5480_arc_move(xy,xy_pos,ij_pos,0);   //插补轴，终点，圆心，顺时针/逆时针
				}
			}
			if(G[i][j]==3&&G[i][2]==1)            //执行逆时针方向圆弧插补
			{
				if(G[i+1][0]!=1&&G[i+1][1]!=1||G[i+1][0]!=2&&G[i+1][1]!=2&&G[i+1][0]!=0&&G[i+1][1]!=0) //解决模态问题，当下一行没有同组G代码时，下一行自动赋值为相同代码
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
				if(G[i][0]==90||G[i][1]==90)//绝对坐标
				{
					XL=-X[i][0]*2500;      //终点坐标，换算成脉冲
                    YL=Y[i][0]*2500;      //换算成脉冲
					IL=-I[i][0]*2500;      //圆心坐标，换算成脉冲
					JL=J[i][0]*2500;
					
					WORD xy[2]={0,1};
					long xy_pos[2]={XL,YL};
					long ij_pos[2]={IL,JL};
					d5480_arc_move(xy,xy_pos,ij_pos,1);   //插补轴，终点，圆心，顺时针/逆时针
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
void CMy0422Dlg::OnButtonEstop()    //紧急停止
{
	// TODO: Add your control notification handler code here
	d5480_emg_stop();
}
void CMy0422Dlg::OnButtonCancel()  //退出
{
	// TODO: Add your control notification handler code here
	d5480_board_close();
//	KillTimer( IDC_TIMER );
	CDialog::OnCancel();
}
void CMy0422Dlg::OnButtonReset()   //位置清零
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

//void CMy0422Dlg::OnTimer(UINT nIDEvent) //实时反馈运动坐标
//{
	// TODO: Add your message handler code here and/or call default
	//status=d5480_check_done(m_nAxis);
	//GetDlgItem( IDC_EDIT1 )->SetWindowText( status?"静止":"运动中");

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

	//GetDlgItem( IDC_EDIT_XPOS )->SetWindowText( Xpos );     //SetWindowText函数改变指定窗口的标题栏的文本内容（如果窗口有标题栏）。如果指定窗口是一个控件，则改变控件的文本内容。然而，SetWindowText函数不改变其他应用程序中的控件的文本内容。[1] 
	//GetDlgItem( IDC_EDIT_YPOS )->SetWindowText( Ypos );
	//GetDlgItem( IDC_EDIT_ZPOS )->SetWindowText( Zpos );
	//GetDlgItem( IDC_EDIT_UPOS )->SetWindowText( Upos );

	//TRACE("X轴速度：%d",d5480_read_vector_speed(0));
//	CDialog::OnTimer(nIDEvent);
//}