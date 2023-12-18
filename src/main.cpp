#include <raylib.h>
#include <iostream>
#include <string>
#include <cmath>
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include "consts.hpp"
#include "config.hpp"
#include "bootstrap.ufc.h"

uint32_t Colors[16] = {0x000000, 0x1D2B53, 0x7E2553, 0x008751, 0xAB5236, 0x5F574F, 0xC2C3C7, 0xFFF1E8, 0xFF004D, 0xFFA300, 0xFFEC27, 0x00E436, 0x29ADFF, 0x83769C, 0xFF77A8, 0xFFCCAA};
uint32_t VRAM[HEIGHT][WIDTH];
lua_State* L;

int pset(lua_State* L) {
    // Run only if amount of args is equal to 3
    if (lua_gettop(L) == 3) {
        int x = static_cast<int>(lua_tonumber(L, -3));
        int y = static_cast<int>(lua_tonumber(L, -2));
        int color = static_cast<int>(lua_tonumber(L, -1));
        if (x >= 0 && x < WIDTH &&
            y >= 0 && y < HEIGHT &&
            color >= 0 && color < 16) {
            VRAM[y][x] = Colors[color];
        }
    }
    return 0;
}

int fill(lua_State* L) {
    // Run only if amount to args is equal to 1
    if (lua_gettop(L) == 1) {
        int color = static_cast<int>(lua_tonumber(L, -1));
        if (color >= 0 && color < 16) {
            for (int y = 0; y < HEIGHT; ++y) {
                for (int x = 0; x < WIDTH; ++x) {
                    VRAM[y][x] = Colors[color];
                }
            }
        }
    }
    return 0;
}

int rect(lua_State* L) {
    // Run only if amount to args is equal to 5
    if (lua_gettop(L) == 5) {
        int x1 = static_cast<int>(lua_tonumber(L, -5));
        int y1 = static_cast<int>(lua_tonumber(L, -4));
        int x2 = static_cast<int>(lua_tonumber(L, -3));
        int y2 = static_cast<int>(lua_tonumber(L, -2));
        int color = static_cast<int>(lua_tonumber(L, -1));

        if (x1 < 0) x1 = 0;
        if (y1 < 0) y1 = 0;
        if (x2 < 0) x2 = 0;
        if (y2 < 0) y2 = 0;

        if (x1 >= WIDTH) x1 = WIDTH - 1;
        if (y1 >= HEIGHT) y1 = HEIGHT - 1;
        if (x2 >= WIDTH) x2 = WIDTH - 1;
        if (y2 >= HEIGHT) y2 = HEIGHT - 1;

        if (color >= 0 && color < 16) {
            for (int y = y1; y < y2; ++y) {
                for (int x = x1; x < x2; ++x) {
                    VRAM[y][x] = Colors[color];
                }
            }
        }
    }
    return 0;
}

int circ(lua_State* L) {
    // Run only if amount to args is equal to 4
    if (lua_gettop(L) == 4) {
        int cx = static_cast<int>(lua_tonumber(L, -4));
        int cy = static_cast<int>(lua_tonumber(L, -3));
        int radius = static_cast<int>(lua_tonumber(L, -2));
        int color = static_cast<int>(lua_tonumber(L, -1));

        if (color >= 0 && color < 16) {
            for (int y = cy - radius; y < cy + radius; ++y) {
                for (int x = cx - radius; x < cx + radius; ++x) {
                    if (sqrt((cy - y) * (cy - y) + (cx - x) * (cx - x)) < radius) {
                        VRAM[y][x] = Colors[color];
                    }
                }
            }
        }
    }
    return 0;
}

void init() {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            VRAM[y][x] = 0x00000;
        }
    }

    if (RELEASE == 1) {
        SetTraceLogLevel(LOG_NONE);
    }
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, TITLE);
    SetTargetFPS(60);

    L = luaL_newstate();
    luaL_openlibs(L);
    lua_register(L, "pset", pset);
    lua_register(L, "fill", fill);
    lua_register(L, "rect", rect);
    lua_register(L, "circ", circ);
    std::string boot_strap_string(reinterpret_cast<char*>(bootstrap_ufc), bootstrap_ufc_len);
    luaL_dostring(L, boot_strap_string.c_str());

    // Run Init funciton from bootstrap
    lua_getglobal(L, "init");
    if (lua_isfunction(L, -1)) {
        lua_pcall(L, 0, 0, 0);
    }
}

void run() {
    while (!WindowShouldClose()) {
        BeginDrawing();
        // Run Update funciton from bootstrap
        lua_getglobal(L, "update");
        if (lua_isfunction(L, -1)) {
            lua_pcall(L, 0, 0, 0);
        }

        // Run Draw funciton from bootstrap
        lua_getglobal(L, "draw");
        if (lua_isfunction(L, -1)) {
            lua_pcall(L, 0, 0, 0);
        }

        // Draw
        for (int y = 0; y < HEIGHT; ++y) {
            for (int x = 0; x < WIDTH; ++x) {
                DrawRectangle(x * SCALE, y * SCALE, SCALE, SCALE, (Color){static_cast<unsigned char>((VRAM[y][x] >> 16) & 0xFF), static_cast<unsigned char>((VRAM[y][x] >> 8) & 0xFF), static_cast<unsigned char>(VRAM[y][x] & 0xFF), 255});
            }
        }
        EndDrawing();
    }
}

void close() {
    CloseWindow();
    lua_close(L);
}

int main(int, char**) {
    std::cout << "Booting up " << Config::Name << " " << Config::Version << ";" << std::endl;
    std::cout << Config::License << std::endl << std::endl;

    init();
    run();
    close();
}
