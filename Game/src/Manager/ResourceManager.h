#pragma once

#include <string>

class ResourceManager
{
public:
    enum ResourceType
    {
        FONT,
        IMAGE,
        SOUND
    }

    ResrourceManager();
    ~ResourceManager();

    static std::string GetResource(ResourceType resourceType, std::string relativeFileName);

private:
    std::string _GetRoot(ResourceType resourceType);
};