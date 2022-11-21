
/* 
File name is linked_list.h
 Purpose: file contains functions for manipulating singly linked list
 
 Revisions
 Doron Nussbaum 2022   File created




  Copyright 2022 Doron Nussbaum
 */


#ifndef LINKED_LIST_2401_HEADER
#define LINKED_LIST_2401_HEADER 1

/************************************************************************/
// INCLUDES

#include "patient.h"

/************************************************************************/
// DEFINES



/************************************************************************/

// STRUCTURES


typedef struct listNode {
	PatientInfo patient;
	struct listNode *next;
} ListNode;



/************************************************************************/
// FUNCTION PROTOTYPES


// Insert Functions 
ListNode *insertToList(ListNode **head, PatientInfo *patient);

ListNode *insertAfter(ListNode *node, PatientInfo *patient);


// Search Functions

ListNode * searchFirstPatientByPriority(ListNode *head, unsigned char priority, PatientInfo *patient);
ListNode * searchNextPatient(ListNode *head, int (*findPatient)(PatientInfo *), PatientInfo *patient);


// Delete Functions
int deleteFromList(ListNode **head, PatientInfo *patient);

int retrieveNextPatientByPriority(ListNode **head, unsigned char priority, PatientInfo *patient);

int retrieveNextPatientByCriteria(ListNode **head, 
	int (*comparePatients)(PatientInfo *p1, PatientInfo *p2, int currentTime), 
	int currentTime, PatientInfo *patient);

void deleteList(ListNode **head);

int releasePatients(ListNode **head, unsigned char priority);

// Print Functions
void printPatient(PatientInfo *patient);

void printList(ListNode *head, void (*myPrint)(PatientInfo *patient));

void printListReverse(ListNode *head, void (*myPrint)(PatientInfo *patient));

// Counting Functions
int numPatientsInEmergency(ListNode *head);

int countPatients(ListNode *head, unsigned char priority);

// Bonus Functions
int releasePatients(ListNode **head, unsigned char priority);
ListNode *reverse(ListNode *head);
void printListReverse(ListNode *head, void (*myPrint)(PatientInfo *patient));


#endif
