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
			PIPE_ACCESS_DUPLEX, // режм доступа к каналу (односторонний/двусторонний)
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, // режим работы канала: передавать сообщения| читать собщения | ждать
			PIPE_UNLIMITED_INSTANCES, // количест во водящих соединений в каналу, в данном случае неогр.
			512, // объем буфера для чтения (байт)
			512,// объем буфера для записи (байт)
			INFINITE, // максимальное время ожидания сообщения
			NULL // указатель на структуру безопасности
		);

		BOOL Connected = ConnectNamedPipe(hNamePipe, NULL); // установка с оединения клиента с каналом
		if (Connected) // если клиент подключился
		{
			printf("\nКлиент успешно подключен\n");
			DWORD size_buffer = 100; // размер буфера для чтения 
			LPWSTR buffer = (CHAR*)calloc(size_buffer, sizeof(CHAR)); // строковая перменная, в которую будут считаны даные

			DWORD actual_readen; // сколько на самом деле было прочитано байт
			BOOL SuccessRead = ReadFile(hNamePipe, buffer, size_buffer, &actual_readen, NULL);
			if (!SuccessRead)
			{
				printf("\nКлиент отключился от сервера\n");
			}
			printf(buffer); // вывод на экран прочитанного сообщения
			CloseHandle(hNamePipe); // закрываем канал

		}

	}
}