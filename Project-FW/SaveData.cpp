#include "SaveData.h"
#include <fstream>
#include <Windows.h>

SaveData::SaveData() : m_nChapterProgress(1), m_nStageProgress(1), m_nTutorialProgress(0),
					   m_bExtra(false)
{
	
	for(int i=0; i<9; i++)
		m_cExtraProgress[i] = 0 ;
}
SaveData::~SaveData()
{
}

void SaveData::Save()
{
	std::ofstream ofs("Resource/Data/.sav", std::ios::binary) ;
	ofs.write((char*)this, sizeof(SaveData)) ;
	ofs.close() ;
}

void SaveData::Load()
{
	std::ifstream ifs("Resource/Data/.sav", std::ios::binary) ;
	if(ifs.fail())
		return ;
	ifs.read((char*)this, sizeof(SaveData)) ;
	ifs.close() ;
}

void SaveData::Reset()
{
	remove("Resource/Data/.sav") ;

	HANDLE h_token;
	TOKEN_PRIVILEGES privilege_info;

	// 현재 프로세스의 권한과 관련된 정보를 변경하기 위해 토큰정보를 엽니다.
	if(!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES |
											  TOKEN_QUERY, &h_token))
	{
		// 권한과 관련된 정보 접근에 실패함..
		return ;
	}

	// 현재 프로세스가 SE_SHUTDOWN_NAME 권한을 사용할수 있도록 설정한다.
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &privilege_info.Privileges[0].Luid);
	privilege_info.PrivilegeCount = 1;
	privilege_info.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	// 지정한 값으로 권한을 조정한다.
	AdjustTokenPrivileges(h_token, FALSE, &privilege_info, 0, (PTOKEN_PRIVILEGES)NULL, 0);
	if(GetLastError() != ERROR_SUCCESS)
	{
		// 권한 조정에 실패한 경우...
		return ;
	}

	ExitWindowsEx(EWX_REBOOT | EWX_FORCE, 0) ;
}