// AppConfigMngr.cpp
// Management of application parameters, global/global user/project/project user

// see AppConfigMngr.h for specifications

#include "stdafx.h"

#include "AppConfigMngr.h"

#ifdef _DEBUG
#undef DEBUG_NEW
#define DEBUG_NEW new(__FILE__, __LINE__)
#define _CRTDBG_MAP_ALLOC
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////
// Constructors
CAppConfigMngr::CAppConfigMngr(CString CurrentOpenDrive, CString CurrentOpenProject, CString CurrentUser)
{
	m_CurrentOpenDrive = CurrentOpenDrive;
	m_CurrentOpenProject = CurrentOpenProject;
	m_CurrentUser = CurrentUser;
}

CAppConfigMngr::CAppConfigMngr()
{
	m_CurrentOpenDrive = "";
	m_CurrentOpenProject = "";
	m_CurrentUser = "";
}

// Get specified parameter
CString CAppConfigMngr::GetAppParameter(CString Name, CString Section, AppParameterScope scope, CString DefaultValue)
{
	CString StorageFileName = GetParametersFileName(scope);

	char prms[1000];
	GetPrivateProfileString(Section, Name, "", prms, 999, StorageFileName);
	if(prms[0]=='\0')
		return DefaultValue;

	return prms;
}

// Get specified parameter
int CAppConfigMngr::GetAppParameterInt(CString Name, CString Section, AppParameterScope scope, int DefaultValue)
{
	CString StorageFileName = GetParametersFileName(scope);

	char prms[1000];
	GetPrivateProfileString(Section, Name, "", prms, 999, StorageFileName);
	if (prms[0] == '\0')
		return DefaultValue;
	int ret;

	ret = atoi(prms);

	return ret;
}


CString CAppConfigMngr::GetAppParameterEffectiveScope(CString Name, CString Section, CString DefaultValue)
{
	CString rez="";

	if(m_CurrentUser!="")
	{
		rez = GetAppParameter(Name, Section, apsUser);
		if(rez!="")
			return rez;
	}
	rez = GetAppParameter(Name, Section, apsGlobal);
	if(rez!="")
		return rez;

	return DefaultValue;
}

// Set specified parameter
void CAppConfigMngr::SetAppParameter(CString Name, CString Section, CString Value, AppParameterScope scope)
{
	CString StorageFileName = GetParametersFileName(scope);
	WritePrivateProfileString(Section, Name, Value, StorageFileName);
}

void CAppConfigMngr::SetAppParameterInt(CString Name, CString Section, AppParameterScope scope, int Value) {
	CString StorageFileName = GetParametersFileName(scope);
	CString strValue;
	strValue.Format("%d", Value);
	WritePrivateProfileString(Section, Name, strValue, StorageFileName);
}

// Get parameters storage file name according to the specified scope
CString CAppConfigMngr::GetParametersFileName(AppParameterScope scope)
{
	CString StorageFileName="";

	CString tmpstr="";

	TCHAR buff[MAX_PATH];
	memset(buff, 0, MAX_PATH);
	::GetModuleFileName(NULL, buff, sizeof(buff));
	CString strFolder = buff;
	StorageFileName = strFolder + ".ini";

	DWORD attr = GetFileAttributes(StorageFileName);
	if (attr == INVALID_FILE_ATTRIBUTES || (attr & FILE_ATTRIBUTE_DIRECTORY)) {
		CFile file;

		if (!file.Open(_T(StorageFileName), CFile::modeCreate | CFile::modeWrite, NULL))
		{
			AfxMessageBox(_T("Failed create file"));
			return StorageFileName;
		}
		file.Close();
	}
	

	return StorageFileName;
}
