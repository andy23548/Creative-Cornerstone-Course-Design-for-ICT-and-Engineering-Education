import BT
import maze
import score

class interface:
    def __init__(self):
        print("")
        print("Arduino Bluetooth Connect Program.")
        print("")
        self.ser = BT.bluetooth()
        port = input("PC bluetooth port name: ")
        while(not self.ser.do_connect(port)):
            if(port == "quit"):
                self.ser.disconnect()
                quit()
            port = input("PC bluetooth port name: ")
        input("Press enter to start.")
        self.ser.SerialWrite('s')

    def cmd_input(self):
        read_in = input(">>> ").split()
        if (len(read_in)>2):
            print("Invalid Command!!")
            print("")
            return "NULL",""
    
        command = read_in[0]
        if (len(read_in) == 2):
            opt = read_in[1]
        else:
            opt = ""

        return command,opt

    def exeCmd(self,cmd,opt):
        if(cmd == "quit"):
            self.ser.disconnect()
            quit()
        elif(cmd == "turn"):
            if(opt == 'F'):
                self.ser.SerialWrite('f')
            elif(opt == 'B'):
                self.ser.SerialWrite('b')
            elif(opt == 'R'):
                self.ser.SerialWrite('r')
            elif(opt == 'L'):
                self.ser.SerialWrite('l')
            elif(opt == "S"):
                self.ser.SerialWrite('h')
        else:
            print("Please type \"connect\" first.")
            print("")

    def wait_for_corner(self):
        return self.ser.SerialReadByte()

    def send_action(self,dirc):
        if(dirc == maze.Action.ADVANCE):
            self.ser.SerialWrite('f')
        elif(dirc == maze.Action.U_TURN):
            self.ser.SerialWrite('b')
        elif(dirc == maze.Action.TURN_RIGHT):
            self.ser.SerialWrite('r')
        elif(dirc == maze.Action.TURN_LEFT):
            self.ser.SerialWrite('l')
        elif(dirc == maze.Action.HALT):
            self.ser.SerialWrite('h')

    def end_process(self):
        self.ser.SerialWrite('e')
        self.ser.disconnect()


