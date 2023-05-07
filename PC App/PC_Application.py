import os
import sys
import serial
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
import datetime
import json
from serial.tools import list_ports

def get_available_ports():
    ports = list_ports.comports()
    return [port.device for port in ports]

class CableData:
    def __init__(self, cable_id, length, cable_gauge):
        self.cable_id = cable_id
        self.length = length
        self.cable_gauge = cable_gauge

    def to_string(self):
        return "Cable ID: {}, Length: {}, Cable Gauge: {}".format(self.cable_id, self.length, self.cable_gauge)

class CableDataWidget(QWidget):
    def __init__(self, parent):
        super().__init__()

        self.parent = parent
        self.initUI()

    def initUI(self):
        self.cable_id_edit = QLineEdit(self)
        self.cable_id_edit.setPlaceholderText('Cable ID')
        self.length_edit = QLineEdit(self)
        self.length_edit.setPlaceholderText('Length')
        self.cable_gauge_edit = QLineEdit(self)
        self.cable_gauge_edit.setPlaceholderText('Cable Gauge')

        save_button = QPushButton('Save', self)
        save_button.clicked.connect(self.save_data)

        layout = QVBoxLayout()
        layout.addWidget(self.cable_id_edit)
        layout.addWidget(self.length_edit)
        layout.addWidget(self.cable_gauge_edit)
        layout.addWidget(save_button)
        self.setLayout(layout)

    def save_data(self):
        cable_id = self.cable_id_edit.text()
        length = self.length_edit.text()
        cable_gauge = self.cable_gauge_edit.text()

        if cable_id and length and cable_gauge:
            data = CableData(cable_id, length, cable_gauge)
            self.parent.cable_data.append(data)
            self.parent.update_cable_data_list()
            self.parent.save_cable_data()  # Save cable data to the JSON file when new data is added
            self.cable_id_edit.clear()
            self.length_edit.clear()
            self.cable_gauge_edit.clear()
        else:
            QMessageBox.warning(self, "Warning", "Please fill in all fields.")

class SettingsWindow(QWidget):
    def __init__(self, parent):
        super().__init__()

        self.parent = parent
        self.initUI()

    def initUI(self):
        # Set up file path input field
        self.filePathLabel = QLabel("Enter filepath for machine log as follows: C:\\User\\Documents\\filename", self)
        self.filePathEdit = QLineEdit(self)
        self.filePathEdit.setText(self.parent.filePath)
        self.filePathEdit.setPlaceholderText('File Path')
        self.filePathEdit.editingFinished.connect(self.filePathEdited)

        # Set up back button
        backButton = QPushButton('Back', self)
        backButton.clicked.connect(self.backButtonClicked)

        vbox = QVBoxLayout()
        vbox.addWidget(self.filePathLabel)
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
        self.cable_data = []
        self.current_cable_data_index = -1
        self.initUI()
        self.initLogFile()
        self.load_cable_data()  # Load cable data from the JSON file when the application is launched

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
        menuButton = QPushButton('Settings', self)
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

        # Set up cable data list display
        self.cableDataList = QListWidget(self)
        self.cableDataList.itemClicked.connect(self.cable_data_list_item_clicked)

        # Set up cable data input widget
        self.cableDataInput = CableDataWidget(self)

        # Set up next and previous buttons
        prevButton = QPushButton('Previous', self)
        prevButton.clicked.connect(self.prevButtonClicked)
        nextButton = QPushButton('Next', self)
        nextButton.clicked.connect(self.nextButtonClicked)

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
        vbox.addWidget(QLabel('Cable Data', self))
        vbox.addWidget(self.cableDataList)
        vbox.addWidget(self.cableDataInput)
        hbox2 = QHBoxLayout()
        hbox2.addWidget(prevButton)
        hbox2.addWidget(nextButton)
        vbox.addLayout(hbox2)
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
        self.settings_window.setGeometry(self.geometry())  # Set menu window width to the same as main window
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
        try:
            if self.serial and self.serial.in_waiting > 0:
                text = self.serial.readline().decode().strip()
                self.textDisplay.append(text)

                # Write log entry to file
                with open(self.filePath, 'a') as f:
                    f.write(text + '\n')
        except serial.serialutil.SerialException as e:
            QMessageBox.warning(self, "Warning", "The serial connection has been lost. Please check the connection.")
            if self.serial:
                self.serial.close()
            self.serial = None

    def update_cable_data_list(self):
        self.cableDataList.clear()
        for data in self.cable_data:
            self.cableDataList.addItem(data.to_string())

    def cable_data_list_item_clicked(self, item):
        index = self.cableDataList.row(item)
        self.current_cable_data_index = index

    def prevButtonClicked(self):
        if self.current_cable_data_index > 0:
            self.current_cable_data_index -= 1
            self.cableDataList.setCurrentRow(self.current_cable_data_index)

    def nextButtonClicked(self):
        if self.current_cable_data_index < len(self.cable_data) - 1:
            self.current_cable_data_index += 1
            self.cableDataList.setCurrentRow(self.current_cable_data_index)

    def save_cable_data(self):
        try:
            with open('cable_data.json', 'w') as f:
                json_data = [data.__dict__ for data in self.cable_data]
                json.dump(json_data, f)
        except Exception as e:
            QMessageBox.warning(self, "Warning", "Unable to save cable data to JSON file.")

    def load_cable_data(self):
        try:
            with open('cable_data.json', 'r') as f:
                json_data = json.load(f)
                self.cable_data = [CableData(**data) for data in json_data]
                self.update_cable_data_list()
        except FileNotFoundError:
            pass
        except Exception as e:
            QMessageBox.warning(self, "Warning", "Unable to load cable data from JSON file.")


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
    timer.start(1000)  # Update date and time label every second
    serialTimer = QTimer()
    serialTimer.timeout.connect(ex.readSerial)
    serialTimer.start(100)  # Read serial input every 100ms

    # Save file path to settings
    QSettings('MyCompany', 'MyApp').setValue('filePath', filePath)

    sys.exit(app.exec_())
