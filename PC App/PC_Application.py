import sys
import serial
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
import datetime
from serial.tools import list_ports

def find_arduino_port():
    ports = list_ports.comports()
    for port in ports:
        if "Arduino" in port.description or "USB Serial Device" in port.description:
            return port.device
    return None

class SettingsWindow(QWidget):
    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):
        backButton = QPushButton('Back', self)
        backButton.clicked.connect(self.backButtonClicked)

        vbox = QVBoxLayout()
        vbox.addWidget(backButton)
        self.setLayout(vbox)
        self.setWindowTitle('Settings')

    def backButtonClicked(self):
        self.close()

class ArduinoController(QWidget):
    def __init__(self):
        super().__init__()

        self.initUI()
        self.serial = None

    def initUI(self):
        # Set up start, pause and menu buttons
        startButton = QPushButton('Start', self)
        startButton.setStyleSheet("background-color: green")
        startButton.clicked.connect(self.startButtonClicked)
        pauseButton = QPushButton('Pause', self)
        pauseButton.setStyleSheet("background-color: orange")
        pauseButton.clicked.connect(self.pauseButtonClicked)
        menuButton = QPushButton('Menu', self)
        menuButton.clicked.connect(self.menuButtonClicked)

        # Set up text input field
        self.textEdit = QTextEdit(self)
        self.textEdit.setPlaceholderText('Enter cable I.D')

        # Set up text display window
        self.messageLabel = QLabel('Messages', self)
        self.textDisplay = QTextEdit(self)
        self.textDisplay.setReadOnly(True)

        # Set up date and time label
        self.dateTimeLabel = QLabel('', self)
        self.updateDateTime()
        self.dateTimeLabel.setAlignment(Qt.AlignRight)

        # Set up layout
        vbox = QVBoxLayout()
        vbox.addWidget(startButton)
        vbox.addWidget(pauseButton)
        vbox.addWidget(menuButton)
        vbox.addWidget(self.messageLabel)
        vbox.addWidget(self.textDisplay)
        vbox.addWidget(self.textEdit)
        vbox.addWidget(self.dateTimeLabel)

        self.setLayout(vbox)
        self.setGeometry(300, 300, 300, 250)
        self.setWindowTitle('Cable Cutter Interface')
        self.show()

    def startButtonClicked(self):
        # Open serial communication with Arduino and send text in the text input field
        if not self.serial:
            arduino_port = find_arduino_port()
            if arduino_port:
                self.serial = serial.Serial(arduino_port, 9600)
                text = self.textEdit.toPlainText()
                self.serial.write(text.encode())
            else:
                QMessageBox.warning(self, "Warning", "Could not find Arduino COM port.")

    def pauseButtonClicked(self):
        # Send 'pause' command to Arduino
        if self.serial:
            self.serial.write(b'pause')

    def menuButtonClicked(self):
        self.settings_window = SettingsWindow()
        self.settings_window.show()

    def updateDateTime(self):
        # Update date and time label
        now = datetime.datetime.now()
        self.dateTimeLabel.setText('Date: ' + now.strftime('%d/%m/%Y') + ' Time: ' + now.strftime('%H:%M:%S'))

    def readSerial(self):
        # Read text sent by Arduino and display it in the text display window
        if self.serial and self.serial.in_waiting > 0:
            text = self.serial.readline().decode().strip()
            self.textDisplay.append(text)

    def closeEvent(self, event):
        # Close serial communication with Arduino when the GUI is closed
        if self.serial:

            self.serial.close()
        event.accept()

if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = ArduinoController()
    timer = QTimer()
    timer.timeout.connect(ex.updateDateTime)
    timer.start(1000) # Update date and time label every second
    serialTimer = QTimer()
    serialTimer.timeout.connect(ex.readSerial)
    serialTimer.start(100) # Read serial input every 100ms
    sys.exit(app.exec_())
