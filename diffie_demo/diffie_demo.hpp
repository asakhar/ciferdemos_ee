#pragma once

#include <iostream>
#include <nana/gui.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/checkbox.hpp>
#include <nana/gui/widgets/label.hpp>
// #include <nana/gui/widgets/menubar.hpp>
#include <cstdlib>
#include <ctime>
#include <nana/gui/widgets/spinbox.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <string>

class diffie_form : public nana::form {
public:
  inline bool isPrime(int num) {
    if (num <= 1)
      return 0; // <- 1 is not prime
    for (int i = 2; i * i <= num; i++)
      if (num % i == 0)
        return 0;
    return 1;
  }
  void update() {
    int Apub = (gbox.to_int()^abox.to_int()) % pbox.to_int();
    int Bpub = (gbox.to_int()^bbox.to_int()) % pbox.to_int();
    Alabel.caption("A public key: "+std::to_string(Apub));
    Blabel.caption("B public key: "+std::to_string(Bpub));
    int Shared = (Apub^bbox.to_int()) % pbox.to_int();
    Slabel.caption("Shared key: "+std::to_string(Shared));
  }
  diffie_form()
      : gbox(*this), pbox(*this), abox(*this), bbox(*this), glabel(*this),
        plabel(*this), alabel(*this), blabel(*this), Blabel(*this), Alabel(*this), Slabel(*this) {
    place_.bind(*this);
    std::srand(
        std::time(nullptr)); // use current time as seed for random generator

    gbox.events().text_changed([this](nana::arg_spinbox const &arg) {
      auto col = nana::color();
      if (isPrime(gbox.to_int())) {
        glabel.caption("Base(Is Prime)");
        col.from_rgb(0, 200, 0);
      } else {
        glabel.caption("Base(Not Prime)");
        col.from_rgb(255, 0, 0);
      }
      glabel.fgcolor(col);
    });
    gbox.range(2, 19, 1);
    pbox.events().text_changed([this](nana::arg_spinbox const &arg) {
      auto col = nana::color();
      if (isPrime(pbox.to_int())) {
        plabel.caption("Modulus(Is Prime)");
        col.from_rgb(0, 200, 0);
        update();
      } else {
        plabel.caption("Modulus(Not Prime)");
        col.from_rgb(255, 0, 0);
      }
      plabel.fgcolor(col);
    });
    pbox.range(5, INT32_MAX, 1);
    pbox.caption("9912391");
    alabel.caption("A secret");
    abox.range(1, INT32_MAX, 1);
    abox.caption(std::to_string(std::rand()));
    blabel.caption("B secret");
    bbox.range(1, INT32_MAX, 1);
    bbox.caption(std::to_string(std::rand()));
    nana::color col;
    Alabel.fgcolor(col.from_rgb(0,0,255));
    // Alabel.caption("123");
    Blabel.fgcolor(col);
    Slabel.fgcolor(col.from_rgb(255, 0, 0));

    place_.div(R"(
      vert 
      <horizontal margin=[10,10] height=40 labels1>
      <horizontal gap=[10,repeated] margin=[15,10] boxes1>
      <horizontal margin=[10,10] height=40 labels2>
      <horizontal gap=[10,repeated] margin=[15,10] boxes2>
      <horizontal margin=[10,10] height=40 labels3>
      <horizontal margin=[10,10] height=40 shared>
      )");
    place_["labels1"] << glabel << plabel;
    place_["boxes1"] << gbox << pbox;
    place_["labels2"] << alabel << blabel;
    place_["boxes2"] << abox << bbox;
    place_["labels3"] << Alabel << Blabel;
    place_["shared"] << Slabel;
    place_.collocate();
  }

private:
  nana::place place_;
  nana::spinbox gbox, pbox, abox, bbox;
  nana::label glabel, plabel, alabel, blabel, Alabel, Blabel, Slabel;
};