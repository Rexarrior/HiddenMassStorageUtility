#pragma once

void ParseArgs(int &argc, char ** argv);

void PrintHelp();


std::string ExtractValue(int argc, char** argv, const char* param, bool* isFinded);
void RunSpecifiedMode(std::string *mode, std::string *drive, std::string *file, long long& offset, long long& bytes);
