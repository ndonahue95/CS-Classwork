




typedef struct Student {
  const char * name;
  int grade;
} Student;



extern int compareInt(void *, void *);
extern int compareStudentByGrade(void *, void *);
extern int compareStudentByName(void *, void *);


// generic comparison function
typedef int (*CompareFunction) (void *a, void *b);

// Prototype for mysort()
void mysort( int n, int elementSize, void * array,
	     int ascending, CompareFunction compFunc );

