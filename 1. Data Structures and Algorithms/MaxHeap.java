/**
 * Your implementation of a max heap.
 *
 * @author Wenqi He
 * @version 1.0
 */
public class MaxHeap<T extends Comparable<? super T>> 
  implements HeapInterface<T> {

  private T[] backingArray;
  private int size;
  
  public MaxHeap() {
    backingArray = (T[]) new Comparable[INITIAL_CAPACITY];
    size = 0;
  }

  @Override
  public void add(T item) {
    if (item == null) {
      throw new IllegalArgumentException("Please specify something to "
        + "add to the heap.");
    }
    if (size + 1 == backingArray.length) {
      T[] tempArray = (T[]) new Comparable[2 * backingArray.length + 1];
      for (int i = 0; i < backingArray.length; i++) {
        tempArray[i] = backingArray[i];
      }
      backingArray = tempArray;
    }
    backingArray[++size] = item;
    int curIndex = size;
    while (curIndex > 1) {
      if (backingArray[curIndex].compareTo(backingArray[curIndex / 2]) > 0) {
        T temp = backingArray[curIndex / 2];
        backingArray[curIndex / 2] = backingArray[curIndex];
        backingArray[curIndex] = temp;
        curIndex = curIndex / 2;
      } else {
        return;
      }
    }
    return;
  }

  @Override
  public T remove() {
    if (size == 0) {
      throw new java.util.NoSuchElementException("There is nothing to remove.");
    }
    T object = backingArray[1];
    backingArray[1] = backingArray[size];
    backingArray[size--] = null;
    int curIndex = 1;
    while (2 * curIndex < size) {
      int maxChild = (
        (
          backingArray[2 * curIndex].compareTo(backingArray[2 * curIndex + 1])
          > 0
        )
        ? 2 * curIndex
        : 2 * curIndex + 1
      );
      if (backingArray[maxChild].compareTo(backingArray[curIndex]) > 0) {
        T temp = backingArray[maxChild];
        backingArray[maxChild] = backingArray[curIndex];
        backingArray[curIndex] = temp;
      } else {
        return object;
      }
      curIndex = maxChild;
    }
    if (2 * curIndex == size) {
      if (backingArray[size].compareTo(backingArray[curIndex]) > 0) {
        T temp = backingArray[size];
        backingArray[size] = backingArray[curIndex];
        backingArray[curIndex] = temp;
      }
    }
    return object;
  }

  @Override
  public boolean isEmpty() {
    return size == 0;
  }

  @Override
  public int size() {
    return size;
  }

  @Override
  public void clear() {
    backingArray = (T[]) new Comparable[INITIAL_CAPACITY];
  }

  @Override
  public Comparable[] getBackingArray() {
    return backingArray;
  }

}
