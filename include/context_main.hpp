#ifndef CONTEXT_MAIN_HPP
#define CONTEXT_MAIN_HPP

#include <GL/glew.h>
#include "context.hpp"
#include "shader.hpp"
#include "texture.hpp"

namespace contexts
{
    class main : public context
    {
        protected:
            GLuint vbo, vao;
            static shader sh();
            texture tex;

        public:
            main();
            ~main();

            void update();
            void render();
    };
}

#endif
