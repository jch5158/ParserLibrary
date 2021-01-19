#include "stdafx.h"


int wmain()
{
	if (CParser::GetInstance()->LoadFile("hello.txt") == true)
	{
		printf_s("good\n");
	}

	int retval = 0;

	if (CParser::GetInstance()->GetValue((char*)"hello_world", &retval) == false)
	{
		printf_s("실패\n");
	}

	printf_s("%d\n", retval);

	if (CParser::GetInstance()->GetValue((char*)"No", &retval) == false)
	{
		printf_s("실패\n");
	}

	printf_s("%d\n", retval);


	if (CParser::GetInstance()->GetValue((char*)"Set", &retval) == false)
	{
		printf_s("실패\n");
	}

	printf_s("%d\n", retval);

}
