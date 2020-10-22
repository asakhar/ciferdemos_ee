#pragma once

#include <iostream>
#include <locale>
#include <nana/gui.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/checkbox.hpp>
#include <nana/gui/widgets/label.hpp>
// #include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/widgets/spinbox.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <string>

using namespace nana;

class caesar_form : public form {
public:
  void tolower(textbox &box) {
    auto m = box.caption_wstring();
    for (auto &ch : m)
      ch = std::towlower(ch);
    if (box.caption_wstring() == m)
      return;
    box.caption(m);
  }
  void perform(int key, textbox &source, textbox &destination) {
    auto abc = abcbox.caption_wstring();
    auto mes = source.caption_wstring();
    std::wstring code;
    for (auto ch : mes) {
      if (abc.find(ch) != std::wstring::npos) {
        auto res = (static_cast<signed long>(abc.find(ch)) + key) %
                   static_cast<signed long>(abc.size());
        if (res < 0)
          res += abc.size();
        code += abc[res];
      } else
        code += ch;
    }
    if (code == destination.caption_wstring())
      return;
    destination.caption(code);
  }
  void encode() { perform(key.to_int(), message, output); }
  void decode() { perform(-key.to_int(), output, message); }
  void update(bool enc) {
    tolower(abcbox);
    tolower(message);
    if (enc)
      encode();
    else
      decode();
  }
  caesar_form() {
    caption("Caesar Demo");
    // menubar_.create(*this);

    message.create(*this);
    message.tip_string("Decrypted message");
    message.events().text_changed([this](arg_textbox const &arg) {
      if (autoupdate.checked())
        update(encodeq.checked());
    });
    mt.create(*this);
    mt.caption("Decrypted: ");

    key.create(*this);
    key.caption("Key");
    key.events().text_changed([this](arg_spinbox const &arg) {
      if (autoupdate.checked())
        update(encodeq.checked());
    });
    kt.create(*this);
    kt.caption("Key: ");

    output.create(*this);
    output.tip_string("Encrypted message");
    output.events().text_changed([this](arg_textbox const &arg) {
      if (autoupdate.checked())
        update(encodeq.checked());
    });
    ot.create(*this);
    ot.caption("Encrypted: ");

    abcbox.create(*this);
    abcbox.tip_string("Alphabet");
    abcbox.events().text_changed([this](arg_textbox const &arg) {
      key.range(0, abcbox.caption_wstring().size(), 1);
      if (autoupdate.checked())
        update(encodeq.checked());
    });
    abcbox.caption("abcdefghijklmnopqrstuvwxyz");
    lt.create(*this);
    lt.caption("Alphabet: ");

    message.caption("Caesar cifer demo");
    encodeq.create(*this);
    encodeq.caption("Encrypt?");
    encodeq.events().checked([this](arg_checkbox const &arg) {
      output.enabled(!arg.widget->checked());
      message.enabled(arg.widget->checked());
    });

    encodeq.check(true);

    autoupdate.create(*this);
    autoupdate.caption("Auto update");
    autoupdate.events().checked([this](arg_checkbox const &arg) {
      if (!arg.widget->checked()) {
        output.enabled(1);
        message.enabled(1);
      } else {
        output.enabled(!encodeq.checked());
        message.enabled(encodeq.checked());
      }
      encodeq.enabled(arg.widget->checked());
    });
    autoupdate.check(true);

    encryptButton.create(*this);
    decryptButton.create(*this);
    encryptButton.caption("Encrypt");
    decryptButton.caption("Decrypt");
    encryptButton.events().click([this](arg_click const &arg) { update(1); });
    decryptButton.events().click([this](arg_click const &arg) { update(0); });

    place_.bind(*this);
    place_.div(R"(
    vert
    <horizontal arrange=[80,variable] margin=[5, 10] message>
    <horizontal arrange=[80,variable] margin=[5, 10] height=40 key>
    <horizontal arrange=[80,variable] margin=[5, 10] output>
    <horizontal arrange=[80,variable] margin=[5, 10] abc>
    <margin=[5,10] height=30 encodeq>
    <margin=[5,10] gap=10 height=40 buttons>
    )");
    place_["encodeq"] << encodeq << autoupdate;
    place_["message"] << mt << message;
    place_["key"] << kt << key;
    place_["output"] << ot << output;
    place_["abc"] << lt << abcbox;
    place_["buttons"] << encryptButton << decryptButton;
    place_.collocate();
  }

private:
  place place_;
  checkbox encodeq, autoupdate;
  button encryptButton, decryptButton;
  textbox message, output, abcbox;
  spinbox key;
  label mt, ot, kt, lt;
  // menubar menubar_;
};
