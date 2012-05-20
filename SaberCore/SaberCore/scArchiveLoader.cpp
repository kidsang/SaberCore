#include "scArchiveLoader.h"


bool scArchiveLoader::Load( const std::string& filepath )
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

		// 我知道下面这段写得很丑
		// 但是我不想为了使用正则表达式而导入boost库

		// 以[]框住的是组信息
		if (s.find("#") != -1)
		{
			// 注释行
			continue;
		}
		else if (s.find("[") != -1)
		{
			if (s.find("]") != -1)
			{
				// 设定当前组
				int beg = s.find("[") + 1;
				int end = s.find("]");
				group =  s.substr(beg, end - beg); 
			}
		}
		else if (s.find(":") != -1)
		{
			// path:name
			int pivot = s.find(':');
			int end = s.find('\n');
			if (end >= 0)
				end -= 1;
			std::string path = s.substr(0, pivot);
			std::string name = s.substr(pivot + 1, end - pivot);//去除换行符
			mEntryList.push_back(Entry(name, path, group));
		}
	}

	fclose(file);
	return true;
}
