#pragma once
#include <raylib.h>
#include <string>
#include "consts.hpp"

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

class UFC {
private:
    int window_width;
    int window_height;
    std::string window_title;
    int target_fps;
    lua_State* L;

    static int average(lua_State *L);

public:
    uint32_t VRAM[HEIGHT][WIDTH];
    bool OptomizedMode;

    UFC(int width, int height, int fps, bool useOptomizedMode, std::string title);
    ~UFC();
    void Redraw();
    void Run();

    void InitLua();
    void CloseLua();
};
