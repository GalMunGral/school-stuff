/**
 * Your implementation of a linked stack.
 *
 * @author WENQI HE
 * @version 1.0
 */
public class LinkedStack<T> implements StackInterface<T> {

  private LinkedNode<T> head;
  private int size;

  @Override
  public boolean isEmpty() {
    return size == 0;
  }

  @Override
  public T pop() {
    if (size == 0) {
      throw new java.util.NoSuchElementException("The stack is empty.");
    }
    T object = head.getData();
    head = head.getNext();
    size--;
    return object;
  }

  @Override
  public void push(T data) {
    if (data == null) {
      throw new IllegalArgumentException("There is nothing to push.");
    }
    LinkedNode<T> newNode = new LinkedNode<T>(data, head);
    head = newNode;
    size++;
  }

  @Override
  public int size() {
    return size;
  }

  public LinkedNode<T> getHead() {
    return head;
  }
}