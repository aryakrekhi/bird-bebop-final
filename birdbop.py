import serial
from pynput.keyboard import Controller
import threading

# Function to read from serial and write to the keyboard
def serial_to_keyboard(serial_port, baud_rate):
    keyboard = Controller()
    ser = serial.Serial(serial_port, baud_rate)

    while True:
        try:
            # Read data from the serial port
            serial_data = ser.readline().decode('utf-8').strip()

            # Check if the received data is 'hello'
            if serial_data == 'Go right':
                # Write 'w' to the keyboard
                keyboard.press('d')
                keyboard.release('d')
            elif serial_data == 'Go left':
                keyboard.press('a')
                keyboard.release('a')
            elif serial_data == 'Jump!':
                keyboard.press(' ')
                keyboard.release(' ')

        except serial.SerialException as e:
            print(f"Error reading from serial port: {e}")
            break

# Main function
def main():
    # Replace 'COMx' with the actual serial port where your Arduino is connected
    serial_port = '/dev/cu.usbserial-110'
    baud_rate = 9600

    # Create and start a thread for serial communication
    serial_thread = threading.Thread(target=serial_to_keyboard, args=(serial_port, baud_rate))
    serial_thread.start()

    # Keep the main thread running
    serial_thread.join()

if __name__ == "__main__":
    main()