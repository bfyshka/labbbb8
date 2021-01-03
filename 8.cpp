#include <iostream>

using namespace std;

template <typename T>
class Operation 
{
public:
    T sum;

    Operation()
    {
        sum = 0;
    };

    ~Operation()
    {

    };

    T add(T item)
    {
        sum += item;
        return sum;
    }

    T take(T item)
    {
        sum -= item;
        return sum;
    }

    bool check(T first, T second)
    {
        return first == second;
    }
};

template <class T2>
class Transaction
{
    T2* curr;
    T2* prev;
public:
    Transaction() : prev(NULL), curr(new T2)
    {

    };

    Transaction(const Transaction& obj) : curr(new T2(*(obj.curr))), prev(NULL)
    {

    };

    ~Transaction()
    {
        delete curr;
        delete prev;
    };

    Transaction& operator=(const Transaction& obj);

    void info(bool);

    int beginDeposit(int);

    int beginWithdrawal(int);

    void commit();

    void deleteTrans();

    T2* operator->();
};

template <class T2>
Transaction<T2>& Transaction<T2>::operator=(const Transaction<T2>& obj)
{
    if (this != &obj)
    {
        delete curr;
        curr = new T2(*(obj.curr));
    }
    return *this;
}

template <class T2>
T2* Transaction<T2>::operator->()
{
    return curr;
}

template <class T2>
void Transaction<T2>::info(bool before)
{
    if (before)
    {
        cout << "Before transaction" << endl;
    }
    else
    {
        cout << "After transaction" << endl;
    }

    if (prev)
    {
        cout << "prev = " << prev->sum << endl;
    }
    else
    {
        cout << "prev = NULL" << endl;
    }

    if (curr)
    {
        cout << "curr = " << curr->sum << endl;
    }
    else
    {
        cout << "curr = NULL" << endl;
    }
}

template <class T2>
int Transaction<T2>::beginDeposit(int value)
{
    delete prev;
    prev = curr;
    curr = new T2(*prev);
    if (!curr)
    {
        return 0;
    }
    curr->add(value);
    return 1;
}

template <class T2>
int Transaction<T2>::beginWithdrawal(int value)
{
    delete prev;
    prev = curr;
    curr = new T2(*prev);
    if (!curr)
    {
        return 0;
    }
    curr->take(value);
    return 1;
}

template <class T2>
void Transaction<T2>::commit()
{
    delete prev;
    prev = NULL;
}

template <class T2>
void Transaction<T2>::deleteTrans()
{
    if (prev != NULL)
    {
        delete curr;
        curr = prev;
        prev = NULL;

    }
    cout << "Error during transcation processing. Transaction canceled." << endl;
}

void print_menu() {
    system("cls");

    cout << "Choose option:" << endl;
    cout << "1. Make deposit" << endl;
    cout << "2. Make withdrawal" << endl;
    cout << "3. Balance" << endl;
    cout << "4. Exit" << endl;
};
int main()
{
    Transaction<Operation<int>> tr;
    int option, value1, value2, value3;
    tr->add(100);
    do {
        print_menu();
    
        cin >> option;
    
        switch (option) {
        case 1:
            cout << "Enter deposit size" << endl;
            cin >> value1;
            cout << "Confirm deposit size" << endl;
            cin >> value2;
    
            tr.info(true);
            if (tr->check(value1, value2))
            {
                tr.beginDeposit(value1);
                tr.info(false);
                tr.commit();
            }
            else {
                tr.deleteTrans();
                tr.info(false);
            }
            break;
        case 2:
            value3 = tr->sum;
            cout << "Enter withdrawal size" << endl;
            cin >> value1;
            cout << "Confirm withdrawal size" << endl;
            cin >> value2;
    
            tr.info(true);
            if (tr->check(value1, value2) && (value3 >= value1))
            {
                tr.beginWithdrawal(value1);
                tr.info(false);
                tr.commit();
            }
            else {
                tr.deleteTrans();
                tr.info(false);
            }
            break;
        case 3:
            cout << "Current balance - " << tr->sum << endl;
            break;
        }
    } while (option != 4);

    return 0;
}