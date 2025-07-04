#pragma once
#include <glm/glm.hpp>
#include "../Math/Math.h"
#include "Texture.h"
#include "Shader.h"
#include <vector>
#include <array>
#include "Buffers.h"
#include <unordered_map>
#include "../Rendering/Camera.h"
#include "Renderable.h"
namespace Palmy {
	constexpr size_t BATCH_SIZE = 100;
	constexpr size_t QUAD_VERTEX_SIZE = 6;
	constexpr glm::vec4 DEFAULT_COLOR = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	constexpr size_t MAX_TEXTURE_COUNT = 32;
	struct QuadVertexData
	{
	private:
		struct VertexData
		{
			glm::vec4 Position;
			glm::vec2 TextureCoordinates;
			glm::vec4 Color;
			int32_t TextureNumber;
		};
	public:
		std::array<VertexData, QUAD_VERTEX_SIZE> VertexDatas;
		QuadVertexData();
	};
	class Renderer2D {
	public:
		Renderer2D(float windowWidth, float windowHeight);
		void RenderQuad(const RenderableData& renderable);
		void RenderQuad(const Transform2D&, std::shared_ptr<Texture2D>, bool fitScreen = false);
		void RenderQuad(const Transform2D&, std::shared_ptr<Texture2D>, const SubTextureInfo& subTextureInfo);
		void RenderQuad(const Transform2D&, const glm::vec4 color);
		inline int32_t SetTextureNumber(const std::shared_ptr<Texture2D>& texture);
		void StartDraw();
		void DrawBatch();
	private:
		inline void SetTextureQuadPosition(QuadVertexData& vertexData, const SubTextureInfo& subTextureInfo);
		inline void SetTextureCoordinates(QuadVertexData& vertexData, std::shared_ptr<Texture2D>texture, const SubTextureInfo& subTextureInfo);
	private:
		std::unique_ptr<VertexArray> m_VertexArray;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<ShaderProgram> m_Shader;
		std::vector<QuadVertexData> m_BatchData;
		std::unordered_map<std::shared_ptr<Texture2D>, int32_t> m_TextureSet;
		glm::vec2 m_WindowSize;
		int32_t m_TextureIndex;
		OrthoGraphicCamera m_OrthographicCamera;
		CameraController m_CameraController;
	};
}