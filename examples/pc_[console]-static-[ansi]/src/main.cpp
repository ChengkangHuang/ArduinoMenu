#include <iostream>
using namespace std;

//main include for ArduinoMenu
#include <staticMenu.h>
//input/output drivers --------------------------------------
#include <menu/IO/consoleOut.h>
#include <menu/IO/linuxKeyIn.h>
//format specifyers -----------------------------------------
#include <menu/fmt/ANSI.h>//to draw index and text cursors (nav and edit)
#include <menu/fmt/fullText.h>
// #include <menu/fmt/textEditMode.h>
// #include <menu/fmt/textCursor.h>
// #include <menu/fmt/textItem.h>
#include <menu/fmt/titleWrap.h>
//components ------------------------------------------------
#include <menu/comp/endis.h>
// #include <menu/comp/numField.h>
using namespace Menu;

//sketch control and actions ------------------------
bool running=true;//exit program when false

bool quit() {
  //just signal program exit
  _trace(MDO<<"Quit!"<<endl);
  running=false;
  return true;
}

bool tog12();//implemented later because we need to access mainMenu

bool action1() {
  cout<<"Action1 called!"<<endl;
}

bool action2() {
  cout<<"Action2 called!"<<endl;
}

//menu texts -------------------------
const char* subText="Sub-menu";
const char* sub1_text="Sub 1";
const char* sub2_text="Sub 2";
const char* tog12_text="Toggle 1&2";
const char* subn_text="Sub...";
const char* exit_text="<Exit";

const char* mainText="Main menu";
const char* op1_text="Option 1";
const char* op2_text="Option 2";
const char* opn_text="Option...";
const char* quit_text="<Quit.";

//menu static structure ---------------------------
using MainMenu=Item<
  Mutable::Part,
  StaticMenu<
    Item<Mutable::Part,StaticText<&mainText>::Part>,
    StaticData<
      Item<Action<action1>::Part,EnDis<>::Part,Mutable::Part,StaticText<&op1_text>::Part>,
      Item<Action<action2>::Part,EnDis<false>::Part,Mutable::Part,StaticText<&op2_text>::Part>,
      Item<Action<tog12>::Part,Mutable::Part,StaticText<&tog12_text>::Part>,
      Item<Mutable::Part,StaticText<&opn_text>::Part>,
      Item<Mutable::Part,StaticText<&opn_text>::Part>,
      Item<
        Mutable::Part,
        EnDis<true>::Part,
        StaticMenu<
          Item<Mutable::Part,StaticText<&subText>::Part>,
          StaticData<
            Item<Mutable::Part,StaticText<&sub1_text>::Part>,
            Item<Mutable::Part,StaticText<&sub2_text>::Part>,
            Item<Mutable::Part,StaticText<&subn_text>::Part>,
            Item<Mutable::Part,StaticText<&exit_text>::Part>
          >
        >::Part
      >,
      Item<StaticText<&opn_text>::Part>,
      Item<Action<quit>::Part,StaticText<&quit_text>::Part>
    >
  >::Part
>;

MainMenu mainMenu;

//menu output ---------------------------------------
StaticMenuOut<
  FullPrinter::Part,//print all parts, title, index, text cursor
  AnsiFmt::Part,//format using ANSI escape codes
  TitleWrapFmt<>::Part,//wrap title in []
  TextFmt::Part,//format the text parts, use `>` as text cursor`
  // TextCursorFmt,//draw text cursor
  // TextEditModeFmt,//draw edit mode text cursor
  // TextItemFmt,//add newline after each item
  PartialDraw::Part,//this device can position the cursor and do a partial draw
  PanelTarget::Part,//detect target (menu) changes
  RangePanel<>::Part,//control vertical scrolling
  StaticPanel<10,10,20,6>::Part,//define output geometry
  Console::Part,//the raw output device to use
  TextMeasure<>::Part//default monometric text measure
> out;

StaticNavRoot<Nav<MainMenu,3>::Part> nav(mainMenu);

//menu input --------------------------------------
LinuxKeyIn in;

bool tog12() {
  _trace(MDO<<"Toggle Enable/Disable of options 1 and 2"<<endl);
  mainMenu.enable(!mainMenu.enabled(Path<0>().ref()),Path<0>().ref());
  mainMenu.enable(!mainMenu.enabled(Path<1>().ref()),Path<1>().ref());
  return true;
}

int main() {
  nav.print(out);
  while(running) if (nav.doInput(in)) {
    nav.print(out);
  }
  return 0;
}