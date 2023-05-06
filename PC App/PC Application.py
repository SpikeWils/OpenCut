import sys
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
import serial
import datetime

# Set up serial communication with Arduino
ser = serial.Serial('COM3', 9600) # Replace 'COM3' with your serial port name and 9600 with your baud rate

class ArduinoController(QWidget):
    def __init__(self):
        super().__init__()
        
        self.initUI()
        
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
        now = datetime.datetime.now()
        dateTimeLabel = QLabel(now.strftime('%Y-%m-%d %H:%M:%S'), self)
        dateTimeLabel.setAlignment(Qt.AlignRight)
        
        # Set up layout
        vbox = QVBoxLayout()
        vbox.addWidget(startButton)
        vbox.addWidget(pauseButton)
        vbox.addWidget(menuButton)
        vbox.addWidget(self.textEdit)
        vbox.addWidget(self.textDisplay)
        vbox.addWidget(dateTimeLabel)
        
        self.setLayout(vbox)
        self.setGeometry(300, 300, 300, 250)
        self.setWindowTitle('Arduino Controller')
        self.show()
        
    def startButtonClicked(self):
        # Send text in the text input field to Arduino
        text = self.textEdit.toPlainText()
        ser.write(text.encode())
        
    def pauseButtonClicked(self):
        # Send 'pause' command to Arduino
        ser.write(b'pause')
        
    def menuButtonClicked(self):
        # Send 'menu' command to Arduino
        ser.write(b'menu')
        
    def updateDateTime(self):
        # Update date and time label
        now = datetime.datetime.now()
        self.dateTimeLabel.setText(now.strftime('%Y-%m-%d %H:%M:%S'))
        
    def readSerial(self):
        # Read text sent by Arduino and display it in the text display window
        if ser.in_waiting > 0:
            text = ser.readline().decode().strip()
            self.textDisplay.append(text)
            
    def closeEvent(self, event):
        # Close serial communication with Arduino when the GUI is closed
        ser.close()
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
