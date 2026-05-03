#include "input/input.hpp"

#include <windows.h>

#include <spdlog/spdlog.h>

std::optional<KeyCode> get_input() {
    return {};
}

std::expected<void, std::string> bind(InputAction action, InputState state, std::function<void()> callback) {
    return {};
}

void setup_input_devices(Input& input, HWND hwnd) {

}

void handle_inputs(Input& input, LPARAM lparam, HWND hwnd) {

}

void keyboard_input(RAWKEYBOARD keyboard) {

}

void mouse_input(RAWMOUSE mouse) {

}
