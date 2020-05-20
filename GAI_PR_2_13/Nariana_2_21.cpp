#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#define THREADS_NUMBER 10
#define ITERATIONS_NUMBER 100
#define PAUSE 10 /* ms */
#include <fstream>
#include <iostream>
#include <windows.h>
#include <string.h>
#include <sys/stat.h>
#include <tchar.h>
#include <cstdlib>
#include <filesystem>
#include <thread>
#include<list>
using namespace std;


void PractanFour()
{
	/*
	setlocale(LC_ALL, "");

	WIN32_FIND_DATA MyFile;
	HANDLE hFind = FindFirstFile(_T("D:\\TestFolder\\*"), &MyFile);

	TCHAR fileName[4095];

	bool allCorrect = true;
	bool findNext;


	// проверка найден ли файл
	if (INVALID_HANDLE_VALUE != hFind )
	{

			do // основная часть алгоритма
			{
				_tcscpy(fileName, MyFile.cFileName);

				if (((MyFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) && ((MyFile.dwFileAttributes & FILE_ATTRIBUTE_DEVICE) == 0)) // проверка на Regular File
				{
					// проверка файла на удаление
					if (!MyFile.nFileSizeHigh && !MyFile.nFileSizeLow && IsIncorrectSymbol(fileName))
					{
						TCHAR way[4095] = TEXT("D:\\TestFolder\\");

						if (!_tcscat(way, MyFile.cFileName))
						{
							allCorrect = false;
							ShowError();
						}

						// назание файла | Размер файла
						cout << MyFile.cFileName << " c==||:::::::> " << MyFile.nFileSizeHigh << " c==||:::::::> " << MyFile.nFileSizeLow << " | " << endl;



						if (DeleteFile(way) != 0) // удаление
						{
							cout << "Deleting Sucess!" << endl; // вывод сообщения успешном удалении
						}
						else
						{
							allCorrect = false;
							ShowError();
						}

					}
				}

					findNext = FindNextFile(hFind, &MyFile);

					if (!GetLastError() == ERROR_NO_MORE_FILES)
					{
						allCorrect = false;
						ShowError();
					}


			} while (NULL != findNext && allCorrect);


	}
	else
		ShowError();


	FindClose(hFind);
	*/
}


// Структура — элемент списка
struct Item {
	HANDLE info;
	Item* next;
};

struct ListHandle {
	Item* tail;
	Item* head;
};

// список процессов
ListHandle myList;
//int iii = 0;

// Добавить поток в список
void AddItem(ListHandle& list, HANDLE* h) {
	Item* thrd = new Item();
	thrd->info = h;
	thrd->next = NULL;

	if (list.head == NULL) {
		list.head = thrd;
	}
	else {
		list.tail->next = thrd;
	}

	list.tail = thrd;

	//iii++;
}

bool AllDirScaned(ListHandle& list) {
	bool allEnded = true;
	Item* myHead = list.head;
	int i = 0;
	while (myHead != NULL && allEnded) {

		if (myHead->info != NULL) {
			DWORD res = WaitForSingleObject(myHead->info, INFINITE);
			allEnded = res == WAIT_OBJECT_0;

		}

		i++;
		//cout << " -> " << i;

		myHead = myHead->next;

		list.head->next;
	}
	cout << endl;
	//list.head = myHead;

	return allEnded;
}





// проверка на наличие запрещённого символа
bool IsIncorrectSymbol(TCHAR* fileName, char symbol = '~')
{
	bool del = false;
	for (; *fileName && !del; fileName++)
	{
		if (*fileName == symbol) del = true;
	}

	return del;
}

void ShowError()
{
	LPTSTR errorText = NULL;
	DWORD errCode = GetLastError();

	FormatMessage(
		// use system message tables to retrieve error text (используем системные таблицы для получения текста ошибки)
		FORMAT_MESSAGE_FROM_SYSTEM
		// allocate buffer on local heap for error text (выделить буфер в локальной куче для текста ошибки)
		| FORMAT_MESSAGE_ALLOCATE_BUFFER
		// Important! will fail otherwise, since we're not (Важно! в противном случае произойдет сбой, поскольку мы не передаем)
		// (and CANNOT) pass insertion parameters ( (и не можем) передать параметры вставки)
		| FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,    // не используется с FORMAT_MESSAGE_FROM_SYSTEM
		errCode, // код ошибки
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // язык ошибки
		(LPTSTR)&errorText,  // output (вывод)
		0, // minimum size for output buffer (минимальный размер выходного буфера )
		NULL);

	if (NULL != errorText)
	{
		MessageBox(NULL, errorText, NULL, 0);

		LocalFree(errorText);
		errorText = NULL;
	}
}

void PractanFiveTwo(TCHAR input[4095]);

DWORD WINAPI newThread(LPVOID lpParameter) {
	TCHAR* way = (TCHAR*)lpParameter;
	PractanFiveTwo(way);
	return 0;
}

// Мой практан 2_13
//void PractanFiveTwo(TCHAR folderWay[4095])
//{
//	setlocale(LC_ALL, "");
//
//	TCHAR mainWay[4095];
//
//	_tcscpy(mainWay, folderWay);
//	_tcscat(mainWay, TEXT("*"));
//
//	WIN32_FIND_DATA MyFile;
//	HANDLE hFind = FindFirstFile(_T(mainWay), &MyFile);
//
//	TCHAR fileName[4095];
//
//	bool allCorrect = true;
//	bool findNext;
//
//	HANDLE h = NULL;
//
//	// проверка найден ли файл
//	if (INVALID_HANDLE_VALUE != hFind)
//	{
//		do // основная часть алгоритма
//		{
//			_tcscpy(fileName, MyFile.cFileName);
//
//			if ((MyFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0 
//				 && (MyFile.dwFileAttributes & FILE_ATTRIBUTE_DEVICE) == 0) // проверка на Regular File
//			{
//				// проверка файла на удаление
//				if (!MyFile.nFileSizeHigh && !MyFile.nFileSizeLow && IsIncorrectSymbol(fileName))
//				{
//					TCHAR fullWay[4095];
//
//					_tcscpy(fullWay, folderWay);
//					if (!_tcscat(fullWay, MyFile.cFileName))
//					{
//						allCorrect = false;
//						ShowError();
//					}
//
//					cout << "way--> " << fullWay << " -- \n";
//					cout << "deWay--> " << folderWay << " -- \n";
//					cout << "fileName--> " << fileName << " -- \n";
//
//					if (/*DeleteFile(way)*/fullWay != 0) // удаление 
//					{
//						cout << "Deleting Sucess!" << endl; // вывод сообщения успешном удалении
//					}
//					else
//					{
//						cout << "Deleting ERROR! " << endl;
//						allCorrect = false;
//						ShowError();
//					}
//
//				}
//			}
//			else if (((MyFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0) && (_tcscmp(fileName, TEXT("."))) > 0 && (_tcscmp(fileName, TEXT(".."))) > 0)
//			{
//				TCHAR deWayCopy[4095];
//
//				_tcscpy(deWayCopy, folderWay);
//
//				if (!_tcscat(deWayCopy, fileName) || !_tcscat(deWayCopy, "\\"))
//				{
//					ShowError();
//				}
//
//				cout << deWayCopy << endl;
//
//				h = CreateThread(NULL, 0, newThread, deWayCopy, 0, NULL); // создать поток
//				// ---------------------------сюда добавляем в список новый поток--------------------
//				AddItem(myList, &h);
//
//				//cout << iii << endl;
//
//
//				if (h == NULL)
//				{
//					ShowError();
//				}
//
//
//			}
//
//
//			findNext = FindNextFile(hFind, &MyFile);
//
//			if (!GetLastError() == ERROR_NO_MORE_FILES)
//			{
//				allCorrect = false;
//				ShowError();
//			}
//
//		} while (NULL != findNext && allCorrect);
//
//		// -----------------------------сюда проверку, что все потоки завершены-----------------------
//		if (h != NULL)
//		{
//			DWORD res = WaitForSingleObject(h, INFINITE);
//			if (res != WAIT_OBJECT_0)
//				_tprintf(_T("ERROR in wait\n"));
//
//			if (AllDirScaned(myList))
//				CloseHandle(h);
//		}
//	}
//	else
//	{
//		ShowError();
//	}
//
//	FindClose(hFind);
//
//}

void PractanFiveTwo(TCHAR folderWay[4095])
{
	setlocale(LC_ALL, "");

	TCHAR mainWay[4095];

	_tcscpy(mainWay, folderWay);
	_tcscat(mainWay, TEXT("*"));

	WIN32_FIND_DATA MyFile;
	HANDLE hFind = FindFirstFile(_T(mainWay), &MyFile);

	TCHAR fileName[4095];

	bool allCorrect = true;
	bool findNext;

	//HANDLE h = NULL;

	// проверка найден ли файл
	if (INVALID_HANDLE_VALUE != hFind)
	{
		do // основная часть алгоритма
		{
			_tcscpy(fileName, MyFile.cFileName);

			if ((MyFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0
				&& (MyFile.dwFileAttributes & FILE_ATTRIBUTE_DEVICE) == 0) // проверка на Regular File
			{
				// проверка файла на удаление
				if (!MyFile.nFileSizeHigh && !MyFile.nFileSizeLow && IsIncorrectSymbol(fileName))
				{
					TCHAR fullWay[4095];

					_tcscpy(fullWay, folderWay);
					if (!_tcscat(fullWay, MyFile.cFileName))
					{
						allCorrect = false;
						ShowError();
					}

					cout << "way--> " << fullWay << " -- \n";
					cout << "deWay--> " << folderWay << " -- \n";
					cout << "fileName--> " << fileName << " -- \n";

					if (/*DeleteFile(way)*/fullWay != 0) // удаление 
					{
						cout << "Deleting Sucess!" << endl; // вывод сообщения успешном удалении
					}
					else
					{
						cout << "Deleting ERROR! " << endl;
						allCorrect = false;
						ShowError();
					}

				}
			}
			else if (((MyFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0) && (_tcscmp(fileName, TEXT("."))) > 0 && (_tcscmp(fileName, TEXT(".."))) > 0)
			{
				TCHAR deWayCopy[4095];

				_tcscpy(deWayCopy, folderWay);

				if (!_tcscat(deWayCopy, fileName) || !_tcscat(deWayCopy, "\\"))
				{
					ShowError();
				}

				cout << deWayCopy << endl;

				// raz
				//h = CreateThread(NULL, 0, newThread, deWayCopy, 0, NULL); // создать поток
				//// ---------------------------сюда добавляем в список новый поток--------------------
				//AddItem(myList, &h);

				//cout << iii << endl;

				// raz
				/*if (h == NULL)
				{
					ShowError();
				}*/


			}

			findNext = FindNextFile(hFind, &MyFile);

			if (!GetLastError() == ERROR_NO_MORE_FILES)
			{
				allCorrect = false;
				ShowError();
			}

		} while (NULL != findNext && allCorrect);

		//raz
		// -----------------------------сюда проверку, что все потоки завершены-----------------------
		/*if (h != NULL)
		{
			DWORD res = WaitForSingleObject(h, INFINITE);
			if (res != WAIT_OBJECT_0)
				_tprintf(_T("ERROR in wait\n"));

			if (AllDirScaned(myList))
				CloseHandle(h);
		}*/
	}
	else
	{
		ShowError();
	}

	FindClose(hFind);

}



int main()
{
	myList.head = NULL;
	myList.tail = NULL;


	TCHAR way[4095] = "D:\\TestFolder\\";

	PractanFiveTwo(way);

}