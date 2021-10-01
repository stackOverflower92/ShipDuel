#include "ResourceManager.h"

ResourceManager::ResrourceManager()
{

}

ResourceManager::~ResourceManager()
{
    
}

std::string ResourceManager::GetResource(ResourceType resourceType, std::string relativeFileName)
{
    std::string root = _GetRoot(resourceType);
}

std::string _GetRoot(ResourceType resourceType)
{
    if (resourceType == ResourceType::FONT)
    {
        return "/media/fonts/";
    }

    if (resourceType == ResourceType::IMAGE)
    {
        return "/media/img/";
    }

    if (resourceType == ResourceType::SOUND)
    {
        return "/media/audio/";
    }
}