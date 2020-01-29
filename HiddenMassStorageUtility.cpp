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
	//int argc = 6;
	size_t len = 50;
	/*char** argv = (char**)malloc(sizeof(char*) * argc);
	for (int i = 0; i < argc; i++)
	{
		argv[i] = (char*)malloc(sizeof(char)*len);
	}

	sprintf_s(argv[0], len, "-d");
	sprintf_s(argv[1], len, "\\\\.\\PHYSICALDRIVE1");
	sprintf_s(argv[2], len, "-f");
	sprintf_s(argv[3], len, "mbr.img");
	sprintf_s(argv[4], len, "-m");
	sprintf_s(argv[5], len, "r");*/
	ParseArgs(argc, (char**)argv);
	getchar();
	/*for (int i = 0; i < argc; i++)
	{
		free(argv[i]);
	}
	free(argv);*/

}


std::string ExtractValue(int argc, char** argv, const char* param)
{
	std::string result;
	for (int i = 0; i < argc; i++)
	{
		if (!strcmp(argv[i], param))
		{
			result =  argv[i + 1];
		}
	}
	return result;
}


void ParseArgs(int &argc, char ** argv)
{
	/*cxxopts::Options options("MyProgram", "One line description of MyProgram");
	options.add_options()
		("m,mode", "Work mode:\n Can be \"w\" - Write mbr to MassStorage.\n \"r\" - Read MBR from MassStorage and save it.",
			cxxopts::value<std::string>())
		("f,file", "Specified file name. Use for saving or loading some data", cxxopts::value<std::string>())
		("d,drive", "Physical drive for apply specidied action", cxxopts::value<std::string>())
		;*/

	std::string drive;
	std::string mode;
	std::string file;
	drive = ExtractValue(argc, argv, "-d");
	mode= ExtractValue(argc, argv, "-m");
	file = ExtractValue(argc, argv, "-f");
	if (drive.empty() || mode.empty() || file.empty())
	{
		PrintHelp();
		return;
	}
	RunSpecifiedMode(&mode, &drive, &file);

}

void PrintHelp()
{
	printf("Error parsing argumentss!");
	printf("Usage:");
	printf("-m - Work mode. Can be r,rd, w, wd - read mbr, read data, write mbr, write data. Data modes require -o argument");
	printf("-f - Specified file name. Use for saving or loading some data");
	printf("-o - Offset for reading or writing data to drive");
	printf("-d --drive - Physical drive for apply specidied action");
}



void RunSpecifiedMode(std::string *mode, std::string *drive, std::string *file)
{
	int result;
	if (!strcmp(mode->c_str(), "w"))
	{
		result = WriteMbr(drive->c_str(), file->c_str());
		printf("result is %d\n", result);
	}
	else
	if (!strcmp(mode->c_str(), "r"))
	{
		result = ReadMbr(drive->c_str(), file->c_str());
		printf("result is %d\n", result);
	}
	else
	if (!strcmp(mode->c_str(), "wd"))
	{
		
		;
	}
	else
	if (!strcmp(mode->c_str(), "rd"))
	{
		;
	}
}

