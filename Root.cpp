#include "Root.h"

Root::Root() {
    ofstream field ("field.txt");
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            field << '8';
        }
        field << endl;
    }
    field.close();
}
