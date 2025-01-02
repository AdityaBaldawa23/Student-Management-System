#include <stdio.h>
#include <malloc.h>
#include <conio.h>
#include <string.h>
#include "Student.h"

struct Student
{
    int iId;
    int iYear;
    char chName[50];
    float fCGPA;
};

struct Student *arrStudents = NULL;
int StudentCount = 0;
int Capacity = 0;

int main(void)
{
    printf("Program Started Successfully!!\n");
    LoadFromFile();
    int iChoice;
    printf("Load from file is working well\n\n");

    while (1)
    {
        printf("=====================   STUDENT MANAGEMENT SYSTEM   =====================\n\n");
        printf("Welcome to Menu Section!!\n\n");
        printf("1. Add a Student\n2. Update Data of a student\n3. Search for a student\n4. Delete a student\n5.Display All Students\n6.Exit\n");
        printf("Enter your operation:\t");
        scanf("%d", &iChoice);

        switch (iChoice)
        {
        case 1:
            AddStudent();
            break;

        case 2:
            UpdateStudent();
            break;

        case 3:
            SearchStudent();
            break;

        case 4:
            DeleteStudent();
            break;

        case 5:
            DisplayStudents();
            break;

        case 6:
            SaveTableToFile();
            FreeMemory();
            return 0;

        default:
            printf("Enter a valid operation choice!!\n");
        }
    }

    getchar();
    return 0;
}

void AddStudent(void)
{
    // iContinue = 0;
    int iNumberOfStudentsToAdd, iCounter;
    printf("Enter the number of students you want to add:\t");
    scanf("%d", &iNumberOfStudentsToAdd);

    for (iCounter = 0; iCounter < iNumberOfStudentsToAdd; iCounter++)
    {
        EnsureCapacity();

        if (StudentCount >= Capacity)
        {
            printf("Max Student Limit Reached!!");
            return;
        }
        struct Student student;

        getchar();
        printf("To add a student:\n");
        printf("Enter Name:\t");
        gets(student.chName);

        student.iId = StudentCount + 1;

        while (1)
        {
            printf("Enter Year of Study (1-4):\t");
            if (scanf("%d", &student.iYear) != 1 || student.iYear < 1 || student.iYear > 4)
            {
                printf("Invalid year. Please enter a valid year (1-4).\n");
                while (getchar() != '\n')
                    ; // Clear the input buffer
            }
            else
            {
                break;
            }
        }

        while (1)
        {
            printf("Enter CGPA (0.0 to 10.0):\t");
            if (scanf("%f", &student.fCGPA) != 1 || student.fCGPA < 0.0 || student.fCGPA > 10.0)
            {
                printf("Invalid CGPA. Please enter a CGPA between 0.0 and 10.0.\n");
                while (getchar() != '\n')
                    ; // Clear the input buffer
            }
            else
            {
                break;
            }
        }

        arrStudents[StudentCount] = student;
        StudentCount++;

        printf("Student Data Added Succesfully!!\n");
    }

    printf("To continue Enter");
    getchar();
}

void UpdateStudent(void)
{
    // iContinue = 0;
    int iRoll_No, iCounter;
    printf("Enter Roll Number of student you need to update:\t");
    scanf("%d", &iRoll_No);

    for (iCounter = 0; iCounter < StudentCount; iCounter++)
    {
        if (arrStudents[iCounter].iId == iRoll_No)
        {
            getchar();
            printf("Enter Name:\t");
            gets(arrStudents[iCounter].chName);

            while (1)
            {
                printf("Enter Year of Study (1-4):\t");
                if (scanf("%d", &arrStudents[iCounter].iYear) != 1 || arrStudents[iCounter].iYear < 1 || arrStudents[iCounter].iYear > 4)
                {
                    printf("Invalid year. Please enter a valid year (1-4).\n");
                    while (getchar() != '\n'); // Clear the input buffer
                }
                else
                {
                    break;
                }
            }

            while (1)
            {
                printf("Enter CGPA (0.0 to 10.0):\t");
                if (scanf("%f", &arrStudents[iCounter].fCGPA) != 1 || arrStudents[iCounter].fCGPA < 0.0 || arrStudents[iCounter].fCGPA > 10.0)
                {
                    printf("Invalid CGPA. Please enter a CGPA between 0.0 and 10.0.\n");
                    while (getchar() != '\n'); // Clear the input buffer
                }
                else
                {
                    break;
                }
            }

            printf("Student information updated successfully!!\n");

            printf("To continue Enter");
            getchar();
            return;
        }
    }
    printf("No student with the entered roll number exists!!\n");

    printf("To continue Enter");
    getchar();
}

void SearchStudent(void)
{
    // iContinue = 0;
    int iRoll_No, iCounter;
    printf("Enter Roll Number of student you need search:\t");
    scanf("%d", &iRoll_No);

    for (iCounter = 0; iCounter < StudentCount; iCounter++)
    {
        if (arrStudents[iCounter].iId == iRoll_No)
        {
            printf("Name: %s\n", arrStudents[iCounter].chName);

            printf("Year of Study: %d\n", arrStudents[iCounter].iYear);

            printf("CGPA of Student: %f\n", arrStudents[iCounter].fCGPA);

            return;
        }
    }
    printf("No such student exists!!\n");

    printf("To continue Enter");
    getchar();
}

void DeleteStudent(void)
{
    // iContinue = 0;
    int iRoll_No, iCounter1, iCounter2;
    printf("Enter Roll number of student you need delete:\t");
    scanf("%d", &iRoll_No);

    for (iCounter1 = 0; iCounter1 < StudentCount; iCounter1++)
    {
        if (arrStudents[iCounter1].iId == iRoll_No)
        {
            for (iCounter2 = iCounter1; iCounter2 < StudentCount - 1; iCounter2++)
            {
                arrStudents[iCounter2] = arrStudents[iCounter2 + 1];
            }
            StudentCount--;
            printf("Successfully deleted the student record!");
            return;
        }
    }
    printf("No such student exists!!\n");

    printf("To continue Enter");
    getchar();
}

void DisplayStudents(void)
{
    int iCounter;
    printf("======= Data of Students =======\n\n");
    for (iCounter = 0; iCounter < StudentCount; iCounter++)
    {
        printf("Roll Number: %d\n", arrStudents[iCounter].iId);

        printf("Name: %s\n", arrStudents[iCounter].chName);

        printf("Year of Study: %d\n", arrStudents[iCounter].iYear);

        printf("CGPA of Student: %f\n", arrStudents[iCounter].fCGPA);

        printf("\n");
    }

    printf("To continue Enter");
    getchar();
}

void SaveTableToFile(void)
{
    printf("In Save func\n");
    int iSort;
    printf("Enter the format in which you want to store the data:\n1. Sort as per Year\n2.Sort as per Name.\n3.Sort as per CGPA.\n");
    scanf("%d", &iSort);

    switch (iSort)
    {
    case 1:
        SortStudentsByYear();
        printf("Sorted as per Year\n");
        break;

    case 2:
        SortStudentsByName();
        printf("Sorted as per Name\n");
        break;

    case 3:
        SortStudentsByCgpa();
        printf("Sorted as per CGPA\n");
        break;

    default:
        printf("Enter a valid technique\n");
    }

    FILE *fp = fopen("student_table.txt", "w");
    if (fp == NULL)
    {
        printf("Error saving data to file!\n");
        return;
    }

    fseek(fp, 0, SEEK_END);

    if (ftell(fp) == 0)
    {
        fprintf(fp, "%-5s %-20s %-5s %-5s\n", "ID", "Name", "Year", "CGPA");
        fprintf(fp, "--------------------------------------------\n");
    }

    for (int i = 0; i < StudentCount; i++)
    {
        fprintf(fp, "%-5d %-20s %-5d %-5.2f\n",
                arrStudents[i].iId,
                arrStudents[i].chName,
                arrStudents[i].iYear,
                arrStudents[i].fCGPA);
    }

    fclose(fp);
    printf("Data saved successfully in table format to file.\n");
}

void LoadFromFile(void)
{
    FILE *fp = fopen("student_table.txt", "r");
    if (fp == NULL)
    {
        printf("No previous data found. Starting fresh.\n");
        return;
    }

    // Make sure arrStudents has been initialized at the beginning
    if (arrStudents == NULL)
    {
        arrStudents = malloc(sizeof(struct Student) * 10); // Initial allocation
        if (arrStudents == NULL)
        {
            printf("Memory allocation failed!\n");
            fclose(fp);
            return;
        }
    }

    char buffer[200];
    int maxId = 0;

    // Skip the header
    fgets(buffer, sizeof(buffer), fp); // Skip "ID    Name..."
    fgets(buffer, sizeof(buffer), fp); // Skip "--------------------------------------------"

    // Read student data from the file
    while (fscanf(fp, "%d %49s %d %f\n",
                  &arrStudents[StudentCount].iId,
                  arrStudents[StudentCount].chName,
                  &arrStudents[StudentCount].iYear,
                  &arrStudents[StudentCount].fCGPA) == 4)
    {
        StudentCount++;

        // Keep track of max ID to ensure new students get unique IDs
        if (arrStudents[StudentCount - 1].iId > maxId)
        {
            maxId = arrStudents[StudentCount - 1].iId;
        }

        // Call EnsureCapacity only when adding new students (outside of the loading loop)
        if (StudentCount >= Capacity)
        {
            EnsureCapacity();
        }
    }

    fclose(fp);
    printf("Data loaded successfully from file.\n");

    // Ensure new students get unique IDs
    StudentCount = maxId;
}

void EnsureCapacity(void)
{
    if (StudentCount >= Capacity)
    {
        Capacity = (Capacity == 0) ? 10 : Capacity * 2;

        struct Student* temp = NULL;

        temp = realloc(arrStudents, Capacity * sizeof(struct Student));

        if (NULL == temp)
        {
            printf("Memory realloction failed!!\n");
            return;
        }

        arrStudents = temp;
    }
}

void FreeMemory(void)
{
    if (arrStudents != NULL)
    {
        free(arrStudents);
        printf("Memory freed Succesfully!!\n\n");
    }
}

void SortStudentsByName(void)
{
    int iCounter1, iCounter2;

    for (iCounter1 = 0; iCounter1 < StudentCount - 1; iCounter1++)
    {
        for (iCounter2 = iCounter1 + 1; iCounter2 < StudentCount; iCounter2++)
        {
            if (strcmp(arrStudents[iCounter1].chName, arrStudents[iCounter2].chName) > 0)
            {
                struct Student temp = arrStudents[iCounter1];
                arrStudents[iCounter1] = arrStudents[iCounter2];
                arrStudents[iCounter2] = temp;
            }
        }
    }
}

void SortStudentsByCgpa(void)
{
    int iCounter1, iCounter2;

    for (iCounter1 = 0; iCounter1 < StudentCount - 1; iCounter1++)
    {
        for (iCounter2 = iCounter1 + 1; iCounter2 < StudentCount; iCounter2++)
        {
            if (arrStudents[iCounter1].fCGPA > arrStudents[iCounter2].fCGPA)
            {
                struct Student temp = arrStudents[iCounter1];
                arrStudents[iCounter1] = arrStudents[iCounter2];
                arrStudents[iCounter2] = temp;
            }
        }
    }
}

void SortStudentsByYear(void)
{
    int iCounter1, iCounter2;

    for (iCounter1 = 0; iCounter1 < StudentCount - 1; iCounter1++)
    {
        for (iCounter2 = iCounter1 + 1; iCounter2 < StudentCount; iCounter2++)
        {
            if (arrStudents[iCounter1].iYear > arrStudents[iCounter2].iYear)
            {
                struct Student temp = arrStudents[iCounter1];
                arrStudents[iCounter1] = arrStudents[iCounter2];
                arrStudents[iCounter2] = temp;
            }
        }
    }
}