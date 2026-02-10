struct Student {
    char name[50];
    int roll;
};

int main() {
    struct Student student1;
    student1.roll = 101;
    strcpy(student1.name, "John");

    printf("Roll: %d\n", student1.roll);
    printf("Name: %s\n", student1.name);

    return 0;
}