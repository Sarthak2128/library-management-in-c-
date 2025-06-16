#include <stdio.h>
#include <string.h>

int main() {
    char username[20], password[20];
    char correct_user[] = "admin", correct_pass[] = "1234";

    char book[20][50] = {
        "C Programming", "Digital Electronics",
        "Thermodynamics", "Basic Electrical", "Building Materials"
    };
    int total_books = 5;

    char issued_books[20][50], student_name[20][50];
    char student_branch[20][30], roll_no[20][20], mobile[20][20];
    int issued_count = 0;

    int choice, i, j, book_count, selected;

    printf("\n===============================================\n");
    printf(" Government Collage Of Engineering Yavatmal    \n\n"); 
    
    printf("                  Library      \n\n");
    printf("===============================================\n");

    // Login
    printf("\nLogin to Continue\n\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    if (strcmp(username, correct_user) == 0 && strcmp(password, correct_pass) == 0) {
        printf("\nLogin successful. Welcome to the library.\n");

        while (1) {
            printf("\n========= MAIN MENU =========\n");
            printf("1. Issue Books\n");
            printf("2. Return Book\n");
            printf("3. View Available Books\n");
            printf("4. View Issued Books\n");
            printf("5. Exit\n");
            printf("=============================\n");
            printf("Enter your choice (1-5): ");
            scanf("%d", &choice);

            if (choice == 1) {
                if (total_books == 0) {
                    printf("\nNo books currently available to issue.\n");
                    continue;
                }

                // Take student details only once
                char name[50], branch[30], roll[20], phone[20];
                getchar(); // flush newline
                printf("\nEnter Student Details:\n");
                printf("Name        : ");
                fgets(name, 50, stdin);
                name[strcspn(name, "\n")] = '\0';

                printf("Branch      : ");
                fgets(branch, 30, stdin);
                branch[strcspn(branch, "\n")] = '\0';

                printf("Roll Number : ");
                fgets(roll, 20, stdin);
                roll[strcspn(roll, "\n")] = '\0';

                printf("Mobile No.  : ");
                fgets(phone, 20, stdin);
                phone[strcspn(phone, "\n")] = '\0';

                printf("\nAvailable Books:\n");
                for (i = 0; i < total_books; i++)
                    printf("%d. %s\n", i + 1, book[i]);

                printf("\nHow many books do you want to issue (max %d): ", total_books);
                scanf("%d", &book_count);

                int books_issued_now = 0;
                int start_index = issued_count;

                for (int b = 0; b < book_count; b++) {
                    printf("\nEnter book number to issue (%d of %d): ", b + 1, book_count);
                    scanf("%d", &selected);

                    if (selected >= 1 && selected <= total_books) {
                        // Store issued book
                        strcpy(issued_books[issued_count], book[selected - 1]);

                        // Store student details for each book
                        strcpy(student_name[issued_count], name);
                        strcpy(student_branch[issued_count], branch);
                        strcpy(roll_no[issued_count], roll);
                        strcpy(mobile[issued_count], phone);

                        // Remove the book from available list
                        for (j = selected - 1; j < total_books - 1; j++)
                            strcpy(book[j], book[j + 1]);
                        total_books--;

                        issued_count++;
                        books_issued_now++;
                    } else {
                        printf("Invalid book number. Try again.\n");
                    }
                }

                // Show e-receipt after all books issued
                if (books_issued_now > 0) {
                    printf("\n--------- Issue Receipt ---------\n");
                    printf("Student   : %s\n", name);
                    printf("Branch    : %s\n", branch);
                    printf("Roll No   : %s\n", roll);
                    printf("Mobile No : %s\n", phone);
                    printf("Books Issued:\n");
                    for (i = start_index; i < start_index + books_issued_now; i++) {
                        printf("  - %s\n", issued_books[i]);
                    }
                    printf("----------------------------------\n");
                }

            } else if (choice == 2) {
                if (issued_count == 0) {
                    printf("\nNo books issued yet.\n");
                    continue;
                }

                printf("\nIssued Books:\n");
                for (i = 0; i < issued_count; i++)
                    printf("%d. %s (Issued to: %s)\n", i + 1, issued_books[i], student_name[i]);

                printf("\nEnter book number to return: ");
                scanf("%d", &selected);

                if (selected >= 1 && selected <= issued_count) {
                    strcpy(book[total_books], issued_books[selected - 1]);
                    total_books++;

                    for (j = selected - 1; j < issued_count - 1; j++) {
                        strcpy(issued_books[j], issued_books[j + 1]);
                        strcpy(student_name[j], student_name[j + 1]);
                        strcpy(student_branch[j], student_branch[j + 1]);
                        strcpy(roll_no[j], roll_no[j + 1]);
                        strcpy(mobile[j], mobile[j + 1]);
                    }
                    issued_count--;

                    printf("Book returned successfully.\n");
                } else {
                    printf("Invalid number.\n");
                }

            } else if (choice == 3) {
                printf("\nAvailable Books:\n");
                if (total_books == 0)
                    printf("None currently available.\n");
                else
                    for (i = 0; i < total_books; i++)
                        printf("%d. %s\n", i + 1, book[i]);

            } else if (choice == 4) {
                printf("\nIssued Books:\n");
                if (issued_count == 0)
                    printf("No books issued yet.\n");
                else
                    for (i = 0; i < issued_count; i++) {
                        printf("%d. %s -> %s (Roll: %s, Mob: %s)\n",
                            i + 1, issued_books[i], student_name[i], roll_no[i], mobile[i]);
                    }

            } else if (choice == 5) {
                printf("Exiting... Thank you for using the Library System.\n");
                break;
            } else {
                printf("Invalid choice. Try again.\n");
            }
        }

    } else {
        printf("\nInvalid login. Access denied.\n");
    }

    return 0;
}
