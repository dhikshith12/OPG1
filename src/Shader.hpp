#pragma once
#include <iostream>
#include <string>
#include <unordered_map>

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
private:
    std::string m_FilePath;
    unsigned int m_RendererID;
    std::unordered_map<std::string, int> m_LocationCache;
public:
    Shader(const std::string& filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    //Set Uniforms
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    bool CompileShader();
private:
    int GetUniformLocation(const std::string& name);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    unsigned int CompileShader(const std::string& source, unsigned int type);
    ShaderProgramSource parseShader(const std::string& filePath);
};
