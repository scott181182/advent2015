#include <stdint.h>
#include <stddef.h>



uint32_t MD5_SHIFTS[64] = {
    7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
    5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
    4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
    6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,
};
uint32_t MD5_SINES[64] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,
};

// F, G, H and I are basic MD5 functions.
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

typedef struct {
    uint32_t a;
    uint32_t b;
    uint32_t c;
    uint32_t d;
} MD5State;


#define CHUNK_BIT_SIZE 512
#define BYTES_PER_CHUNK (CHUNK_BIT_SIZE / 8)
#define INTS_PER_CHUNK (BYTES_PER_CHUNK / 4)

#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

void md5_step(MD5State *state, uint32_t chunk[16]) {
    // Initialize hash value for this chunk:
    uint32_t A = state->a;
    uint32_t B = state->b;
    uint32_t C = state->c;
    uint32_t D = state->d;

    // Main loop:
    for (size_t i = 0; i < 64; i++) {
        uint32_t f, g;
        if (i < 16) {
            f = F(B, C, D);
            g = i;
        } else if (i < 32) {
            f = G(B, C, D);
            g = (5 * i + 1) % 16;
        } else if (i < 48) {
            f = H(B, C, D);
            g = (3 * i + 5) % 16;
        } else {
            f = I(B, C, D);
            g = (7 * i) % 16;
        }
        
        // Be wary of the below definitions of a,b,c,d
        uint32_t next_b = f + A + MD5_SINES[i] + chunk[g];
        A = D;
        D = C;
        C = B;
        B = B + ROTATE_LEFT(next_b, MD5_SHIFTS[i]);
    }
    // Add this chunk's hash to result so far:
    state->a += A;
    state->b += B;
    state->c += C;
    state->d += D;
}

void md5_hash(char* input, size_t input_length, MD5State *output) {
    // All variables are unsigned 32 bit and wrap modulo 2^32 when calculating
    uint8_t chunk[BYTES_PER_CHUNK] = { 0 };
    memcpy(chunk, input, input_length);

    // Initialize variables:
    output->a = 0x67452301;
    output->b = 0xefcdab89;
    output->c = 0x98badcfe;
    output->d = 0x10325476;
    
    // Pre-processing: adding a single 1 bit
    chunk[input_length] = 0x80;

    // append original length in bits mod 2^64 to message
    uint64_t input_bit_length = input_length * 8;
    memcpy(chunk + BYTES_PER_CHUNK - sizeof(uint64_t), &input_bit_length, sizeof(uint64_t));

    md5_step(output, (uint32_t*)chunk);
};
