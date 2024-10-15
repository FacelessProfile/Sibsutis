void main(){
int a;
int counter=0;
int bit;             //1231414 = 7 digits  
scanf("%d",&a);
bit = a & 1;
while(bit!=0){
    counter++;
    a=a>>1;
    bit=a & 1;
}
printf("%d",counter);

}
// 5
//a00000101
//a00000101 >> 0
//b00000001 & 1
//c10000000 1<<7
//a00000010 >> 1
// 

//&00000001
