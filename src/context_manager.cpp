#include "context.hpp"
#include "window.hpp"

enum command_type
{
    push,
    pop,
    stop
};

class context_manager_command
{
    public:
        command_type type;

        union
        {
            context *c;
        };

        context_manager_command(command_type type)
        {
            this->type = type;
        }

        context_manager_command(command_type type, context *c)
        {
            this->type = type;
            this->c = c;
        }
};

namespace
{
    std::vector<context *> stack;
    std::queue<context_manager_command> commands;
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
    commands.push(context_manager_command(::push, c));
}

void context_manager::pop()
{
    commands.push(context_manager_command(::pop));
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
    commands.push(context_manager_command(::stop));
}
