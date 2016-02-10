#include "window.hpp"

window::window()
{
    sf::ContextSettings cs;
    cs.majorVersion = 3;
    cs.minorVersion = 2;
    cs.depthBits = 24;
    cs.stencilBits = 8;

    win.create(sf::VideoMode(640, 480), PROJ_NAME, sf::Style::Titlebar | sf::Style::Close, cs);
    win.setVerticalSyncEnabled(true);
}

window::~window()
{
}

window &window::get()
{
    static window w;
    return w;
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
