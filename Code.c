#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <time.h>
typedef struct Student
{
 char name[50];
 char rollNo[15];
 char branch[10];
 float age;
}Student;
void createAccount();
void displayInfo();
void deleteInfo();
void searchInfo();
int main()
{
 clock_t t;
 char option;
 while (option != '0')
 {
 system("cls");
 printf("\t\t====== Student Management Database System ======\n");
 printf("\n\t\t\t1. Add Student Account");
 printf("\n\t\t\t2. Display All Students Information");
 printf("\n\t\t\t3. Delete Student Information");
 printf("\n\t\t\t4. Search Student Information");
 printf("\n\t\t\t0. Exit");
 printf("\n\n\n\t\t\tEnter Your Option: ");
 scanf("%c", &option);
 switch (option)
 {
 case '1':
 createAccount();
 break;
 case '2':
 displayInfo();
 break;
 case '3':
 deleteInfo();
 break;
 case '4':
 t = clock();
 searchInfo();
 t = clock() - t;
 double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
 printf("\n\n\t\t\tsearchInfo() operation took %f seconds to execute \n",
time_taken);
 printf("\n\n\n\t\t\tEnter any keys to continue.......");
 getch();
 break;
 case '0':
 printf("\n\t\t\t====== Thank You ======");
 break;
 default:
 printf("\n\t\t\tInvalid Option, Please Enter Right Option !\n");
 }
 }
 return 0;
}
void createAccount()
{
 FILE *fileOne = fopen("studInfoFile.txt", "ab+");
 if (fileOne == NULL)
 {
 printf("\n\t\t\tError !\n");
 }
 Student stuInfo;
 system("cls");
 printf("\t\t\t====== Create Student Account ======\n");
 printf("\n\t\t\tEnter Student's Name : ");
 getchar();
 gets(stuInfo.name);
 printf("\t\t\tEnter Student's ID : ");
 gets(stuInfo.rollNo);
 printf("\t\t\tEnter Student's Depertment : ");
 gets(stuInfo.branch);
 printf("\t\t\tEnter Student's Current age : ");
 scanf("%f", &stuInfo.age);
 fwrite(&stuInfo, sizeof(stuInfo), 1, fileOne);
 printf("\n\n\t\t\tInformations have been stored sucessfully\n");
 printf("\n\n\t\t\tEnter any keys to continue.......");
 getch();
 fclose(fileOne);
}
void displayInfo()
{
 FILE *fileOne = fopen("studInfoFile.txt", "rb");
 if (fileOne == NULL)
 {
 printf("\n\t\t\tError !\n");
 }
 Student stuInfo;
 system("cls");
 printf("\t\t\t\t====== All Students Information ======\n");
 printf("\n\n\t\t%-20s%-13s%-10s%-15s\n", "Name", "ID", "Dept.", "AGE");
 printf("\t\t----------------------------------------------------");
 while (fread(&stuInfo, sizeof(stuInfo), 1, fileOne) == 1)
 {
 printf("\n\n\t\t%-20s%-13s%-10s%-.2f", stuInfo.name, stuInfo.rollNo,
stuInfo.branch, stuInfo.age);
 }
 printf("\n\n\t\tEnter any keys to continue.......");
 getch();
 fclose(fileOne);
}
void updateInfo()
{
 FILE *fileOne = fopen("studInfoFile.txt", "rb");
 FILE *temp = fopen("temp.bin", "wb");
 Student studentInformation, tempInformation;
 int choice, flag = 0;
 if (fileOne == NULL || temp == NULL)
 {
 printf("\n\t\t\tError !\n");
 }
 system("cls");
 printf("\t\t\t\t====== Update Students Information ======\n");
 printf("\n\t\t\tEnter Student's ID : ");
 getchar();
 gets(tempInformation.rollNo);
 while (fread(&studentInformation, sizeof(studentInformation), 1, fileOne) == 1)
 {
 if (strcmp(studentInformation.rollNo, tempInformation.rollNo) == 0)
 {
 flag++;
 printf("\n\t\t\tChoose your option :\n\t\t\t1.Update Student Name\n\t\t\t2.Update
Student Dept.\n\t\t\t3.Update Student AGE");
 printf("\n\n\t\t\tEnter Your Option : ");
 scanf("%d", &choice);
 if (choice == 1)
 {
 printf("\n\t\t\tEnter Student's Name to Update: ");
 getchar();
 gets(tempInformation.name);
 strcpy(studentInformation.name, tempInformation.name);
 fwrite(&studentInformation, sizeof(studentInformation), 1, temp);
 printf("\n\n\t\t\tUpdated successfully!\n\n");
 }
 else if (choice == 2)
 {
 printf("\n\t\t\tEnter Student's Dept. to Update: ");
 getchar();
 gets(tempInformation.branch);
 strcpy(studentInformation.branch, tempInformation.branch);
 fwrite(&studentInformation, sizeof(studentInformation), 1, temp);
 printf("\n\n\t\t\tUpdated successfully!\n\n");
 }
 else if (choice == 3)
 {
 printf("\n\t\t\tEnter Student's AGE to Update: ");
 scanf("%f", &tempInformation.age);
 studentInformation.age = tempInformation.age;
 fwrite(&studentInformation, sizeof(studentInformation), 1, temp);
 printf("\n\n\t\t\tUpdated successfully!\n\n");
 }
 else
 {
 printf("\n\t\t\tInvalid Option.");
 fwrite(&studentInformation, sizeof(studentInformation), 1, temp);
 }
 }
 else
 {
 fwrite(&studentInformation, sizeof(studentInformation), 1, temp);
 }
 }
 fclose(fileOne);
 fclose(temp);
 remove("studInfoFile.bin");
 rename("temp.bin", "studInfoFile.bin");
 if (flag == 0)
 {
 printf("\n\t\t\tStudent Id is not found");
 }
 printf("\n\n\t\t\tEnter any keys to continue.......");
 getch();
}
void deleteInfo()
{
 FILE *fileOne = fopen("studInfoFile.bin", "rb");
 FILE *temp = fopen("temp.bin", "wb");
 Student studentInformation, tempInformation;
 int choice, flag = 0;
 if (fileOne == NULL || temp == NULL)
 {
 printf("\n\t\t\tError !\n");
 }
 system("cls");
 printf("\t\t\t\t====== Delete Student Information ======\n");
 printf("\n\t\t\tEnter Student's ID : ");
 getchar();
 gets(tempInformation.rollNo);
 while (fread(&studentInformation, sizeof(studentInformation), 1, fileOne) == 1)
 {
 if (strcmp(studentInformation.rollNo, tempInformation.rollNo) == 0)
 {
 flag++;
 printf("\n\t\t\tAre you sure to delete ??\n\t\t\t\t1.Yes\n\t\t\t\t2.Back\n\t\t\t\tEnter
Your Option : ");
 scanf("%d", &choice);
 if (choice == 1)
 {
 printf("\n\n\t\t\tInformation has been deleted successfully!\n\n");
 }
 else if (choice == 2)
 {
 fwrite(&studentInformation, sizeof(studentInformation), 1, temp);
 }
 else
 {
 printf("\n\t\t\tInvalid Option");
 fwrite(&studentInformation, sizeof(studentInformation), 1, temp);
 }
 }
 else
 {
 fwrite(&studentInformation, sizeof(studentInformation), 1, temp);
 }
 }
 fclose(fileOne);
 fclose(temp);
 remove("studInfoFile.bin");
 rename("temp.bin", "studInfoFile.bin");
 if (flag == 0)
 {
 printf("\n\t\t\tStudent Id is not found");
 }
 printf("\n\n\t\t\tEnter any keys to continue.......");
 getch();
}
void searchInfo()
{
 FILE *fileOne = fopen("studInfoFile.bin", "rb");
 Student studentInformation;
 int choice, flag = 0;
 char rollNo[20], branch[10];
 if (fileOne == NULL)
 {
 printf("\n\t\t\tError !\n");
 }
 system("cls");
 printf("\t\t\t\t====== Search Student Information ======\n");
 printf("\n\n\t\t\tEnter Student ID : ");
  getchar();
 gets(rollNo);
 while (fread(&studentInformation, sizeof(studentInformation), 1, fileOne) == 1)
 {
 if (strcmp(studentInformation.rollNo, rollNo) == 0)
 {
 flag++;
 printf("\n\t\t\tStudent Name : %s\n\t\t\tStudent ID : %s\n\t\t\tStudent Dept. :
%s\n\t\t\tStudent AGE : %.2f\n", studentInformation.name, studentInformation.rollNo,
studentInformation.branch, studentInformation.age);
 }
 }
 if (flag == 0)
 {
 printf("\n\t\t\tStudent Id is not found");
 }
 fclose(fileOne);
}
