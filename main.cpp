
    // Your First C++ Program

#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <utility>
#include <cstdlib>
#include <vector>


std::string ToHex(const std::string& s, bool upper_case = true)
{
    std::ostringstream ret;

    for (std::string::size_type i = 0; i < s.length(); ++i)
        ret << std::hex << std::setfill('0') << std::setw(2) << (upper_case ? std::uppercase : std::nouppercase) << (int)s[i];

    return ret.str();
}

std::string my(const std::vector<uint8_t>& data)
{
    return std::accumulate(std::next(data.begin()), data.end(),
                                std::string{(char)data.at(0)}, // start with first element
                                [](std::string a, uint8_t b)
                                {
                                    return std::move(a) + (char)b;
                                });
}
int FromHex(const std::string &s) { return strtoul(s.c_str(), nullptr, 16); }

int main() {
    std::vector<uint8_t> code = {
		0x48, 0x83, 0xC4, 0x48,					  // add rsp, 0x48; Stack unwind
		0x48, 0x31, 0xC9,						  // xor rcx, rcx; hWnd
		0x48, 0xC7, 0xC2, 0x10, 0x20, 0x40, 0x00, // mov rdx, Message(0x402010) (offset 10)
		0x49, 0xC7, 0xC0, 0x00, 0x20, 0x40, 0x00, // mov r8, Title(0x402000) (offset 17)
		0x4D, 0x31, 0xC9,						  // xor r9, r9; MB_OK
		0x48, 0xC7, 0xC0, 0x5C, 0x30, 0x40, 0x00, // mov rax, MessageBoxA address(0x40305c) (offset 27)
		0xFF, 0x10,								  // call[rax]; MessageBoxA(hWnd, Message, Title, MB_OK)
		// 0x48, 0x31, 0xC9,				// xor rcx, rcx; exit value
		// 0x48, 0xC7, 0xC0,       0x6C, 0x30, 0x40, 0x00,	// mov rax, ExitProcess address (0x40306c)
		// 0xFF, 0x10,					// call[rax]; ExitProcess(0)
		0xC3 // ret; Never reached
	};

    std::vector<uint8_t> data = {
		0x43, 0x6F, 0x6E, 0x73, 0x6F, 0x6C, 0x65, 0x20, 0x4D, 0x65, 0x73, 0x73, 0x61, 0x67, 0x65, 0x20, 0x36, 0x34, 0x0D, 0x0A
	};

    std::cout << my(data);


    std::string mystr = "hihihi";
    std::cout << ToHex(mystr);

    data[10] = 0x43;

    std::cout << my(data);

    return 0;
}
