import java.util.Collection;
import java.util.List;
import java.util.ArrayList;
import java.util.LinkedList;
/**
 * Your implementation of an AVL Tree.
 *
 * @author Wenqi He
 * @version 1.0
 */
public class AVL<T extends Comparable<? super T>> implements AVLInterface<T> {
  
  private AVLNode<T> root;
  private int size;

  public AVL() {}

  public AVL(Collection<T> data) {
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

  /**
   * Helper method for {@code recursiveAdd}, {@code recursiveRemove}.
   * Updates {@code height} and {@code balanceFactor} of the node
   * @param node the node being updated.
   */
  private void updateNode(AVLNode<T> node) {
    int leftHeight;
    int rightHeight;
    if (node.getLeft() == null) {
      leftHeight = -1;
    } else {
      leftHeight = node.getLeft().getHeight();
    }
    if (node.getRight() == null) {
      rightHeight = -1;
    } else {
      rightHeight = node.getRight().getHeight();
    }
    node.setHeight(Math.max(leftHeight, rightHeight) + 1);
    node.setBalanceFactor(leftHeight - rightHeight);
  }

  /**
   * Helper method for {@code balance}. Perform a left rotation.
   * @param node the node around which a left rotation is performed.
   * @return the new root of the subtree.
   */
  private AVLNode<T> leftRotation(AVLNode<T> node) {
    AVLNode<T> transfer = node.getRight().getLeft();
    node.getRight().setLeft(node);
    AVLNode<T> newRoot = node.getRight();
    node.setRight(transfer);
    updateNode(node);
    updateNode(newRoot);
    return newRoot;
  }

  /**
   * Helper method for {@code balance}. Perform a right rotation.
   * @param node the node around which a right rotation is performed.
   * @return the new root of the subtree.
   */
  private AVLNode<T> rightRotation(AVLNode<T> node) {
    AVLNode<T> transfer = node.getLeft().getRight();
    node.getLeft().setRight(node);
    AVLNode<T> newRoot = node.getLeft();
    node.setLeft(transfer);
    updateNode(node);
    updateNode(newRoot);
    return newRoot;
  }

  /**
   * Helper method for {@code recursiveAdd} and {@code recursiveRemove}
   * perform left or right rotation based on the updated balance factor.
   * @param node the old root of the subtree.
   * @return the new root of the subtree.
   */
  private AVLNode<T> balance(AVLNode<T> node) {
    if (node.getBalanceFactor() == -2) {
      if (node.getRight().getBalanceFactor() == -1) {
        return leftRotation(node);
      } else if (node.getRight().getBalanceFactor() == 1) {
        node.setRight(rightRotation(node.getRight()));
        return leftRotation(node);
      }
    } else if (node.getBalanceFactor() == 2) {
      if (node.getLeft().getBalanceFactor() == 1) {
        return rightRotation(node);
      } else if (node.getLeft().getBalanceFactor() == -1) {
        node.setLeft(leftRotation(node.getLeft()));
        return rightRotation(node);
      }
    }
    return node;
  }

  @Override
  public void add(T data) {
    if (data == null) {
      throw new IllegalArgumentException("Please specify something to add.");
    }
    root = recursiveAdd(data, root);
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
  private AVLNode<T> recursiveAdd(T data, AVLNode<T> node) {
    if (node == null) {
      size++;
      return new AVLNode<T>(data);
    }
    if (data.compareTo(node.getData()) < 0) {
      node.setLeft(recursiveAdd(data, node.getLeft()));
    } else if (data.compareTo(node.getData()) > 0) {
      node.setRight(recursiveAdd(data, node.getRight()));
    }
    updateNode(node);
    return balance(node);
  }

  @Override
  public T remove(T data) {
    if (data == null) {
      throw new IllegalArgumentException("Please specify something to remove.");
    }
    AVLNode<T> dummyNode = new AVLNode<T>(null);
    root = recursiveRemove(data, root, dummyNode);
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
  private AVLNode<T> recursiveRemove(
    T data,
    AVLNode<T> current,
    AVLNode<T> dummy
  ) {
    if (current == null) {
      throw new java.util.NoSuchElementException("Data not found.");
    }
    if (current.getData().equals(data)) {
      size--;
      dummy.setData(current.getData());
      if (current.getLeft() == null && current.getRight() == null) {
        return null;
      } else if (current.getLeft() == null) {
        return current.getRight();
      } else if (current.getRight() == null) {
        return current.getLeft();
      } else {
        AVLNode<T> temp = new AVLNode<T>(null);
        current.setRight(removeSmallestNode(current.getRight(), temp));
        current.setData(temp.getData());
        updateNode(current);
        current = balance(current);
        return current;
      }
    }
    if (data.compareTo(current.getData()) < 0) {
      current.setLeft(recursiveRemove(data, current.getLeft(), dummy));
    } else if (data.compareTo(current.getData()) > 0) {
      current.setRight(recursiveRemove(data, current.getRight(), dummy));
    }
    updateNode(current);
    return balance(current);
  }

  /**
   * Helper method for {@code recursiveRemove()}.
   * Removes the leftmost node in the subtree.
   * @param current the root node of the current subtree.
   * @param dummy the dummy node that stores the smallest data in the subtree.
   * @return the node itself or a node that will replace the original node.
   */
  private AVLNode<T> removeSmallestNode(AVLNode<T> current, AVLNode<T> dummy) {
    if (current.getLeft() == null) {
      dummy.setData(current.getData());
      return current.getRight();
    }
    current.setLeft(removeSmallestNode(current.getLeft(), dummy));
    updateNode(current);
    return balance(current);
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
  private T recursiveGet(T data, AVLNode<T> node) {
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
    if (data == null) {
      throw new IllegalArgumentException("Please specify the data you"
        + "are looking for");
    }
    return recursiveCon(data, root);
  }

  /**
   * Helper method for {@code contains()}.
   * Searches for the given data recursively, starting from the given node.
   * @param data the data being searched for.
   * @param node the node where the search begins.
   * @return true if data is found, false if not found.
   */
  private boolean recursiveCon(T data, AVLNode<T> node) {
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
  private void preorderAdd(List<T> list, AVLNode<T> node) {
    list.add(node.getData());
    if (node.getLeft() != null) {
      preorderAdd(list, node.getLeft());
    }
    if (node.getRight() != null) {
      preorderAdd(list, node.getRight());
    }
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
  private void postorderAdd(List<T> list, AVLNode<T> node) {
    if (node.getLeft() != null) {
      postorderAdd(list, node.getLeft());
    }
    if (node.getRight() != null) {
      postorderAdd(list, node.getRight());
    }
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
  private void inorderAdd(List<T> list, AVLNode<T> node) {
    if (node.getLeft() != null) {
      inorderAdd(list, node.getLeft());
    }
    list.add(node.getData());
    if (node.getRight() != null) {
      inorderAdd(list, node.getRight());
    }
  }

  @Override
  public List<T> levelorder() {
    ArrayList<T> result = new ArrayList<T>(size);
    LinkedList<AVLNode<T>> queue = new LinkedList<>();
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
    if (root == null) {
      return -1;
    } else {
      int leftHeight;
      if (root.getLeft() == null) {
        leftHeight = -1;
      } else {
        leftHeight = root.getLeft().getHeight();
      }
      int rightHeight;
      if (root.getRight() == null) {
        rightHeight = -1;
      } else {
        rightHeight = root.getRight().getHeight();
      }
      return Math.max(leftHeight, rightHeight) + 1;
    }
  }

  @Override
  public AVLNode<T> getRoot() {
    return root;
  }
}
