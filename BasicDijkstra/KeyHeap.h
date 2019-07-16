#pragma once
#pragma once
#include <vector>
template <typename KeyType, typename ValueType, typename comparer>
class KeyHeap
{
private:
    vector<unsigned> pos;
    vector<pair<KeyType, ValueType> > m_data; // m_data[0]×öÉÚ±ø
    unsigned elem_num;
    void up(int p)
    {
        pair<KeyType, ValueType> x = m_data[p];
        for (; p > 1 && comparer()(x.second, m_data[p / 2].second); p = p / 2)
        {
            m_data[p] = m_data[p / 2];
            pos[m_data[p].first] = p; //pos.insert(m_data[p].first, p);
        }
        m_data[p] = x;
        pos[x.first] = p; // pos.insert(x.first, p);
    }
    void down(int p)
    {
        pair<KeyType, ValueType> tmp;

        for (int i = p; p < elem_num; p = i)
        {
            if (p * 2 < elem_num
                && comparer()(m_data[p * 2].second, m_data[p].second))
                i = p * 2;
            if (p * 2 + 1 < elem_num
                && comparer()(m_data[p * 2 + 1].second, m_data[i].second))
                i = p * 2 + 1;
            if (i == p) break;
            tmp = m_data[p];
            m_data[p] = m_data[i];
            pos[m_data[p].first] = p; //pos.insert(m_data[p].first, p);
            m_data[i] = tmp;
        }
        pos[m_data[p].first] = p;//pos.insert(m_data[p].first, p);
    }

public:
    KeyHeap()
    {
        elem_num = 1;
    }
    KeyHeap(int n) :pos(n + 1), m_data(n + 1)
    {
        memset(pos.data(), 0xFF, sizeof(KeyType) * pos.size());
        elem_num = 1;
    }

    void init(int n)
    {
        pos.resize(n + 1);
        m_data.resize(n + 1);
        memset(pos.data(), 0xFF, sizeof(unsigned) * pos.size());
        elem_num = 1;
    }

    KeyType head()
    {
        return m_data[1].key;
    }

    void clear()
    {
        memset(pos.data(), 0xFF, sizeof(KeyType) * pos.size());
        elem_num = 1;
    }

    void update(KeyType  x, ValueType y)
    {
        if (pos[x] == 0xFFFFFFFF)
        {
            m_data[elem_num] = { x, y };
            pos[x] = elem_num;
            elem_num++;
            up(elem_num - 1);
        }
        else
        {
            if (comparer()(y, m_data[pos[x]].second))
            {
                m_data[pos[x]].second = y;
                up(pos[x]);
            }
            else
            {
                m_data[pos[x]].second = y;
                down(pos[x]);
            }
        }
    }
    KeyType pop()
    {
        KeyType tmp = m_data[1].first;
        pos[tmp] = 0xFFFFFFFF;
        if (elem_num == 2)
        {
            elem_num--;
            return tmp;
        }
        m_data[1] = m_data[elem_num - 1];
        elem_num--;
        down(1);
        return tmp;
    }
    bool empty()
    {
        return (elem_num == 1);
    }
};