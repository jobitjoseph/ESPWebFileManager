/* 
 * ESPWebFileManager Library
 * Copyright (C) 2026 Jobit Joseph
 * Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 * You may not use this work for commercial purposes. Modifications must credit the original author.
 * See the LICENSE file for more details.
 * Project Name: ESPWebFileManager Library
 * Project Brief: ESPWebFileManager Library
 * Author: Jobit Joseph @ https://github.com/jobitjoseph
 * IDE: Arduino IDE 2.x.x
 * Arduino Core: ESP32 Arduino Core V 3.3.7
 * GitHub: https://github.com/jobitjoseph/ESPWebFileManager
 * Dependencies : 
 *                Async TCP Library for ESP32 V 3.4.10 @ https://github.com/ESP32Async/AsyncTCP
 *                ESPAsyncWebServer Library V 3.10.3 @ https://github.com/ESP32Asyxnc/ESPAsyncWebServer
 * Copyright © Jobit Joseph
 * 
 * This code is licensed under the following conditions:
 *
 * 1. Non-Commercial Use:
 * This program is free software: you can redistribute it and/or modify it
 * for personal or educational purposes under the condition that credit is given 
 * to the original author. Attribution is required, and the original author 
 * must be credited in any derivative works or distributions.
 *
 * 2. Commercial Use:
 * For any commercial use of this software, you must obtain a separate license
 * from the original author. Contact the author for permissions or licensing
 * options before using this software for commercial purposes.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT. IN NO EVENT SHALL 
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES, OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT, OR OTHERWISE, ARISING 
 * FROM, OUT OF, OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
 * DEALINGS IN THE SOFTWARE.
 *
 * Author: Jobit Joseph
 * Date: 24 March 2026
 *
 * For commercial use or licensing requests, please contact [jobitjoseph1@gmail.com].
 */

#ifndef ESP_WEB_FILE_MANAGER_H
#define ESP_WEB_FILE_MANAGER_H

#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#if SOC_SDMMC_HOST_SUPPORTED
#include <SD_MMC.h>
#endif

// Define file system types
#define FS_SPIFFS 1
#define FS_SD 2
#define FS_LITTLEFS 3
#define FS_FATFS 4
#define FS_SD_MMC 5 // New file system type for SD_MMC

#define EN_DEBUG
#define DEBUG_SERIAL Serial

#ifdef EN_DEBUG
#define DEBUG_PRINTLN(x) { DEBUG_SERIAL.println(x); }
#define DEBUG_PRINT(x) { DEBUG_SERIAL.print(x); }
#define DEBUG_PRINT2(x, y)   DEBUG_SERIAL.print(F(x)); DEBUG_SERIAL.println(y)
#define DEBUG_PRINTX(...)     DEBUG_SERIAL.printf(__VA_ARGS__)
#else
#define DEBUG_PRINTLN(x)
#define DEBUG_PRINT(x)
#define DEBUG_PRINT2(x, y)
#define DEBUG_PRINTX(...)
#endif

class ESPWebFileManager {
public:
    ESPWebFileManager(int fsType, bool formatOnFailFlag); // Single constructor for all file systems
    ESPWebFileManager(int fsType, bool formatOnFailFlag, bool SPIreconfig, int csPin = -1, int mosi = -1, int miso = -1, int sck = -1);
    ESPWebFileManager(int fsType, bool formatOnFailFlag, int lineMode);
    ESPWebFileManager(int fsType, bool formatOnFailFlag, int lineMode, int clk, int cmd, int d0, int d1 = -1, int d2 = -1, int d3 = -1);

    bool begin();
    String sanitizePath(const String &path);
    void setServer(AsyncWebServer *server);
    void listDir(const char *dirname, uint8_t levels);
    int getFsType();

private:
    FS *current_fs = nullptr;
    bool memory_ready = false;
    String str_data = "";
    AsyncWebServer *_server = nullptr;

    int _fsType;
    bool _formatOnFailFlag;
    bool _SPIreconfig;
    int _args[4];
    int _csPin;

    int _lineMode;
    int _clk, _cmd, _d0, _d1, _d2, _d3;

    bool initFileSystem(fs::FS &fs, const char *fsName, std::function<bool()> beginFn, std::function<bool()> formatFn);
    bool initSD();
#if SOC_SDMMC_HOST_SUPPORTED
    bool initSD_MMC();
#endif
};


#endif
