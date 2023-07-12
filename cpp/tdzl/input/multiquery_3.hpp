#pragma once

template <typename derived>
struct multi_query_solution {
    void process_query() {
        int x;
        cin >> x;
        switch (x) {
            case 0: {
                ((derived*)this)->work0();
                break;
            }
            case 1: {
                ((derived*)this)->work1();
                break;
            }
            case 2: {
                ((derived*)this)->work2();
                break;
            }
        }
    }
    void process_queries(int Q) {
        REP(i, 0, Q) {
            process_query();
        }
    }
};
