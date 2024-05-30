#pragma once
#include <string>
#include <unordered_map>
#include "Mesh.h"
#include "Model.h"
#include "Shader.h"
#include "Texture.h"

class Resource {
public:

    enum class ResourceType {
        MODEL,
        MESH,
        TEXTURE,
        AUDIO,
        FONT,
        SHADER
    };
    
    union ResourcePointer {
        Mesh* meshPtr;
        Model* modelPtr;
    };
    
    static std::string RESOURCE_PATH;

    //std::unordered_map<ResourceType, std::unordered_map<std::string, ResourcePointer>> resources;



    /*
    std::unordered_map<std::string, Texture*> textures_;
    std::unordered_map<std::string, Mesh*> meshes_;
    std::unordered_map<std::string, TextFile*> textFiles_;
    std::unordered_map<std::string, AudioFile*> audioFiles_;
    std::unordered_map<std::string, Font*> fonts_;
     std::vector<unsigned char> data // undefined binary data
    */

    std::unordered_map<std::string, Mesh*> mMeshes_;
    std::unordered_map<std::string, Model*> mModels_;

    ~Resource();

   void loadResource(ResourceType type, const std::string& resourcePath, const std::string& resourceName);

   void addResource(ResourceType type, void* resource, const std::string& resourceName);
   
   void* getResource(ResourceType type, const std::string& resourceName);

   void release();

};

/*

// Define your resource types
enum class ResourceType {
    Texture,
    Mesh,
    TextFile,
    AudioFile,
    Font
};

// Define a union to hold different resource pointers (size of this would be the size of the largest member which in this case is a single pointer)
union ResourcePointer {
    Texture* texturePtr;
    Mesh* meshPtr;
    TextFile* textFilePtr;
    AudioFile* audioFilePtr;
    Font* fontPtr;

    // Add constructors if needed
};

// Define your map using nested unordered_maps
std::unordered_map<ResourceType, std::unordered_map<std::string, ResourcePointer>> resources;
// Example of adding a resource
std::string resourceName = "myTexture";
Texture* texture = new Texture(); // Example texture creation
ResourcePointer pointer;
pointer.texturePtr = texture;
resources[ResourceType::Texture][resourceName] = pointer;

// Example of accessing a resource
std::string textureName = "myTexture";
Texture* texturePtr = resources[ResourceType::Texture][textureName].texturePtr;

*/