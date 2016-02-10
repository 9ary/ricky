#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Window.hpp>

class window
{
    private:
        sf::Window win;

        window();
        ~window();

    public:
        static window &get();

        window(window const &) = delete;
        void operator =(window const &) = delete;

        bool closed();
        void swap_buffers();
        void poll_events();
};

#endif
