import os
import sys
import serial
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
import datetime
from serial.tools import list_ports

def get_available_ports():
    ports = list_ports.comports()
    return [port.device for port in ports]


class SettingsWindow(QWidget):
    def __init__(self, parent):
        super().__init__()

        self.parent = parent
        self.initUI()

    def initUI(self):
        # Set up file path input field
        self.filePathEdit = QLineEdit(self)
        self.filePathEdit.setText(self.parent.filePath)
        self.filePathEdit.setPlaceholderText('File Path')
        self.filePathEdit.editingFinished.connect(self.filePathEdited)

        # Set up back button
        backButton = QPushButton('Back', self)
        backButton.clicked.connect(self.backButtonClicked)

        vbox = QVBoxLayout()
        vbox.addWidget(self.filePathEdit)
        vbox.addWidget(backButton)
        self.setLayout(vbox)
        self.setWindowTitle('Settings')

    def backButtonClicked(self):
        self.close()

    def filePathEdited(self):
        self.parent.filePath = self.filePathEdit.text()
        self.parent.initLogFile()

class ArduinoController(QWidget):
    def __init__(self):
        super().__init__()

        self.filePath = 'machine_log_{}.txt'.format(datetime.datetime.now().strftime('%Y-%m-%d'))
        self.serial = None

        self.initUI()
        self.initLogFile()

    def initUI(self):
        # Set up port selection drop-down menu and connect button
        self.portSelector = QComboBox(self)
        self.portSelector.addItems(get_available_ports())
        connectButton = QPushButton('Connect', self)
        connectButton.clicked.connect(self.connectButtonClicked)

        # Set up pause and resume buttons
        pauseButton = QPushButton('Pause Machine', self)
        pauseButton.setStyleSheet("background-color: orange")
        pauseButton.clicked.connect(self.pauseButtonClicked)
        resumeButton = QPushButton('Resume Machine', self)
        resumeButton.setStyleSheet("background-color: green")
        resumeButton.clicked.connect(self.resumeButtonClicked)

        # Set up menu button
        menuButton = QPushButton('Menu', self)
        menuButton.clicked.connect(self.menuButtonClicked)

        # Set up text input field
        self.textEdit = QLineEdit(self)
        self.textEdit.setPlaceholderText('Commands')
        regex = QRegExp("[A-Za-z0-9.,-]*")
        validator = QRegExpValidator(regex)
        self.textEdit.setValidator(validator)

        # Set up execute button
        executeButton = QPushButton('Execute', self)
        executeButton.clicked.connect(self.executeButtonClicked)

        # Set up text display window
        self.messageLabel = QLabel('Event Log', self)
        self.textDisplay = QTextEdit(self)
        self.textDisplay.setReadOnly(True)

        # Set up date and time label
        self.dateTimeLabel = QLabel('', self)
        self.updateDateTime()
        self.dateTimeLabel.setAlignment(Qt.AlignRight)

        # Set up layout
        vbox = QVBoxLayout()
        hbox = QHBoxLayout()
        hbox.addWidget(self.portSelector)
        hbox.addWidget(connectButton)
        vbox.addLayout(hbox)
        vbox.addWidget(pauseButton)
        vbox.addWidget(resumeButton)
        vbox.addWidget(menuButton)
        vbox.addWidget(self.messageLabel)
        vbox.addWidget(self.textDisplay)
        vbox.addWidget(self.textEdit)
        vbox.addWidget(executeButton)
        vbox.addWidget(self.dateTimeLabel)

        self.setLayout(vbox)
        self.setGeometry(300, 300, 300, 250)
        self.setWindowTitle('Cable Cutter Interface')
        self.show()

    def initLogFile(self):
        # Create log file and write header
        try:
            with open(self.filePath, 'x') as f:
                f.write('Event Log\n\n')
        except FileExistsError:
            pass

    def connectButtonClicked(self):
        # Open serial communication with Arduino
        if not self.serial:
            arduino_port = self.portSelector.currentText()
            if arduino_port:
                self.serial = serial.Serial(arduino_port, 9600)
            else:
                QMessageBox.warning(self, "Warning", "Please select a valid port.")

    def pauseButtonClicked(self):
        # Send 'pause' command to Arduino
        if self.serial:
            self.serial.write(b'pause')

    def resumeButtonClicked(self):
        # Send 'resume' command to Arduino
        if self.serial:
            self.serial.write(b'resume')

    def menuButtonClicked(self):
        self.settings_window = SettingsWindow(self)
        self.settings_window.show()

    def executeButtonClicked(self):
        # Send text from the input field to the Arduino
        if self.serial:
            command = self.textEdit.text().encode()
            self.serial.write(command)

    def updateDateTime(self):
        # Update date and time label
        now = datetime.datetime.now()
        self.dateTimeLabel.setText('Date: ' + now.strftime('%d/%m/%Y') + ' Time: ' + now.strftime('%H:%M:%S'))

    def readSerial(self):
        # Read text sent by Arduino and display it in the text display window
        if self.serial and self.serial.in_waiting > 0:
            text = self.serial.readline().decode().strip()
            self.textDisplay.append(text)

            # Write log entry to file
            with open(self.filePath, 'a') as f:
                f.write(text + '\n')

    def closeEvent(self, event):
        # Close serial communication with Arduino when the GUI is closed
        if self.serial:
            self.serial.close()
        event.accept()

if __name__ == '__main__':
    app = QApplication(sys.argv)

    # Load file path from settings
    filePath = os.path.abspath('machine_log_{}.txt'.format(datetime.datetime.now().strftime('%Y-%m-%d')))
    settingsFilePath = QSettings('MyCompany', 'MyApp').value('filePath')
    if settingsFilePath:
        filePath = settingsFilePath

    ex = ArduinoController()
    timer = QTimer()
    timer.timeout.connect(ex.updateDateTime)
    timer.start(1000) # Update date and time label every second
    serialTimer = QTimer()
    serialTimer.timeout.connect(ex.readSerial)
    serialTimer.start(100) # Read serial input every 100ms

    # Save file path to settings
    QSettings('MyCompany', 'MyApp').setValue('filePath', filePath)

    sys.exit(app.exec_())
