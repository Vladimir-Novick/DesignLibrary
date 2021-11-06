#pragma once

// AppConfigMngr.h
// Management of application parameters, global/global user/project/project user

//////////////////////////////////////////////////////////////////////
#if !defined(AFX_AppConfigMngr_H__6A8F1950_11E8_4EEF_A430_C36A79B5C4E5__INCLUDED_)
#define AFX_AppConfigMngr_H__6A8F1950_11E8_4EEF_A430_C36A79B5C4E5__INCLUDED_

//////////////////////////////////////////////////////////////////////

// Application parameters scope enum:
enum AppParameterScope
  {
	apsGlobal = 0,		// all users 
	apsUser = 1,		// per user 
  };

// Application parameter data structure
struct AppParam
{
	CString Section;
	CString Name;
	CString Value;
	CString Description;
	AppParameterScope Scope;
};

class CAppConfigMngr
{
 public:
	// members
	CString m_CurrentOpenDrive;
	CString m_CurrentOpenProject;
	CString m_CurrentUser;

	// constructor
	CAppConfigMngr(CString CurrentOpenDrive, CString CurrentOpenProject, CString CurrentUser);
	CAppConfigMngr();

	// generic methods
	CString GetAppParameter(CString Name, CString Section, AppParameterScope scope, CString DefaultValue="");
	int GetAppParameterInt(CString Name, CString Section, AppParameterScope scope, int DefaultValue );
	void SetAppParameterInt(CString Name, CString Section, AppParameterScope scope, int Value);


	CString	GetAppParameterEffectiveScope(CString Name, CString Section, CString DefaultValue="");
	void	SetAppParameter(CString Name, CString Section, CString Value, AppParameterScope scope);
	CString GetParametersFileName(AppParameterScope scope);

	// specific report params management

};

////////////////////////////////////////////////////////
#endif // !defined(AFX_AppConfigMngr_H__6A8F1950_11E8_4EEF_A430_C36A79B5C4E5__INCLUDED_)

