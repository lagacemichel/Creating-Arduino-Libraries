# Creating Arduino Libraries
This repository demonstrates the directory structure and artefacts required
to create an Arduino library. The main directory hosts four files and three
subdirectories. The four files describe the purpose, properties, and general
informationthe about the Arduino library. The'library.properties' file
describes the library and its properties. The 'keywords.txt' file lists the
keywords highlighted in the Arduino IDE when the library is included in a
project. The 'README.md' file, this file, describes the purpose of the library
and its content. The 'LICENSE.txt' file that contains the license associated
with the project.

As stated above, the Arduino library has three subdirectories. The '/src'
subdirectory contains the library components: C++ header and implementation
files. the '/examples' subdirectory contains example implementations using the
library. Finally, the '/extras' subdirectory, contains reference material and
documentation pertaining to the content and purpose of the library. 

As an example, this Arduino library contains a DHT22 temperature and humidity
sensor monitoring implementation. The '/src' subdirectory holds header file
'DHT22.h', containing a class description for the DHT22 sensor library and an
implementation file, 'DHT22.cpp', containing the sensor library code. The
'/examples' subdirectory holds an Arduino sketch, 'DHT22SensorLibraryTest',
demonstrating the use of the DHT22 sensor library. The 'extras' subdirectory
holds a PDF file containing a previous Mike's Electroshack post on the use of
the DHT22 sensor to provide relative humidity and temperature readings.
