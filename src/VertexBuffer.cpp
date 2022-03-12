#include "VertexBuffer.hpp"
#include "Renderer.hpp"


VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    GLCall(glGenBuffers(1,&m_RendererID)); /* buffer is the id of generated buffer */
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); /* set the state currently bound buffer */
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
   GLCall(glDeleteBuffers(1, &m_RendererID));
}
void VertexBuffer::Bind() const
{
    /* set the state currently bound buffer */
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const
{
    /* unobound the state currently bounder buffer */
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
