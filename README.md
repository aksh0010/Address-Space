# Address-Space

It takes three command line arguments with the following information:

  1) The type of the page table. Only two values 1 and 2 can be accepted. 1 means single-level linear page table and 2 means two-level tree-structured page table.
  2) The total number of bits in the binary format of the memory address. This can be an integer in the range [8..63].
  3) The page size in terms of the number of KB (1024 Bytes). This can be 1, 2, 4, 8, 16, 32, 64, 128, 256, 512.

This program outputs
  1) The size of the memory in terms of the number of bytes, the number of KB, the number of MB, or the number of GB, whichever is the most appropriate.
  2) The total number of pages
  3) The total number of page table entries
  4) The size of the page table in terms of the number of bytes
  5) The total number of bits in an address for the VPN
  6) The total number of bits in an address for the offset within a page
  7) The total number of page table entries in a page of a page table (type 2 only)
  8) The total number of pages in a page table (type 2 only)
  9) The total number of bits in an address for the page directory index (type 2 only)
 10) The total number of bits in an address for the page table index (type 2 only)
