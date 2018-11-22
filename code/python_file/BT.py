from time import sleep
import serial
# these codes are for bluetooth
# hint: please check the function "sleep". how does it work?

class bluetooth:
    def __init__(self):
        self.ser = serial.Serial()

    def do_connect(self,port):
        self.ser.close()
        #TODO: Connect the port with Serial. A clear description for exception may be helpful.
        if port == "quit" :
            print("BYBYE  HAHAHAHAHA!!")
            return False
        else :
            print("HELLO  HAHAHAHAHA!!")    
            ## Add condition!
            self.ser = serial.Serial(port, 9600, timeout = 2)
            return True

    def disconnect(self):
        self.ser.close()

    def SerialWrite(self,output):
        send = output.encode("utf-8")
        self.ser.write(send)

    def SerialReadString(self):
        #TODO: Get the information from Bluetooth. Notice that the return type should be transformed into hex. 
        waiting = self.ser.in_waiting
        if waiting > 0:
            rv = self.ser.read(1).decode("utf-8")
            # print(rv) #use for debug
            # reset_input_buffer()
            return rv
        return ""

    def SerialReadByte(self):
        #TODO: Get the UID from bytes. Notice that the return type should be transformed into hex. 
        return 0


