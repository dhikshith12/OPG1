#include "Shader.hpp"
#include "Renderer.hpp"
#include <iostream>
#include <GL/glew.h>
#include <iostream>
#include <limits.h>
#include <fstream>
#include <sstream>
#include <string>
#include <glm/glm.hpp>
Shader::Shader(const std::string& filepath)
    :m_FilePath(filepath), m_RendererID(0)
{

        ShaderProgramSource source = parseShader(filepath);
        std::cout << "Vertex Shader" <<std::endl;
        std::cout << source.VertexSource <<std::endl;
        std::cout << "Fragment Shader" <<std::endl;
        std::cout << source.FragmentSource <<std::endl;

        m_RendererID = CreateShader(source.VertexSource,source.FragmentSource);

}

Shader::~Shader()
{
        GLCall(glDeleteProgram(m_RendererID));
}
void Shader::SetUniform1i(const std::string& name, int value)
{
    int location = GetUniformLocation(name);
    GLCall(glUniform1i(location, value));
}
void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& proj)
{
    GLCall(glUniformMatrix4fv(GetUniformLocation(name),1,GL_FALSE, &proj[0][0]));
}
void Shader::SetUniform1f(const std::string& name, float value)
{
    int location = GetUniformLocation(name);
    GLCall(glUniform1f(location, value));
}
void Shader::Bind() const
{
        GLCall(glUseProgram(m_RendererID));
}
void Shader::Unbind() const
{
        GLCall(glUseProgram(0));
}
void Shader::SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3)
{
    int location = GetUniformLocation(name);
    GLCall(glUniform4f(location, v0, v1, v2, v3));
}

int Shader::GetUniformLocation(const std::string &name){
        if(m_LocationCache.find(name) != m_LocationCache.end())
            return m_LocationCache[name];
        GLCall(int location = glGetUniformLocation(m_RendererID,name.c_str()));
        if(location != -1)
        {
            std::cout << "Warning: uniform '" << name <<"' doesn't exist!"<< std::endl;
        }
        m_LocationCache[name] = location;
        return location;
}

ShaderProgramSource Shader::parseShader(const std::string& filePath)
{
    std::ifstream stream(filePath);
    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    std::stringstream ss[2];
    std::string line;
    ShaderType type = ShaderType::NONE;
    while(getline(stream, line))
    {
        if(line.find("#shader") != std::string::npos)
        {
            if(line.find("vertex") !=std::string::npos)
                type = ShaderType::VERTEX;
            else if(line.find("fragment") !=std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else{
            ss[(int)type]<<line<<'\n';
        }
    }
    return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::CompileShader(const std::string& source, unsigned int type)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    const int shaderLen = source.length();
    GLCall(glShaderSource(id,1,&src,&shaderLen));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id,GL_COMPILE_STATUS,&result));// i - integer, v - vector
    if(result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id,GL_INFO_LOG_LENGTH,&length);
        char* message = (char*)alloca((length+1)*sizeof(char));
        glGetShaderInfoLog(id, length,&length,message);
        std::cout<<"Failed to compile "<<(type==GL_VERTEX_SHADER?"Vertex Shader":"Fragment Shader")
            <<std::endl;
        std::cout<<message<<std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(vertexShader,GL_VERTEX_SHADER);
    unsigned int fs = CompileShader(fragmentShader,GL_FRAGMENT_SHADER);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLint programLinkStatus;
    GLCall(glGetProgramiv(program,GL_LINK_STATUS,&programLinkStatus));

    if(programLinkStatus==GL_FALSE)
    {
        int programLogInfoLen;
        glGetProgramiv(program,GL_INFO_LOG_LENGTH,&programLogInfoLen);
        char* programLogInfo= (char*)alloca(programLogInfoLen*sizeof(char));
        glGetProgramInfoLog(program,INT_MAX,&programLogInfoLen,programLogInfo);
        std::cout<<"Failed to Link Shaders"<<std::endl;
        std::cout<<"Length: "<<programLogInfoLen<<std::endl;
        std::cout<<"Log: "<<programLogInfo<<std::endl;
    }

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));
    return program;
}
