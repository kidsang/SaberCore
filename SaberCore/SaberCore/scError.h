#ifndef scError_h__
#define scError_h__

/**
 * �ļ���scError
 * ���ڣ�2012/05/20
 * ���ߣ�kid
 */

#include <iostream>
#include <string>

/// �رչ���fopen�ľ���
#pragma warning(disable: 4996)

/// ���������Ϣ
inline void scErrMsg(std::string msg)
{
	std::cerr << msg << std::endl;
}

/// ���������Ϣ
inline void scErrMsg(char* msg)
{
	std::cerr << msg << std::endl;
}

#endif // scError_h__
