/* linker.ld */
SECTIONS
{
    . = 0x0;

    .header : {
        KEEP(*(.alua_header))
        . = 0x80; 
    }

    .text : {
        *(.text*)
        *(.rodata*)
        *(.data*)
        *(.sdata*)
    }

    __kernel_end = .;

    /DISCARD/ : {
        *(.eh_frame)
        *(.note*)
        *(.comment)
    }

    .bss : {
        __bss_start = .;
        *(.bss*)
        *(COMMON)
        __bss_end = .;
    }
}

