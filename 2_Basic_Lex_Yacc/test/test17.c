int main() {
    char source[] = "Hello, C Programming!";
    char destination[100];

    strcpy(destination, source);

    printf("Source: %s\n", source);
    printf("Destination: %s\n", destination);

    return 0;
}