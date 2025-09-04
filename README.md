# ESPWebFileManager

**EspWebFileManager** is a library that manages various file systems and provides file management over a web interface for ESP32. With the **EspWebFileManager** library, you will get a  responsive interface that allows you to upload, download, and delete files stored on the ESP32's filesystem. Now Supports folders too. You can create or delete folders on LittleFS, FAT FS or SD card. Folders are not supported on SPIFFS. The **EspWebFileManager** library supports multiple file systems like SD Card, SPIFFS, LittleFS, and FATfs on ESP32.

<p align="center">
  <a href="https://www.paypal.com/paypalme/jobitjoseph">
    <img src="https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif" alt="Donate with PayPal" />
  </a>
</p>

<img src="https://github.com/jobitjoseph/ESPWebFileManager/blob/main/Images/Desktop.jpg" width="" alt="alt_text" title="image_tooltip">
<img src="https://github.com/jobitjoseph/ESPWebFileManager/blob/main/Images/Phone.jpg" width="" alt="alt_text" title="image_tooltip">

## Features

- **Support for multiple file systems:** SPIFFS, LittleFS, FATFS, SD, and SD_MMC.
- **File Management:** web interface for file management tasks such as upload, download, and delete.
- **Folder Management:** You can create or delete folders on LittleFS, FAT FS or SD card. Folders are not supported on SPIFFS.
- **Automatic file system formatting if mounting fails (Not available for SD card in SPI mode).#**

## Installation

### Arduino IDE
1. Through Arduino Library Manager: In the Arduino library manager search for ESPWebFileManager and install.
2. Manual Installation: Download the zip file and install it using `Sketch -> Include Library -> Add .ZIP Library` or Extract the zip file to the Arduino libraries folder.
### PlatformIO
1. Add the library to your `platformio.ini`:
   ```ini
   lib_deps =
       https://github.com/jobitjoseph/ESPWebFileManager.git

## Usage 
    
Check the Example file provided. Libraray usage is now much easier. All you have to do is include the header file and create the proper constructor at the start of the sketch and call the begin function in the setup. :
### include the library in your sketch:

```cpp
#include "ESPWebFileManager.h"
```

---

### Constructor Explanation
The `ESPWebFileManager` class provides several constructors tailored to different file systems. Choose the one that fits your project.

#### Constructor Options

##### Common Parameters
- **File System Types**: 
  - `FS_SPIFFS`
  - `FS_LITTLEFS`
  - `FS_FATFS`
  - `FS_SD`
  - `FS_SD_MMC` (Only supported on ESP32 and ESP32-S3)
- **Format on Fail**: Set to `true` to format the file system if mounting fails.

##### Additional Options
1. **For FS_SD:**
   - Reconfigure SPI pins (`true/false`).
   - Provide custom SPI pin configurations (CS, MOSI, MISO, SCK).
2. **For FS_SD_MMC:**
   - Specify line mode: 
     - `1` for 1-bus mode.
     - `4` for 4-bus mode.
   - For ESP32: Use default pins for SD_MMC.
   - For ESP32-S3: Provide custom pins (CLK, CMD, D0, and optionally D1, D2, D3 for 4-bus mode).

---

#### Example Constructor Usages
Below are sample configurations for initializing the file manager. Uncomment the required configuration based on your file system and requirements:

```cpp
/* ESPWebFileManager Constructors */

// File System: FS_SPIFFS
ESPWebFileManager fileManager(FS_SPIFFS, true);  // Format on fail: true/false

// File System: FS_LITTLEFS
ESPWebFileManager fileManager(FS_LITTLEFS, true);  // Format on fail: true/false

// File System: FS_FATFS
ESPWebFileManager fileManager(FS_FATFS, true);  // Format on fail: true/false

// File System: FS_SD with default SPI pins
ESPWebFileManager fileManager(FS_SD, false, false);  // Format on fail: true/false, Reconfigure SPI: true/false

// File System: FS_SD with custom SPI pins
ESPWebFileManager fileManager(FS_SD, false, true, 10, 11, 13, 12); // CS, MOSI, MISO, SCK

// File System: FS_SD_MMC (ESP32 Default Pins)
ESPWebFileManager fileManager(FS_SD_MMC, true, 1);  // 1-bit mode
ESPWebFileManager fileManager(FS_SD_MMC, true, 4);  // 4-bit mode

// File System: FS_SD_MMC (ESP32-S3 Custom Pins)
ESPWebFileManager fileManager(FS_SD_MMC, true, 1, 39, 40, 47);                // 1-bit mode, CLK, CMD, D0
ESPWebFileManager fileManager(FS_SD_MMC, true, 4, 39, 40, 47, 21, 42, 41);     // 4-bit mode, CLK, CMD, D0, D1, D2, D3
```

---


### Initialization    
Call the begin function in the setup. :
   ```cpp
   fileManager.begin()
```


After uploading the code, you can access the file manager through the URL **`http://ipadrees/file`**. for eg **`http://192.168.0.124/file`**
## Issues and Warnings
    Don't use files with way too long file names.

## License

 *EspWebFileManager Library
 * Copyright (C) 2024 Jobit Joseph
 * Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 * You may not use this work for commercial purposes without permission from the original author. Modifications must credit the original author.
 * See the LICENSE file for more details.
