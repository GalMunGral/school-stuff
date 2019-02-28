import java.util.List;
import java.util.Set;
import java.util.HashSet;
import java.util.ArrayList;

/**
 * Your implementation of HashMap.
 * 
 * @author Wenqi He
 * @version 1.0
 */
public class HashMap<K, V> implements HashMapInterface<K, V> {

  private MapEntry<K, V>[] table;
  private int size;

  public HashMap() {
    this(INITIAL_CAPACITY);
  }

  public HashMap(int initialCapacity) {
    table = new MapEntry[initialCapacity];
    size = 0;
  }

  @Override
  public V put(K key, V value) {
    if (key == null || value == null) {
      throw new IllegalArgumentException("invalid Data.");
    }
    if (size + 1 > table.length * MAX_LOAD_FACTOR) {
      resizeBackingTable(2 * table.length + 1);
    }
    int hash = Math.abs(key.hashCode()) % table.length;
    int firstRemoved = -1;
    for (int i = 0; i <= table.length; i++) {
      int cur = (hash + i * i) % table.length;
      if (table[cur] == null) {
        size++;
        if (firstRemoved == -1) {
          table[cur] = new MapEntry(key, value);
          return null;
        } else {
          table[firstRemoved] = new MapEntry(key, value);
          return null;
        }
      } else if (firstRemoved == -1 && table[cur].isRemoved()) {
        firstRemoved = cur;
      } else if (table[cur].getKey().equals(key)) {
        V oldValue = table[cur].getValue();
        table[cur].setValue(value);
        return oldValue;
      }
    }
    resizeBackingTable(2 * table.length + 1);
    return put(key, value);
  }

  @Override
  public V remove(K key) {
    return access(key, true);
  }

  @Override
  public V get(K key) {
    return access(key, false);
  }

  @Override
  public boolean containsKey(K key) {
    try {
      access(key, false);
      return true;
    } catch (java.util.NoSuchElementException e) {
      return false;
    }
  }


  /**
   * Helper method for {@code remove}, {@code get} and {@code containsKey}.
   * Check if given key exists, and return the value associated with the key.
   * @param key the key to be searched.
   * @param remove whether or not to remove the entry.
   * @return the value associated with the key.
   * @throws java.util.NoSuchElementException if the key does not exist.
   */
  private V access(K key, boolean remove) {
    if (key == null) {
      throw new IllegalArgumentException("Please specify a key to access");
    }
    int hash = Math.abs(key.hashCode()) % table.length;
    for (int i = 0; i <= table.length; i++) {
      int cur = (hash + i * i) % table.length;
      if (
        table[cur] != null
        && table[cur].getKey().equals(key)
        && !table[cur].isRemoved()
      ) {
        if (remove) {
          table[cur].setRemoved(true);
          size--;
        }
        return table[cur].getValue();
      }
    }
    throw new java.util.NoSuchElementException("Entry not found.");
  }

  @Override
  public void clear() {
    table = new MapEntry[INITIAL_CAPACITY];
    size = 0;
  }

  @Override
  public int size() {
    return size;
  }

  @Override
  public Set<K> keySet() {
    HashSet<K> keys = new HashSet<K>(size);
    for (int i = 0; i < table.length; i++) {
      if (table[i] != null && !table[i].isRemoved()) {
        keys.add(table[i].getKey());
      }
    }
    return keys;
  }

  @Override
  public List<V> values() {
    ArrayList<V> values = new ArrayList<V>(size);
    for (int i = 0; i < table.length; i++) {
      if (table[i] != null && !table[i].isRemoved()) {
        values.add(table[i].getValue());
      }
    }
    return values;
  }

  @Override
  public void resizeBackingTable(int length) {
    if (length <= 0 || length < size) {
      throw new IllegalArgumentException("New length must be longer.");
    }
    MapEntry<K, V>[] tempTable = table;
    table = new MapEntry[2 * table.length + 1];
    for (int i = 0; i < tempTable.length; i++) {
      if (tempTable[i] != null && !tempTable[i].isRemoved()) {
        K key = tempTable[i].getKey();
        V value = tempTable[i].getValue();
        recursivePut(key, value);
      }
    }
  }

  /**
   * Helper method for {@code resizeBackingTable}. Essentially a simplified
   * version of {@code put}.
   * @param key the key of the new entry
   * @param value the value of the new entry
   */
  private void recursivePut(K key, V value) {
    int hash = Math.abs(key.hashCode()) % table.length;
    int j = 0;
    int cur = (hash + j * j) % table.length;
    while (j <= table.length && table[cur] != null) {
      j++;
      cur = (hash + j * j) % table.length;
    }
    if (table[cur] == null) {
      table[cur] = new MapEntry(key, value);
    } else {
      resizeBackingTable(2 * table.length + 1);
      recursivePut(key, value);
    }
  }


  @Override
  public MapEntry<K, V>[] getTable() {
    return table;
  }
}
