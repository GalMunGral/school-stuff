import java.util.NoSuchElementException;
/**
 * Your implementation of a SinglyLinkedList
 *
 * @author WENQI HE
 * @version 1.0
 */
public class SinglyLinkedList<T> implements LinkedListInterface<T> {

  private LinkedListNode<T> head;
  private LinkedListNode<T> tail;
  private int size;

  @Override
  public void addAtIndex(int index, T data) {
    if (index == 0) {
      this.addToFront(data);
    } else if (index == size) {
      this.addToBack(data);
    } else if (index < 0 || index > size) {
      throw new IndexOutOfBoundsException("Cannot add an item here.");
    } else if (data == null) {
      throw new IllegalArgumentException("Please use valid data.");
    } else {
      LinkedListNode<T> currentNode = head;
      int nextIndex = 1;
      while (nextIndex < index) {
        currentNode = currentNode.getNext();
        nextIndex++;
      }
      LinkedListNode<T> newNode = new LinkedListNode<T>(
        data,
        currentNode.getNext()
      );
      currentNode.setNext(newNode);
      size++;
    }
  }

  @Override
  public void addToFront(T data) {
    if (data == null) {
      throw new IllegalArgumentException("Please use valid data.");
    }
    LinkedListNode<T> newNode = new LinkedListNode<T>(data, head);
    head = newNode;
    if (size == 0) tail = newNode;
    size++;
  }

  @Override
  public void addToBack(T data) {
    if (data == null) {
      throw new IllegalArgumentException("Please use valid data.");
    }
    LinkedListNode<T> newNode = new LinkedListNode<T>(data);
    if (size == 0) {
      head = newNode;
    } else {
      tail.setNext(newNode);
    }
    tail = newNode;
    size++;
  }

  @Override
  public T removeAtIndex(int index) {
    if (index < 0 || index >= size) {
      throw new IndexOutOfBoundsException("Nothing to remove here.");
    } else if (index == 0) {
      return this.removeFromFront();
    } else if (index == size - 1) {
      return this.removeFromBack();
    } else {
      LinkedListNode<T> currentNode = head;
      int nextIndex = 1;
      while (nextIndex < index) {
        currentNode = currentNode.getNext();
        nextIndex++;
      }
      T object = currentNode.getNext().getData();
      currentNode.setNext(currentNode.getNext().getNext());
      size--;
      return object;
    }
  }

  @Override
  public T removeFromFront() {
    if (size == 0) return null;
    T object = head.getData();
    head = head.getNext();
    size--;
    return object;
  }

  @Override
  public T removeFromBack() {
    if (size == 0) return null;
    T object = tail.getData();
    tail = null;
    LinkedListNode<T> currentNode = head;
    int nextIndex = 1;
    while (nextIndex < size - 1) {
      currentNode = currentNode.getNext();
      nextIndex++;
    }
    tail = currentNode;
    size--;
    return object;
  }

  @Override
  public T removeFirstOccurrence(T data) {
    if (data == null) {
      throw new IllegalArgumentException("Please specify the data to remove.");
    }
    T object;
    if (head.getData().equals(data)) {
      object = head.getData();
      head = head.getNext();
      return object;
    }
    LinkedListNode<T> currentNode = head;
    while (
      currentNode != null
      && !currentNode.getNext().getData().equals(data)
    ) {
      currentNode = currentNode.getNext();
    }
    if (currentNode == null) {
      throw new NoSuchElementException("Data not found.");
    }
    object = currentNode.getNext().getData();
    currentNode.setNext(currentNode.getNext().getNext());
    if (currentNode.getNext() == null) {
      tail = currentNode;
    }
    return object;
  }

  @Override
  public T get(int index) {
    if (index < 0 || index >= size) {
      throw new IndexOutOfBoundsException("Cannot find an item here.");
    }
    if (index == 0) return this.head.getData();
    if (index == size - 1) return this.tail.getData();
    LinkedListNode<T> currentNode = this.head;
    int currentIndex = 0;
    while (currentIndex < index) {
      currentNode = currentNode.getNext();
      currentIndex++;
    }
    return currentNode.getData();
  }

  @Override
  public Object[] toArray() {
    Object[] array = new Object[this.size];
    LinkedListNode<T> currentNode = this.head;
    int currentIndex = 0;
    while (currentNode != null) {
      array[currentIndex] = currentNode.getData();
      currentNode = currentNode.getNext();
      currentIndex++;
    }
    return array;
  }

  @Override
  public boolean isEmpty() {
    return this.size == 0;
  }

  @Override
  public int size() {
    return this.size;
  }

  @Override
  public void clear() {
    head = null;
    tail = null;
    size = 0;
  }

  @Override
  public LinkedListNode<T> getHead() {
    return head;
  }

  @Override
  public LinkedListNode<T> getTail() {
    return tail;
  }
}
