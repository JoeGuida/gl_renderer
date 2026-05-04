#ifndef INPUT_INPUT_HPP
#define INPUT_INPUT_HPP

#include <cstdint>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

#include <Windows.h>

#include "input/binding.hpp"
#include "input/keycode.hpp"
#include "input/key_state.hpp"
#include "input/scancode.hpp"

struct Input {
    static std::unordered_map<ScanCode, KeyCode> key_mapping;
    static std::unordered_map<KeyCode, bool> current_key_state;
    static std::unordered_map<KeyCode, bool> previous_key_state;
    static std::unordered_map<KeyCode, InputState> key_states;
    inline static std::queue<KeyCode> keys;
    inline static std::vector<InputBinding> bindings;
};

void bind(const InputBinding& binding);
void handle_inputs(LPARAM lparam);
void input_update();
void keyboard_input(RAWKEYBOARD keyboard);
void mouse_input(RAWMOUSE mouse);
void remap(KeyCode keycode, ScanCode scancode);
void setup_input_devices(HWND hwnd);

#endif

