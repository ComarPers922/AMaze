#ifndef RANDOMQUEUE_H
#define RANDOMQUEUE_H

#include <QLinkedList>
#include <QtGlobal>
#include <ctime>

template<class T>
class RandomQueue
{
private:
    QLinkedList<T> queue;
public:
    RandomQueue()
    {
      qsrand(time(NULL));
    }

    void add(T data)
    {
        if(qrand() % 100 < 50)
        {
            queue.push_back(data);
        }
        else
        {
            queue.push_front(data);
        }
    }

    T remove()
    {
        if(qrand() % 100 < 50)
        {
            T data = queue.front();
            queue.pop_front();
            return data;
        }
        else
        {
            T data = queue.back();
            queue.pop_back();
            return data;
        }
    }

    int size()
    {
      return queue.size();
    }

    bool isEmpty()
    {
        return size() == 0;
    }
};

#endif // RANDOMQUEUE_H
