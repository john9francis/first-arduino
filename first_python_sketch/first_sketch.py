import serial
import time

time_between = 5 # seconds
N = 20

data_file = open('./data.txt', 'w')
ser = serial.Serial('COM3', baudrate=9600, timeout=1)

print('getting started...')

i = 0

while (i < N):
  wait_start = time.time()

  while(time.time() - wait_start < time_between):
    arduino_data = ser.readline().decode('ascii')

    print(arduino_data)

    write_string = str(arduino_data)

    data_file.write(write_string)

    i += 1

print('done with data collection, closing file and serial port')

data_file.close()
ser.close()
