#include <iostream>
#include "fmod.hpp"
#include "conio.h"
#include "AudioDemo.hpp"

int main()
{
    AudioDemo demo;
    demo.Prepare();
    demo.RunDemo();
    demo.ShutDown();
    return 0;
}