#include <iostream>
#include "Riviere.h"

int main()
{
    Riviere riviere;
    riviere.getCase(4, 4).setObstacle();

    riviere.printRiviere();
}
