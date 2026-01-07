/*
 * Project Name: Example code for ESPWebFileManager Library
 * Project Brief: Example code for ESPWebFileManager Library
 * Author: Jobit Joseph @ https://github.com/jobitjoseph
 * IDE: Arduino IDE 2.x.x
 * Arduino Core: ESP32 Arduino Core V 3.3.5
 * Dependencies: ESPWebFileManager Library V 2.1.2 @ https://github.com/jobitjoseph/ESPWebFileManager
                 Async TCP Library for ESP32 V 3.4.10 @ https://github.com/ESP32Async/AsyncTCP
 *               ESPAsyncWebServer Library V 3.9.4 @ https://github.com/ESP32Asyxnc/ESPAsyncWebServer
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
 * Date: 03 January 2025
 *
 * For commercial use or licensing requests, please contact [jobitjoseph1@gmail.com].
 */


#include <ESPWebFileManager.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>

/*ESPWebFileManager Constructor*/
/*File System: FS_SPIFFS, FS_LITTLEFS, FS_FATFS, FS_SD, FS_SD_MMC(SD_MMC only supports ESP32 and ESP32-S3)
  Format the file system if mounting failed: true/false
  Additional options:
    - For FS_SD only: Reconfigure SPI pins true/false, followed by SPI pin configuration: CS, MOSI, MISO, SCK.
    - For FS_SD_MMC: Specify line mode (1 for 1-bus, 4 for 4-bus).
        - For ESP32: No need to specify pins, just the bus mode. On ESP32, SD_MMC peripheral is connected to specific GPIO pins and cannot be changed 
        - For ESP32-S3: Provide custom pins: CLK, CMD, D0, (D1, D2, D3 for 4-bus mode).
*/

// Example Constructor Usages: Comment out the unused constructors and uncomment the needed one. For eg here the LittleFS is used.

/* ESPWebFileManager Constructors */

  /**** File System: FS_SPIFFS, Format the file system if mounting failed: true/false ****/
//ESPWebFileManager fileManager(FS_SPIFFS, true);  // FS_SPIFFS, true/false

  /**** File System: FS_LITTLEFS, Format the file system if mounting failed: true/false ****/
ESPWebFileManager fileManager(FS_LITTLEFS, true);  // FS_LITTLEFS, true/false

  /**** File System: FS_FATFS, Format the file system if mounting failed: true/false ****/
//ESPWebFileManager fileManager(FS_FATFS, true);  // FS_FATFS, true/false

  /**** File System: FS_SD, Format the file system if mounting failed: true/false, Reconfigure SPI pins: true/false ****/
//ESPWebFileManager fileManager(FS_SD, false, false);          // FS_SD, true/false, true/false, default SPI pins, CS = -1
//ESPWebFileManager fileManager(FS_SD, false, false, 10);          // FS_SD, true/false, true/false, default SPI pins, CS = -1
//ESPWebFileManager fileManager(FS_SD, false, true, 10, 11, 13, 12); // FS_SD, true/false, true/false, CS, MOSI, MISO, SCK

  /**** File System: FS_SD_MMC (ESP32 Default Pins), Bus mode: 1 for 1-bit mode and 4 for 4-bit mode ****/
    /*
    * SD Card | ESP32
    *    D2       12
    *    D3       13
    *    CMD      15
    *    VSS      GND
    *    VDD      3.3V
    *    CLK      14
    *    VSS      GND
    *    D0       2  (add 1K pull up after flashing)
    *    D1       4
    */
//ESPWebFileManager fileManager(FS_SD_MMC, true, 1);  // FS_SD_MMC, true/false, 1-bit mode
//ESPWebFileManager fileManager(FS_SD_MMC, true, 4);  // FS_SD_MMC, true/false, 4-bit mode

  /**** File System: FS_SD_MMC (ESP32-S3 Custom Pins), Bus mode: 1 for 1-bit mode & 4 for 4-bit mode, pins: CLK, CMD, D0 (D1, D2, D3 for 4-bit mode) ****/
//ESPWebFileManager fileManager(FS_SD_MMC, true, 1, 39, 40, 47);                // FS_SD_MMC, true/false, 1-bit mode, CLK, CMD, D0
//ESPWebFileManager fileManager(FS_SD_MMC, true, 4, 39, 40, 47, 21, 42, 41);     // FS_SD_MMC, true/false, 4-bit mode, CLK, CMD, D0 (D1, D2, D3


#define DEBUG_SERIAL Serial
const char *ssid = "YourSSID";
const char *password = "YourWiFiPassword";
AsyncWebServer server(80);

void setup() {
    DEBUG_SERIAL.begin(115200);
    DEBUG_SERIAL.println("Initializing system...");

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        DEBUG_SERIAL.print(".");
    }
    DEBUG_SERIAL.println("\nWi-Fi connected");
    DEBUG_SERIAL.print("IP Address: ");
    DEBUG_SERIAL.println(WiFi.localIP());

    // Initialize SPIFFS (Change to other types as needed, Valid types: FS_SD_CARD, FS_SPIFFS, FS_LITTLEFS, FS_FATFS )
    if (!fileManager.begin()) {
        DEBUG_SERIAL.println("Failed to initialize file system");
    }

    fileManager.setServer(&server);
    server.begin();
    DEBUG_SERIAL.println("Web server started");
}

void loop() {
    delay(5);
}
