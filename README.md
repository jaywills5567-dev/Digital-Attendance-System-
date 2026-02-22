# Digital Attendance System for Hour-Based Lectures

## Course
Course Code: EEE227
Programme: HND Electrical Engineering (Level 200)

## Description
A console-based C++ application that manages student registration, session creation, attendance marking, and attendance reporting using text file storage.

## Features
Register students  
 View all students  
 Search for students  
 Create session (Date/Time/Duration)  
 Mark attendance (Present/Absent/Late)  
 View session attendance report  
 Persistent storage using files  

## How It Works
- Registered student data is stored in **students.txt**
- Each lecture session has its own file under the `sessions/` folder
- Summary attendance counts are stored at the end of each session file

## Folder Structure
digital-attendance-system/  
│── main.cpp  
│── students.txt  
│── sessions/  
│   └── session_code_date.txt  
│── README.md  

## How to Build
Compile using g++:

g++ main.cpp -o attendance

## How to Run

./attendance

## Author
Jonas Abakah-Williams
01241328D
