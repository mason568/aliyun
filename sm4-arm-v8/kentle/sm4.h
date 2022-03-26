// sm4.h
#ifndef SM4_H
#define SM4_H

#include <stdint.h>

/**
 * @brief SM4 ÃÜÔ¿
 */
typedef struct _SM4_Key {
    uint32_t rk[32];//32ÂÖÃÜÔ¿
} SM4_Key;

/**
 * @brief ³õÊ¼»¯ SM4 ÂÖÃÜÔ¿
 * @param key 128bit³¤¶ÈÃÜÔ¿
 * @param sm4_key SM4 ÃÜÔ¿
 */
void SM4_KeyInit(uint8_t* key, SM4_Key* sm4_key);

#endif
