#pragma once

#include <nana/gui.hpp>
#include <nana/gui/filebox.hpp>
#include <nana/gui/msgbox.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <string>
#include <memory>

using namespace nana;

class welcome_form : public form {
public:
  welcome_form();

private:
  // std::string _m_pick_file(bool is_open) const
  // {
  //     filebox fbox(*this, is_open);
  //     fbox.add_filter("Text", "*.txt");
  //     fbox.add_filter("All Files", "*.*");
  //     fbox.allow_multi_select(false);
  //     auto files = fbox.show();
  //     return files.size() > 0 ? files.at(0).generic_string() : std::string();
  // }

  // bool _m_ask_save()
  // {
  //     if (textbox_.edited())
  //     {
  //         auto fs = textbox_.filename();
  //         msgbox box(*this, "Simple Notepad",
  //         msgbox::button_t::yes_no_cancel); box << "Do you want to save these
  //         changes?";

  //         switch (box.show())
  //         {
  //         case msgbox::pick_yes:
  //             if (fs.empty())
  //             {
  //                 fs = _m_pick_file(false);
  //                 if (fs.empty())
  //                     break;
  //                 if (!fs.has_extension() || fs.extension().generic_string()
  //                 != ".txt")
  //                     fs += ".txt";
  //             }
  //             textbox_.store(fs);
  //             break;
  //         case msgbox::pick_no:
  //             break;
  //         case msgbox::pick_cancel:
  //             return false;
  //         }
  //     }
  //     return true;
  // }

  // void _m_make_menus() {
  //   menubar_.push_back("&FILE");
  //   menubar_.at(0).append("New", [this](menu::item_proxy &ip) {
  //     if (_m_ask_save())
  //       textbox_.reset();
  //   });
  //   menubar_.at(0).append("Open", [this](menu::item_proxy &ip) {
  //     if (_m_ask_save()) {
  //       auto fs = _m_pick_file(true);
  //       if (fs.size())
  //         textbox_.load(fs);
  //     }
  //   });
  //   menubar_.at(0).append("Save", [this](menu::item_proxy &) {
  //     auto fs = textbox_.filename().generic_string();
  //     if (fs.empty()) {
  //       fs = _m_pick_file(false);
  //       if (fs.empty())
  //         return;
  //     }
  //     textbox_.store(fs);
  //   });

  //   menubar_.push_back("F&ORMAT");
  //   menubar_.at(1).append("Line Wrap", [this](menu::item_proxy &ip) {
  // textbox_.line_wrapped(ip.checked());
  // });
  // menubar_.at(1).check_style(0, menu::checks::highlight);
  // }

private:
  place place_;
  button caesarButton, diffi_hellmanButton;
  // menubar menubar_;
  // textbox textbox_;
};
