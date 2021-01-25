#include "stdafx.h"
#include "CParser.h"


int wmain()
{
	CParser parser;
	
	if (parser.LoadFile(L"Config\\hello.ini") == false)
	{
		return false;
	}

	int retval = 0;
	
	WCHAR str[MAX_PATH] = { 1, };

	if (parser.GetNamespaceString(L"NO1", L"hello", str, MAX_PATH) == false)
	{
		wprintf_s(L"failed\n");
	}
	
	wprintf_s(L"%s\n", str);


	if (parser.GetNamespaceString(L"HI", L"hello", str, MAX_PATH) == false)
	{
		wprintf_s(L"failed\n");
	}

	wprintf_s(L"%s\n", str);


}
