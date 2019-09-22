#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <windows.h>
#include <string.h>
#include <sys/stat.h>
#include <tchar.h>
#include <cstdlib>
#include <filesystem>


using namespace std;



// проверка на наличие запрещённого символа
bool IsIncorrectSymbol(TCHAR* fileName, char symbol = '~')
{
	bool del = false;
	for ( ; *fileName && !del; fileName++)
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
		(LPTSTR)& errorText,  // output (вывод)
		0, // minimum size for output buffer (минимальный размер выходного буфера )
		NULL);

	if (NULL != errorText)
	{
		MessageBox(NULL, errorText, NULL, 0);

		LocalFree(errorText);
		errorText = NULL;
	}
}


void Charmix() 
{
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

}


void Enchantix(TCHAR deWay[4095])
{
	setlocale(LC_ALL, "");

	TCHAR mainWay[4095];


	_tcscpy(mainWay, deWay);
	_tcscat(mainWay, TEXT("*"));

	WIN32_FIND_DATA MyFile;
	HANDLE hFind = FindFirstFile(_T(mainWay), &MyFile);

	TCHAR fileName[4095];

	bool allCorrect = true;
	bool findNext;


	// проверка найден ли файл
	if (INVALID_HANDLE_VALUE != hFind)
	{
		
			do // основная часть алгоритма
			{
				_tcscpy(fileName, MyFile.cFileName);

				//cout << deWay << fileName << endl;

				
				if ((MyFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0 && (MyFile.dwFileAttributes & FILE_ATTRIBUTE_DEVICE) == 0) // проверка на Regular File
				{
					// проверка файла на удаление
					if (!MyFile.nFileSizeHigh && !MyFile.nFileSizeLow && IsIncorrectSymbol(fileName))
					{
						TCHAR way[4095];

						cout << " - - - - - - - - - - - - -" << endl;
						cout << deWay << MyFile.cFileName << endl;
						cout << " - - - - - - - - - - - - -" << endl;

						_tcscpy(way, deWay);
						if (!_tcscat(way, MyFile.cFileName))
						{
							allCorrect = false;
							ShowError();
						}

						// назание файла | Размер файла
						//cout << MyFile.cFileName << " c==||:::::::> " << MyFile.nFileSizeHigh << " c==||:::::::> " << MyFile.nFileSizeLow << " | " << endl;

						cout << "[==> " <<way << "<==]" << endl;

						if (DeleteFile(way) != 0) // удаление 
						{
							wcout << "Deleting Sucess!" << endl; // вывод сообщения успешном удалении
						}
						else
						{
							allCorrect = false;
							ShowError();
						}

					}
				}
				else if (((MyFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0) && (_tcscmp(fileName, TEXT("."))) > 0 && (_tcscmp(fileName, TEXT(".."))) > 0)
				{
					TCHAR deWayCopy[4095];

					_tcscpy(deWayCopy, deWay);
					
					if (!_tcscat(deWayCopy, fileName) || !_tcscat(deWayCopy, "\\"))
					{
						ShowError();
					}

					cout << deWayCopy<< endl;
								
					Enchantix(deWayCopy);
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
	{
		
		//ShowError();
	}


	FindClose(hFind);

}



int main()
{
	//Charmix();

	TCHAR deWay[4095] = "D:\\TestFolder\\";

	Enchantix(deWay);
	

	return 0;
}

