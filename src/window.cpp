#include <SFML/Window.hpp>
#include "window.hpp"

namespace
{
    sf::Window win;
}

void window::init()
{
    sf::ContextSettings cs;
    cs.majorVersion = 3;
    cs.minorVersion = 2;

    win.create(sf::VideoMode(640, 480), PROJ_NAME, sf::Style::Titlebar | sf::Style::Close, cs);
    win.setVerticalSyncEnabled(true);
}

bool window::closed()
{
    return !win.isOpen();
}

void window::swap_buffers()
{
    win.display();
}

void window::poll_events()
{
    sf::Event event;
    while (win.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                win.close();
                break;

            default:
                continue;
        }
    }
}
