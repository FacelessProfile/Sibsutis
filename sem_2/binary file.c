#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define HEADING_SIZE 10

struct Train {
    char Heading[HEADING_SIZE + 1];
    int number;
    int hours;
    int minutes;
};

void RoadTo(char *buf, int len) {
    for (int i = 0; i < len; i++) {
        buf[i] = 'A' + rand() % 26;
    }
    buf[len] = '\0';
}

void RandTime(int *timeArray) {
    timeArray[0] = rand() % 24;
    timeArray[1] = rand() % 60;
}

int main() {
    srand(time(NULL));

    int N = 5;
    struct Train *trains = malloc(N * sizeof(struct Train));
    if (trains == NULL) {
        printf("cant mallocnut memory sore\n");
        return 1;
    }

    // Заполнение структур
    for (int i = 0; i < N; i++) {
        RoadTo(trains[i].Heading, HEADING_SIZE);
        trains[i].number = i + 1;
        int timeArr[2];
        RandTime(timeArr);
        trains[i].hours = timeArr[0];
        trains[i].minutes = timeArr[1];
    }

    // Вывод для проверки
    for (int i = 0; i < N; i++) {
        printf("Heading: %s, TrainNo: %d, Time: %02d:%02d\n",
               trains[i].Heading,
               trains[i].number,
               trains[i].hours,
               trains[i].minutes);
    }

    // Запись в файл
    FILE *f = fopen("uwu.txt", "wb");
    if (!f) {
        perror("ERR");
        free(trains);
        return 1;
    }
    fwrite(trains, sizeof(struct Train), N, f);
    fclose(f);
    free(trains);

    // Поиск в файле
    printf("\nfind by:\n");
    printf("1. Heading\n");
    printf("2. TrainNo\n");
    printf("3. Time\n");
    printf("Enter option: ");
    int option;
    scanf("%d", &option);

    // Открываем файл для чтения
    f = fopen("uwu.txt", "rb");
    if (!f) {
        perror("ERR");
        return 1;
    }

    // Считываем данные из файла в новый массив
    struct Train *readTrains = malloc(N * sizeof(struct Train));
    if (readTrains == NULL) {
        printf("cant mallocnut memory sore\n");
        fclose(f);
        return 1;
    }
    fread(readTrains, sizeof(struct Train), N, f);
    fclose(f);

    int found = 0;
    if (option == 1) {
        char key[HEADING_SIZE + 1];
        printf("enter find-key: ");
        scanf("%s", key);
        for (int i = 0; i < N; i++) {
            if (strcmp(readTrains[i].Heading, key) == 0) {
                printf("Found: Heading: %s, TrainNo: %d, Time: %02d:%02d\n",
                       readTrains[i].Heading,
                       readTrains[i].number,
                       readTrains[i].hours,
                       readTrains[i].minutes);
                found = 1;
            }
        }
    } else if (option == 2) {
        int key;
        printf("enter find-key: ");
        scanf("%d", &key);
        for (int i = 0; i < N; i++) {
            if (readTrains[i].number == key) {
                printf("Found: Heading: %s, TrainNo: %d, Time: %02d:%02d\n",
                       readTrains[i].Heading,
                       readTrains[i].number,
                       readTrains[i].hours,
                       readTrains[i].minutes);
                found = 1;
            }
        }
    } else if (option == 3) {
        int keyHours, keyMinutes;
        char timeInput[6]; // Формат hh:mm
        printf("enter find-key: ");
        scanf("%5s", timeInput);
        if (sscanf(timeInput, "%d:%d", &keyHours, &keyMinutes) != 2) {
            printf("Wrong time format.\n");
            free(readTrains);
            return 1;
        }
        for (int i = 0; i < N; i++) {
            if (readTrains[i].hours == keyHours && readTrains[i].minutes == keyMinutes) {
                printf("Found: Heading: %s, TrainNo: %d, Time: %02d:%02d\n",
                       readTrains[i].Heading,
                       readTrains[i].number,
                       readTrains[i].hours,
                       readTrains[i].minutes);
                found = 1;
            }
        }
    } else {
        printf("Wronh option.\n");
        free(readTrains);
        return 1;
    }

    if (!found) {
        printf("Cant find the data\n");
    }

    free(readTrains);
    return 0;
}
