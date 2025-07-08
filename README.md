# About

Its a compact, pure C++ string class without using the standard library,  
designed for convenient WinAPI usage and optimized memory handling. 
*It was created for my project, and I will add functionality if necessary.*

## Features

- ✅ Small string optimization (stores short strings on the stack)  
- ✅ Dynamic allocation for longer strings  
- ✅ Conversion to wide strings (`wchar_t*`) for WinAPI functions  
- ✅ Full manual memory management, no STL dependencies  

## Example Usage

```cpp
#include <iostream>
#include "BetterString.h"
#include <string>
#include <Windows.h>
int main()
{
	BetterString ex1 = "First example";
	std::cout << ex1.ToCString() << std::endl;
	
	bool isEx1Empty = ex1.IsEmpty();
	std::cout << "Is first example empty: " << isEx1Empty << std::endl;
	size_t ex1Length = ex1.Length();
	std::cout << "First example length: " << ex1Length << std::endl;
	bool isEx1InHeap = ex1.IsStringInHeap();
	std::cout << "Is first example in heap: " << isEx1Empty << std::endl;
	std::string ex1String = ex1.ToCString();
	std::cout << "std::string: " << ex1String << std::endl;
	std::wstring ex1WString = ex1.ToWString();
	std::wcout << "std::wstring: " << ex1WString << std::endl;

	BetterString ex2 = "Second example for showcase heap allocation when variable has many letters";
	std::cout << ex2.ToCString() << std::endl;

	bool isEx2InHeap = ex2.IsStringInHeap();
	std::cout << "Is second example in heap: " << isEx2InHeap << std::endl;

	ex1 = ex2;
	std::cout << "Copy ex2 to ex1: " << ex1.ToCString() << std::endl;
	std::cout << "Is ex1 in heap: " << ex1.IsStringInHeap() << std::endl;
	
	BetterString winTitle = "Title test";
	BetterString winText = "Winapi";
	MessageBoxW(nullptr, winText.ToWString(), winTitle.ToWString(), S_OK);

	return 0;
}
