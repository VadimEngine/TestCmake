#include "Resource.h"

// std::string Resource::RESOURCE_PATH = "res/";
// TODO filepath?
std::string Resource::RESOURCE_PATH = "C:\\Users\\Administrator\\Desktop\\Programing\\C++\\TestCmake\\res\\";

Resource::~Resource() {
    release();
}

void Resource::loadResource(Resource::ResourceType type, const std::string& resourcePath, const std::string& resourceName) {
    if (type == Resource::ResourceType::MODEL) {
        Model* theModel = new Model();
        theModel->loadMesh(resourcePath);
        mModels_[resourceName] = theModel;
    }
}

void Resource::addResource(Resource::ResourceType type, void* resource, const std::string& resourceName) {

}

void* Resource::getResource(ResourceType type, const std::string& resourceName) {
    if (type == Resource::ResourceType::MODEL) {
        return (void*)mModels_[resourceName];
    } else {
        return nullptr;
    }
}

void Resource::release() {
    // TODO release all
}
