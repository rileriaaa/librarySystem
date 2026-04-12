#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

typedef struct {
    char id[20];
    char title[50];
    char author[50];
    char copyright[20];
    char publisher[50];
    char category[50];
} Book;

typedef struct {
    char id[20];
    char name[50];
    char course[50];
    int yearLevel;
}Student;

typedef struct {
    char id[20];
    char name[50];
    char department[50];
    char position[50];
}Faculty;

typedef struct {
    char userId[20];
    char userType[20];
    char bookId[20];
    char dateBorrowed[20];
    char dateReturned[20];
    float penalty;
    bool isReturned;
}Record;

Book books[6] = {
    {"INPR111", "Intermediate Programming", "Mrs. Chua", "2020", "Test Publish", "COMPUTER"},
    {"C0002", "Digital Logic", "Mr. Santos", "2020", "Test Publisher", "COMPUTER"},
    {"M0001", "Differential Calculus", "Ms. Reyes", "2018", "Test Publisher", "MATHEMATICS"},
    {"M0002", "Discrete Mathematics", "Mr. Cruz", "2021", "Test Publisher", "MATHEMATICS"},
    {"S0001", "General Microbiology", "Ms. Lim", "2017", "Test Publisher", "SCIENCES"},
    {"S0002", "Biological Evolution", "Mr. Garcia", "2019", "Test Publisher", "SCIENCES"},
};

void showBooksDetails (char category[], Book books[], int bookCount, bool *borrowStatus) {
    char choice;

    int index = 0;
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].category, category) == 0){
            printf("[%c] - %s\n", 'A' + index, books[i].title);
        }
    }
    printf("[C] - Back");
    printf("Select your answer: ");
    scanf(" %c", &choice);

    if (choice == 'C') return; 
}

int main(){
    int studentCount = 0, facultyCount = 0;
    Student students[50];
    Faculty faculty[50];
    Record borrowedRecords[100];

    char userProfile, mainMenu, bookCategory, borrowUserType, returnUserType, userProfileTryAgain, returnTryAgain, borrowTryAgain, reportsMenu;
    bool status = true, returnStatus = true, borrowStatus = true, userProfileStatus = true;

    while (status) {
        printf("MENU \n");
        printf("[A] BORROW\n");
        printf("[B] RETURN\n");
        printf("[C] USERS PROFILE\n");
        printf("[D] REPORTS\n");
        printf("[E] EXIT\n");
        printf("Select your answer: ");
        scanf(" %c", &mainMenu);
        char upperMainMenu = toupper(mainMenu);

        switch (upperMainMenu) {
            case 'A': 
                printf("BORROW MENU \n");
                printf("Input user type:\n");
                printf("[A] student\n");
                printf("[B] faculty\n");
                printf("Select your answer: ");
                scanf(" %c", &borrowUserType);
                char upperBorrowUserType = toupper(borrowUserType);

                switch (upperBorrowUserType) {
                    case 'A':
                        char searchId;
                        printf("User type: Student\n");
                        printf("Student id: ");
                        scanf(" %s", &searchId);

                        int found = -1;
                        for (int i = 0; i < studentCount; i++) {
                            if (strcmp(students[i].id, searchId) == 0){
                                found = i;
                                break;
                            }
                        }

                        if (found == -1) {
                            printf("Student not found. Please register first.");
                            break;
                        }

                        printf("\tName: %s\n", students[found].name);
                        printf("\tCourse: %s\n", students[found].course);
                        printf("\tYear Level: %s\n", students[found].yearLevel);

                        break;

                    case 'B':
                       char searchId;
                        printf("User type: Faculty\n");
                        printf("Employee id: ");
                        scanf(" %s", &searchId);

                        int found = -1;
                        for (int i = 0; i < facultyCount; i++) {
                            if (strcmp(faculty[i].id, searchId) == 0){
                                found = i;
                                break;
                            }
                        }

                        if (found == -1) {
                            printf("Employee not found. Please register first.");
                            break;
                        }

                        printf("\tName: %s\n", faculty[found].name);
                        printf("\tDepartment: %s\n", faculty[found].department);
                        printf("\tPosition: %s\n", faculty[found].position);

                        break;

                    default:
                        printf("invalid, try again.");
                }

                while (borrowStatus) {
                    printf("BOOK CATEGORY \n");
                    printf("[A] COMPUTER\n");
                    printf("[B] MATHEMATICS\n");
                    printf("[C] SCIENCES\n");
                    printf("[D] BACK\n");
                    printf("Select your answer: ");
                    scanf(" %c", &bookCategory);
                    char upperBookCategory = toupper(bookCategory);

                    switch (upperBookCategory){
                        case 'A':
                            showBooksDetails("COMPUTER", books, 6, &borrowStatus);
                            break;

                            // printf("COMPUTER CATEGORY\n");
                            // printf("[A] – Intermediate Programming\n");
                            // printf("[B] – Digital Logic\n");
                            // printf("[C] – BACK\n");
                            // printf("Select your answer:\n");
                            // scanf("");
                            // printf("Book id: \n");
                            // scanf("");
                            // printf("\tBook title: ");
                            // printf("\tAuthor: ");
                            // printf("\tCopyright: ");
                            // printf("\tPublisher: ");
                            // printf("Date Borrowed: %s \n");
                            // printf("Do you want to borrow this?[y/n]: ");
                            // scanf("");
                            // printf("This book was added to your account \n");
                            // printf("Do you want to try again?: ");
                            // scanf("%c", &borrowTryAgain);

                            // if (borrowTryAgain == 'y'){
                            //     break;
                            // } else {
                            //     borrowStatus = false;
                            //     break;
                            // }
                        
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
                            printf("invalid, try again.");
                    }
                }

            break;
            
            case 'B':
                while (returnStatus) {
                    printf("RETURN MENU \n");
                    printf("Input user type: \n");
                    printf("[A] student\n");
                    printf("[B] faculty\n");
                    printf("Select your answer:");
                    scanf(" %c", &returnUserType);
                    char upperReturnUserType = toupper(returnUserType);
                    
                    // search user - error handling - print logs

                    switch (upperReturnUserType) {
                        case 'A':
                            printf("User type: %s\n");
                            printf("Student id:");
                            scanf("");

                            printf("\tName: \n");
                            printf("\tCourse: \n");
                            printf("\tInput book id: \n");
                            printf("\tBook title: \n");
                            printf("\tAuthor: \n");
                            printf("\tCopyright: \n");
                            printf("\tPublisher: \n");
                            printf("\tDate Borrowed: \n");

                            printf("Date Returned: \n");
                            printf("No. Of days: \n");
                            printf("Penalty: \n");
                            printf("Amount received: \n");
                            printf("Change: \n");
                            printf("Do you want to go back to main menu?[y/n]:");
                            scanf("%c", &returnTryAgain);

                            if (returnTryAgain == 'y') {
                                returnStatus = false;
                                break;
                            } else {
                                break;
                            }

                        
                        case 'B':
                            printf("User type: %s\n");
                            printf("Employee id: ");
                            scanf("");

                            printf("\tName: \n");
                            printf("\tCourse: \n");
                            printf("\tInput book id: \n");
                            printf("\tBook title: \n");
                            printf("\tAuthor: \n");
                            printf("\tCopyright: \n");
                            printf("\tPublisher: \n");
                            printf("\tDate Borrowed: \n");

                            printf("Date Returned: \n");
                            printf("No. Of days: \n");
                            printf("Penalty: \n");
                            printf("Amount received: \n");
                            printf("Change: \n");
                            printf("Do you want to go back to main menu?[y/n]:");
                            scanf("%c", &returnTryAgain);

                            if (returnTryAgain == 'y') {
                                returnStatus = false;
                                break;
                            } else {
                                break;
                            }
                    }
                }
            
            break;
            
            case 'C':
                printf("USERS PROFILE:\n");
                printf("Input user type:\n");
                printf("[A] tudent\n");
                printf("[B] faculty\n");
                printf("[C] back\n");
                printf("Select your answer: ");
                scanf(" %c", &userProfile);
                char upperUserProfile = toupper(userProfile);

                switch (upperUserProfile){
                    case 'A':
                        userProfileStatus = true;
                        while (userProfileStatus) {
                        printf("Student id: ");
                        scanf(" %s", students[studentCount].id);
                        printf("Name: ");
                        scanf(" %[^\n]", students[studentCount].name);
                        printf("Course: ");
                        scanf(" %s", students[studentCount].course);
                        printf("Year Level: ");
                        scanf(" %i", &students[studentCount].yearLevel);
                        printf("Do you want to save? y/n: ");
                        scanf(" %c", &userProfileTryAgain);
                        char upperUserProfileTryAgain = toupper(userProfileTryAgain);

                        if (upperUserProfileTryAgain == 'y'){
                            studentCount++;
                            userProfileStatus = false;
                        } else {
                            userProfileStatus = false ;
                        }

                     }
                    
                    case 'B':
                        userProfileStatus = true;
                        while (userProfileStatus) {
                            printf("Employee id: ");
                            scanf("%s", faculty[facultyCount].id);
                            printf("Name: ");
                            scanf(" %[^\n]", faculty[facultyCount].id);
                            printf("Department: ");
                            scanf(" %s", faculty[facultyCount].department);
                            printf("Position: ");
                            scanf(" %s", faculty[facultyCount].position);
                            printf("Do you want to save? [Y/N]: ");
                            scanf(" %c", &userProfileTryAgain);
                            char upperUserProfileTryAgain = toupper(userProfileTryAgain);

                            if (upperUserProfileTryAgain == 'Y'){
                                studentCount++;
                                userProfileStatus = false;
                            } else {
                                userProfileStatus = false;
                            }
                        }
                    
                    default:
                        printf("invalid, please try again");
                }

            case 'D':
                printf("REPORTS MENU");
                printf("[A] Borrowed Books");
                printf("[B] Returned Book");
                printf("[C] Students Profile Report");
                printf("[D] Faculty Profile Report");
                printf("[E] Back");
                printf("plz select: ");
                scanf(" %c", reportsMenu);
                char upperReportsMenu = toupper(reportsMenu);


                break;
            
            case 'E':
                printf("The system will close now.");
                break;
            
            default:
                printf("invalid, please try again.");

        }
    }

    
    
}