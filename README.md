# LibManSys
RCive++ Project Repository for CPE104L Module 2

## Description:
The LibManSys or Library eTracker project is a Library Management System developed using C++ and [Qt](https://www.qt.io/). Key features of the program include the ability to perform CRUD operations, Searching and Sorting, a working GUI, a ticketing system for book borrowing, and a way to manage these tickets automatically. The project is being worked on and developed by RCive++, a group of 3 beginner programmers.

## Notice:
The password to enter admin mode is " ***password*** ".

The text file generated by the program is named **bookRepository.txt** and can be found in the **build-LibManSys-Desktop_x86_windows_msys_pe_64bit-Debug** folder. This folder is usually generated in the same folder as the main files of the program which can be found in the folder named **LibManSys**.

However the names of these folders may be dependent on the name of the project file you created to use the program in Qt.

The text file also makes use of vertical lines ("|") to separate data. When adding a book to the repository, do not use this character as it will make the program create a new column. In the event that this occurs, navigate to the **bookRepository.txt** file and clear out its contents. Refer to the above paragraph to find the file.

The following files are unnecessary:
* userlogin.h
* userlogin.cpp
* userlogin.ui

In the case of the programmers, the directories are:

D:\QT Projects\LibManSys

D:\QT Projects\build-LibManSys-Desktop_x86_windows_msys_pe_64bit-Debug

## Project Versions:

### Version 1: ###
 * Button Functionality, able to switch windows

### Version 2: ###
 * CSV reading
 * AdminMain and UserMain windows were added

### Version 2.1: ###
 * Re-commit (disregard)

### Version 3: ###
 * Replaced CSV with txt
 * CRUD Functionality
 * P.S. adminmain.ui is not made in the ui, instead the widgets (i.e. buttons and table) are made in the .cpp file instead.

### Version 3.1: ###
 * Added sorting functionality
   * Can sort by ID, Book Name, Book Author, Genre, Number of Units in Inventory, and Description

### Version 3.2: ###
// * Added ticket queue button (No implementation)
 * Added new category 'description'
 * Modified adminmain.ui and adminmain.cpp for a better UI
   * adminmain.ui is now made in the ui as opposed to the use of code in the .cpp file
 * Minor bug fixes
   * Program crashing after entering adminmain
   * Program crashing after adding new row
   * Program crashing after updating rows
   * Inadvertent creation of new columns due to the use of commas in the data cells
     * Program now makes use of vertical lines("|") to separate data in the txt file as opposed to commas(","). This is due to the new 'description' column.
   * Table view not showing

### Version 4: ###
 * Created UI for usermain.ui
   * tableView
   * 4 Buttons
     * borrowBook - Implemented
     * returnBook
     * searchTable - Implemented
     * sortTable - Implemented
 * Known Issues:
   * Sorting sorts by first number if using ID, Inventory
   * Searching is overly-specific, making it difficult to search by description
   * Borrow Book merely creates a text file containing user name and book id or book name

## Extra Documentation:
The programmers made use of youtube to learn Qt. The following are a few of the videos that were viewed and studied by the programmers while learning the software:
* [How To Install Qt Creator on Windows 11 (2023)](https://www.youtube.com/watch?v=OoVNt-KJ96w) by ProgrammingKnowledge
* [How to get started with Qt Creator | C++ GUI | Libraries | Qt Designer | Cross platform](https://www.youtube.com/watch?v=H2ud-ATLIdI) by Code, Tech, and Tutorials
* [Qt Crash Course for Beginners - Create C++ GUI Apps](https://www.youtube.com/watch?v=cXojtB8vS2E) by Sciber
* [Qt Tutorial 2 : C++ Calculator](https://www.youtube.com/watch?v=txGRU7OrTZo) by Derek Banas
* [Qt Tutorial : C++ Notepad App](https://www.youtube.com/watch?v=I96uPDifZ1w) by Derek Banas
* [Qt Tutorials For Beginners 9 - How to Show Another Window From MainWindow in QT](https://www.youtube.com/watch?v=VigUMAfE2q4) by ProgrammingKnowledge
* [QT C++ GUI Tutorial 12- How to open a new window after successful Login](https://www.youtube.com/watch?v=EAD8x7z75tU) by ProgrammingKnowledge
* [Pass Data Between Windows - PyQt5 GUI Thursdays #25](https://www.youtube.com/watch?v=hdR1pE35ad4) by Codemy.com
* [Qt C++ GUI Application Tutorial | Qt QFile | QTextStream | Read And Write Data In CSV File Using Qt](https://www.youtube.com/watch?v=BTwOLCBWcnE) by Qt With Ketan
* [Qt C++ GUI Application Tutorial | Qt QFile | How To Read And Write File](https://www.youtube.com/watch?v=FM5i_nep08c) by Qt With Ketan
* [QT C++ GUI Tutorial 17- Load SqLite table data to QTableView](https://www.youtube.com/watch?v=OrHitqwJu8Q) by ProgrammingKnowledge

The programmers also made use of google and various websites to help in navigating and programming in Qt. The following are links to a few of the websites:
* [Qt for Beginners](https://wiki.qt.io/Qt_for_Beginners) - Qt
* [Handling CSV](https://wiki.qt.io/Handling_CSV) - Qt
* [Presenting Data in a Table View](https://doc.qt.io/qt-6/sql-presenting.html) - Qt
* [Passing Data Between 2 Windows](https://stackoverflow.com/questions/19200598/passing-data-between-2-windows-qt) - Stack overflow
* [QDialog Class](https://doc.qt.io/qt-6/qdialog.html) - Qt
* [QObject Class](https://doc.qt.io/qt-6/qobject.html) - Qt
* [Qt creator throws permission error on project (files owned by me) within directory of root)](https://superuser.com/questions/639968/qt-creator-throws-permission-error-on-project-files-owned-by-me-within-directo) - Stack Exchange
* [QTCreator changing permissions of files](https://stackoverflow.com/questions/50911796/qtcreator-changing-permissions-of-files) - Stack overflow
* [Building and Running an Example](https://doc.qt.io/qtcreator/creator-build-example-application.html) - Qt
* [Build Systems](https://doc.qt.io/qtcreator/creator-project-other.html) - Qt
* [Changing location of header file causes missing vtable error when compiling with CMake](https://stackoverflow.com/questions/56435647/changing-location-of-header-file-causes-missing-vtable-error-when-compiling-with) - Stack overflow
* [QRadioButton Class](https://doc.qt.io/qt-6/qradiobutton.html) - Qt
* [QDialogButtonBox Class](https://doc.qt.io/qt-6/qdialogbuttonbox.html) - Qt
