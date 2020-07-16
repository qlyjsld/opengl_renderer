#pragma once

class IndexBuffer{
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
public:
	IndexBuffer(const unsigned int* data, const unsigned int& count);
	~IndexBuffer() { Release(); }

	IndexBuffer(const IndexBuffer& other) = delete;
	IndexBuffer& operator=(const IndexBuffer& other) = delete;

	IndexBuffer(IndexBuffer&& other) noexcept
		: m_RendererID(other.m_RendererID)
	{
		m_Count = other.m_Count;
		other.m_RendererID = 0;
	}

	IndexBuffer& operator=(IndexBuffer&& other) noexcept{
		if (this != &other) {
			Release();
			m_RendererID = other.m_RendererID;
			other.m_RendererID = 0;
		}
		return *this;
	}
	
	void Release() {
		if (m_RendererID)
			glDeleteBuffers(1, &m_RendererID);
	}

	void Bind() const;
	void Unbind() const;

	unsigned int getCount() const{
		return m_Count;
	}
};