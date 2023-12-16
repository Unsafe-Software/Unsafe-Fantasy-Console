#include "ufc.hpp"
#include <raylib.h>
#include <string>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

int UFC::average(lua_State *L) {
   int n = lua_gettop(L);
   double sum = 0;
   int i;

   for (i = 1; i <= n; i++) {
       sum += lua_tonumber(L, i);
   }

   lua_pushnumber(L, sum / n);
   lua_pushnumber(L, sum);
   return 2;
}

UFC::UFC(int width, int height, int fps, bool useOptomizedMode, std::string title) {
    window_width = width;
    window_height = height;
    window_title = title;
    target_fps = fps;
    OptomizedMode = useOptomizedMode;

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            VRAM[y][x] = 0x00000;
        }
    }

    InitWindow(window_width, window_height, window_title.c_str());
    SetTargetFPS(target_fps);

    L = luaL_newstate();
    luaL_openlibs(L);
    lua_register(L, "average", average);
    luaL_dofile(L, "app.lua");
    // luaL_do
};

UFC::~UFC() {
    CloseWindow();
    lua_close(L);
};

void UFC::Redraw() {
    BeginDrawing();
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            DrawRectangle(x * SCALE, y * SCALE, SCALE, SCALE, (Color){static_cast<unsigned char>((VRAM[y][x] >> 16) & 0xFF), static_cast<unsigned char>((VRAM[y][x] >> 8) & 0xFF), static_cast<unsigned char>(VRAM[y][x] & 0xFF), 255});
        }
    }
    EndDrawing();
};

void UFC::Run() {
    while (WindowShouldClose()) {
        Redraw();
    }
}
