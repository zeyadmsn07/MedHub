cmake_minimum_required(VERSION 3.21)
project(MedHub VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(MedHub 
    main.cpp
    doctors-1.csv
    availability-1.csv
    resources.qrc
    QtLogic/mainwindow.cpp
    QtLogic/mainwindow.h
    QtLogic/mainwindow.ui
    Logic/AvailabilitySlot.cpp
    Logic/AvailabilitySlot.h
    Logic/Appointment.cpp
    Logic/Appointment.h
    Logic/HospitalSystem.cpp
    Logic/HospitalSystem.h
    Logic/DataManager.cpp
    Logic/DataManager.h
    Individuals/Doctor.cpp
    Individuals/Doctor.h
    Individuals/Person.cpp
    Individuals/Person.h
    Individuals/Patient.cpp
    Individuals/Patient.h
)

target_link_libraries(MedHub PRIVATE Qt6::Widgets)

target_include_directories(MedHub PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Individuals
    ${CMAKE_CURRENT_SOURCE_DIR}/Logic
    ${CMAKE_CURRENT_SOURCE_DIR}/QtLogic
)
