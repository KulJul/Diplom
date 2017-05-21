
#ifndef MODEL_H
#define MODEL_H

class Model
{
	public:
		
		struct Mesh
		{
			int m_materialIndex;
			int m_numTriangles;
			int *m_pTriangleIndices;
		};

		
		struct Material
		{
			float m_ambient[4], m_diffuse[4], m_specular[4], m_emissive[4];
			float m_shininess;
			GLuint m_texture;
			char *m_pTextureFilename;
		};

		
		struct Triangle
		{
			float m_vertexNormals[3][3];
			float m_s[3], m_t[3];
			int m_vertexIndices[3];
		};

		
		struct Vertex
		{
			char m_boneID;	
			float m_location[3];
		};

	public:
		/*	Constructor. */
		Model();

		/*	Destructor. */
		virtual ~Model();

		/*	
			Load the model data into the private variables. 
				filename			Model filename
		*/
		virtual bool loadModelData( const char *filename ) = 0;

		/*
			Draw the model.
		*/
		void draw();

		/*
			Called if OpenGL context was lost and we need to reload textures, display lists, etc.
		*/
		void reloadTextures();

		char* m_name;
	protected:
		
		int m_numMeshes;
		Mesh *m_pMeshes;

		
		int m_numMaterials;
		Material *m_pMaterials;

		
		int m_numTriangles;
		Triangle *m_pTriangles;

		
		int m_numVertices;
		Vertex *m_pVertices;
	
};

#endif 
