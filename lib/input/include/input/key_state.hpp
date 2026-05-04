#ifndef INPUT_KEY_STATE_HPP
#define INPUT_KEY_STATE_HPP

#include <cstdint>

enum class KeyState : uint32_t {
    Pressed,
    Released,
    Up,
    Hold
};

struct InputState {
    KeyState state;
    bool toggled;
};

#endif

