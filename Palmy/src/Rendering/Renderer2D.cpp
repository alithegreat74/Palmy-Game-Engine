#include "pch.h"
#include "Renderer2D.h"
#include <glm/gtx/matrix_operation.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "RendererApi.h"
#include <Core/RendererDebugger.h>
#include "../Application/ResourceManager.h"

namespace Palmy {
	Renderer2D::Renderer2D()
		:m_BatchData(),m_TextureIndex(0),
		m_OrthographicCamera({0.0f,0.0f,1.0f},{0.0f,0.0f,-1.0f},-1.0f, 1.0f, 1.0f,-1.0f,0.1f,10.0f),
		m_CameraController(m_OrthographicCamera)
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
	void Renderer2D::RenderQuad(const Transform2D& transform, std::shared_ptr<Texture2D> texture) {
		if (m_BatchData.size() >= BATCH_SIZE || m_TextureSet.size() >= MAX_TEXTURE_COUNT)
			DrawBatch();
		glm::mat4 transformMatrix = transform.GetTransformMatrix();
		QuadVertexData vertexData;
		int32_t textureNumber = SetTextureNumber(texture);
		for (size_t i = 0; i < QUAD_VERTEX_SIZE; i++)
		{
			vertexData.VertexDatas[i].Position = transformMatrix * vertexData.VertexDatas[i].Position;
			vertexData.VertexDatas[i].Color = DEFAULT_COLOR;
			vertexData.VertexDatas[i].TextureNumber = textureNumber;
		}
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