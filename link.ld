/* The entry point of the program is the _start symbol. */
/* When the program starts executing, it will begin at */
/* the address defined by _start */
ENTRY(_start)

MEMORY
{
  /* Define the memory regions */
  ram : ORIGIN = 0x80000000, LENGTH = 64K /* 64KB of RAM starting at 0x80000000 */
}

SECTIONS
{
    /* sets the current memory position */
    /* to the origin of ram */
    . = ORIGIN(ram); 

    /* specific defined section */
    _start :
    {
    /* Link the function with the attribute .start */
    KEEP(*(.start))
    } > ram

    /* Code goes in the text section */
    .text :
    {
    *(.text)
    } > ram

    /* Any initialized data goes in the .data section */
    .data :
    {
    *(.data)
    } > ram

    /* Any uninitialized data goes in the .bss section */
    .bss :
    {
    *(.bss)
    } > ram
}
