#include <iostream>
using namespace std;

struct Button {
  virtual void paint() = 0;
};
 
struct WinButton : public Button {
  void paint (){
    std::cout << " I'm a window button \n";
  }
};
 
struct OSXButton : public Button {
  void paint (){
    std::cout << " I'm a OSX button \n";
  }
};
 
struct GUIFactory {
  virtual Button* createButton () = 0;
};
 
struct WinGUIFactory : public GUIFactory {
  Button* createButton (){
    return new WinButton();
  }
};
 
struct OSXGUIFactory : public GUIFactory {
  Button* createButton (){
    return new OSXButton();
  }
};
 
struct Application {
  Application(GUIFactory* factory){
    Button * button = factory->createButton();
    button->paint();
  }
};
 
/* application code */
 
int main()
{
  GUIFactory* factory1 = new WinGUIFactory();
  GUIFactory* factory2 = new OSXGUIFactory();
 
  Application* winApp  = new Application (factory1); 
  Application* osxApp  = new Application (factory2);
 
  delete factory1, factory2;
 
  return 0;
}
