/**
 * Your implementation of an ArrayList.
 *
 * @author WENQI HE
 * @version 1
 */
public class ArrayList<T> implements ArrayListInterface<T> {
  
  private T[] backingArray;
  private int size;

  public ArrayList() {
      backingArray = (T[]) new Object[INITIAL_CAPACITY];
      size = 0;
  }

  @Override
  public void addAtIndex(int index, T data) {
    if (index < 0 || index > size) {
      throw new IndexOutOfBoundsException("Cannot find the given index.");
    }
    if (data == null) {
      throw new IllegalArgumentException("Cannot add a null item.");
    }
    if (index == size && size + 1 <= backingArray.length) {
      backingArray[size] = data;
    } else {
      T[] tempArray;
      if (size + 1 > backingArray.length) {
        tempArray = (T[]) new Object[backingArray.length * 2];
      } else {
        tempArray = (T[]) new Object[backingArray.length];
      }
      for (int i = 0; i < index; i++) tempArray[i] = backingArray[i];
      for (int i = index; i < size; i++) tempArray[i + 1] = backingArray[i];
      tempArray[index] = data;
      backingArray = tempArray;
    }
    size++;
  }

  @Override
  public void addToFront(T data) {
    addAtIndex(0, data);
  }

  @Override
  public void addToBack(T data) {
    addAtIndex(size, data);
  }

  @Override
  public T removeAtIndex(int index) {
    T value = get(index);
    if (index == size - 1) {
      backingArray[index] = null;
    } else {
      T[] tempArray = (T[]) new Object[backingArray.length];
      for (int i = 0; i < index; i++) {
        tempArray[i] = backingArray[i];
      }
      for (int i = index; i < size - 1; i++) {
        tempArray[i] = backingArray[i + 1];
      }
      backingArray = tempArray;
    }
    size--;
    return value;
  }

  @Override
  public T removeFromFront() {
    if (isEmpty()) return null;
    return removeAtIndex(0);
  }

  @Override
  public T removeFromBack() {
    if (isEmpty()) return null;
    return removeAtIndex(size - 1);
  }

  @Override
  public T get(int index) {
    if (index < 0 || index >= size) {
        throw new IndexOutOfBoundsException("Cannot find the given index.");
    }
    return backingArray[index];
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
    backingArray = (T[]) new Object[INITIAL_CAPACITY];
    size = 0;
  }

  @Override
  public Object[] getBackingArray() {
    return backingArray;
  }
}
