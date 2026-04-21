import subprocess

result = subprocess.run(
    ['nvidia-smi', '--query-gpu=temperature.gpu,utilization.gpu', '--format=csv,noheader'],
    capture_output=True, text=True
)
temp, usage = result.stdout.strip().split(',')
newtemp = temp.strip() 
newusage = usage.strip().replace(' %', '')

print(type(newtemp), newusage)