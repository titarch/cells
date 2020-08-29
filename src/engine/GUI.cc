//
// Created by bparsy on 8/29/20.
//

#include "GUI.hh"

static void multimap_call_all(auto& map, auto key) {
    for (auto it = map.lower_bound(key); it != map.upper_bound(key); ++it)
        it->second();
}

void GUI::draw() const {

}

void GUI::handle_events(sf::Event& evt) const {
    multimap_call_all(events_, evt.type);

    if (auto kit = key_events_.find(evt.type); kit != key_events_.end())
        multimap_call_all(kit->second, evt.key.code);
}

auto GUI::add_event(sf::Event::EventType type, void_func const& callback) -> GUI& {
    events_.insert({type, callback});
    return *this;
}

auto GUI::add_key_event(sf::Event::EventType key_event, sf::Keyboard::Key key, void_func const& callback) -> GUI& {
    key_events_[key_event].insert({key, callback});
    return *this;
}

auto GUI::add_mousebutton_event(sf::Event::EventType mousebutton_event, sf::Mouse::Button button,
                                auto callback) -> GUI& {
    return *this;
}
