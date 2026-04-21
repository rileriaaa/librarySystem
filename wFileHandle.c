#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

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

void getCurrentDate(char result[])
{
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(result, 20, "%Y-%m-%d", tm_info);
}

void toUpperCase(char str[])
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        str[i] = toupper(str[i]);
    }
}

void toTitleCase(char str[])
{
    int capitalizeNext = 1;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == ' ')
        {
            capitalizeNext = 1;
        }
        else if (capitalizeNext)
        {
            str[i] = toupper(str[i]);
            capitalizeNext = 0;
        }
        else
        {
            str[i] = tolower(str[i]);
        }
    }
}

int dateToDays(char date[])
{
    int year, month, day;
    sscanf(date, "%d-%d-%d", &year, &month, &day);

    return year * 365 + month * 30 + day;
}

float calculatePenalty(char dateBorrowed[], char dateReturned[], char userType[], int allowedDays)
{
    int borrowed = dateToDays(dateBorrowed);
    int returned = dateToDays(dateReturned);
    int daysHeld = returned - borrowed;
    int daysOverdue = daysHeld - allowedDays;

    if (daysOverdue <= 0)
        return 0;

    float rate = (strcmp(userType, "STUDENT") == 0) ? 5.00 : 10.00;
    return daysOverdue * rate;
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
        fprintf(fp, "%s,%s,%s,%d\n",
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
        fprintf(fp, "%s,%s,%s,%s\n",
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
        fprintf(fp, "%s,%s,%s,%s,%s,%.2f,%d\n",
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
        printf("no students file found, creating new one.");
        return 0;
    }

    int count = 0;
    while (fscanf(fp, "%[^,],%[^,],%[^,],%d\n",
                  students[count].id,
                  students[count].name,
                  students[count].course,
                  &students[count].yearLevel) == 4)
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
        printf("no faculty file found, creating new one.");
        return 0;
    }

    int count = 0;
    while (fscanf(fp, "%[^,],%[^,],%[^,],%[^\n]\n",
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
    FILE *fp = fopen("records.csv", "r");
    if (fp == NULL)
    {
        printf("no records file found, creating new one.");
        return 0;
    }

    int count = 0;
    int isReturned;
    while (fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^,],%f,%d\n",
                  records[count].userId,
                  records[count].userType,
                  records[count].bookId,
                  records[count].dateBorrowed,
                  records[count].dateReturned,
                  &records[count].penalty,
                  &isReturned) == 7)
    {
        records[count].isReturned = isReturned;
        count++;
    }
    fclose(fp);
    return count;
}

void showBooksDetails(char category[], Book books[], int bookCount, bool *borrowStatus,
                      Record records[], int *recordCount, char userId[], char userType[])
{
    char choice;
    int index = 0;
    int bookIndices[2];
    char confirm;
    char today[20];
    getCurrentDate(today);

    for (int i = 0; i < bookCount; i++)
    {
        if (strcmp(books[i].category, category) == 0)
        {
            printf("[%c] - %s\n", 'A' + index, books[i].title);
            bookIndices[index] = i;
            index++;
        }
    }
    printf("[C] - Back\n");
    printf("Select your answer: ");
    scanf(" %c", &choice);
    char upperChoice = toupper(choice);

    if (upperChoice == 'C')
        return;

    int selectedBook = -1;
    if (upperChoice >= 'A' && upperChoice <= 'A' + index)
    {
        selectedBook = bookIndices[upperChoice - 'A'];
    }

    if (selectedBook == -1)
    {
        printf("invalid, try again.\n");
        return;
    }

    printf("Book id: %s\n", books[selectedBook].id);
    printf("\tBook title: %s\n", books[selectedBook].title);
    printf("\tAuthor: %s\n", books[selectedBook].author);
    printf("\tCopyright: %s\n", books[selectedBook].copyright);
    printf("\tPublisher: %s\n", books[selectedBook].publisher);

    printf("do you want to borrow this book? [Y/N]: ");
    scanf(" %c", &confirm);
    char upperConfirm = toupper(confirm);

    if (upperConfirm == 'Y')
    {
        // add to records
        strcpy(records[*recordCount].userId, userId);
        strcpy(records[*recordCount].userType, userType);
        strcpy(records[*recordCount].bookId, books[selectedBook].id);
        strcpy(records[*recordCount].dateBorrowed, today); // dynamic date // change date for simulation par
        strcpy(records[*recordCount].dateReturned, "N/A");
        records[*recordCount].penalty = 0;
        records[*recordCount].isReturned = false;
        (*recordCount)++;
        saveRecords(records, *recordCount);
        printf("Book added to your account!\n");
    }

    char tryAgain;
    printf("do you want to try again? [Y/N]: ");
    scanf(" %c", &tryAgain);
    if (toupper(tryAgain) == 'N')
    {
        *borrowStatus = false;
    }
}

int main()
{
    Student students[50];
    Faculty faculty[50];
    Record borrowedRecords[100];

    char userProfile, mainMenu, bookCategory, borrowUserType, returnUserType, userProfileTryAgain, reportsMenu, searchIdReturn[20];
    bool status = true, returnStatus = true, borrowStatus = true, userProfileStatus = true;

    int studentCount = loadStudents(students);
    int facultyCount = loadFaculty(faculty);
    int recordCount = loadRecords(borrowedRecords);

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

            char currentUserId[20];
            char currentUserType[20];

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

                strcpy(currentUserId, students[found].id);
                strcpy(currentUserType, "STUDENT");

                printf("\tName: %s\n", students[found].name);
                printf("\tCourse: %s\n", students[found].course);
                printf("\tYear Level: %d\n", students[found].yearLevel);
                userFound = true;

                for (int i = 0; i < recordCount; i++)
                {
                    if (strcmp(borrowedRecords[i].userId, currentUserId) == 0 &&
                        !borrowedRecords[i].isReturned)
                    {
                        printf("You still have an unreturned book! please return it furst.\n");
                        userFound = false;
                        break;
                    }
                }
                break;
            }

            case 'B':
            {
                char searchId[20];
                printf("User type: Faculty\n");
                printf("Employee id: ");
                scanf(" %s", searchId);
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

                strcpy(currentUserId, faculty[found].id);
                strcpy(currentUserType, "FACULTY");

                printf("\tName: %s\n", faculty[found].name);
                printf("\tDepartment: %s\n", faculty[found].department);
                printf("\tPosition: %s\n", faculty[found].position);
                userFound = true;

                for (int i = 0; i < recordCount; i++)
                {
                    if (strcmp(borrowedRecords[i].userId, currentUserId) == 0 &&
                        !borrowedRecords[i].isReturned)
                    {
                        printf("You still have an unreturned book! please return it furst.\n");
                        userFound = false;
                        break;
                    }
                }

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
                        showBooksDetails("COMPUTER", books, 6, &borrowStatus, borrowedRecords, &recordCount, currentUserId, currentUserType);
                        break;

                    case 'B':
                        showBooksDetails("MATHEMATICS", books, 6, &borrowStatus, borrowedRecords, &recordCount, currentUserId, currentUserType);
                        break;

                    case 'C':
                        showBooksDetails("SCIENCES", books, 6, &borrowStatus, borrowedRecords, &recordCount, currentUserId, currentUserType);
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

                    char returnBookId[20];
                    printf("input book id: ");
                    scanf(" %s", returnBookId);
                    while (getchar() != '\n')
                        ;

                    int recordFound = -1;
                    for (int i = 0; i < recordCount; i++)
                    {
                        if (strcmp(borrowedRecords[i].userId, searchIdReturn) == 0 &&
                            strcmp(borrowedRecords[i].bookId, returnBookId) == 0 &&
                            !borrowedRecords[i].isReturned)
                        {
                            recordFound = i;
                            break;
                        }
                    }

                    if (recordFound == -1)
                    {
                        printf("no active borrow record found.");
                        break;
                    }

                    printf("\tDate Borrowed: %s\n", borrowedRecords[recordFound].dateBorrowed);

                    char today[20];
                    getCurrentDate(today);
                    int allowedDays = 3;
                    float penalty = calculatePenalty(borrowedRecords[recordFound].dateBorrowed, today, "STUDENT", allowedDays);

                    printf("Date Returned: %s\n", today);
                    printf("No. of days: %d\n", dateToDays(today) - dateToDays(borrowedRecords[recordFound].dateBorrowed));
                    printf("Penalty: %.2f\n", penalty);

                    if (penalty > 0)
                    {
                        float amountReceived;
                        printf("Amound received: ");
                        scanf("%f", &amountReceived);
                        while (getchar() != '\n')
                            ;
                        printf("Change: %.2f\n", amountReceived - penalty);
                    }

                    strcpy(borrowedRecords[recordFound].dateReturned, today);
                    borrowedRecords[recordFound].penalty = penalty;
                    borrowedRecords[recordFound].isReturned = true;
                    saveRecords(borrowedRecords, recordCount);

                    printf("Book returned successfully. See you again!");

                    char goBbackk = ' ';
                    printf("Go back to main menu? [Y/N]: ");
                    scanf(" %c", &goBbackk);
                    while (getchar() != '\n')
                        ;
                    if (toupper(goBbackk) == 'Y')
                    {
                        returnStatus = false;
                    }

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

                    char returnBookId[20];
                    printf("input book id: ");
                    scanf(" %s", returnBookId);
                    while (getchar() != '\n')
                        ;

                    int recordFound = -1;
                    for (int i = 0; i < recordCount; i++)
                    {
                        if (strcmp(borrowedRecords[i].userId, searchIdReturn) == 0 &&
                            strcmp(borrowedRecords[i].bookId, returnBookId) == 0 &&
                            !borrowedRecords[i].isReturned)
                        {
                            recordFound = i;
                            break;
                        }
                    }

                    if (recordFound == -1)
                    {
                        printf("no active borrow record found.");
                        break;
                    }

                    printf("\tDate Borrowed: %s\n", borrowedRecords[recordFound].dateBorrowed);

                    char today[20];
                    getCurrentDate(today);
                    int allowedDays = 5;
                    float penalty = calculatePenalty(borrowedRecords[recordFound].dateBorrowed, today, "STUDENT", allowedDays);

                    printf("Date Returned: %s\n", today);
                    printf("No. of days: %d\n", dateToDays(today) - dateToDays(borrowedRecords[recordFound].dateBorrowed));
                    printf("Penalty: %.2f\n", penalty);

                    if (penalty > 0)
                    {
                        float amountReceived;
                        printf("Amound received: ");
                        scanf("%f", &amountReceived);
                        while (getchar() != '\n')
                            ;
                        printf("Change: %.2f\n", amountReceived - penalty);
                    }

                    strcpy(borrowedRecords[recordFound].dateReturned, today);
                    borrowedRecords[recordFound].penalty = penalty;
                    borrowedRecords[recordFound].isReturned = true;
                    saveRecords(borrowedRecords, recordCount);

                    printf("Book returned successfully. See you again!");

                    char goBbackk = ' ';
                    printf("Go back to main menu? [Y/N]: ");
                    scanf(" %c", &goBbackk);
                    while (getchar() != '\n')
                        ;
                    if (toupper(goBbackk) == 'Y')
                    {
                        returnStatus = false;
                    }

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
                    toTitleCase(students[studentCount].name);
                    while (getchar() != '\n')
                        ;

                    printf("Course: ");
                    scanf("%[^\n]", students[studentCount].course);
                    toUpperCase(students[studentCount].course);
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
                            saveStudents(students, studentCount);
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
                    scanf("%[^\n]", faculty[facultyCount].name);
                    toTitleCase(faculty[facultyCount].name);
                    while (getchar() != '\n')
                        ;

                    printf("Department: ");
                    scanf("%[^\n]", faculty[facultyCount].department);
                    toTitleCase(faculty[facultyCount].department);
                    while (getchar() != '\n')
                        ;

                    printf("Position: ");
                    scanf("%[^\n]", faculty[facultyCount].position);
                    toTitleCase(faculty[facultyCount].position);
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
                            saveFaculty(faculty, facultyCount);
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
            printf("REPORTS MENU\n");
            printf("[A] Borrowed Books\n");
            printf("[B] Returned Book\n");
            printf("[C] Students Profiles\n");
            printf("[D] Faculty Profiles\n");
            printf("[E] Back\n");
            printf("plz select: ");
            scanf(" %c", &reportsMenu);
            printf("\n");
            char upperReportsMenu = toupper(reportsMenu);

            switch (upperReportsMenu)
            {
            case 'A':
                printf("Borrowed Books\n");
                for (int i = 0; i < recordCount; i++)
                {
                    if (!borrowedRecords[i].isReturned)
                    {
                        printf("User Type: %s | User: %s | Book: %s | Date: %s\n",
                               borrowedRecords[i].userType,
                               borrowedRecords[i].userId,
                               borrowedRecords[i].bookId,
                               borrowedRecords[i].dateBorrowed);
                    }
                }
                break;

            case 'B':
                printf("Returned Books\n");
                for (int i = 0; i < recordCount; i++)
                {
                    if (!borrowedRecords[i].isReturned)
                    {
                        printf("User Type: %s | User: %s | Book: %s | Date: %s\n",
                               borrowedRecords[i].userType,
                               borrowedRecords[i].userId,
                               borrowedRecords[i].bookId,
                               borrowedRecords[i].dateBorrowed);
                    }
                }
                break;

            case 'C':
                printf("Student Profiles\n");
                for (int i = 0; i < studentCount; i++)
                {
                    printf("ID: %s | Name: %s | Course: %s | Year: %d\n",
                           students[i].id,
                           students[i].name,
                           students[i].course,
                           students[i].yearLevel);
                }
                break;

            case 'D':
                printf("Faculty Profiles\n");
                for (int i = 0; i < facultyCount; i++)
                {
                    printf("ID: %s | Name: %s | Dept: %s | Position: %s\n",
                           faculty[i].id,
                           faculty[i].name,
                           faculty[i].department,
                           faculty[i].position);
                }
                break;

            case 'E':
                break;

            default:
                printf("invalid, try again.\n");
            }

            break;
        }

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