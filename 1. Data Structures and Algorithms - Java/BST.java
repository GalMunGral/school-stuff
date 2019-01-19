import java.util.Collection;
import java.util.List;
import java.util.ArrayList;
import java.util.LinkedList;

/**
 * Your implementation of a binary search tree.
 *
 * @author WENQI HE
 * @version 1.0
 */
public class BST<T extends Comparable<? super T>> implements BSTInterface<T> {

  private BSTNode<T> root;
  private int size;

  public BST() {}

  public BST(Collection<T> data) {
    this();
    if (data == null) {
      throw new IllegalArgumentException("You didn't pass in any data.");
    }
    for (T o : data) {
      if (o == null) {
        throw new IllegalArgumentException("This collection contains "
          + "invalid data.");
      }
      add(o);
    }
  }

  @Override
  public void add(T data) {
    if (data == null) {
      throw new IllegalArgumentException("Please specify something to add.");
    }
    root = recursiveAdd(data, root);
    size++;
  }

  /**
   * Helper method for {@code add()}.
   * Searches for given data recursively, adds a new node containing the data
   * if no such node was found.
   * @param data the data being added.
   * @param node the node currently being inspected.
   * @return the node itself or a new node containing the data if the current
   * node is null.
   */
  private BSTNode<T> recursiveAdd(T data, BSTNode<T> node) {
    if (node == null) return new BSTNode<T>(data);
    if (data.compareTo(node.getData()) < 0) {
      node.setLeft(recursiveAdd(data, node.getLeft()));
    } else if (data.compareTo(node.getData()) > 0) {
      node.setRight(recursiveAdd(data, node.getRight()));
    }
    return node;
  }

  @Override
  public T remove(T data) {
    if (data == null) {
      throw new IllegalArgumentException("Please specify something to remove.");
    }
    BSTNode<T> dummyNode = new BSTNode<T>(null);
    root = recursiveRemove(data, root, dummyNode);
    size--;
    return dummyNode.getData();
  }

  /**
   * Helper method for {@code remove()}.
   * Searches for given data recursively and removes the node containing given
   * data, if such node is found.
   * @param data data that will be removed.
   * @param current the node currently being inspected.
   * @param dummy a dummy node that stores the removed data.
   * @return the node itself or a node that will replace the original node.
   * @throws java.util.NoSuchElementException if given data was not found.
   */
  private BSTNode<T> recursiveRemove(
    T data,
    BSTNode<T> current,
    BSTNode<T> dummy
  ) {
    if (current == null) {
      throw new java.util.NoSuchElementException("Data not found.");
    }
    if (current.getData().equals(data)) {
      dummy.setData(current.getData());
      if (current.getLeft() == null && current.getRight() == null) {
        return null;
      } else if (current.getLeft() == null) {
        return current.getRight();
      } else if (current.getRight() == null) {
        return current.getLeft();
      } else {
        BSTNode<T> temp = new BSTNode<T>(null);
        current.setRight(removeSmallestNode(current.getRight(), temp));
        current.setData(temp.getData());
        return current;
      }
    }
    if (data.compareTo(current.getData()) < 0) {
      current.setLeft(recursiveRemove(data, current.getLeft(), dummy));
    } else if (data.compareTo(current.getData()) > 0) {
      current.setRight(recursiveRemove(data, current.getRight(), dummy));
    }
    return current;
  }


  /**
   * Helper method for {@code recursiveRemove()}.
   * Removes the leftmost node in the subtree.
   * @param current the root node of the current subtree.
   * @param dummy the dummy node that stores the smallest data in the subtree.
   * @return the node itself or a node that will replace the original node.
   */
  private BSTNode<T> removeSmallestNode(BSTNode<T> current, BSTNode<T> dummy) {
    if (current.getLeft() == null) {
      dummy.setData(current.getData());
      return current.getRight();
    }
    current.setLeft(removeSmallestNode(current.getLeft(), dummy));
    return current;
  }

  @Override
  public T get(T data) {
    if (data == null) {
      throw new IllegalArgumentException("Please specify the data"
        + "you are looking for.");
    }
    return recursiveGet(data, root);
  }

  /**
   * Helper method for {@code get()}.
   * Searches for the given data recursively and returns the data if found.
   * @param data the data being searched for
   * @param node the node where the search begins.
   * @return the data stored in the tree that matches the data passed in.
   * @throws java.util.NoSuchElementException if the data is not found.
   */
  private T recursiveGet(T data, BSTNode<T> node) {
    if (node == null) {
      throw new java.util.NoSuchElementException("Data not found.");
    }
    if (node.getData().equals(data)) {
      return node.getData();
    }
    if (data.compareTo(node.getData()) < 0) {
      return recursiveGet(data, node.getLeft());
    } else {
      return recursiveGet(data, node.getRight());
    }
  }

  @Override
  public boolean contains(T data) {
    return recursiveCon(data, root);
  }

  /**
   * Helper method for {@code contains()}.
   * Searches for the given data recursively, starting from the given node.
   * @param data the data being searched for.
   * @param node the node where the search begins.
   * @return true if data is found, false if not found.
   */
  private boolean recursiveCon(T data, BSTNode<T> node) {
    if (node == null) return false;
    if (node.getData().equals(data)) return true;
    if (data.compareTo(node.getData()) < 0) {
      return recursiveCon(data, node.getLeft());
    } else {
      return recursiveCon(data, node.getRight());
    }
  }

  @Override
  public int size() {
    return size;
  }

  @Override
  public List<T> preorder() {
    ArrayList<T> result = new ArrayList<T>(size);
    preorderAdd(result, root);
    return result;
  }

  /**
   * Helper method for {@code preorder()}.
   * Adds data recursively to a list following the order:
   * parent --> left child --> right child.
   * @param list The list where data will be stored.
   * @param node the node currently being inspected.
   */
  private void preorderAdd(List<T> list, BSTNode<T> node) {
    if (node.getLeft() == null && node.getRight() == null) {
      list.add(node.getData());
      return;
    }
    list.add(node.getData());
    preorderAdd(list, node.getLeft());
    preorderAdd(list, node.getRight());
  }

  @Override
  public List<T> postorder() {
    ArrayList<T> result = new ArrayList<T>(size);
    postorderAdd(result, root);
    return result;
  }

  /**
   * Helper method for {@code postorder()}.
   * Adds data recursively to a list following the order:
   * left child --> right child --> parent.
   * @param list The list where data will be stored.
   * @param node the node currently being inspected.
   */
  private void postorderAdd(List<T> list, BSTNode<T> node) {
    if (node.getLeft() == null && node.getRight() == null) {
      list.add(node.getData());
      return;
    }
    postorderAdd(list, node.getLeft());
    postorderAdd(list, node.getRight());
    list.add(node.getData());
  }

  @Override
  public List<T> inorder() {
    ArrayList<T> result = new ArrayList<T>(size);
    inorderAdd(result, root);
    return result;
  }

  /**
   * Helper method for {@code inorder()}.
   * Adds data recursively to a list following the order:
   * left child --> parent --> right child.
   * @param list The list where data will be stored.
   * @param node the node currently being inspected.
   */
  private void inorderAdd(List<T> list, BSTNode<T> node) {
    if (node.getLeft() == null && node.getRight() == null) {
      list.add(node.getData());
      return;
    }
    inorderAdd(list, node.getLeft());
    list.add(node.getData());
    inorderAdd(list, node.getRight());
  }

  @Override
  public List<T> levelorder() {
    ArrayList<T> result = new ArrayList<T>(size);
    LinkedList<BSTNode<T>> queue = new LinkedList<BSTNode<T>>();
    queue.addLast(root);
    while (queue.size() > 0) {
      if (queue.get(0) != null) {
        result.add(queue.get(0).getData());
        queue.addLast(queue.get(0).getLeft());
        queue.addLast(queue.get(0).getRight());
      }
      queue.removeFirst();
    }
    return result;
  }

  @Override
  public void clear() {
    root = null;
    size = 0;
  }

  @Override
  public int height() {
    if (root == null) return -1;
    return recursiveHeight(root);
  }

  /**
   * Helper method for {@code height()}.
   * Calculates the height of the given node recursively.
   * @param node The node currently being inspected.
   * @return the height of the current node.
   */
  private int recursiveHeight(BSTNode<T> node) {
    if (node.getLeft() == null && node.getRight() == null) return 0;
    return Math.max(recursiveHeight(
      node.getLeft()),
      recursiveHeight(node.getRight()) + 1
    );
  }

  @Override
  public BSTNode<T> getRoot() {
    return root;
  }
}
