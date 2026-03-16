G = {
    1: [2,3],
    2: [1,4],
    3: [1],
    4: [2]
}

from collections import deque

def BFS(G, s):
    n = len(G)
    No = [0] * (n + 1 ) # Assuming vertices are numbered from 1 to n
    nr = 1

    Q = deque()

    No[s] = nr
    Q.append(s)

    while Q:
        v = Q.popleft()

        for u in G[v]:
            if No[u] == 0:
                nr += 1
                No[u] = nr
                Q.append(u)

    return No

def DFS(G, s):

    n = len(G)
    No = [0] * (n + 1)
    nr = 1

    def Visit(u):
        nonlocal nr

        for v in G[u]:
            if No[v] == 0:
                nr += 1
                No[v] = nr
                Visit(v)

    No[s] = nr
    Visit(s)

    return No


#Graf jest niespójny, gdy nie da się dojść z jednego wierzchołka do wszystkich pozostałych.

def is_consistent(G,s):
    No = BFS(G, s)
    if 0 in No[1:]: # Ignoring the 0th index as vertices are numbered from 1
        return False
    return True

#cykl w grafie to ścieżka, która zaczyna się i kończy w tym samym wierzchołku, a wszystkie krawędzie są różne.

def DFS_cycle(G, s):

    n = len(G)
    visited = [False]*(n+1)
    parent = [-1]*(n+1)
    cycle = False

    def visit(u):
        nonlocal cycle
        visited[u] = True

        for v in G[u]:

            if not visited[v]:
                parent[v] = u
                visit(v)

            elif parent[u] != v:
                cycle = True

    visit(s)

    if cycle:
        print("Graf zawiera cykl")
    else:
        print("Graf jest acykliczny")