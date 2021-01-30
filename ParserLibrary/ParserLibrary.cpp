
#include "CParser.h"

struct stDissession
{
	DWORD messageType;
	UINT64 sessionID;
};

stDissession disArray[53] = { 0, };

UINT64 releaseArray[51] = { 0, };

UINT64 inDisArray[50] = { 0, };

int wmain()
{
	WCHAR buffer[MAX_PATH] = { 0, };
	
	CParser parser;

	if (parser.LoadFile(L"DisconnectSessionList.txt") == false)
	{
		wprintf_s(L"Failed\n");
		return 1;
	}

	for (int index = 0; index < _countof(disArray); ++index)
	{
		ZeroMemory(buffer, MAX_PATH * sizeof(WCHAR));

		swprintf_s(buffer, L"messageType[%d]", index);

		if (parser.GetValue((const WCHAR*)buffer, (int*)&disArray[index].messageType) == false)
		{
			wprintf_s(L"Failed1\n");
			return 1;
		}

		ZeroMemory(buffer, MAX_PATH * sizeof(WCHAR));

		swprintf_s(buffer, L"sessionID[%d]", index);

		if (parser.GetValue((const WCHAR*)buffer, (long long*)&disArray[index].sessionID) == false)
		{
			wprintf_s(L"Failed2\n");
			return 1;
		}
	}

	if (parser.LoadFile(L"InDisconnectSessionList.txt") == false)
	{
		wprintf_s(L"Failed\n");
		return 1;
	}

	for (int index = 0; index < _countof(inDisArray); ++index)
	{
		ZeroMemory(buffer, MAX_PATH * sizeof(WCHAR));

		swprintf_s(buffer, L"[%d]", index);

		if (parser.GetValue((const WCHAR*)buffer, (long long*)&inDisArray[index]) == false)
		{
			wprintf_s(L"Failed3\n");
			return 1;
		}
	}

	if (parser.LoadFile(L"ReleaseSessionList.txt") == false)
	{
		wprintf_s(L"Failed\n");
		return 1;
	}

	for (int index = 0; index < _countof(releaseArray); ++index)
	{
		ZeroMemory(buffer, MAX_PATH * sizeof(WCHAR));

		swprintf_s(buffer, L"[%d]", index);

		if (parser.GetValue((const WCHAR*)buffer, (long long*)&releaseArray[index]) == false)
		{
			wprintf_s(L"Failed4\n");
			return 1;
		}
	}

	for (int index = 0; index < _countof(releaseArray); ++index)
	{
		for (int compareIndex = 0; compareIndex < _countof(releaseArray); ++compareIndex)
		{
			if (index != compareIndex)
			{
				if (releaseArray[index] == releaseArray[compareIndex])
				{
					wprintf_s(L"Overlapped\n");
				}
			}
		}
	}

	for (int index = 0; index < _countof(inDisArray); ++index)
	{
		for (int compareIndex = 0; compareIndex < _countof(inDisArray); ++compareIndex)
		{
			if (index != compareIndex)
			{
				if (inDisArray[index] == inDisArray[compareIndex])
				{
					wprintf_s(L"Overlapped\n");
				}
			}
		}
	}

	int overapCount = 0;

	for (int index = 0; index < _countof(inDisArray); ++index)
	{
		for (int compareIndex = 0; compareIndex < _countof(disArray); ++compareIndex)
		{
			if (inDisArray[index] == disArray[compareIndex].sessionID)
			{
				overapCount++;
			}
		}

		if (overapCount == 0)
		{
			wprintf_s(L"Dis Overlapped\n");
		}

		overapCount = 0;
	}

	overapCount = 0;

	for (int index = 0; index < _countof(disArray); ++index)
	{
		for (int compareIndex = 0; compareIndex < _countof(inDisArray); ++compareIndex)
		{
			if (disArray[index].sessionID == inDisArray[compareIndex])
			{
				overapCount++;
			}
		}

		if (overapCount == 0)
		{
			wprintf_s(L"In Dis Overpped\n");
		}

		overapCount = 0;
	}


	overapCount = 0;


	for (int index = 0; index < _countof(releaseArray); ++index)
	{
		for (int compareIndex = 0; compareIndex < _countof(disArray); ++compareIndex)
		{
			if (releaseArray[index] == disArray[compareIndex].sessionID)
			{
				++overapCount;		
			}
		}

		if (overapCount == 0)
		{
			wprintf_s(L"None Release Dis Overpaed : %lld\n", releaseArray[index]);
		}

		overapCount = 0; 
	}


	overapCount = 0;

	for (int index = 0; index < _countof(disArray); ++index)
	{
		for (int compareIndex = 0; compareIndex < _countof(releaseArray); ++compareIndex)
		{
			if (disArray[index].sessionID == releaseArray[compareIndex])
			{
				overapCount++;
			}
		}

		if (overapCount == 0)
		{
			wprintf_s(L"None Dis Release Overapped : %lld\n", disArray[index].sessionID);
		}

		overapCount = 0;
	}

	overapCount = 0;


	for (int index = 0; index < _countof(releaseArray); ++index)
	{
		for (int compareIndex = 0; compareIndex < _countof(inDisArray); ++compareIndex)
		{
			if (releaseArray[index] == inDisArray[compareIndex])
			{
				++overapCount;
			}
		}

		if (overapCount == 0)
		{
			wprintf_s(L"None Release InDis Overpaed : %lld\n", releaseArray[index]);
		}

		overapCount = 0;
	}


	overapCount = 0;

	for (int index = 0; index < _countof(inDisArray); ++index)
	{
		for (int compareIndex = 0; compareIndex < _countof(releaseArray); ++compareIndex)
		{
			if (inDisArray[index] == releaseArray[compareIndex])
			{
				overapCount++;
			}
		}

		if (overapCount == 0)
		{
			wprintf_s(L"None InDis Release Overapped : %lld\n", inDisArray[index]);
		}

		overapCount = 0;
	}


}
