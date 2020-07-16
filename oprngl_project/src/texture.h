#pragma once
#include <string>

class Texture {
private:
	
	std::string m_Filepath;
	unsigned char* m_LocalBuffer;
	int m_width, m_height, m_BPP;
public:
	Texture(const std::string& path);
	~Texture();
	unsigned int m_RendererID;
	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int Getwidth() const{ return m_width; }
	inline int Getheight() const{ return m_height; }
};