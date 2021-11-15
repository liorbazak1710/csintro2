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

/***************************************************************************************************************
* Function Name: hexToDec
* Input: none
* Output: none
* Function Operation: the function asks the user for a hexadecimal value in reversed order,and converts it to
*                     decimal-it takes one char each time, checks if the values entered are valid, converts them
*                     to decimal using the 'convertHextoDec' function, and prints the decimal value result
****************************************************************************************************************/
void hexToDec() {
    const int HEX_BASE = 16;
    //defining a dummy variable for cleaning the scanf buffer
    char dummy;
    char hexDigit;
    int decDigit = 0;
    long long int decSum = 0, digitIndex = 0;
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
    int userBaseChoice, exponent = 0;
    unsigned long decVal = 0, divisionRes = 0;
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
    int userBaseChoice, digitIndex = 0;
    unsigned long num = 0, divisionRes = 0, divisionRemainder = 0, total = 0;
    printf("Enter base and a number:\n");
    scanf("%d %lu", &userBaseChoice, &num);
    //if the number is already in decimal presentation, print it and exit function
    if(userBaseChoice == DECIMAL_BASE){
        printf("%lu", num);
        return;
    }
    divisionRes = num;
    //going digit by digit and adding it's decimal value to a total variable
    while (divisionRes != 0) {
        divisionRemainder = divisionRes % DECIMAL_BASE;
        //checks if all of the digits are compatible with the users base choice
        if(divisionRemainder >= userBaseChoice){
            printf("Error!");
            return;
        }
        //calculating each digit decimal value, multiplying it by its base pow its location
        total += divisionRemainder * (unsigned long)powl(userBaseChoice, (long double)digitIndex);
        //dividing the number by 10 to go to the next digit
        divisionRes /= DECIMAL_BASE;
        digitIndex++;
    }
    printf("%lu\n", total);
}

/***************************************************************************************************************
* Function Name: plus
* Input: none
* Output: none
* Function Operation: the function asks the user for 2 binary numbers, checks if the input is valid, add the
*                     numbers by going digit by digit, and printing the carry line, the numbers, and the result.
****************************************************************************************************************/
void plus() {
    const int DECIMAL_BASE = 10;
    const int BINARY_BASE = 2;
    unsigned long num2 = 0, num1 = 0, temp1 = 0, bigNum = 0, smallNum = 0,
                  totalCarry = 0, currCarry = 0, currRes = 0, totalRes = 0;
    unsigned int divisionRemainder1 = 0, divisionRemainder2 = 0, digitIndex = 0,totalIterations = 0;
    int maxPadding = 0;

    printf("Enter 2 binary numbers:\n");
    scanf("%lu %lu", &num1,&num2);
    //checking which number is bigger and insert the values to the corresponding variables
    bigNum = num1 > num2 ? num1 : num2;
    smallNum= num1 <= num2 ? num1 : num2;
    //checking how many digits the big number has, to know how many iterations we need for the main loop
    temp1 = bigNum;
    while (temp1 > 0){
        totalIterations++;
        temp1 /= DECIMAL_BASE;
    }
    //going digit by digit in both numbers and add it, save the result and the carry
    while (digitIndex <= totalIterations){
        //the remainder of the division of each number by 10 will be the rightmost digit
        divisionRemainder1 = num1 % DECIMAL_BASE;
        divisionRemainder2 = num2 % DECIMAL_BASE;
        //printing error in case the input is invalid (digits are not 0/1)
        if(divisionRemainder1 > 1 || divisionRemainder2 > 1){
            printf("Error!\n");
            return;
        }
        //the current result will be the remainder of the sum of 2 digits and the carry, divided by 2
        currRes = (divisionRemainder1 + divisionRemainder2 + currCarry) % BINARY_BASE;
        //the total result will be the current result, mult by its location index in the whole number
        totalRes += currRes * (unsigned long)pow(DECIMAL_BASE, digitIndex);
        //stop the loop here if we reached the last digits
        if(digitIndex == totalIterations){
            break;
        }
        //the current carry will be the sum of 2 digits and the previous curry, divided by 2
        currCarry = (divisionRemainder1 + divisionRemainder2 + currCarry) / BINARY_BASE;
        /*
        the total carry will be the current carry, mult by its location index+1 in the whole number,
        since the carry starts from the 2nd index on (the 1st index will always be 0)
        */
        totalCarry += currCarry * (unsigned long)pow(DECIMAL_BASE, digitIndex + 1);
        digitIndex++;
        //dividing the numbers by 10 to go to the next digit
        num1 /= DECIMAL_BASE;
        num2 /= DECIMAL_BASE;
    }
    //checking how many digits we have at most, for padding with 0 the smaller numbers
    maxPadding = (int)totalIterations + (int)currCarry;
    printf("%0*lu\n%0*lu\n+\n%0*lu\n",maxPadding,totalCarry,maxPadding, bigNum, maxPadding, smallNum);
    for (int i = 0; i < maxPadding; ++i) {
        printf("-");
    }
    printf("\n");
    printf("%0*lu\n",maxPadding, totalRes);
}

/*************************************************************************************************************
* Function Name: butterFly
* Input: none
* Output: none
* Function Operation: the function asks the user for a number, and prints a butterfly that its height is 2n-1
*                     and its width is 2n, wrapped by a # frame so that its final height is 2n+1 and final
*                     width is 2n+2.
**************************************************************************************************************/
void butterFly() {
    int n = 0;
    printf("Enter a number:\n");
    scanf("%u", &n);
    //if n == 0 print only the # frame
    if(n == 0){
        printf("##\n##\n");
        return;
    }
    for (int i = 0; i < 2*n+1; ++i) {
        for (int j = 0; j < 2*n+2; ++j) {
            //print # for the frame top and bottom rows
            if((i == 0 || i == 2*n) && (j <= 2 || j>= 2*n-1)) {
                printf("#");
            }
            //print # for the frame side columns
            else if(j == 0 || j == 2*n+1) {
                printf("#");
            }
            //print # for the frame main diagonal
            else if((j == i+1 && i<n) || (j == i && i>n)) {
                printf("#");
            }
            //print # for the frame second diagonal
            else if((j+i == 2*n && i<n) || (j+i == 2*n+1 && i>n)) {
                printf("#");
            }
            //print * for the butterfly body, top part
            else if((j <= i || j >= 2*n+1-i) && i < n) {
                printf("*");
            }
            //print * for the butterfly body, bottom part
            else if((j > i || j < 2*n+1-i) && i >= n) {
                printf("*");
            }else{
                printf(" ");
            }
        }
        printf("\n");
    }
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
    unsigned long decVal = 0, count = 0, divisionRes = 0, divisionRemainder = 0;
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
    while(enterKey!=7) {
        printf("Choose an option:\n"
               "\t1. hexaDecimal to Decimal\n"
               "\t2. Decimal to Base\n"
               "\t3. Base to Decimal\n"
               "\t4. PLUS\n"
               "\t5. Shape\n"
               "\t6. Count bits\n"
               "\t7. Exit\n");
        scanf("%d",&enterKey);
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
