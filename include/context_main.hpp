#ifndef CONTEXT_MAIN_HPP
#define CONTEXT_MAIN_HPP

#include <GL/glew.h>
#include "context.hpp"
#include "shader.hpp"

namespace contexts
{
    class main : public context
    {
        protected:
            GLuint vbo, shp, vao, pos_attrib;
            static shader vsh();
            static shader fsh();

        public:
            main();
            ~main();

            void update();
            void render();
    };
}

#endif
