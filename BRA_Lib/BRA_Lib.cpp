#include <iostream>
#include <iostream>
#include <ctime>
#include <math.h>
#include <string>
#include <Windows.h>
#include <time.h>
#include <cstring>
#include <stdlib.h>
#include <string.h>

extern "C" {

	unsigned long _stdcall _compare(char* str1, char* str2) {
		if (str1 == NULL || str2 == NULL || strlen(str1) != strlen(str2))
			return (unsigned long)3;
		else
		{
			for (size_t i = 0; i < strlen(str1); i++)
			{
				if (str1[i] > str2[i])
					return 1;
				else if (str1[i] < str2[i])
					return 2;
			}
			return 0;
		}
	}

	unsigned long _stdcall _strln(char* str) {
		if (str == NULL)
		{
			std::cout << std::endl;
			return 0;
		}
		unsigned long z = strlen(str);
		return z;
	}

	void _stdcall _outInt(long value)
	{
		std::cout << value << std::endl;
		return;
	}
	void _stdcall _out(char* ptr)
	{
		setlocale(0, "");
		if (ptr == NULL)
		{
			std::cout << " !!  null  !!" << std::endl;
			return;
		}
		std::cout << ptr << std::endl;
		return;
	}
	
	char* __stdcall _strcopy(char* str1, char* str2)
	{

		if (!str1 || !str2)
		{
			/*std::cout << "ERROR: Null string pointer in copystr function!!!" << std::endl;*/
			system("pause");
			ExitProcess(0);
		}
		else
		{
			str1 = str2;
			return (char*)str2;
		}

	}

	char* _stdcall _strcon(char* str1, char* str2)
	{
		if (strlen(str1) + strlen(str2) > 254) {
			std::cout << "Ошибка. Длинна результатирующей строки превышает 255 символов";
			ExitProcess(0);
		}
		char* buf = (char*)malloc(strlen(str1) + strlen(str2));
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		if (!str1 || !str2)
		{
			std::cout << "ERROR: Null string in strcon function!!!" << std::endl;
			system("pause");
			ExitProcess(0);
		}
		int size = 0;
		for (; str2[size] != '\0'; size++)
			buf[size] = str2[size];
		for (int i = 0; str1[i] != '\0'; size++, i++)
			buf[size] = str1[i];
		buf[size] = '\0';
		return  buf;
	}
}