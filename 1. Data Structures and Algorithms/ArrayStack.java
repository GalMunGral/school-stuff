/**
 * Your implementation of an array-backed stack.
 *
 * @author WENQI HE
 * @version 1.0
 */
public class ArrayStack<T> implements StackInterface<T> {

  private T[] backingArray;
  private int size;

  public ArrayStack() {
    backingArray = (T[]) new Object[INITIAL_CAPACITY];
    size = 0;
  }

  @Override
  public boolean isEmpty() {
    return size == 0;
  }

  @Override
  public T pop() {
    if (size == 0) {
      throw new java.util.NoSuchElementException("The stack is empty.");
    }
    T object = backingArray[--size];
    backingArray[size] = null;
    return object;
  }

  @Override
  public void push(T data) {
    if (data == null) {
      throw new IllegalArgumentException("There is nothing to push.");
    }
    if (size + 1 > backingArray.length) {
      T[] tempArray = (T[]) new Object[2 * backingArray.length + 1];
      for (int i = 0; i < size; i++) {
        tempArray[i] = backingArray[i];
      }
      backingArray = tempArray;
    }
    backingArray[size++] = data;
  }

  @Override
  public int size() {
    return size;
  }

  public Object[] getBackingArray() {
    return backingArray;
  }
}
