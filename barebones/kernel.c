// GCC provides these header files automatically
// They guve us access to useful thingsl ike fixed-width types
#include <stddef.h>
#include <stdint.h>

// First, let's do some basic checks to make sure we are using our x86-elf cross-compiler correctly
#if defined(__linux__)
  #error "This code must be compiled with a cross compiler"
#elif !defined(__i386__)
  #error "This code must be compiled with an x86-elf compiler"
#endif

enum vga_color {
  VGA_BLACK = 0,
  VGA_BLUE = 1,
  VGA_GREEN = 2,
  VGA_CYAN = 3,
  VGA_RED = 4,
  VGA_MAGENTA = 5,
  VGA_BROWN = 6,
  VGA_LIGHT_GREY = 7,
  VGA_DARK_GREY = 8,
  VGA_LIGHT_BLUE = 9,
  VGA_LIGHT_GREEN = 10,
  VGA_LIGHT_CYAN = 11,
  VGA_LIGHT_RED = 12,
  VGA_LIGHT_MAGENTA = 13,
  VGA_LIGHT_BROWN = 14,
  VGA_WHITE = 15,
};

// This is the x86's VGA textmode buffer. To display text, we write data to this memory location
volatile uint16_t *vga_buffer = (uint16_t*)0xB8000;
// By default, the VGA textmode buffer has a size of 80x25 characters
const int VGA_COLS = 80;
const int VGA_ROWS = 25;

// We start displaying text in the top-left of the screen (column = 0, row = 0)
int term_col = 0;
int term_row = 0;

static inline size_t calculate_idx(int row, int col) {
  return (VGA_COLS * row) + col;
}

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
  return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
  return (uint16_t) uc | (uint16_t) color << 8;
}

// This function initiates the terminal by clearing it
void term_init(void) {
  // Clear the textmode buffer
  for (int col = 0; col < VGA_COLS; col++) {
    for (int row = 0; row < VGA_ROWS; row++) {
      // The VGA textmode buffer has size (VGA_COLS * VGA_ROWS).
      // Given this, we find an index into the buffer for our character
      const size_t index = calculate_idx(row, col);
      // Entries in the VGA buffer take the binary form BBBBFFFFCCCCCCCC, where:
      // - B is the background color
      // - F is the foreground color
      // C is the ASCII character


      vga_buffer[index] = vga_entry(' ', vga_entry_color(VGA_LIGHT_GREY, VGA_RED));
    }
  }
}

// This function places a single character onto the screen
void term_putc(char c) {
  // Remember - we don't want to display ALL characters!
  switch (c) {
    case '\n': { 
      // Newline characters should return the column to 0, and incrent the row 
      term_col = 0;
      term_row++;
      break;
    }
    default: {
      // Normal characters just get displated and then increment the column
      const size_t index = calculate_idx(term_row, term_col);
      vga_buffer[index] = vga_entry(c, vga_entry_color(VGA_LIGHT_GREY, VGA_RED));
      term_col++;
      break;
    }
  }

  // What happens if we get past the last column? We need to reset the column to 0, and increment the row to get to a new line
  if (term_col >= VGA_COLS) {
    term_col = 0;
    term_row++;
  }

  // What happens if we get past the last row? We need to reset both column and row to 0 in order to loop back to the top of the screen
  if (term_row >= VGA_ROWS) {
    term_col = 0;
    term_row = 0;
  }
}

// This function prints an entire string onto the screen
void term_print(const char *str) {
	for (size_t i = 0; str[i] != '\0'; i ++) // Keep placing characters until we hit the null-terminating character ('\0')
		term_putc(str[i]);
}

void print_me(void) {
  int middle_col = VGA_COLS / 2;
  int middle_row = VGA_ROWS / 2;

  size_t idx = calculate_idx(middle_row, middle_col);

  uint8_t color = 0;


  while (1) {
    vga_buffer[idx] = vga_entry(' ', vga_entry_color(VGA_BLACK, color));

    color = (color + 1) % 16;
  }

}

// This is our kernel's main function
void kernel_main() {
  term_init();
  
  term_print("Hello, World!\n");
  term_print("Welcome to the kernel.\n");
  term_print("Yo what's up.\n");

  print_me();
}