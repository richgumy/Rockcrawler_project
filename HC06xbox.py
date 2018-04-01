"""Connect to HC-06 module"""

from __future__ import print_function
import bluetooth, subprocess
import xbox
import time

__author__ = 'Richie E'
__date__ = 'May 2017'

but_delay = 0.15
bt_buf_size = 128

# Format floating point number to string format -x.xxx
def fmtFloat(n):
	return '{:6.3f}'.format(n)

def main():



	last_button_push = ''
	cmd_state = False
	mac_address = '00:21:13:00:83:9B' # HC-06 BT module
	print("BT connection attempt...")
	# try:
	s = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
	connect = s.connect((mac_address, 1))
	print("this is it")
	# except bluetooth.btcommon.BluetoothError as err:
	#     # Error handler
	#     print("failed..")
	#     pass
	joy = xbox.Joystick()

	while not joy.connected():
		print('Not connected')

	print('CONNECTED!')


	while (joy.connected() or not joy.Back()):

		# if joy.Start():
		# 	s.send('...' + chr(13))
        #
		# if joy.A():
		# 	s.send('p' + chr(13))
		# 	time.sleep(but_delay)
        #
		# if joy.B():
		# 	s.send('b' + chr(13))
		# 	time.sleep(but_delay)
        #
		# if joy.Y():
		# 	s.send('y' + chr(13))
		# 	time.sleep(but_delay)
        #
		# if joy.dpadDown():
		# 	print('Down')
		# 	s.send('s' + chr(13))
		# 	time.sleep(but_delay)
        #
		# if joy.dpadUp():
		# 	print('Up')
		# 	s.send('w' + chr(13))
		# 	time.sleep(but_delay)
        #
		# if joy.dpadLeft():
		# 	print('Left')
		# 	s.send('a' + chr(13))
		# 	time.sleep(but_delay)
        #
		# if joy.dpadRight():
		# 	print('Right')
		# 	s.send('d' + chr(13))
		# 	time.sleep(but_delay)

		if joy.rightTrigger():
			print('Fwd')
			s.send('w' + str(joy.rightTrigger()) + chr(13))
			time.sleep(but_delay)

		if joy.leftTrigger():
			print('Rev')
			s.send('s' + str(joy.leftTrigger()) + chr(13))
			time.sleep(but_delay)

		if joy.leftStick():
			x,y = joy.leftStick()
			if x > 0:
				s.send('d' + str(x/2) + chr(13))
				time.sleep(but_delay)
			elif x < 0:
				x = x * -1
				s.send('a' + str(x/2) + chr(13))
				time.sleep(but_delay)

	s.disconnect()


if __name__ == '__main__':
	main()
