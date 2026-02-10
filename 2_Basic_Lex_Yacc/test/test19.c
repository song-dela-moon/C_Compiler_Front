struct Student {
    char name[50];
    int roll;
};
int main() {
    struct Student students[3];
    strcpy(students[0].name, "Alice");
    students[0].roll = 101;
    strcpy(students[1].name, "Bob");
    students[1].roll = 102;
    strcpy(students[2].name, "Charlie");
    students[2].roll = 103;
    for (i = 0; i < 3; i++) {
        printf("Student %d\n", i + 1);
        printf("Name: %s\n", students[i].name);
        printf("Roll: %d\n", students[i].roll);
        printf("\n");
    }

    return 0;
}


