#ifndef scError_h__
#define scError_h__

/**
 * 文件：scError
 * 日期：2012/05/20
 * 作者：kid
 */

#include <iostream>
#include <string>

/// 关闭关于fopen的警告
#pragma warning(disable: 4996)

/// 输出错误信息
inline void scErrMsg(std::string msg)
{
	std::cerr << msg << std::endl;
}

/// 输出错误信息
inline void scErrMsg(char* msg)
{
	std::cerr << msg << std::endl;
}

#endif // scError_h__
