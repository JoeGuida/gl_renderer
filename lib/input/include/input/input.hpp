#ifndef INPUT_INPUT_HPP
#define INPUT_INPUT_HPP

#include <expected>
#include <functional>
#include <optional>
#include <string>

#include <windows.h>

#include "input/keycode.hpp"

enum class InputAction : uint32_t {
    MoveForward,
    MoveBack,
    MoveLeft,
    MoveRight,
    MoveUp,
    MoveDown
};

enum class InputState : uint32_t {
    Pressed,
    Released,
    Down,
    Up
};

struct InputBinding {
    InputState state;
    std::function<void()> callback;
};

struct Input {
    std::array<RAWINPUTDEVICE, 2> devices;
};

inline std::unordered_map<KeyCode, InputAction> key_to_action;
inline std::unordered_map<InputAction, InputBinding> bindings;

std::optional<KeyCode> get_input();
std::expected<void, std::string> bind(InputAction action, InputState state, std::function<void()> callback);
void setup_input_devices(Input& input, HWND hwnd);
void handle_inputs(Input& input, LPARAM lparam, HWND hwnd);
void keyboard_input(RAWKEYBOARD keyboard);
void mouse_input(RAWMOUSE mouse);

#endif
