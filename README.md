# CPP_single
本人的一些算法题

 void clear()
    {
        NODE *p = head;
        NODE *q = p->next;
        while (len > 1)
        {
            delete p;
            p = q;
            q = q->next;
        }
        delete p;
    }
void clear()
    {
        NODE *p = head;
        while (p->next != head)
        {
            NODE *temp = p->next;
            p->next = temp->next;
            delete temp;
        }
        delete p;
        head = nullptr;
    }
12
1 0 4
1 0 8
1 0 57
1 3 41
1 2 5
1 6 21
4 0
4 3
4 5
3 0
3 4
3 2