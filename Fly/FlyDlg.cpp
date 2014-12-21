// FlyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Fly.h"
#include "FlyDlg.h"
#include "shlwapi.h"
#include "io.h"
#pragma comment(lib,"shlwapi.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFlyDlg dialog




CFlyDlg::CFlyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFlyDlg::IDD, pParent)
	, m_iFilecount(0)
	, m_iFilecurcount(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFlyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EFR, m_ctrFr);
	DDX_Control(pDX, IDC_ETD, m_ctrTd);
	DDX_Control(pDX, IDC_STA, m_ctrSt);
}

BEGIN_MESSAGE_MAP(CFlyDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BFR, &CFlyDlg::OnBnClickedBfr)
	ON_BN_CLICKED(IDC_BTD, &CFlyDlg::OnBnClickedBtd)
	ON_BN_CLICKED(IDC_BRNM, &CFlyDlg::OnBnClickedBrnm)
	ON_BN_CLICKED(IDC_BCP, &CFlyDlg::OnBnClickedBcp)
END_MESSAGE_MAP()


// CFlyDlg message handlers

BOOL CFlyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	//pan-the process deal with
	m_ctrSt.SetWindowText("start..........");

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFlyDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFlyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CFlyDlg::OnBnClickedBfr()
{
	// TODO: Add your control notification handler code here
	//pan-choose dir
	char buf[MAX_PATH];
	ZeroMemory(buf,MAX_PATH);

    BROWSEINFO bi;
	bi.hwndOwner=GetSafeHwnd();
	bi.pidlRoot=NULL;
	bi.lpszTitle="choose dir";
	bi.ulFlags=BIF_EDITBOX;
	bi.lpfn=NULL;
	bi.iImage=0;
	bi.lParam=0;
	bi.pszDisplayName=buf;

	LPITEMIDLIST plist=NULL;
	if((plist=SHBrowseForFolder(&bi))!=NULL)
	{
		char path[MAX_PATH];
		ZeroMemory(path,MAX_PATH);
		SHGetPathFromIDList(plist,path);
		m_ctrFr.SetWindowText(path);
	}

}

void CFlyDlg::OnBnClickedBtd()
{
	// TODO: Add your control notification handler code here
	//pan-choose dir
	char buf[MAX_PATH];
	ZeroMemory(buf,MAX_PATH);

    BROWSEINFO bi;
	bi.hwndOwner=GetSafeHwnd();
	bi.pidlRoot=NULL;
	bi.lpszTitle="choose dir";
	bi.ulFlags=BIF_EDITBOX;
	bi.lpfn=NULL;
	bi.iImage=0;
	bi.lParam=0;
	bi.pszDisplayName=buf;

	LPITEMIDLIST plist=NULL;
	if((plist=SHBrowseForFolder(&bi))!=NULL)
	{
		char path[MAX_PATH];
		ZeroMemory(path,MAX_PATH);
		SHGetPathFromIDList(plist,path);
		m_ctrTd.SetWindowText(path);
	}
}

void CFlyDlg::OnBnClickedBrnm()
{
	// TODO: Add your control notification handler code here
	//pan-ranme file
	CString renamePath;
	CString strSt;
	m_ctrFr.GetWindowText(renamePath);
	if(renamePath.IsEmpty()||(!PathIsDirectory(renamePath)))
	{
		MessageBox("Please choose the rename directory in FromSource");
		return;
	}
	else
	{
		m_iFilecount=0;
		strSt.Format("start..........please wait!");
		m_ctrSt.SetWindowText(strSt);
		GetDlgItem(IDOK)->EnableWindow(false);
		GetDlgItem(IDC_EFR)->EnableWindow(false);
		GetDlgItem(IDC_ETD)->EnableWindow(false);
		GetDlgItem(IDC_BFR)->EnableWindow(false);
		GetDlgItem(IDC_BTD)->EnableWindow(false);
		GetDlgItem(IDC_BRNM)->EnableWindow(false);
		GetDlgItem(IDC_BCP)->EnableWindow(false);
		Krename(renamePath);

	}
	GetDlgItem(IDOK)->EnableWindow(true);
	GetDlgItem(IDC_EFR)->EnableWindow(true);
	GetDlgItem(IDC_ETD)->EnableWindow(true);
	GetDlgItem(IDC_BFR)->EnableWindow(true);
	GetDlgItem(IDC_BTD)->EnableWindow(true);
	GetDlgItem(IDC_BRNM)->EnableWindow(true);
	GetDlgItem(IDC_BCP)->EnableWindow(true);
	strSt.Format("finished.....%Ld.....please again!",m_iFilecount);
	m_ctrSt.SetWindowText(strSt);
}

void CFlyDlg::OnBnClickedBcp()
{
	// TODO: Add your control notification handler code here
	//pan-copy file
	CString strFpath;
	CString strTpath;
	CString strSt;
	m_ctrFr.GetWindowText(strFpath);
	m_ctrTd.GetWindowText(strTpath);
	if(strFpath.IsEmpty()||(!PathIsDirectory(strFpath))||
	   strTpath.IsEmpty()||(!PathIsDirectory(strTpath)))
	{
		MessageBox("Please choose the from directory in FromSource and to directory in to destination");
		return;
	}
	else
	{
		m_iFilecount=0;
		strSt.Format("start..........please wait!");
		m_ctrSt.SetWindowText(strSt);
		GetDlgItem(IDOK)->EnableWindow(false);
		GetDlgItem(IDC_EFR)->EnableWindow(false);
		GetDlgItem(IDC_ETD)->EnableWindow(false);
		GetDlgItem(IDC_BFR)->EnableWindow(false);
		GetDlgItem(IDC_BTD)->EnableWindow(false);
		GetDlgItem(IDC_BRNM)->EnableWindow(false);
		GetDlgItem(IDC_BCP)->EnableWindow(false);
		Kcopy(strFpath,strTpath);


	}
	GetDlgItem(IDOK)->EnableWindow(true);
	GetDlgItem(IDC_EFR)->EnableWindow(true);
	GetDlgItem(IDC_ETD)->EnableWindow(true);
	GetDlgItem(IDC_BFR)->EnableWindow(true);
	GetDlgItem(IDC_BTD)->EnableWindow(true);
	GetDlgItem(IDC_BRNM)->EnableWindow(true);
	GetDlgItem(IDC_BCP)->EnableWindow(true);
	strSt.Format("finished.....%Ld.....please again!",m_iFilecount);
	m_ctrSt.SetWindowText(strSt);
}
//pan-rename fun
void CFlyDlg::Krename(CString strDir)
{
	CString strpath;

	CString strnewfilepath;
	CString strfilepath;
	CString strfilename;
	CString strfilenewname;

	CFile   file;
	CFileFind find;
	BOOL      bf;
	CFileStatus  fileSta;

	if(strDir.IsEmpty()||(!PathIsDirectory(strDir)))
		return;
	else
	{
		strpath=strDir;
		if(strpath.Right(1)!="\\")
			strpath+="\\*.*";

		bf=find.FindFile(strpath);
		while(bf)
		{
			bf=find.FindNextFile();
			//system directory
			if(find.IsDots())
				continue;
			//sub directory
			else if(find.IsDirectory())
			{
				Krename(find.GetFilePath());
			}
			//file
			else
			{
				//pan-open ok
				if(file.Open(find.GetFilePath(),CFile::modeRead))
				{
					if(file.GetStatus(fileSta))
					{
						if(fileSta.m_size == 16384)
						{
							char szline[1024]="";
							file.Read(szline,1000);
							file.Close();
							strfilenewname=szline;
							strfilenewname+=".dat";
                            //pan-rename file
							m_iFilecount++;
							strfilename=find.GetFileName();
							strfilepath=find.GetFilePath();
							strnewfilepath=find.GetFilePath();
							strnewfilepath.Replace(strfilename,strfilenewname);
							::rename(strfilepath,strnewfilepath);	
						}
					}
					file.Close();
				}
				//pan-open fail return
				else
				{
					return;
				}
			}//end file 
		}//while(bf)
	}//end path
}

//pan-copy fun
void CFlyDlg::Kcopy(CString strFromPath, CString strToPath)
{
	CString strSt;
	CString strFpath;
	CString strTpath;
	CString strNewpath;
	CString strFilename;
	CFileFind  find;
	BOOL       bf;

	if(strFromPath.IsEmpty()||(!PathIsDirectory(strFromPath))||
	   strToPath.IsEmpty()||(!PathIsDirectory(strToPath)))
		return;

	else
	{
		strFpath=strFromPath;
		strTpath=strToPath;
        //pan-build path
		if(strFpath.Right(1)!="\\")
			strFpath+="\\*.*";
		if(strTpath.Right(1)!="\\")
			strTpath+="\\";

		bf=find.FindFile(strFpath);
		while(bf)
		{
			bf=find.FindNextFile();
			//system directory
			if(find.IsDots())
				continue;
			//sub directory
			else if(find.IsDirectory())
			{
				Kcopy(find.GetFilePath(),strTpath);
			}
			//file
			else
			{
				strFilename=find.GetFileName();
				//pan-which file to copy
				if(strFilename.Right(4)==".dat")
				{
					m_iFilecount++;                   
					strNewpath=strTpath+strFilename;
					CopyFile(find.GetFilePath(),strNewpath,0);
				}

			}//end file

		}//end while(bf)

	}//end path
}
//pan-get rename file counts
int CFlyDlg::GetRenameFileCount(CString strDir)
{
	CString strpath;
	CFile   file;
	CFileFind find;
	BOOL      bf;
	CFileStatus  fileSta;

	if(strDir.IsEmpty()||(!PathIsDirectory(strDir)))
		return 0;
	else
	{
		strpath=strDir;
		if(strpath.Right(1)!="\\")
			strpath+="\\*.*";

		bf=find.FindFile(strpath);
		while(bf)
		{
			bf=find.FindNextFile();
			//system directory
			if(find.IsDots())
				continue;
			//sub directory
			else if(find.IsDirectory())
			{
				GetRenameFileCount(find.GetFilePath());
			}
			//file
			else
			{
				if(file.Open(find.GetFilePath(),CFile::modeRead))
				{
					if(file.GetStatus(fileSta))
					{
						if(fileSta.m_size == 16384)
						{
							m_iFilecount++;
						}
					}
					file.Close();
				}

			}//end file else
		}//while(bf)
	}//path else

	return m_iFilecount;
}

int CFlyDlg::GetCopyFileCount(CString strDir)
{
	CString strpath;
	CString strFilename;
	CFileFind  find;
	BOOL       bf;

	if(strDir.IsEmpty()||(!PathIsDirectory(strDir)))
		return 0;

	else
	{
		strpath=strDir;
        //pan-build path
		if(strpath.Right(1)!="\\")
			strpath+="\\*.*";

		bf=find.FindFile(strpath);
		while(bf)
		{
			bf=find.FindNextFile();
			//system directory
			if(find.IsDots())
				continue;
			//sub directory
			else if(find.IsDirectory())
			{
				GetCopyFileCount(find.GetFilePath());
			}
			//file
			else
			{
				strFilename=find.GetFileName();
				//pan-which file to copy
				if(strFilename.Right(4)==".dat")
				{
					m_iFilecount++;
				}

			}//end file

		}//end while(bf)

	}//end path
	return m_iFilecount;
}


