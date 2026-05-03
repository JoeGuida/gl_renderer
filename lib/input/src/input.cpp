#include "input/input.hpp"

#include <windows.h>

#include <spdlog/spdlog.h>

std::optional<KeyCode> get_input() {
    return {};
}

std::expected<void, std::string> bind(InputAction action, InputState state, std::function<void()> callback) {
    if(bindings.contains(action)) {
        return std::unexpected("binding is already set");
    }

    InputBinding binding {
        .state = state,
        .callback = callback
    };

    bindings.insert({ action, binding });
    return {};
}

void setup_input_devices(Input& input, HWND hwnd) {
    // KeyBoard
    input.devices[0] = {
        .usUsagePage = 0x01, // HID_USAGE_PAGE_GENERIC
        .usUsage = 0x06,     // HID_USAGE_GENERIC_KEYBOARD
        .dwFlags = 0,
        .hwndTarget = hwnd
    };

    // Mouse 
    input.devices[1] = {
        .usUsagePage = 0x01, // HID_USAGE_PAGE_GENERIC
        .usUsage = 0x02,     // HID_USAGE_GENERIC_MOUSE
        .dwFlags = 0,
        .hwndTarget = hwnd
    };

    if(RegisterRawInputDevices(input.devices.data(), input.devices.size(), sizeof(RAWINPUTDEVICE)) == FALSE) {
        spdlog::error("RegisterRawInputDevices failed!");
    }
}

void handle_inputs(Input& input, LPARAM lparam, HWND hwnd) {
    UINT dw_size;
    GetRawInputData((HRAWINPUT)lparam, RID_INPUT, NULL, &dw_size, sizeof(RAWINPUTHEADER));
    LPBYTE lpb = new BYTE[dw_size];

    if(GetRawInputData((HRAWINPUT)lparam, RID_INPUT, lpb, &dw_size, sizeof(RAWINPUTHEADER)) != dw_size) {
        spdlog::error("GetRawInputData returning incorrect size");
    }

    RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(lpb);
    if(!raw) {
        spdlog::error("RAWINPUT* raw is null");
    }

    if(raw->header.dwType == RIM_TYPEKEYBOARD) {
        keyboard_input(raw->data.keyboard);
    }

    if(raw->header.dwType == RIM_TYPEMOUSE) {
        mouse_input(raw->data.mouse);
    }

    delete[] lpb;
}

void keyboard_input(RAWKEYBOARD keyboard) {
    if((keyboard.Flags & RI_KEY_BREAK) == 0) {
        spdlog::info("KeyDown:");
        KeyCode key = get_keycode(ScanCode { .make_code = keyboard.MakeCode });
        if(static_cast<KeyCode>(keyboard.MakeCode) == KeyCode::Escape) {
            //DestroyWindow(hwnd);
        }
    }
}

void mouse_input(RAWMOUSE mouse) {
    switch(mouse.usFlags) {
        case MOUSE_MOVE_RELATIVE:
            spdlog::info("MouseRel ({}, {})", mouse.lLastX, mouse.lLastY);
            break;
        case MOUSE_MOVE_ABSOLUTE:
            break;
        case MOUSE_VIRTUAL_DESKTOP:
            break;
        case MOUSE_ATTRIBUTES_CHANGED:
            break;
        case MOUSE_MOVE_NOCOALESCE:
            break;
        default:
            break;
    }
}
