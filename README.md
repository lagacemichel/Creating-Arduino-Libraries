# Creating Arduino Libraries
This repository demonstrates the directory structure and artifacts required
to create an Arduino library. The main directory contains four files and
three subdirectories. These four files describe the purpose, properties,
and general information about the Arduino library:

- The ``library.properties`` file describes the library and its properties.
- The ``keywords.txt`` file lists the keywords highlighted in the Arduino IDE
  when the library is included in a project.
- The ``README.md`` file describes the purpose of the library and its content.
- The ``LICENSE.txt`` file contains the license associated with the project.

The three subdirectories contain the Arduino code for the library, examples,
and reference materials:

- The ``/src`` subdirectory contains the library components, such as C++ header
  and implementation files.
- The ``/examples`` subdirectory contains example implementations that demonstrate
  how to use the library.
- The ``/extras`` subdirectory contains reference materials and documentation
  related to the content and purpose of the library.

To illustrate how to create an Arduino library, I developed a DHT22 temperature
and humidity sensor monitoring library. The main directory contains the
``LICENSE.txt`` file and this ``README.md`` file. It also includes the ``keywords.txt``
and ``library.properties`` files, which identify IDE keywords for the DHT22 sensor
library and specify the library's properties.

The DHT22 sensor library's ``/src`` subdirectory contains the header file, ``DHT22.h``,
which includes a class description for the DHT22 sensor library, and the
implementation file, ``DHT22.cpp``, which contains the sensor library code. The
``/examples`` subdirectory contains an Arduino sketch, ``DHT22SensorLibraryTest.ino``,
that demonstrates how to use the DHT22 sensor library. The ``/extras`` subdirectory
includes a PDF file containing a previous Mike's Electroshack post discussing
how to use of the DHT22 sensor to provide relative humidity and temperature
readings.

The blog post can be found at https://lagacemichel.com.
