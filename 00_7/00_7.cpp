#include <iostream>
#include <vector>
#include "\O-O-P\boolMatrix\boolMatrix.h"
#include "\O-O-P\List\List.h"

bool searchInVector(std::vector<int>& array, int const value)
{
    for (int i = 0; i < array.size(); i++)
        if (array[i] == value)
            return true;
    return false;
}

bool addEdge(BoolMatrix& bm, int const a, int const b)
{
    if (a == 0)
        return false;
    bm.setComponent(a - 1, b - 1, true);
    return true;
}

bool deleteEdge(BoolMatrix& bm, std::vector<int>& array)
{
    BoolVector v0(bm.columnCount(), 0);
    BoolVector v1(bm.columnCount(), 0);
    BoolVector v2(bm.columnCount(), 0);

    v1 = bm.disjunctionAllLines();
    v0 = ~v1;
    for (int i = 0; i < v0.length(); i++)
        if (v0[i] == 1)
        {
            array.push_back(i + 1);
            bm[i].setValue(0);
        }

    while (v0.weight() != v0.length())
    {
        v1 = bm.disjunctionAllLines();
        v2 = ~v1 & ~v0;
        for (int i = 0; i < v2.length(); i++)
            if (v2[i] == 1 && !searchInVector(array, i + 1))
            {
                v0[i] = true;
                array.push_back(i + 1);
            }
        if (v2.weight() == 0)
            return false;
        for (int i = 0; i < bm.columnCount(); i++)
            if (bm.weightColumn(i) == 0)
            {
                bm[i].setValue(0);
            }
    }
    return true;
}


class Leader
{
public:
    int key;
    int count = 0;
    List<Leader*> trLd;

    Leader();
    Leader(int key);

    bool operator==(const Leader& ld) const;
};

Leader::Leader()
{}

Leader::Leader(int keyA)
    :key(keyA)
    ,trLd()
{}

void addEdge(List<Leader>& ld, int const a, Leader*& ptrA)
{
    bool search = 0;
    int j = 0;
    for (int i = 0; i < ld.size(); i++)
    {
        if (ld[i].key == a)
        {
            j = i;
            search = true;
            break;
        }
    }
    if (search)
        ptrA = &ld[j];
    else
    {
        Leader aLead(a);
        ld.addToHead(aLead);
        ptrA = &ld[j];
    }
}

bool addEdge(List<Leader>& ld, int const a, int const b)
{
    Leader* ptrA = nullptr;
    Leader* ptrB = nullptr;

    if (a == 0)
        return false;

    addEdge(ld, a, ptrA);
    addEdge(ld, b, ptrB);

    ptrB->count++;
    ptrA->trLd.addToHead(ptrB);

    return true;
}

void transferLd(List<Leader>& ld, List<Leader>& ldNew)
{
    for (int i = 0; i < ld.size(); i++)
        if (ld[i].count == 0)
        {
            ldNew.addToHead(ld[i]);
            ld.deleteElement(ld[i]);
            i--;
        }
}

bool deleteEdge(List<Leader>& ld, std::vector<int>& array)
{
    List<Leader> ldNew;
    transferLd(ld, ldNew);

    while (!ldNew.isEmpty())
    {
        Leader p = ldNew[0];
        ldNew.deleteFromHead();

        for(List<Leader*>::iterator runner = p.trLd.begin(); runner != p.trLd.end(); runner++)
            (*runner)->count--;

        transferLd(ld, ldNew);
        array.push_back(p.key);
    }

    if (!ld.isEmpty())
        return false;
    return true;
}

bool topologicalSortForBM(BoolMatrix& bm, std::vector<int>& array)
{
    int a = 1, b = 2, c = 3, d = 4, f = 5, e = 6, j = 7;
    addEdge(bm, b, a);
    addEdge(bm, d, f);
    addEdge(bm, f, a);
    addEdge(bm, f, c);
    addEdge(bm, e, b);
    addEdge(bm, e, c);
    addEdge(bm, e, f);
    addEdge(bm, j, a);

    if (deleteEdge(bm, array))
        return true;
    return false;
}

bool topologicalSortForList(List<Leader>& ld, std::vector<int>& array)
{
    int a = 1, b = 2, c = 3, d = 4, f = 5, e = 6, j = 7;

    addEdge(ld, b, a);
    addEdge(ld, d, f);
    addEdge(ld, f, a);
    addEdge(ld, f, c);
    addEdge(ld, e, b);
    addEdge(ld, e, c);
    addEdge(ld, e, f);
    addEdge(ld, j, a);


    if (deleteEdge(ld, array))
        return true;
    return false;

}


int main()
{
    List<Leader> ld;
    BoolMatrix bm(7, 7, false);
    std::vector<int> array, array1;

    if (topologicalSortForBM(bm,array))
    {
        std::cout << "Topological sorting via BM:   ";
        for (int i = 0; i < array.size(); i++)
            std::cout << array[i] << " ";
    }
    else
        std::cout << "BM have cycle";

    if (topologicalSortForList(ld, array1))
    {
        std::cout << "\nTopological sorting via List: ";
        for (int i = 0; i < array1.size(); i++)
            std::cout << array1[i] << " ";
    }
    else 
        std::cout << "\nList have cycle";
}




bool Leader::operator==(const Leader& ld) const
{
    return (key == ld.key);
}
