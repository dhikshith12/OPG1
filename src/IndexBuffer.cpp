#include "IndexBuffer.hpp"
#include "Renderer.hpp"



IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    :m_Count(count)
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    GLCall(glGenBuffers(1,&m_RendererID)); /* buffer is the id of generated buffer */
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID)); /* set the state currently bound buffer */
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
   GLCall(glDeleteBuffers(1, &m_RendererID));
}
void IndexBuffer::Bind() const
{
    /* set the state currently bound buffer */
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind() const
{
    /* unobound the state currently bounder buffer */
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
