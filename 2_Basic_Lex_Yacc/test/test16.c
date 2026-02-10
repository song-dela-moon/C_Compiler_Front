int main() {
    FILE *file = fopen("sample.txt", "r");
    if (file != NULL) {
        char buffer[100];
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            printf("%s", buffer);
        }
        fclose(file);
    } else {
        printf("Failed to open the file.\n");
    }
    return 0;
}