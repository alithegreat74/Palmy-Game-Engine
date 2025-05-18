#include "pch.h"
#include "Buffers.h"
#include <glad/glad.h>
#include <Core/RendererDebugger.h>
namespace Palmy {
	VertexBuffer::VertexBuffer(size_t size, std::initializer_list<BufferLayoutElement> elements):
		m_Layout(elements)
	{
		glGenBuffers(1, &m_RendererId);
		Bind();
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);
		m_Layout.SetAttributes();
		Unbind();
	}
	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererId);
	}
	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
	}
	void VertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void VertexBuffer::SetBatchData(const void* data, size_t dataSize)
	{
		Bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, dataSize, data);
		Unbind();
	}
	IndexBuffer::IndexBuffer(const void* indicies, size_t size)
	{
		glGenBuffers(1, &m_RendererId);
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indicies, GL_STATIC_DRAW);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererId);
	}

	void IndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
	}

	void IndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_RendererId);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererId);
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(m_RendererId);
	}

	void VertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	BufferLayout::BufferLayout(std::initializer_list<BufferLayoutElement> elements):
		m_Elements(elements), m_RowLength(0), m_RowSize(0)
	{
		for (const auto& element : elements)
		{
			m_RowSize += element.Size;
			m_RowLength += element.NumberOfElements;
		}
	}

	void BufferLayout::SetAttributes()
	{
		size_t stride = 0;
		for (size_t i = 0; i < m_Elements.size(); i++)
		{
			glEnableVertexAttribArray(i);
			if(m_Elements[i].BaseDataType==GL_FLOAT)
				glVertexAttribPointer(i, m_Elements[i].NumberOfElements, m_Elements[i].BaseDataType, m_Elements[i].Normalize, m_RowSize, (void*)(stride));
			else
				glVertexAttribIPointer(i, m_Elements[i].NumberOfElements, m_Elements[i].BaseDataType, m_RowSize, (void*)(stride));
			stride += m_Elements[i].Size;
		}
	}

}