#pragma once



namespace GameEngineDebug
{
	void LeakCheckOn();
	void ConsoleOpen();
	void OutputString(const std::string& _text);
	void Destroy();
	void GetLastErrorPrint();
};

#define MsgBox(text) MessageBeep(0);	\
MessageBoxA(nullptr, text, "Error!", MB_OK);

#define MsgBoxAssert(text)	MessageBeep(0);	\
MessageBoxA(nullptr, text, "Error!", MB_OK);	\
assert(false);

#define MsgBoxAssertString(text) MessageBeep(0);	\
MessageBoxA(nullptr, (text).c_str(), "Error!", MB_OK);	\
assert(false);