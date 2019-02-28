import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Set;

/**
 * Your implementations of various graph algorithms.
 *
 * @author Wenqi He
 * @version 1.0
 */
public class GraphAlgorithms {

  public static <T> List<Vertex<T>> breadthFirstSearch(
    Vertex<T> start,
    Graph<T> graph
  ) {
    if (start == null || graph == null) {
      throw new IllegalArgumentException("You must provide valid input.");
    }
    if (!graph.getAdjacencyList().containsKey(start)) {
      throw new IllegalArgumentException("Given vertex is not in the graph.");
    }
    List<Vertex<T>> visited = new ArrayList<>();
    Set<Vertex<T>> explored = new HashSet<>();
    explored.add(start);
    Queue<Vertex<T>> queue = new LinkedList<>();
    queue.add(start);
    while (!queue.isEmpty()) {
      Vertex<T> cur = queue.remove();
      visited.add(cur);
      List<VertexDistancePair<T>> neighbors = graph.getAdjacencyList().get(cur);
      for (VertexDistancePair<T> p : neighbors) {
        Vertex<T> curNeighbor = p.getVertex();
        if (!explored.contains(curNeighbor)) {
          explored.add(curNeighbor);
          queue.add(curNeighbor);
        }
      }
    }
    return visited;
  }

  public static <T> List<Vertex<T>> depthFirstSearch(
    Vertex<T> start,
    Graph<T> graph
  ) {
    if (start == null || graph == null) {
      throw new IllegalArgumentException("You must provide valid input.");
    }
    if (!graph.getAdjacencyList().containsKey(start)) {
      throw new IllegalArgumentException("Given vertex is not in the graph.");
    }
    List<Vertex<T>> visited = new ArrayList<>();
    Set<Vertex<T>> visitedSet = new HashSet<>();
    depthFirstSearch(start, graph, visited, visitedSet);
    return visited;
  }

  /**
   * Helper method for {@code depthFirstSearch}. Search the graph recursively.
   * @param cur the Vertex you are visiting
   * @param graph the Graph you are traversing
   * @param visited the list that contains all visited vertices
   * @param visitedSet the set that contains all visited vertices
   * @param <T> the data type representing the vertices in the graph.
   */
  private static <T> void depthFirstSearch(
    Vertex<T> cur,
    Graph<T> graph，
    List<Vertex<T>> visited,
    Set<Vertex<T>> visitedSet
  ) {
    visited.add(cur);
    visitedSet.add(cur);
    List<VertexDistancePair<T>> neighbors = graph.getAdjacencyList().get(cur);
    for (VertexDistancePair<T> p : neighbors) {
      Vertex<T> curNeighbor = p.getVertex();
      if (!visitedSet.contains(curNeighbor)) {
        depthFirstSearch(curNeighbor, graph, visited, visitedSet);
      }
    }
  }

  public static <T> Map<Vertex<T>, Integer> dijkstras(
    Vertex<T> start,
    Graph<T> graph
  ) {
    if (start == null || graph == null) {
      throw new IllegalArgumentException("You must provide valid input.");
    }
    if (!graph.getAdjacencyList().containsKey(start)) {
      throw new IllegalArgumentException("Given vertex is not in the graph.");
    }
    Map<Vertex<T>, Integer> shortestDist = new HashMap<>();
    PriorityQueue<VertexDistancePair<T>> queue = new PriorityQueue<>();
    for (Vertex<T> v : graph.getAdjacencyList().keySet()) {
      shortestDist.put(v, Integer.MAX_VALUE);
    }
    shortestDist.put(start, 0);
    queue.add(new VertexDistancePair<>(start, 0));
    while (!queue.isEmpty()) {
      Vertex<T> min = queue.poll().getVertex();
      List<VertexDistancePair<T>> neighbors = graph.getAdjacencyList().get(min);
      for (VertexDistancePair<T> p : neighbors) {
        Vertex<T> v = p.getVertex();
        int dist = p.getDistance();
        int newDist = shortestDist.get(min) + dist;
        if (newDist < shortestDist.get(v)) {
          queue.remove(new VertexDistancePair<>(v, shortestDist.get(v)));
          queue.add(new VertexDistancePair<>(v, newDist));
          shortestDist.put(v, newDist);
        }
      }
    }
    return shortestDist;
  }

  public static <T> Set<Edge<T>> prims(Vertex<T> start, Graph<T> graph) {
    if (start == null || graph == null) {
      throw new IllegalArgumentException("You must provide valid input.");
    }
    if (!graph.getAdjacencyList().containsKey(start)) {
      throw new IllegalArgumentException("Given vertex is not in the graph.");
    }
    int size = graph.getAdjacencyList().keySet().size();
    Set<Edge<T>> mst = new HashSet<>();
    Set<Vertex<T>> mstNodes = new HashSet<>();
    PriorityQueue<Edge<T>> edgeQueue = new PriorityQueue<>();
    Edge<T> newEdge;
    Vertex<T> newVertex;
    mstNodes.add(start);
    List<VertexDistancePair<T>> neighbors = graph.getAdjacencyList().get(start);
    for (VertexDistancePair<T> p : neighbors) {
      edgeQueue.add(new Edge<>(start, p.getVertex(), p.getDistance(), false));
    }
    while (mstNodes.size() < size) {
      if (edgeQueue.isEmpty()) return null;
      newEdge = edgeQueue.poll();
      if (
        !mstNodes.contains(newEdge.getU())
        || !mstNodes.contains(newEdge.getV())
      ) {
        if (!mstNodes.contains((newEdge.getU()))) {
          newVertex = newEdge.getU();
        } else {
          newVertex = newEdge.getV();
        }
        mst.add(newEdge);
        mstNodes.add(newVertex);
        neighbors = graph.getAdjacencyList().get(newVertex);
        for (VertexDistancePair<T> p : neighbors) {
          edgeQueue.add(new Edge<>(
            newVertex,
            p.getVertex(),
            p.getDistance(),
            false
          ));
        }
      }
    }
    return mst;
  }
}


