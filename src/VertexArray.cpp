#include "VertexArray.hpp"
#include "VertexBufferLayout.hpp"
#include "Renderer.hpp"
/*
      //vertex attributepointer has to be set for each attribute we have only
      //one attribute position.
      vertex array objects which maintain the state of layout state for vertexbuffer
      in OpenGl core profile 0 is not an object at all, while in OpenGl compat
      profile 0 is a default object for VAO
      When we are binding a vertex array and we bind a buffer down here,
      nothing actually links the two, but glVertexAttribPointer(0...) links the buffer and vao.
*/
void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
       Bind();
       vb.Bind();
       const auto& elements = layout.GetElements();
       unsigned int attribPtr=0;
       for(unsigned int i=0;i<elements.size();++i)
       {
        GLCall(glEnableVertexAttribArray(i)); //enable the vertexAttribPointer
        /*this is actually linking our vertex buffer and vertex array object*/
        GLCall(glVertexAttribPointer(i, elements[i].count,
            elements[i].type, elements[i].normalized,layout.GetStride(),(const void*)attribPtr));
        attribPtr+=elements[i].count*VertexBufferElement::GetSizeOfType(elements[i].type);
       }
}

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &m_RendererID));
}
void VertexArray::Bind() const
{
    GLCall(glBindVertexArray(m_RendererID));
}
void VertexArray::Unbind() const
{
    GLCall(glBindVertexArray(0));
}
VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1,&m_RendererID));
}


