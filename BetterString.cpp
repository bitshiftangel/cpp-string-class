#include "BetterString.h"

void BetterString::IncomeStringLength(const char* String)
{
	Capacity = 0;

	for (size_t i = 0; String[i] != '\0'; i++)
	{
		Capacity++;
	}
}

bool BetterString::IsSafeToSave(const char* String)
{
	if (String == nullptr)
	{
		return false;
	}

	return true;
}

bool BetterString::IsSafeToCopy(const char* String)
{
	if (String == nullptr)
	{
		return false;
	}

	return true;
}

bool BetterString::IsSafeToCopy(const BetterString& Other)
{
	if (this == &Other)
	{
		return false;
	}

	return true;
}

void BetterString::AnnulStack()
{
	Stack[0] = '\0';
	Capacity = 0;
}

void BetterString::AllocateHeapMemory()
{
	Heap.Data = new char[Capacity + 1];
}

bool BetterString::FreeAllocatedMemory()
{
	if (WideString != nullptr)
	{
		delete[] WideString;
		WideString = nullptr;
	}

	if (IsHeap)
	{
		if (Heap.Data != nullptr)
		{
			delete[] Heap.Data;
			Heap.Data = nullptr;
		}
	}

	return true;
}

void BetterString::ReAllocateMemory()
{
	if (FreeAllocatedMemory())
	{
		AllocateHeapMemory();
	}
}

void BetterString::CopyIncomeStringToMemory(const char* String)
{
	char* target = IsHeap ? Heap.Data : Stack;
	for (size_t i = 0; i < Capacity; i++)
	{
		target[i] = String[i];
	}
	target[Capacity] = '\0';
}

void BetterString::ConvertToWString()
{
	WideString = new wchar_t[Capacity + 1];

	char* target = IsHeap ? Heap.Data : Stack;
	for (size_t i = 0; i < Capacity; i++)
	{
		WideString[i] = target[i];
	}
	WideString[Capacity] = L'\0';
}

BetterString::BetterString(const char* String)
{
	if (IsSafeToSave(String))
	{
		IncomeStringLength(String);
		IsHeap = Capacity > MaxStackLength;
		if (IsHeap)
		{
			if (FreeAllocatedMemory())
			{
				AllocateHeapMemory();
			}
		}

		CopyIncomeStringToMemory(String);
	}
	else
	{
		AnnulStack();
	}
}

BetterString::BetterString(const BetterString& Other)
{
	Capacity = Other.Capacity;
	IsHeap = Other.IsHeap;
	WideString = nullptr;
	const char* data = IsHeap ? Other.Heap.Data : Other.Stack;
	if (IsHeap)
	{
		ReAllocateMemory();
	}

	CopyIncomeStringToMemory(data);
}

BetterString& BetterString::operator=(const char* String)
{
	if (IsSafeToCopy(String))
	{
		IncomeStringLength(String);
		IsHeap = Capacity > MaxStackLength;
		if (IsHeap)
		{
			ReAllocateMemory();
		}

		CopyIncomeStringToMemory(String);

		return *this;
	}
	else
	{
		AnnulStack();
		return *this;
	}
}

BetterString& BetterString::operator=(const BetterString& Other)
{
	if (IsSafeToCopy(Other))
	{
		if (IsHeap)
		{
			FreeAllocatedMemory();
		}

		Capacity = Other.Capacity;
		IsHeap = Capacity > MaxStackLength;
		const char* data = Other.IsHeap ? Other.Heap.Data : Other.Stack;
		if (IsHeap)
		{
			AllocateHeapMemory();
		}

		CopyIncomeStringToMemory(data);

		return *this;
	}
	else
	{
		return *this;
	}
}

BetterString::~BetterString()
{
	FreeAllocatedMemory();
}

bool BetterString::IsEmpty() const
{
	if (Capacity == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

size_t BetterString::Length() const
{
	return Capacity;
}

const char* BetterString::ToCString() const
{
	if (IsHeap)
	{
		return Heap.Data;
	}
	else
	{
		return Stack;
	}
}

const wchar_t* BetterString::ToWString()
{
	if (WideString != nullptr)
	{
		delete[] WideString;
	}

	ConvertToWString();

	return WideString;
}

bool BetterString::IsStringInHeap()
{
	return IsHeap;
}
