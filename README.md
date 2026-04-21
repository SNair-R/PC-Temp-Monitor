# PC-Stat-Monitor

A real-time PC hardware monitor that displays CPU temperature, CPU usage, GPU temperature, and GPU usage on a 128x32 OLED screen using a Raspberry Pi Pico W.

## Hardware

- Raspberry Pi Pico W
- SSD1306 128x32 OLED display (I2C)

### Wiring

| OLED Pin | Pico Pin |
|----------|----------|
| SDA      | GP4      |
| SCL      | GP5      |
| VCC      | 3V3      |
| GND      | GND      |

## How It Works

A Python script (`send_temps.py`) runs on the host PC and collects hardware stats every second:
- CPU temperature via WMI
- CPU usage via `psutil`
- GPU temperature and usage via `nvidia-smi`

The data is sent over USB serial to the Pico in the format:
```
CPU:52.1,USAGE:23.0,GPU:68.0,GUSAGE:14.0
```

The Pico parses the data and displays it on the OLED. If CPU temp exceeds 80°C or GPU temp exceeds 85°C, a warning is shown on screen.

## Requirements

### Hardware
- NVIDIA GPU (required for GPU stats via `nvidia-smi`)
- Intel CPU (required for WMI temperature readings)

### Software
- Python 3
- `psutil` — CPU usage
- `pyserial` — serial communication
- `wmi` — CPU temperature (Windows only)

Install dependencies:
```
pip install psutil pyserial wmi
```

> **Note:** The script must be run with administrator privileges for WMI CPU temperature access. Right-click your terminal and select "Run as administrator" before running the script.

## Building the Firmware

### Prerequisites
- [Pico SDK](https://github.com/raspberrypi/pico-sdk) with `PICO_SDK_PATH` set
- `cmake`
- `arm-none-eabi-gcc`
- MinGW (Windows)

### Build
```
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
```

### Flash
1. Hold the BOOTSEL button on the Pico and plug it into USB
2. It mounts as `RPI-RP2`
3. Copy `PC_TEMP_MONITER.uf2` from the `build` folder to the drive

## Running

1. Flash the firmware to the Pico
2. Plug the Pico in via USB
3. Run the Python script as administrator:
```
python send_temps.py
```

## Display Layout

```
PC STATS
CPU 52.1 °C
USAGE 23.0%
GPU 68.0°C 14%
```

## Future Plans

- Wireless data transmission so the monitor can sit anywhere on your desk without a USB cable tethering it to your PC
