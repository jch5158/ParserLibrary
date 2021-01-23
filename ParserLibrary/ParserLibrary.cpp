#include "stdafx.h"


int wmain()
{
	if (CParser::GetInstance()->LoadFile("hello.txt") == true)
	{
		printf_s("good\n");
	}

	int retval = 0;

	if (CParser::GetInstance()->GetValue((char*)"hello", &retval) == false)
	{
		printf_s("실패\n");
	}

	printf_s("%d\n", retval);

	if (CParser::GetInstance()->GetValue((char*)"set", &retval) == false)
	{
		printf_s("실패\n");
	}

	printf_s("%d\n", retval);


	if (CParser::GetInstance()->GetValue((char*)"name", &retval) == false)
	{
		printf_s("실패\n");
	}

	printf_s("%d\n", retval);

}
