#pragma once

namespace tdzl {
    namespace internal {
        class bitset_item_reference {
        public:
            bitset_item_reference(unsigned long long& ref, int ofs) :
                ref_(ref), ofs_(ofs) {

            }
            operator bool() const {
                return (ref_ & (1ULL << ofs_)) != 0;
            }

            bool operator!() {
                return (ref_ & (1ULL << ofs_)) == 0;
            }

            bitset_item_reference operator =(bool value) {
                if (value) {
                    ref_ = ref_ | (1ULL << ofs_);
                }
                else {
                    ref_ = ref_ & ~(1ULL << ofs_);
                }
                return *this;
            }
        private:
            unsigned long long& ref_;
            int ofs_;
        };
    }

    class bitset {
    public:
        bitset(size_t sz = 0, bool val = false) :
            sz_(sz),
            data_((sz + 63)/64, val ? -1 : 0)
        {
            trim();
        }

        internal::bitset_item_reference operator[](size_t idx) {
            assert(0 <= idx && idx < sz_);
            return internal::bitset_item_reference(data_[idx / 64], idx % 64);
        }

        size_t size() const {
            return sz_;
        }

        void resize(size_t newsz) {
            if (newsz == sz_) {
                return;
            }
            if (newsz < sz_) {
                data_.resize((newsz + 63) / 64);
                sz_ = newsz;
                trim();
            }
            else {
                data_.resize((newsz + 63) / 64);
                sz_ = newsz;
            }
        }

        void trim() {
            int tail = sz_ & 0x3f;
            if (tail) {
                data_.back() &= (1ULL << tail) - 1;
            }
        }

        bitset& operator|=(const bitset& other) {
            for (int i = 0; i < other.data_.size() && i < data_.size(); i++) {
                data_[i] |= other.data_[i];
            }
            return *this;
        }

        bitset& operator&=(const bitset& other) {
            for (int i = 0; i < other.data_.size() && i < data_.size(); i++) {
                data_[i] &= other.data_[i];
            }
            return *this;
        }

        bitset& operator<<=(size_t sz) {
            const auto _Wordshift = static_cast<ptrdiff_t>(sz / 64);
            if (_Wordshift != 0) {
                for (ptrdiff_t _Wpos = data_.size() - 1; 0 <= _Wpos; --_Wpos) {
                    data_[_Wpos] = _Wordshift <= _Wpos ? data_[_Wpos - _Wordshift] : 0;
                }
            }
            if ((sz %= 64) != 0) { // 0 < _Pos < _Bitsperword, shift by bits
                for (ptrdiff_t _Wpos = data_.size() - 1; 0 < _Wpos; --_Wpos) {
                    data_[_Wpos] = (data_[_Wpos] << sz) | (data_[_Wpos - 1] >> (64 - sz));
                }

                data_[0] <<= sz;
                trim();
            }
            return *this;
        }

        bitset& operator>>=(size_t sz) {
            const auto _Wordshift = static_cast<ptrdiff_t>(sz / 64);
            if (_Wordshift != 0) {
                for (ptrdiff_t _Wpos = 0; _Wpos < data_.size(); ++_Wpos) {
                    data_[_Wpos] = _Wordshift < data_.size() - _Wpos ? data_[_Wpos + _Wordshift] : 0;
                }
            }

            if ((sz %= 64) != 0) { // 0 < _Pos < _Bitsperword, shift by bits
                for (ptrdiff_t _Wpos = 0; _Wpos < data_.size() - 1; ++_Wpos) {
                    data_[_Wpos] = (data_[_Wpos] >> sz) | (data_[_Wpos + 1] << (64 - sz));
                }

                data_.back() >>= sz;
            }
            return *this;
        }

        void clear() {
            fill(data_.begin(), data_.end(), 0ULL);
        }

        void set() {
            fill(data_.begin(), data_.end(), ~0ULL);
            trim();
        }

        void clear(size_t start, size_t end = (size_t)-1) {
            if (start >= sz_) {
                return;
            }
            end = std::min(end, sz_);
            if (start / 64 == end / 64) {
                data_[start / 64] &= ((1ULL << (start % 64)) - 1) | ((-1ULL) << (end % 64));
                return;
            }
            if (start % 64) {
                data_[start / 64] &= (1ULL << (start%64)) - 1;
                start = start - start % 64 + 64;
            }
            start /= 64;
            if (end % 64) {
                data_[end / 64] &= (-1ULL) << (end % 64);
                end = end - end % 64;
            }
            end /= 64;
            if (start < data_.size()) {
                std::fill(data_.begin() + start, data_.begin() + end, 0);
            }
        }

    private:
        vector<unsigned long long> data_;
        size_t sz_;
    };


}
