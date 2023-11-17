/*
 * Copyright (c) 2023 Rumbledethumps
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * SPDX-License-Identifier: Unlicense
 */

#include <rp6502.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
//#include "raspberry_128x128_bgar5515.h"
#include "possum.h"
#include "lookups.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <fcntl.h>


#define SPRITE_CONFIG 0xF000
#define SPRITE_LENGTH 10






void main()
{
    FILE * input;
    int result;
    uint8_t rotation =0;
    uint16_t cos;
    uint16_t negsin;
    uint16_t sin;

    unsigned u;
uint8_t v;

    // Copy sprite data
    RIA.addr0 = 0;
    RIA.step0 = 1;

    for (u = 0; u < sizeof(possum); u++)
        RIA.rw0 = possum[u];   
        xram0_struct_set(SPRITE_CONFIG, vga_mode4_asprite_t, transform[0],256);// 1.0    
        xram0_struct_set(SPRITE_CONFIG, vga_mode4_asprite_t, transform[1], 0);
        xram0_struct_set(SPRITE_CONFIG, vga_mode4_asprite_t, transform[2], 0);

        xram0_struct_set(SPRITE_CONFIG, vga_mode4_asprite_t, transform[3], 0);
        xram0_struct_set(SPRITE_CONFIG, vga_mode4_asprite_t, transform[4], 256); // 1.0
        xram0_struct_set(SPRITE_CONFIG, vga_mode4_asprite_t, transform[5], 0);

        xram0_struct_set(SPRITE_CONFIG, vga_mode4_asprite_t, x_pos_px, 100);
        xram0_struct_set(SPRITE_CONFIG, vga_mode4_asprite_t, y_pos_px, 100);
        xram0_struct_set(SPRITE_CONFIG, vga_mode4_asprite_t, xram_sprite_ptr, 0x0000);
        xram0_struct_set(SPRITE_CONFIG, vga_mode4_asprite_t, log_size, 7);
        xram0_struct_set(SPRITE_CONFIG, vga_mode4_asprite_t, has_opacity_metadata, true);
    

    // Program VGA
    xreg_vga_canvas(1);
    xreg_vga_mode(0);
    xreg_vga_mode(4, 1, SPRITE_CONFIG, SPRITE_LENGTH);

    // Vsync loop
    v = RIA.vsync;
    while (1)
    {
        if (RIA.vsync == v)
            continue;
        v = RIA.vsync;

        cos = cos_lookup_fp8_8[rotation];
        sin = sin_lookup_fp8_8[rotation];
        negsin = 65535- sin;

        xram0_struct_set(SPRITE_CONFIG, vga_mode4_asprite_t, transform[0], cos  );
        xram0_struct_set(SPRITE_CONFIG, vga_mode4_asprite_t, transform[1], negsin);
        xram0_struct_set(SPRITE_CONFIG, vga_mode4_asprite_t, transform[2], 0);
        xram0_struct_set(SPRITE_CONFIG, vga_mode4_asprite_t, transform[3], sin);
        xram0_struct_set(SPRITE_CONFIG, vga_mode4_asprite_t, transform[4], cos);
        xram0_struct_set(SPRITE_CONFIG, vga_mode4_asprite_t, transform[5], 0);
    
        rotation++;
        if (rotation == 256)
        rotation = 0;



    }

}