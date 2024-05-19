#include "QueueBank.h"

using namespace std;

int main(){

    Bank bank;
    bank.make_start_data();
    bank.work();
    bank.display_data();
    bank.display_data_in_file();

    return 0;
}