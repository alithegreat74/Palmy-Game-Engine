#include "pch.h"
#include "Renderer2D.h"
#include <glm/gtx/matrix_operation.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "RendererApi.h"
#include <Core/RendererDebugger.h>
namespace Palmy {
	Renderer2D::Renderer2D()
		:m_BatchIndex(0),m_BatchData()
	{
		CHECK_FOR_GRAPHICS_ERRORS;
		m_VertexArray = std::make_unique<VertexArray>();
		m_VertexArray->Bind();
		m_VertexBuffer = std::make_unique<VertexBuffer>(sizeof(QuadVertexData)*BATCH_SIZE,
			std::initializer_list<BufferLayoutElement>({ 
				{ GL_FLOAT, 4, 4 * sizeof(float),false },
				{ GL_FLOAT, 2, 2 * sizeof(float),false },
				{ GL_FLOAT, 4, 4 * sizeof(float),false } 
			}));
		m_VertexBuffer->Unbind();
		m_VertexArray->Unbind();
	}
	void Renderer2D::RenderQuad(const Transform2D& transform) {
		CHECK_FOR_GRAPHICS_ERRORS;
		glm::mat4 transformMatrix = transform.GetTransformMatrix();
		if (m_BatchIndex >= BATCH_SIZE)
			DrawBatch();
		QuadVertexData vertexData;
		for (size_t i = 0; i < QUAD_VERTEX_SIZE; i++)
		{
			vertexData.VertexDatas[i].Position = transformMatrix * vertexData.VertexDatas[i].Position;
		}
		m_BatchData.push_back(vertexData);
		m_BatchIndex++;
	}

	void Renderer2D::RenderQuad(const Transform2D& transform, const glm::vec4 color)
	{
		glm::mat4 transformMatrix = transform.GetTransformMatrix();
		if (m_BatchIndex >= BATCH_SIZE)
			DrawBatch();
		QuadVertexData vertexData;
		for (size_t i = 0; i < QUAD_VERTEX_SIZE; i++)
		{
			vertexData.VertexDatas[i].Position = transformMatrix * vertexData.VertexDatas[i].Position;
			vertexData.VertexDatas[i].Color = color;
			
		}
		m_BatchData.push_back(vertexData);
		m_BatchIndex++;
	}
	void Renderer2D::DrawBatch()
	{
		CHECK_FOR_GRAPHICS_ERRORS;
		m_VertexArray->Bind();
		m_VertexBuffer->SetBatchData(static_cast<const void*>(m_BatchData.data()), m_BatchData.size() * sizeof(QuadVertexData));
		RendererApi::QuadDrawCall(QUAD_VERTEX_SIZE * m_BatchData.size());
		m_BatchData.clear();
		m_VertexArray->Unbind();
		m_BatchIndex = 0;
	}
	QuadVertexData::QuadVertexData()
	{
		VertexDatas = {
			VertexData{glm::vec4(-0.5f,-0.5f,0.0f,1.0f),glm::vec2(0.0f, 0.0f),glm::vec4(1.0f,1.0f,1.0f,1.0f)},
			VertexData{glm::vec4( 0.5f,-0.5f,0.0f,1.0f),glm::vec2(1.0f, 0.0f),glm::vec4(1.0f,1.0f,1.0f,1.0f)},
			VertexData{glm::vec4( 0.5f, 0.5f,0.0f,1.0f),glm::vec2(1.0f, 1.0f),glm::vec4(1.0f,1.0f,1.0f,1.0f)},
			VertexData{glm::vec4( 0.5f, 0.5f,0.0f,1.0f),glm::vec2(1.0f, 1.0f),glm::vec4(1.0f,1.0f,1.0f,1.0f)},
			VertexData{glm::vec4(-0.5f, 0.5f,0.0f,1.0f),glm::vec2(0.0f, 1.0f),glm::vec4(1.0f,1.0f,1.0f,1.0f)},
			VertexData{glm::vec4(-0.5f,-0.5f,0.0f,1.0f),glm::vec2(0.0f, 0.0f),glm::vec4(1.0f,1.0f,1.0f,1.0f)}
		};
	}
}