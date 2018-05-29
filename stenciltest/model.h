#include <vector>
#include <string>

#include <assimp/scene.h>
#include "mesh.h"
#include "../Shader.hpp"

class Model
{
    public:
        Model(const char* path);
        void draw(Shader shader);

    private:
        std::vector<Mesh> meshes;
        std::vector<Texture> texturesLoaded;
        std::vector<Texture> textures;
        std::string directory;
        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

};

unsigned int textureFromFile(const char* path, const std::string &directory);