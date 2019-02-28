/**
 * Your implementation of a linked queue.
 *
 * @author WENQI HE
 * @version 1.0
 */
public class LinkedQueue<T> implements QueueInterface<T> {

  private LinkedNode<T> head;
  private LinkedNode<T> tail;
  private int size;

  @Override
  public T dequeue() {
    if (size == 0) {
      throw new java.util.NoSuchElementException("The queue is empty!");
    }
    T object = head.getData();
    head = head.getNext();
    size--;
    return object;
  }

  @Override
  public void enqueue(T data) {
    if (data == null) {
      throw new IllegalArgumentException("There is nothing to enqueue.");
    }
    LinkedNode<T> newNode = new LinkedNode<T>(data);
    if (size == 0) {
      head = newNode;
    } else {
      tail.setNext(newNode);
    }
    tail = newNode;
    size++;
  }

  @Override
  public boolean isEmpty() {
    return size == 0;
  }

  @Override
  public int size() {
    return size;
  }

  public LinkedNode<T> getHead() {
    return head;
  }

  public LinkedNode<T> getTail() {
    return tail;
  }
}