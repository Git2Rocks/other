// DstSelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "transferfile.h"
#include "transferfileDlg.h"
#include "DstSelDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


										//hosts�ļ�������·�����ļ���	
CString HostFilePath="C:\\winnt\\system32\\drivers\\etc\\hosts";

/////////////////////////////////////////////////////////////////////////////
// CDstSelDlg dialog


CDstSelDlg::CDstSelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDstSelDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDstSelDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDstSelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDstSelDlg)
	DDX_Control(pDX, IDC_LISTHOST, m_listHost);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDstSelDlg, CDialog)
	//{{AFX_MSG_MAP(CDstSelDlg)
	ON_BN_CLICKED(IDCONFIRM, OnConfirm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDstSelDlg message handlers

void CDstSelDlg::OnConfirm() 
{
	// TODO: Add your control notification handler code here
		int i,iState,nItemSelected,nItemCount;
		nItemSelected=m_listHost.GetSelectedCount();	//��ѡ������
		nItemCount=m_listHost.GetItemCount();			//��������#
		if(nItemSelected<1) return;
		for(i=0;i<nItemCount;i++)
		{
			iState=m_listHost.GetItemState(i,LVIS_SELECTED);
			if(iState!=0)							//���Ϊ��ѡ����ȡ��������
			{
				m_curName=m_listHost.GetItemText(i,0);
			}
		}
	CDialog::OnOK();
}


BOOL CDstSelDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	//��ʼ��HOST������б�
	m_listHost.InsertColumn(0, "�������");		
	m_listHost.InsertColumn(1, "IP��ַ");
	m_listHost.SetColumnWidth(0, 150);
	m_listHost.SetColumnWidth(1, 150);	
	//��ȡhosts�ļ�
	int i;
	int nIndex;
	CStdioFile myfile;
	CString strFilePath;
	CString strline;
	CString strIP;
	CString strName;
	TCHAR exeFullPath[MAX_PATH]; // MAX_PATH��API�ж����˰ɣ�������128 
	GetWindowsDirectory(exeFullPath,MAX_PATH);
	HostFilePath=exeFullPath;
	HostFilePath=HostFilePath+"\\system32\\drivers\\etc\\hosts";
	strFilePath=HostFilePath;
	if ( !myfile.Open(strFilePath,CFile::modeRead,NULL) )
	{
		MessageBox(strFilePath+"û���ҵ���","Error",MB_OK);
		return true;
	}

	while(myfile.ReadString(strline))
	{
		i=strline.Find("#");
		if(strline.Find("#")<0)			//�����Ƿ���#��
		{
			
			if(strline.Find(".")>=0)
			{
				strline.TrimLeft();
				strline.TrimRight();
				strline.Replace("	"," ");
				i=strline.Find(" ");
				strIP=strline.Left(i);
				strName=strline.Right(strline.GetLength()-i-1);
				strName.TrimLeft();
				nIndex = m_listHost.InsertItem(0,strName);
				m_listHost.SetItemText(nIndex, 1, strIP);
			
			}
		}
		//FileContainer.Add(strline);
	}

	myfile.Close();

	UpdateData(false);
	return true;
}

//��HOST�ļ��ж�ȡ������б�
BOOL CDstSelDlg::GetListFromHost()
{
	CString strtmp;
	strtmp=HostFilePath;
	return true;
}
