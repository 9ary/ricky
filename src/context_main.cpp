#include "context_main.hpp"
#include "log.hpp"

namespace
{
    float vertices[] =
    {
        0.0f, 0.5f,
        0.5f, -0.5f,
        -0.5f, -0.5f
    };
}

namespace contexts
{
    main::main() :
        vsh(GL_VERTEX_SHADER, "shaders/test.vsh"),
        fsh(GL_FRAGMENT_SHADER, "shaders/test.fsh")
    {
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        shp = glCreateProgram();
        glAttachShader(shp, vsh);
        glAttachShader(shp, fsh);
        glBindFragDataLocation(shp, 0, "outColor");
        glLinkProgram(shp);
        glUseProgram(shp);

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        pos_attrib = glGetAttribLocation(shp, "position");
        glVertexAttribPointer(pos_attrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(pos_attrib);
    }

    main::~main()
    {
    }

    void main::update()
    {
    }

    void main::render()
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
}
