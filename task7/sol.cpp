//
// время O((n+q) * 10 * alpha(n))
// память O(10n)
//
// Для каждого t рассмотрим граф только из ребер веса не больше t и обозначим число его компонент через C_t.
// Вес минимального остовного дерева равен
// n - 10 + sum_{t=1}^{9} C_t
//
// При добавлении ребра веса w оно появляется во всех таких графах с t >= w
// Если в DSU для порога t ребро объединяет две компоненты - C_t уменьшается на один, вес MST также уменьшается
//

#include <iostream>
#include <vector>

using namespace std;

class DSU
{
  private:
    std::vector<int> parent, componentSize;

  public:
    DSU(int n)
    {
        parent.resize(n);
        componentSize.resize(n, 1);

        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int FindRoot(int vertex)
    {
        int root = vertex;

        while (parent[root] != root)
            root = parent[root];

        while (parent[vertex] != vertex)
        {
            int nextVertex = parent[vertex];
            parent[vertex] = root;
            vertex = nextVertex;
        }

        return root;
    }

    bool Unite(int first, int second)
    {
        first = FindRoot(first);
        second = FindRoot(second);

        if (first == second)
            return false;

        if (componentSize[first] < componentSize[second])
        {
            int temporary = first;
            first = second;
            second = temporary;
        }

        parent[second] = first;
        componentSize[first] += componentSize[second];

        return true;
    }
};

int main()
{
    std::ios::sync_with_stdio(false); // ускорение ввода, вывода
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<DSU> structures;
    structures.reserve(10);

    for (int weight = 0; weight <= 9; ++weight)
        structures.emplace_back(n);

    int64_t mstWeight = 0;

    // исходные ребра образуют дерево
    // поэтому их сумма равна начальному весу MST
    for (int i = 0; i < n - 1; ++i)
    {
        int first, second, weight;
        std::cin >> first >> second >> weight;

        --first;
        --second;

        mstWeight += weight;

        for (int limit = weight; limit <= 9; ++limit)
            structures[limit].Unite(first, second);
    }

    for (int query = 0; query < q; ++query)
    {
        int first, second, weight;
        std::cin >> first >> second >> weight;

        --first;
        --second;

        for (int limit = weight; limit <= 9; ++limit)
            if (structures[limit].Unite(first, second))
                --mstWeight;

        std::cout << mstWeight << '\n';
    }

    return 0;
}
