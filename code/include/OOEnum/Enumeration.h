// This is a set of macros designed to make a type-safe enumeration class
// Copyright (c) 2005, James Zachary Howland.  All rights reserved.
//
// This code is free to use in both personal and commercial applications so
// long as the comments in the first 21 lines of this file are unchanged.
// If you make any additions, find any bugs, or wish to make any suggestions
// feel free to email the original author at zachowland@hotmail.com.  If your
// comments lead to further development of this project, I will add your name
// to the credits section below.
///////////////////////////////////////////////////////////////////////////////
// CREDITS:	James Zachary Howland, Original Author
//			David Heath and Zigge, requested const char*->enum feature
//
///////////////////////////////////////////////////////////////////////////////
// NOTE:	For this class to work correctly, each enum constant must be unique
//			If duplicate values are used, it is impossible to obtain the correct
//			string name when using the const char*() operator.
//			A workaround for this is to use the same string names if you use
//			the same value for multiple constant names
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <string.h>							// needed for FindName search

#define BEGIN_ENUM_DEFINITION(theEnumClass) \
	class E##theEnumClass \
	{ \
	public: \
		enum theEnumClass; \
	protected: \
		theEnumClass m_eCurrentValue; \
	public: \
		struct SEnumMap \
		{ \
			theEnumClass eVal; \
			unsigned long eData; \
			const char* eName; \
		}; \
		typedef SEnumMap* Position; \
		typedef SEnumMap* EnumItem; \
	protected: \
		static SEnumMap ms_EnumMap[]; \
	public: \
		E##theEnumClass() \
			{ m_eCurrentValue = (theEnumClass)0; } \
		E##theEnumClass(const E##theEnumClass& eVal) \
			{ *this = eVal; } \
		E##theEnumClass(const int& iVal) \
			{ m_eCurrentValue = (theEnumClass)iVal; } \
		const E##theEnumClass& operator= (const E##theEnumClass& eVal) \
			{ m_eCurrentValue = eVal.m_eCurrentValue; return *this; } \
		const E##theEnumClass& operator= (const int& eVal) \
			{ m_eCurrentValue = (theEnumClass)eVal; return *this; } \
		bool operator==(const E##theEnumClass& eVal) const \
			{ return m_eCurrentValue == eVal.m_eCurrentValue; } \
		bool operator!=(const E##theEnumClass& eVal) const \
			{ return m_eCurrentValue != eVal.m_eCurrentValue; } \
		bool operator< (const E##theEnumClass& eVal) const \
			{ return m_eCurrentValue < eVal.m_eCurrentValue; } \
		bool operator> (const E##theEnumClass& eVal) const \
			{ return m_eCurrentValue > eVal.m_eCurrentValue; } \
		bool operator<=(const E##theEnumClass& eVal) const \
			{ return (*this < eVal || *this == eVal); } \
		bool operator>=(const E##theEnumClass& eVal) const \
			{ return (*this > eVal || *this == eVal); } \
		bool operator==(const int& iVal) const \
			{ return m_eCurrentValue == iVal; } \
		bool operator!=(const int& iVal) const \
			{ return m_eCurrentValue != iVal; } \
		bool operator< (const int& iVal) const \
			{ return m_eCurrentValue < iVal; } \
		bool operator> (const int& iVal) const \
			{ return m_eCurrentValue > iVal; } \
		bool operator<=(const int& iVal) const \
			{ return (*this < iVal || *this == iVal); } \
		bool operator>=(const int& iVal) const \
			{ return (*this > iVal || *this == iVal); } \
		operator int() const \
			{ return (int)m_eCurrentValue; } \
		operator const char*() const \
			{ return GetEnumName(); } \
		const char* GetEnumName() const \
			{ return GetEnumName(*this); } \
		static const char* GetEnumName(const int& iVal) \
			{ return GetEnumName((E##theEnumClass)iVal); } \
		unsigned long GetEnumData() \
			{ return GetEnumData(*this); } \
		static unsigned long GetEnumData(const int& iVal) \
			{ return GetEnumData((E##theEnumClass)iVal); } \
		static bool IsValidEnum(const int& iVal) \
			{ return IsValidEnum((E##theEnumClass)iVal); } \
		bool IsValidEnum() \
			{ return IsValidEnum(*this); } \
		static const char* GetEnumName(const E##theEnumClass& eVal); \
		static unsigned int GetCount(); \
		static unsigned long GetEnumData(const E##theEnumClass& eVal); \
		static EnumItem FindName(const char* name); \
		static bool IsValidEnum(const E##theEnumClass& eVal); \
		static Position GetFirstEnumPosition(); \
		static const EnumItem GetNextEnumPosition(Position& pos); \
		enum theEnumClass \
		{ \

#define DEFINE_ENUM_VALUE(enumName, enumValue) \
			enumName = enumValue,\

#define DEFINE_ENUM(enumName) \
			enumName,\

#define DEFINE_LAST_ENUM(enumName) \
			enumName \

#define END_ENUM_DEFINITION() \
		}; \
	}; \

#define BEGIN_ENUM_IMPLEMENTATION(theEnumClass) \
	E##theEnumClass::SEnumMap E##theEnumClass::ms_EnumMap[] = \
		{ \

#define ENUM_ENTRY(enumValue, enumName) \
			{enumValue, 0L, enumName}, \

#define ENUM_ENTRY_DATA(enumValue, enumName, enumData) \
			{enumValue, enumData, enumName}, \

#define END_ENUM_IMPLEMENTATION(theEnumClass) \
		}; \
	const char* E##theEnumClass::GetEnumName(const E##theEnumClass& eVal) \
	{ \
		Position pos = GetFirstEnumPosition(); \
		while (0 != pos) \
		{ \
			EnumItem pVal = GetNextEnumPosition(pos); \
			if (pVal->eVal == eVal) \
				return pVal->eName; \
		} \
		return 0; \
	} \
	unsigned int E##theEnumClass::GetCount() \
	{ return (unsigned int)(sizeof(ms_EnumMap) / sizeof(ms_EnumMap[0])); } \
	unsigned long E##theEnumClass::GetEnumData(const E##theEnumClass& eVal) \
	{ \
		Position pos = GetFirstEnumPosition(); \
		while (0 != pos) \
		{ \
			EnumItem pVal = GetNextEnumPosition(pos); \
			if (pVal->eVal == eVal) \
				return pVal->eData; \
		} \
		return 0; \
	} \
	E##theEnumClass::EnumItem E##theEnumClass::FindName(const char* name) \
	{ \
		Position pos = GetFirstEnumPosition(); \
		while (0 != pos) \
		{ \
			EnumItem pVal = GetNextEnumPosition(pos); \
			if (0 == strcmp(name, pVal->eName)) \
				return pVal; \
		} \
		return 0; \
	} \
	bool E##theEnumClass::IsValidEnum(const E##theEnumClass& eVal) \
	{ \
		Position pos = GetFirstEnumPosition(); \
		while (0 != pos) \
		{ \
			EnumItem pVal = GetNextEnumPosition(pos); \
			if (pVal->eVal == eVal) \
				return true; \
		} \
		return false; \
	} \
	E##theEnumClass::Position E##theEnumClass::GetFirstEnumPosition() \
	{ \
		return &ms_EnumMap[0]; \
	} \
	const E##theEnumClass::EnumItem E##theEnumClass::GetNextEnumPosition(E##theEnumClass::Position& pos) \
	{ \
		EnumItem ret = pos; \
		if (pos < &ms_EnumMap[GetCount() - 1]) \
			pos++; \
		else \
			pos = 0; \
		return ret; \
	} \
				



