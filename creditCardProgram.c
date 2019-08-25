#include <cs50.h>
#include <stdbool.h>
#include <stdio.h>

int main(void)
{
    // This variable will be used later for different cases for different digit sized cards.
    bool digitIsZero = false;
    // This will be a flag I will use for printing "INVALID" when the user doesn't enter a valid credit card number.
    bool flag = false;
    long long creditCardNumber;
    // Variables to hold each digit of a credit card.*NOTE, digit1 represents the far right digit. digit 16 would be the far left
    // digit. In the case of Amex though, digit 15 would be the far left digit.
    int digit1, digit2, digit3, digit4, digit5, digit6, digit7, digit8;
    int digit9, digit10, digit11, digit12, digit13, digit14, digit15, digit16;
    // These variables will be for the first part of the checksum where starting from the second to last digit they're multiplied
    // by two.
    int digit16MultTwo, digit14MultTwo, digit12MultTwo, digit10MultTwo, digit8MultTwo, digit6MultTwo, digit4MultTwo, digit2MultTwo;
    // Ending and starting even digits for the mult two's, where the end digit is on the far right, and the start digit is on the
    // far left.
    int endDigitFor16, startDigitFor16, endDigitFor14, startDigitFor14, endDigitFor12, startDigitFor12, endDigitFor10, startDigitFor10;
    int endDigitFor8, startDigitFor8, endDigitFor6, startDigitFor6, endDigitFor4, startDigitFor4, endDigitFor2, startDigitFor2;
    // Ending and starting odd digits for the mult two's.
    int endDigitFor15, startDigitFor15, endDigitFor13, startDigitFor13, endDigitFor11, startDigitFor11, endDigitFor9, startDigitFor9;
    int endDigitFor7, startDigitFor7, endDigitFor5, startDigitFor5, endDigitFor3, startDigitFor3, endDigitFor1, startDigitFor1;
    // variables for the different sum steps in regards to the check sum.
    int finalSum, checkEndDigitFinalSum, digitsSum;
    // Ask the user to enter a credit card number if they enter negative numbers or strings.
    do
    {
        creditCardNumber = get_long_long("Enter a credit card number: ");
    }
    while (creditCardNumber < 0);
    // Here I'm always going to get 16 digits even if the user only enters 2 digits or 11 digits. I get all the digits after digit1
    // through modulus arithmetic. Getting the digits past digit1 follows a pattern of dividing the credit card by the previous mod-
    // ulus times 10, then subtracting this from the previous digit and dividing by 10. For digits 3-16 the previous devision is
    // multiplied by 10 in the same way as the modulus was multiplied by 10 going from digit1 to digit2.
    digit1 = creditCardNumber % 10;
    digit2 = ((creditCardNumber % 100) - digit1) / 10;
    digit3 = ((creditCardNumber % 1000) - digit2) / 100;
    digit4 = ((creditCardNumber % 10000) - digit3) / 1000;
    digit5 = ((creditCardNumber % 100000) - digit4) / 10000;
    digit6 = ((creditCardNumber % 1000000) - digit5) / 100000;
    digit7 = ((creditCardNumber % 10000000) - digit6) / 1000000;
    digit8 = ((creditCardNumber % 100000000) - digit7) / 10000000;
    digit9 = ((creditCardNumber % 1000000000) - digit8) / 100000000;
    digit10 = ((creditCardNumber % 10000000000) - digit9) / 1000000000;
    digit11 = ((creditCardNumber % 100000000000) - digit10) / 10000000000;
    digit12 = ((creditCardNumber % 1000000000000) - digit11) / 100000000000;
    digit13 = ((creditCardNumber % 10000000000000) - digit12) / 1000000000000;
    digit14 = ((creditCardNumber % 100000000000000) - digit13) / 10000000000000;
    digit15 = ((creditCardNumber % 1000000000000000) - digit14) / 100000000000000;
    digit16 = ((creditCardNumber % 10000000000000000) - digit15) / 1000000000000000;
    // In the case that I'm dealing with a 13 digit visa card then I know the next digit being 14 is zero, and so I set a boolean
    // equal to true for my visa case.
    if (digit14 == 0)
    {
        digitIsZero = true;
    }
    // I'm doing the same logic as the above if-statement, but for the American Express which uses 15-digit numbers.
    if (digit16 == 0)
    {
        digitIsZero = true;
    }
    //American Express case, starting numbers are either 34 or 37. The max number of digits an American Express card can have is 15,
    //hence why I'm checking for digit 15 and 14. Remember, 15 and 14 represent the LEFT most digits.
    if ((digit15 == 3 && digit14 == 4 && digitIsZero == true) || (digit15 == 3 && digit14 == 7 && digit16 == 0))
    {
        // This flag gets set to true in the AMEX, MASTERCARD, and VISA cases. I set this variable to true in these cases,
        // so I don't get a print INVALID twice. I have logic at the end of each of these cases that will print "INVALID",but I
        // also have to have a case after all these credit card cases where if the user enters 24, the program says INVALID.
        flag = true;
        // First part of checksum. I'm storing the multiplication of every other digit by 2 starting from digit2-digit14.
        digit14MultTwo = (digit14 * 2);
        digit12MultTwo = (digit12 * 2);
        digit10MultTwo = (digit10 * 2);
        digit8MultTwo = (digit8 * 2);
        digit6MultTwo = (digit6 * 2);
        digit4MultTwo = (digit4 * 2);
        digit2MultTwo = (digit2 * 2);
        // I have to get into a variable the ending and starting digit for each of the above mults. The reason for this is that lets
        // say digit14MultTwo has the value 14, for the next part of the check sum I have to add 1 + 4, so I have to have those in-
        // dividual digits.
        endDigitFor14 = digit14MultTwo % 10;
        startDigitFor14 = ((digit14MultTwo % 100) - endDigitFor14) / 10;
        endDigitFor12 = digit12MultTwo % 10;
        startDigitFor12 = ((digit12MultTwo % 100) - endDigitFor12) / 10;
        endDigitFor10 = digit10MultTwo % 10;
        startDigitFor10 = ((digit10MultTwo % 100) - endDigitFor10) / 10;
        endDigitFor8 = digit8MultTwo % 10;
        startDigitFor8 = ((digit8MultTwo % 100) - endDigitFor8) / 10;
        endDigitFor6 = digit6MultTwo % 10;
        startDigitFor6 = ((digit6MultTwo % 100) - endDigitFor6) / 10;
        endDigitFor4 = digit4MultTwo % 10;
        startDigitFor4 = ((digit4MultTwo % 100) - endDigitFor4) / 10;
        endDigitFor2 = digit2MultTwo % 10;
        startDigitFor2 = ((digit2MultTwo % 100) - endDigitFor2) / 10;
        // I'm adding the end and starting digits for the mults in the digitsSum variable.
        digitsSum = (endDigitFor14 + startDigitFor14 + endDigitFor12 + startDigitFor12 + endDigitFor10 + startDigitFor10 + endDigitFor8
                     + startDigitFor8 + endDigitFor6 + startDigitFor6 + endDigitFor4 + startDigitFor4 + endDigitFor2 + startDigitFor2);
        // Now that I have the digit's sum I want to add that sum to all the odd numbered digits. The mults got every other digit
        // starting from the right going to the left. Now I'm adding not those mults, but the odd digits that weren't multiplied
        // by anything.
        finalSum = (digitsSum + digit1 + digit3 + digit5 + digit7 + digit9 + digit11 + digit13 + digit15);
        // This is the final step for determining if a credit card is AMEX, and will work the same for MASTERCARD, and VISA.
        // If the end digit for the final sum is zero, then this is valid. Otherwise, the card isn't legit.
        checkEndDigitFinalSum = finalSum % 10;
        // Valid credit card!
        if (checkEndDigitFinalSum == 0)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    //Mastercard case. Everything follows the same formula as the AMEX case.
    if ((digit16 == 5 && digit15 == 1) || (digit16 == 5 && digit15 == 2) || (digit16 == 5 && digit15 == 3) || (digit16 == 5
            && digit15 == 4) || (digit16 == 5 && digit15 == 5))
    {
        flag = true;
        digit16MultTwo = (digit16 * 2);
        digit14MultTwo = (digit14 * 2);
        digit12MultTwo = (digit12 * 2);
        digit10MultTwo = (digit10 * 2);
        digit8MultTwo = (digit8 * 2);
        digit6MultTwo = (digit6 * 2);
        digit4MultTwo = (digit4 * 2);
        digit2MultTwo = (digit2 * 2);
        // This will give me the ending digit for a two digit number.
        endDigitFor16 = digit16MultTwo % 10;
        // This will give me the start digit for a two digit number.
        startDigitFor16 = ((digit16MultTwo % 100) - endDigitFor16) / 10;
        endDigitFor14 = digit14MultTwo % 10;
        startDigitFor14 = ((digit14MultTwo % 100) - endDigitFor14) / 10;
        endDigitFor12 = digit12MultTwo % 10;
        startDigitFor12 = ((digit12MultTwo % 100) - endDigitFor12) / 10;
        endDigitFor10 = digit10MultTwo % 10;
        startDigitFor10 = ((digit10MultTwo % 100) - endDigitFor10) / 10;
        endDigitFor8 = digit8MultTwo % 10;
        startDigitFor8 = ((digit8MultTwo % 100) - endDigitFor8) / 10;
        endDigitFor6 = digit6MultTwo % 10;
        startDigitFor6 = ((digit6MultTwo % 100) - endDigitFor6) / 10;
        endDigitFor4 = digit4MultTwo % 10;
        startDigitFor4 = ((digit4MultTwo % 100) - endDigitFor4) / 10;
        endDigitFor2 = digit2MultTwo % 10;
        startDigitFor2 = ((digit2MultTwo % 100) - endDigitFor2) / 10;
        digitsSum = (endDigitFor16 + startDigitFor16 + endDigitFor14 + startDigitFor14 + endDigitFor12 + startDigitFor12 + endDigitFor10
                     + startDigitFor10 + endDigitFor8 + startDigitFor8 + endDigitFor6 + startDigitFor6 + endDigitFor4 + startDigitFor4
                     + endDigitFor2 + startDigitFor2);
        finalSum = (digitsSum + digit1 + digit3 + digit5 + digit7 + digit9 + digit11 + digit13 + digit15);
        checkEndDigitFinalSum = finalSum % 10;
        if (checkEndDigitFinalSum == 0)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    //Visa case where it's a 13 digit card. Follows same pattern as above credit card cases.
    if ((digit13 == 4 && digitIsZero == true))
    {
        flag = true;
        digit12MultTwo = (digit12 * 2);
        digit10MultTwo = (digit10 * 2);
        digit8MultTwo = (digit8 * 2);
        digit6MultTwo = (digit6 * 2);
        digit4MultTwo = (digit4 * 2);
        digit2MultTwo = (digit2 * 2);
        // This will give me the ending digit for a two digit number.
        endDigitFor12 = digit12MultTwo % 10;
        // This will give me the start digit for a two digit number.
        startDigitFor12 = ((digit12MultTwo % 100) - endDigitFor12) / 10;
        endDigitFor10 = digit10MultTwo % 10;
        startDigitFor10 = ((digit10MultTwo % 100) - endDigitFor10) / 10;
        endDigitFor8 = digit8MultTwo % 10;
        startDigitFor8 = ((digit8MultTwo % 100) - endDigitFor8) / 10;
        endDigitFor6 = digit6MultTwo % 10;
        startDigitFor6 = ((digit6MultTwo % 100) - endDigitFor6) / 10;
        endDigitFor4 = digit4MultTwo % 10;
        startDigitFor4 = ((digit4MultTwo % 100) - endDigitFor4) / 10;
        endDigitFor2 = digit2MultTwo % 10;
        startDigitFor2 = ((digit2MultTwo % 100) - endDigitFor2) / 10;
        digitsSum = (endDigitFor12 + startDigitFor12 + endDigitFor10 + startDigitFor10 + endDigitFor8 + startDigitFor8 + endDigitFor6
                     + startDigitFor6 + endDigitFor4 + startDigitFor4 + endDigitFor2 + startDigitFor2);
        finalSum = (digitsSum + digit1 + digit3 + digit5 + digit7 + digit9 + digit11 + digit13);
        checkEndDigitFinalSum = finalSum % 10;

        if (checkEndDigitFinalSum == 0)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    //Visa case where it's a 16 digit card. Follows same pattern as above credit card cases.
    if (digit16 == 4)
    {
        flag = true;
        digit16MultTwo = (digit16 * 2);
        digit14MultTwo = (digit14 * 2);
        digit12MultTwo = (digit12 * 2);
        digit10MultTwo = (digit10 * 2);
        digit8MultTwo = (digit8 * 2);
        digit6MultTwo = (digit6 * 2);
        digit4MultTwo = (digit4 * 2);
        digit2MultTwo = (digit2 * 2);
        // This will give me the ending digit for a two digit number.
        endDigitFor16 = digit16MultTwo % 10;
        // This will give me the start digit for a two digit number.
        startDigitFor16 = ((digit16MultTwo % 100) - endDigitFor16) / 10;
        endDigitFor14 = digit14MultTwo % 10;
        startDigitFor14 = ((digit14MultTwo % 100) - endDigitFor14) / 10;
        endDigitFor12 = digit12MultTwo % 10;
        startDigitFor12 = ((digit12MultTwo % 100) - endDigitFor12) / 10;
        endDigitFor10 = digit10MultTwo % 10;
        startDigitFor10 = ((digit10MultTwo % 100) - endDigitFor10) / 10;
        endDigitFor8 = digit8MultTwo % 10;
        startDigitFor8 = ((digit8MultTwo % 100) - endDigitFor8) / 10;
        endDigitFor6 = digit6MultTwo % 10;
        startDigitFor6 = ((digit6MultTwo % 100) - endDigitFor6) / 10;
        endDigitFor4 = digit4MultTwo % 10;
        startDigitFor4 = ((digit4MultTwo % 100) - endDigitFor4) / 10;
        endDigitFor2 = digit2MultTwo % 10;
        startDigitFor2 = ((digit2MultTwo % 100) - endDigitFor2) / 10;
        digitsSum = (endDigitFor16 + startDigitFor16 + endDigitFor14 + startDigitFor14 + endDigitFor12 + startDigitFor12
                     + endDigitFor10 + startDigitFor10 + endDigitFor8 + startDigitFor8 + endDigitFor6 + startDigitFor6 + endDigitFor4
                     + startDigitFor4 + endDigitFor2 + startDigitFor2);
        finalSum = (digitsSum + digit1 + digit3 + digit5 + digit7 + digit9 + digit11 + digit13 + digit15);
        checkEndDigitFinalSum = finalSum % 10;
        if (checkEndDigitFinalSum == 0)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }

    }
    // If I didn't get into the AMEX, MASTERCARD, or VISA cases, then this flag is false which means the user never got into those
    // cases which means they entered an invalid number.
    if (flag == false)
    {
        printf("INVALID\n");
    }
    return 0;
}

