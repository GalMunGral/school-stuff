import java.util.Comparator;
import java.util.Random;
import java.util.LinkedList;

/**
 * Your implementation of various sorting algorithms.
 *
 * @author Wenqi He
 * @version 1.0
 */
public class Sorting {

  public static <T> void bubbleSort(T[] arr, Comparator<T> comparator) {
    if (arr == null) {
      throw new IllegalArgumentException("Please provide an array.");
    }
    if (comparator == null) {
      throw new IllegalArgumentException("Please provide a comparator.");
    }
    int i = 0;
    boolean swapped = true;
    while (i < arr.length - 1 && swapped) {
      swapped = false;
      for (int j = 0; j < arr.length - i - 1; j++) {
        if (comparator.compare(arr[j], arr[j + 1]) > 0) {
          T temp = arr[j];
          arr[j] = arr[j + 1];
          arr[j + 1] = temp;
          swapped = true;
        }
      }
      i++;
    }
  }

  public static <T> void insertionSort(T[] arr, Comparator<T> comparator) {
    if (arr == null) {
      throw new IllegalArgumentException("Please provide an array.");
    }
    if (comparator == null) {
      throw new IllegalArgumentException("Please provide a comparator.");
    }
    for (int i = 1; i < arr.length; i++) {
      int j = i;
      while (j > 0 && comparator.compare(arr[j - 1], arr[j]) > 0) {
        T temp = arr[j];
        arr[j] = arr[j - 1];
        arr[j - 1] = temp;
        j--;
      }
    }
  }

  public static <T> void quickSort(
    T[] arr,
    Comparator<T> comparator,
    Random rand
  ) {
    if (arr == null) {
      throw new IllegalArgumentException("Please provide an array.");
    }
    if (comparator == null) {
      throw new IllegalArgumentException("Please provide a comparator.");
    }
    if (rand == null) {
      throw new IllegalArgumentException("Please provide a random object.");
    }
    if (arr.length == 0) return;
    quickSort(arr, comparator, rand, 0, arr.length);
  }

  /**
   * Recursive helper method for {@code quickSort}.
   * @param arr the array being sorted
   * @param comparator the Comparator used to compare the data in arr
   * @param rand the Random object used to select pivots
   * @param left the start index of the sub-array
   * @param right the end index of the sub-array
   * @param <T> data type to sort
   */
  private static <T> void quickSort(
    T[] arr,
    Comparator<T> comparator,
    Random rand,
    int left,
    int right
  ) {
    if (right - left == 1) return;
    int pivotIndex = rand.nextInt(right - left) + left;
    T pivot = arr[pivotIndex];
    T temp = arr[left];
    arr[left] = arr[pivotIndex];
    arr[pivotIndex] = temp;
    int i = left + 1;
    int j = right - 1;
    while (i <= j) {
      while (i < right && comparator.compare(arr[i], pivot) <= 0) i++;
      while (j > left && comparator.compare(arr[j], pivot) >= 0) j--;
      if (i < j) {
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        i++;
        j--;
      }
    }

    temp = arr[j];
    arr[j] = arr[left];
    arr[left] = temp;
    if (j > left) quickSort(arr, comparator, rand, left, j);
    if (right > j + 1) quickSort(arr, comparator, rand, j + 1, right);
  }

  public static <T> void mergeSort(T[] arr, Comparator<T> comparator) {
    if (arr == null) {
      throw new IllegalArgumentException("Please provide an array.");
    }
    if (comparator == null) {
      throw new IllegalArgumentException("Please provide a comparator.");
    }
    if (arr.length == 1 || arr.length == 0) return;
    int midIndex = arr.length / 2;
    T[] leftArray = (T[]) new Object[midIndex];
    for (int i = 0; i < midIndex; i++) {
      leftArray[i] = arr[i];
    }
    T[] rightArray = (T[]) new Object[arr.length - midIndex];
    for (int i = midIndex; i < arr.length; i++) {
      rightArray[i - midIndex] = arr[i];
    }
    mergeSort(leftArray, comparator);
    mergeSort(rightArray, comparator);
    int i = 0;
    int j = 0;
    int cur = 0;
    while (i < leftArray.length && j < rightArray.length) {
      if (comparator.compare(leftArray[i], rightArray[j]) <= 0) {
        arr[cur] = leftArray[i];
        i++;
      } else {
        arr[cur] = rightArray[j];
        j++;
      }
      cur++;
    }
    while (i < leftArray.length) {
      arr[cur] = leftArray[i];
      i++;
      cur++;
    }
    while (j < rightArray.length) {
      arr[cur] = rightArray[j];
      j++;
      cur++;
    }
  }

  public static int[] lsdRadixSort(int[] arr) {
    if (arr == null) {
      throw new IllegalArgumentException("Please provide an array.");
    }
    if (arr.length == 0) return arr;
    LinkedList<Integer>[] buckets = (LinkedList<Integer>[]) new LinkedList[19];
    for (int i = 0; i < 19; i++) {
      buckets[i] = (LinkedList<Integer>) new LinkedList();
    }
    int max = Math.abs(arr[0]);
    for (int i = 1; i < arr.length; i++) {
      if (arr[i] == Integer.MIN_VALUE) {
        max = Integer.MAX_VALUE;
      } else {
        int a = Math.abs(arr[i]);
        if (a > max) max = a;
      }
    }
    int iterations = 0;
    if (max == 0) {
      iterations = 1;
    } else {
      while (max != 0) {
        max = max / 10;
        iterations++;
      }
    }
    for (int i = 1; i <= iterations; i++) {
      for (int n : arr) {
        int digit;
        if (i == 10) {
          digit = n / pow(10, i - 1);
        } else {
          digit = n / pow(10, i - 1) - n / pow(10, i) * 10;
        }
        buckets[digit + 9].add(n);
      }
      int index = 0;
      for (int j = 0; j < 19; j++) {
        while (!buckets[j].isEmpty()) {
          arr[index] = buckets[j].remove();
          index++;
        }
      }
    }
    return arr;
  }

  public static int[] msdRadixSort(int[] arr) {
    if (arr == null) {
      throw new IllegalArgumentException("Please provide an array.");
    }
    if (arr.length == 0) return arr;
    int max = Math.abs(arr[0]);
    for (int i = 1; i < arr.length; i++) {
      if (arr[i] == Integer.MIN_VALUE) {
        max = Integer.MAX_VALUE;
      } else {
        int a = Math.abs(arr[i]);
        if (a > max) max = a;
      }
    }
    int maxLength = 0;
    if (max == 0) {
      maxLength = 1;
    } else {
      while (max != 0) {
        max = max / 10;
        maxLength++;
      }
    }
    return msdRadixSort(arr, maxLength);
  }

  /**
   * Recursive helper method for {@code msdRadixSort}.
   * @param arr the array being sorted
   * @param i the index (starting from 1) of the digit under inspection.
   * @return the sorted array.
   */
  private static int[] msdRadixSort(int[] arr, int i) {
    LinkedList<Integer>[] buckets = (LinkedList<Integer>[]) new LinkedList[19];
    for (int j = 0; j < 19; j++) {
      buckets[j] = (LinkedList<Integer>) new LinkedList();
    }
    for (int n : arr) {
      int digit;
      if (i == 10) {
        digit = n / pow(10, i - 1);
      } else {
        digit = n / pow(10, i - 1) - n / pow(10, i) * 10;
      }
      buckets[digit + 9].add(n);
    }
    int index = 0;
    for (int j = 0; j < 19; j++) {
      if (buckets[j].size() > 1 && i > 1) {
        int[] bucket = new int[buckets[j].size()];
        for (int k = 0; k < bucket.length; k++) {
          bucket[k] = (int) buckets[j].remove();
        }
        bucket = msdRadixSort(bucket, i - 1);
        for (int n: bucket) {
          arr[index] = n;
          index++;
        }
      } else {
        while (!buckets[j].isEmpty()) {
          arr[index] = (int) buckets[j].remove();
          index++;
        }
      }
    }
    return arr;
  }

  /**
   * Calculate the result of a number raised to a power. Use this method in
   * your radix sorts instead of {@code Math.pow()}.
   *
   * DO NOT MODIFY THIS METHOD.
   *
   * @throws IllegalArgumentException if both {@code base} and {@code exp} are
   * 0
   * @throws IllegalArgumentException if {@code exp} is negative
   * @param base base of the number
   * @param exp power to raise the base to. Must be 0 or greater.
   * @return result of the base raised to that power
   */
  private static int pow(int base, int exp) {
    if (exp < 0) {
      throw new IllegalArgumentException("Exponent cannot be negative.");
    } else if (base == 0 && exp == 0) {
      throw new IllegalArgumentException("Both base and exponent cannot be 0.");
    } else if (exp == 0) {
      return 1;
    } else if (exp == 1) {
      return base;
    }
    int halfPow = pow(base, exp / 2);
    if (exp % 2 == 0) {
      return halfPow * halfPow;
    } else {
      return halfPow * halfPow * base;
    }
  }
}
