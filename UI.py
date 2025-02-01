import tkinter as tk
from tkinter import ttk, messagebox
import serial
from serial import Serial
import time
import os

# Define the baud rate
baud_rate = 9600

def upload_code():
    selected_folder = folder_combo.get()
    selected_com = com_combo.get()
    try:
        arduino = Serial(selected_com, baud_rate, timeout=1)
        time.sleep(2)
        
        # Reset the Arduino
        arduino.setDTR(False)
        time.sleep(1)
        arduino.setDTR(True)
        
        # The code file is in the same directory as the script
        script_dir = os.path.dirname(__file__)
        code_file = os.path.join(script_dir, selected_folder, f'{selected_folder}.ino')
        with open(code_file, 'r') as file:
            code = file.read()
        
        arduino.write(code.encode())
        time.sleep(2)
        arduino.close()
        
        messagebox.showinfo("Success", f"Mode {selected_folder[-1]} applied successfully!")
    except Exception as e:
        messagebox.showerror("Error", f"Mode {selected_folder[-1]} failed: {e}")

# Create the main window
root = tk.Tk()
root.title("Arduino Code Uploader")
root.geometry("400x200")

# List of folder names
folders = ['ARGBfan1', 'ARGBfan2', 'ARGBfan3', 'ARGBfan4']

# List of COM ports (you can add more if needed)
com_ports = ['COM1', 'COM2', 'COM3', 'COM4']

# Create a dropdown menu for folders
folder_label = tk.Label(root, text="Select a folder:")
folder_label.pack(pady=5)
folder_combo = ttk.Combobox(root, values=folders)
folder_combo.set("ARGBfan1")  # Set default selection
folder_combo.pack(pady=5)

# Create a dropdown menu for COM ports
com_label = tk.Label(root, text="Select a COM port:")
com_label.pack(pady=5)
com_combo = ttk.Combobox(root, values=com_ports)
com_combo.set("COM3")  # Set default selection
com_combo.pack(pady=5)

# Create an upload button
upload_button = tk.Button(root, text="Upload Code", command=upload_code)
upload_button.pack(pady=20)

# Run the GUI event loop
root.mainloop()