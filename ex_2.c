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
    //check if the hex digit is a-f and return the corresponding decimal digit
    if(hexDigit >= 'a' && hexDigit <= 'f') {
        return hexDigit - 'a' + A_HEX_VAL;
    }
    //if none of the above applies to the hex digit, it's invalid and the function returns -1
    return -1;
}

/**************************************************************************************************************
* Function Name: hexToDec
* Input: none
* Output: none
* Function Operation: the function asks the user for a hexadecimal value in reversed order,and convert it to
*                    decimal-it takes one char each time, checks if the values entered are valid, converts them
*                    to decimal using the 'convertHextoDec' function, and prints the decimal value result
***************************************************************************************************************/
void hexToDec() {
    //defining a dummy variable for cleaning the scanf buffer
    char dummy;
    const int HEX_BASE = 16;
    char hexDigit;
    int decDigit = 0;
    long long int decSum = 0;
    long long int digitIndex = 0;
    printf("Enter a reversed number in base 16:\n");
    while(1) {
        /*
        take input from the user char by char,
        ignore whitespces and \n on the first scanf loop
        */
        if(digitIndex == 0) {
            scanf(" %c", &hexDigit);
        } else{
            scanf("%c", &hexDigit);
        }
        //if we reached the end of user input - break the loop
        if(hexDigit == '\n'){
            break;
        }
        //convert hex digit to decimal int
        decDigit = convertHextoDec(hexDigit);
        //if user input is invalid - inform the user and leave function
        if(decDigit == -1){
            //clean the buffer until it has a '\n'
            do {
                scanf("%c", &dummy);
            }
            while (dummy != '\n');
            //print error to inform the user they entered invalid values, exit the function
            printf("Error!\n");
            return;
        }
        //sum up all the decimal digits we got, multiply it by 16^index to go from hex to decimal value
        decSum += decDigit * (long long int)powl((long double)HEX_BASE, (long double)digitIndex);
        //raise the digitIndex variable for the calculation of the next digit
        digitIndex++;
    }
    //prints the result
    printf("%lld\n", decSum);
}

/***********************************************************************************************************
* Function Name: decimalToBase
* Input: none
* Output: none
* Function Operation: the function asks the user for a base and a decimal value, and converts it to a number
*                     in the chosen base presentation- working by the base transition algorithm- it divides
*                     the decimal number by the base. because we need the reversed result- it starts by
*                     the last division (dividing multiple times until 0) and goes up.
************************************************************************************************************/
void decimalToBase() {
    int userBaseChoice;
    unsigned long decVal;
    unsigned long divisionRes;
    int exponent = 0;
    printf("Enter base and a number:\n");
    scanf("%d %lu", &userBaseChoice, &decVal);
    //get the integer value of the exponent needed to get from the user chosen base to the decimal number.
    exponent = (int)(log10l((long double)decVal) / log10l((long double)userBaseChoice));
    /*
     * print the results of the base transition algorithm in reversed order of division.
     * we start from dividing the number by the base multiple times (using the pow function).
     * this needed to be done in reverse since in the original algorithm we save the remainders,
     * and print them from the end to the start. here we just print them at the moment we divide.
     */
    while(exponent >= 0){
        divisionRes = decVal;
        //get the result of the division of the chosen number with the base power the exponent.
        divisionRes /= (unsigned long)pow((double)userBaseChoice,(double)exponent);
        printf("%lu", divisionRes % userBaseChoice);
        exponent--;
    }
    printf("\n");
}

/*************************************************************************************************************
* Function Name: baseToDecimal
* Input: none
* Output: none
* Function Operation: the function asks the user for a base and a number in that base, and convert it to
*                     decimal number. it takes the whole number, checks what's the remainder when dividing
*                     by 10, and multiplying the result by base^the digit index, in order to get to the decimal
*                     value of the number.
**************************************************************************************************************/
void baseToDecimal() {
    const int DECIMAL_BASE = 10;
    int userBaseChoice;
    unsigned long num;
    unsigned long divisionRes;
    unsigned long divisionRemainder;
    unsigned long total = 0;
    int digitIndex = 0;
    printf("Enter base and a number:\n");
    scanf("%d %lu", &userBaseChoice, &num);
    if(num < 0){
        printf("Error!");
        return;
    }
    if(userBaseChoice == DECIMAL_BASE){
        printf("%lu", num);
    } else {
        divisionRes = num;
        while (divisionRes != 0) {
            divisionRemainder = divisionRes % DECIMAL_BASE;
            if(divisionRemainder >= userBaseChoice){
                printf("Error!");
                return;
            }
            total += divisionRemainder * (unsigned long)powl(userBaseChoice, (long double)digitIndex);
            divisionRes /= DECIMAL_BASE;
            digitIndex++;
        }
        printf("%lu\n", total);
    }
}

void plus() {
    const int DECIMAL_BASE = 10;
    char dummy;
    unsigned long num1;
    unsigned long num2;
    unsigned long temp1;
    unsigned long temp2;
    unsigned long bigNum = 0;
    unsigned long smallNum = 0;
    unsigned int divisionRemainder1;
    unsigned int divisionRemainder2;
    unsigned long totalCarry = 0;
    unsigned long currCarry = 0;
    unsigned long currRes = 0;
    unsigned long totalRes = 0;
    unsigned int digitIndex = 0;
    printf("Enter 2 binary numbers:\n");
    scanf("%lu %lu", &num1,&num2);
    temp1 = num1;
    temp2 = num2;
    if(num1 > num2){
        bigNum = num1;
        smallNum = num2;
    } else{
        bigNum = num2;
        smallNum = num1;
    }
    while (bigNum > 0){
        divisionRemainder1 = bigNum % DECIMAL_BASE;
        divisionRemainder2 = smallNum % DECIMAL_BASE;
        currRes = (divisionRemainder1 + divisionRemainder2 + currCarry) % 2;
        currCarry = (divisionRemainder1 + divisionRemainder2 + currCarry) / 2;
        totalCarry += currCarry * (unsigned long)pow(DECIMAL_BASE, digitIndex + 1);
        totalRes += currRes * (unsigned long)pow(DECIMAL_BASE, digitIndex);
        digitIndex++;
        bigNum /= DECIMAL_BASE;
        smallNum /= DECIMAL_BASE;
    }
    printf("%lu\n", totalCarry);
    printf("%lu\n", num1);
    printf("+\n");
    printf("%lu\n", num2);
    printf("-----");
    printf("%lu\n", totalRes);




















//    while (temp1 !=0 && temp2 !=0){
//        divisionRemainder1 = temp1 % DECIMAL_BASE;
//        divisionRemainder2 = temp2 % DECIMAL_BASE;
//        if(divisionRemainder1 != 0 && divisionRemainder1 != 1 || divisionRemainder2 != 0 && divisionRemainder2 != 1){
//            printf("Error!\n");
//            scanf("%c", &dummy);
//            return;
//        }
//        temp1 /= DECIMAL_BASE;
//        temp2 /= DECIMAL_BASE;
//    }
}

void butterFly() {
    int n=0;
    printf("Enter a number:\n");
    scanf("%u", &n);

    for (int i = 0; i < 2*n+1; ++i) {
        for (int j = 0; j < 2*n+2; ++j) {
            if((i == 0 || i == 2*n) && (j <= 2 || j>= 2*n-1)){
                printf("#");
            }else if(j == 0 || j == 2*n+1){
                printf("#");
            }else if((j==i+1 && i<n) || (j==i && i>n)){
                printf("#");
            }else if((j+i == 2*n && i<n) || (j+i == 2*n+1 && i>n)){
                printf("#");
            }else if((j <= i || j >= 2*n+1-i) && i < n) {
                printf("*");
            } else if((j > i || j < 2*n+1-i) && i >= n) {
                printf("*");
            } else{
                printf(" ");
            }
        }
        printf("\n");
    }
    //i=0, j=0, 2n-1
    //i=1, j=0,1,2n-2,2n-1
}

/************************************************************************************************************
* Function Name: countBits
* Input: none
* Output: none
* Function Operation: the function asks the user for a decimal value, then calculates its value in base 2,
*                     each time it reaches a '1' bit- increase a counter and at the end prints the counter
*                     value which is the amount of '1' bits of the binary representation of the decimal value
*************************************************************************************************************/
void countBits() {
    const int BINARY_BASE = 2;
    unsigned long decVal;
    unsigned long count = 0;
    unsigned long divisionRes;
    unsigned long divisionRemainder;
    printf("enter a number:\n");
    scanf("%lu", &decVal);
    divisionRes = decVal;
    //go from decimal representation to binary representation, using the algorithm of division + remainder
    while (divisionRes != 0) {
        divisionRemainder = divisionRes % BINARY_BASE;
        //increase a counter if the remainder is 1 (all of the remainders are also the representation in binary base)
        if(divisionRemainder == 1) {
            count += 1;
        }
        //divide the value by the binary base to go to the next digit
        divisionRes /= BINARY_BASE;
    }
    printf("no of bits those are 1 in its binary representation: %lu\n", count);
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
                hexToDec();
                break;
            case 2:
                decimalToBase();
                break;
            case 3:
                baseToDecimal();
                break;
            case 4:
                plus();
                break;
            case 5:
                butterFly();
                break;
            case 6:
                countBits();
                break;
            case 7:
                break;
            default:
                enterKey = 0;
                printf("Wrong option!\n");
                break;
        }
    }
    return 0;
}
