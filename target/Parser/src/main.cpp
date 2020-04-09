#include <iostream>
#include "ParseSystemInfo.h"


using namespace std;

int main()
{
    Init();
    string src = R"(HDQQ:$STRING("IIP:", $STEP_IP, " ;" , $IFNULL($STEP_IP, $STEP_IP, "NA"))$STRING("MAC:", $IFNULL($STEP_IIP,  $STEP_IIP, "NA"), $STEP_LOCAL_MAC, "; ",1))";
    cout << src << endl;
    cout << ParseSystemInfo(src) << endl;

}
