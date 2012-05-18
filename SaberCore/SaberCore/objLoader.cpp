/*
    Beginning DirectX 11 Game Programming
    By Allen Sherrod and Wendy Jones

    ObjModel - Used to represent an OBJ model.
*/


#include<fstream>
#include<vector>
#include<string>
#include"objLoader.h"

//////////////////////////////////////////////////////////////////////////

bool isValidIdentifier( char c )
{
	// Ascii from ! to ~.
	if( ( int )c > 32 && ( int )c < 127 )
		return true;

	return false;
}


bool isValidIdentifier( char c, char* delimiters, int totalDelimiters )
{
	if( delimiters == 0 || totalDelimiters == 0 )
		return isValidIdentifier( c );

	for( int i = 0; i < totalDelimiters; i++ )
	{
		if( c == delimiters[i] )
			return false;
	}

	return true;
}


TokenStream::TokenStream( )
{
	ResetStream( );
}


void TokenStream::ResetStream( )
{
	startIndex_ = endIndex_ = 0;
}


void TokenStream::SetTokenStream( char *data )
{
	ResetStream( );
	data_ = data;
}


bool TokenStream::GetNextToken( std::string* buffer, char* delimiters, int totalDelimiters )
{
	startIndex_ = endIndex_;

	bool inString = false;
	int length = ( int )data_.length( );

	if( startIndex_ >= length - 1 )
		return false;

	while( startIndex_ < length && isValidIdentifier( data_[startIndex_],
		delimiters, totalDelimiters ) == false )
	{
		startIndex_++;
	}

	endIndex_ = startIndex_ + 1;

	if( data_[startIndex_] == '"' )
		inString = !inString;

	if( startIndex_ < length )
	{
		while( endIndex_ < length && ( isValidIdentifier( data_[endIndex_], delimiters,
			totalDelimiters ) || inString == true ) )
		{
			if( data_[endIndex_] == '"' )
				inString = !inString;

			endIndex_++;
		}

		if( buffer != NULL )
		{
			int size = ( endIndex_ - startIndex_ );
			int index = startIndex_;

			buffer->reserve( size + 1 );
			buffer->clear( );

			for( int i = 0; i < size; i++ )
			{
				buffer->push_back( data_[index++] );
			}
		}

		return true;
	}

	return false;
}


bool TokenStream::MoveToNextLine( std::string* buffer )
{
	int length = ( int )data_.length( );

	if( startIndex_ < length && endIndex_ < length )
	{
		endIndex_ = startIndex_;

		while( endIndex_ < length && ( isValidIdentifier( data_[endIndex_] ) ||
			data_[endIndex_] == ' ' ) )
		{
			endIndex_++;
		}

		if( ( endIndex_ - startIndex_ ) == 0 )
			return false;

		if( endIndex_ - startIndex_ >= length )
			return false;

		if( buffer != NULL )
		{
			int size = ( endIndex_ - startIndex_ );
			int index = startIndex_;

			buffer->reserve( size + 1 );
			buffer->clear( );

			for( int i = 0; i < size; i++ )
			{
				buffer->push_back( data_[index++] );
			}
		}
	}
	else
	{
		return false;
	}

	endIndex_++;
	startIndex_ = endIndex_ + 1;

	return true;
}


//////////////////////////////////////////////////////////////////////////

ObjModel::ObjModel( )
{
    vertices_ = 0;
    normals_ = 0;
    texCoords_ = 0;
    totalVerts_ = 0;
}

      
ObjModel::~ObjModel( )
{
    Release( );
}


void ObjModel::Release( )
{
    totalVerts_ = 0;

    if( vertices_ != 0 ) delete[] vertices_;
    if( normals_ != 0 ) delete[] normals_;
    if( texCoords_ != 0 ) delete[] texCoords_;

    vertices_ = 0;
    normals_ = 0;
    texCoords_ = 0;
}


bool ObjModel::LoadOBJ( char *fileName )
{
    std::ifstream fileStream;
    int fileSize = 0;

    fileStream.open( fileName, std::ifstream::in );
   
    if( fileStream.is_open( ) == false )
        return false;

    fileStream.seekg( 0, std::ios::end );
    fileSize = ( int )fileStream.tellg( );
    fileStream.seekg( 0, std::ios::beg );

    if( fileSize <= 0 )
        return false;

    char *buffer = new char[fileSize];

    if( buffer == 0 )
        return false;

    memset( buffer, '\0', fileSize );

    TokenStream tokenStream, lineStream, faceStream;
    std::string tempLine, token;

    fileStream.read( buffer, fileSize );
    tokenStream.SetTokenStream( buffer );

    delete[] buffer;

    tokenStream.ResetStream( );

    std::vector<float> verts, norms, texC;
    std::vector<int> faces;

    char lineDelimiters[2] = { '\n', ' ' };

    while( tokenStream.MoveToNextLine( &tempLine ) )
    {
        lineStream.SetTokenStream( ( char* )tempLine.c_str( ) );
        tokenStream.GetNextToken( 0, 0, 0 );

        if( !lineStream.GetNextToken( &token, lineDelimiters, 2 ) )
            continue;

        if( strcmp( token.c_str( ), "v" ) == 0 )
        {
            lineStream.GetNextToken( &token, lineDelimiters, 2 );
            verts.push_back( ( float )atof( token.c_str( ) ) );

            lineStream.GetNextToken( &token, lineDelimiters, 2 );
            verts.push_back( ( float )atof( token.c_str( ) ) );

            lineStream.GetNextToken( &token, lineDelimiters, 2 );
            verts.push_back( ( float )atof( token.c_str( ) ) );
        }
        else if( strcmp( token.c_str( ), "vn" ) == 0 )
        {
            lineStream.GetNextToken( &token, lineDelimiters, 2 );
            norms.push_back( ( float )atof( token.c_str( ) ) );

            lineStream.GetNextToken( &token, lineDelimiters, 2 );
            norms.push_back( ( float )atof( token.c_str( ) ) );

            lineStream.GetNextToken( &token, lineDelimiters, 2 );
            norms.push_back( ( float )atof( token.c_str( ) ) );
        }
        else if( strcmp( token.c_str( ), "vt" ) == 0 )
        {
            lineStream.GetNextToken( &token, lineDelimiters, 2 );
            texC.push_back( ( float )atof( token.c_str( ) ) );

            lineStream.GetNextToken( &token, lineDelimiters, 2 );
            texC.push_back( ( float )atof( token.c_str( ) ) );
        }
        else if( strcmp( token.c_str( ), "f" ) == 0 )
        {
            char faceTokens[3] = { '\n', ' ', '/' };
            std::string faceIndex;

            faceStream.SetTokenStream( ( char* )tempLine.c_str( ) );
            faceStream.GetNextToken( 0, 0, 0 );

            for( int i = 0; i < 3; i++ )
            {
                faceStream.GetNextToken( &faceIndex, faceTokens, 3 );
                faces.push_back( ( int )atoi( faceIndex.c_str( ) ) );

                faceStream.GetNextToken( &faceIndex, faceTokens, 3 );
                faces.push_back( ( int )atoi( faceIndex.c_str( ) ) );

                faceStream.GetNextToken( &faceIndex, faceTokens, 3 );
                faces.push_back( ( int )atoi( faceIndex.c_str( ) ) );
            }
        }
        else if( strcmp( token.c_str( ), "#" ) == 0 )
        {
            int a = 0;
            int b = a;
        }

        token[0] = '\0';
    }

    // "Unroll" the loaded obj information into a list of triangles.

    int vIndex = 0, nIndex = 0, tIndex = 0;
    int numFaces = ( int )faces.size( ) / 9;

    totalVerts_ = numFaces * 3;

    vertices_ = new float[totalVerts_ * 3];

    if( ( int )norms.size( ) != 0 )
    {
        normals_ = new float[totalVerts_ * 3];
    }

    if( ( int )texC.size( ) != 0 )
    {
        texCoords_ = new float[totalVerts_ * 2];
    }

    for( int f = 0; f < ( int )faces.size( ); f+=3 )
    {
        vertices_[vIndex + 0] = verts[( faces[f + 0] - 1 ) * 3 + 0];
        vertices_[vIndex + 1] = verts[( faces[f + 0] - 1 ) * 3 + 1];
        vertices_[vIndex + 2] = verts[( faces[f + 0] - 1 ) * 3 + 2];
        vIndex += 3;

        if(texCoords_)
        {
            texCoords_[tIndex + 0] = texC[( faces[f + 1] - 1 ) * 2 + 0];
            texCoords_[tIndex + 1] = texC[( faces[f + 1] - 1 ) * 2 + 1];
            tIndex += 2;
        }

        if(normals_)
        {
            normals_[nIndex + 0] = norms[( faces[f + 2] - 1 ) * 3 + 0];
            normals_[nIndex + 1] = norms[( faces[f + 2] - 1 ) * 3 + 1];
            normals_[nIndex + 2] = norms[( faces[f + 2] - 1 ) * 3 + 2];
            nIndex += 3;
        }
    }

    verts.clear( );
    norms.clear( );
    texC.clear( );
    faces.clear( );

    return true;
}