#ifndef INPUT_SCANCODES_HPP
#define INPUT_SCANCODES_HPP

#include <array>
#include <cstdint>
#include <utility>

namespace Keyboard {
    struct ScanCode {
        uint32_t make_code;
    };

    static inline constexpr ScanCode A            {0x1E};
    static inline constexpr ScanCode B            {0x30};
    static inline constexpr ScanCode C            {0x2E};
    static inline constexpr ScanCode D            {0x20};
    static inline constexpr ScanCode E            {0x12};
    static inline constexpr ScanCode F            {0x21};
    static inline constexpr ScanCode G            {0x22};
    static inline constexpr ScanCode H            {0x23};
    static inline constexpr ScanCode I            {0x17};
    static inline constexpr ScanCode J            {0x24};
    static inline constexpr ScanCode K            {0x25};
    static inline constexpr ScanCode L            {0x26};
    static inline constexpr ScanCode M            {0x32};
    static inline constexpr ScanCode N            {0x31};
    static inline constexpr ScanCode O            {0x18};
    static inline constexpr ScanCode P            {0x19};
    static inline constexpr ScanCode Q            {0x10};
    static inline constexpr ScanCode R            {0x13};
    static inline constexpr ScanCode S            {0x1F};
    static inline constexpr ScanCode T            {0x14};
    static inline constexpr ScanCode U            {0x16};
    static inline constexpr ScanCode V            {0x2F};
    static inline constexpr ScanCode W            {0x11};
    static inline constexpr ScanCode X            {0x2D};
    static inline constexpr ScanCode Y            {0x15};
    static inline constexpr ScanCode Z            {0x2C};

    static inline constexpr ScanCode N0           {0x0B};
    static inline constexpr ScanCode N1           {0x02};
    static inline constexpr ScanCode N2           {0x03};
    static inline constexpr ScanCode N3           {0x04};
    static inline constexpr ScanCode N4           {0x05};
    static inline constexpr ScanCode N5           {0x06};
    static inline constexpr ScanCode N6           {0x07};
    static inline constexpr ScanCode N7           {0x08};
    static inline constexpr ScanCode N8           {0x09};
    static inline constexpr ScanCode N9           {0x0A};

    static inline constexpr ScanCode BackTick     {0x29};
    static inline constexpr ScanCode Minus        {0x0C};
    static inline constexpr ScanCode Equals       {0x0D};
    static inline constexpr ScanCode BackSlash    {0x2B};
    static inline constexpr ScanCode BackSpace    {0x0E};
    static inline constexpr ScanCode Space        {0x39};
    static inline constexpr ScanCode Tab          {0x0F};
    static inline constexpr ScanCode CapsLock     {0x3A};
    static inline constexpr ScanCode LeftShift    {0x2A};
    static inline constexpr ScanCode RightShift   {0x36};
    static inline constexpr ScanCode LeftControl  {0x1D};
    static inline constexpr ScanCode LeftAlt      {0x38};
    static inline constexpr ScanCode Enter        {0x1C};
    static inline constexpr ScanCode Escape       {0x01};

    static inline constexpr ScanCode F1           {0x3B};
    static inline constexpr ScanCode F2           {0x3C};
    static inline constexpr ScanCode F3           {0x3D};
    static inline constexpr ScanCode F4           {0x3E};
    static inline constexpr ScanCode F5           {0x3F};
    static inline constexpr ScanCode F6           {0x40};
    static inline constexpr ScanCode F7           {0x41};
    static inline constexpr ScanCode F8           {0x42};
    static inline constexpr ScanCode F9           {0x43};
    static inline constexpr ScanCode F10          {0x44};
    static inline constexpr ScanCode F11          {0x57};
    static inline constexpr ScanCode F12          {0x58};

    static inline constexpr ScanCode LeftBracket  {0x1A};
    static inline constexpr ScanCode RightBracket {0x1B};
    static inline constexpr ScanCode SemiColon    {0x27};
    static inline constexpr ScanCode Quote        {0x28};
    static inline constexpr ScanCode Comma        {0x33};
    static inline constexpr ScanCode Period       {0x34};
    static inline constexpr ScanCode Slash        {0x35};

    static inline constexpr ScanCode RightControl {0x1D};
    static inline constexpr ScanCode RightAlt     {0x38};
    static inline constexpr ScanCode Up           {0x48};
    static inline constexpr ScanCode Left         {0x4B};
    static inline constexpr ScanCode Down         {0x50};
    static inline constexpr ScanCode Right        {0x4D};

    constexpr std::array<ScanCode, 69> scancodes {
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,

        N0,
        N1,
        N2,
        N3,
        N4,
        N5,
        N6,
        N7,
        N8,
        N9,

        BackTick,
        Minus,
        Equals,
        BackSlash,
        BackSpace,
        Space,
        Tab,
        CapsLock,
        LeftShift,
        RightShift,
        LeftControl,
        LeftAlt,
        Enter,
        Escape,

        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,

        LeftBracket,
        RightBracket,
        SemiColon,
        Quote,
        Comma,
        Period,
        Slash,
    };

    constexpr std::array<ScanCode, 6> e0_scancodes {
        RightControl,
        RightAlt,
        Up,
        Left,
        Down,
        Right
    };
};

#endif
