#ifndef STUDENT_H
#define STUDENT_H

struct Student
{
    int iId;
    int iYear;
    char chName[50];
    float fCGPA;
};

void AddStudent(void);
void UpdateStudent(void);
void DeleteStudent(void);
void SearchStudent(void);
void DisplayStudents(void);
void SortStudentsByCgpa(void);
void SortStudentsByName(void);
void SortStudentsByYear(void);
void FreeMemory(void);
void EnsureCapacity(void);
void LoadFromFile(void);
void SaveTableToFile(void);


#endif