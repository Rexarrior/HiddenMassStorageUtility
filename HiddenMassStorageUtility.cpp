// HiddenMassStorageUtility.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include "cxxopts.hpp"
#include "HiddenMassStorageUtility.h"
#include "MbrTools.h"
#include "string.h"

int main(int argc, char** argv)
{
	/* argc = 10;
	size_t len = 50;
	argv = (char**)malloc(sizeof(char*) * argc);
	for (int i = 0; i < argc; i++)
	{
		argv[i] = (char*)malloc(sizeof(char)*len);
	}

	sprintf_s(argv[0], len, "-d");
	sprintf_s(argv[1], len, "\\\\.\\PHYSICALDRIVE1");
	sprintf_s(argv[2], len, "-f");
	sprintf_s(argv[3], len, "mbr.img");
	sprintf_s(argv[4], len, "-m");
	sprintf_s(argv[5], len, "wd");
	sprintf_s(argv[6], len, "-b");
	sprintf_s(argv[7], len, "512");
	sprintf_s(argv[8], len, "-o");
	sprintf_s(argv[9], len, "0");*/
	ParseArgs(argc, (char**)argv);
	/*for (int i = 0; i < argc; i++)
	{
		free(argv[i]);
	}
	free(argv);*/

}


std::string ExtractValue(int argc, char** argv, const char* param, bool* isFinded)
{
	std::string result;
	*isFinded = FALSE;
	for (int i = 0; i < argc; i++)
	{
		if (!strcmp(argv[i], param))
		{
			result =  argv[i + 1];
			*isFinded = TRUE;
			return result;
		}
	}
	return result;
}


void ParseArgs(int &argc, char ** argv)
{
	

	bool isFinded;
	std::string drive;
	std::string mode;
	std::string file;
	std::string offset_s;
	std::string bytes_s;
	long long offset = -1;
	int64_t bytes = -1;
	drive = ExtractValue(argc, argv, "-d", &isFinded);
	mode= ExtractValue(argc, argv, "-m", &isFinded);
	file = ExtractValue(argc, argv, "-f", &isFinded);
	offset_s = ExtractValue(argc, argv, "-o", &isFinded);
	if (isFinded)
	{
		offset = _strtoi64(offset_s.c_str(), NULL, 0);
	}
	bytes_s = ExtractValue(argc, argv, "-b", &isFinded);
	if (isFinded)
	{
		bytes = _strtoi64(bytes_s.c_str(), NULL, 0);
	}
	if (drive.empty() || mode.empty() || file.empty())
	{
		PrintHelp();
		return;
	}
	RunSpecifiedMode(&mode, &drive, &file, offset, bytes);

}

void PrintHelp()
{
	printf("Error parsing argumentss!");
	printf("Usage:");
	printf("-m - Work mode. Can be r,rd, w, wd - read mbr, read data, write mbr, write data. Data modes require -o argument");
	printf("-f - Specified file name. Use for saving or loading some data");
	printf("-o - Offset for reading or writing data to drive");
	printf("-d --drive - Physical drive for apply specidied action");
	printf("-b --bytes - Bytes to read. To use with rd mode");
}



void RunSpecifiedMode(std::string *mode, std::string *drive, std::string *file, long long& offset, long long& bytes)
{
	int result;
	if (!strcmp(mode->c_str(), "w"))
	{
		result = WriteMbr(drive->c_str(), file->c_str());
	}
	else
	if (!strcmp(mode->c_str(), "r"))
	{
		result = ReadMbr(drive->c_str(), file->c_str());
	}
	else
	if (!strcmp(mode->c_str(), "wd"))
	{
		if (offset == -1)
		{
			printf("ERROR! For wd mode offset (-o) must be specidied");
			return;
		}
		result = WriteDataArea(drive->c_str(), file->c_str(), offset);
	}
	else
	if (!strcmp(mode->c_str(), "rd"))
	{
		if (offset == -1)
		{
			printf("ERROR! For rd mode offset (-o) must be specidied");
			return;
		}
		if (bytes == -1)
		{
			printf("ERROR! For rd mode bytes (-b) must be specidied");
			return;
		}
		result = ReadDataArea(drive->c_str(), file->c_str(), offset, bytes);
	}
	else
	{
		result = -1000;
	}
	printf("result is %d\n", result);

}

