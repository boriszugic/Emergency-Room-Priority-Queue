
/* 
File name is linked_list_hospital.c
 Purpose: file contains functions for manipulating singly linked list
 
 Revisions
 Doron Nussbaum 2022 File created
 Boris Zugic    2022 Implementation
 
 
 
 
 
 Copyright 2022 Doron Nussbaum
 
 */

/******************************************************************/
// INCLUDE 

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "linked_list_hospital.h"
#include "patient.h"


/************************************************************************/
// Define 



/************************************************************************/

/*
Purpose: insert a new node into the list as the first element
input
patient - the patient record

input/output
head - head of linked list

return
A pointer to the node that was allocated.  

NULL - if the operation was not successful

*/
ListNode *insertToList(ListNode **head, PatientInfo *patient)

{	
	ListNode *p = NULL;
	
	p = (ListNode*)malloc(sizeof(ListNode));	// allocate memory for new node
	if (p == NULL) return NULL;		// return NULL if allocation failed

	p->patient = *patient;	// set the data
	
	p->next = *head;	// connect list to new node
	
	*head = p;	// connect new node to list

	free(p);	// release memory from p
	
	p = NULL;	// good practice

	return *head;	// return pointer to head of new list

}


/************************************************************************/
/*
Purpose: insert a new node into the list after the given node  

Input
input
patient - the patient record


return
A pointer to the node that was allocated.  

NULL - if the operation was not successful

*/
ListNode *insertAfter(ListNode *node, PatientInfo *patient)
{
	
	if (node == NULL) return NULL; 	// if empty list return NULL
	
	ListNode *p = NULL; // initialize pointer to NULL
	
	p = (ListNode*)malloc(sizeof(ListNode));	// allocate memory for new node
	if (p == NULL) return NULL;		// if allocation failed return NULL

	p->patient = *patient;		// set the data
	
	p->next = node->next;	// connect node to list
	
	node->next = p;		// connect list to node

	return p;
 

}




/************************************************************************/
/*
Purpose: search for the first patient with the matching priority
Input
head - the head of the list
priority - first priority of the patient

output
patient - the patient record

return
a pointer to the node that was found.
NULL - if no node was found or list empty

*/
ListNode * searchFirstPatientByPriority(ListNode *head, unsigned char priority, PatientInfo *patient)

{
	ListNode *p = NULL;
	p = head; 
	
	while (p != NULL)	// while list is not empty
	{
			if ((p->patient).priorityLevel == priority)		// if current patient's priorityLevel == given priority
			{
				*patient = p->patient;		// copy data
				return p;		// return pointer to node containing patient with matching priority
			}
		p = p->next;	// advance p to next node
	}
	
	return NULL;

}

/************************************************************************/
/*
Purpose: search for the first patient with the matching criteria.  The criteria is determined
by the comparison function 
Input
head - the head of the list
findPatient -  a function pointer that returns a 0 if the patient's record matches that criteria

output
patient - the patient record

return
a pointer to the node that was found.
NULL - if no node was found or list empty

*/
ListNode * searchNextPatient(ListNode *head, int (*findPatient)(PatientInfo *), PatientInfo *patient)
{
	ListNode *p = NULL;
	p = head; 
	
	while (p != NULL)	// while list is not empty
	{
			if (findPatient(&(p->patient)) == 0) 	// if current patient satisfies the criteria
			{
				*patient = p->patient; 		// copy data
				return p;	// return pointer to node containing patient with satisfied criteria
			}
		p = p->next;	// advance to next node in list
	}
	
	return NULL;

}

/***************************************************************/

/*
Purpose: delete the first node from the list
Input
head - the head of the list

output
head - the head of the list
patient - the patient record


return

0 if node was deleted
1 if node was not deleted or list is empty

*/
int deleteFromList(ListNode **head, PatientInfo *patient)

{
	if (head == NULL || *head == NULL) return 1;	// if linked list does not exist or is empty, return 1
	
	ListNode *temp = NULL;
	temp = *head;

	*patient = temp->patient;	// copy data
	*head = (*head)->next;	// disconnect list from node
	temp->next = NULL;	// disconnect node from list
	
	free(temp); // release memory
	temp = NULL;
	
	return 0;
}


/***************************************************************/

/*
Purpose: Retrieve the first node that matches the priority.  When found the node is deleted and the patient
information is provided. 

Input
head - the head of the list

output
head - the head of the list
patient - the patient record


return

0 if node was deleted  
1 if node was not found or list is empty 

*/
int retrieveNextPatientByPriority(ListNode **head, unsigned char priority, PatientInfo *patient)

{
	ListNode *currNode = NULL, *prevNode = NULL;
	currNode = *head;
    
	if (head == NULL || *head == NULL) return 1; 	// if linked list does not exist or is empty, return 1

	while (currNode != NULL) // while list is not empty
	{
		if(currNode->patient.priorityLevel == priority) // if node's patient's priorityLevel matches given priority
		{
			if (currNode == *head) // if node found is head of list
			{
				*patient = currNode->patient; // copy data to output
				*head = (*head)->next;	// disconnect list from node
				currNode->next = NULL;	// disconnect node from list
			}

			else
			{
				*patient = currNode->patient;	// copy data to output
				prevNode->next = currNode->next;	// disconnect list from node
				currNode->next = NULL;	// disconnect node from list
			}
		
		free(currNode);	// deallocate memory 
		free(prevNode);
		
		currNode = NULL;
		prevNode = NULL;
		
		return 0;
		
		}
		
		prevNode = currNode;
		currNode = currNode->next; // advance to next node in list
	
	}
	
	return 1;
}

/***************************************************************/

/*
Purpose: Retrieve the patient with the highest criteria to be treated.  The maximum criteria is determined by 
a comparePatients function.  Once the patient is found it is deleted from the list and its information is 
returned. 

Input
head - the head of the list
comparePatients - this function takes two paitent records and compares them.  
				It returns, -1, 0 or 1 if p1 < p2, p1 == p2, or p1 > p2, respectively. 

output
head - the head of the list
patient - the patient record


return
0 if  patient was found and the node was deleted  
1 if no paitent was found or the list is empty 


Algorithm:
The function first finds the patient with the hights criteria by comparing all the patients records and 
finding the first patient with the maximum criteria to be treated.  It then deletes the patient and returns
its information. 
*/
int retrieveNextPatientByCriteria(ListNode **head, int (*comparePatients)(PatientInfo *p1, PatientInfo *p2, int currentTime), int currentTime, PatientInfo *patient)

{
	
	/* NOTE: node will always be returned unless list is empty */

	ListNode *currNode = NULL, *prevNode = NULL, *highestPriority = NULL, *nodeBeforeHighestPriority = NULL; // initializing all pointers to NULL
	prevNode = *head, highestPriority = *head; // prevNode keeps track of node before currNode
	currNode = (*head)->next; // sets currNode to 2nd node in list

	if (head == NULL || *head == NULL) return 1;	// if list does not exist or is empty return 1

	while (currNode != NULL)	// while list is not empty
	{
		
		if(comparePatients(&(highestPriority->patient), &(currNode->patient), currentTime) < 0) 	// if p1 < p2
		{
			highestPriority = currNode; 	// set highest priority to current patient
			nodeBeforeHighestPriority = prevNode; // update nodeBeforeHighestPriority
		}
		
		// update prev and curr nodes	
		prevNode = currNode;	
		currNode = currNode->next;
		
	}	
			
	if (highestPriority == *head) // if highest priority patient is head of list
	{
		*patient = highestPriority->patient; // copy data to output
		*head = highestPriority->next;	// move head
		highestPriority->next = NULL;	// disconnect head from list
		
		free(highestPriority);		// deallocate memory
		free(prevNode);	
		free(currNode);
		
		highestPriority = NULL;		// set pointers to NULL
		prevNode = NULL;
		currNode = NULL;
	}
			
	else	// if highest priority patient is NOT head of list
	{
	
		*patient = highestPriority->patient;	// copy data to output
		nodeBeforeHighestPriority->next = highestPriority->next;	// disconnect list from node
		highestPriority->next = NULL;	// disconnect node from list
		
			
		free(highestPriority);		// deallocate memory
		free(prevNode);	
		free(currNode);
		
		highestPriority = NULL;		// set pointers to NULL
		prevNode = NULL;
		currNode = NULL;
		
	}
		
		return 0;
}


/************************************************************************/
/*
Purpose: deletes all nodes from the list
input/output
head - the head of the list


*/
void deleteList(ListNode **head)
{
	ListNode *currNode = NULL;
	currNode = *head;
	
	while (currNode != NULL)	// while list is not empty
	{

		*head = (*head)->next;	// disconnect list from node (advance head to list one node shorter)
		free(currNode);	// release memory of single node
		currNode = *head;	// advance to next node in list
		
	}
	
	free(head);	// release memory of linked list
	head = NULL;
}



/************************************************************************/
/*
Purpose: prints all the records in the list

input
head - the head of the list
myPrint - a function pointer for print the patient information. 
*/
void printList(ListNode *head, void (*myPrint)(PatientInfo *patient))
{	
	ListNode *p = NULL;
	p = head; 

	while (p != NULL)	// while list not empty
	{
		myPrint(&(p->patient));	// print patient
		p = p->next;	// advance to next node in list
	}

	free(p); // release memory
	p = NULL;
}


/************************************************************************/
/*
Purpose: counts the number of patients that are waiting to be treted
input
head - the head of the list

return 
the number of registered patients

*/
int numPatientsInEmergency(ListNode *head)
{
	int count = 0;	// counting variable
	ListNode *currNode = head;

	while (currNode != NULL)	// while list not empty
	{
		count++;	// increment count
		currNode = currNode->next;	// advance to next node
	}

	free(currNode); // release memory
	currNode = NULL;

	return count;

}

/************************************************************************/
/*
Purpose: counts the number of patients with a matching priority
input
head - the head of the list


return 
the number of patients with a matching priority


*/
int countPatients(ListNode *head, unsigned char priority)
{
	ListNode *currNode = head;
	int count = 0;

	while (currNode != NULL)	// while list is not empty
	{

		if (currNode->patient.priorityLevel == priority) count++;	// if priority level of current patient matches given priority. increment count

		currNode = currNode->next;	// advance to next node in list
	}
	
	free(currNode);	// release memory
	currNode = NULL;

	return count;
}



/************************************************************************/
/*

Purpose: store all the patients records in the file by printing out the information i.e., in ASCII readable format. 


input
filename - the name of the file to be used for storing the data
head - the head of the  list

Algorithm:
use the '$' character as a delimeter between the fields
For example:
Miya                 $Bronson                 $ 9700    $ 20  $ 2 $ Broken Bone 
*/

// Backup Functions
int createAsciiBackup(char *fileName, ListNode *head)

{
	// add code 

	// open the file

	// store each patient records in the file

	// close the file

    return(0);
}

/************************************************************************/
/*

Purpose: store all the patients records in the file in their binary format. 


input
filename - the name of the file to be used for storing the data
head - the head of the  list



*/

int createBinaryBackup(char *fileName, ListNode *head)
{
	// add code 

	// open the file

	// store each patient records in the file

	// close the file

    return(0);
}

////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

// BONUS SECTION



/************************************************************************/
/*

Purpose: removes all Patients with priority less than or equal to the given priority 
(remove all patients with priorityLevel <= priority).   


input
head - the head of the  list

Ouput
head - the head of the list where all patients with priorityLevel < priority are removed 

*/
int releasePatients(ListNode **head, unsigned char priority)

/* code */
{
	// add code 

	// remove all patients that head is pointing to and meet the criteria


	// remove all other patients that meet the crieria
	return(0);

}

/************************************************************************/
/*
Purpose: prints all the patients' records in the list in reverse order using recursion

input
head - the head of the list
*/
void printListReverse(ListNode *head, void (*myPrint)(PatientInfo *patient))
{
	if (head == NULL) return; // if list is empty return
 
	printListReverse(head->next, printPatient);	// recursive call
	myPrint(&(head->patient));	// print patient
	
}





/*****************************************************************************/

/************************************************************************/
/*
Purpose: Reverse the list such that the last node in the list becomes the first node and the first node in the list becomes the last node.  

Restrictions:
1.	This operation must be achieved using recursive calls
2.	No memory is to be allocated or released at any time during the execution of the function



input
head - the head of the list


Returns:
the head of the new list
*/
ListNode *reverse(ListNode *head)

{
	ListNode *currNode = head;

	if (currNode == NULL || currNode->next == NULL) return currNode;	// if list is empty or current node is last node in list, return current node
	
	ListNode *temp = reverse(currNode->next);
	currNode->next->next = currNode;
	currNode->next = NULL;

	free(currNode);
	currNode = NULL;

	return temp;

}




