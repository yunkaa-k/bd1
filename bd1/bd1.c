#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LEN 100
#define MAX_STUDENTS 10000000

typedef struct {
    char lastName[30];
    char firstName[30];
    int grade;
    int classroom;
    int bus;
    char teacherLastName[30];
    char teacherFirstName[30];
} Student;

Student students[MAX_STUDENTS];
int studentCount = 0;

void loadStudents(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Не вдалося відкрити файл: %s\n", filename);
        exit(1);
    }
    
    while (studentCount < MAX_STUDENTS && fscanf(file, "%[^,], %[^,], %d, %d, %d, %[^,], %[^\n]\n",
     	students[studentCount].lastName,
    	students[studentCount].firstName,
        &students[studentCount].grade,
        &students[studentCount].classroom,
        &students[studentCount].bus,
        students[studentCount].teacherLastName,
        students[studentCount].teacherFirstName) == 7) {
        studentCount++;
    }
    
    fclose(file);
}


void searchStudentByLastName(char *lastName) {
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].lastName, lastName) == 0) {
            printf("Студент: %s %s, Клас: %d, Клас викладача: %d, Викладач: %s %s\n",
                   students[i].lastName, students[i].firstName,
                   students[i].classroom, students[i].classroom,
                   students[i].teacherLastName, students[i].teacherFirstName);
            found = 1;
        }
    }
    if (!found) {
        printf("Студент з прізвищем %s не знайдений.\n", lastName);
    }
}

void searchStudentBus(char *lastName) {
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].lastName, lastName) == 0) {
            printf("Студент: %s %s, Маршрут автобуса: %d\n",
                   students[i].lastName, students[i].firstName, students[i].bus);
            found = 1;
        }
    }
    if (!found) {
        printf("Студент з прізвищем %s не знайдений.\n", lastName);
    }
}

void searchTeacherStudents(char *lastName) {
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].teacherLastName, lastName) == 0) {
            printf("Студент: %s %s\n", students[i].lastName, students[i].firstName);
            found = 1;
        }
    }
    if (!found) {
        printf("Учнів у викладача з прізвищем %s не знайдено.\n", lastName);
    }
}

void searchByClassroom(int classroom) {
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].classroom == classroom) {
            printf("Студент: %s %s\n", students[i].lastName, students[i].firstName);
            found = 1;
        }
    }
    if (!found) {
        printf("Студенти у класі номер %d не знайдені.\n", classroom);
    }
}

void searchByBusRoute(int bus) {
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].bus == bus) {
            printf("Студент: %s %s, Клас: %d, Клас викладача: %d\n",
                   students[i].lastName, students[i].firstName, students[i].classroom, students[i].classroom);
            found = 1;
        }
    }
    if (!found) {
        printf("Студенти на маршруті автобуса номер %d не знайдені.\n", bus);
    }
}

int main() {
    loadStudents("students.txt");

    char command[20];
    clock_t start, end;
    double cpu_time_used;

    while (1) {
    	printf("\nКоманди: S[tudent], SB[us], T[eacher], C[lassroom], B[us], Q[uit]. ");
        printf("\nВведіть команду: ");
        scanf("%s", command);

        if (strcmp(command, "Q") == 0) {
            break;
        } else if (strncmp(command, "S", 7) == 0) {
            char lastName[30];
            scanf("%s", lastName);
            
            start = clock();

                searchStudentByLastName(lastName);
            end = clock();
        } else if (strncmp(command,"SB",8) == 0){
        	char lastName[30];
            scanf("%s", lastName); 
			start = clock();
			searchStudentBus(lastName);
			end = clock();
		} 
		else if (strncmp(command, "T", 2) == 0) {
            char lastName[30];
            scanf("%s", lastName);
         
            start = clock();
            searchTeacherStudents(lastName);
            end = clock();
        } else if (strncmp(command, "C", 9) == 0) {
            int classroom;
            scanf("%d", &classroom);
            
            start = clock();
            searchByClassroom(classroom);
            end = clock();
        } else if (strncmp(command, "B", 3) == 0) {
            int bus;
            scanf("%d", &bus);
            
            start = clock();
            searchByBusRoute(bus);
            end = clock();
        } else {
            printf("Невідома команда.\n");
            continue;
        }

        // Підрахунок часу пошуку
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("Час пошуку: %.6f секунд\n", cpu_time_used);
    }

    return 0;
}
