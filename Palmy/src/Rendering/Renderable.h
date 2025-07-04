#pragma once
#include "../Math/Math.h"
#include "Texture.h"
#include <memory>
namespace Palmy
{
	struct RenderableData
	{
		std::shared_ptr<Texture2D> Texture;
		Transform2D Transform;
		SubTextureInfo SubTexture;
		bool FitScreen;
		RenderableData(std::shared_ptr<Texture2D>& texture, const Transform2D& transform, const SubTextureInfo& subTextureInfo, bool fitScreen)
			:Texture(texture), Transform(transform), SubTexture(subTextureInfo), FitScreen(fitScreen)
		{}
	};

	class Renderable {
	public:
		Renderable(std::shared_ptr<Texture2D> texture, bool fitScreen)
			:m_Texture(texture), m_FitScreen(fitScreen)
		{
			m_Transform = Transform2D();
			m_SubTextureInfo = SubTextureInfo();
		}
		virtual RenderableData GetRenderableData()
		{
			return Palmy::RenderableData(m_Texture, m_Transform, m_SubTextureInfo, m_FitScreen);
		}
	protected:
		bool m_FitScreen;
		std::shared_ptr<Texture2D> m_Texture;
		Transform2D m_Transform;
		SubTextureInfo m_SubTextureInfo;
	};
}