// MbrTools.cpp : Определяет экспортированные функции для приложения DLL.
//

#include "pch.h"
#include "MbrTools.h"

typedef unsigned char byte;

#define INVALID_DISK_OR_PRIVILEGES_REQUIRED -1
#define BINARY_FILE_NOT_FOUNT -2
#define INVALID_BINARY_FILE -3
#define ERROR_READING_BINARY_FILE -4
#define ERROR_READING_MBR -6
#define CANT_OVERRIDE_1ST_SECTOR -5
#define ERROR_WRITING_BINARY_FILE -7
#define IS_MBR_OVERRIDEN(res) res > 0


#define MBR_SIZE_BYTES 512



using namespace std::string_literals;


std::wstring s2ws(const std::string& s);


//-1 Invalid disk handle or administrator privileges required
//-2 Can't find the binary file to read from
//-3 Invalid binary file
//-4 Error reading from binary file
//-5 Can't override 1st sector!
//>=0 number of bytes writed
int WriteMbr(const char* device, const char* path)
{
	//DWORD result = 0;
	//DWORD dw;
	//HANDLE drive = CreateFileA(device, GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
	//if (drive != INVALID_HANDLE_VALUE) {
	//	HANDLE binary = CreateFileA(path, GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
	//	if (binary != INVALID_HANDLE_VALUE) {
	//		DWORD size = GetFileSize(binary, 0);
	//		if (size > 0) {
	//			byte *mbr = new byte[size];
	//			if (ReadFile(binary, mbr, size, &dw, 0)) {
	//				if (WriteFile(drive, mbr, size, &dw, 0))
	//				{
	//					result = dw;
	//				}
	//				else
	//					result = CANT_OVERRIDE_1ST_SECTOR;
	//			}
	//			else
	//				result = ERROR_READING_BINARY_FILE;
	//		}
	//		else
	//			result = INVALID_BINARY_FILE;
	//	}
	//	else {
	//		result = BINARY_FILE_NOT_FOUNT;
	//	}
	//	CloseHandle(binary);
	//}
	//else
	//	result = INVALID_DISK_OR_PRIVILEGES_REQUIRED;
	//CloseHandle(drive);

	int result = WriteDataArea(device, path, 0);
	return result;

}



//-1 Invalid disk handle or administrator privileges required
//-2 Can't find the binary to write to
//-6 Can't read mbr
//-7 Error writing to binary file
//>=0 number of bytes writed
int ReadMbr(const char* device, const char* path)
{
	/*printf("device %s  \n pathToBin %s\n", device, path);
	DWORD result = 0;
	DWORD dw;
	HANDLE drive = CreateFileA(device, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
	if (drive != INVALID_HANDLE_VALUE) {
		HANDLE binary = CreateFileA(path, GENERIC_WRITE, 0, 0, CREATE_NEW, 0, 0);
		if (binary != INVALID_HANDLE_VALUE) {
			DWORD size = MBR_SIZE_BYTES;
			byte *mbr = new byte[size];
			if (ReadFile(drive, mbr, size, &dw, 0)) {
				if (WriteFile(binary, mbr, size, &dw, 0))
				{
					result = dw;
				}
				else
					result = ERROR_WRITING_BINARY_FILE;

			}
			else
				result = ERROR_READING_MBR;
		}
		else {
			result = BINARY_FILE_NOT_FOUNT;
		}
		CloseHandle(binary);
	}
	else
		result = INVALID_DISK_OR_PRIVILEGES_REQUIRED;
	CloseHandle(drive);*/

	int result = ReadDataArea(device, path, 0, 512);
	return result;

}



int ReadDataArea(const char* device, const char* path, const long long offset, const int64_t bytes)
{
	DWORD result = 0;
	DWORD dw;
	HANDLE drive = CreateFileA(device, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
	if (drive != INVALID_HANDLE_VALUE) {
		HANDLE binary = CreateFileA(path, GENERIC_WRITE, 0, 0, CREATE_NEW, 0, 0);
		if (binary != INVALID_HANDLE_VALUE) {
			DWORD size = bytes;
			byte *mbr = new byte[size];
			long low = (long)offset;
			long hight = NULL;
			//long hight = (long)(offset >> sizeof(long));
			SetFilePointer(drive, low, &hight, FILE_BEGIN);
			if (ReadFile(drive, mbr, size, &dw, 0)) {
				if (WriteFile(binary, mbr, size, &dw, 0))
				{
					result = dw;
				}
				else
					result = ERROR_WRITING_BINARY_FILE;

			}
			else
			{
				result = ERROR_READING_MBR;
				DWORD res = GetLastError();
				printf("Last error is %d\n", res);
			}
		}
		else {
			result = BINARY_FILE_NOT_FOUNT;
		}
		CloseHandle(binary);
	}
	else
		result = INVALID_DISK_OR_PRIVILEGES_REQUIRED;
	CloseHandle(drive);
	return result;
}



int WriteDataArea(const char* device, const char* path, const long long offset)
{
	DWORD result = 0;
	DWORD dw;
	HANDLE drive = CreateFileA(device, GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
	if (drive != INVALID_HANDLE_VALUE) {
		HANDLE binary = CreateFileA(path, GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
		if (binary != INVALID_HANDLE_VALUE) {
			DWORD size = GetFileSize(binary, 0);
			long low = (long)offset;
			long hight = NULL;
			//long hight = (long)(offset >> sizeof(long));
			DWORD res = SetFilePointer(drive, low, &hight, FILE_BEGIN);
			if (size > 0) {
				byte *mbr = new byte[size];
				if (ReadFile(binary, mbr, size, &dw, 0)) {
					if (WriteFile(drive, mbr, size, &dw, 0))
					{
						result = dw;
					}
					else
					{
						result = CANT_OVERRIDE_1ST_SECTOR;
						res = GetLastError();
						printf("Last error is %d\n", res);
					}
				}
				else
					result = ERROR_READING_BINARY_FILE;
			}
			else
				result = INVALID_BINARY_FILE;
		}
		else {
			result = BINARY_FILE_NOT_FOUNT;
		}
		CloseHandle(binary);
	}
	else
		result = INVALID_DISK_OR_PRIVILEGES_REQUIRED;
	CloseHandle(drive);
	return result;
}