int main() {
    int n = 5;
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr != NULL) {
        for (i = 0; i < n; i++) {
            arr[i] = i * 2;
        }

        for (i = 0; i < n; i++) {
            printf("%d\n", arr[i]);
        }

        free(arr);
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}


