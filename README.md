# dll-shared-memory
Simple project to show possible problems when using shared memory structures between DLL and DLL host.

Note: this projects shows how *not* to do it. It is an abstract version of propietary code and is intended to serve as an example of how interprocess communication between a DLL and a host should better not be designed. The task derived from this is to create the same functionality with modern means. 

For the sake of simplicity no threads are used.

# Features

* DLL can request user input from host
* DLL can request data from database with timeout
* DLL can send logging data to host
* DLL can send processed data to host
* DLL has a main "message loop" where data is processed
* Host can "shutdown" DLL in a safe way

# Compilers / IDEs

Tested with
* CLion (CMake based, gcc)
  * .\CMakeLists.txt
* VS 2019 (Community Edition, msvc)
  * projectfiles\dll-shared-memory.sln
* C++ Builder 10.3 (Community Edition, bcc32c (clang based))
  * projectfiles\shared-memory.groupproj

# Task and constraints in the context of a Bachelor thesis

## Constraints

* Code must compile with bcc32c
* Host and DLL run on the same machine
* The minimum supported C++ standard is C++11

## Task

* Which problems could arise by using the shared memory interface?
  * Is it possible to use different compilers for DLL and host?
  * What are possible alternatives to a shared memory interface?
* Find solutions that are C++ compiler independent (the host could be created with bcc32c and the DLL with mscvc)

## Optional tasks

* Create a host in a different programming language (Python, Ruby, Java, etc.)
* Allow data exchange over the network
  * of course this implies the use of two "host" - processes (in contrast to the original "host loads DLL" solution)

