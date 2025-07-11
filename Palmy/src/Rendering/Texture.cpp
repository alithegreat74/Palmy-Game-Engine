#include "pch.h"
#include "Texture.h"
#include <stb_image.h>
#include <glad/glad.h>

namespace Palmy {
	TextureInfo TextureLoader::LoadTexture(const char* path)
	{
		int width, height, nChannels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(path, &width, &height, &nChannels, 0);
		return { width,height,nChannels,data };
	}
	void TextureLoader::UnloadTexture(unsigned char* data)
	{
		stbi_image_free(data);
	}

	Texture::Texture(uint32_t resourceId)
		:m_ResourceId(resourceId)
	{
		glGenTextures(1,&m_RendererId);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_RendererId);
	}

	Texture2D::Texture2D(const char* filePath, uint32_t resourceId)
		:Texture(resourceId)
	{
		TextureInfo info = TextureLoader::LoadTexture(filePath);
		m_Width = info.Width;
		m_Height = info.Height;

		int format = info.ChannelNumber == 3 ? GL_RGB : GL_RGBA;
		Bind();
		glTexImage2D(GL_TEXTURE_2D, 0, format, info.Width, info.Height, 0, format, GL_UNSIGNED_BYTE, info.Data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
		Unbind();
		TextureLoader::UnloadTexture(info.Data);
	}

	void Texture2D::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_RendererId);
	}
	void Texture2D::Bind(int32_t textureNumber) const
	{
		glActiveTexture(GL_TEXTURE0 + textureNumber);
		glBindTexture(GL_TEXTURE_2D, m_RendererId);
	}
	void Texture2D::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void Texture2D::Update(const char* filepath)
	{
		TextureInfo info = TextureLoader::LoadTexture(filepath);
		m_Width = info.Width;
		m_Height = info.Height;
		int format = info.ChannelNumber == 3 ? GL_RGB : GL_RGBA;
		Bind();
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, info.Width, info.Height, format, GL_UNSIGNED_BYTE, info.Data);
		glGenerateMipmap(GL_TEXTURE_2D);
		TextureLoader::UnloadTexture(info.Data);
	}
}