#pragma once
#include <Windows.h>
#include <iostream>

class Memory
{
private:
	DWORD id = 0;
	HANDLE hProc {};

public:
	Memory(const char* name);

	DWORD getProcessId()
	{
		return this->id;
	}

	HANDLE getProcessHandle()
	{
		return this->hProc;
	}

	uintptr_t getModuleAddress(const char* name);

	template <typename T>
	T Read(uintptr_t address)
	{
		T value{};
		ReadProcessMemory(this->hProc, (LPVOID)address, &value, sizeof(T), 0);
		return value;
	}

	template <typename T>
	bool Write(uintptr_t address, T value)
	{
		return WriteProcessMemory(this->hProc, (LPVOID)address, &value, sizeof(T), 0);
	}

	~Memory();
};