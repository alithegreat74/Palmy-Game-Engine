#pragma once
#include <stdint.h>
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
		Texture();
		virtual ~Texture();
		virtual void Bind()const = 0;
		virtual void Unbind()const = 0;
	protected:
		uint32_t m_RendererId;
	};
	class Texture2D:public Texture {
	public:
		Texture2D(const char* filePath);
		virtual void Bind()const override;
		virtual void Unbind()const override;
	};
}