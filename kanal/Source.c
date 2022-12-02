#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>

int main()
{
	system("chcp 1251 > null");
	while (TRUE)
	{
		HANDLE hNamePipe; //объявление дескриптора канала
		LPSTR lpstPipeName = L"\\\\.\\pipe\\MyPipe"; // переменная, содержащая имя канала
		hNamePipe = CreateNamedPipe( // создание канала
			lpstPipeName, // имя канала
			PIPE_ACCESS_DUPLEX, // режм доступа к каналу
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
			PIPE_UNLIMITED_INSTANCES,
			512,
			512,
			INFINITE,
			NULL
		);

		BOOL Connected = ConnectNamedPipe(hNamePipe, NULL);
		if (Connected)
		{
			printf("\nКлиент успешно подключен\n");
			DWORD size_buffer = 100;
			LPWSTR buffer = (CHAR*)calloc(size_buffer, sizeof(CHAR));

			DWORD actual_readen;
			BOOL SuccessRead = ReadFile(hNamePipe, buffer, size_buffer, &actual_readen, NULL);
			if (!SuccessRead)
			{

			}

		}


		
	}
	return 0;
}