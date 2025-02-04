#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student{
 char name[64];
 int math;
 int phy;
 int inf;
 int total;
};

struct student addStudent(char name[], int math, int phy, int inf){
	struct student newStudent;
	strcpy(newStudent.name,name);
	newStudent.math=math;
	newStudent.phy=phy;
	newStudent.inf=inf;
	newStudent.total=math+phy+inf;
	return newStudent;
}
int main(){

printf("%s",addStudent("nikita",100,100,100).name);
}
