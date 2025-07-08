#ifndef BETTERSTRING_H
#define BETTERSTRING_H

class BetterString
{
private:
	size_t Capacity = 0;
	bool IsHeap = false;
	union
	{
		struct
		{
			char* Data = nullptr;
		} Heap;

		char Stack[sizeof(Heap) * 2];
	};
	size_t MaxStackLength = sizeof(Heap) * 2 - 1;
	wchar_t* WideString = nullptr;

	void IncomeStringLength(const char* String);
	bool IsSafeToSave(const char* String);
	bool IsSafeToCopy(const char* String);
	bool IsSafeToCopy(const BetterString& Other);
	void AnnulStack();
	void AllocateHeapMemory();
	bool FreeAllocatedMemory();
	void ReAllocateMemory();
	void CopyIncomeStringToMemory(const char* String);
	void ConvertToWString();
public:
	BetterString(const char* String);
	BetterString(const BetterString& Other);
	BetterString& operator=(const char* String);
	BetterString& operator=(const BetterString& Other);
	~BetterString();

	bool IsEmpty() const;
	size_t Length() const;
	const char* ToCString() const;
	const wchar_t* ToWString();
	bool IsStringInHeap();
};
#endif // !BETTERSTRING_H
