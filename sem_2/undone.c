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

// Структура данных Student
struct Student {
    char name[NAME_LENGTH];
    int math;
    int physics;
    int informatics;
    int total;
};

// Функция создания студента
struct Student addStudent(const char *name, int math, int physics, int informatics) {
    struct Student newStudent;
    strncpy(newStudent.name, name, NAME_LENGTH - 1);
    newStudent.name[NAME_LENGTH - 1] = '\0';
    newStudent.math = math;
    newStudent.physics = physics;
    newStudent.informatics = informatics;
    newStudent.total = math + physics + informatics;
    return newStudent;
}

// Функция вывода информации о студенте
void printStudentInfo(struct Student student) {
    printf("Имя: %s | Математика: %d | Физика: %d | Информатика: %d | Общий балл: %d\n",
           student.name, student.math, student.physics, student.informatics, student.total);
}

// Генерация случайного имени
void generateRandomName(char *name, int length) {
    static const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < length - 1; i++) {
        name[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    name[length - 1] = '\0';
}

// Заполнение массива студентов случайными данными
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

// *** 1. Сортировка выбором ***
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

// *** 2. Сортировка подсчетом (Counting Sort) ***
void countingSort(struct Student arr[], int size) {
    struct Student output[size];
    int count[MAX_GRADE * 3 + 1] = {0};

    // Заполняем массив частот
    for (int i = 0; i < size; i++) {
        count[arr[i].total]++;
    }

    // Преобразуем count в кумулятивную сумму
    for (int i = 1; i <= MAX_GRADE * 3; i++) {
        count[i] += count[i - 1];
    }

    // Заполняем отсортированный массив
    for (int i = size - 1; i >= 0; i--) {
        output[count[arr[i].total] - 1] = arr[i];
        count[arr[i].total]--;
    }

    // Копируем результат обратно
    for (int i = 0; i < size; i++) {
        arr[i] = output[size - 1 - i]; // Разворачиваем для убывания
    }
}

// *** 3. Быстрая сортировка (QuickSort) ***
void quickSort(struct Student arr[], int left, int right) {
    if (left >= right) return;

    int pivot = arr[(left + right) / 2].total;
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

// Функция измерения времени работы сортировки
double measureTime(void (*sortFunc)(struct Student[], int), struct Student arr[], int size) {
    struct timeval start, end;
    gettimeofday(&start, NULL);
    sortFunc(arr, size);
    gettimeofday(&end, NULL);
    return (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_usec - start.tv_usec) / 1000.0;
}

int main() {
    srand(time(NULL));

    // Вывод информации о процессоре
    printf("Информация о процессоре:\n");
    system("cat /proc/cpuinfo | grep -E 'model name|cpu MHz'");

    // Тестирование сортировок для N_SMALL, N_MEDIUM, N_LARGE
    int sizes[] = {N_SMALL, N_MEDIUM, N_LARGE};
    char *sortNames[] = {"Selection Sort", "Counting Sort", "Quick Sort"};
    void (*sortFuncs[])(struct Student[], int) = {selectionSort, countingSort, quickSort};

    for (int s = 0; s < 3; s++) {
        int size = sizes[s];
        struct Student *students = malloc(size * sizeof(struct Student));
        generateStudents(students, size);

        printf("\nТест для N = %d:\n", size);
        for (int i = 0; i < 3; i++) {
            struct Student *copy = malloc(size * sizeof(struct Student));
            memcpy(copy, students, size * sizeof(struct Student));
            double timeTaken = measureTime(sortFuncs[i], copy, size);
            printf("%s: %.2f мс\n", sortNames[i], timeTaken);
            free(copy);
        }
        free(students);
    }

    return 0;
}
