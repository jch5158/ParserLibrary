#pragma once
class CParser
{
public:

	static CParser *GetInstance()
	{
		static CParser parser;

		return &parser;
	}

	bool LoadFile(const char* fileName)
	{
		FILE* fp = nullptr;	

		if (mpFileData != nullptr)
		{
			free(mpFileData);

			clearParser();
		}

		do
		{
			fopen_s(&fp, fileName, "r+t");
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

			mpFileData = (char*)malloc(mFileSize + (int)1);
			if (mpFileData == nullptr)
			{	
				break;
			}

			ZeroMemory(mpFileData, mFileSize + (int)1);

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

	bool GetValue(char* pTag, int* pValue)
	{
		int wordLength = 0;

		char retval[MAX_PATH];

		for (;;)
		{
			getNextWord(retval, &wordLength);
			

			if (0 == strcmp(pTag, retval))
			{
				getNextWord(retval, &wordLength);

				if (0 == strcmp(retval, "="))
				{	
					getNextWord(retval, &wordLength);

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

private:

	CParser()
		: mFileSize(0)
		, mOffsetCount(0)
		, mpFileData(nullptr)
	{
	}

	~CParser()
	{
	}

	void skipNoneCommand(void)
	{
		for (;;)
		{
			if (mOffsetCount >= mFileSize - 1)
			{
				break;
			}

			if (*mpFileData == '.' || *mpFileData == '"' || *mpFileData == ',' || *mpFileData == 0x20 || *mpFileData == 0x08
				|| *mpFileData == 0x09 || *mpFileData == 0x0a || *mpFileData == 0x0d)
			{

				++mOffsetCount;
				++mpFileData;
			}
			else
			{
				break;
			}
		}

		return;
	}

	void getWordLength(char* pRetval, int* pWordLength)
	{
		int wordLength = 0;

		char* pFileData = mpFileData;

		for (;;)
		{		
			if (*mpFileData == '.' || *mpFileData == '"' || *mpFileData == ',' || *mpFileData == 0x20 || *mpFileData == 0x08
				|| *mpFileData == 0x09 || *mpFileData == 0x0a || *mpFileData == 0x0d)
			{			

				*pWordLength = wordLength;

				ZeroMemory(pRetval, MAX_PATH);

				memcpy_s(pRetval, wordLength, pFileData, wordLength);

				return;
			}

			++mOffsetCount;

			++mpFileData;

			++wordLength;

			if (mOffsetCount >= mFileSize - 1)
			{	
				*pWordLength = wordLength;

				ZeroMemory(pRetval, MAX_PATH);

				memcpy_s(pRetval, wordLength, pFileData, wordLength);

				return;
			}
		}
	}

	void getNextWord(char *pRetval,int* pWordLength)
	{
		skipNoneCommand();

		getWordLength(pRetval,pWordLength);

		return;
	}


	void clearParser(void)
	{
		mFileSize = 0;
		mOffsetCount = 0;
		mpFileData = nullptr;
	}
	
	int mFileSize;

	int mOffsetCount;

	char* mpFileData;
};

