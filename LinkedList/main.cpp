#include "LinkedList.h"

int main()
{
    ostream& out = cout;

    LinkedList <int> ll1(1);
    const LinkedList <int> ll2(1);
    cout << ll1[0] << endl;
    cout << ll2[0] << endl;
    ll1.insertAt(0, 0);
    ll1.insert(1);
    ll1.insert(2);
    ll1.insertAt(3, 3);
    cout << ll1.itemAt(0) << endl;
    cout << ll1.itemAt(1) << endl;
    cout << ll1.itemAt(2) << endl;
    cout << ll1.itemAt(3) << endl;
    cout << ll1.itemAt(4) << endl;

    ll1.removeAt(3);
    ll1.remove(0);
    ll1.display(out);

    ll1.remove(4);

    ll1.clear();
    return 0;
}
