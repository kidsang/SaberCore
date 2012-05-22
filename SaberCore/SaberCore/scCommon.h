#ifndef scCommon_h__
#define scCommon_h__

/**
 * 文件：scCommon
 * 日期：2012/05/22
 * 作者：kid
 */

/// 该文件包含了一些通用的定义和数据结构

#include <string>
#include <map>

/// 用来传输参数的键值对列表
typedef std::map<std::string, std::string> scNameValuePairList;

/// 将字符串转换成整型
int inline scConvertToInt(const std::string& str)
{
	return atoi(str.c_str());
}

/// 将字符串转换成浮点型
float inline scConvertToFloat(const std::string& str)
{
	return (float)atof(str.c_str());
}

#endif // scCommon_h__
