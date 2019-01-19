/**
 * Your implementation of an array-backed queue.
 *
 * @author WENQI HE
 * @version 1.0
 */
public class ArrayQueue<T> implements QueueInterface<T> {
  
  private T[] backingArray;
  private int front;
  private int back;
  private int size;

  public ArrayQueue() {
    backingArray = (T[]) new Object[INITIAL_CAPACITY];
    front = 0;
    back = 0;
    size = 0;
  }

  @Override
  public T dequeue() {
    if (size == 0) {
      throw new java.util.NoSuchElementException("The queue is empty!");
    }
    T object = backingArray[front];
    backingArray[front] = null;
    front = (front + 1) % backingArray.length;
    size--;
    return object;
  }

  @Override
  public void enqueue(T data) {
    if (data == null) {
      throw new IllegalArgumentException("There is nothing to enqueue.");
    }
    if (size + 1 > backingArray.length) {
      T[] tempArray = (T[]) new Object[2 * backingArray.length + 1];
      for (int i = 0; i < size; i++) {
        tempArray[i] = backingArray[(front + i) % backingArray.length];
      }
      backingArray = tempArray;
      front = 0;
      back = size;
    }
    backingArray[back] = data;
    size++;
    back = (front + size) % backingArray.length;
  }

  @Override
  public boolean isEmpty() {
    return size == 0;
  }

  @Override
  public int size() {
    return size;
  }

  public Object[] getBackingArray() {
    return backingArray;
  }
}