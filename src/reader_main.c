#include "shared_stuff.h"
#include "reader.h"
#include <time.h>

int main () {
    int file_num;
    
    srand (time(NULL));
    
    file_num = RANDOM_RANGE(0, 4);
    
    return reader(file_num);
}