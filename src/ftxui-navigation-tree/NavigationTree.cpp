// Copyright 2025 Giorgio Menichetti. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include "NavigationTree.hpp"

#include "ftxui/dom/elements.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/component/mouse.hpp"

namespace ftxui {
namespace {
class NavigationNode {
public:
    std::string code;
    std::string value;
    Box nBox;
    bool opened = true;
    std::vector<NavigationNode *> childs;
};

class Impl : public ComponentBase {
public:
    Impl(std::map<std::string, std::string> tree, std::function<std::map<std::string, std::string>(std::string)> back) {
        _tree = tree;
        _back = back;
        auto it = _tree.begin();
        _root = createTree(it);
    }
    Element OnRender() override {
        Elements el;
        setTree(_root, "└─ ", 0, 0, el);
        return vbox(el);
    }
    
    void clearTree(NavigationNode *root) {
        for (auto c : root->childs) {
            clearTree(c);
        }
        root->childs.clear();
        root = nullptr;
    }
    
    NavigationNode *createTree(std::map<std::string, std::string>::iterator &it) {
        if (it == _tree.end()) {
            return nullptr;
        }
        NavigationNode *result = new NavigationNode();
        result->code = it->first;
        result->value = it->second;
        if (_opened.find(it->first) == _opened.end()) {
            _opened[it->first] = result->opened;
        }
        else {
            result->opened = _opened[it->first];
        }
        it = std::next(it);
        while (it != _tree.end()) {
            std::string code = it->first;
            if (code.length() <= result->code.length() ||
                code.substr(0, result->code.length()) != result->code) {
                break;
            }
            auto child = createTree(it);
            result->childs.push_back(child);
        }
        return result;
    }
    
    // compose navigation tree text
    void setTree(NavigationNode *root, std::string prefix, long nSon, long nSons, Elements &el) {
        // main value
        Element nodeEl = text(root->value);
        nodeEl |= reflect(root->nBox);
        el.push_back(hbox({text(prefix), nodeEl}));
        if (!root->opened) {
            return;
        }
        std::string nextPrefix = prefix;
        if (root->childs.size() > 0) {
            if (nSons > 0 && nSon != nSons-1) {
                nextPrefix = prefix.substr(0, prefix.length()-7) + "│  ";
            }
            else {
                nextPrefix = prefix.substr(0, prefix.length()-7) + "   ";
            }
        }
        // childs
        for (long indC=0; indC<root->childs.size(); indC++) {
            std::string childPrefix = "";
            if (indC == root->childs.size()-1) {
                childPrefix = nextPrefix + "└─ ";
            }
            else {
                childPrefix = nextPrefix + "├─ ";
            }
            setTree(root->childs.at(indC), childPrefix, indC, root->childs.size(), el);
        }
    }
    
    bool OnEvent(Event event) override {
        CaptureMouse(event);
        if (event.is_mouse() &&
            event.mouse().button == Mouse::Left &&
            event.mouse().motion == Mouse::Pressed) {
                onEventTree(_root, event);
            return true;
        }
        if (event.is_mouse() &&
            event.mouse().button == Mouse::WheelUp) {
            
        }
        return false;
    }
    
    // compose navigation tree text
    bool onEventTree(NavigationNode *root, Event event) {
        if (root->nBox.Contain(event.mouse().x, event.mouse().y)) {
            // no childs is as "closed"
            if (root->opened && root->childs.size() > 0) {
                root->opened = false;
                _opened[root->code] = false;
            }
            else {
                root->opened = true;
                _opened[root->code] = true;
                std::map<std::string, std::string> result = _back(root->code);
                for (auto r : result) {
                    _tree[r.first] = r.second;
                }
                clearTree(_root);
                auto it = _tree.begin();
                _root = createTree(it);
            }
            return true;
        }
        // childs
        for (auto c : root->childs) {
            if (onEventTree(c, event)) {
                return true;
            }
        }
        return false;
    }
    NavigationNode *_root;
private:
    
    std::map<std::string, bool> _opened;
    std::map<std::string, std::string> _tree;
    std::function<std::map<std::string, std::string>(std::string)> _back;
};

} // namespace

Component NavigationTree(std::map<std::string, std::string> tree, std::function<std::map<std::string, std::string>(std::string)> back) {
    return Make<Impl>(std::move(tree), std::move(back));
}

}