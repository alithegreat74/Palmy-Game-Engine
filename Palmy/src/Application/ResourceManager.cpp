#include "pch.h"
#include "ResourceManager.h"
#include "ResourceLoader.h"
#include "../Core/Core.h"
#include <GLFW/glfw3.h>

namespace Palmy
{
	void ResourceManager::CheckForResources()
	{
		std::string filename = "";
		while (!s_FileQueue.Empty())
		{
			s_FileQueue.TryPop(filename);
			ResourceMetaData resourceData = ResourceLoader::GetResourceType(filename.c_str());
			//TODO: Create a resource class that all resources inherit from it
			if (resourceData.Type == "Shader")
			{
				if (s_Shaders.find(resourceData.Id) != s_Shaders.end())
					continue;
				std::shared_ptr<Shader> shader = ResourceLoader::LoadShader(filename.c_str());
				s_Shaders.insert({ resourceData.Id,shader });
			}
			else if (resourceData.Type == "Texture")
			{
				auto it = s_Textures.find(resourceData.Id);
				if (it != s_Textures.end())
				{
					ENGINE_LOG("Texture {0} was uppdated", filename);
					it->second->Update(filename.c_str());
					continue;
				}
				std::shared_ptr<Texture2D> texture = ResourceLoader::LoadTexture(filename.c_str());
				s_Textures.insert({ resourceData.Id,texture });
			}
		}
	}
	std::shared_ptr<Shader>& ResourceManager::GetShader(uint32_t id)
	{
		auto it = s_Shaders.find(id);
		ENGINE_ASSERT((it != s_Shaders.end()), "Couldn't find a shader with the id {0}", id);
		return it->second;
	}
	std::shared_ptr<Texture2D>& ResourceManager::GetTexture2D(uint32_t id)
	{
		auto it = s_Textures.find(id);
		ENGINE_ASSERT((it != s_Textures.end()), "Couldn't find a texture with the id {0}", id);
		return it->second;
	}
}