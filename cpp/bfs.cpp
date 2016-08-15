#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
#include <queue>
using namespace std;

struct Node {
    int n = 0;
    std::vector<Node *> children;
};

struct Explored {
    Explored(struct Node *n, int distance) :
        n(n),
        distance(distance)
    {
    }
    
    struct Node *n;
    int distance;
};

int bfsDistanceTo(Explored node, int target_node_index, int n_nodes) {
    int visited[1000];
    std::queue<Explored> q;
    
    for (size_t i = 0; i < n_nodes; ++i)
        visited[i] = 9999;
    
    q.push(node);
    
    int best_distance = std::numeric_limits<int>::max();
    bool found_solution = false;
    
    while (!q.empty()) {
        /* Keep expanding this node's children on a breadth-first basis */
        node = q.front();
        q.pop();
        
        /* If this is the target, make a note of how far away it is,
         * but keep exploring other solutions */
        if (node.n->n == target_node_index &&
            node.distance < best_distance) {
            found_solution = true;
            best_distance = node.distance;
        }
        
        for (auto &child : node.n->children) {
            int distance = node.distance + 6;
            if (visited[child->n] > distance) {
                visited[child->n] = distance;
                q.push(Explored(child, node.distance + 6));
            }
        }
    }
    
    if (found_solution) {
        return best_distance;
    }
    
    return -1;
}


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n_test_cases;
    scanf("%i", &n_test_cases);
    
    int test_index = 0;
    for (; test_index < n_test_cases; ++test_index) {
        int n_nodes = 0;
        int n_edges = 0;
        scanf("%i %i\n", &n_nodes, &n_edges);

        Node node_list[1000];
        
        int edge_index = 0;
        int node_index = 0;
        
        for (node_index = 0; node_index < n_nodes; ++node_index) {
            node_list[node_index].n = node_index;
        }

        for (; edge_index < n_edges; ++edge_index) {
            int left, right;
            scanf("%i %i\n", &left, &right);
            
            node_list[left - 1].children.push_back(&node_list[right - 1]);
            node_list[right - 1].children.push_back(&node_list[left - 1]);
        }
        
        int start = 0;
        scanf("%i\n", &start);



        int distances[1000];
        memset(distances, 0, sizeof(int) * n_nodes);
        int target_node_index = 0;
        for (; target_node_index < n_nodes; ++target_node_index) {
            if (target_node_index == start - 1)
                continue;
            
            printf("%i ", bfsDistanceTo(Explored(&node_list[start - 1], 0),
                                        target_node_index,
                                        n_nodes));
        }
        
        printf("\n");
    }
    
    printf("\n");
    
    return 0;
}
