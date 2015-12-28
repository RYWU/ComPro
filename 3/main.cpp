//
//  main.cpp
//  5
//
//  Created by RYWU on 11/3/15.
//  Copyright (c) 2015 吳瑞洋公司. All rights reserved.
//
#include <iostream>
#include <algorithm> // fill()
#define DIGITOFNUM 1500
using namespace std;

struct Number {
    int number[DIGITOFNUM] = {0};
};
void Number_init(Number* n);
void Number_print(Number n);
Number larger_sum(Number previous_num, int previous_sum, int current_sum);
Number equal_sum(Number previous_num, int previous_sum, int current_sum);
Number smaller_sum(Number previous_num, int previous_sum, int current_sum);
Number find_next(Number previous_num, int previous_sum, int current_sum);
void decipher(int size, int cipher_array[]);

int main(int argc, const char * argv[]) {
    int T = 0;
    scanf("%d", &T);
    
    int size = 0;
    int cipher_array[1002] = {0};
    
    for (int i = 0; i < T; i++) {
        fill(cipher_array, cipher_array+1002, -1);
        scanf("%d", &size);
        cipher_array[0] = 0;
        for (int j = 1; j <= size; j++) {
            scanf("%d", &cipher_array[j]);
        }
        decipher(size, cipher_array);
        printf("\n");
    }
    return 0;
}

void Number_init(Number* n){
    /*
     This function initialize the struct Number n all digit to '0'.
     @param (Number) n:
     */    
    for (int i = 0; i < DIGITOFNUM; i++){
        n->number[i] = 0;
    }
}

void Number_print(Number n){
    /*
     This function print the value of struct(Number) n to string.
     @param (Number) n:
     @return (void)
     */
    int scale = 0;
    for (int i = DIGITOFNUM-1; i >= 0; i--){
        if (n.number[i] != 0){
            scale = i;
            break;
        }
    }
    for (int i = scale; i >= 0; i--){
        printf("%d", n.number[i]);
    }
}

Number find_next(Number previous_num, int previous_sum, int current_sum) {
    /*
     This function calculate the next Number, given previous Number, and previous number's sum.
     @param (Number) previous_num:
     @param (int) previous_sum:
     @param (int) current_sum:
     @return (Number) next Number:
     */
    Number n;
    Number_init(&n);
    
    if (current_sum > previous_sum) {
        n = larger_sum(previous_num, previous_sum, current_sum);
    }
    else if (current_sum < previous_sum) {
        n = smaller_sum(previous_num, previous_sum, current_sum);
    }
    else if (current_sum == previous_sum) {
        n = equal_sum(previous_num, previous_sum, current_sum);
    }
    return n;
}

void decipher(int size, int cipher_array[]){
    /*
     This function calculate the decipher value of a given cipher array.
     @param (int) size: the size of the cipher array.
     @param (int) cipher_array[]: the cipher array.
     @return (void): print the values of the deciphered array;
     */
    
    Number answer[1002];
    for (int i = 0; i < 1002; i++){ // initialize the answer[].
        Number_init(&answer[i]);
    }
    
    answer[0].number[0] = 0; // initialize the answer[0] = 0;
    
    for (int i = 1; i <= size; i++) {
        answer[i] = find_next(answer[i-1], cipher_array[i-1], cipher_array[i]);
    }
    
    for (int i = 1; i < size; i++){ // print the answer array.
        Number_print(answer[i]);
        printf(" ");
    }
    Number_print(answer[size]);
}


Number larger_sum(Number previous_num, int previous_sum, int current_sum) {
    /*
     This function calculate the next Number when current_sum > previous sum.
     @param (Number) previous_num:
     @param (int) previous_sum:
     @param (int) current_sum:
     @return (Number) larger_sum:
     */
    int difference = current_sum - previous_sum;
    int digit_pointer = 0;
    while (difference > 0){
        if (previous_num.number[digit_pointer] + difference >= 9){
            difference -= 9 - previous_num.number[digit_pointer];
            previous_num.number[digit_pointer] = 9;
            digit_pointer ++;
        } else { // previous_num.number[digit_pointer] + difference < 9
            previous_num.number[digit_pointer] += difference;
            difference = 0;
        }
    }
    return previous_num;
}

Number equal_sum(Number previous_num, int previous_sum, int current_sum) {
    /*
     This function calculate the next Number when current_sum == previous sum.
     @param (Number) previous_num:
     @param (int) previous_sum:
     @param (int) current_sum:
     @return (Number) larger_sum:
     */
    int digit_pointer = 0;
    while (current_sum == previous_sum || previous_num.number[digit_pointer] == 9){
        previous_sum -= previous_num.number[digit_pointer];
        previous_num.number[digit_pointer] = 0;
        digit_pointer++;
    }
    
    previous_num.number[digit_pointer] += 1;
    previous_sum += 1;
    
    return larger_sum(previous_num, previous_sum, current_sum);
}

Number smaller_sum(Number previous_num, int previous_sum, int current_sum) {
    /*
     This function calculate the next Number when current_sum < previous sum.
     @param (Number) previous_num:
     @param (int) previous_sum:
     @param (int) current_sum:
     @return (Number) larger_sum:
     */
    int digit_pointer = 0;
    while (current_sum <= previous_sum || previous_num.number[digit_pointer] == 9){
        previous_sum -= previous_num.number[digit_pointer];
        previous_num.number[digit_pointer] = 0;
        digit_pointer++;
    }
    
    previous_num.number[digit_pointer] += 1;
    previous_sum += 1;
    
    if (current_sum == previous_sum) {
        return previous_num;
    }
    else {
        return larger_sum(previous_num, previous_sum, current_sum);
    }
    return previous_num;
}

