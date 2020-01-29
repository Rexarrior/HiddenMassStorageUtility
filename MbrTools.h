#pragma once

#include "pch.h"


int ReadMbr(const char* device, const char* path);
int WriteMbr(const char* device, const char* path);
int ReadDataArea(const char* device, const char* path, const long long offset, const int64_t bytes);
int WriteDataArea(const char* device, const char* path, const long long offset);
