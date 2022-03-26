//main.c
#include <stdio.h>

#include "sm4.h"
#include "sm4_x4.h"

int main() {
    SM4_Key sm4_key;
    uint8_t key[16] = { 0 };
    uint8_t a[16 * 4] = { 0 };
    uint8_t b[16 * 4];
    SM4_KeyInit(key, &sm4_key);
    SM4_Encrypt_x4(a, b, &sm4_key);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 16; j++) {
            printf("%02x ", b[16 * i + j]);
        }
        printf("\n");
    }
    return 0;
}