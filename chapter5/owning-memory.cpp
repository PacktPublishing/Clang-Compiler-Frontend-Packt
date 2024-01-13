auto main() -> int {
  int* ptr = new int[10];  // allocate an array of 10 ints
  // Missing delete[] for the allocated memory.
  return 0;
}
