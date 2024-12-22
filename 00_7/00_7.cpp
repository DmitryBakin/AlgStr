﻿#include <iostream>
#include <vector>
#include "\O-O-P\boolMatrix\boolMatrix.h"
#include "\O-O-P\List\List.h"

class Trailer;
class Leader
{
public:
    int key;
    int count = 0;
    Trailer* tr;

    bool operator==(const Leader& ld);
};

class Trailer
{
public:
    Leader *ld;
    Trailer *nx;
};

bool searchInVector(std::vector<int>& array, int const value)
{
    for (int i = 0; i < array.size(); i++)
        if (array[i] == value)
            return true;
    return false;
}

bool addEdge(BoolMatrix& bm, int const a, int const b)
{
    bm.setComponent(a - 1, b - 1, true);
    return true;
}

void deleteEdge(BoolMatrix& bm, std::vector<int>& array)
{
    while (array.size() != bm.columnCount())
    {
        for (int i = 0; i < bm.columnCount(); i++)
            if (bm.weightColumn(i) == 0 && !searchInVector(array, i + 1))
            {
                array.push_back(i + 1);
                bm.setComponents(i, 0, bm.columnCount(), 0);
            }
    }
}

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
        Leader aLead;
        aLead.key = a;
        aLead.count = 0;
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
    Trailer* elemTr = new Trailer;
    elemTr->ld = ptrB;
    elemTr->nx = ptrA->tr;
    ptrA->tr = elemTr;

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

void deleteEdge(List<Leader>& ld, std::vector<int>& array)
{
    List<Leader> ldNew;
    transferLd(ld, ldNew);
    
    while (!ldNew.isEmpty())
    {
        Leader p = ldNew[0];
        Trailer* T = p.tr;
        ldNew.deleteFromHead();
        while(T != nullptr)
        {
            T->ld->count = T->ld->count - 1;
            if (T->nx != nullptr)
                T = T->nx;
            else
                break;
        }
        transferLd(ld, ldNew);
        delete T;
        array.push_back(p.key);
    }
}

int main()
{
    List<Leader> ld;
    BoolMatrix bm(7, 7, false);
    std::vector<int> array, array1;
    int a = 1, b = 2, c = 3, d = 4, f = 5,e = 6, j= 7;
    addEdge(ld, b, a);
    addEdge(ld, d, f);
    addEdge(ld, f, a);
    addEdge(ld, f, c);
    addEdge(ld, e, b);
    addEdge(ld, e, c);
    addEdge(ld, e, f);
    addEdge(ld, j, a);


    addEdge(bm, b, a);
    addEdge(bm, d, f);
    addEdge(bm, f, a);
    addEdge(bm, f, c);
    addEdge(bm, e, b);
    addEdge(bm, e, c);
    addEdge(bm, e, f);
    addEdge(bm, j, a);

    deleteEdge(bm, array);
    deleteEdge(ld, array1);

    std::cout << "\nTopological sorting via BM:   ";
    for (int i = 0; i < array.size(); i++)
        std::cout << array[i] << " ";
    std::cout << "\nTopological sorting via List: ";
    for (int i = 0; i < array1.size(); i++)
        std::cout << array1[i] << " ";
}




bool Leader::operator==(const Leader& ld)
{
    return (key == ld.key);
}
