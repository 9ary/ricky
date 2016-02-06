#include "context.hpp"
#include "window.hpp"

enum command_type
{
    push,
    pop,
    stop
};

class command
{
    public:
        command_type type;

        union
        {
            context *c;
        };

        command(command_type type)
        {
            this->type = type;
        }

        command(command_type type, context *c)
        {
            this->type = type;
            this->c = c;
        }
};

namespace
{
    std::vector<context *> stack;
    std::queue<command> commands;
}

void context_manager::init()
{
}

void context_manager::terminate()
{
    while (!stack.empty())
    {
        delete stack.back();
        stack.pop_back();
    }
}

void context_manager::push(context *c)
{
    commands.push(command(::push, c));
}

void context_manager::pop()
{
    commands.push(command(::pop));
}

void context_manager::loop()
{
    while ((!stack.empty() || !commands.empty()) && !window::closed())
    {
        window::poll_events();

        while (!commands.empty())
        {
            auto command = commands.front();
            switch (command.type)
            {
                case ::push:
                    stack.push_back(command.c);
                    break;

                case ::pop:
                    delete stack.back();
                    stack.pop_back();
                    break;

                case ::stop:
                    return;
            }
            commands.pop();
        }

        auto context = stack.back();
        context->update();
        context->render();

        window::swap_buffers();
    }
}

void context_manager::stop()
{
    commands.push(command(::stop));
}
