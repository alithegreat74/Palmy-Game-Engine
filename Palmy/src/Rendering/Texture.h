#pragma once
#include <stdint.h>
#include <glm/glm.hpp>
namespace Palmy {

	struct TextureInfo
	{
		int Width, Height, ChannelNumber;
		unsigned char* Data;
	};
	class TextureLoader {
	public:
		static TextureInfo LoadTexture(const char* path);
		static void UnloadTexture(unsigned char* data);
	};
	class Texture {
	public:
		Texture(uint32_t resourceId);
		virtual ~Texture();
		virtual void Bind()const = 0;
		virtual void Unbind()const = 0;
		virtual void Bind(int32_t)const = 0;
		virtual void Update(const char* filepath)= 0;
		inline virtual uint32_t GetWidth()const = 0;
		inline virtual uint32_t GetHeight()const = 0;
		virtual uint32_t GetId() {
			return m_RendererId;
		}
	protected:
		uint32_t m_RendererId;
		uint32_t m_ResourceId;
		uint32_t m_Width;
		uint32_t m_Height;
	};
	struct SubTextureInfo
	{
		glm::vec2 Offset;
		glm::vec2 Size;
	};
	class Texture2D:public Texture {
	public:
		Texture2D(const char* filePath, uint32_t resourceId = 0);
		virtual void Bind()const override;
		virtual void Unbind()const override;
		virtual void Bind(int32_t)const override;
		virtual void Update(const char* filepath)override;
		inline virtual uint32_t GetWidth()const override { return m_Width; }
		inline virtual uint32_t GetHeight()const override { return m_Height; }
	};
}