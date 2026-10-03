[project_readme.md](https://github.com/user-attachments/files/32955179/project_readme.md)
# esp32-web-server: LED Control

A beginner-friendly Internet of Things (IoT) project that turns an ESP32 microcontroller into a standalone Wi-Fi web server. By connecting to this server through any web browser on your local network, you can wirelessly control the ESP32's built-in LED.

## Hardware Requirements
* Any standard **ESP32 Development Board**
* A data-capable Micro-USB or USB-C cable (ensure it is not a "charge-only" cable)
* A computer (Windows, Mac, or Linux)
* A local Wi-Fi network

## Software Setup

1. **Install the Arduino IDE:** Download and install it from the [official Arduino website](https://www.arduino.cc/en/software).
2. **Install the ESP32 Board Add-on:**
   * Open the Arduino IDE. Go to **File** > **Preferences**.
   * In the "Additional Boards Manager URLs" field, paste: `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
   * Go to **Tools** > **Board** > **Boards Manager**, search for "esp32", and install the package by Espressif Systems.
3. **USB Drivers:** If your computer does not recognize the ESP32 port, you may need to install the USB-to-Serial drivers (usually **CP210x** or **CH340** depending on your specific board model).

## Step-by-Step Usage Guide

### 1. Configure the Code
1. Clone this repository or download the files.
2. Open the `ESP32_Web_Server/ESP32_Web_Server.ino` file in the Arduino IDE.
3. Update the network credentials in the code to match your home network:
   ```cpp
   const char* ssid = "YOUR_WIFI_NETWORK_NAME";
   const char* password = "YOUR_WIFI_PASSWORD";
   ```

### 2. Upload to the ESP32
1. Plug your ESP32 into your computer.
2. In the Arduino IDE, go to **Tools** > **Board** and select your specific ESP32 model (e.g., "DOIT ESP32 DEVKIT V1").
3. Go to **Tools** > **Port** and select the COM port for your ESP32.
4. Click the **Upload** button (the right-pointing arrow at the top left).

### 3. Connect and Test
1. Once the upload reads "Done uploading", open the **Serial Monitor** (the magnifying glass icon in the top right).
2. Set the baud rate in the bottom right corner of the Serial Monitor to **115200**.
3. Press the physical **EN** or **RST** button on your ESP32 board to restart it.
4. Watch the Serial Monitor. Once it connects to your Wi-Fi, it will print a local IP address (e.g., `192.168.1.45`).
5. Open any web browser on a phone or computer connected to the same Wi-Fi network.
6. Type the IP address into the browser's address bar and hit enter. 
7. You should see a webpage with "Turn ON" and "Turn OFF" buttons. Click them to control the physical LED on your board!
