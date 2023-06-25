# OpenCut

OpenCut is an open-source project aimed at developing an automated cable processing machine. It is designed to measure, cut cables to length, and print a cable ID directly onto the cable. Currently, the project is in its infancy, and only a prototype machine has been constructed. However, the project has the vision to continue development and cultivate a flexible and innovative solution to automated cable processing for wiring looms and harnesses. The intent is to foster a community to contribute to and further the development of the project.

The project includes two main components: MAS (Manufacturing Automation Software) and Machine Software.

## Directory Structure

The repository is divided into two main directories: `OpenCut Src` and `OpenCut Docs`.

### Source Code

The `OpenCut Src` directory contains the source code of the project and is divided into two sub-directories:

- `OpenCut MAS Software`: This directory contains the code for the MAS component of the OpenCut project. The MAS is the interface between the operator and the machine, allowing data about different cable types to be added, stored, modified, etc. It also saves machine parameters. It is designed to be executed on a desktop computer but can also be run on an SBC like a Raspberry Pi.
- `OpenCut Machine Software`: This directory contains the code for the Machine software component of the OpenCut project. This software is to be flashed onto the microcontroller embedded in the OpenCut machine.

### Documentation

The `OpenCut Docs` directory contains various forms of documentation and resources related to the project, including:

- `3D Printing Files`: This directory contains files related to 3D printing parts for the OpenCut project.
- `Functional Flow Charts`: This directory contains flowcharts that explain the functional flow of the OpenCut hardware and software.
- `Laser Cutting Files`: This directory contains files related to laser cutting parts for the OpenCut project.
- `Schematics`: This directory contains schematics related to the OpenCut project.
