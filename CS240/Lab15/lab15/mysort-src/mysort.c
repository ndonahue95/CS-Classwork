#include "mysort.h"
#include <alloca.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>



/* Compare two integer numbers*/
int compareInt( void * a, void * b )
{
  return *(int*)a - *(int*) b;
}



// Compare students by name 
// Hint: use strcmp 
int compareStudentByName( void * a, void * b )
{
  Student * sa = (Student *) a;
  Student * sb = (Student *) b;

  // Please complete this function
    
    return strcmp(sa->name, sb->name);
   
}





  /* Compare students by grade first.
     return 1 if grade a is larger than grade b
     return -1 if grade a is less than grade b
     if grades are the same then 
     compare alphabetically
  */ 

int compareStudentByGrade( void * a, void * b )
{

    Student * sa = (Student *) a;
    Student * sb = (Student *) b;
    
  // Please complete this function
    
    if (sa->grade == sb->grade) {
        
        return compareStudentByName(sa, sb);
        
    } else if (sa->grade > sb->grade) {
        
        return 1;
        
    } else if (sa->grade < sb->grade) {
        
        return -1;
        
    }
    
  return 0;
}




//
// Sort an array of element of any type
// it uses "compFunc" to sort the elements.
// The elements are sorted such as:
//
// if ascending != 0
//   compFunc( array[ i ], array[ i+1 ] ) <= 0
// else
//   compFunc( array[ i ], array[ i+1 ] ) >= 0
//
// See test_sort to see how to use mysort.
//
void mysort( int n,                      // Number of elements
	     int elementSize,            // Size of each element
	     void * array,               // Pointer to an array
	     int ascending,              // 0 -> descending; 1 -> ascending
	     CompareFunction compFunc )  // Comparison function.
{
	// Please complete this function
    
    void * temp = malloc(elementSize);
    
    int i, j;
    
    for (i = 0; i < n; i++) {
        
        for (j = 0; j < i; j++) {
            
            void * entry1 = (void *)((char *)array + j * elementSize);
            void * entry2 =(void *)((char *)array + (j + 1) * elementSize);
            
            if (ascending != 0) {
                
                if ((*compFunc)(entry1, entry2) <= 0) {
                    
                    memcpy(temp, entry1, elementSize);
                    memcpy(entry1, entry2, elementSize);
                    memcpy(entry2, temp, elementSize);
                    
                }
                
            } else {
             
                if ((*compFunc)(entry1, entry2) >= 0) {
                    
                    memcpy(temp, entry1, elementSize);
                    memcpy(entry1, entry2, elementSize);
                    memcpy(entry2, temp, elementSize);
                    
                }
                
            }
        }
        
    }
    
    free(temp);
}

