from time import sleep
import serial

class bluetooth:
    def __init__(self):
        self.ser = serial.Serial()

    def do_connect(self,port):
        self.ser.close()
        print("Connecting...")
        try:
            self.ser = serial.Serial(port,9600,timeout=2)
            print("connect success")
            print("")
        except serial.serialutil.SerialException:
            print("fail to connect")
            print("")
            return False
        return True

    def disconnect(self):
        self.ser.close()

    def SerialWrite(self,output):
        send = output.encode("utf-8")
        self.ser.write(send)

    def SerialReadString(self):
        sleep(0.01)
        waiting = self.ser.inWaiting()
        rv = [chr(c) for c in self.ser.read(waiting)]
        #print(rv)
        #rv = self.ser.readline().decode("utf-8")
        if(waiting != 0):
            print("".join(rv))
            self.ser.flushInput()
            return "".join(rv)
        else:
            return ""

    def SerialReadByte(self):
        sleep(0.05)
        waiting = self.ser.inWaiting()
        rv = self.ser.read(waiting)
        #rv = self.ser.readline()
        if(rv):
            UID = hex(int.from_bytes(rv, byteorder='big', signed=False))
            #print(UID)
            print("")
            self.ser.flushInput()
            return UID
        else:
            return 0


