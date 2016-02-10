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

context_manager::context_manager()
{
}

context_manager::~context_manager()
{
    while (!stack.empty())
    {
        delete stack.back();
        stack.pop_back();
    }
}

context_manager &context_manager::get()
{
    static context_manager cm;
    return cm;
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
    window &win = window::get();

    while ((!stack.empty() || !commands.empty()) && !win.closed())
    {
        win.poll_events();

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

        win.swap_buffers();
    }
}

void context_manager::stop()
{
    commands.push(command(::stop));
}
