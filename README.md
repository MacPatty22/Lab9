# Lab 9 - System Calls

**Author:** Mac Patterson
**Course:** CPE-2600 Systems Programming
**Assignment:** Lab 9 - System Calls

## Overview
This lab explores commonly used POSIX system calls in three categories:
information maintenance, process control, and file management.

## Programs

|Program|Description 
|-------|-----------|
| info  | Prints the current time (ns), network name, OS name/release/version, hardware type, CPU count, and total/free memory in bytes. |
| pinfo | Prints the priority and scheduling policy of a process. Uses the current process if no PID is given. |
| pmod  | Reduces its own priority by 10, sleeps for 1,837,272,638 ns, then prints a goodbye message. |
| finfo | Prints the type, permissions, owner UID, size in bytes, and last modification time of a file. |

## Building
make        # builds all four programs
make clean  # removes object files and executables


## Usage
./info
./pinfo [pid]
./pmod
./finfo <filename>

