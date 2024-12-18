#include <stdio.h>

// Function to get decimal value of a Roman numeral symbol
int getValue(char c) {
    // Using switch to map Roman symbols to their decimal values
    switch(c) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default: return 0;
    }
}

// Function to get length of string without using strlen
int getLength(char str[]) {
    int len = 0;
    // Only need to check for '\0' since we null-terminate our strings
    while(str[len] != '\0') {
        len++;
    }
    return len;
}

// Function to convert Roman numeral to decimal
int romanToDecimal(char str[]) {
    int result = 0;
    int len = getLength(str);

    for(int i = 0; i < len; i++) {
        int current = getValue(str[i]);
        int next = 0;

        if (i + 1 < len) {
            next = getValue(str[i + 1]);
        }

        if (i + 1 < len && current < next) {
            result += (next - current);
            i++;
        } else {
            result += current;
        }
    }
    return result;
}

// Function to write a word to output file
void writeWord(FILE *fp, char *word) {
    int i = 0;
    // Write each character of the word
    while(word[i] != '\0') {
        putc(word[i], fp);
        i++;
    }
}

// Function to convert number to words and write to file
void numberToWords(FILE *fp, int num) {

    // Arrays for number words
    char *ones[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
    char *tens[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    char *teens[] = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};

    // Handle thousands
    if(num >= 1000) {
        writeWord(fp, ones[num/1000]);
        putc(' ', fp);
        writeWord(fp, "Thousand");
        if(num % 1000 != 0) putc(' ', fp);
        num = num % 1000;
    }

    // Handle hundreds
    if(num >= 100) {
        writeWord(fp, ones[num/100]);
        putc(' ', fp);
        writeWord(fp, "Hundred");
        if(num % 100 != 0) putc(' ', fp);
        num = num % 100;
    }

    // Handle tens and ones
    if(num >= 20) {
        writeWord(fp, tens[num/10]);
        if(num % 10 != 0) {
            putc(' ', fp);
            writeWord(fp, ones[num%10]);
        }
    }
    else if(num >= 10) {
        writeWord(fp, teens[num-10]);
    }
    else if(num > 0) {
        writeWord(fp, ones[num]);
    }
}

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    if(!input || !output) {
        printf("Error opening files\n");
        return 1;
    }

    char line[100];
    int lineIndex = 0;
    char c;
    
    // Continue reading until we hit EOF
    while((c = getc(input)) != EOF) {
        // Process line when newline is found
        if(c == '\n') {
            if(lineIndex > 0) {
                // Null terminate the current line
                line[lineIndex] = '\0';
                
                // Variables for parsing
                char roman1[50] = {0};
                char roman2[50] = {0};
                char op;
                int j = 0, k = 0;

                // Parse first Roman numeral
                while(line[j] != ' ' && line[j] != '\0') {
                    roman1[k] = line[j];
                    j++; k++;
                }
                roman1[k] = '\0';

                // Skip spaces and get operator
                while(line[j] == ' ') j++;
                op = line[j++];

                // Skip spaces and get second Roman numeral
                while(line[j] == ' ') j++;
                k = 0;
                while(j < lineIndex) {
                    roman2[k] = line[j];
                    j++; k++;
                }
                roman2[k] = '\0';

                // Convert and calculate
                int n1 = romanToDecimal(roman1);
                int n2 = romanToDecimal(roman2);

                // All operations are addition for this specific problem
                int result = n1 + n2;

                // Write result to output file
                numberToWords(output, result);
                putc('\n', output);
            }
            
            // Reset line buffer
            lineIndex = 0;
        } else {
            // Add character to current line
            line[lineIndex++] = c;
        }
    }

    // Process the last line if it doesn't end with newline
    if(lineIndex > 0) {
        // Null terminate the current line
        line[lineIndex] = '\0';
        
        // Variables for parsing
        char roman1[50] = {0};
        char roman2[50] = {0};
        char op;
        int j = 0, k = 0;

        // Parse first Roman numeral
        while(line[j] != ' ' && line[j] != '\0') {
            roman1[k] = line[j];
            j++; k++;
        }
        roman1[k] = '\0';

        // Skip spaces and get operator
        while(line[j] == ' ') j++;
        op = line[j++];

        // Skip spaces and get second Roman numeral
        while(line[j] == ' ') j++;
        k = 0;
        while(j < lineIndex) {
            roman2[k] = line[j];
            j++; k++;
        }
        roman2[k] = '\0';

        // Convert and calculate
        int n1 = romanToDecimal(roman1);
        int n2 = romanToDecimal(roman2);
        int result = n1 + n2;

        // Write result to output file
        numberToWords(output, result);
        putc('\n', output);
    }

    fclose(input);
    fclose(output);
    return 0;
}
