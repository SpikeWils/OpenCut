import sys
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
import datetime

class ArduinoController(QWidget):
    def __init__(self):
        super().__init__()

        self.initUI()
        self.serial = None

    def initUI(self):
        # Set up start, pause and menu buttons
        startButton = QPushButton('Start', self)
        startButton.clicked.connect(self.startButtonClicked)
        pauseButton = QPushButton('Pause', self)
        pauseButton.clicked.connect(self.pauseButtonClicked)
        menuButton = QPushButton('Menu', self)
        menuButton.clicked.connect(self.menuButtonClicked)

        # Set up text input field
        self.textEdit = QTextEdit(self)
        self.textEdit.setPlaceholderText('Type text to be sent to Arduino')

        # Set up text display window
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
        vbox.addWidget(self.textEdit)
        vbox.addWidget(self.textDisplay)
        vbox.addWidget(self.dateTimeLabel)

        self.setLayout(vbox)
        self.setGeometry(300, 300, 300, 250)
        self.setWindowTitle('Arduino Controller')
        self.show()

    def startButtonClicked(self):
        # Open serial communication with Arduino and send text in the text input field
        if not self.serial:
            self.serial = serial.Serial('COM5', 9600) # Replace 'COM3' with your serial port name and 9600 with your baud rate
        text = self.textEdit.toPlainText()
        self.serial.write(text.encode())

    def pauseButtonClicked(self):
        # Send 'pause' command to Arduino
        if self.serial:
            self.serial.write(b'pause')

    def menuButtonClicked(self):
        # Send 'menu' command to Arduino
        if self.serial:
            self.serial.write(b'menu')

    def updateDateTime(self):
        # Update date and time label
        now = datetime.datetime.now()
        self.dateTimeLabel.setText(now.strftime('%Y-%m-%d %H:%M:%S'))

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
