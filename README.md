# AlgoShield2_Reference

The purspose of this repo is to show how AlgoShield library can be integrated and used.

Repo consists of several folders:
- api - folder for Algoshield API header files which should be provided together with library itself
- lib - folder for Algoshield library file
- scripts - folder which contains CMake compiling scripts
- src - reference source code

Reference source code folder contains following folders:
- app - folder with example applications for the library usage. It can be used as a reference for the library usage.
- integration -  folder which contains examples of different integration options which are described in details below

Integration folder is used for the integration examples and provides following options:
- alloc - memory allocation integration - static or dynamic
- async - asynchronous integration API - tasks, queues, locks etc
- HAL - platform specific integration - different MCUs, PCs etc

To compile application please do following
1. ```cmake -B build```
2. ```cmake --build build --target <target_name>``` - where target_name is name oof application (i.e. "linux_async_dynamic")

For more information please read integration manual document.



