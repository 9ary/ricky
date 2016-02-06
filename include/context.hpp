#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <vector>
#include <queue>

class context
{
    public:
        const bool transparent = false;

        virtual ~context() {};
        virtual void update() = 0;
        virtual void render() = 0;
};

class context_manager_command;

namespace context_manager
{
    void init();
    void terminate();

    void push(context *c);
    void pop();

    void loop();

    void stop();
};

#endif
