#include "memory.h"
#include <iostream>
#include <thread>

namespace offsets
{
	// client offsets
	constexpr ::std::ptrdiff_t dwLocalPlayer = 0xDEA98C;
	constexpr ::std::ptrdiff_t dwForceJump = 0x52BBCD8;

	// player offsets
	constexpr ::std::ptrdiff_t m_iHealth = 0x100;
	constexpr ::std::ptrdiff_t m_fFlags = 0x104;
};

int main()
{
	Memory mem{ "csgo.exe" };
	std::cout << "[+] Process ID -> " << mem.getProcessId() << '\n';

	const auto client = mem.getModuleAddress("client.dll");

	std::cout << "[+] Client Dll -> 0x" << std::hex << client << std::dec << '\n';

	while (true)
	{
		if (!GetAsyncKeyState(VK_SPACE)) 
			continue;

		const auto localPlayer = mem.Read<uintptr_t>(client + offsets::dwLocalPlayer);

		if (!localPlayer) 
			continue;

		const auto hp = mem.Read<int32_t>(localPlayer + offsets::m_iHealth);

		if (!hp) continue;

		const auto flags = mem.Read<int32_t>(localPlayer + offsets::m_fFlags);

		(flags & (1 << 0)) ?
			mem.Write<int32_t>(client + offsets::dwForceJump, 6) // force the local player to jump
			: mem.Write<int32_t>(client + offsets::dwForceJump, 4); // reset

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}