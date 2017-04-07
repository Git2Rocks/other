// transferfileDlg.cpp : implementation file
//
#include "stdafx.h"
#include "transferfile.h"
#include "transferfileDlg.h"
#include "DstprmDlg.h"
#include "SetFilterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

/////////////////////////////////////////////////////////////////////
//ȫ�ֱ���
/////////////////////////////////////////////////////////////////////

int FtpTransMode=1;						//ftp���䷽ʽ,0Ϊ.bat��ʽ��1Ϊ����CFtpConnection����ʽ��Ŀǰֻ�÷�ʽ1											
CString XcopyFilePath="";				//xcopy�ļ�������·�����ļ���
CTransferfileDlg *pTransferfileDlg;
int threadcontroller =0;				//���̿��Ʊ�ʶ������1Ϊ���ڴ��䣬0Ϊδ����
int transferType=0;						//�������࣬0Ϊ����,1Ϊ����
bool IsExit=false;						//�˳���ʶ����Ϊtrue���˳�
bool IsTransDB=false;					//�Ƿ����ڴ���Database.Out�ļ�
int curDst=-1;							//��ǰ��ѡĿ��������m_config�ı��
CString csMessage;						//һ����־��Ϣ����
CString strDriverName[6];
CString strVerName[3];
CTransferConfig m_config;				//����������Ϣ����
CString CurExeFilePath="";				//��ִ���ļ�������·�����ļ���
CString strWindowsPath="";				//ϵͳWindowsĿ¼
CString FtpTxtName="autoftp.txt";		//autoftp.txt�ļ�
CString FtpBatName="autoftp.bat";		//autoftp.bat�ļ�
int nErrCount=0;						//ͳ�ƴ�����еĹ��ϴ���
int nTransferCount=0;					//�����ļ�����
CString strErrLog="";					//������־
					
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
	virtual void OnOK();
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
// CTransferfileDlg dialog

CTransferfileDlg::CTransferfileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTransferfileDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTransferfileDlg)
	m_editLog = _T("");
	m_radioVer = 2;
	m_radioDriver = 2;
	m_check1 = TRUE;
	m_check2 = FALSE;
	m_check3 = TRUE;
	m_check4 = TRUE;
	m_check5 = TRUE;
	m_check6 = TRUE;
	m_check7 = TRUE;
	m_check8 = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON4);
	pTransferfileDlg=this;
}

void CTransferfileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTransferfileDlg)
	DDX_Control(pDX, IDSETFILTER, m_buttonSet);
	DDX_Control(pDX, IDSTARTGET, m_buttonGet);
	DDX_Control(pDX, IDCANCEL, m_buttonCancel);
	DDX_Control(pDX, IDSAVECONFIG, m_buttonSave);
	DDX_Control(pDX, IDADDDST, m_buttonAddDst);
	DDX_Control(pDX, IDSTARTTRANSFER, m_starttransfer);
	DDX_Control(pDX, IDC_EDITLOG, m_editLogCtrl);
	DDX_Control(pDX, IDC_LISTDST, m_listDst);
	DDX_Text(pDX, IDC_EDITLOG, m_editLog);
	DDX_Radio(pDX, IDC_RADIOVER1, m_radioVer);
	DDX_Radio(pDX, IDC_RADIODRIVERA, m_radioDriver);
	DDX_Check(pDX, IDC_CHECK1, m_check1);
	DDX_Check(pDX, IDC_CHECK2, m_check2);
	DDX_Check(pDX, IDC_CHECK3, m_check3);
	DDX_Check(pDX, IDC_CHECK4, m_check4);
	DDX_Check(pDX, IDC_CHECK5, m_check5);
	DDX_Check(pDX, IDC_CHECK6, m_check6);
	DDX_Check(pDX, IDC_CHECK7, m_check7);
	DDX_Check(pDX, IDC_CHECK8, m_check8);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTransferfileDlg, CDialog)
	//{{AFX_MSG_MAP(CTransferfileDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_ADDMENU, OnAddDst)
	ON_COMMAND(ID_DELMENU, OnDelDst)
	ON_COMMAND(ID_MODIFYMENU, OnModifyDst)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDSTARTTRANSFER, OnStarttransfer)
	ON_BN_CLICKED(IDADDDST, OnAdddst)
	ON_BN_CLICKED(IDSAVECONFIG, OnSaveconfig)
	ON_BN_CLICKED(IDSTARTGET, OnStartget)
	ON_COMMAND(ID_GETMENU, OnGetmenu)
	ON_BN_CLICKED(IDSETFILTER, OnSetFilter)
	ON_BN_CLICKED(IDC_RADIODRIVERF, OnRadiodriverf)
	ON_BN_CLICKED(IDC_RADIODRIVERE, OnRadiodrivere)
	ON_BN_CLICKED(IDC_RADIODRIVERD, OnRadiodriverd)
	ON_NOTIFY(NM_CLICK, IDC_LISTDST, OnClickListdst)
	ON_BN_CLICKED(IDSETFILTER1, OnSetfilter1)
	ON_BN_CLICKED(IDSETFILTER2, OnSetfilter2)
	ON_BN_CLICKED(IDSETFILTER3, OnSetfilter3)
	ON_BN_CLICKED(IDSETFILTER4, OnSetfilter4)
	ON_BN_CLICKED(IDSETFILTER5, OnSetfilter5)
	ON_BN_CLICKED(IDSETFILTER6, OnSetfilter6)
	ON_BN_CLICKED(IDSETFILTER7, OnSetfilter7)
	ON_BN_CLICKED(IDC_RADIODRIVERC, OnRadiodriverc)
	ON_BN_CLICKED(IDC_RADIOVER2, OnRadiover2)
	ON_BN_CLICKED(IDC_RADIOVER3, OnRadiover3)
	ON_COMMAND(ID_ENABLEMENU, OnEnablemenu)
	ON_BN_CLICKED(IDSETFILTER8, OnSetfilter8)
	ON_MESSAGE(WM_THREADPROC,UpdateLog)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransferfileDlg message handlers

BOOL CTransferfileDlg::OnInitDialog()
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
	//��ʼ��ȫ�ֱ���
	int j,curPos;
	CString strtmp="";
	TCHAR exeFullPath[MAX_PATH];	// MAX_PATH��API�ж����˰ɣ�������128 
	//��ȡ��ǰ����·�����ļ�����
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);
	strtmp=exeFullPath;		
	CurExeFilePath="";
	j=1;
	while(j>=0)
	{
		j=strtmp.Find("\\");
		CurExeFilePath=CurExeFilePath+strtmp.Left(j+1);
		strtmp=strtmp.Right(strtmp.GetLength()-j-1);
		curPos=j;
	};
	//���ϵͳĿ¼
	GetWindowsDirectory(exeFullPath,MAX_PATH);
	strWindowsPath=exeFullPath;
					
	
	strDriverName[0]="A";
	strDriverName[1]="C";
	strDriverName[2]="D";
	strDriverName[3]="E";
	strDriverName[4]="F";
	strDriverName[5]="J";
	strVerName[0]="v2.0a";
	strVerName[1]="v3.0a";
	strVerName[2]="v4.0a";
	//��ʼ����־��
	UpdateData(true);
	//��ʼ��Ŀ�������б�
	m_listDst.InsertColumn(0, "IP��ַ");		
	m_listDst.InsertColumn(1, "����");
	m_listDst.InsertColumn(2, "����");		
	m_listDst.SetColumnWidth(0, 150);
	m_listDst.SetColumnWidth(1, 60);
	m_listDst.SetColumnWidth(2, 60);
	UpdateData(false);
	
	//�������ļ���ȡ������Ϣ����ʾ�ڶԻ�����
	m_config.GetConfigFromFile();
	m_config.SetConfigDir();  
	UpdateIPList();
	UpdatePubConfig();
	//��ȡFtp���䷽ʽ��0Ϊ.bat��ʽ��1Ϊ�෽ʽ
	FtpTransMode=m_config.m_ftpTransMode;	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTransferfileDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTransferfileDlg::OnPaint() 
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
HCURSOR CTransferfileDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/////////////////////////////////////////////////////////////////////
//��Ӧ�Ҽ��¼�
/////////////////////////////////////////////////////////////////////
void CTransferfileDlg::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	//������ڴ��䣬������Ҽ��˵�
	if(threadcontroller==1)
	{
		return;
	}
	//�õ�ѡ�еĿͻ���
	int nIndex = this->m_listDst.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED); 
    if(nIndex == -1)
        return;

	CMenu menu;
	menu.LoadMenu(MAKEINTRESOURCE(IDR_DSTIPMENU));
//	menu.GetSubMenu(0)->TrackPopupMenu(0, point.x, point.y, this, NULL);
	
	int i,iState;
	int nDst=0;										//ѡ�е�Ŀ���������
	CString	str;
	int nItemSelected=m_listDst.GetSelectedCount();	//��ѡ������
	int nItemCount=m_listDst.GetItemCount();		//��������
	if(nItemSelected<1) return;
	//�����ѡ��������
	for(i=0;i<nItemCount;i++)
	{
		iState=m_listDst.GetItemState(i,LVIS_SELECTED);
		if(iState!=0)
		{
			nDst=m_config.m_dstCount-1-i;
			break;
		}
	}
	if(m_config.m_dstComputer[nDst].Status==0)
		str= "����";
	else
		str= "����";
	menu.ModifyMenu(ID_ENABLEMENU, MF_BYCOMMAND|MF_STRING, ID_ENABLEMENU, str);
	menu.GetSubMenu(0)->TrackPopupMenu(0, point.x, point.y, this, NULL);

}
/////////////////////////////////////////////////////////////////////
//��Ӧ�����˵����Ӽ������
/////////////////////////////////////////////////////////////////////
void CTransferfileDlg::OnAddDst() 
{
	// TODO: Add your command handler code here
	CDstprmDlg dlg;								//�����Ի������
	//m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();				//�����Ի���
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	
}
/////////////////////////////////////////////////////////////////////
//ɾ��Ŀ������
/////////////////////////////////////////////////////////////////////
void CTransferfileDlg::OnDelDst() 
{
	// TODO: Add your command handler code here
	//ȷ���Ƿ���
	if(MessageBox("�Ƿ�ȷ��ɾ��?","��ȷ��...",MB_YESNO|MB_ICONQUESTION)!=IDYES)
	{
		return;
	}
	int i,iState;
	int nDst=0;										//ѡ�е�Ŀ���������
	int nItemSelected=m_listDst.GetSelectedCount();	//��ѡ������
	
	int nItemCount=m_listDst.GetItemCount();		//��������
	if(nItemSelected<1) return;
	for(i=0;i<nItemCount;i++)
	{
		iState=m_listDst.GetItemState(i,LVIS_SELECTED);
		if(iState!=0)
		{
			nDst=m_config.m_dstCount-1-i;
			//ɾ����ѡ�����
			m_config.DelDst(nDst);
			UpdateIPList();	
			break;
		}
	}
	return;
}
void CTransferfileDlg::OnModifyDst() 
{
	// TODO: Add your command handler code here
	CDstprmDlg dlg(this);							//�����Ի������
	int i,iState;
	int nDst=0;										//ѡ�е�Ŀ���������
	int nItemSelected=m_listDst.GetSelectedCount();	//��ѡ������
	int nItemCount=m_listDst.GetItemCount();		//��������
	if(nItemSelected<1) return;
	//�����ѡ��������
	for(i=0;i<nItemCount;i++)
	{
		iState=m_listDst.GetItemState(i,LVIS_SELECTED);
		if(iState!=0)
		{
			nDst=m_config.m_dstCount-1-i;
			break;
		}
	}
	//���Ի����������
	dlg.m_ip=m_config.m_dstComputer[nDst].DstIP;
	dlg.m_passwd=m_config.m_dstComputer[nDst].Passwd;
	dlg.m_pwdConf=m_config.m_dstComputer[nDst].Passwd;
	dlg.m_username=m_config.m_dstComputer[nDst].Username;
	dlg.m_radioType=m_config.m_dstComputer[nDst].DstType;
	dlg.m_status=m_config.m_dstComputer[nDst].Status;
	for(i=0;i<6;i++)
	{
		if(strDriverName[i]==m_config.m_dstComputer[nDst].DstDriver)
		{
			dlg.m_radiodriver=i;
			break;
		}
	}
	int nResponse = dlg.DoModal();				//�����Ի���
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
		//���޸ĺ����Ϣд��m_config
		m_config.m_dstComputer[nDst].DstIP=dlg.m_ip;
		if(dlg.m_radiodriver<0) dlg.m_radiodriver=0;
		//�ӶԻ����ȡ��Դ�̺Ͱ汾������m_config	
		m_config.m_dstComputer[nDst].DstDriver=strDriverName[dlg.m_radiodriver];
		m_config.m_dstComputer[nDst].DstType=dlg.m_radioType;
		m_config.m_dstComputer[nDst].Status=dlg.m_status;
		m_config.m_dstComputer[nDst].Username=dlg.m_username;
		m_config.m_dstComputer[nDst].Passwd=dlg.m_passwd;
		m_config.m_dstComputer[nDst].PortNum=21;
		//ˢ��m_config��·�������Ϣ
		m_config.SetConfigDir();
		//ͨ��m_config��Ŀ��������Ϣ����IP�б����Ϣ
		UpdateIPList();
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

}

void CTransferfileDlg::OnButton1() 
{
	//AfxMessageBox(CurExeFilePath);
	CString strDir="e:\\a\\b\\c\\d\\e\\f\\";
	if(CreateDirectory(strDir,NULL)==0)
	{
		AfxMessageBox("����Ŀ¼ �����ˣ�" );
	}
}
/////////////////////////////////////////////////////////////////////
//������־�������
/////////////////////////////////////////////////////////////////////
long CTransferfileDlg::UpdateLog(WPARAM wParam, LPCTSTR lParam) 
{
	// TODO: Add your command handler code here
	UpdateData(true);
	Sleep(10);
	if(m_editLog.GetLength()>10000)
	{
		//m_editLog=m_editLog.Left(500);
		m_editLog="";
	}
	CString strtmp="\r\n";
	m_editLog=m_editLog +strtmp+lParam;
	UpdateData(false);
	m_editLogCtrl.SetSel(m_editLog.GetLength()-1,m_editLog.GetLength());
	return 0;
}

/////////////////////////////////////////////////////////////////////
//������־������ݣ��򵥷�ʽ
/////////////////////////////////////////////////////////////////////
long CTransferfileDlg::UpdateLogLine(CString MyStrLine) 
{
	// TODO: Add your command handler code here
	UpdateData(true);
	Sleep(10);
	if(m_editLog.GetLength()>10000)
	{
		//m_editLog=m_editLog.Left(500);
		m_editLog="";
	}
	CString strtmp="\r\n";
	m_editLog=m_editLog +strtmp+MyStrLine;
	UpdateData(false);
	m_editLogCtrl.SetSel(m_editLog.GetLength()-1,m_editLog.GetLength());
	return 0;
}

/////////////////////////////////////////////////////////////////////
//����IP�б������
/////////////////////////////////////////////////////////////////////
bool CTransferfileDlg::UpdateIPList() 
{
	// TODO: Add your command handler code here
	UpdateData(true);
	int i=0;
	int nIndex=0;
	int tmp;
	CString strDstType="Unix";
	CString strDstStatus="����";
	//���ԭ������
	m_listDst.DeleteAllItems();
	//ѭ����ʾÿһ��Ŀ������
	for(i=0;i<m_config.m_dstCount;i++)
	{	
		tmp=m_config.m_dstComputer[i].DstType;
		if(m_config.m_dstComputer[i].DstType==0) 
			strDstType="PC";
		else
			strDstType="Unix";
		if(m_config.m_dstComputer[i].Status==0) 
			strDstStatus="����";
		else
			strDstStatus="����";
		nIndex = m_listDst.InsertItem(0,m_config.m_dstComputer[i].DstIP);
		m_listDst.SetItemText(nIndex, 1, strDstType);
		m_listDst.SetItemText(nIndex, 2, strDstStatus);
	}
	UpdateData(false);
	return true;
}
/////////////////////////////////////////////////////////////////////
//���¹�����Ϣ������
/////////////////////////////////////////////////////////////////////
bool CTransferfileDlg::UpdatePubConfig() 
{
	// TODO: Add your command handler code here
	UpdateData(true);
	int i=0;
	//�汾
	for(i=0;i<3;i++)
	{
		if(strVerName[i]==m_config.m_srcVersion)
		{
			m_radioVer=i;
		}
	}
	//Դ��
	for(i=0;i<6;i++)
	{
		if(strDriverName[i]==m_config.m_srcDriver)
		{
			m_radioDriver=i;
		}
	}
	//��ѡ�ļ�
	if(m_config.m_srcFileSel[0]==1)
	{
		m_check1=1;
	}
	else
	{
		m_check1=0;
	}
	if(m_config.m_srcFileSel[1]==1)
	{
		m_check2=1;
	}
	else
	{
		m_check2=0;
	}
	if(m_config.m_srcFileSel[2]==1)
	{
		m_check3=1;
	}
	else
	{
		m_check3=0;
	}
	if(m_config.m_srcFileSel[3]==1)
	{
		m_check4=1;
	}
	else
	{
		m_check4=0;
	}
	if(m_config.m_srcFileSel[4]==1)
	{
		m_check5=1;
	}
	else
	{
		m_check5=0;
	}
	if(m_config.m_srcFileSel[5]==1)
	{
		m_check6=1;
	}
	else
	{
		m_check6=0;
	}
	if(m_config.m_srcFileSel[6]==1)
	{
		m_check7=1;
	}
	else
	{
		m_check7=0;
	}
	if(m_config.m_srcFileSel[7]==1)
	{
		m_check8=1;
	}
	else
	{
		m_check8=0;
	}
	UpdateData(false);
	return true;
}

void CTransferfileDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
}

void CTransferfileDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	if(m_config.GetConfigFromFile()==false)
		AfxMessageBox("��ȡ�����ļ����ִ���");
	else
		AfxMessageBox("������Ϣ��ʼ���ɹ���");
}

/////////////////////////////////////////////////////////////////////
//PC���ļ����䴦����
//����shellexecuteex����xcopy.exe�����ļ�����
/////////////////////////////////////////////////////////////////////
bool TransferFileToPC(int nDst)
{
	int i,j;
	CString strTmp;							
	XcopyFilePath=strWindowsPath+"\\system32\\xcopy.exe";
	//���Ҹ��ļ��Ƿ����
	CFileFind fileFind;								//�����ļ�����
	i=fileFind.FindFile(XcopyFilePath);
	//���û�ҵ�����ȡ��ǰĿ¼�µ�xcopy.exe�ļ�
	if(!i)
	{
		XcopyFilePath=CurExeFilePath+"xcopy.exe";
	}
	SHELLEXECUTEINFO ShExecInfo = {0};				//ShellExecuteEX����
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = "open";
	ShExecInfo.lpFile = XcopyFilePath;	
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_HIDE;
	ShExecInfo.hInstApp = NULL;	
	for(i=0;i<MaxFileType;i++)
	{
		if(m_config.m_srcFileSel[i]==1)
		{
			for(j=0;j<m_config.m_srcFileNum[j];j++)
			{
				strTmp= " " + m_config.m_srcFileDir[i]+"\\"+m_config.m_srcFileList[i][j];
				csMessage=" xcopy " + strTmp + "     ����";
				strTmp= strTmp+ "  \\\\"+ m_config.m_dstComputer[nDst].DstIP +"\\" ;
				strTmp= strTmp+ m_config.m_dstComputer[nDst].DstFileDir[i] +"\\ ";
				strTmp= strTmp + " /y";
				ShExecInfo.lpParameters=strTmp;
				ShellExecuteEx(&ShExecInfo);
				WaitForSingleObject(ShExecInfo.hProcess,INFINITE);
				Sleep(30);
				MyMsgBox(csMessage);
				Sleep(100);
			}
		}
	}
	return true;
}

/////////////////////////////////////////////////////////////////////
//Unix���ļ����䴦����
/////////////////////////////////////////////////////////////////////
bool TransferFileToUnix(int nDst)
{
	//�ж�nDst�Ϸ���
	if((nDst<0)||(nDst>(m_config.m_dstCount-1)))
	{
		csMessage="TransferFileToUnix������Ŀ��������Ŵ���!";
		MyMsgBox(csMessage);		
		return false;
	}
	int i,j;
	CFileFind fileFind;								//�����ļ�����
	CString strtmp,strLocFiles,strDstDir,tFile,
		strSrcFullName,strDstFullName;				//·�����ļ���
	UINT bContinue;									//��ʶ
	CInternetSession *pInetSession;					//Internetsession����
	CFtpConnection *pFtpConnection=NULL;			//ftpconnection����
	CString DstIP,Username,Passwd;					//�û���������
	int PortNum;									//�˿ں�
	DWORD myFlags;									//�������ͣ�ΪFTP_TRANSFER_TYPE_BINARY��FTP_TRANSFER_TYPE_ASCII
	IsTransDB=false;
	DstIP=m_config.m_dstComputer[nDst].DstIP;
	Username=m_config.m_dstComputer[nDst].Username;
	Passwd=m_config.m_dstComputer[nDst].Passwd;
	PortNum=m_config.m_dstComputer[nDst].PortNum;
	//��ʼ��Internetsession����	
	pInetSession=new CInternetSession(AfxGetAppName(),1, PRE_CONFIG_INTERNET_ACCESS); 
	try 
	{	
		//����IP��servername��ftp����
		Sleep(30);
		csMessage="���ڴ�ftp���ӣ����Ժ�...";
		MyMsgBox(csMessage);
		pFtpConnection=pInetSession->GetFtpConnection(DstIP,Username,Passwd,PortNum); 

	} 
	//�쳣����
	catch (CInternetException* pEx)					
	{
		// catch errors from WinINet
		TCHAR szErr[1024];
		//�����������ʧ���򱨴�
		Sleep(30);
		if (pEx->GetErrorMessage(szErr, 1024))		
			{
			csMessage="����" + DstIP +"ʧ�ܣ�ԭ��" + szErr;
			MyMsgBox(csMessage);
			}
		else
			{		
			csMessage="Could not get the ftp connection";
			MyMsgBox(csMessage);
			}

		Sleep(30);
		csMessage="���䵽Unix�� "+DstIP+" ʱ���ֹ��ϡ�\r\n��ȷ�ϸ������Ƿ����߻��û�����������ȷ��";
		nErrCount=nErrCount+1;
		strErrLog=strErrLog+csMessage+"\r\n";
		MyMsgBox(csMessage);

		pEx->Delete();
		if (pFtpConnection != NULL)
		{
			pFtpConnection->Close();
		
		}
		delete pFtpConnection;
		if (pInetSession != NULL)
		{
			pInetSession->Close();
		}
		delete pInetSession;
		Sleep(1000);
		return false;
	}
	Sleep(30);
	csMessage="��ftp���ӳɹ�!";
	MyMsgBox(csMessage);
	Sleep(30);
	CFtpFileFind CFtp(pFtpConnection);
	CString Tmp,Dir,strFilter;
	BOOL Ret=false;
	
	/////////////////////////////////////////////////////////////////////
	//���Ϊ�����ļ�
	if(transferType==0)
	{
		//ѭ������ÿһ���ļ�
		for(i=0;i<MaxFileType;i++)						
		{	
			Sleep(100);
			if(IsExit==true)
			{
				break;
			}
			//�õ��������ͣ�0ΪASC�ļ���1Ϊ�������ļ�
			if(m_config.m_fileType[i]==0)
			{	
				myFlags=FTP_TRANSFER_TYPE_ASCII;
			}	
			else
			{
				myFlags=FTP_TRANSFER_TYPE_BINARY;
			}
			//�ж��Ƿ�Ϊ�����ļ�
			if(i==1||i==3)
			{
				IsTransDB=true;
			}
			else
			{
				IsTransDB=false;
			}
			//continue;
			//����Windows��*.DBIN��*.dbin��ͬ������
	/*		if(i==7)
			{
				if((m_config.m_srcFileList[7]=="*.dbin") && 
					(m_config.m_srcFileList[4]=="*.DBIN"))
				{
					continue;
				}
			}
			if(m_config.m_srcFileList[i].GetLength()<1)
			{
				continue;
			}
	*/
			if(m_config.m_srcFileSel[i]==1)
			{

				for(j=0;j<m_config.m_srcFileNum[i];j++)
				{		
					m_config.m_srcFileList[i][j].TrimLeft();
					m_config.m_srcFileList[i][j].TrimRight();		
					//��ȡԴ�ļ�Ŀ¼�����������
					strLocFiles= m_config.m_srcFileDir[i]+"\\"+m_config.m_srcFileList[i][j];
					strDstDir=m_config.m_dstComputer[nDst].DstFileDir[i];
					//Sleep(30);
					//csMessage=strLocFiles+ "  ���ڽ��д���...";
					//MyMsgBox(csMessage);
					//���Ϊ�����ļ�
					//���ݹ������������ļ�
					bContinue=fileFind.FindFile(strLocFiles);		
					//�����ҳɹ�
					if(!bContinue)
					{
						Sleep(30);
						csMessage="����" + strLocFiles+ "  ʧ�ܡ�";
						MyMsgBox(csMessage);
						nErrCount=nErrCount+1;
						strErrLog=strErrLog+csMessage+"\t\r\n";
					}
					
					if(bContinue)								
					{
						//ѭ������ÿһ���ļ�
						do										
						{
							if(IsExit==true)
							{
								break;
							}
							bContinue=fileFind.FindNextFile();
							//��ȡ�ļ���
							tFile=fileFind.GetFileName();
							if(tFile=="."||tFile==".."||fileFind.IsHidden())continue;
							//��ȡԴ�ļ�����·��
							strSrcFullName=m_config.m_srcFileDir[i]+"\\"+tFile;
							//��ȡĿ���ļ�����·��
							strDstFullName=m_config.m_dstComputer[nDst].DstFileDir[i] +"/" +tFile;
							//����һ����Ӧ�ļ�
							Sleep(30);
							if(!pFtpConnection->PutFile(strSrcFullName,strDstFullName,myFlags)) 
							{
								nErrCount=nErrCount+1;
								csMessage="FtpPutFile " + strSrcFullName +" ʱ���ִ���";
								strErrLog=strErrLog+csMessage+"\t\r\n";
								MyMsgBox(csMessage);
							}
							else
							{
								nTransferCount=nTransferCount+1;
								csMessage="FtpPutFile " + strSrcFullName +" ��ɡ�";
								MyMsgBox(csMessage);
							}//end if
						}while(bContinue);
						fileFind.Close();
					}//end for
				}//end if
				Sleep(30);
				//csMessage=strLocFiles+ "  ����";
				//MyMsgBox(csMessage);
				//Sleep(30);
			}//end if
		}//end for
	}//end if

	
	/////////////////////////////////////////////////////////////////////
	//���Ϊ�����ļ�
	if(transferType==1)
	{
		//ѭ������ÿһ���ļ�
		for(i=0;i<MaxFileType;i++)						
		{	
			Sleep(100);
			if(IsExit==true)
			{
				break;
			}
			//�õ���������
			if(m_config.m_fileType[i]==0)
			{	
				myFlags=FTP_TRANSFER_TYPE_ASCII;
			}	
			else
			{
				myFlags=FTP_TRANSFER_TYPE_BINARY;
			}

			if(m_config.m_srcFileSel[i]==1)
			{
				for(j=0;j<m_config.m_srcFileNum[j];j++)
				{				
					//��ȡԴ�ļ�Ŀ¼�����������
					strLocFiles= m_config.m_srcFileDir[i]+"\\"+m_config.m_srcFileList[i][j];
					strDstDir=m_config.m_dstComputer[nDst].DstFileDir[i];
					strFilter=m_config.m_srcFileList[i][j];
					Dir=strDstDir+"/"+m_config.m_srcFileList[i][j];
					//Sleep(30);
					//csMessage=Dir+ "  ���ڽ��д���...";
					//MyMsgBox(csMessage);
					//���ݹ������������ļ�
					pFtpConnection->SetCurrentDirectory(strDstDir);
					bContinue=CFtp.FindFile(strFilter, 0);				
					if(!bContinue)
					{
						Sleep(30);
						csMessage="����" + Dir+ "  ʧ�ܡ�";
						MyMsgBox(csMessage);
						nErrCount=nErrCount+1;
						strErrLog=strErrLog+csMessage+"\t\r\n";
					}
					//�����ҳɹ�
					if(bContinue)								
					{
						//����Ŀ¼
			/*			if(CreateDirectory(m_config.m_srcFileDir[i],NULL)==0)
						{
							Sleep(30);
							nErrCount=nErrCount+1;
							csMessage="����Ŀ¼ " + m_config.m_srcFileDir[i] +" ʱ���ִ���";
							strErrLog=strErrLog+csMessage+"\t\r\n";
							MyMsgBox(csMessage);

						}
			*/
						//ѭ������ÿһ���ļ�
						do										
						{
							if(IsExit==true)
							{
								break;
							}
							bContinue=CFtp.FindNextFile();
							//��ȡ�ļ���
							tFile=CFtp.GetFileName();
							strtmp=tFile;
							//���ļ������д�����Ϊsun solaris��ȡ�õ��ļ�����������
							j=0;
							tFile.TrimRight();
							do
							{
								tFile.TrimLeft();
								j=tFile.Find(" ");
								tFile=tFile.Right(tFile.GetLength()-j-1);
							}while(j>=0);

							if(tFile=="."||tFile==".."||CFtp.IsHidden())continue;
							if(CFtp.IsDirectory()) continue;
							//��ȡԴ�ļ�����·��
							strSrcFullName=m_config.m_srcFileDir[i]+"\\"+tFile;
							//��ȡĿ���ļ�����·��
							strDstFullName=strDstDir +"/" +tFile;
							//����һ����Ӧ�ļ�
							Sleep(30);
			/*				if(tFile==".dbin")
							{
								Sleep(30);
								continue;
							}
			*/
							if(!pFtpConnection->GetFile(strDstFullName,strSrcFullName,false,FILE_ATTRIBUTE_NORMAL,myFlags)) 
							{
								nErrCount=nErrCount+1;
								strDstFullName=strDstDir +"/" +strtmp;
								csMessage="FtpGetFile " + strDstFullName +" ʱ���ִ���";
								strErrLog=strErrLog+csMessage+"\t\r\n";
								MyMsgBox(csMessage);
							}
							else
							{
								nTransferCount=nTransferCount+1;
								csMessage="FtpGetFile " + strDstFullName +" ��ɡ�";
								MyMsgBox(csMessage);
							}//end if
						}while(bContinue);
						fileFind.Close();
					}//end if
				}//end for
				Sleep(30);
				//csMessage=Dir+ "  ���ͽ���";
				//MyMsgBox(csMessage);
				//Sleep(30);
			}//end if
		}//end for
	}//end if
	
	//����ɾ��
	CFtp.Close();
	if (pFtpConnection != NULL)
	{
		pFtpConnection->Close();
		Sleep(200);
	}
	delete pFtpConnection;
	if (pInetSession != NULL)
	{
		pInetSession->Close();
		Sleep(200);
	}
	delete pInetSession;
	Sleep(1000);
	return true;
}


/////////////////////////////////////////////////////////////////////
//Unix���ļ����䴦����������.bat�ļ�������ftp.exe��ʽ��
/////////////////////////////////////////////////////////////////////
bool TransferFileToUnixByBat(int nDst)
{
/*
	CString strTxt;					//д��autoftp.txt�е����ݣ�ÿ����\r\n�ָ�  
	CString strBat;					//д��autoftp.bat�е�����
	CString FtpBatFullName;			//.bat�ļ�����·��
	CString strtmp,strLocFiles,strDstDir,tFile,
		strSrcFullName,strDstFullName;				//·�����ļ���	
	int i;
	CString DstIP,Username,Passwd;					//�û���������
	CString strFilter;
	int PortNum;									//�˿ں�
	FtpBatFullName=CurExeFilePath+FtpBatName;		
	SHELLEXECUTEINFO ShExecInfo = {0};				//ShellExecuteEX����
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = "open";
	ShExecInfo.lpFile = FtpBatFullName;	
	ShExecInfo.lpDirectory = NULL;
	if(m_config.m_ShowMode==0)
	{
		ShExecInfo.nShow = SW_HIDE;
	}
	else
	{
		ShExecInfo.nShow = SW_SHOW;
	}
	ShExecInfo.hInstApp = NULL;	
	ShExecInfo.lpParameters="";
	//�ж�nDst�Ϸ���
	if((nDst<0)||(nDst>(m_config.m_dstCount-1)))
	{
		csMessage="TransferFileToUnixByBat������Ŀ��������Ŵ���!";
		MyMsgBox(csMessage);		
		return false;
	}
	DstIP=m_config.m_dstComputer[nDst].DstIP;
	Username=m_config.m_dstComputer[nDst].Username;
	Passwd=m_config.m_dstComputer[nDst].Passwd;
	Username.TrimLeft();
	Username.TrimRight();
	if(Username.GetLength()<1)
	{
		Username="anonymous";
		Passwd="test@yang";
	}

	PortNum=m_config.m_dstComputer[nDst].PortNum;
	//autoftp.bat�Ĵ�
	strBat="ftp -s:"+CurExeFilePath + FtpTxtName + "\t" +DstIP; 
	
	/////////////////////////////////////////////////////////////////////
	//���Ϊ�����ļ�
	if(transferType==0)
	{
		//����autoftp.txt�ļ��Ĵ�
		strTxt="";
		strTxt=Username+"\r\n";
		strTxt=strTxt+Passwd+"\r\n";
		strTxt=strTxt+"prompt"+"\r\n";
		//����asc��mput ��
		strTxt=strTxt+"asc"+"\r\n";
		strTxt=strTxt+"\r\n";
		for(i=0;i<MaxFileType;i++)						
		{
			//�õ��������ͣ�0ΪASC�ļ���1Ϊ�������ļ�
			if((m_config.m_fileType[i]==0) && (m_config.m_srcFileSel[i]==1))
			{
				//��ȡԴ�ļ�Ŀ¼�����������
				strLocFiles= m_config.m_srcFileDir[i]+"\\"+m_config.m_srcFileList[i];
				strDstDir=m_config.m_dstComputer[nDst].DstFileDir[i];
				strTxt=strTxt+"cd"+"\t"+strDstDir+"\r\n";		
				strTxt=strTxt+"mput"+"\t"+strLocFiles+"\r\n";						
				strTxt=strTxt+"\r\n";
			}
		}
		//����bin��mput ��
		strTxt=strTxt+"bin"+"\r\n";
		strTxt=strTxt+"\r\n";
		for(i=0;i<MaxFileType;i++)						
		{
			//�õ��������ͣ�0ΪASC�ļ���1Ϊ�������ļ�
			if((m_config.m_fileType[i]==1) && (m_config.m_srcFileSel[i]==1))
			{
				//��ȡԴ�ļ�Ŀ¼�����������
				strLocFiles= m_config.m_srcFileDir[i]+"\\"+m_config.m_srcFileList[i];
				strDstDir=m_config.m_dstComputer[nDst].DstFileDir[i];
				strTxt=strTxt+"cd"+"\t"+strDstDir+"\r\n";		
				strTxt=strTxt+"mput"+"\t"+strLocFiles+"\r\n";						
				strTxt=strTxt+"\r\n";
			}
		}
		strTxt=strTxt+"quit"+"\r\n";
		//д��autoftp.bat��autoftp.txt�ļ�
		if(!WriteToFtpTxt(strBat,strTxt))
		{
			csMessage=DstIP + " ����ʱд���ı�/bat�ļ�ʱ����! ";
			MyMsgBox(csMessage);
			return false;
		}

		//����autoftp.bat�ļ�
//		ShellExecute(NULL, _T("open"), _T(FtpBatFullName), _T(""), NULL, SW_SHOW);
		csMessage=DstIP + " ���ڴ����ļ������Ժ�...... ";
		MyMsgBox(csMessage);
		ShellExecuteEx(&ShExecInfo);
		WaitForSingleObject(ShExecInfo.hProcess,INFINITE);
		Sleep(30);
		csMessage=DstIP + " �������! ";
		MyMsgBox(csMessage);

	}//end if
	
	/////////////////////////////////////////////////////////////////////
	//���Ϊ�����ļ�
	if(transferType==1)
	{
		//����autoftp.txt�ļ��Ĵ�
		strTxt="";
		strTxt=Username+"\r\n";
		strTxt=strTxt+Passwd+"\r\n";
		strTxt=strTxt+"prompt"+"\r\n";
		//����asc��mget ��
		strTxt=strTxt+"asc"+"\r\n";
		strTxt=strTxt+"\r\n";
		for(i=0;i<MaxFileType;i++)						
		{
			//�õ��������ͣ�0ΪASC�ļ���1Ϊ�������ļ�
			if((m_config.m_fileType[i]==0) && (m_config.m_srcFileSel[i]==1))
			{
				//��ȡԴ�ļ�Ŀ¼�����������
				strLocFiles= m_config.m_srcFileDir[i]+"\\"+m_config.m_srcFileList[i];
				strDstDir=m_config.m_dstComputer[nDst].DstFileDir[i];
				strTxt=strTxt+"cd"+"\t"+strDstDir+"\r\n";
				strTxt=strTxt+"lcd"+"\t"+m_config.m_srcFileDir[i]+"\r\n";
				strTxt=strTxt+"mget"+"\t"+m_config.m_srcFileList[i]+"\r\n";						
				strTxt=strTxt+"\r\n";
			}
		}

		//����bin��mget ��
		strTxt=strTxt+"bin"+"\r\n";
		strTxt=strTxt+"\r\n";
		for(i=0;i<MaxFileType;i++)						
		{
			//�õ��������ͣ�0ΪASC�ļ���1Ϊ�������ļ�
			if((m_config.m_fileType[i]==1) && (m_config.m_srcFileSel[i]==1))
			{
				//��ȡԴ�ļ�Ŀ¼�����������
				strLocFiles= m_config.m_srcFileDir[i]+"\\"+m_config.m_srcFileList[i];
				strDstDir=m_config.m_dstComputer[nDst].DstFileDir[i];
				strTxt=strTxt+"cd"+"\t"+strDstDir+"\r\n";
				strTxt=strTxt+"lcd"+"\t"+m_config.m_srcFileDir[i]+"\r\n";
				strTxt=strTxt+"mget"+"\t"+m_config.m_srcFileList[i]+"\r\n";						
				strTxt=strTxt+"\r\n";
			}
		}
		strTxt=strTxt+"quit"+"\r\n";
		//д��autoftp.bat��autoftp.txt�ļ�
		if(!WriteToFtpTxt(strBat,strTxt))
		{
			csMessage=DstIP + " ����ʱд���ı�/bat�ļ�ʱ����! ";
			MyMsgBox(csMessage);
			return false;
		}

		//����autoftp.bat�ļ�
		csMessage=DstIP + " ���ڴ����ļ������Ժ�...... ";
		MyMsgBox(csMessage);
		ShellExecuteEx(&ShExecInfo);
		WaitForSingleObject(ShExecInfo.hProcess,INFINITE);
		Sleep(30);
		csMessage=DstIP + " �������! ";
		MyMsgBox(csMessage);

	}//end if
//	AfxMessageBox(strTxt);
	Sleep(1000);
*/
	return true;
}

/////////////////////////////////////////////////////////////////////
//��ť����ʼ���䡱����Ӧ��������������̵Ĵ���
/////////////////////////////////////////////////////////////////////
void CTransferfileDlg::OnStarttransfer() 
{
	//ȷ���Ƿ���
	if(MessageBox("�����ļ�������ԭ���ļ������ȹر�\r\nĿ��������H9000ϵͳ���Ƿ����?",
		"��ȷ��...",MB_YESNO|MB_ICONQUESTION)==IDYES)
	{
		transferType=0;
		TransferControl();	
	}

}
/////////////////////////////////////////////////////////////////////
//������ƺ��������ݴ������Ͳ�ͬ���Է��ͺͽ��ս��п���
/////////////////////////////////////////////////////////////////////
bool CTransferfileDlg::TransferControl()
{
	//��������
	int i;
	i=0;
	//��һ�������ؼ���ֵ����m_config
	UpdateData(true);
	if(m_radioVer<0) m_radioVer=0;
	if(m_radioDriver<0) m_radioDriver=0;
	//�ӶԻ����ȡ��Դ�̺Ͱ汾������m_config	
	m_config.m_srcDriver=strDriverName[m_radioDriver];
	m_config.m_srcVersion=strVerName[m_radioVer];
	//UpdateLogLine(m_config.m_srcVersion);
	//UpdateLogLine(m_config.m_srcDriver);
	//�ӶԻ����ȡ�ô����ļ����Ͳ�����m_config
	for(i=0;i<MaxFileType;i++)
	{
		m_config.m_srcFileSel[i]=0;
	}
	if(m_check1==1)
	{
		m_config.m_srcFileSel[0]=1;
	}
	if(m_check2==1)
	{
		m_config.m_srcFileSel[1]=1;
	}
	if(m_check3==1)
	{
		m_config.m_srcFileSel[2]=1;
	}
	if(m_check4==1)
	{
		m_config.m_srcFileSel[3]=1;
	}
	if(m_check5==1)
	{
		m_config.m_srcFileSel[4]=1;
	}
	if(m_check6==1)
	{
		m_config.m_srcFileSel[5]=1;
	}
	if(m_check7==1)
	{
		m_config.m_srcFileSel[6]=1;
	}
	if(m_check8==1)
	{
		m_config.m_srcFileSel[7]=1;
	}
	//����Դ�̺Ͱ汾��Ϣ���õ�m_config�����·����Ϣ
	if(!m_config.SetConfigDir())			
	{	
		AfxMessageBox("����·������");
		return false;
	}
	//�ж�DATABASE.OUT�Ƿ���Ҫ�����Լ��Ƿ�ռ��
	if(m_config.m_srcFileSel[1]==1)
	{
		CString DBFilename;		
		DBFilename=m_config.m_srcFileDir[1]+"\\"+m_config.m_srcFileList[1][0];
		CFileFind fileFind;								//�����ļ�����
		i=fileFind.FindFile(DBFilename);
		//�����ڸ��ļ�
		if(i)
		{
			CFile myfile;
			
			if(!myfile.Open(DBFilename,CFile::modeReadWrite|CFile::shareExclusive))
			{
				AfxMessageBox("���ݿ������ļ�"+DBFilename+"���ڱ�ռ�á�\r\n\r\n���ȹرձ�����H9000��DETool��IPM������ٽ��д���!",MB_ICONSTOP);
				return false;//����ʧ�ܷ���
			}
			myfile.Close();
		}
	}
	//�ڶ����������������
	HWND hWnd=GetSafeHwnd();
	AfxBeginThread(ThreadProc,hWnd,0);
	//���������Ի�����洦��
	m_starttransfer.EnableWindow (FALSE);
	m_buttonAddDst.EnableWindow (FALSE);
	m_buttonSave.EnableWindow (FALSE);
	m_buttonGet.EnableWindow (FALSE);
	m_buttonSet.EnableWindow (FALSE);
	return true;
}

/////////////////////////////////////////////////////////////////////
//�ļ����䴦����̣��ļ������������
/////////////////////////////////////////////////////////////////////
UINT ThreadProc(LPVOID param)
{
	
	int i;									//��ʱ����
	int nDstCount;							//Ŀ�������ĸ���
	int nType;								//Ŀ����������
//	char buffer[10];
	threadcontroller=1;
	nTransferCount=0;
	nDstCount=m_config.m_dstCount;			//��������Ϣ�л�ȡĿ�������ĸ���
	Sleep(30);
	strErrLog="";
	csMessage="\r\n��ʼ���д���...";
	MyMsgBox(csMessage);
	Sleep(1000);
	nErrCount=0;
	//���Ϊ����
	if(transferType==0)
	{
	for(i=0;i<nDstCount;i++)							//ѭ������ÿ��Ŀ���������ļ�����
	{
		nType=m_config.m_dstComputer[i].DstType;		//��ȡ����
		if(m_config.m_dstComputer[i].Status != 1) continue;

		csMessage = "��ʼ����  " + m_config.m_dstComputer[i].DstIP +"  �Ĵ���...";
		Sleep(30);
		MyMsgBox(csMessage);
		Sleep(1000);
		
		if(nType==0)									//���ΪPC���������PC������
		{
			if(TransferFileToPC(i)==false)				//����PC���ļ����亯��
			{
				Sleep(30);
				nErrCount=nErrCount+1;
				csMessage="���䵽PC��ʱ���ֹ��ϡ�";
				strErrLog=strErrLog+csMessage+"\r\n";
				MyMsgBox(csMessage);
			}
		}
		else									//���ΪUnix���������Unix��������
		{
			//�������CFtpConnection��ʽ
			if(FtpTransMode==1)								
			{
				if(TransferFileToUnix(i)==false)		//����Unix���ļ����亯��
				{
					Sleep(300);
				}//end if
			}//end if
			//�������.bat��ʽ���д���
			else
			{
				if(TransferFileToUnixByBat(i)==false)		//����Unix���ļ���.bat��ʽ�����亯��
				{
					Sleep(300);
				}//end if
			}//end else
		}//end if
	}//end for
	}//end if
	
	//���Ϊ����
	if(transferType==1)
	{
		nType=m_config.m_dstComputer[curDst].DstType;	//��ȡ����

		csMessage = "��ʼ����  " + m_config.m_dstComputer[curDst].DstIP +"  �Ĵ���...";
		Sleep(30);
		MyMsgBox(csMessage);
		Sleep(1000);
		
		if(nType==0)									//���ΪPC�������˳�
		{
			//csMessage = m_config.m_dstComputer[i].DstIP +"ΪPC�������ܴ�PC�������ļ���";
			//Sleep(30);
			//MyMsgBox(csMessage);
			//Sleep(1000);
			threadcontroller=0;			
			return 0;
		}
		else											//���ΪUnix���������Unix��������
		{
			//�������CFtpConnection��ʽ
			if(FtpTransMode==1)								
			{
				if(TransferFileToUnix(curDst)==false)		//����Unix���ļ����亯��
				{
					Sleep(300);
				}//end if
			}//end if
			//�������.bat��ʽ���д���
			else
			{
				if(TransferFileToUnixByBat(curDst)==false)		//����Unix���ļ���.bat��ʽ�����亯��
				{
					Sleep(300);
				}//end if
			}//end else
		}//end if
	}
	Sleep(1000);
	csMessage="\r\n���д�������ѽ�����";
	MyMsgBox(csMessage);
	Sleep(300);	
	csMessage="���д�������ѽ�����";

/*	
	if(nErrCount<1)
	{
		sprintf(buffer,"%d",nTransferCount);
		csMessage="�����ļ��ɹ��������� ";
		csMessage=csMessage+buffer;
		csMessage=csMessage+" ���ļ���";
	}
	else
	{
		sprintf(buffer,"%d",nErrCount);
		csMessage=csMessage+"\r\n��������г��ֹ� " ;
		csMessage=csMessage+buffer;
		csMessage=csMessage+" �ι�����Ϣ��\r\n\r\n";
		csMessage=csMessage+strErrLog;
	}
*/

	csMessage="�����ļ�������";
	
	
	//�ָ��Ի���ؼ�
	pTransferfileDlg->m_starttransfer.EnableWindow (TRUE);
	pTransferfileDlg->m_buttonAddDst.EnableWindow (TRUE);
	pTransferfileDlg->m_buttonSave.EnableWindow (TRUE);
	pTransferfileDlg->m_buttonSet.EnableWindow (TRUE);
	AfxMessageBox(csMessage,MB_ICONINFORMATION);
	threadcontroller=0;
	Sleep(500);
	return 0;
}


/////////////////////////////////////////////////////////////////////
//���Ŀ������
/////////////////////////////////////////////////////////////////////
void CTransferfileDlg::OnAdddst() 
{
	// TODO: Add your command handler code here
	//m_tmpConfig=m_config;
	CDstprmDlg dlg(this);								//�����Ի������
	int nDstCount;
	int nResponse = dlg.DoModal();						//�����Ի���
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
		//����һ��Ŀ��������m_config
		m_config.m_dstCount=m_config.m_dstCount+1;
		nDstCount=m_config.m_dstCount;
		m_config.m_dstComputer[nDstCount-1].DstIP=dlg.m_ip;
		if(dlg.m_radiodriver<0) dlg.m_radiodriver=0;
		//�ӶԻ����ȡ��Դ�̺Ͱ汾������m_config	
		m_config.m_dstComputer[nDstCount-1].DstDriver=strDriverName[dlg.m_radiodriver];
		m_config.m_dstComputer[nDstCount-1].DstType=dlg.m_radioType;
		m_config.m_dstComputer[nDstCount-1].Status=dlg.m_status;
		m_config.m_dstComputer[nDstCount-1].Username=dlg.m_username;
		m_config.m_dstComputer[nDstCount-1].Passwd=dlg.m_passwd;
		m_config.m_dstComputer[nDstCount-1].PortNum=21;
		//ˢ��m_config��·�������Ϣ
		m_config.SetConfigDir();
		//ͨ��m_config��Ŀ��������Ϣ����IP�б����Ϣ
		UpdateIPList();
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
}

void MyMsgBox(CString MyMsg)
{
	pTransferfileDlg->PostMessage(WM_THREADPROC,0,(LPARAM)(LPCTSTR)MyMsg);
	//pTransferfileDlg->m_editLogCtrl
}


void CAboutDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

/////////////////////////////////////////////////////////////////////
//��������������Ϣ
/////////////////////////////////////////////////////////////////////
void CTransferfileDlg::OnSaveconfig() 
{
	// TODO: Add your control notification handler code here
	//���ؼ���ֵ����m_config
	int i;
	UpdateData(true);
	if(m_radioVer<0) m_radioVer=0;
	if(m_radioDriver<0) m_radioDriver=0;
	//�ӶԻ����ȡ��Դ�̺Ͱ汾������m_config	
	m_config.m_srcDriver=strDriverName[m_radioDriver];
	m_config.m_srcVersion=strVerName[m_radioVer];
	//�ӶԻ����ȡ�ô����ļ����Ͳ�����m_config
	for(i=0;i<MaxFileType;i++)
	{
		m_config.m_srcFileSel[i]=0;
	}
	if(m_check1==1)
	{
		m_config.m_srcFileSel[0]=1;
	}
	if(m_check2==1)
	{
		m_config.m_srcFileSel[1]=1;
	}
	if(m_check3==1)
	{
		m_config.m_srcFileSel[2]=1;
	}
	if(m_check4==1)
	{
		m_config.m_srcFileSel[3]=1;
	}
	if(m_check5==1)
	{
		m_config.m_srcFileSel[4]=1;
	}
	if(m_check6==1)
	{
		m_config.m_srcFileSel[5]=1;
	}
	if(m_check7==1)
	{
		m_config.m_srcFileSel[6]=1;
	}
	if(m_check8==1)
	{
		m_config.m_srcFileSel[7]=1;
	}
	
	m_config.WriteConfigToFile();
	csMessage="����������Ϣ�ɹ�!";
	MyMsgBox(csMessage);


}

/////////////////////////////////////////////////////////////////////
//��Ӧ��ȡ�ļ���ť
/////////////////////////////////////////////////////////////////////
void CTransferfileDlg::OnStartget() 
{
	// TODO: Add your control notification handler code here
	int i,iState;
	int nItemSelected=m_listDst.GetSelectedCount();	//��ѡ������
	int nItemCount=m_listDst.GetItemCount();		//��������
	curDst=-1;
	if(nItemSelected<1) 
	{
		AfxMessageBox("û��ѡ��������\r\n���ȴӼ�����б���ѡȡ��");
		return;
	}
	for(i=0;i<nItemCount;i++)
	{
		iState=m_listDst.GetItemState(i,LVIS_SELECTED);
		if(iState!=0)
		{
			curDst=m_config.m_dstCount-1-i;
			break;
		}
	}
	if(curDst<0)
	{
		AfxMessageBox("û��ѡ��������\r\n���ȴӼ�����б���ѡȡ��");
		return;
	}
	//���ΪPC��������GET
	if(m_config.m_dstComputer[curDst].DstType==0)
	{
		AfxMessageBox("���ܴ�PC���������ݣ�\r\n��Ӽ�����б�������ѡȡUNIX����");
		return;
	}
	if(MessageBox("�ò�������ѡ�еļ���������ļ���\r\n������ԭĿ¼��Ӧ�ļ����Ƿ����?",
		"��ȷ��...",MB_YESNO|MB_ICONWARNING)==IDYES)
	{
		transferType=1;				
		TransferControl();	
	}
}

void CTransferfileDlg::OnGetmenu() 
{
	// TODO: Add your command handler code here
	//����OnstartGet
	OnStartget(); 
}

void CTransferfileDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	//ȷ���Ƿ���
	if(MessageBox("�Ƿ�ȷ���˳���","��ȷ��...",MB_YESNO|MB_ICONQUESTION)!=IDYES)
	{
		return;
	}

	if(IsTransDB==true)
	{
		AfxMessageBox("���ڴ������ݿ���ۺϼ�������������ļ������Ժ����˳�����!");
		return;
	}
	//һֱ�ȴ��������˳�
	
	IsExit=true;
//	while(threadcontroller==1)
//	{
//		Sleep(100);
//	}
	CDialog::OnCancel();
	DestroyWindow();
}

/////////////////////////////////////////////////////////////////////
//���ù���������ť
/////////////////////////////////////////////////////////////////////
void CTransferfileDlg::OnSetFilter() 
{
	// TODO: Add your control notification handler code here
/*	CSetFilterDlg dlg(this);								//�����Ի������
	int i;
	CString strline,strtmp;	
	//���Ի����������
	dlg.m_editF1=m_config.m_srcFileList[0];
	dlg.m_editF2=m_config.m_srcFileList[1];
	dlg.m_editF3=m_config.m_srcFileList[2];
	dlg.m_editF4=m_config.m_srcFileList[3];
	dlg.m_editF6=m_config.m_srcFileList[5];
	dlg.m_editF7=m_config.m_srcFileList[6];
	//�����ļ����⴦��
	dlg.m_editF5=m_config.m_srcFileList[4]+" | ";
	dlg.m_editF5=dlg.m_editF5+m_config.m_srcFileList[7]+" | ";
	dlg.m_editF5=dlg.m_editF5+m_config.m_srcFileList[8]+" | ";
	dlg.m_editF5=dlg.m_editF5+m_config.m_srcFileList[9];
	int nResponse = dlg.DoModal();				//�����Ի���
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
		//���޸ĺ����Ϣд��m_config
		m_config.m_srcFileList[0]=dlg.m_editF1;
		m_config.m_srcFileList[1]=dlg.m_editF2;
		m_config.m_srcFileList[2]=dlg.m_editF3;
		m_config.m_srcFileList[3]=dlg.m_editF4;
		m_config.m_srcFileList[5]=dlg.m_editF6;
		m_config.m_srcFileList[6]=dlg.m_editF7;
		//�����ļ����⴦��
		strline=dlg.m_editF5;
		strline.TrimLeft();
		strline.TrimRight();
		strline.Replace(" ","");
		i=strline.Find("|");
		//����һ
		if(i>=0)
		{	
			m_config.m_srcFileList[4]=strline.Left(i);
			strline=strline.Right(strline.GetLength()-i-1);
		}
		else
		{
			m_config.m_srcFileList[4]=strline;
			strline="";
		}
		//������
		i=strline.Find("|");		
		if(i>=0)
		{	
			m_config.m_srcFileList[7]=strline.Left(i);
			strline=strline.Right(strline.GetLength()-i-1);
		}
		else
		{
			m_config.m_srcFileList[7]=strline;;
			strline="";
		}
		//������
		i=strline.Find("|");		
		if(i>=0)
		{	
			m_config.m_srcFileList[8]=strline.Left(i);
			strline=strline.Right(strline.GetLength()-i-1);
		}
		else
		{
			m_config.m_srcFileList[8]=strline;;
			strline="";
		}
		//������
		i=strline.Find("|");		
		if(i>=0)
		{	
			m_config.m_srcFileList[9]=strline.Left(i);
		}
		else
		{
			m_config.m_srcFileList[9]=strline;
			strline="";
		}
		csMessage="���ù��������ɹ�!";
		MyMsgBox(csMessage);
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
*/
}

/////////////////////////////////////////////////////////////////////
//����autoftp.bat��autoftp.txt�ļ�
/////////////////////////////////////////////////////////////////////
bool WriteToFtpTxt(CString mystrBat,CString mystrTxt)
{
/*
	CString strFilePath;
	CFile myfile;
	//д��autoftp.txt�ļ�
	strFilePath=CurExeFilePath+FtpTxtName;		
	if (!myfile.Open(strFilePath,CFile::modeCreate|CFile::modeWrite,NULL))
	{
		csMessage="��/����txt�ļ�ʧ��!";
		MyMsgBox(csMessage);
		return false;
	}
	myfile.Write(mystrTxt,mystrTxt.GetLength());
	myfile.Close();
	//д��autoftp.bat�ļ�
	strFilePath=CurExeFilePath+FtpBatName;		
	if (!myfile.Open(strFilePath,CFile::modeCreate|CFile::modeWrite,NULL))
	{
		csMessage="��/����txt�ļ�ʧ��!";
		MyMsgBox(csMessage);
		return false;
	}
	myfile.Write(mystrBat,mystrBat.GetLength());
	myfile.Close();
*/
	return true;
}

void CTransferfileDlg::OnRadiodriverf() 
{
	// TODO: Add your control notification handler code here
	csMessage="���ش�������ΪF:\\ ,  ����·��ΪF:\\Users\\ems\\";
	MyMsgBox(csMessage);
	
}

void CTransferfileDlg::OnRadiodrivere() 
{
	// TODO: Add your control notification handler code here
/*
	if(MessageBox("���Ƿ�ȷ�������ش�������Ϊ E �� ? ","��ȷ��...",MB_YESNO|MB_ICONQUESTION)!=IDYES)
	{
		m_radioDriver=2;
		UpdateData(false);
		return;
	}
*/
	csMessage="���ش�������ΪE:\\ ,  ����·��ΪE:\\Users\\ems\\";
	MyMsgBox(csMessage);
	UpdateData(true);
	m_config.m_srcDriver=strDriverName[m_radioDriver];
	m_config.m_srcVersion=strVerName[m_radioVer];
	if(!m_config.SetConfigDir())			
	{	
		AfxMessageBox("����·������");
	}
	return;
}

void CTransferfileDlg::OnRadiodriverd() 
{
	// TODO: Add your control notification handler code here
/*	if(MessageBox("���Ƿ�ȷ�������ش�������Ϊ D �� ? ","��ȷ��...",MB_YESNO|MB_ICONQUESTION)!=IDYES)
	{
		m_radioDriver=3;
		UpdateData(false);
		return;
	}
*/
	csMessage="���ش�������ΪD:\\ ,  ����·��ΪD:\\Users\\ems\\";
	MyMsgBox(csMessage);
	UpdateData(true);
	m_config.m_srcDriver=strDriverName[m_radioDriver];
	m_config.m_srcVersion=strVerName[m_radioVer];	
	if(!m_config.SetConfigDir())			
	{	
		AfxMessageBox("����·������");
	}
	return;	
}

void CTransferfileDlg::OnClickListdst(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CTransferfileDlg::OnSetfilter1() 
{
	// TODO: Add your control notification handler code here
	if(ShowFileDlg(0)==true)
	{

	}
}

bool CTransferfileDlg::ShowFileDlg(int DlgID)
{
	int i,j;
	CString strFile;						//��ѡ�ļ��б�
	char buff[10];
	CString strFilename,strPathname,strTmp;				
	CFileDialog dlgFile(TRUE);				//ѡ���ļ��Ի��� 
	char* buf = new char[MAXFILE];
	dlgFile.m_ofn.lStructSize=76;			//88ΪWind2000�ķ��76ΪWin98�ļ򵥷��	
	dlgFile.m_ofn.lpstrFile = buf;
	dlgFile.m_ofn.lpstrFile[0] = NULL; 
	dlgFile.m_ofn.lpstrDefExt=".rtf";
	if(DlgID==0)
	{
		dlgFile.m_ofn.lpstrFilter= "���ݿ��ı��ļ�(*.*)\0*.*";
	}
	if(DlgID==1)
	{
		dlgFile.m_ofn.lpstrFilter= "���ݿ������ļ�(*.OUT)\0*.OUT";
	}
	if(DlgID==2)
	{
		dlgFile.m_ofn.lpstrFilter= "�����������ۺϼ����ı�(*.txt)\0*.txt";
	}
	if(DlgID==3)
	{
		dlgFile.m_ofn.lpstrFilter= "�����������ۺϼ��������ļ�(*.dat)\0*.dat";
	}
	if(DlgID==4)
	{
		dlgFile.m_ofn.lpstrFilter= "�����ļ�(*.*)\0*.*";
	}
	if(DlgID==5)
	{
		dlgFile.m_ofn.lpstrFilter= "�����ļ�(*.wav)\0*.wav";
	}
	if(DlgID==6)
	{
		dlgFile.m_ofn.lpstrFilter= "�¹�׷���ļ�(*.FAIL)\0*.FAIL";
	}
	if(DlgID==7)
	{
		dlgFile.m_ofn.lpstrFilter= "��Ŀ�����ļ�(*.txt)\0*.txt";
	}
	dlgFile.m_ofn.Flags|=OFN_PATHMUSTEXIST|OFN_CREATEPROMPT|OFN_ENABLESIZING|OFN_EXTENSIONDIFFERENT|OFN_ALLOWMULTISELECT;
	dlgFile.m_ofn.nMaxFile = MAXFILE; 
	dlgFile.m_ofn.lpstrInitialDir=m_config.m_srcFileDir[DlgID];
	//strFile="ע�⣺һ��ѡ����ļ��������ܳ���1000��!\r\n";
	//UpdateLogLine(strFile);
	if(dlgFile.DoModal() == IDOK)        
	{		
		j=0;
		POSITION pos = dlgFile.GetStartPosition();
		while (pos != NULL)
		{
			strPathname=dlgFile.GetNextPathName(pos); 
			strPathname.TrimRight();
			i=strPathname.ReverseFind('\\');			
			m_config.m_srcFileList[DlgID][j]=strPathname.Mid(i+1); 
			j++;
			strFile+=strPathname.Mid(i+1);
			strFile+="\r\n";
		}
		sprintf(buff,"%d",j);
		strFile+="��ѡ���ļ�������";
		strFile+=buff;
		strFile+="\r\n";
		m_config.m_srcFileNum[DlgID]= j;
	}

	UpdateLogLine(strFile);
	return true;
}

void CTransferfileDlg::OnSetfilter2() 
{
	// TODO: Add your control notification handler code here
	if(ShowFileDlg(1)==true)
	{

	}	
}

void CTransferfileDlg::OnSetfilter3() 
{
	// TODO: Add your control notification handler code here
	if(ShowFileDlg(2)==true)
	{

	}	
}

void CTransferfileDlg::OnSetfilter4() 
{
	// TODO: Add your control notification handler code here
	if(ShowFileDlg(3)==true)
	{

	}	
}

void CTransferfileDlg::OnSetfilter5() 
{
	// TODO: Add your control notification handler code here
	if(ShowFileDlg(4)==true)
	{

	}	
}

void CTransferfileDlg::OnSetfilter6() 
{
	// TODO: Add your control notification handler code here
	if(ShowFileDlg(5)==true)
	{

	}	
}

void CTransferfileDlg::OnSetfilter7() 
{
	// TODO: Add your control notification handler code here
	if(ShowFileDlg(6)==true)
	{

	}	
}

void CTransferfileDlg::OnRadiodriverc() 
{
	// TODO: Add your control notification handler code here
	csMessage="���ش�������Ϊc:\\ ,  ����·��Ϊc:\\Users\\ems\\";
	MyMsgBox(csMessage);
	UpdateData(true);
	m_config.m_srcDriver=strDriverName[m_radioDriver];
	m_config.m_srcVersion=strVerName[m_radioVer];
	if(!m_config.SetConfigDir())			
	{	
		AfxMessageBox("����·������");
	}
}

void CTransferfileDlg::OnRadiover2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	//����Դ�̺Ͱ汾��Ϣ���õ�m_config�����·����Ϣ
	m_config.m_srcDriver=strDriverName[m_radioDriver];
	m_config.m_srcVersion=strVerName[m_radioVer];
	if(!m_config.SetConfigDir())			
	{	
		AfxMessageBox("����·������");
	}
}

void CTransferfileDlg::OnRadiover3() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	//����Դ�̺Ͱ汾��Ϣ���õ�m_config�����·����Ϣ
	m_config.m_srcDriver=strDriverName[m_radioDriver];
	m_config.m_srcVersion=strVerName[m_radioVer];
	if(!m_config.SetConfigDir())			
	{	
		AfxMessageBox("����·������");
	}
}

void CTransferfileDlg::OnEnablemenu() 
{
	// TODO: Add your command handler code here
	// TODO: Add your command handler code here
	int i,iState;
	int nDst=0;										//ѡ�е�Ŀ���������
	int nItemSelected=m_listDst.GetSelectedCount();	//��ѡ������
	int nItemCount=m_listDst.GetItemCount();		//��������
	if(nItemSelected<1) return;
	//�����ѡ��������
	for(i=0;i<nItemCount;i++)
	{
		iState=m_listDst.GetItemState(i,LVIS_SELECTED);
		if(iState!=0)
		{
			nDst=m_config.m_dstCount-1-i;
			break;
		}
	}
	if(m_config.m_dstComputer[nDst].Status==0)
		m_config.m_dstComputer[nDst].Status= 1;
	else
		m_config.m_dstComputer[nDst].Status= 0;
	UpdateIPList();
	return;	
}



void CTransferfileDlg::OnSetfilter8() 
{
	// TODO: Add your control notification handler code here
	if(ShowFileDlg(7)==true)
	{

	}	
}

void CTransferfileDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnLButtonDown(nFlags, point);
}
