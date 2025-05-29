#include "pch.h"
#include "Renderer2D.h"
#include <glm/gtx/matrix_operation.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "RendererApi.h"
#include <Core/RendererDebugger.h>
#include "../Application/ResourceManager.h"

namespace Palmy {
	Renderer2D::Renderer2D(float windowWidth, float windowHeight)
		:m_BatchData(),m_TextureIndex(0),
		m_OrthographicCamera({0.0f,0.0f,1.0f},{0.0f,0.0f,-1.0f},-1.0f, 1.0f, 1.0f,-1.0f,0.1f,10.0f),
		m_CameraController(m_OrthographicCamera),
		m_WindowSize({windowWidth, windowHeight})
	{
		m_Shader = std::make_unique<ShaderProgram>(*ResourceManager::GetShader(2204820834), *ResourceManager::GetShader(4187305228));
		m_Shader->Bind();
		m_VertexArray = std::make_unique<VertexArray>();
		m_VertexArray->Bind();
		m_VertexBuffer = std::make_unique<VertexBuffer>(sizeof(QuadVertexData)*BATCH_SIZE,
			std::initializer_list<BufferLayoutElement>({ 
				{ GL_FLOAT, 4, 4 * sizeof(float),false },
				{ GL_FLOAT, 2, 2 * sizeof(float),false },
				{ GL_FLOAT, 4, 4 * sizeof(float),false },
				{ GL_INT, 1, sizeof(int32_t),true }
			}));
		m_VertexBuffer->Unbind();
		m_VertexArray->Unbind();
	}
	void Renderer2D::RenderQuad(const Transform2D& transform, std::shared_ptr<Texture2D> texture) 
	{
		SubTextureInfo subTextureInfo{
			glm::vec2(0.0f,0.0f),
			glm::vec2(texture->GetWidth(), texture->GetHeight())
		};
		RenderQuad(transform, texture, subTextureInfo);
	}
	void Renderer2D::RenderQuad(const Transform2D& transform, std::shared_ptr<Texture2D> texture, const SubTextureInfo& subTextureInfo)
	{
		if (m_BatchData.size() >= BATCH_SIZE || m_TextureSet.size() >= MAX_TEXTURE_COUNT)
			DrawBatch();
		glm::mat4 transformMatrix = transform.GetTransformMatrix();
		QuadVertexData vertexData;
		int32_t textureNumber = SetTextureNumber(texture);
		SetTextureQuadPosition(vertexData, subTextureInfo);
		for (size_t i = 0; i < QUAD_VERTEX_SIZE; i++)
		{
			vertexData.VertexDatas[i].Position = transformMatrix * vertexData.VertexDatas[i].Position;
			vertexData.VertexDatas[i].Color = DEFAULT_COLOR;
			vertexData.VertexDatas[i].TextureNumber = textureNumber;
		}
		SetTextureCoordinates(vertexData, texture, subTextureInfo);
		m_BatchData.push_back(vertexData);
	}
	void Renderer2D::RenderQuad(const Transform2D& transform, const glm::vec4 color)
	{
		glm::mat4 transformMatrix = transform.GetTransformMatrix();
		if (m_BatchData.size() >= BATCH_SIZE)
			DrawBatch();
		QuadVertexData vertexData;
		for (size_t i = 0; i < QUAD_VERTEX_SIZE; i++)
		{
			vertexData.VertexDatas[i].Position = transformMatrix * vertexData.VertexDatas[i].Position;
			vertexData.VertexDatas[i].Color = color;
			vertexData.VertexDatas[i].TextureNumber = -1;
		}
		m_BatchData.push_back(vertexData);
	}
	void Renderer2D::StartDraw()
	{
		m_Shader->Bind();
		m_Shader->ChangeUniform("uCameraMatrix", m_OrthographicCamera.GetCameraMatrix());
	}
	int32_t Renderer2D::SetTextureNumber(const std::shared_ptr<Texture2D>& texture)
	{
		auto textureIterator = m_TextureSet.find(texture);
		if (textureIterator != m_TextureSet.end())
			return textureIterator->second;
		m_TextureSet.insert({ texture,m_TextureIndex });
		texture->Bind(m_TextureIndex);
		return m_TextureIndex++;
	}
	void Renderer2D::DrawBatch()
	{
		int32_t textureArray[32];
		for (size_t i = 0; i < MAX_TEXTURE_COUNT; i++)
			textureArray[i] = i;
		m_Shader->ChangeUniform("uTexture", MAX_TEXTURE_COUNT, textureArray);
		m_VertexArray->Bind();
		m_VertexBuffer->SetBatchData(static_cast<const void*>(m_BatchData.data()), m_BatchData.size() * sizeof(QuadVertexData));
		RendererApi::QuadDrawCall(QUAD_VERTEX_SIZE * m_BatchData.size());
		m_BatchData.clear();
		m_VertexArray->Unbind();
	}
	inline void Renderer2D::SetTextureQuadPosition(QuadVertexData& vertexData, const SubTextureInfo& subTextureInfo)
	{
		float vMin = -1.0f * (subTextureInfo.Size.x / 2) / m_WindowSize.x;
		float uMin = -1.0f * (subTextureInfo.Size.y / 2) / m_WindowSize.y;
		float vMax = (subTextureInfo.Size.x / 2) / m_WindowSize.x;
		float uMax = (subTextureInfo.Size.y / 2) / m_WindowSize.y;

		vertexData.VertexDatas[0].Position = { vMin, uMin, 0.0f, 1.0f };
		vertexData.VertexDatas[1].Position = { vMax, uMin, 0.0f, 1.0f };
		vertexData.VertexDatas[2].Position = { vMax, uMax, 0.0f, 1.0f };
		vertexData.VertexDatas[3].Position = { vMax, uMax, 0.0f, 1.0f };
		vertexData.VertexDatas[4].Position = { vMin, uMax, 0.0f, 1.0f };
		vertexData.VertexDatas[5].Position = { vMin, uMin, 0.0f, 1.0f };
	}
	inline void Renderer2D::SetTextureCoordinates(QuadVertexData& vertexData, std::shared_ptr<Texture2D>texture, const SubTextureInfo& subTextureInfo)
	{
		float texWidth = texture->GetWidth();
		float texHeight = texture->GetHeight();

		float uMin = subTextureInfo.Offset.x / texWidth;
		float vMin = subTextureInfo.Offset.y / texHeight;
		float uMax = (subTextureInfo.Offset.x + subTextureInfo.Size.x) / texWidth;
		float vMax = (subTextureInfo.Offset.y + subTextureInfo.Size.y) / texHeight;

		vertexData.VertexDatas[0].TextureCoordinates = { uMin, vMin };
		vertexData.VertexDatas[1].TextureCoordinates = { uMax, vMin };
		vertexData.VertexDatas[2].TextureCoordinates = { uMax, vMax };
		vertexData.VertexDatas[3].TextureCoordinates = { uMax, vMax };
		vertexData.VertexDatas[4].TextureCoordinates = { uMin, vMax };
		vertexData.VertexDatas[5].TextureCoordinates = { uMin, vMin };
	}
	QuadVertexData::QuadVertexData()
	{
		VertexDatas = {
			VertexData{glm::vec4(-0.5f,-0.5f,0.0f,1.0f), glm::vec2(0.0f, 0.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f), -1},
			VertexData{glm::vec4( 0.5f,-0.5f,0.0f,1.0f), glm::vec2(1.0f, 0.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f), -1},
			VertexData{glm::vec4( 0.5f, 0.5f,0.0f,1.0f), glm::vec2(1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f), -1},
			VertexData{glm::vec4( 0.5f, 0.5f,0.0f,1.0f), glm::vec2(1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f), -1},
			VertexData{glm::vec4(-0.5f, 0.5f,0.0f,1.0f), glm::vec2(0.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f), -1},
			VertexData{glm::vec4(-0.5f,-0.5f,0.0f,1.0f), glm::vec2(0.0f, 0.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f), -1}
		};
	}
}