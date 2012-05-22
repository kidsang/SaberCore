#ifndef scCommon_h__
#define scCommon_h__

/**
 * �ļ���scCommon
 * ���ڣ�2012/05/22
 * ���ߣ�kid
 */

/// ���ļ�������һЩͨ�õĶ�������ݽṹ

#include <string>
#include <map>

/// ������������ļ�ֵ���б�
typedef std::map<std::string, std::string> scNameValuePairList;

/// ���ַ���ת��������
int inline scConvertToInt(const std::string& str)
{
	return atoi(str.c_str());
}

/// ���ַ���ת���ɸ�����
float inline scConvertToFloat(const std::string& str)
{
	return (float)atof(str.c_str());
}

#endif // scCommon_h__
