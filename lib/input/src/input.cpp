#include "input/input.hpp"

#include <stdexcept>
#include <string>

#include <Windows.h>
#include <hidsdi.h>
#include <SetupAPI.h>

#include <spdlog/spdlog.h>
#include <winuser.h>

constexpr bool KEY_DOWN = true;
constexpr bool KEY_UP = false;

std::unordered_map<ScanCode, KeyCode> Input::key_mapping {
    { ScanCode::A,            KeyCode::A },
    { ScanCode::B,            KeyCode::B },
    { ScanCode::C,            KeyCode::C },
    { ScanCode::D,            KeyCode::D },
    { ScanCode::E,            KeyCode::E },
    { ScanCode::F,            KeyCode::F },
    { ScanCode::G,            KeyCode::G },
    { ScanCode::H,            KeyCode::H },
    { ScanCode::I,            KeyCode::I },
    { ScanCode::J,            KeyCode::J },
    { ScanCode::K,            KeyCode::K },
    { ScanCode::L,            KeyCode::L },
    { ScanCode::M,            KeyCode::M },
    { ScanCode::N,            KeyCode::N },
    { ScanCode::O,            KeyCode::O },
    { ScanCode::P,            KeyCode::P },
    { ScanCode::Q,            KeyCode::Q },
    { ScanCode::R,            KeyCode::R },
    { ScanCode::S,            KeyCode::S },
    { ScanCode::T,            KeyCode::T },
    { ScanCode::U,            KeyCode::U },
    { ScanCode::V,            KeyCode::V },
    { ScanCode::W,            KeyCode::W },
    { ScanCode::X,            KeyCode::X },
    { ScanCode::Y,            KeyCode::Y },
    { ScanCode::Z,            KeyCode::Z },
    { ScanCode::N0,           KeyCode::N0 },
    { ScanCode::N1,           KeyCode::N1 },
    { ScanCode::N2,           KeyCode::N2 },
    { ScanCode::N3,           KeyCode::N3 },
    { ScanCode::N4,           KeyCode::N4 },
    { ScanCode::N5,           KeyCode::N5 },
    { ScanCode::N6,           KeyCode::N6 },
    { ScanCode::N7,           KeyCode::N7 },
    { ScanCode::N8,           KeyCode::N8 },
    { ScanCode::N9,           KeyCode::N9 },
    { ScanCode::Tilde,        KeyCode::Tilde },
    { ScanCode::Minus,        KeyCode::Minus },
    { ScanCode::Equals,       KeyCode::Equals },
    { ScanCode::BackSlash,    KeyCode::BackSlash },
    { ScanCode::BackSpace,    KeyCode::BackSpace },
    { ScanCode::Space,        KeyCode::Space },
    { ScanCode::Tab,          KeyCode::Tab },
    { ScanCode::Caps,         KeyCode::Caps },
    { ScanCode::LeftShift,    KeyCode::LeftShift },
    { ScanCode::Control,      KeyCode::Control },
    { ScanCode::Alt,          KeyCode::Alt },
    { ScanCode::RightShift,   KeyCode::RightShift },
    { ScanCode::Enter,        KeyCode::Enter },
    { ScanCode::Escape,       KeyCode::Escape },
    { ScanCode::F1,           KeyCode::F1 },
    { ScanCode::F2,           KeyCode::F2 },
    { ScanCode::F3,           KeyCode::F3 },
    { ScanCode::F4,           KeyCode::F4 },
    { ScanCode::F5,           KeyCode::F5 },
    { ScanCode::F6,           KeyCode::F6 },
    { ScanCode::F7,           KeyCode::F7 },
    { ScanCode::F8,           KeyCode::F8 },
    { ScanCode::F9,           KeyCode::F9 },
    { ScanCode::F10,          KeyCode::F10 },
    { ScanCode::F11,          KeyCode::F11 },
    { ScanCode::F12,          KeyCode::F12 },
    { ScanCode::LeftBracket,  KeyCode::LeftBracket },
    { ScanCode::RightBracket, KeyCode::RightBracket },
    { ScanCode::UpArrow,      KeyCode::UpArrow },
    { ScanCode::LeftArrow,    KeyCode::LeftArrow },
    { ScanCode::DownArrow,    KeyCode::DownArrow },
    { ScanCode::RightArrow,   KeyCode::RightArrow },
    { ScanCode::SemiColon,    KeyCode::SemiColon },
    { ScanCode::Quote,        KeyCode::Quote },
    { ScanCode::Comma,        KeyCode::Comma },
    { ScanCode::Period,       KeyCode::Period },
    { ScanCode::Slash,        KeyCode::Slash },
};

std::unordered_map<KeyCode, bool> Input::current_key_state {
    { KeyCode::A,            KEY_UP },
    { KeyCode::B,            KEY_UP },
    { KeyCode::C,            KEY_UP },
    { KeyCode::D,            KEY_UP },
    { KeyCode::E,            KEY_UP },
    { KeyCode::F,            KEY_UP },
    { KeyCode::G,            KEY_UP },
    { KeyCode::H,            KEY_UP },
    { KeyCode::I,            KEY_UP },
    { KeyCode::J,            KEY_UP },
    { KeyCode::K,            KEY_UP },
    { KeyCode::L,            KEY_UP },
    { KeyCode::M,            KEY_UP },
    { KeyCode::N,            KEY_UP },
    { KeyCode::O,            KEY_UP },
    { KeyCode::P,            KEY_UP },
    { KeyCode::Q,            KEY_UP },
    { KeyCode::R,            KEY_UP },
    { KeyCode::S,            KEY_UP },
    { KeyCode::T,            KEY_UP },
    { KeyCode::U,            KEY_UP },
    { KeyCode::V,            KEY_UP },
    { KeyCode::W,            KEY_UP },
    { KeyCode::X,            KEY_UP },
    { KeyCode::Y,            KEY_UP },
    { KeyCode::Z,            KEY_UP },
    { KeyCode::N0,           KEY_UP },
    { KeyCode::N1,           KEY_UP },
    { KeyCode::N2,           KEY_UP },
    { KeyCode::N3,           KEY_UP },
    { KeyCode::N4,           KEY_UP },
    { KeyCode::N5,           KEY_UP },
    { KeyCode::N6,           KEY_UP },
    { KeyCode::N7,           KEY_UP },
    { KeyCode::N8,           KEY_UP },
    { KeyCode::N9,           KEY_UP },
    { KeyCode::Tilde,        KEY_UP },
    { KeyCode::Minus,        KEY_UP },
    { KeyCode::Equals,       KEY_UP },
    { KeyCode::BackSlash,    KEY_UP },
    { KeyCode::BackSpace,    KEY_UP },
    { KeyCode::Space,        KEY_UP },
    { KeyCode::Tab,          KEY_UP },
    { KeyCode::Caps,         KEY_UP },
    { KeyCode::LeftShift,    KEY_UP },
    { KeyCode::Control,      KEY_UP },
    { KeyCode::Alt,          KEY_UP },
    { KeyCode::RightShift,   KEY_UP },
    { KeyCode::Enter,        KEY_UP },
    { KeyCode::Escape,       KEY_UP },
    { KeyCode::F1,           KEY_UP },
    { KeyCode::F2,           KEY_UP },
    { KeyCode::F3,           KEY_UP },
    { KeyCode::F4,           KEY_UP },
    { KeyCode::F5,           KEY_UP },
    { KeyCode::F6,           KEY_UP },
    { KeyCode::F7,           KEY_UP },
    { KeyCode::F8,           KEY_UP },
    { KeyCode::F9,           KEY_UP },
    { KeyCode::F10,          KEY_UP },
    { KeyCode::F11,          KEY_UP },
    { KeyCode::F12,          KEY_UP },
    { KeyCode::LeftBracket,  KEY_UP },
    { KeyCode::RightBracket, KEY_UP },
    { KeyCode::UpArrow,      KEY_UP },
    { KeyCode::LeftArrow,    KEY_UP },
    { KeyCode::DownArrow,    KEY_UP },
    { KeyCode::RightArrow,   KEY_UP },
    { KeyCode::SemiColon,    KEY_UP },
    { KeyCode::Quote,        KEY_UP },
    { KeyCode::Comma,        KEY_UP },
    { KeyCode::Period,       KEY_UP },
    { KeyCode::Slash,        KEY_UP }
};

std::unordered_map<KeyCode, bool> Input::previous_key_state {
    { KeyCode::A,            KEY_UP },
    { KeyCode::B,            KEY_UP },
    { KeyCode::C,            KEY_UP },
    { KeyCode::D,            KEY_UP },
    { KeyCode::E,            KEY_UP },
    { KeyCode::F,            KEY_UP },
    { KeyCode::G,            KEY_UP },
    { KeyCode::H,            KEY_UP },
    { KeyCode::I,            KEY_UP },
    { KeyCode::J,            KEY_UP },
    { KeyCode::K,            KEY_UP },
    { KeyCode::L,            KEY_UP },
    { KeyCode::M,            KEY_UP },
    { KeyCode::N,            KEY_UP },
    { KeyCode::O,            KEY_UP },
    { KeyCode::P,            KEY_UP },
    { KeyCode::Q,            KEY_UP },
    { KeyCode::R,            KEY_UP },
    { KeyCode::S,            KEY_UP },
    { KeyCode::T,            KEY_UP },
    { KeyCode::U,            KEY_UP },
    { KeyCode::V,            KEY_UP },
    { KeyCode::W,            KEY_UP },
    { KeyCode::X,            KEY_UP },
    { KeyCode::Y,            KEY_UP },
    { KeyCode::Z,            KEY_UP },
    { KeyCode::N0,           KEY_UP },
    { KeyCode::N1,           KEY_UP },
    { KeyCode::N2,           KEY_UP },
    { KeyCode::N3,           KEY_UP },
    { KeyCode::N4,           KEY_UP },
    { KeyCode::N5,           KEY_UP },
    { KeyCode::N6,           KEY_UP },
    { KeyCode::N7,           KEY_UP },
    { KeyCode::N8,           KEY_UP },
    { KeyCode::N9,           KEY_UP },
    { KeyCode::Tilde,        KEY_UP },
    { KeyCode::Minus,        KEY_UP },
    { KeyCode::Equals,       KEY_UP },
    { KeyCode::BackSlash,    KEY_UP },
    { KeyCode::BackSpace,    KEY_UP },
    { KeyCode::Space,        KEY_UP },
    { KeyCode::Tab,          KEY_UP },
    { KeyCode::Caps,         KEY_UP },
    { KeyCode::LeftShift,    KEY_UP },
    { KeyCode::Control,      KEY_UP },
    { KeyCode::Alt,          KEY_UP },
    { KeyCode::RightShift,   KEY_UP },
    { KeyCode::Enter,        KEY_UP },
    { KeyCode::Escape,       KEY_UP },
    { KeyCode::F1,           KEY_UP },
    { KeyCode::F2,           KEY_UP },
    { KeyCode::F3,           KEY_UP },
    { KeyCode::F4,           KEY_UP },
    { KeyCode::F5,           KEY_UP },
    { KeyCode::F6,           KEY_UP },
    { KeyCode::F7,           KEY_UP },
    { KeyCode::F8,           KEY_UP },
    { KeyCode::F9,           KEY_UP },
    { KeyCode::F10,          KEY_UP },
    { KeyCode::F11,          KEY_UP },
    { KeyCode::F12,          KEY_UP },
    { KeyCode::LeftBracket,  KEY_UP },
    { KeyCode::RightBracket, KEY_UP },
    { KeyCode::UpArrow,      KEY_UP },
    { KeyCode::LeftArrow,    KEY_UP },
    { KeyCode::DownArrow,    KEY_UP },
    { KeyCode::RightArrow,   KEY_UP },
    { KeyCode::SemiColon,    KEY_UP },
    { KeyCode::Quote,        KEY_UP },
    { KeyCode::Comma,        KEY_UP },
    { KeyCode::Period,       KEY_UP },
    { KeyCode::Slash,        KEY_UP }
};

std::unordered_map<KeyCode, InputState> Input::key_states {
    { KeyCode::A,            { .state = KeyState::Up, .toggled = false } },
    { KeyCode::B,            { .state = KeyState::Up, .toggled = false } },
    { KeyCode::C,            { .state = KeyState::Up, .toggled = false } },
    { KeyCode::D,            { .state = KeyState::Up, .toggled = false } },
    { KeyCode::E,            { .state = KeyState::Up, .toggled = false } },
    { KeyCode::F,            { .state = KeyState::Up, .toggled = false } },
    { KeyCode::G,            { .state = KeyState::Up, .toggled = false } },
    { KeyCode::H,            { .state = KeyState::Up, .toggled = false } },
    { KeyCode::I,            { .state = KeyState::Up, .toggled = false } },
    { KeyCode::J,            { .state = KeyState::Up, .toggled = false } },
    { KeyCode::K,            { .state = KeyState::Up, .toggled = false } },
    { KeyCode::L,            { .state = KeyState::Up, .toggled = false } },
    { KeyCode::M,            { .state = KeyState::Up, .toggled = false } },
    { KeyCode::N,            { .state = KeyState::Up, .toggled = false } },
    { KeyCode::O,            { .state = KeyState::Up, .toggled = false } },
    { KeyCode::P,            { .state = KeyState::Up, .toggled = false } },
    { KeyCode::Q,            { .state = KeyState::Up, .toggled = false } },
    { KeyCode::R,            { .state = KeyState::Up, .toggled = false } },
    { KeyCode::S,            { .state = KeyState::Up, .toggled = false } },
    { KeyCode::T,            { .state = KeyState::Up, .toggled = false } },
    { KeyCode::U,            { .state = KeyState::Up, .toggled = false } },
    { KeyCode::V,            { .state = KeyState::Up, .toggled = false } },
    { KeyCode::W,            { .state = KeyState::Up, .toggled = false } },
    { KeyCode::X,            { .state = KeyState::Up, .toggled = false } },
    { KeyCode::Y,            { .state = KeyState::Up, .toggled = false } },
    { KeyCode::Z,            { .state = KeyState::Up, .toggled = false } },
    { KeyCode::N0,           { .state = KeyState::Up, .toggled = false } },
    { KeyCode::N1,           { .state = KeyState::Up, .toggled = false } },
    { KeyCode::N2,           { .state = KeyState::Up, .toggled = false } },
    { KeyCode::N3,           { .state = KeyState::Up, .toggled = false } },
    { KeyCode::N4,           { .state = KeyState::Up, .toggled = false } },
    { KeyCode::N5,           { .state = KeyState::Up, .toggled = false } },
    { KeyCode::N6,           { .state = KeyState::Up, .toggled = false } },
    { KeyCode::N7,           { .state = KeyState::Up, .toggled = false } },
    { KeyCode::N8,           { .state = KeyState::Up, .toggled = false } },
    { KeyCode::N9,           { .state = KeyState::Up, .toggled = false } },
    { KeyCode::Tilde,        { .state = KeyState::Up, .toggled = false } },
    { KeyCode::Minus,        { .state = KeyState::Up, .toggled = false } },
    { KeyCode::Equals,       { .state = KeyState::Up, .toggled = false } },
    { KeyCode::BackSlash,    { .state = KeyState::Up, .toggled = false } },
    { KeyCode::BackSpace,    { .state = KeyState::Up, .toggled = false } },
    { KeyCode::Space,        { .state = KeyState::Up, .toggled = false } },
    { KeyCode::Tab,          { .state = KeyState::Up, .toggled = false } },
    { KeyCode::Caps,         { .state = KeyState::Up, .toggled = false } },
    { KeyCode::LeftShift,    { .state = KeyState::Up, .toggled = false } },
    { KeyCode::Control,      { .state = KeyState::Up, .toggled = false } },
    { KeyCode::Alt,          { .state = KeyState::Up, .toggled = false } },
    { KeyCode::RightShift,   { .state = KeyState::Up, .toggled = false } },
    { KeyCode::Enter,        { .state = KeyState::Up, .toggled = false } },
    { KeyCode::Escape,       { .state = KeyState::Up, .toggled = false } },
    { KeyCode::F1,           { .state = KeyState::Up, .toggled = false } },
    { KeyCode::F2,           { .state = KeyState::Up, .toggled = false } },
    { KeyCode::F3,           { .state = KeyState::Up, .toggled = false } },
    { KeyCode::F4,           { .state = KeyState::Up, .toggled = false } },
    { KeyCode::F5,           { .state = KeyState::Up, .toggled = false } },
    { KeyCode::F6,           { .state = KeyState::Up, .toggled = false } },
    { KeyCode::F7,           { .state = KeyState::Up, .toggled = false } },
    { KeyCode::F8,           { .state = KeyState::Up, .toggled = false } },
    { KeyCode::F9,           { .state = KeyState::Up, .toggled = false } },
    { KeyCode::F10,          { .state = KeyState::Up, .toggled = false } },
    { KeyCode::F11,          { .state = KeyState::Up, .toggled = false } },
    { KeyCode::F12,          { .state = KeyState::Up, .toggled = false } },
    { KeyCode::LeftBracket,  { .state = KeyState::Up, .toggled = false } },
    { KeyCode::RightBracket, { .state = KeyState::Up, .toggled = false } },
    { KeyCode::UpArrow,      { .state = KeyState::Up, .toggled = false } },
    { KeyCode::LeftArrow,    { .state = KeyState::Up, .toggled = false } },
    { KeyCode::DownArrow,    { .state = KeyState::Up, .toggled = false } },
    { KeyCode::RightArrow,   { .state = KeyState::Up, .toggled = false } },
    { KeyCode::SemiColon,    { .state = KeyState::Up, .toggled = false } },
    { KeyCode::Quote,        { .state = KeyState::Up, .toggled = false } },
    { KeyCode::Comma,        { .state = KeyState::Up, .toggled = false } },
    { KeyCode::Period,       { .state = KeyState::Up, .toggled = false } },
    { KeyCode::Slash,        { .state = KeyState::Up, .toggled = false } }
};

void bind(const InputBinding& binding) {
    Input::bindings.push_back(binding);
}

void handle_inputs(LPARAM lparam) {
    UINT dw_size;
    GetRawInputData((HRAWINPUT)lparam, RID_INPUT, NULL, &dw_size, sizeof(RAWINPUTHEADER));
    LPBYTE lpb = new BYTE[dw_size];

    if(GetRawInputData((HRAWINPUT)lparam, RID_INPUT, lpb, &dw_size, sizeof(RAWINPUTHEADER)) != dw_size) {
        spdlog::error("GetRawInputData returning incorrect size");
    }

    RAWINPUT* raw_input = reinterpret_cast<RAWINPUT*>(lpb);
    if(!raw_input) {
        spdlog::error("RAWINPUT* raw is null");
    }

    switch(raw_input->header.dwType) {
        case RIM_TYPEKEYBOARD: {
            keyboard_input(raw_input->data.keyboard);
            break;
        }
        case RIM_TYPEMOUSE: {
            mouse_input(raw_input->data.mouse);
            break;
        }
    }

    delete[] lpb;
}

void input_update() {
    // Update key states
    for(auto& [key, input_state] : Input::key_states) {
        bool& current = Input::current_key_state[key];
        bool& previous = Input::previous_key_state[key];

        if(current && !previous) {
            input_state.state = KeyState::Pressed;
        }
        else if(!current && previous) {
            input_state.state = KeyState::Released;
        }
        else if(current && previous) {
            input_state.state = KeyState::Hold;
        }
        else {
            input_state.state = KeyState::Up;
        }
    }

    // run any bindings that are triggered
    for(const auto& binding : Input::bindings) {
        InputState& input_state = Input::key_states[binding.keycode];

        switch(binding.action) {
            case InputAction::Call: {
                if(binding.trigger == input_state.state) {
                    binding.callback();
                }
                break;
            }
            case InputAction::Toggle: {
                if(binding.trigger == input_state.state) {
                    input_state.toggled = !input_state.toggled;
                }

                if(input_state.toggled) {
                    binding.callback();
                }

                break;
            }
        }
    }

    // Update previous key sates
    for(auto& [key, state] : Input::key_states) {
        bool& current = Input::current_key_state[key];
        bool& previous = Input::previous_key_state[key];
        previous = current;
    }
}

void keyboard_input(RAWKEYBOARD keyboard) {
    spdlog::info("KeyDown: {}, MakeCode: {}", to_string(static_cast<ScanCode>(keyboard.MakeCode)), keyboard.MakeCode);

    ScanCode scancode = static_cast<ScanCode>(keyboard.MakeCode);
    if(scancode == ScanCode::Undefined) {
        return;
    }

    KeyCode keycode;
    try {
        keycode = Input::key_mapping.at(scancode);
    }
    catch(std::out_of_range e) {
        return;
    }

    if(keyboard.Flags & RI_KEY_BREAK) {
        Input::current_key_state[keycode] = KEY_UP;
    }
    else if(keyboard.Message == WM_KEYDOWN) {
        Input::current_key_state[keycode] = KEY_DOWN;
    }
}

void mouse_input(RAWMOUSE mouse) {
    if(mouse.usFlags == MOUSE_MOVE_RELATIVE) {
        spdlog::info("MouseRel ({}, {})", mouse.lLastX, mouse.lLastY);
    }
}

void remap(KeyCode keycode, ScanCode scancode) {
    Input::key_mapping[scancode] = keycode;
}

void setup_input_devices(HWND hwnd) {
    std::array<RAWINPUTDEVICE, 2> devices = {
        RAWINPUTDEVICE { // Keyboard
            .usUsagePage = 0x01, // HID_USAGE_PAGE_GENERIC
            .usUsage = 0x06,     // HID_USAGE_GENERIC_KEYBOARD
            .dwFlags = 0,
            .hwndTarget = hwnd
        },
        RAWINPUTDEVICE { // Mouse
            .usUsagePage = 0x01, // HID_USAGE_PAGE_GENERIC
            .usUsage = 0x02,     // HID_USAGE_GENERIC_MOUSE
            .dwFlags = 0,
            .hwndTarget = hwnd
        }
    };

    if(RegisterRawInputDevices(devices.data(), devices.size(), sizeof(RAWINPUTDEVICE)) == FALSE) {
        spdlog::error("RegisterRawInputDevices failed!");
    }
}

