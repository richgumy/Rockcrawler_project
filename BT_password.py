import bluetooth, subprocess
nearby_devices = bluetooth.discover_devices(duration=4,lookup_names=True,
                                                      flush_cache=True, lookup_class=False)
name = name      # Device name
addr = addr      # Device Address
port = 1         # RFCOMM port
passkey = "1111" # passkey of the device you want to connect

# kill any "bluetooth-agent" process that is already running
subprocess.call("kill -9 `pidof bluetooth-agent`",shell=True)

# Start a new "bluetooth-agent" process where XXXX is the passkey
status = subprocess.call("bluetooth-agent " + passkey + " &",shell=True)

# Now, connect in the same way as always with PyBlueZ
try:
    s = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
    s.connect((addr,port))
except bluetooth.btcommon.BluetoothError as err:
    # Error handler
    pass
