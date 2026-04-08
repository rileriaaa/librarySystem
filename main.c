#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

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
    char id[20];
    char title[50];
    char author[50];
    char copyright[50];
    char publisher[50];
    char category[50];
}Book;

typedef struct {
    char userId[20];
    char userType[20];
    char bookId[20];
    char dateBorrowed[20];
    char dateReturned[20];
    float penalty;
    bool isReturned;
}Record;

int main(){
    Student students[50];
    Faculty faculty[50];
    Book books;
    Record borrowedRecords[100];

    char userProfile, mainMenu, bookCategory, borrowUserType, returnUserType, userProfileTryAgain, returnTryAgain, borrowTryAgain;
    bool status = true, returnStatus = true, borrowStatus = true, userProfileStatus = true;

    while (status) {
        printf("MENU \n");
        printf("[A] – BORROW\n");
        printf("[B] – RETURN\n");
        printf("[C] – USERS PROFILE\n");
        printf("[D] – REPORTS\n");
        printf("[E] – EXIT\n");
        printf("Select your answer: ");
        scanf("%c", &mainMenu);

        switch (mainMenu) {
            case 'a': 
                printf("BORROW MENU \n");
                printf("Input user type:\n");
                printf("[a] student\n");
                printf("[b] faculty\n");
                printf("Select your answer:\n");
                scanf("%c", &borrowUserType);

                switch (borrowUserType) {
                    case 'a':
                        printf("User type: %s\n");
                        printf("Student id: %s\n");
                        scanf("");
                        printf("Name: ");
                        scanf("");
                        printf("Course: ");
                        scanf("");
                    
                    case 'b':
                        printf("User type: %s\n");
                        printf("Student id: %s\n");
                        scanf("");
                        printf("Name: ");
                        scanf("");
                        printf("Department: ");
                        scanf("");

                    default:
                        printf("invalid, try again.");
                }

                while (borrowStatus) {
                    printf("BOOK CATEGORY \n");
                    printf("[A] – COMPUTER\n");
                    printf("[B] – MATHEMATICS\n");
                    printf("[C] – SCIENCES\n");
                    printf("[D] – BACK\n");
                    printf("Select your answer:\n");
                    scanf("%c", &bookCategory);

                    switch (bookCategory){
                        case 'A':
                            printf("COMPUTER CATEGORY\n");
                            printf("[A] – Intermediate Programming\n");
                            printf("[B] – Digital Logic\n");
                            printf("[C] – BACK\n");
                            printf("Select your answer:\n");
                            scanf("");
                            printf("Book id: \n");
                            scanf("");
                            printf("\tBook title: ");
                            printf("\tAuthor: ");
                            printf("\tCopyright: ");
                            printf("\tPublisher: ");
                            printf("Date Borrowed: %s \n");
                            printf("Do you want to borrow this?[y/n]: ");
                            scanf("");
                            printf("This book was added to your account \n");
                            printf("Do you want to try again?: ");
                            scanf("%c", &borrowTryAgain);

                            if (borrowTryAgain == 'y'){
                                break;
                            } else {
                                borrowStatus = false;
                                break;
                            }
                        
                        case 'B':
                            printf("MATHEMATICS CATEGORY\n");
                            printf("[A] – Differential Calculus\n");
                            printf("[B] – Discrete Mathematics\n");
                            printf("[C] – BACK\n");
                            printf("Select your answer:\n");
                            scanf("");
                            printf("Book id: \n");
                            scanf("");
                            printf("\tBook title: ");
                            printf("\tAuthor: ");
                            printf("\tCopyright: ");
                            printf("\tPublisher: ");
                            printf("Date Borrowed: %s \n");
                            printf("Do you want to borrow this?[y/n]: ");
                            scanf("");
                            printf("This book was added to your account \n");
                            printf("Do you want to try again?: ");
                            scanf("%c", &borrowTryAgain);

                            if (borrowTryAgain == 'y'){
                                break;
                            } else {
                                borrowStatus = false;
                                break;
                            }
                        
                        case 'C':
                            printf("SCIENCES CATEGORY\n");
                            printf("[A] – General Microbiology\n");
                            printf("[B] – Biological Evolution\n");
                            printf("[C] – BACK\n");
                            printf("Select your answer:\n");
                            scanf("");
                            printf("Book id: \n");
                            scanf("");
                            printf("\tBook title: ");
                            printf("\tAuthor: ");
                            printf("\tCopyright: ");
                            printf("\tPublisher: ");
                            printf("Date Borrowed: %s \n");
                            printf("Do you want to borrow this?[y/n]: ");
                            scanf("");
                            printf("This book was added to your account \n");
                            printf("Do you want to try again?: ");
                            scanf("%c", &borrowTryAgain);

                            if (borrowTryAgain == 'y'){
                                break;
                            } else {
                                borrowStatus = false;
                                break;
                            }

                        case 'D':
                            borrowStatus = false;
                            break;
                        
                        default:
                            printf("invalid, try again.");
                    }
                }

            break;
            
            case 'b':
                while (returnStatus) {
                    printf("RETURN MENU \n");
                    printf("Input user type: \n");
                    printf("[a] student\n");
                    printf("[b] faculty\n");
                    printf("Select your answer:\n");
                    scanf("%c", &returnUserType);
                    
                    switch (returnUserType) {
                        case 'a':
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

                        
                        case 'b':
                            printf("User type: %s\n");
                            printf("Employee id:");
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
            
            case 'c':
                printf("USERS PROFILE:");
                printf("Input user type:");
                printf("[a] student");
                printf("[b] faculty ");
                printf("[c] back");
                printf("Select your answer:");
                scanf("%c", &userProfile);

                switch (userProfile){
                    case 'a':
                        while (userProfileStatus) {
                        printf("Student id: ");
                        scanf("");
                        printf("Name:");
                        scanf("");
                        printf("Course:");
                        scanf("");
                        printf("Year Level:");
                        scanf("");
                        printf("Do you want to save? y/n:");
                        scanf("%c", &userProfileTryAgain);

                        if (userProfileTryAgain == 'y'){
                            // append user

                            break;

                        }

                     }
                    
                    case 'b':
                        while (userProfileStatus) {
                            printf("Employee id: ");
                            scanf("");
                            printf("Name:");
                            scanf("");
                            printf("Department:");
                            scanf("");
                            printf("Position:");
                            scanf("");
                            printf("Do you want to save? y/n:");
                            scanf("%c", &userProfileTryAgain);

                            if (userProfileTryAgain == 'y'){
                                // append user

                                break;

                            }
                        }
                    
                    default:
                        printf("invalid, please try again");
                }

            case 'd':
                printf("REPORTS MENU");
                printf("[1] Borrowed Books");
                printf("[2] Returned Book");
                printf("[3] Students Profile Report");
                printf("[4] Faculty Profile Report");
                printf("slect ur answer: ");
                scanf("");

            
            case 'e':
                printf("The system will close now.");
                break;
            
            default:
                printf("invalid, please try again.");

        }
    }

    
    
}