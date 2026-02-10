
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int main() {
    int (*operation)(int, int);
    operation = add;
    int result = operation(5, 3);
    printf("Result: %d\n", result);

    operation = subtract;
    result = operation(5, 3);
    printf("Result: %d\n", result);

    return 0;
}