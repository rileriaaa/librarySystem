#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

typedef struct
{
    char id[20];
    char title[50];
    char author[50];
    char copyright[20];
    char publisher[50];
    char category[50];
} Book;

typedef struct
{
    char id[20];
    char name[50];
    char course[50];
    int yearLevel;
} Student;

typedef struct
{
    char id[20];
    char name[50];
    char department[50];
    char position[50];
} Faculty;

typedef struct
{
    char userId[20];
    char userType[20];
    char bookId[20];
    char dateBorrowed[20];
    char dateReturned[20];
    float penalty;
    bool isReturned;
} Record;

Book books[6] = {
    {"INPR111", "Intermediate Programming", "Mrs. Chua", "2020", "Test Publish", "COMPUTER"},
    {"C0002", "Digital Logic", "Mr. Santos", "2020", "Test Publisher", "COMPUTER"},
    {"M0001", "Differential Calculus", "Ms. Reyes", "2018", "Test Publisher", "MATHEMATICS"},
    {"M0002", "Discrete Mathematics", "Mr. Cruz", "2021", "Test Publisher", "MATHEMATICS"},
    {"S0001", "General Microbiology", "Ms. Lim", "2017", "Test Publisher", "SCIENCES"},
    {"S0002", "Biological Evolution", "Mr. Garcia", "2019", "Test Publisher", "SCIENCES"},
};

void showBooksDetails(char category[], Book books[], int bookCount, bool *borrowStatus)
{
    char choice;

    int index = 0;
    for (int i = 0; i < bookCount; i++)
    {
        if (strcmp(books[i].category, category) == 0)
        {
            printf("[%c] - %s\n", 'A' + index, books[i].title);
            index++;
        }
    }
    printf("[C] - Back\n");
    printf("Select your answer: ");
    scanf(" %c", &choice);

    if (choice == 'C')
        return;
}

void saveStudents(Student students[], int count)
{
    FILE *fp = fopen("students.csv", "w");
    if (fp == NULL)
    {
        printf("Error Saving Students.\n");
        return;
    }
    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "%s %s %s %d\n",
                students[i].id,
                students[i].name,
                students[i].course,
                students[i].yearLevel);
    }
    fclose(fp);
}

void saveFaculty(Faculty faculty[], int count)
{
    FILE *fp = fopen("faculty.csv", "w");
    if (fp == NULL)
    {
        printf("Error Saving faculty.\n");
        return;
    }
    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "%s %s %s %d\n",
                faculty[i].id,
                faculty[i].name,
                faculty[i].department,
                faculty[i].position);
    }
    fclose(fp);
}

void saveRecords(Record records[], int count)
{
    FILE *fp = fopen("records.csv", "w");
    if (fp == NULL)
    {
        printf("Error saving reciords.\n");
        return;
    }
    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "%s %s %s %d\n",
                records[i].userId,
                records[i].userType,
                records[i].bookId,
                records[i].dateBorrowed,
                records[i].dateReturned,
                records[i].penalty,
                records[i].isReturned);
    }
    fclose(fp);
}

int loadStudents(Student students[])
{
    FILE *fp = fopen("students.csv", "r");
    if (fp == NULL)
    {
        printf("no found file, creating new one.");
        return 0;
    }

    int count = 0;
    while (fscanf(fp, "%[^,],%[^,],%[^,],%d\n",
                  students[count].id,
                  students[count].name,
                  students[count].course,
                  students[count].yearLevel) == 4)
    {
        count++;
    }
    fclose(fp);
    return count;
}

int loadFaculty(Faculty faculty[])
{
    FILE *fp = fopen("faculty.csv", "r");
    if (fp == NULL)
    {
        printf("no found file, creating new one.");
        return 0;
    }

    int count = 0;
    while (fscanf(fp, "%[^,],%[^,],%[^,],%d\n",
                  faculty[count].id,
                  faculty[count].name,
                  faculty[count].department,
                  faculty[count].position) == 4)
    {
        count++;
    }
    fclose(fp);
    return count;
}

int loadRecords(Record records[])
{
    FILE *fp = fopen("students.csv", "r");
    if (fp == NULL)
    {
        printf("no found file, creating new one.");
        return 0;
    }

    int count = 0;
    while (fscanf(fp, "%[^,],%[^,],%[^,],%d\n",
                  records[count].userId,
                  records[count].userType,
                  records[count].bookId,
                  records[count].dateBorrowed,
                  records[count].dateReturned,
                  records[count].penalty,
                  records[count].isReturned) == 7)
    {
        count++;
    }
    fclose(fp);
    return count;
}

int main()
{
    int studentCount = 0, facultyCount = 0;
    Student students[50];
    Faculty faculty[50];
    Record borrowedRecords[100];

    char userProfile, mainMenu, bookCategory, borrowUserType, returnUserType, userProfileTryAgain, returnTryAgain, borrowTryAgain, reportsMenu, searchIdReturn[20];
    bool status = true, returnStatus = true, borrowStatus = true, userProfileStatus = true;

    while (status)
    {
        printf("\nMENU \n");
        printf("[A] BORROW\n");
        printf("[B] RETURN\n");
        printf("[C] USERS PROFILE\n");
        printf("[D] REPORTS\n");
        printf("[E] EXIT\n");
        printf("plz select: ");
        scanf(" %c", &mainMenu);
        printf("\n");
        char upperMainMenu = toupper(mainMenu);

        switch (upperMainMenu)
        {
        case 'A':
        {
            printf("BORROW MENU \n");
            printf("Input user type:\n");
            printf("[A] student\n");
            printf("[B] faculty\n");
            printf("Select your answer: ");
            scanf(" %c", &borrowUserType);
            printf("\n");
            char upperBorrowUserType = toupper(borrowUserType);

            bool userFound = false;
            switch (upperBorrowUserType)
            {

            case 'A':
            {
                char searchId[20];
                printf("User type: Student\n");
                printf("Student id: ");
                scanf(" %s", searchId);

                int found = -1;
                for (int i = 0; i < studentCount; i++)
                {
                    if (strcmp(students[i].id, searchId) == 0)
                    {
                        found = i;
                        break;
                    }
                }

                if (found == -1)
                {
                    printf("Student not found. Please register first.\n");
                    break;
                }

                printf("\tName: %s\n", students[found].name);
                printf("\tCourse: %s\n", students[found].course);
                printf("\tYear Level: %d\n", students[found].yearLevel);
                userFound = true;
                break;
            }

            case 'B':
            {
                char searchId[20];
                printf("User type: Faculty\n");
                printf("Employee id: ");
                scanf(" %s", &searchId);
                printf("\n");

                int found = -1;
                for (int i = 0; i < facultyCount; i++)
                {
                    if (strcmp(faculty[i].id, searchId) == 0)
                    {
                        found = i;
                        break;
                    }
                }

                if (found == -1)
                {
                    printf("Employee not found. Please register first.\n");
                    break;
                }

                printf("\tName: %s\n", faculty[found].name);
                printf("\tDepartment: %s\n", faculty[found].department);
                printf("\tPosition: %s\n", faculty[found].position);
                userFound = true;
                break;
            }
            default:
                printf("invalid, try again.\n");
            }

            if (userFound)
            {
                borrowStatus = true;
                while (borrowStatus)
                {
                    printf("BOOK CATEGORY \n");
                    printf("[A] COMPUTER\n");
                    printf("[B] MATHEMATICS\n");
                    printf("[C] SCIENCES\n");
                    printf("[D] BACK\n");
                    printf("Select your answer: ");
                    scanf(" %c", &bookCategory);
                    printf("\n");

                    char upperBookCategory = toupper(bookCategory);

                    switch (upperBookCategory)
                    {
                    case 'A':
                        showBooksDetails("COMPUTER", books, 6, &borrowStatus);
                        break;

                    case 'B':
                        showBooksDetails("MATHEMATICS", books, 6, &borrowStatus);
                        break;

                    case 'C':
                        showBooksDetails("SCIENCES", books, 6, &borrowStatus);
                        break;

                    case 'D':
                        borrowStatus = false;
                        break;

                    default:
                        printf("invalid, try again.\n");
                    }
                }
            }

            break;
        }

        case 'B':
        {
            while (returnStatus)
            {
                printf("\nRETURN MENU \n");
                printf("Input user type: \n");
                printf("[A] student\n");
                printf("[B] faculty\n");
                printf("[C] back\n");
                printf("Select your answer: ");
                scanf(" %c", &returnUserType);
                while (getchar() != '\n')
                    ;
                printf("\n");

                char upperReturnUserType = toupper(returnUserType);

                // search user - error handling - print logs

                switch (upperReturnUserType)
                {
                case 'A':
                {
                    printf("User type: Student\n");
                    printf("Student id: ");
                    scanf(" %s", searchIdReturn);
                    while (getchar() != '\n')
                        ;

                    int found = -1;
                    for (int i = 0; i < studentCount; i++)
                    {
                        if (strcmp(students[i].id, searchIdReturn) == 0)
                        {
                            found = i;
                            break;
                        }
                    }

                    if (found == -1)
                    {
                        printf("Student not found. please register first.\n");
                        break;
                    }

                    printf("\tName: %s\n", students[found].name);
                    printf("\tCourse: %s\n", students[found].course);
                    printf("\tYear Level: %d\n", students[found].yearLevel);

                    break;
                }

                case 'B':
                {
                    printf("User type: Employee\n");
                    printf("Employee id: ");
                    scanf(" %s", searchIdReturn);
                    while (getchar() != '\n')
                        ;
                    printf("\n");

                    int found = -1;
                    for (int i = 0; i < facultyCount; i++)
                    {
                        if (strcmp(faculty[i].id, searchIdReturn) == 0)
                        {
                            found = i;
                            break;
                        }
                    }

                    if (found == -1)
                    {
                        printf("employee not found. please register first.\n");
                        break;
                    }

                    printf("\tName: %s\n", faculty[found].name);
                    printf("\tDepartment: %s\n", faculty[found].department);
                    printf("\tPosition: %s\n", faculty[found].position);

                    break;
                }

                case 'C':
                    returnStatus = false;
                    break;

                default:
                    printf("invalid, plz try again.\n");
                }
            }

            break;
        }

        case 'C':
        {
            printf("USERS PROFILE:\n");
            printf("Input user type:\n");
            printf("[A] tudent\n");
            printf("[B] faculty\n");
            printf("[C] back\n");
            printf("Select your answer: ");
            scanf(" %c", &userProfile);
            while (getchar() != '\n')
                ;

            char upperUserProfile = toupper(userProfile);

            switch (upperUserProfile)
            {
            case 'A':
            {
                userProfileStatus = true;
                while (userProfileStatus)
                {
                    printf("Student id: ");
                    scanf(" %s", students[studentCount].id);
                    while (getchar() != '\n')
                        ;

                    printf("Name: ");
                    scanf("%[^\n]", students[studentCount].name);
                    while (getchar() != '\n')
                        ;

                    printf("Course: ");
                    scanf(" %s", students[studentCount].course);
                    while (getchar() != '\n')
                        ;

                    printf("Year Level: ");
                    scanf(" %i", &students[studentCount].yearLevel);
                    while (getchar() != '\n')
                        ;

                    printf("Do you want to save? y/n: ");
                    scanf(" %c", &userProfileTryAgain);
                    while (getchar() != '\n')
                        ;

                    char upperUserProfileTryAgain = toupper(userProfileTryAgain);

                    if (upperUserProfileTryAgain == 'Y')
                    {
                        int duplicate = -1;
                        for (int i = 0; i < studentCount; i++)
                        {
                            if (strcmp(students[i].id, students[studentCount].id) == 0)
                            {
                                duplicate = i;
                                break;
                            }
                        }

                        if (duplicate != -1)
                        {
                            printf("student already exists!\n");
                        }
                        else
                        {
                            studentCount++;
                            userProfileStatus = false;
                            printf("User Added Successfully.\n");
                        }
                    }
                }

                break;
            }

            case 'B':
                userProfileStatus = true;
                while (userProfileStatus)
                {
                    printf("Employee id: ");
                    scanf(" %s", faculty[facultyCount].id);
                    while (getchar() != '\n')
                        ;

                    printf("Name: ");
                    scanf(" %[^\n]", faculty[facultyCount].name);
                    while (getchar() != '\n')
                        ;

                    printf("Department: ");
                    scanf(" %s", faculty[facultyCount].department);
                    while (getchar() != '\n')
                        ;

                    printf("Position: ");
                    scanf(" %s", faculty[facultyCount].position);
                    while (getchar() != '\n')
                        ;

                    printf("Do you want to save? [Y/N]: ");
                    scanf(" %c", &userProfileTryAgain);
                    while (getchar() != '\n')
                        ;

                    printf("\n");
                    char upperUserProfileTryAgain = toupper(userProfileTryAgain);

                    if (upperUserProfileTryAgain == 'Y')
                    {
                        int duplicate = -1;
                        for (int i = 0; i < facultyCount; i++)
                        {
                            if (strcmp(faculty[i].id, faculty[facultyCount].id) == 0)
                            {
                                duplicate = i;
                                break;
                            }
                        }

                        if (duplicate != -1)
                        {
                            printf("employee already exists!\n");
                        }
                        else
                        {
                            facultyCount++;
                            userProfileStatus = false;
                            printf("User Added Successfully.\n");
                        }
                    }
                }

                break;

            case 'C':
                break;

            default:
                printf("invalid, please try again...\n");
            }

            break;
        }

        case 'D':
        {
            printf("REPORTS MENU");
            printf("[A] Borrowed Books");
            printf("[B] Returned Book");
            printf("[C] Students Profile Report");
            printf("[D] Faculty Profile Report");
            printf("[E] Back");
            printf("plz select: ");
            scanf(" %c", &reportsMenu);
            printf("\n");
            char upperReportsMenu = toupper(reportsMenu);

            break;
        }

            // csv printout

        case 'E':
        {
            printf("The system will close now.\n");
            status = false;
            break;
        }

        default:
        {
            printf("invalid, please try again.\n");
        }
        }
    }
}