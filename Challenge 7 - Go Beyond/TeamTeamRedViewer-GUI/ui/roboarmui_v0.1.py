from PyQt5.QtCore import QObject, QThread, pyqtSignal
from PyQt5 import QtWidgets, QtGui
from PyQt5 import uic

import hunter

# import serial
from time import sleep

import paho.mqtt.client as mqtt

class UiMainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        """
        Initializes a QMainWindow from the .ui file and sets up the GUI.
        """
        QtWidgets.QMainWindow.__init__(self)
        self.ui = uic.loadUi('roboarmui_v0.1.ui', self)
        self.setWindowTitle("roboarmui_v0.1")
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap("WindowIcon.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.setWindowIcon(icon)

        self.textBrowserList = [self.textBrowserFWD_0, self.textBrowserREV_0,
                                self.textBrowserFWD_2, self.textBrowserREV_2,
                                self.textBrowserArm_0, self.textBrowserArm_2,
                                self.textBrowserServo,
                                self.textBrowserLogging]

        self.helper = MQTTHelper(self.textBrowserList, self.startSerialBtn, self.stopSerialBtn)

        # self.startSerialBtn.setEnabled(True)
        # self.stopSerialBtn.setEnabled(False)

        self.startSerialBtn.clicked.connect(self.helper.start_worker)
        self.stopSerialBtn.clicked.connect(self.helper.stop_worker)

class MQTTHelper:
    """
    TODO: write contract
    """
    def __init__(self, text_browser_list, start_btn, stop_btn):

        self.textBrowserList = text_browser_list

        self.start_btn = start_btn
        self.stop_btn = stop_btn

        for textBrowser in self.textBrowserList:
            textBrowser.insertPlainText("n/a")

        self.thread = None
        self.worker = None

    def report_pico_data(self, data):
        """
        TODO: write contract -- this feels so cursed beyond belief help

        Crazy thing, so the parameter, when the function is called, at least in PyQt5, it seems that
        you don't call the funcition like report_pico_data(data). The parameter is passed in through
        the signal the function is connected to. That's why in start_worker, it's:
            self.worker.picodata.connect(self.report_picodata)
                        ^ THIS IS THE SIGNAL WHICH IS PASSED INTO THE FUNCTION AS PARAMETER

        NONE OF THIS IS GOOD CODE AHAHAHAHAHAHHGHAHAH

        :param n:
        :return: none
        """
        index = 0
        for textBrowser in self.textBrowserList:
            # found = textBrowser.find("$$$")
            # print(f"test:{found}")
            if data.find("$$$") > -1 and index != len(self.textBrowserList) - 1:
                parsedata = data[3:]
                parsedata = parsedata.split(",")
                print(f"test:{parsedata}")
                for item in parsedata:
                    if item.find("L") > -1 and index == 0: # Appends to FWD_0
                        textBrowser.clear()
                        opposite = not(not(int(item[2:]))) # :))))))) HAHAHAHAHAHAHA
                        textBrowser.setText(str(opposite))
                    if item.find("L") > -1 and index == 1: # Appends to REV_0
                        textBrowser.clear()
                        opposite = not(int(item[2:]))
                        textBrowser.setText(str(opposite))

                    if item.find("R") > -1 and index == 2: # Appends to FWD_2
                        textBrowser.clear()
                        opposite = not(not(int(item[2:]))) # :))))))) HAHAHAHAHAHAHA
                        textBrowser.setText(str(opposite))
                    if item.find("R") > -1 and index == 3: # Appends to REV_2
                        textBrowser.clear()
                        opposite = not(int(item[2:]))
                        textBrowser.setText(str(opposite))

                    if item.find("A") > -1 and index == 4: # Appends to Arm_0
                        textBrowser.clear()
                        textBrowser.setText(item[2:])
                    if item.find("B") > -1 and index == 5: # Appends to Arm_1
                        textBrowser.clear()
                        textBrowser.setText(item[2:])
                    if item.find("S") > -1 and index == 6: # Appends to Servo
                        textBrowser.clear()
                        textBrowser.setText(item[2:])
            elif index == len(self.textBrowserList) - 1:
                textBrowser.append(f"{data}")
            index += 1

    def start_worker(self):
        """
        TODO: write contract
        :return:
        """
        print("calling start_worker")
        if self.worker is None:
            self.start_btn.setEnabled(False)
            self.stop_btn.setEnabled(True)
            print("starting thread!")
            self.thread = QThread()
            self.worker = Worker()

            self.worker.moveToThread(self.thread)

            self.thread.started.connect(self.worker.receive_sensor_data)

            self.worker.finished.connect(self.thread.quit)
            self.worker.finished.connect(self.worker.deleteLater)
            self.thread.finished.connect(self.thread.deleteLater)

            self.worker.picodata.connect(self.report_pico_data)

            self.thread.start()

            try:
                self.worker.setup_mqtt()
            except RuntimeError as e:
                print(str(e))

    def stop_worker(self):
        """
        TODO: write contract
        :return:
        """
        print("calling stop_worker")
        if self.worker is not None:
            self.start_btn.setEnabled(True)
            self.stop_btn.setEnabled(False)
            print("exiting thread!")
            self.worker.exit_worker()
            self.worker = None

class Worker(QObject):
    """
    TODO: write contract
    """
    alive = True
    finished = pyqtSignal()
    picodata = pyqtSignal(str)

    # MQTT code is borrowed from: https://github.com/eclipse/paho.mqtt.python/blob/master/examples/client_sub.py
    # The example file is "mqtttest.py"

    # If you want to use a specific client id, use
    # mqttc = mqtt.Client("client-id")
    # but note that the client id must be unique on the broker. Leaving the client
    # id parameter empty will generate a random id for you.
    mqttc = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)

    def setup_mqtt(self):
        print("setup_mqtt")
        try:
            # self.pico = serial.Serial("COM6", 115200)
            self.pico.write(b"join\n")
        except Exception as e:
            print(e)

    def disconnect(self):
        try:
            self.pico.write(b"quit\n")
        except Exception as e:
            print(e)

    def on_connect(self, mqttc, obj, flags, reason_code, properties):
        print("reason_code: " + str(reason_code))

    def on_message(self, mqttc, obj, msg):
        print(msg.topic + " " + str(msg.qos) + " " + str(msg.payload))

    def on_subscribe(self, mqttc, obj, mid, reason_code_list, properties):
        print("Subscribed: " + str(mid) + " " + str(reason_code_list))

    def on_log(self, mqttc, obj, level, string):
        print(string)

    def receive_sensor_data(self):
        while self.alive is True:
            try:
                incoming_data = self.pico.readline()
                incoming_data = str(incoming_data)[2:-5]
                print(f"from pico:{incoming_data}")
                self.picodata.emit(incoming_data)
                sleep(0.1)
            except RuntimeError as e:
                print(str(e))
            # else:
            #     print(f"from pico:{incoming_data}")
                # self.sensors_signal.emit(self.sensors)
        self.finished.emit()

    def exit_worker(self):
        """
        TODO: write contract
        :return:
        """
        print("exiting worker and disconnecting attached pico's BLE!")
        self.disconnect() # Sends signal to Pico to disconnect BLE
        self.alive = False
        self.finished.emit()

if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    mainWindow = UiMainWindow()
    mainWindow.show()
    sys.exit(app.exec_())