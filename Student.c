#include <stdio.h>
#define MAX 100

struct Student
{
    int iId;
    int iYear;
    char chName[50];
    float fCGPA;
};

struct Student arrStudents[MAX];
int StudentCount = 0;
int iContinue = 1;

void AddStudent(void);
void UpdateStudent(void);
void SearchStudent(void);
void DeleteStudent(void);
void DisplayStudents(void);
void SaveTableToFile(void);
void LoadFromFile(void);

int main(void)
{
    LoadFromFile();
    int iChoice;

    while (iContinue)
    {
        printf("=====================   STUDENT MANAGEMENT SYSTEM   =====================\n\n");
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
            return 0;

        default:
            printf("Enter a valid operation choice!!\n");
        }
    }

    getch();
    return 0;
}

void AddStudent(void)
{
    iContinue = 0;
    int iNumberOfStudentsToAdd, iCounter;

    printf("Enter the number of students you want to add:\t");
    scanf("%d", &iNumberOfStudentsToAdd);

    for (iCounter = 0; iCounter < iNumberOfStudentsToAdd; iCounter++)
    {
        if (StudentCount >= MAX)
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

        printf("Enter Year of Study:\t");
        scanf("%d", &student.iYear);

        printf("Enter CGPA of the Student:\t");
        scanf("%f", &student.fCGPA);

        arrStudents[StudentCount] = student;
        StudentCount++;

        printf("Student Data Added Succesfully!!\n");
    }

    printf("To continue enter 1");
    scanf("%d", &iContinue);
}

void UpdateStudent(void)
{
    iContinue = 0;
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

            printf("Enter year of Student:\t");
            scanf("%d", &arrStudents[iCounter].iYear);

            printf("Enter CGPA of Student:\t");
            scanf("%f", &arrStudents[iCounter].fCGPA);

            printf("Student information updated successfully!!\n");

            printf("To continue enter 1: ");
            scanf("%d", &iContinue);
            return;
        }
    }
    printf("No student with the entered roll number exists!!\n");

    printf("To continue enter 1: ");
    scanf("%d", &iContinue);
}

void SearchStudent(void)
{
    iContinue = 0;
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

    printf("To continue enter 1");
    scanf("%d", &iContinue);
}

void DeleteStudent(void)
{
    iContinue = 0;
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

    printf("To continue enter 1");
    scanf("%d", &iContinue);
}

void DisplayStudents(void)
{
    iContinue = 0;
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
    printf("To continue enter 1");
    scanf("%d", &iContinue);
}

void SaveTableToFile(void)
{
    FILE *fp = fopen("student_table.txt", "w");
    if (fp == NULL)
    {
        printf("Error saving data to file!\n");
        return;
    }

    fseek(fp, 0,SEEK_END);

    if(ftell(fp) == 0)
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

    char buffer[200];
    int maxId = 0;

    // Skip the header
    fgets(buffer, sizeof(buffer), fp); // Skip "ID    Name..."
    fgets(buffer, sizeof(buffer), fp); // Skip "--------------------------------------------"

    // Read student data from the file
    while (fscanf(fp, "%d %s %d %f\n",
                  &arrStudents[StudentCount].iId,
                  arrStudents[StudentCount].chName,
                  &arrStudents[StudentCount].iYear,
                  &arrStudents[StudentCount].fCGPA) == 4)
    {
        if (arrStudents[StudentCount].iId > maxId)
        {
            maxId = arrStudents[StudentCount].iId; // Update max ID
        }
        StudentCount++;
    }

    fclose(fp);
    printf("Data loaded successfully from file.\n");

    // Ensure new students get unique IDs
    StudentCount = maxId;
}
