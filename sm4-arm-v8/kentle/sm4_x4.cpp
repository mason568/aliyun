//sm4_x4.c
#include "sm4_x4.h"

#include <arm_neon.h>

uint8x16_t vqtbl4q_u8(uint8x16x4_t& tb, uint8x16_t tmp) {
    uint8x16_t res;

    return res;
}

uint8x16_t simd_transform16(uint8x16x4_t* table, uint8x16_t input) {
    uint8x16_t  t1 = vqtbl4q_u8(table[0], input);
    uint8x16_t  t2 = vqtbl4q_u8(table[1],
    veorq_u8(input, vdupq_n_u8(0x40)));
    uint8x16_t  t3 = vqtbl4q_u8(table[2],
    veorq_u8(input, vdupq_n_u8(0x80)));
    uint8x16_t  t4 = vqtbl4q_u8(table[3],
    veorq_u8(input, vdupq_n_u8(0xc0)));
    return vorrq_u8(vorrq_u8(t1, t2), vorrq_u8(t3, t4));
}

static uint8_t SBox[256] = {
    0xD6, 0x90, 0xE9, 0xFE, 0xCC, 0xE1, 0x3D, 0xB7, 0x16, 0xB6, 0x14, 0xC2,
    0x28, 0xFB, 0x2C, 0x05, 0x2B, 0x67, 0x9A, 0x76, 0x2A, 0xBE, 0x04, 0xC3,
    0xAA, 0x44, 0x13, 0x26, 0x49, 0x86, 0x06, 0x99, 0x9C, 0x42, 0x50, 0xF4,
    0x91, 0xEF, 0x98, 0x7A, 0x33, 0x54, 0x0B, 0x43, 0xED, 0xCF, 0xAC, 0x62,
    0xE4, 0xB3, 0x1C, 0xA9, 0xC9, 0x08, 0xE8, 0x95, 0x80, 0xDF, 0x94, 0xFA,
    0x75, 0x8F, 0x3F, 0xA6, 0x47, 0x07, 0xA7, 0xFC, 0xF3, 0x73, 0x17, 0xBA,
    0x83, 0x59, 0x3C, 0x19, 0xE6, 0x85, 0x4F, 0xA8, 0x68, 0x6B, 0x81, 0xB2,
    0x71, 0x64, 0xDA, 0x8B, 0xF8, 0xEB, 0x0F, 0x4B, 0x70, 0x56, 0x9D, 0x35,
    0x1E, 0x24, 0x0E, 0x5E, 0x63, 0x58, 0xD1, 0xA2, 0x25, 0x22, 0x7C, 0x3B,
    0x01, 0x21, 0x78, 0x87, 0xD4, 0x00, 0x46, 0x57, 0x9F, 0xD3, 0x27, 0x52,
    0x4C, 0x36, 0x02, 0xE7, 0xA0, 0xC4, 0xC8, 0x9E, 0xEA, 0xBF, 0x8A, 0xD2,
    0x40, 0xC7, 0x38, 0xB5, 0xA3, 0xF7, 0xF2, 0xCE, 0xF9, 0x61, 0x15, 0xA1,
    0xE0, 0xAE, 0x5D, 0xA4, 0x9B, 0x34, 0x1A, 0x55, 0xAD, 0x93, 0x32, 0x30,
    0xF5, 0x8C, 0xB1, 0xE3, 0x1D, 0xF6, 0xE2, 0x2E, 0x82, 0x66, 0xCA, 0x60,
    0xC0, 0x29, 0x23, 0xAB, 0x0D, 0x53, 0x4E, 0x6F, 0xD5, 0xDB, 0x37, 0x45,
    0xDE, 0xFD, 0x8E, 0x2F, 0x03, 0xFF, 0x6A, 0x72, 0x6D, 0x6C, 0x5B, 0x51,
    0x8D, 0x1B, 0xAF, 0x92, 0xBB, 0xDD, 0xBC, 0x7F, 0x11, 0xD9, 0x5C, 0x41,
    0x1F, 0x10, 0x5A, 0xD8, 0x0A, 0xC1, 0x31, 0x88, 0xA5, 0xCD, 0x7B, 0xBD,
    0x2D, 0x74, 0xD0, 0x12, 0xB8, 0xE5, 0xB4, 0xB0, 0x89, 0x69, 0x97, 0x4A,
    0x0C, 0x96, 0x77, 0x7E, 0x65, 0xB9, 0xF1, 0x09, 0xC5, 0x6E, 0xC6, 0x84,
    0x18, 0xF0, 0x7D, 0xEC, 0x3A, 0xDC, 0x4D, 0x20, 0x79, 0xEE, 0x5F, 0x3E,
    0xD7, 0xCB, 0x39, 0x48 };

/**
 * @brief SM4 4组并行
 * @param in 128x4bit输入
 * @param out 128x4bit输出
 * @param sm4_key SM4密钥
 * @param enc 加密(0)或者解密(1)
 */
static void _SM4_do_x4(uint8_t* in, uint8_t* out, SM4_Key* sm4_key, int enc);

void SM4_Encrypt_x4(uint8_t* plaintext, uint8_t* ciphertext, SM4_Key* sm4_key) {
    _SM4_do_x4(plaintext, ciphertext, sm4_key, 0);
}

void SM4_Decrypt_x4(uint8_t* ciphertext, uint8_t* plaintext, SM4_Key* sm4_key) {
    _SM4_do_x4(ciphertext, plaintext, sm4_key, 1);
}

static void _SM4_do_x4(uint8_t* in, uint8_t* out, SM4_Key* sm4_key, int enc) {
    const static uint8_t SubData[16] = { 64, 64, 64, 64, 64, 64, 64, 64,
                                        64, 64, 64, 64, 64, 64, 64, 64 };
    uint8x16_t dec;
    uint8x16x4_t Table[4];  // S表
    uint32x4x4_t x;         //数据
    uint32x4_t tmp_32x4, tmp1_32x4, tmp2_32x4, tmp3_32x4;
    uint8x16_t tmp_8x16, tmp1_8x16, tmp2_8x16;
    //---------------------Load Data------------------
    dec = vld1q_u8(SubData);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            Table[i].val[j] = vld1q_u8(SBox + 64 * i + 16 * j);
        }
    }
    //加载数据，32bit一组分组
    x = vld4q_u32((uint32_t*)in);
    // 32bit内8bit逆序
    x.val[0] = vreinterpretq_u32_u8(vrev32q_u8(vreinterpretq_u8_u32(x.val[0])));
    x.val[1] = vreinterpretq_u32_u8(vrev32q_u8(vreinterpretq_u8_u32(x.val[1])));
    x.val[2] = vreinterpretq_u32_u8(vrev32q_u8(vreinterpretq_u8_u32(x.val[2])));
    x.val[3] = vreinterpretq_u32_u8(vrev32q_u8(vreinterpretq_u8_u32(x.val[3])));
    //-------------------Loop 32-------------------
    for (int i = 0; i < 32; i++) {
        //----------X1 xor X2 xor X3 xor Kr------------
        tmp_32x4 =
            vdupq_n_u32((enc == 0) ? (sm4_key->rk[i]) : (sm4_key->rk[31 - i]));
        tmp_32x4 = veorq_u32(tmp_32x4, x.val[1]);
        tmp_32x4 = veorq_u32(tmp_32x4, x.val[2]);
        tmp_32x4 = veorq_u32(tmp_32x4, x.val[3]);
        //--------------------S Box-------------------

        tmp_8x16 = vreinterpretq_u8_u32(tmp_32x4);   //类型转换
        tmp1_8x16 = vqtbl4q_u8(Table[0], tmp_8x16);  //第一次查表

        tmp_8x16 = vsubq_u8(tmp_8x16, dec);
        tmp2_8x16 = vqtbl4q_u8(Table[1], tmp_8x16);  //第二次查表
        tmp1_8x16 = veorq_u8(tmp1_8x16, tmp2_8x16);

        tmp_8x16 = vsubq_u8(tmp_8x16, dec);
        tmp2_8x16 = vqtbl4q_u8(Table[2], tmp_8x16);  //第三次查表
        tmp1_8x16 = veorq_u8(tmp1_8x16, tmp2_8x16);

        tmp_8x16 = vsubq_u8(tmp_8x16, dec);
        tmp2_8x16 = vqtbl4q_u8(Table[3], tmp_8x16);  //第四次查表
        tmp1_8x16 = veorq_u8(tmp1_8x16, tmp2_8x16);
        tmp_32x4 = vreinterpretq_u32_u8(tmp1_8x16);  //类型转换
        //--------------------L---------------------
        x.val[0] = veorq_u32(x.val[0], tmp_32x4);

        tmp1_32x4 = vshlq_n_u32(tmp_32x4, 2);
        tmp2_32x4 = vshrq_n_u32(tmp_32x4, 32 - 2);
        tmp3_32x4 = veorq_u32(tmp1_32x4, tmp2_32x4);  //循环左移2位
        x.val[0] = veorq_u32(x.val[0], tmp3_32x4);

        tmp1_32x4 = vshlq_n_u32(tmp_32x4, 10);
        tmp2_32x4 = vshrq_n_u32(tmp_32x4, 32 - 10);
        tmp3_32x4 = veorq_u32(tmp1_32x4, tmp2_32x4);  //循环左移10位
        x.val[0] = veorq_u32(x.val[0], tmp3_32x4);

        tmp1_32x4 = vshlq_n_u32(tmp_32x4, 18);
        tmp2_32x4 = vshrq_n_u32(tmp_32x4, 32 - 18);
        tmp3_32x4 = veorq_u32(tmp1_32x4, tmp2_32x4);  //循环左移18位
        x.val[0] = veorq_u32(x.val[0], tmp3_32x4);

        tmp1_32x4 = vshlq_n_u32(tmp_32x4, 24);
        tmp2_32x4 = vshrq_n_u32(tmp_32x4, 32 - 24);
        tmp3_32x4 = veorq_u32(tmp1_32x4, tmp2_32x4);  //循环左移24位
        x.val[0] = veorq_u32(x.val[0], tmp3_32x4);
        //
        tmp_32x4 = x.val[0];
        x.val[0] = x.val[1];
        x.val[1] = x.val[2];
        x.val[2] = x.val[3];
        x.val[3] = tmp_32x4;
    }
    //逆序x
    tmp_32x4 = x.val[0];
    x.val[0] = x.val[3];
    x.val[3] = tmp_32x4;
    tmp_32x4 = x.val[1];
    x.val[1] = x.val[2];
    x.val[2] = tmp_32x4;
    // 32bit内8bit逆序
    x.val[0] = vreinterpretq_u32_u8(vrev32q_u8(vreinterpretq_u8_u32(x.val[0])));
    x.val[1] = vreinterpretq_u32_u8(vrev32q_u8(vreinterpretq_u8_u32(x.val[1])));
    x.val[2] = vreinterpretq_u32_u8(vrev32q_u8(vreinterpretq_u8_u32(x.val[2])));
    x.val[3] = vreinterpretq_u32_u8(vrev32q_u8(vreinterpretq_u8_u32(x.val[3])));
    //存储数据
    vst4q_u32((uint32_t*)out, x);
}