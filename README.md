# Creating Arduino Libraries
Directory structure containing all atefacts required to create an Arduino
library. The main directory contains the `library.properties` file that
describes the library and its properties, the `keywords.txt` file that lists
the keywords that will be highlighted by the Arduino IDE, the `README.md`
file, this file, that describes the content of the Github repository and the
`LICENSE.txt` file that contains the license associated to the project.

The `/src` subdirectory contains the DHT22 sensor library components: a header
file, `DHT22.h`, containing a class description for the DHT22 sensor library
and an implementation file, `DHT22.cpp`, containing the sensor library code.
the `/examples` subdirectory contains an Arduino sketch demonstrating the use
of the DHT22 sensor library. Finally, the `extras` subdirectory, has a PDF
file containing a previous Mike's Electroshack post on the use of the DHT22
sensor on providing relative humidity and temperature readings.
