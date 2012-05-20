#ifndef scArchiveLoader_h__
#define scArchiveLoader_h__

/**
 * �ļ���scArchiveLoader
 * ���ڣ�2012/05/20
 * ���ߣ�kid
 */

#include "scError.h"
#include <vector>
#include <stdio.h>

/// ���ļ��ж�ȡ��Դ��·����Ϣ
/// �ļ���ʽ����
/// [group]
/// path:name
class scArchiveLoader
{
	/// ��
	/// �������ļ��ж������Ŀ
	/// ���а�������Դ������Դ·������Դ����
	struct Entry
	{
		std::string name;
		std::string path;
		std::string group;

		Entry(std::string n, std::string p, std::string g)
			: name(n), path(p), group(g)
		{

		}
	};

	typedef std::vector<Entry> EntryList;

public:
	/// ��ȡ������Ŀ�б�
	EntryList mEntryList;

	/// ��ָ��·����ȡ��Դ��·����Ŀ
	/// @param filepath �����ļ�����·��
	/// @return ��ȡ�Ƿ�ɹ�
	bool Load(const std::string& filepath);
};

#endif // scArchiveLoader_h__

