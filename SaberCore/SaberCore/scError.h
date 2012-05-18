#ifndef scError_h__
#define scError_h__

#include <iostream>
#include <string>

// 关闭关于fopen的警告
#pragma warning(disable: 4996)

inline void scErrMsg(std::string msg)
{
	std::cerr << msg << std::endl;
}

inline void scErrMsg(char* msg)
{
	std::cerr << msg << std::endl;
}

#endif // scError_h__
