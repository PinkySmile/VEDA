String[] shift(String[] array, String dir) {
  if (dir == "up") {
      for (int i = 0; i < array.length - 1; i++)
          array[i] = array[i + 1];
      array[array.length - 1] = null;
  } else {
      for (int i = array.length - 1; i > 1; i--)
          array[i] = array[i - 1];
      array[0] = null;    
  }
  return array;
}