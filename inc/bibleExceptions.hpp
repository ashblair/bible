#pragma once
#include <stdexcept>
#include <exception>

namespace BIBX
{
    class bibleexception: public std::exception
    { 
    public:
        enum biblextypes {
            ADV = 0,
            CHAR = 1,
            LST = 2,
            WPL = 3,
            INT = 4,
            OFF1 = 5,
            DUP = 6,
            INS = 7,
            PVT = 8,
            OFF2 = 9
        };
        const char * b_Exception[10] = {
            "Error - invalid advance past the end of the string",
            "Error - invalid character get past the end of the string",
            "Error - invalid last character",
            "Error - too many words per line",
            "Error - wrong size for an integer",
            "Error - offset not found",
            "Error - too many duplicate indices",
            "Error - failed to insert string",
            "Error - invalid pivot",
            "Error - offset AVL error"
        };
    };

    class advance: public bibleexception
    {
    public:
        virtual const char* what() const throw() {return b_Exception[ADV];};
    };

    class get_char: public bibleexception
    {
    public:
        virtual const char * what() const throw() {return b_Exception[CHAR];};
    };

    class last_char: public bibleexception
    {
    public:
        virtual const char * what() const throw() {return b_Exception[LST];};
    };

    class words_per_line: public bibleexception
    {
    public:
        virtual const char * what() const throw() {return b_Exception[WPL];};
    };

    class integer: public bibleexception
    {
    public:
        virtual const char * what() const throw() {return b_Exception[INT];};
    };

    class offset_not_found: public bibleexception
    {
    public:
        virtual const char * what() const throw() {return b_Exception[OFF1];};
    };

    class duplicate_indices: public bibleexception
    {
    public:
        virtual const char * what() const throw() {return b_Exception[DUP];};
    };

    class insert: public bibleexception
    {
    public:
        virtual const char * what() const throw() {return b_Exception[INS];};
    };

    class pivot: public bibleexception
    {
    public:
        virtual const char * what() const throw() {return b_Exception[PVT];};
    };

    class offsetAVL: public bibleexception
    {
    public:
        virtual const char * what() const throw() {return b_Exception[OFF2];};
    };


};