#include <stdafx.h>




AVoid UIWorkStation::Init()
{


    UIManager::Init();
    Add("Console", new UIConsole());


}







AVoid UIWorkStation::Clean()
{


    UIManager::Clean();


}





AVoid UIWorkStation::Enable()
{



    UIManager::Enable();



}
