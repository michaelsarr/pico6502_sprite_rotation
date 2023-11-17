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

#define SPRITE_WIDTH 128




void main()
{

    uint8_t rotation = 0;
    uint16_t   sprite_center_x = 100;
    uint16_t   sprite_center_y = 100;

    uint16_t   sprite_x;
    uint16_t   sprite_y;
    
    uint16_t loop;
    
    uint8_t rotoffset = 4;


    unsigned u;
    uint8_t v;

    // Copy sprite data
    RIA.addr0 = 0;
    RIA.step0 = 1;

    for (u = 0; u < sizeof(possum); u++)
        RIA.rw0 = possum[u];   
        xram0_struct_set(SPRITE_CONFIG, vga_mode4_asprite_t, transform[0],256);// 256  -> 1.0, 080 -> 0.5    
        xram0_struct_set(SPRITE_CONFIG, vga_mode4_asprite_t, transform[1], 0);
        xram0_struct_set(SPRITE_CONFIG, vga_mode4_asprite_t, transform[2], 0);

        xram0_struct_set(SPRITE_CONFIG, vga_mode4_asprite_t, transform[3], 0);
        xram0_struct_set(SPRITE_CONFIG, vga_mode4_asprite_t, transform[4], 256); // 1.0
        xram0_struct_set(SPRITE_CONFIG, vga_mode4_asprite_t, transform[5], 0);

        xram0_struct_set(SPRITE_CONFIG, vga_mode4_asprite_t, x_pos_px, sprite_center_x - 90);
        xram0_struct_set(SPRITE_CONFIG, vga_mode4_asprite_t, y_pos_px, sprite_center_y - 90);
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

        sprite_x = sprite_center_x + xpos_diff[rotation];
        sprite_y = sprite_center_y + ypos_diff[rotation];

       if (1)
       {
        xram0_struct_set(SPRITE_CONFIG, vga_mode4_asprite_t, transform[0], cos_lookup_fp8_8[rotation]  );
        xram0_struct_set(SPRITE_CONFIG, vga_mode4_asprite_t, transform[1],  sin_lookup_fp8_8[rotation]);
        xram0_struct_set(SPRITE_CONFIG, vga_mode4_asprite_t, transform[2], 0);
        xram0_struct_set(SPRITE_CONFIG, vga_mode4_asprite_t, transform[3], 65535 - sin_lookup_fp8_8[rotation]);
        xram0_struct_set(SPRITE_CONFIG, vga_mode4_asprite_t, transform[4], cos_lookup_fp8_8[rotation]);
        xram0_struct_set(SPRITE_CONFIG, vga_mode4_asprite_t, transform[5], 0);
       }
       if (true)
        {
        xram0_struct_set(SPRITE_CONFIG, vga_mode4_asprite_t, x_pos_px, sprite_x);
        xram0_struct_set(SPRITE_CONFIG, vga_mode4_asprite_t, y_pos_px, sprite_y);
        }
        for(loop =0 ; loop < 20; loop ++)
                  printf("rotation: %-2d x:%-3d   y:%-3d\n",rotation,sprite_x,sprite_y);

        rotation++;
        if (rotation == 32)
        rotation = 0;



    }

}