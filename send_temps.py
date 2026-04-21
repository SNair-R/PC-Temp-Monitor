import psutil
import serial
import time
import subprocess
from serial.tools import list_ports
import wmi


def find_port():
    for port in list_ports.comports():
        if "Board CDC" in port.description or "Pico" in port.description:
            return port.device
        
def get_cpu_temp():
    w = wmi.WMI(namespace=r"root\wmi")
    temps = w.MSAcpi_ThermalZoneTemperature()
    return round((temps[0].CurrentTemperature / 10) - 273.15, 1)

def get_gpu_stats():
    result = subprocess.run(
        ['nvidia-smi', '--query-gpu=temperature.gpu,utilization.gpu', '--format=csv,noheader'],
        capture_output=True, text=True
    )

    temp, usage = result.stdout.strip().split(',')
    return temp.strip(), usage.strip().replace(' %', '')

PORT = find_port()
BAUD = 115200

s = serial.Serial(PORT, BAUD)

time.sleep(2)


while(1):
    C_temp = get_cpu_temp()
    C_usage = psutil.cpu_percent()
    C_usage = str(C_usage)
    
    G_temp, G_usage = get_gpu_stats()

    msg = f"CPU:{C_temp},USAGE:{C_usage},GPU:{G_temp},GUSAGE:{G_usage}\n"

    s.write(msg.encode())
    print(msg)
    time.sleep(1)