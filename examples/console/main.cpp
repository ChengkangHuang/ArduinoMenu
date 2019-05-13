#include <menu.h>
#include <menu/IO/consoleOut.h>

// using Out=TextFmt<TitleWrap<RawOut<ostream&,cout>>>;
using Out=TextFmt<TitleWrap<Console<>>>;

const char* singleOp_text="Just testing";
using SingleOp=StaticText<&singleOp_text>;

const char* op1_text="Op 1";
const char* op2_text="Op ...";
const char* op3_text="Op 3";
const char* extra_text="extra option";
const char* mainMenu_title="Main menu";
using MainMenu=
  StaticText<
    &mainMenu_title,
    StaticMenu<
      StaticText<&op1_text>,
      StaticText<&op2_text>,
      StaticText<&op3_text>
    >
  >;

using DynaMenu=
  Prompt<
    StaticText<
      &mainMenu_title,
      VectorMenu<>
    >
  >;

DynaMenu dynaMenu(
  new Prompt<StaticText<&op1_text>>(),
  new Prompt<StaticText<&op2_text>>(),
  new Prompt<StaticText<&op3_text>>()
);

Out out;//to use with single option
StaticNav<Out,MainMenu,NavPos<>> nav;
DynamicNav<MenuOutDef<Out>,DynaMenu,NavPos<>> dyNav(dynaMenu);

StaticNav<Out,SingleOp> singleNav;

int main() {
  cout<<"AM5 tests"<<endl;

  cout<<"{single option test}"<<endl;
  SingleOp().print(singleNav,out);
  cout<<endl;

  cout<<"{static menu test}"<<endl;
  nav.printMenu();
  cout<<endl;

  cout<<"{dynamic menu test}"<<endl;
  dyNav.printMenu();
  cout<<"{adding option}"<<endl;
  dynaMenu.push_back(new Prompt<StaticText<&extra_text>>());
  dyNav.printMenu();
  cout<<endl<<"-------"<<endl;
  cout<<"{navigate up (index)}"<<endl;
  dyNav.up();
  dyNav.printMenu();
  cout<<endl<<"-------"<<endl;
}