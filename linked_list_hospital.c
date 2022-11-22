
/* 
File name is linked_list_hospital.c
 Purpose: file contains functions for manipulating singly linked list
 
 Revisions
 Doron Nussbaum 2022 File created

 
 
 
 
 
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
	
	// allocate memory for new node
	p = (ListNode*)malloc(sizeof(ListNode));
	if (p == NULL) return NULL;

	// set the data
	p->patient = *patient;
	
	// connect list to new node
	p->next = *head;
	
	// connect new node to list
	*head = p;

	return p;





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
	// if empty list return NULL
	if (node == NULL) 
	{
	return NULL;
	}

	ListNode *p = NULL;
	
	// allocate memory for new node
	p = (ListNode*)malloc(sizeof(ListNode));
	if (p == NULL) return NULL;

	// set the data
	p->patient = *patient;
	
	// connect list to new node
	if (node == NULL)
	{
		p->next = NULL;
		node = p;
	}
	else 
	{
		p->next = node->next;
	

		// connect new node to list
		node->next = p;
	}

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
	// iterate through list
	while (p != NULL)
	{
			// if current node's patient's priority == priority, return a pointer to current node 
			if ((p->patient).priorityLevel == priority)
			{
				*patient = p->patient;
				return p;
			}
		p = p->next;
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
	// iterate through list
	while (p != NULL)
	{
			// if current node's patient's priority == priority, return a pointer to current node 
			if (findPatient(&(p->patient)) == 0) 
			{
				*patient = p->patient;
				return p;
			}
		p = p->next;
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
	ListNode *temp = NULL;
	temp = *head;
	if (head == NULL || *head == NULL) return 1;
	if ((*head)->next == NULL) 
	{
		*patient = temp->patient;
		*head = NULL;
		return 0;
	}
	
	*patient = temp->patient;
	*head = temp->next;
	
	free(temp);
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
    
	if (head == NULL || *head == NULL) return 1;


	while (currNode != NULL)
	{
		
		if(currNode->patient.priorityLevel == priority) // if note is found
		{
			if (currNode == *head) 
			{
				*patient = currNode->patient; // copy data to output
				*head = currNode->next;	// move head
				currNode->next = NULL;	
				free(currNode);
				currNode = NULL;	// deallocate memory 
				free(prevNode);
				prevNode = NULL;
			}
			else
			{
				*patient = currNode->patient;	// copy data to output
				prevNode->next = currNode->next;	// move head
				currNode->next = NULL;	
				free(currNode);	
				currNode = NULL;	// deallocate memory 
			}
		return 0;
		}
		currNode = currNode->next;
		prevNode = currNode;
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
	ListNode *currNode = NULL, *prevNode = NULL, *highestPriority = NULL, *nodeBeforeHighestPriority = NULL;
	prevNode = *head, highestPriority = *head;
	currNode = (*head)->next;
    

	if (head == NULL || *head == NULL) return 1;	// if list does not exist or is empty return 1


	while (currNode != NULL)	// iterate through list
	{
		
		if(comparePatients(&(highestPriority->patient), &(currNode->patient), currentTime) < 0) 
		{
			highestPriority = currNode; // if highest priority patient (initially the first patient in list) is less than the current patient, set highest priority to curr patient
			nodeBeforeHighestPriority = prevNode; // keep track of node before highest priority patient for deletion purposes
			//printf("\n%d\n", highestPriority->patient.priorityLevel + 2*(currentTime - highestPriority->patient.arrivalTime));
		}
		// update prev and curr nodes	
		prevNode = currNode;	
		currNode = currNode->next;
		
	}	
			
	if (highestPriority == *head) // if highest priority patient is the head of the list
	{
		*patient = highestPriority->patient; // copy data to output
		*head = highestPriority->next;	// move head
		highestPriority->next = NULL;	// disconnect head from list
		free(highestPriority);		// deallocate memory
		highestPriority = NULL;	// set pointer to NULL
		free(prevNode);	
		prevNode = NULL;
	}
			
	else	// if highest priority patient is not the head of the list
	{
	
		*patient = highestPriority->patient;	// copy data to output
		nodeBeforeHighestPriority->next = highestPriority->next;	// move head
		highestPriority->next = NULL;	// disconnect from list
		free(highestPriority);		// deallocate memory
		currNode = NULL;	// set pointer to NULL
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
	// add code 


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
	// assign function pointer to printPatient function
	//myPrint = printPatient;
	
	// iterate through list using pointer arithmetic
	while (head != NULL)
	{
		myPrint(&(head->patient));
		head = head->next;
	}

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
	int count = 0;
	ListNode *currNode = head;
	while (currNode != NULL)
	{
		count++;
		currNode = currNode->next;
	}

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
	
	if (head == NULL) return 0;

	int count = 0;
	while (head != NULL)
	{

		if (head->patient.priorityLevel == priority) count++;

		head = head->next;
	}
	
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
	// add code 
 
    
 
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

	/* Add code */


}




