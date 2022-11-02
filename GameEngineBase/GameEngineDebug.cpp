#include "PreCompile.h"
#include "GameEngineDebug.h"

namespace GameEngineDebug
{
	HANDLE hConsole_ = nullptr;

	void LeakCheckOn()
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		//_CrtSetBreakAlloc(3311);
	}

	void ConsoleOpen()
	{
		if (AllocConsole())
		{
			FILE* file;
			freopen_s(&file, "CONIN$", "rb", stdin);
			freopen_s(&file, "CONOUT$", "wb", stdout);
			freopen_s(&file, "CONOUT$", "wb", stderr);

			hConsole_ = GetStdHandle(STD_OUTPUT_HANDLE);
			std::cout << "Console Start." << std::endl;
		}
	}

	void OutputString(const std::string& _text)
	{
		OutputDebugStringA((_text + "\n").c_str());
	}

	void Destroy()
	{
		if (nullptr != hConsole_)
		{
			FreeConsole();
			hConsole_ = nullptr;
		}
	}

	void GetLastErrorPrint()
	{
		DWORD error = GetLastError();
		char* errorMessage = nullptr;

		FormatMessageA(
			FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
			nullptr,
			error,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(char*)&errorMessage,
			0,
			nullptr
		);

		if (nullptr != errorMessage)
		{
			std::string errorText = "ErrorCode: ";
			errorText += std::to_string(error);
			errorText += " ErrorMessage: ";
			errorText += errorMessage;

			MessageBoxA(
				nullptr,
				errorText.c_str(),
				"Error!",
				MB_OK
			);

			LocalFree(errorMessage);
		}
	}
}

