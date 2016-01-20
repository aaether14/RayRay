#include <stdafx.h>




AVoid AUIWindow::Add(std::string key, AModule * module)
{


      AModule::Add(key, module);
      GetWindow()->addChild(static_cast<AUIWindow*>(module)->GetWindow());


}
