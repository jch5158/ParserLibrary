#include "stdafx.h"


int wmain()
{

	CParser::GetInstance()->LoadFile(L"hello.txt");

	int retval = 0;

	
	WCHAR str[MAX_PATH] = { 1, };

	if (CParser::GetInstance()->GetNameSpaceString(L"HI", L"hello", str, MAX_PATH) == false)
	{
		wprintf_s(L"failed\n");
	}
	
	wprintf_s(L"%s\n", str);

}
