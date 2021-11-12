/***********************
* Name: Lior Bazak
* ID: 207106709
* Assignment: ex_2
***********************/

#include <stdio.h>
#include <math.h>

/*******************************************************************************************
* Function Name: convertHextoDec
* Input: int hexDigit (valid values between 0-9, a-f, A-F)
* Output: int (values between 0-15, -1 for invalid input)
* Function Operation: the function converts the given hexadecimal digit to its
*                     corresponding decimal digit- (A-F => 10-15, a-f => 10-15, 0-9 => 0-9)
*                     if the input is invalid the function returns -1
*******************************************************************************************/
int convertHextoDec(char hexDigit){
    const int A_HEX_VAL = 10;
    //check if the hex digit is 0-9 and return the corresponding decimal digit
    if(hexDigit >= '0' && hexDigit <= '9'){
        return hexDigit - '0';
    }
    //check if the hex digit is A-F and return the corresponding decimal digit
    if(hexDigit >= 'A' && hexDigit <= 'F'){
        return hexDigit - 'A' + A_HEX_VAL;
    }
    if(hexDigit >= 'a' && hexDigit <= 'f') {
        return hexDigit - 'a' + A_HEX_VAL;
    }
    return -1;
}

void decimalToBase() {
    char dummy;
    const int HEX_BASE = 16;
    char hexDigit;
    int decDigit = 0;
    long long int decSum = 0;
    long long int digitIndex = 0;
    printf("Enter a reversed number in base 16:\n");
    while(1) {
        //take input from the user char by char
        if(digitIndex == 0) {
            scanf(" %c", &hexDigit);
        } else{
            scanf("%c", &hexDigit);
        }
        //printf("%c\n", hexDigit);
        //if we reached the end of user input - break the loop
        if(hexDigit == '\n'){
            break;
        }
        //convert hex digit to decimal int
        decDigit = convertHextoDec(hexDigit);
        //if user input is invalid - inform the user and leave function
        if(decDigit == -1){
            do {
                scanf("%c", &dummy);
            }
            while (dummy != '\n');
            printf("Error!\n");
            return;
        }
        decSum += decDigit * (long long int)powl((long double)HEX_BASE, (long double)digitIndex);
        digitIndex++;
    }
    printf("%lld\n", decSum);
}

void plus() {
    long num1;
    long num2;
    scanf("%lu%lu", num1,num2);
}

void butterFly() {
    int n=0;
    printf("Enter a number:\n");
    scanf("%u", &n);
    for (int i = 0; i < n*2-1; ++i) {
        for (int j = 0; j < 2*n; ++j) {
            if(j==0 || j== 2*n-1 || (j<=2 && (i==0||i==n*2-2)) ||
               (j>=2*n-3 && (i==0||i==n*2-2)) || (i+1==j && i<n-1) || (i==j && i>n-1)){
                printf("#");
            } //else if(i){
                //   printf(" ");
                //  }
            else {
                printf("*");
            }
            //printf("(%d,%d)", i,j);
            //printf("  ");
        }
        printf("\n");
    }

    /* for (int i = 0; i < n*2-1; ++i) {
         for (int j = 0; j < n*2; ++j) {
             printf("(%d,%d)",i,j);
         }
         printf("\n");
     }*/
}

int main() {
    int enterKey= 0;
    //char dummy;
    while(enterKey!=7) {
        printf("Choose an option:\n"
               "    1. hexadecimal to Decimal\n"
               "    2. Decimal to Base\n"
               "    3. Base to Decimal\n"
               "    4. PLUS\n"
               "    5. Shape\n"
               "    6. Count bits\n"
               "    7. Exit\n");
        scanf("%d",&enterKey);
        //scanf("%c", &dummy);
        switch (enterKey) {
            case 1:
                decimalToBase();
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                butterFly();
                break;
            case 6:
                break;
            case 7:
                break;
            default:
                enterKey=0;
                printf("Wrong option!\n");
                break;
        }
    }
    return 0;
}
