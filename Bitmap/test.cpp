#include "Bitmap.h"

void TestBitMap()
{
    BitMap am(-1);
    BitMap bm(200);
    bm.Set(136);
    bm.Set(1);
    cout << bm.Find(136) << endl;
    bm.Reset(136);
    cout << bm.Find(136) << endl;
}

int main()
{
    TestBitMap();
    return 0;
}