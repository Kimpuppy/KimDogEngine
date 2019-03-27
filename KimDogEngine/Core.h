#pragma once

//------------------------------[Window]
#define WINDOW_WIDTH	1920
#define WINDOW_HEIGHT	1080

//------------------------------[Release/Delete]
#define SAFE_RELEASE(p) \
if (p != nullptr) { p->Release(); p = nullptr; }
#define SAFE_DELETE(p) \
if (p != nullptr) { delete p; p = nullptr; }
#define SAFE_RELEASE_DELETE(p) \
if (p != nullptr) { p->Release(); delete p; p = nullptr; }

//------------------------------[GetSet]
#define GET(Type, MemberName, FaceName) \
private: \
	Type MemberName; \
public: \
	inline Type Get##FaceName() const { return MemberName; } \

#define SET(Type, MemberName, FaceName) \
private: \
	Type MemberName; \
public: \
	inline void Set##FaceName(Type value) { MemberName = value; } \

#define GETSET(Type, MemberName, FaceName) \
private: \
	Type MemberName; \
public: \
	inline Type Get##FaceName() const { return MemberName; } \
	inline void Set##FaceName(Type value) { MemberName = value; } \

//------------------------------[Random]
#define RANDOMIZE() srand((unsigned int)time(NULL))

inline int RandomRange(int min, int max)
{
	return min + rand() % (max + 1 - min);
}

//------------------------------[TypeCheck]
template <typename Type1, typename Type2>
struct is_same
{
	const bool value = false;
};
template <typename Type1>
struct is_same<Type1, Type1>
{
	const bool value = true;
};

template <typename Type, typename VarType>
bool IsSameType(VarType var)
{
	bool isSame = std::is_same<Type, VarType>::value;

	return isSame;
}

template <typename Type1, typename Type2>
bool IsSameType(Type1 var1, Type2 var2)
{
	bool isSame = std::is_same<Type1, Type2>::value;

	return isSame;
}