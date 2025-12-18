// Copyright 2025 Giorgio Menichetti. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <map>

#include "NavigationTree.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/component/component.hpp"

using namespace ftxui;

int main(int argc, const char * argv[]) {
    auto screen = ScreenInteractive::TerminalOutput();
    screen.Fullscreen();
    
    std::map<std::string, std::string> tree;
    tree["n1"] = "desc1";
    tree["n1.n11"] = "desc2";
    tree["n1.n11.n111"] = "desc3";
    tree["n1.n11.n112"] = "desc4";
    tree["n1.n11.n113"] = "desc5";
    tree["n1.n11.n114"] = "desc6";
    tree["n1.n12"] = "desc7";
    tree["n1.n13"] = "desc8";
    tree["n1.n13.n131"] = "desc9";
    tree["n1.n13.n132"] = "desc10";
    tree["n1.n13.n133"] = "desc11";
    tree["n1.n13.n134"] = "desc12";
    tree["n1.n13.n135"] = "desc13";
    tree["n1.n13.n136"] = "desc14";
    tree["n1.n13.n137"] = "desc15";
    tree["n1.n13.n138"] = "desc16";
    tree["n1.n13.n139"] = "desc17";
    tree["n1.n13.n140"] = "desc18";
    tree["n1.n13.n141"] = "desc19";
    tree["n1.n13.n142"] = "desc20";
    tree["n1.n13.n143"] = "desc21";

    auto cn = NavigationTree(tree, [=] (std::string code) {
        std::map<std::string, std::string> toAdd;
        if (code == "n1.n11") {
            toAdd["n1.n11.n115"] = "opop5";
        }
        return toAdd;
    });
    Component w = Window({
        .title = "Maccosa?",
        .top = 0,
        .left = 0,
        .width = screen.dimx(),
        .height = screen.dimy(),
        .inner = cn,
    });
    
    screen.Loop(w);
    
    return 0;
}
