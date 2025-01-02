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

#endif