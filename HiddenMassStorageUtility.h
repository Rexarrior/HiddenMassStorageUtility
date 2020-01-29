#pragma once

void ParseArgs(int &argc, char ** argv);

void PrintHelp();

void RunSpecifiedMode(std::string *mode, std::string *drive, std::string *file);

std::string ExtractValue(int argc, char** argv, const char* param);
