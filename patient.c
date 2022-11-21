/*
Purpose: file contains functions related to patients
 
 Revisions
 Doron Nussbaum 2022   File created






  Copyright 2022 Doron Nussbaum
 */


/************************************************************************/
  // INCLUDES

#include "stdio.h"
#include "patient.h"

/************************************************************************/
// DEFINES


/************************************************************************/

// STRUCTURES



/************************************************************************/
/*
Purpose: prints the fields of a node
input:
node - a pointer to a given node

*/


void printPatient(PatientInfo *p)
{
	printf("%-20s %-20s %7d %5d %3d  %s \n",p->firstName, p->familyName, p->id, p->arrivalTime, 
		p->priorityLevel, p->medicalProblem);

}




/************************************************************************/
/*
Purpose: function which determines which patient has higher priority to be treated
input:
p1 - patient info
p2 - patient info

return 
-1 if p1 < p2
0 if p1 == p2
1 if p1 > p2

Criteria is based on priorityLevel and on the arrival time of the patients.  
Patients with low priority will be bimped up in priority due to long wait time.

Patient priority is determiend by priorityLevel + 2*(currentTime - arrivalTime)
*/

int comparePatients(PatientInfo *p1, PatientInfo *p2, int currentTime)

{
	int p1Level = p1->priorityLevel + 2*(currentTime - p1->arrivalTime);
	int p2Level = p2->priorityLevel + 2*(currentTime - p2->arrivalTime);
	if (p1Level < p2Level) return(-1);
	return (p1Level > p2Level);

}



/************************************************************************/
/*
Purpose: function which determines whehter a patient was found
input:
p - patient info


return 
0 if a match was found
1 otherwise

Criteria is based on priorityLevel.  The function checks whehte the patient has high priority (5-9)

*/

int findPatient(PatientInfo *p)

{
	if (p->priorityLevel >= 5) return(0);
	return(1);
}




