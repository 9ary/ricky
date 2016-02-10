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

class command;

class context_manager
{
    private:
        std::vector<context *> stack;
        std::queue<command> commands;

        context_manager();
        ~context_manager();

    public:
        static context_manager &get();

        context_manager(context_manager const &) = delete;
        void operator =(context_manager const &) = delete;

        void push(context *c);
        void pop();

        void loop();

        void stop();
};

#endif
