#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>



using namespace std;

int main()
{

    GLFWwindow *window;
    if(!glfwInit()) //init GLFW -> allocate memory
    {
        std::cerr<<"GLFW failed\n";
        return -1;
    }
    window = glfwCreateWindow(600, 600, "My first OpenGL", nullptr, nullptr);
    if(window==nullptr)
    {
        std::cerr<<"GLFW window failed\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);


    if(glewInit() != GLEW_OK)
    {
        std::cerr<<"GLEW failed\n";
        glfwTerminate(); //delete
        return -1;

    }


    glClearColor(0.2, 0.2, 0.5, 0.0);


    std::vector<float> points =
    {
        0.0f,  0.5f,  0.0f,
        0.5f, -0.5f,  0.0f,
        -0.5f, -0.5f, 0.0f
    };


    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), &points[0], GL_STATIC_DRAW);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //glVertexAttribIPointer(0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);


    const char * verter_shader =
            "#version 400\n"
            "in vec3 vp;"
            "void main(){"
            "gl_Position = vec4(vp, 1.0);"
            "}";

    const char * fragment_shader =
            "#version 400\n"
            "out vec4 frag_color;"
            "void main(){"
            "frag_color = vec4(0.5, 0.0,0.0, 0.5);"
            "}";


    GLuint vs  = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &verter_shader, nullptr);
    glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, nullptr);
    glCompileShader(fs);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, fs);
    glAttachShader(shaderProgram, vs);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);


    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window); //opengl
        glfwPollEvents(); //user

    }

    glfwTerminate(); //delete


    return 0;
}
