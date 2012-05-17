#ifndef scArchiveLoader_h__
#define scArchiveLoader_h__

#include "scError.h"
#include <vector>
#include <stdio.h>

// ���ļ��ж�ȡ��Դ��·����Ϣ
// �ļ���ʽ����
// [group]
// path:name
class scArchiveLoader
{
	// ��
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
	EntryList mEntryList;

	bool Load(const std::string& filepath)
	{
		std::string group = "default";
		mEntryList.clear();

		FILE* file = fopen(filepath.c_str(), "r");
		if (!file)
		{
			scErrMsg("Can not open file: " + filepath);
			return false;
		}

		std::string s;
		char buf[256];

		while(fgets(buf, sizeof(buf), file))
		{
			s = std::string(buf);
			int len = s.size();
			if (s.empty())
				continue;
			
			// ��֪���������д�úܳ�
			// �����Ҳ���Ϊ��ʹ��������ʽ������boost��

			// ��[]��ס��������Ϣ
			if (s.find("[") != -1)
			{
				if (s.find("]") != -1)
				{
					// �趨��ǰ��
					int beg = s.find("[") + 1;
					int end = s.find("]");
					group =  s.substr(beg, end - beg); 
				}
			}
			else if (s.find(":") != -1)
			{
				// path:name
				int pivot = s.find(':');
				std::string path = s.substr(0, pivot);
				std::string name = s.substr(pivot + 1, s.size() - pivot - 2);//ȥ�����з�
				mEntryList.push_back(Entry(name, path, group));
			}
		}

		fclose(file);
	}
};

#endif // scArchiveLoader_h__

