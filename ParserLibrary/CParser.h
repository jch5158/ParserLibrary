#pragma once
class CParser
{
public:

	static CParser *GetInstance()
	{
		static CParser parser;

		return &parser;
	}

	bool LoadFile(const WCHAR* pFileName)
	{
		FILE* fp = nullptr;	

		if (mpFileData != nullptr)
		{
			free(mpFileData);

			clearParser();
		}

		char multiByteFileName[MAX_PATH] = { 0, };
	
		if (WideCharToMultiByte(CP_ACP, 0, pFileName, -1, multiByteFileName, MAX_PATH, NULL, NULL) == 0)
		{
			return false;
		}

		do
		{
			fopen_s(&fp, multiByteFileName, "r+t");
			if (fp == nullptr)
			{
				return false;
			}

			if (fseek(fp, 0, SEEK_END) != 0)
			{
			
				break;
			}

			mFileSize = ftell(fp);

			if (fseek(fp, 0, SEEK_SET) != 0)
			{			
				break;
			}

			mpFileData = (char*)malloc(mFileSize + (long long)1);
			if (mpFileData == nullptr)
			{	
				break;
			}

			ZeroMemory(mpFileData, mFileSize + (long long)1);

			if (fread_s(mpFileData, mFileSize, 1, mFileSize, fp) == 0)
			{			
				break;
			}

			fclose(fp);

			return true;

		} while (0);

		fclose(fp);

		return false;
	}



	bool GetValue(const WCHAR* pTag, int* pValue)
	{
		mOffset = 0;

		char multiByteTag[MAX_PATH] = { 0, };

		if (WideCharToMultiByte(CP_ACP, 0, pTag, -1, multiByteTag, MAX_PATH, NULL, NULL) == 0)
		{
			return false;
		}

		int wordLength = 0;

		char retval[MAX_PATH] = { 0, };

		for (;;)
		{		
			if (getNextWord(retval, &wordLength) == false)
			{
				return false;
			}

			if (strcmp(multiByteTag, retval) == 0)
			{
				if (getNextWord(retval, &wordLength) == false)
				{
					return false;
				}

				if (strcmp("=", retval) == 0)
				{	
					if (getNextWord(retval, &wordLength) == false)
					{
						return false;
					}

					*pValue = atoi(retval);

					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}



	bool GetString(const WCHAR* pTag, WCHAR* pString, int stringLen)
	{
		ZeroMemory(pString, stringLen);

		mOffset = 0;

		char multiByteTag[MAX_PATH] = { 0, };

		if (WideCharToMultiByte(CP_ACP, 0, pTag, -1, multiByteTag, MAX_PATH, NULL, NULL) == 0)
		{
			return false;
		}

		int wordLength = 0;

		char retval[MAX_PATH] = { 0, };

		for (;;)
		{
			if (getNextWord(retval, &wordLength) == false)
			{
				return false;
			}

			if (strcmp(multiByteTag, retval) == 0)
			{
				if (getNextWord(retval, &wordLength) == false)
				{
					return false;
				}

				if (strcmp("=", retval) == 0)
				{
					if (getNextWord(retval, &wordLength) == false)
					{
						return false;
					}

					if (MultiByteToWideChar(CP_ACP, 0, retval, wordLength, pString, stringLen) == 0)
					{
						return false;
					}

					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}




	bool GetNameSpaceValue(const WCHAR* pNamespace, const WCHAR* pTag, int* pValue)
	{
		mOffset = 0;

		int wordLength = 0;

		char multiByteNamespace[MAX_PATH] = { 0, };

		char multiByteTag[MAX_PATH] = { 0, };

		char retval[MAX_PATH] = { 0, };

		multiByteNamespace[0] = ':';

		
		if (WideCharToMultiByte(CP_ACP, 0, pNamespace, -1, &multiByteNamespace[1], MAX_PATH - 1, NULL, NULL) == 0)
		{
			return false;
		}

		if (WideCharToMultiByte(CP_ACP, 0, pTag, -1, multiByteTag, MAX_PATH, NULL, NULL) == 0)
		{
			return false;
		}


		for (;;)
		{
			if (getNextWord(retval, &wordLength) == false)
			{
				return false;
			}

			if (strcmp(multiByteNamespace, retval) == 0)
			{
				if (getNextWord(retval, &wordLength) == false)
				{
					return false;
				}

				if (strcmp(retval, "{") != 0)
				{
					return false;
				}

				for (;;)
				{	
					if (getNextWord(retval, &wordLength) == false)
					{
						return false;
					}
					
					if (strcmp(retval, "}") == 0)
					{
						return false;
					}

					if (strcmp(retval, multiByteTag) == 0)
					{
						if (getNextWord(retval, &wordLength) == false)
						{
							return false;
						}

						if (strcmp(retval, "}") == 0)
						{
							return false;
						}

						if (strcmp(retval,"=") == 0)
						{
							if (getNextWord(retval, &wordLength) == false)
							{
								return false;
							}

							if (strcmp(retval, "}") == 0)
							{
								return false;
							}

							*pValue = atoi(retval);

							return true;
						}
						else
						{
							return false;
						}
					}						
				}
			}
		}
	}



	bool GetNameSpaceString(const WCHAR* pNamespace, const WCHAR* pTag, WCHAR* pString, int stringLen)
	{
		ZeroMemory(pString, stringLen);

		mOffset = 0;

		int wordLength = 0;

		char multiByteNamespace[MAX_PATH] = { 0, };

		char multiByteTag[MAX_PATH] = { 0, };

		char retval[MAX_PATH] = { 0, };

		multiByteNamespace[0] = ':';

		if (WideCharToMultiByte(CP_ACP, 0, pNamespace, -1, &multiByteNamespace[1], MAX_PATH - 1, NULL, NULL) == 0)
		{
			return false;
		}

		if (WideCharToMultiByte(CP_ACP, 0, pTag, -1, multiByteTag, MAX_PATH, NULL, NULL) == 0)
		{
			return false;
		}


		for (;;)
		{
			if (getNextWord(retval, &wordLength) == false)
			{
				return false;
			}

			if (strcmp(multiByteNamespace, retval) == 0)
			{
				if (getNextWord(retval, &wordLength) == false)
				{
					return false;
				}

				if (strcmp(retval, "{") != 0)
				{
					return false;
				}

				for (;;)
				{
					if (getNextWord(retval, &wordLength) == false)
					{
						return false;
					}

					if (strcmp(retval, "}") == 0)
					{
						return false;
					}

					if (strcmp(retval, multiByteTag) == 0)
					{
						if (getNextWord(retval, &wordLength) == false)
						{
							return false;
						}

						if (strcmp(retval, "}") == 0)
						{
							return false;
						}

						if (strcmp(retval, "=") == 0)
						{
							if (getNextWord(retval, &wordLength) == false)
							{
								return false;
							}

							if (strcmp(retval, "}") == 0)
							{
								return false;
							}

							if (MultiByteToWideChar(CP_ACP, 0, retval, wordLength, pString, stringLen) == 0)
							{
								return false;
							}

							return true;
						}
						else
						{
							return false;
						}
					}
				}
			}
		}
	}



private:

	CParser()
		: mFileSize(0)
		, mOffset(0)
		, mpFileData(nullptr)
	{
	}

	~CParser()
	{
	}

	bool IsRemark(void)
	{
		// 주석을 위한 문자 "//" 2BYTE 필요
		if (mOffset >= mFileSize - 1)
		{
			return false;
		}

		if (mpFileData[mOffset] == '/' && mpFileData[mOffset + 1] == '/')
		{

			mOffset += 2;
			
			for (;;)
			{
				if (mOffset >= mFileSize - 1)
				{
					break;
				}
				
				// '\n' 을 만날 때 까지 무시한다.
				if (mpFileData[mOffset] == '\n')
				{
					++mOffset;
					
					return true;
				}
				
				++mOffset;
			}
		}	
		
		return false;
	}

	void skipNoneCommand(void)
	{
		for (;;)
		{
			if (mOffset >= mFileSize - 1)
			{
				break;
			}

			// 0x20 은 스페이스바
			if (mpFileData[mOffset] == '.' || mpFileData[mOffset] == '"' || mpFileData[mOffset] == ',' || mpFileData[mOffset] == 0x20 || mpFileData[mOffset] == '\b'
				|| mpFileData[mOffset] == '\t' || mpFileData[mOffset] == '\n' || mpFileData[mOffset] == '\r')
			{

				++mOffset;
			}
			else
			{
				if (IsRemark() == true)
				{
					continue;
				}

				break;
			}
		}

		return;
	}

	void getWordLength(char* pRetval, int* pWordLength)
	{
		int wordLength = 0;

		char* pFileData = &mpFileData[mOffset];

		for (;;)
		{		
			// 0x20 은 스페이스바
			if (mpFileData[mOffset] == '.' || mpFileData[mOffset] == '"' || mpFileData[mOffset] == ',' || mpFileData[mOffset] == 0x20 || mpFileData[mOffset] == '\b'
				|| mpFileData[mOffset] == '\t' || mpFileData[mOffset] == '\n' || mpFileData[mOffset] == '\r')
			{			

				*pWordLength = wordLength;

				ZeroMemory(pRetval, MAX_PATH);

				memcpy_s(pRetval, MAX_PATH, pFileData, wordLength);

				return;
			}

			++mOffset;
			
			++wordLength;

			if (mOffset >= mFileSize - 1)
			{
				*pWordLength = wordLength;

				ZeroMemory(pRetval, MAX_PATH);

				memcpy_s(pRetval, MAX_PATH, pFileData, wordLength);

				return;
			}
		}
	}

	// 마지막까지 확인했는데 길이가 0이면은 단어 찾기 실패로 return false
	bool getNextWord(char *pRetval,int* pWordLength)
	{

		// 단어의 시작지점까지 찾는다.
		skipNoneCommand();
		
		getWordLength(pRetval, pWordLength);

		if (*pWordLength == 0 && mOffset >= mFileSize - 1)
		{
			return false;
		}
		
		return true;;
	}


	void clearParser(void)
	{
		mFileSize = 0;
		mOffset = 0;
		mpFileData = nullptr;
	}
	
	int mFileSize;

	int mOffset;

	char* mpFileData;
};

