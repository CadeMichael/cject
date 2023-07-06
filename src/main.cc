/*
 * File: main.cc
 * Author: Cade Lueker
 * Date: July 5, 2023
 * Description: Run Tui
 * License: MIT
 */

#include <filesystem>
#include <memory>  // for allocator, make_shared, __shared_ptr_access
#include <utility> // for move
#include <vector>  // for vector

#include "ftxui/component/captured_mouse.hpp" // for ftxui
#include "ftxui/component/component.hpp" // for Collapsible, Renderer, Vertical
#include "ftxui/component/component_base.hpp" // for ComponentBase
#include "ftxui/component/screen_interactive.hpp" // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"                 // for text, hbox, Element

// #include "file.cc"
#include "tui.cc"

using namespace ftxui;

int main(int argc, char* argv[]) {
  if (argc < 2) {
    ScreenInteractive screen = ScreenInteractive::FitComponent();
    auto component = render_tui();
    screen.Loop(component);
  } else if (*argv[1] == '.') {
    std::string path = std::filesystem::current_path();
    std::unique_ptr<ProjectFile> pf = std::make_unique<ProjectFile>();
    
    pf->append_proj(path);
  }
  // File testing
  // std::vector<std::string> files = pf->read_path("/home/cadel/Desktop/cject/");
  // for (auto x : files)
    // std::cout << x << std::endl;
}
