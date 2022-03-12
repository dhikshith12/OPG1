#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.hpp"
#include "Renderer.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "VertexArray.hpp"

int main(int argc, char **argv)
{
    GLFWwindow* window;

    if(!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(640, 480, "OpenGL Exp",NULL,NULL);
    if(!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    //glewInit() has to be called only after we have a proper context
    //which is created by glfwMakeContextCurrent(window)
    if(glewInit()!=GLEW_OK)
        std::cout<< "Error!" << std::endl;
    std::cout<<glGetString(GL_VERSION)<<std::endl;

    //vertex buffer with 4 vertices each vertex having only one
    //attribute(position) stride will be offset b/w vertices 2*sizeof(float)
    {
        float positions[] = {
            -0.5f, -0.5f, //0
            0.5f, -0.5f, //1
            0.5f,  0.5f, //2
            -0.5f,  0.5f, //3
        };

        //this index buffers help us reuse the same vertex buffer objects in this
        //case decreases vram consumption by 33.3%
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };
        // unsigned int vao; /* vertex array objects which maintain the state of layout state for vertexbuffer*/
        // GLCall(glGenVertexArrays(1,&vao));
        // GLCall(glBindVertexArray(vao));
        /* in OpenGl core profile 0 is not an object at all, while in OpenGl compat
              profile 0 is a default object for VAO
              When we are binding a vertex array and we bind a buffer down here,
              nothing actually links the two, but glVertexAttribPointer(0...) links the buffer and vao.i
          */

        VertexArray va;
        VertexBuffer vb(positions,4*2*sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);


        IndexBuffer ib(indices,6);

        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
        /*
         * Uniforms in OpenGl are set per draw.
         * Attributes are set per vertex.

         * Vertex Array Objects are actually what contains the state of binding of
         * layout spec with the Vertex Buffer. so for each draw we can directly draw()
         * call because we have already defined layout.
         */
        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        Renderer renderer;
        float r = 0.0f;
        float increment = 0.05f;
        while(!glfwWindowShouldClose(window))
        {
            GLCall(glClear(GL_COLOR_BUFFER_BIT));
            /* */
            shader.Bind();
            shader.SetUniform4f("u_Color", r, 0.3f, 0.8f,1.0f);
            renderer.Draw(va,ib,shader);

            if(r>1.0f)
                increment=-0.05;
            else if(r<0.0f)
                increment=0.05;

            r+=increment;
            /*OpenGl is a state machine
              draws the currently bound vertex buffers*/

            glfwSwapBuffers(window);

            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}
