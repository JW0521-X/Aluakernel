#include <stdint.h>

struct alua_boot_info {
    uint64_t framebuffer;
    uint32_t width;
    uint32_t height;
    uint32_t pitch;
};

struct __attribute__((packed)) alua_header {
    char     magic[6];
    uint16_t version;
    uint64_t entry;
    uint64_t load_addr;
    uint64_t kernel_size;
    uint64_t bss_size;
};

static uint64_t g_reloc_offset = 0;

#define RELOC(ptr) ((__typeof__(&(ptr)[0]))((uint64_t)(ptr) + g_reloc_offset))

extern const uint8_t _binary_cp850_8x16_psf_start[];

__attribute__((section(".alua_header")))
__attribute__((used))
struct alua_header header = {
    .magic = "ALUAOS", .version = 1, .entry = 0x80, .load_addr = 0,
    .kernel_size = 1024 * 512, .bss_size = 1024 * 512
};

void draw_glyph(struct alua_boot_info* binfo, uint8_t* font_ptr, unsigned char c, int x, int y, uint32_t color) {
    uint8_t* glyph = font_ptr + 4 + (c * 16);
    volatile uint32_t* fb = (volatile uint32_t*)binfo->framebuffer;
    for (int i = 0; i < 16; i++) {
        uint8_t row = glyph[i];
        for (int j = 0; j < 8; j++) {
            if ((row >> (7 - j)) & 1) {
                fb[(y + i) * binfo->pitch + (x + j)] = color;
            }
        }
    }
}

void k_print(struct alua_boot_info* binfo, uint8_t* font_ptr, const char* str, int* px, int* py, uint32_t color) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            *px = 60; *py += 16;
            continue;
        }
        draw_glyph(binfo, font_ptr, (unsigned char)str[i], *px, *py, color);
        *px += 8;
        if (*px + 8 > binfo->width) { *px = 60; *py += 16; }
    }
}

__attribute__((ms_abi))
void kernel_main(struct alua_boot_info* binfo) {

    uintptr_t rip;
    __asm__ ("lea kernel_main(%%rip), %0" : "=r"(rip));
    g_reloc_offset = rip - (uintptr_t)kernel_main;

    if (!binfo) return;
    volatile uint32_t* fb = (volatile uint32_t*)binfo->framebuffer;

    uint8_t* font_search;
    __asm__ ("lea _binary_cp850_8x16_psf_start(%%rip), %0" : "=r"(font_search));
    uint8_t* font_ptr = 0;
    for (int i = 0; i < 2048; i++) {
        if (font_search[i] == 0x36 && font_search[i+1] == 0x04) {
            font_ptr = &font_search[i];
            break;
        }
    }

    if (!font_ptr) {
        for(int i=0; i<100; i++) fb[i] = 0xFFFF0000;
        while(1) __asm__("hlt");
    }

    for (uint32_t i = 0; i < binfo->height * binfo->pitch; i++) fb[i] = 0xFF000000;

    int x = 60, y = 60;
    
    k_print(binfo, font_ptr, RELOC("Welcome to AluaKernel! "), &x, &y, 0xFFFFFFFF);

    while (1) { __asm__ __volatile__("hlt"); }
}

