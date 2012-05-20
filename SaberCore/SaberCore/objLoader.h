/*
    Beginning DirectX 11 Game Programming
    By Allen Sherrod and Wendy Jones

    ObjModel - Used to represent an OBJ model.
*/


#ifndef _OBJ_LOADER_H_
#define _OBJ_LOADER_H_


/// ~¡£~
class TokenStream
{
public:
	TokenStream( );

	void ResetStream( );

	void SetTokenStream( char* data );
	bool GetNextToken( std::string* buffer, char* delimiters, int totalDelimiters );
	bool MoveToNextLine( std::string *buffer );

private:
	int startIndex_, endIndex_;
	std::string data_;
};

/// ~¡£~
class ObjModel
{
   public:
      ObjModel( );      
      ~ObjModel( );

      void Release( );
      bool LoadOBJ( char *fileName );

      float *GetVertices()   { return vertices_; }
      float *GetNormals()    { return normals_; }
      float *GetTexCoords()  { return texCoords_; }
      int    GetTotalVerts() { return totalVerts_; }

   private:
      float *vertices_;
      float *normals_;
      float *texCoords_;
      int totalVerts_;
};

#endif