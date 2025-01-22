#pragma once
#include <initializer_list>
#include <vector>

namespace Palmy {
	struct BufferLayoutElement {
		uint32_t BaseDataType;
		uint8_t NumberOfElements;
		size_t Size;
		bool Normalize;
	};
	class BufferLayout {
	public:
		BufferLayout(std::initializer_list<BufferLayoutElement> elements);
		void SetAttributes();
	private:
		std::vector<BufferLayoutElement> m_Elements;
		size_t m_RowLength;
		size_t m_RowSize;
	};
	class VertexBuffer {
	public:
		VertexBuffer(const void* verticies, size_t size, std::initializer_list<BufferLayoutElement> elements);
		~VertexBuffer();
		void Bind()const;
		void Unbind()const;
	private:
		uint32_t m_RendererId;
		BufferLayout m_Layout;
	};
	class IndexBuffer {
	public:
		IndexBuffer(const void* indicies, size_t size);
		~IndexBuffer();
		void Bind()const;
		void Unbind()const;
	private:
		uint32_t m_RendererId;
	};
	class VertexArray {
	public:
		VertexArray();
		~VertexArray();

		void Bind()const;
		void Unbind()const;
	private:
		uint32_t m_RendererId;
	};
}
