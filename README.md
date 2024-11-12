# BugFoundry

## About
BugFoundry, a bug-tracking software, was developed in SFU CMPT 276 Software Engineering course  
in the 2024 Summer semester by 4 computing science students.  

## Developers
Sanchit Jain  
Seoyoung Kim  
Jason Lee  
Nicholas Susanto  

## Environment
BugFoundry supports Linux and Windows operating system.  
Initially, BugFoundry was developed and designed to operate on Windows 11 by the Visual Studio Code terminal,  
as all the members were familiar with that particular environment.  

## How to Run System - Linux
1. Download the repository and unzip the file
2. Open the terminal
3. Navigate to the file in the terminal
4. In the file, create a new directory called "build":
   ```mkdir build```
6. Move into the "build" directory and call command:
   ```cmake ../```
8. To compile, call command:
   ```cmake --build .```
10. To run the system, call command:
    ```./system```

## How to Run System - Windows
1. Download the repository and unzip the file
2. Open Visual Studio Code (VS Code)
3. Open the downloaded file with VS Code
4. Open VS Code terminal
5. To compile, call command in the terminal:
   ```g++ -Wall src/Main.cpp```
7. To run the system, call command:
   ```./a.exe```

## How to Run Test Cases - Linux
1. Follow steps 1 to 6 in "How to Run System - Linux" instruction
2. To run the test cases, call command
    ```./test```

## How to Run Test Cases - Windows
1. Follow steps 1 to 4 in "How to Run System - Windows" instruction
2. To compile, call command:
   ```g++ -Wall src/Test.cpp```
4. To run the test cases, call command:
   ```./a.exe```

## Documents
Throughout the course, we have written 5 different documents to plan, present, and guide the project.  

- Requirement Specification: [Google Doc](https://docs.google.com/document/d/1XLYd_4A9i-at-_bP_w-ud8FabQD6ywQ-gZd3Olx2XxI/edit?usp=sharing)
  - The purpose of this document is to present what to expect from the system. That includes the development environment, its expected size, performance, and key features. On the technical side, the document goes over the case scenarios, describes relationships of key objects and attributes, and how users can interact with the system.
- User Manual: [Google Doc](https://docs.google.com/document/d/1P1HL_GefHkuRNPWh0a0nxDXsuL-PYMMRrcKaIZeNk7o/edit?usp=sharing)
  - This document guides the users on how to use this system.  
- Architectural Design: [Google Doc](https://docs.google.com/document/d/1PuVe06ipWgS54-gVSWmiYIsfZTXcNkRcmkGutO1__1I/edit?usp=sharing)
  - In this document, the main functionality of the system is demonstrated by the system's software function chain. In addition, it explains what kind of functional test cases are performed for the software.  
- Detailed Design: [Google Doc](https://docs.google.com/document/d/1l5YLkBxt2cIvUFn8Pd9DuPKrSL9qmJRhTk3VdNGHqro/edit?usp=sharing)
  - This document explains how the data structure is formulated and managed. It also shows what is being tested in the unit test cases module. (CSCI is a physical paper copy of codes. Therefore, not available)
- Integration Report: [Google Doc](https://docs.google.com/document/d/1K_ukWNiqA4UfA90QitZEfWhLc4xQeHPEHtkuWQO_Jc4/edit?usp=sharing)
  - The final document shows in what way the software is implemented. It shows the integration strategies and what other test cases were used. In the end, the developers' review of the project is shown.
