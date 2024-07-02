#include "../utility/md_vector.hpp"
#include "../bits/common.hpp"

template <class S, S(*op)(S, S), S(*e)()>
struct segtree2d {
public:
    segtree2d(int n, int m) {
        n_ = n;
        logn_ = ceil_pow2(n);
        sizen_ = 1 << logn_;
        m_ = m;
        logm_ = ceil_pow2(m);
        sizem_ = 1 << logm_;
        d_ = md_vector<S, 2>({ (size_t)sizen_*2, (size_t)sizem_*2 }, e());
    }

    segtree2d(md_vector<S, 2> d) {
        // TODO
        assert(("TODO", false));
    }

    void set(int i, int j, S x) {
        assert(0 <= i && i < n_);
        assert(0 <= j && j < m_);

        i += sizen_;
        j += sizem_;
        d_[i][j] = x;
        for (int dj = 1; dj <= logm_; dj++) {
            _update_x(i, j >> dj);
        }
        for (int di = 1; di <= logn_; di++) {
            for (int dj = 0; dj <= logm_; dj++) {
                _update_y(i >> di, j >> dj);
            }
        }
    }

    S get(int i, int j) const {
        assert(0 <= i && i < n_);
        assert(0 <= j && j < m_);
        return d_[i + sizen_][j + sizem_];
    }

    S prod(int t, int b, int l, int r) const {
        assert(0 <= t && t <= b && b <= n_);
        assert(0 <= l && l <= r && r <= m_);
        S smt = e(), smb = e();
        t += sizen_;
        b += sizen_;
        l += sizem_;
        r += sizem_;

        while (t < b) {
            if (t & 1) smt = op(smt, _prod_x(t++, l, r));
            if (b & 1) smb = op(_prod_x(--b, l, r), smb);
            t >>= 1;
            b >>= 1;
        }
        return op(smt, smb);
    }

    S all_prod() const {
        return d_[1][1];
    }

private:
    S _prod_x(int i, int l, int r) const {
        S sml = e(), smr = e();
        while (l < r) {
            if (l & 1) sml = op(sml, d_[i][l++]);
            if (r & 1) smr = op(d_[i][--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }
    void _update_x(int i, int j) {
        d_[i][j] = op(d_[i][j * 2], d_[i][j * 2 + 1]);

    }
    void _update_y(int i, int j) {
        d_[i][j] = op(d_[i * 2][j], d_[i * 2 + 1][j]);
    }

    md_vector<S, 2> d_;
    int n_, m_;
    int logn_, logm_;
    int sizen_, sizem_;
};
