#ifndef CONFIG_H
#define CONFIG_H

extern "C" {
#include <bits/stdint-uintn.h>
#include <libavcodec/avcodec.h>
#include <signal.h>
#include <stdbool.h>
}

#include <string>
#include <bitset>
#include "magic_enum.hpp"

using namespace magic_enum::bitwise_operators;

//
// CMake Defined Settings
//

/* #undef KIMERA_WINDOWS */
/* #undef KIMERA_MACOS */
#define KIMERA_LINUX

#define KIMERA_VERSION_MAJOR 1
#define KIMERA_VERSION_MINOR 0

//
// Default Settings
//

#define HEADER_SIZE          20
#define KIMERA_PSK_IDENTITY  "KIMERA_PSK_IDENTITY"
#define MAX_KEY_LEN          256
#define DEFAULT_KEY_LEN      64
#define DEFAULT_PACKET_SIZE  1020
#define DEFAULT_FORMAT       AV_PIX_FMT_YUV420P

enum class Interfaces : uint16_t {
    NONE         = 0 << 0,
    // Source/Sink Options
    UNIX         = 1 << 0,
    TCP          = 1 << 1,
    UDP          = 1 << 2,
    DISPLAY      = 1 << 3,
    LOOPBACK     = 1 << 4,
    // Pipe Options
    FILTER       = 1 << 5,
    RESAMPLE     = 1 << 6,
    GPU_RESAMPLE = 1 << 7,
    CRYPTO       = 1 << 8,
};

enum class Mode : uint16_t {
    NONE        = 0 << 0,
    TRANSMITTER = 1 << 0,
    RECEIVER    = 1 << 1,
};

bool CHECK(Interfaces value, Interfaces flag);
bool CHECK(Mode value, Mode flag);

typedef struct {
    int width;
    int height;
    int bitrate;
    int framerate;
    int port;

    std::string vert_shader;
    std::string frag_shader;
    std::string crypto_key;
    std::string coder_name;
    std::string address;
    std::string loopback;

    enum AVPixelFormat in_format  = DEFAULT_FORMAT;
    enum AVPixelFormat out_format = DEFAULT_FORMAT;
    int packet_size = DEFAULT_PACKET_SIZE;

    Mode mode        = Mode::NONE;
    Interfaces source = Interfaces::NONE;
    Interfaces pipe   = Interfaces::NONE;
    Interfaces sink   = Interfaces::NONE;
} State;

#endif
