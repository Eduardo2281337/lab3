#include <iostream>
#include "Explorer.h"
#include "GroupByFolders.h"
#include "GroupByTypes.h"

int main()
{
    IExplore* gpf = new GroupByFolders();
    IExplore* gpt = new GroupByTypes();
    Explorer* e = new Explorer(gpf);
    e->explore("D:/games");
    e->setStrategy(gpt);
    e->explore("D:/games");
    delete gpf;
    delete gpt;
    delete e;
    return 0;
}
