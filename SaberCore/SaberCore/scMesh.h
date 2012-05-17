#ifndef scMesh_h__
#define scMesh_h__

#include <string>

class scMesh
{
private:
	std::string mName;
	unsigned int mVertexCount;
	unsigned int mIndexCount;

public:
	scMesh(void);
	~scMesh(void);

	const std::string GetName()
	{
		return mName;
	}
};


#endif // scMesh_h__
