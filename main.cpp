#include "caesar_demo/caesar_demo.hpp"
#include "diffih_demo/diffih_demo"
#include "main_form.hpp"

#include <iostream>

welcome_form::welcome_form() {
  caption("Cifer Demos");
  caesarButton.create(*this);
  caesarButton.caption("Caesar demo");
  diffi_hellmanButton.create(*this);
  diffi_hellmanButton.caption("Diffi-Hellman protocol demo");
  caesarButton.events().click([this](const arg_click &arg) {
    hide();
    caesar_form caesarForm;
    caesarForm.events().unload([this]() { show(); });
    caesarForm.modality();
  });
  // menubar_.create(*this);

  // textbox_.create(*this);
  // textbox_.borderless(true);
  // API::effects_edge_nimbus(textbox_, effects::edge_nimbus::none);
  // textbox_.enable_dropfiles(true);
  // textbox_.events().mouse_dropfiles([this](const arg_dropfiles& arg)
  // {
  //     if (arg.files.size() && _m_ask_save())
  //         textbox_.load(arg.files.at(0));
  // });

  // _m_make_menus();

  place_.bind(*this);
  place_.div("vert<caesarb><diffihb>");
  place_["caesarb"] << caesarButton;
  place_["diffihb"] << diffi_hellmanButton;

  // place_.field("menubar") << menubar_;
  // place_.field("textbox") << textbox_;
  place_.collocate();

  // events().unload([this](const arg_unload &arg) {
  //   if (!_m_ask_save())
  //     arg.cancel = true;
  // });
}

int main() {
  welcome_form npform;
  npform.show();
  exec();
}