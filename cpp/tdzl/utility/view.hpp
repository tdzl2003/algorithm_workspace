#pragma once

template <typename Cont>
class reverse_view {
public:
    reverse_view(Cont& _cont): cont(_cont) {}

    auto begin(){
        return cont.rbegin();
    }

    auto end() {
        return cont.rend();
    }

private:
    Cont& cont;
};

