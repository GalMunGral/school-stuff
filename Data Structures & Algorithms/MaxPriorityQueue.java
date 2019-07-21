/**
 * Your implementation of a max priority queue.
 * 
 * @author Wenqi He
 * @version 1.0
 */
public class MaxPriorityQueue<T extends Comparable<? super T>>
  implements PriorityQueueInterface<T> {

  private HeapInterface<T> backingHeap;

  public MaxPriorityQueue() {
    backingHeap = new MaxHeap();
  }

  @Override
  public void enqueue(T item) {
    backingHeap.add(item);
  }

  @Override
  public T dequeue() {
    return backingHeap.remove();
  }

  @Override
  public boolean isEmpty() {
    return backingHeap.isEmpty();
  }

  @Override
  public int size() {
    return backingHeap.size();
  }

  @Override
  public void clear() {
    backingHeap.clear();
  }

  @Override
  public HeapInterface<T> getBackingHeap() {
    return backingHeap;
  }

}
