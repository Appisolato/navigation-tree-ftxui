// Copyright 2025 Giorgio Menichetti. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef NavigationTree_hpp
#define NavigationTree_hpp

#include <string>
#include <map>

#include "ftxui/component/component_base.hpp"

using namespace ftxui;

namespace ftxui {

/// @brief Draw a navigable tree
/// @param tree A tree in dot notation (nodeA, nodeA.nodeA1, nodeA, nodeA2, nodeB, nodeC)
/// @param back A function called everyonce a node has to be expanded
/// @ingroup component
///
/// ### Example
///
/// ```cpp
/// std::map<std::string, std::string> tree;
/// tree["n1"] = "desc1";
/// tree["n1.n11"] = "desc2";
/// tree["n1.n11.n111"] = "desc3";
/// tree["n1.n11.n112"] = "desc4";
/// tree["n1.n11.n113"] = "desc5";
/// tree["n1.n11.n114"] = "desc6";
/// tree["n1.n12"] = "desc7";
/// tree["n1.n13"] = "desc8";
/// tree["n1.n13.n131"] = "desc9";
/// tree["n1.n13.n132"] = "desc10";
/// tree["n1.n13.n133"] = "desc11";
/// tree["n1.n13.n134"] = "desc12";
/// tree["n1.n13.n135"] = "desc13";
/// tree["n1.n13.n136"] = "desc14";
/// tree["n1.n13.n137"] = "desc15";
/// tree["n1.n13.n138"] = "desc16";
/// tree["n1.n13.n139"] = "desc17";
/// tree["n1.n13.n140"] = "desc18";
/// tree["n1.n13.n141"] = "desc19";
/// tree["n1.n13.n142"] = "desc20";
/// tree["n1.n13.n143"] = "desc21";
/// auto cn = NavigationTree(tree, [=] (std::string code) {
///     std::map<std::string, std::string> toAdd;
///     if (code == "n1.n11") {
///         toAdd["n1.n11.n115"] = "desc6_1";
///     }
///     return toAdd;
/// });
/// ```
///
/// ### Output
///
/// ```
/// └─ desc1
/// ├─ desc2
/// │  ├─ desc3
/// │  ├─ desc4
/// │  ├─ desc5
/// │  └─ desc6
/// ├─ desc7
/// └─ desc8
///    ├─ desc9
///    ├─ desc10
///    ├─ desc11
///    ├─ desc12
///    ├─ desc13
///    ├─ desc14
///    ├─ desc15
///    ├─ desc16
///    ├─ desc17
///    ├─ desc18
///    ├─ desc19
///    ├─ desc20
///    ├─ desc21
/// ```
// NOLINTNEXTLINE
Component NavigationTree(std::map<std::string, std::string> tree, std::function<std::map<std::string, std::string>(std::string)> back);
}

#endif /* NavigationTree_hpp */