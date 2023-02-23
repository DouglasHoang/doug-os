gdt:
  null_descriptor: dw 0, 0, 0, 0
  kernel_code_descriptor: dw 0xFFFF, 0x0000, 0x9A00, 0x00CF
  kernel_data_descriptor: dw 0xFFFF, 0x0000, 0x9200, 0x00CF
  userspace_code_descriptor: dw 0xFFFF, 0x000, 0xFA00, 0x00CF
  userspace_data_descriptor: dw 0xFFFF, 0x0000, 0xF200, 0x00CF

gdtr:
  gdt_size_in_bytes: dw (5 * 8)
  gdt_base_address: dd gdt