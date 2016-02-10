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
    shader main::sh()
    {
        static shader shp("shaders/test.vsh", "", "shaders/test.fsh");
        return shp;
    }

    main::main()
    {
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glUseProgram(sh());

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        pos_attrib = glGetAttribLocation(sh(), "position");
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
