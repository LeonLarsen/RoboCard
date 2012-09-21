# Python script for controlling frobit using the accelerometer of an Android phone
# Author: Morten Larsen

# to use the script:
#    get http://code.google.com/p/android-scripting/downloads/detail?name=PythonForAndroid_r4.apk&can=2&q=
#    start Python for android
#    choose install
#    get http://code.google.com/p/android-scripting/downloads/detail?name=sl4a_r6.apk&can=2&q=
#    start sl4a
#    select script to run

# put this file in sdcard/sl4a/scripts

import android
import math
import time

droid = android.Android()

droid.toggleBluetoothState(True)
droid.startSensingTimed(2,100)

if droid.bluetoothConnect('00001101-0000-1000-8000-00805F9B34FB'):
    while True:
        try:
            xyz = droid.sensorsReadAccelerometer().result
            roll = math.atan2(xyz[0], math.sqrt(math.pow(xyz[1], 2) + math.pow(xyz[2], 2))) / (math.pi/2);
            pitch  = math.atan2(xyz[1], math.sqrt(math.pow(xyz[0], 2) + math.pow(xyz[2], 2))) / (math.pi/2);
            
            print "Raw"
            print pitch, roll
            
            pitch = pitch * 100;
            roll = roll *50;
            l = pitch - roll
            r = pitch + roll
            
            print "Cmd"
            print l,r
            
            droid.bluetoothWrite('$ANDCR,%d,%d*00\n'%(l*10,r*10))
            
            time.sleep(0.1)
        except:
            droid.makeToast("Failed")
            break
else:
    droid.makeToast("Could not connect")