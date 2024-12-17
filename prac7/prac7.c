#include <stdio.h>
#include <string.h>

void bubble_sort(int arr[], int n) {
    for (int i=0;i<n-1;i++) {
        for (int j=0;j<n-i-1;j++) {
            if (arr[j]>arr[j+1]) {
                int temp=arr[j];
                arr[j]=arr[j + 1];
                arr[j+1]=temp;
            }
        }
    }
}

void find_unique_chars(char *str) {
    int n=strlen(str);
    int ascii_values[n];
    int count[128]= {0};

    int index=0;

    for (int i=0;i<n;i++) {
        if (str[i]>='a' && str[i]<='z' || str[i]>='A' && str[i]<='Z') {
            int ascii_val=(int)str[i];
            ascii_values[index++]=ascii_val;
            count[ascii_val]++;
        }
    }

    bubble_sort(ascii_values, index);

    printf("Characters that appear only once:\n");
    for (int i=0;i<index;i++) {
        if (count[ascii_values[i]]==1 && (i==0 || ascii_values[i]!=ascii_values[i-1])) {
            printf("%c ", (char)ascii_values[i]);
        }
    }
    printf("\n");
}

void main() {
    char input[256];
    printf("Enter sentence: ");
    fgets(input, 256, stdin);
    find_unique_chars(input);
}
