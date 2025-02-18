#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#define N_SMALL 100
#define N_MEDIUM 10000
#define N_LARGE 100000
#define NAME_LENGTH 64
#define MAX_GRADE 100

struct Student {
    char name[NAME_LENGTH];
    int math;
    int physics;
    int informatics;
    int total;
};


struct Student addStudent(const char *name, int math, int physics, int informatics) {
    struct Student newStudent;
    strncpy(newStudent.name, name, NAME_LENGTH-1);
    newStudent.math =math;
    newStudent.physics =physics;
    newStudent.informatics = informatics;
    newStudent.total = math + physics + informatics;
    return newStudent;
}

void printStudentInfo(struct Student student) {
    printf("name: %s | math: %d | phy: %d | inf: %d | total: %d\n",
           student.name, student.math, student.physics, student.informatics, student.total);
}

void generateRandomName(char *name, int length) {
    static const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < length - 1; i++) {
        name[i] = charset[rand() % (sizeof(charset) - 1)];
    }
}


void generateStudents(struct Student students[], int size) {
    for (int i = 0; i < size; i++) {
        char randomName[NAME_LENGTH];
        generateRandomName(randomName, 8 + rand() % 5);
        int math = rand() % (MAX_GRADE + 1);
        int physics = rand() % (MAX_GRADE + 1);
        int informatics = rand() % (MAX_GRADE + 1);
        students[i] = addStudent(randomName, math, physics, informatics);
    }
}

void selectionSort(struct Student arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int maxIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j].total > arr[maxIndex].total) {
                maxIndex = j;
            }
        }
        if (maxIndex != i) {
            struct Student temp = arr[i];
            arr[i] = arr[maxIndex];
            arr[maxIndex] = temp;
        }
    }
}

void countingSort(struct Student arr[], int size) {
    struct Student output[size];
    int count[MAX_GRADE * 3 + 1] = {0};

    for (int i = 0; i < size; i++) {
        count[arr[i].total]++;
    }

    for (int i = 1; i <= MAX_GRADE * 3; i++) {
        count[i] += count[i - 1];
    }
    for (int i = size - 1; i >= 0; i--) {
        output[count[arr[i].total] - 1] = arr[i];
        count[arr[i].total]--;
    }

    for (int i = 0; i < size; i++) {
        arr[i] = output[size - 1 - i];
    }
}

void quickSort(struct Student arr[], int left,int right) {
    if (left >= right) return;

    int pivot = arr[(left + right)/2].total;
    int i = left, j = right;
    while (i <= j) {
        while (arr[i].total > pivot) i++;
        while (arr[j].total < pivot) j--;
        if (i <= j) {
            struct Student temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }
    quickSort(arr, left, j);
    quickSort(arr, i, right);
}


double measureTime(void (*sortFunc)(struct Student[], int), struct Student arr[], int size) {
    struct timeval start, end;
    gettimeofday(&start, NULL);
    sortFunc(arr, size);
    gettimeofday(&end, NULL);
    return (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_usec - start.tv_usec) / 1000.0;
}


void printHead(int n,struct Student arr[]){
	for(int x=0;x<n;x++){
	struct Student student=arr[x];
	 printf("name: %s | math: %d | phy: %d | inf: %d | total: %d\n",
           student.name, student.math, student.physics, student.informatics, student.total);
	}
}

int main() {
    srand(time(NULL));

    printf("processor info:\n");
    system("cat /proc/cpuinfo | grep -E 'model name|cpu MHz'");

    int sizes[] = {N_SMALL, N_MEDIUM, N_LARGE};
    char *sortNames[] = {"Selection Sort", "Counting Sort", "Quick Sort"};
    void (*sortFuncs[])(struct Student arr[],int size) = {selectionSort,countingSort};
    for (int s = 0; s < 3; s++) {
        int size = sizes[s];
        struct Student *students = malloc(size * sizeof(struct Student));
        generateStudents(students, size);

        printf("\ntestin for N = %d:\n", size);
        for (int i = 0; i<2;i++) {
            struct Student *copy = malloc(size * sizeof(struct Student));
            memcpy(copy, students, size * sizeof(struct Student));
            double timeTaken = measureTime(sortFuncs[i],copy,size);
            printf("%s: %.2f milliseconds\n", sortNames[i], timeTaken);
	    printf("\n\n");
	    printHead(10,copy);
	    printf("\n\n");
        }
	
	    struct Student *copy = malloc(size * sizeof(struct Student));
            memcpy(copy, students, size * sizeof(struct Student));
            struct timeval start, end;
    	    gettimeofday(&start, NULL);
   	    quickSort(copy,0,size-1);
    	    gettimeofday(&end, NULL);
   	   double timeTaken=(end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_usec - start.tv_usec) / 1000.0;
            printf("%s: %.2f milliseconds\n", "quickSort", timeTaken);
	    printf("\n\n");
	    printHead(10,copy);
            free(copy);
        free(students);
    }

    return 0;
}
