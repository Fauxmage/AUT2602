import serial
import time

# Serial port, baudrate
ser = serial.Serial("/dev/tty.usbmodem1102", 9600, timeout=1)
# Enable DTR
ser.dtr = True


def read_from_serial():
    try:
        while True:
            # Check if data in serial buffer
            if ser.in_waiting > 0:
                data = ser.readline().decode("ISO-8859-1").rstrip()
                rawdata = ser.readline().rstrip()

                print(f"Received data: {data}\nRaw data: {rawdata}\n")
            time.sleep(1)
    except KeyboardInterrupt:
        print("Exiting...")


if __name__ == "__main__":
    read_from_serial()

    # Close the serial port when done
    ser.close()
