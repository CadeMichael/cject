/*
 * File: tui.cc
 * Author: Cade Lueker
 * Date: July 5, 2023
 * Description: Create TUI for user interop
 * License: MIT
 */
#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

#include "file.cc"
#include "ftxui/screen/screen.hpp"
#include <string>
#include <vector>

using namespace ftxui;

Component Inner(std::vector<Component> children) {
  Component vlist = Container::Vertical(std::move(children));
  return Renderer(vlist, [vlist] {
    return hbox({
        text(""),
        vlist->Render(),
    });
  });
}

Component Files(std::vector<std::string> files) {
  std::vector<Component> compFiles;
  for (std::string f : files) {
    // auto file = Renderer([f] { return text(f); });
    auto file = MenuEntry(f);
    compFiles.push_back(file);
  }
  Component vlist = Container::Vertical(std::move(compFiles));
  return Renderer(vlist, [vlist] {
    return hbox({
        text("|=>"),
        vlist->Render(),
    });
  });
}

std::vector<Component> Projects() {
  std::unique_ptr<ProjectFile> pf = std::make_unique<ProjectFile>();
  std::vector<std::string> projs = pf->read_proj();
  std::vector<Component> proj_col;

  for (auto p : projs) {
    std::vector<std::string> files = pf->read_path(p);
    auto col = MenuEntry("=> " + p);
    col |= CatchEvent([p, col](Event event) mutable {
      if (event == Event::Character(' ')) {
        std::string command = "tmux new-window -c" + p;
        system(command.c_str());

        return true;
      } else if (event == Event::Character('d')) {
        std::unique_ptr<ProjectFile> pf = std::make_unique<ProjectFile>();
        pf->remove_proj(p);
        col |= border;

        return true;
      }

      return false;
    });
    proj_col.push_back(col);
  }
  return proj_col;
}

auto render_tui() { return Container::Vertical({Renderer([] {return text("|==> Projects <==|") | color(Color::Green);}), Inner(Projects())}); }
