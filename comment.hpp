#include <iostream>
#include <streambuf>


template <class CharT, CharT lf = '\n', class Traits = std::char_traits<CharT>>
class basic_comment_buf : public std::basic_streambuf<CharT, Traits> {
    using Base = std::basic_streambuf<CharT, Traits>;
public:
    using int_type = typename Base::int_type;
    using comment_type = std::basic_string<CharT, Traits, std::allocator<CharT>>;
    basic_comment_buf(Base * sb, comment_type const& comment)
        : sb(sb), begin(true), comment(comment) {}
private:
    virtual int_type overflow(int c) {
        if (c == Traits::eof())
            return !Traits::eof();
        else {
            bool succ = true;
            if (begin) {
                begin = false;
                for (CharT cc : comment) {
                    int_type const r = sb->sputc(cc);
                    succ &= (r != Traits::eof());
                }
            }
            {
                int_type const r = sb->sputc(c);
                succ &= (r != Traits::eof());
            }
            if (c == lf) {
                begin = true;
            }
            return succ ? c : Traits::eof();
        }
    }

    virtual int_type sync() {
        return sb->pubsync();
    }
private:
    Base * sb;
    bool begin;
    comment_type const comment;
};

using comment_buf = basic_comment_buf<char>;
using wcomment_buf = basic_comment_buf<wchar_t>;


template <class CharT, CharT lf = '\n', class Traits = std::char_traits<CharT>>
class basic_comment_stream : public std::basic_ostream<CharT, Traits> {
    using Base = std::basic_ostream<CharT, Traits>;
    using Buf = basic_comment_buf<CharT, lf, Traits>;
public:
    using comment_type = typename Buf::comment_type;
    basic_comment_stream(std::ostream& os, comment_type const& comment)
        : Base(&cbuf), cbuf(os.rdbuf(), comment) {}
private:
    Buf cbuf;
};

using comment_stream = basic_comment_stream<char>;
using wcomment_stream = basic_comment_stream<wchar_t>;
