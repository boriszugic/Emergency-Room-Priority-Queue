Purpose of software: to manage patients arriving to ER by assisting the doctors and nurses to decide which patient to treat next.
Revision information:
    Doron Nussbaum 2022 Initial Code
    Boris Zugic 2022 implementation of functions
Software organization: 
    linked_list_hospital.c contains the implementation of linked list functions
    linked_list_hospital.h corresponding h file
    patient.c contains implementations of patients' functions
    patient.h corresponding h file
    emergencyRoomMain.c testing program
    Makefile - makefile for generating the Code
Compiling the program:
    gcc -g emergencyRoomMain.c linked_list_hospital.c patient.c
Issues/Limitations:
    No known issues or limitations
Instructions:
    Run Makefile to execute a program that will test all implemented functions
