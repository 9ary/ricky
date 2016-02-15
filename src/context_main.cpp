#include "context_main.hpp"
#include "log.hpp"

namespace
{
    int vertices[] =
    {
        0, 0,
        639, 479,
        320, 360,
        480, 120,
        160, 120
    };
}

namespace contexts
{
    shader main::sh()
    {
        static shader shp("shaders/test.vsh", "shaders/test.gsh", "shaders/test.fsh");
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
        glVertexAttribPointer(pos_attrib, 2, GL_INT, GL_FALSE, 0, 0);
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

        glDrawArrays(GL_POINTS, 0, 5);
    }
}
