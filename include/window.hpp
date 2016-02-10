#ifndef WINDOW_HPP
#define WINDOW_HPP

namespace window
{
    void init();
    bool closed();
    void swap_buffers();
    void poll_events();
};

#endif
