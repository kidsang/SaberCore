#ifndef scArchiveLoader_h__
#define scArchiveLoader_h__

/**
 * 文件：scArchiveLoader
 * 日期：2012/05/20
 * 作者：kid
 */

#include "scError.h"
#include <vector>
#include <stdio.h>

/// 从文件中读取资源的路径信息
/// 文件格式如下
/// [group]
/// path:name
class scArchiveLoader
{
	/// 项
	/// 从配置文件中读入的条目
	/// 其中包含了资源名，资源路径和资源分组
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
	/// 读取到的条目列表
	EntryList mEntryList;

	/// 从指定路径读取资源的路径条目
	/// @param filepath 配置文件所在路径
	/// @return 读取是否成功
	bool Load(const std::string& filepath);
};

#endif // scArchiveLoader_h__

