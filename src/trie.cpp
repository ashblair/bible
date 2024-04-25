#include "first.hpp"
#include "trie.hpp"
#include "bibleExceptions.hpp"

using namespace std;

// these statics pertain to The Project Gutenberg eBook of The King James Version of the Bible
    vector<TRIE::verseOff> TRIE::KJV::VERSES;
    TRIE::pDiv TRIE::KJV::DIVS = NULL; // offsets into embedded txt file

    const UINT TRIE::KJV::EXTENTS[] = {TEST_COUNT, OTBK_COUNT, NTBK_COUNT};
    const UINT TRIE::KJV::KJV_START = 0xBC7;
    const UINT TRIE::KJV::KJV_END = 0x43B3DA;
    const char * TRIE::KJV::TESTAMENTS[] = 
    {
        "The Old Testament of the King James Version of the Bible",
        "The New Testament of the King James Bible",
        "***"
    };
    const char * TRIE::KJV::TESTAMENTS_ABBR[] = {"O", "N", "*"};
    const UINT TRIE::KJV::TESTAMENTS_OFFS[] = {0xB58, 0x341CCC, 0x341CBF};
    const char * TRIE::KJV::OTBOOKS[] = 
    {
        "The First Book of Moses: Called Genesis",
        "The Second Book of Moses: Called Exodus",
        "The Third Book of Moses: Called Leviticus",
        "The Fourth Book of Moses: Called Numbers",
        "The Fifth Book of Moses: Called Deuteronomy",
        "The Book of Joshua",
        "The Book of Judges",
        "The Book of Ruth",
        "The First Book of Samuel",
        "The Second Book of Samuel",
        "The First Book of the Kings",
        "The Second Book of the Kings",
        "The First Book of the Chronicles",
        "The Second Book of the Chronicles",
        "Ezra",
        "The Book of Nehemiah",
        "The Book of Esther",
        "The Book of Job",
        "The Book of Psalms",
        "The Proverbs",
        "Ecclesiastes",
        "The Song of Solomon",
        "The Book of the Prophet Isaiah",
        "The Book of the Prophet Jeremiah",
        "The Lamentations of Jeremiah",
        "The Book of the Prophet Ezekiel",
        "The Book of Daniel",
        "Hosea",
        "Joel",
        "Amos",
        "Obadiah",
        "Jonah",
        "Micah",
        "Nahum",
        "Habakkuk",
        "Zephaniah",
        "Haggai",
        "Zechariah",
        "Malachi"
    };
    const char * TRIE::KJV::NTBOOKS[] = 
    {
        "The Gospel According to Saint Matthew",
        "The Gospel According to Saint Mark",
        "The Gospel According to Saint Luke",
        "The Gospel According to Saint John",
        "The Acts of the Apostles",
        "The Epistle of Paul the Apostle to the Romans",
        "The First Epistle of Paul the Apostle to the Corinthians",
        "The Second Epistle of Paul the Apostle to the Corinthians",
        "The Epistle of Paul the Apostle to the Galatians",
        "The Epistle of Paul the Apostle to the Ephesians",
        "The Epistle of Paul the Apostle to the Philippians",
        "The Epistle of Paul the Apostle to the Colossians",
        "The First Epistle of Paul the Apostle to the Thessalonians",
        "The Second Epistle of Paul the Apostle to the Thessalonians",
        "The First Epistle of Paul the Apostle to Timothy",
        "The Second Epistle of Paul the Apostle to Timothy",
        "The Epistle of Paul the Apostle to Titus",
        "The Epistle of Paul the Apostle to Philemon",
        "The Epistle of Paul the Apostle to the Hebrews",
        "The General Epistle of James",
        "The First Epistle General of Peter",
        "The Second General Epistle of Peter",
        "The First Epistle General of John",
        "The Second Epistle General of John",
        "The Third Epistle General of John",
        "The General Epistle of Jude",
        "The Revelation of Saint John the Divine"
    };
    const char ** TRIE::KJV::BOOKS[] = {OTBOOKS, NTBOOKS};
    const char * TRIE::KJV::OTBOOKS_ABBR[] = 
    {
        "GEN", "EXO", "LEV", "NUM", "DEU", "JOS", "JDG", "RUT", "SA1", "SA2", 
        "KI1", "KI2", "CH1", "CH2", "EZR", "NEH", "EST", "JOB", "PSA", "PRO",
        "ECC", "SOS", "ISA", "JER", "LAM", "EZE", "DAN", "HOS", "JOE", "AMO",
        "OBA", "JON", "MIC", "NAH", "HAB", "ZEP", "HAG", "ZEC", "MAL"
    }; 
    const char * TRIE::KJV::NTBOOKS_ABBR[] =   
    {
        "MAT", "MAR", "LUK", "JOH", "ACT", "ROM", "CO1", "CO2", "GAL", "EPH",
        "PHI", "COL", "TH1", "TH2", "TI1", "TI2", "TIT", "PHL", "HEB", "JAM",
        "PE1", "PE2", "JO1", "JO2", "JO3", "JUD", "REV"
    };

    const char ** TRIE::KJV::BOOKS_ABBR[] = {OTBOOKS_ABBR, NTBOOKS_ABBR}; 
    const UINT TRIE::KJV::OTBOOKS_OFFS[] = 
    {
        0xB9A, 0x34747, 0x60BE2, 0x81C6C, 0xAF97F, 0xD594B, 0xEF896, 0x109203,
        0x10C7F1, 0x12E17C, 0x149CAB, 0x16AC62, 0x18A0E2, 0x1A7351, 0x1CB32E,
        0x1D5AC6, 0x1E486D, 0x1EC533, 0x205941, 0x242209, 0x257AE3, 0x25F166,
        0x262AE5, 0x295201, 0x2CF116, 0x2D3D21, 0x3090D3, 0x319057, 0x320156,
        0x322DC5, 0x32880F, 0x3296DA, 0x32B269, 0x32F5EA, 0x3312A1, 0x33338B,
        0x3356C3, 0x336E7F, 0x33F6D3
    };
     
    const UINT TRIE::KJV::NTBOOKS_OFFS[] =    
    {
        0x341CFF, 0x3629A5, 0x3776A7, 0x39ADEB,
        0x3B4C32, 0x3D6C4E, 0x3E3F37, 0x3F0DA7, 0x3F9397, 0x3FD81C, 0x401C66,
        0x404D0F, 0x407A0C, 0x40A2D0, 0x40B9BD, 0x40EF23, 0x4115DE, 0x412B76,
        0x413575, 0x41D135, 0x420442, 0x423C43, 0x42605E, 0x4295F5, 0x429CA1,
        0x42A378, 0x42B23B
    };
    const UINT * TRIE::KJV::BOOKS_OFFS[] = {OTBOOKS_OFFS, NTBOOKS_OFFS}; 

UINT 
    TRIE::KJVtype::edgeCount = 0, 
    TRIE::KJVtype::nodeCount = 0, 
    TRIE::KJVtype::reptCount = 0, 
    TRIE::KJVtype::offsetAVLidx = 0,
    TRIE::KJVtype::dupCount = 0;

string TRIE::KJVtype::reptLine = "";

avlNexus<TRIE::trieEdge> * TRIE::trieNode::EDGE_NEXUS = NULL;
vector<TRIE::trieNode> TRIE::trieTree::TRIE_NODES;
const char 
    TRIE::trieStr::END_CHR = '\0', 
    TRIE::trieStr::C_WC = '_', 
    TRIE::trieStr::S_WC = '%';
bool TRIE::trieStr::caseInsensitive = false;


extern char TXT_START   asm("_binary_rsc_KJV_txt_start");
extern char TXT_END     asm("_binary_rsc_KJV_txt_end");


extern char DATA_START  asm("_binary_rsc_parse_dat_start");
extern char DATA_END    asm("_binary_rsc_parse_dat_end");

extern char VERSE_START asm("_binary_rsc_verse_txt_start");
extern char VERSE_END   asm("_binary_rsc_verse_txt_end");

// NON-METHODS START HERE:
/*void TRIE::checkBookHardCodes(void)
{
    UINT 
        szB = sizeof(TRIE::KJV::BOOKS) / sizeof(TRIE::KJV::BOOKS[0]),
        szA = sizeof(TRIE::KJV::BOOKS_ABBR) / sizeof(TRIE::KJV::BOOKS_ABBR[0]),
        szO = sizeof(TRIE::KJV::BOOKS_OFFS) / sizeof(TRIE::KJV::BOOKS_OFFS[0]);

    std::cout << "Book Count [" << szB << "]\n";
    if (szA != szB)
    {
        std::cout << "Abbreviation Count [" << szA << "] does not match.\n";
        return;
    }
    if (szO != szB)
    {
        std::cout << "Offset Count [" << szO << "] does not match.\n";
        return;
    }
    for (UINT j = 0; j < 2; ++j)
    {
        for (UINT i = 0; i < szB; ++i)
        {
            UINT szI = strlen(TRIE::KJV::BOOKS[j][i]);
            string 
                s1 = string(TRIE::KJV::BOOKS[j][i], szI),
                s2 = string(&TXT_START + TRIE::KJV::BOOKS_OFFS[j][i], szI);
            int cmp = s1.compare(s2);
            string s3 = "GOOD\n";
            if (cmp != 0) s3 = "BAD " + s2 + "\n";
            std::cout << i << ") " << TRIE::KJV::BOOKS_ABBR[j][i] << " or " << s1 << " " << s3;

        }
    }

}

void TRIE::checkTestamentHardCodes(void)
{
    UINT 
        szT = sizeof(TRIE::KJV::TESTAMENTS) / sizeof(TRIE::KJV::TESTAMENTS[0]),
        szA = sizeof(TRIE::KJV::TESTAMENTS_ABBR) / sizeof(TRIE::KJV::TESTAMENTS_ABBR[0]),
        szO = sizeof(TRIE::KJV::TESTAMENTS_OFFS) / sizeof(TRIE::KJV::TESTAMENTS_OFFS[0]);

    std::cout << "Testament Count [" << szT << "]\n";
    if (szA != szT)
    {
        std::cout << "Abbreviation Count [" << szA << "] does not match.\n";
        return;
    }
    if (szO != szT)
    {
        std::cout << "Offset Count [" << szO << "] does not match.\n";
        return;
    }
    for (UINT i = 0; i < szT; ++i)
    {
        UINT szI = strlen(TRIE::KJV::TESTAMENTS[i]);
        string 
            s1 = string(TRIE::KJV::TESTAMENTS[i], szI),
            s2 = string(&TXT_START + TRIE::KJV::TESTAMENTS_OFFS[i], szI);
        int cmp = s1.compare(s2);
        string s3 = "GOOD\n";
        if (cmp != 0) s3 = "BAD\n";
        std::cout << i << ") " << TRIE::KJV::TESTAMENTS_ABBR[i] << " or " << s1 << s3;

    }

}*/

// NON-METHODS END HERE



TRIE::DivType::DivType(void): startOff(INIT_UINT), endOff(INIT_UINT), indices(NULL) {}
TRIE::DivType::DivType(const DivType & a): startOff(a.startOff), endOff(a.endOff) 
{
    if (a.indices == NULL) indices = NULL;
    else 
    {
        indices = new vector<pDiv>;
        for (vector<pDiv>::const_iterator iIT = a.indices->begin(); iIT != a.indices->end(); ++iIT)
        {
            indices->push_back(new DivType(*(*iIT))); // recusion
        }
    }
}
TRIE::DivType::DivType(const UINT & s, const UINT & e): startOff(s), endOff(e), indices(NULL) {}

TRIE::DivType::~DivType(void)
{
    delIndices(this);
}

void TRIE::DivType::delIndices(const pDiv & d)
{
    if (d->indices == NULL) return;
    vector<pDiv>::const_iterator bIT = d->indices->begin(), eIT = d->indices->end();
    for (; bIT != eIT; ++bIT)
    {
        delIndices(*bIT); // recursion
        delete (*bIT);
    }
    d->indices->clear();
    delete d->indices;
    d->indices = NULL;
}

string TRIE::DivType::toStr(void)
{
    UINT offset = startOff, len = endOff - startOff;
    if (indices == NULL)
    { // this is a chapter, our Offs here are not offsets
        verseOff 
            & v0 = KJV::VERSES[startOff], 
            & v1 = KJV::VERSES[startOff + endOff - 1];
        offset = v0.start;
        len = v1.start + v1.len;
        len -= offset;
    }
    return string(&TXT_START + offset, len);
}


/*start, len, chapter, book, testament*/
TRIE::verseOff::verseOff(void): start(INIT_UINT), len(INIT_USHRT), chapter(INIT_UCHAR), verse(INIT_UCHAR), book(INIT_UCHAR), testament(INIT_UCHAR), sstart(INIT_UINT), slen(INIT_USHRT) {}
TRIE::verseOff::verseOff(const verseOff & a): start(a.start), len(a.len), chapter(a.chapter), verse(a.verse), book(a.book), testament(a.testament), sstart(a.sstart), slen(a.slen) {}
TRIE::verseOff::verseOff(const UINT & s, const USHRT & l, const UCHAR & c, const UCHAR & v, const UCHAR & b, const UCHAR & t, const UINT & o, const USHRT & f): 
    start(s), len(l), chapter(c), verse(v), book(b), testament(t), sstart(o), slen(f) {/*assert (l <= 0xffff);*/} // limit length to 65535 chars

TRIE::verseOff & TRIE::verseOff::operator= (const verseOff & a)
{
    start = a.start;
    len = a.len;
    chapter = a.chapter;
    verse = a.verse;
    book = a.book;
    testament = a.testament;
    sstart = a.sstart;
    slen = a.slen;
    return *this;
}


/*bool TRIE::verseOff::IsEQ(const verseOff & a) const
{
    UINT len0 = len, len1 = a.len;
    if (len0 == len1) return getPivot(a) == len0;
    return false;
}

UINT TRIE::verseOff::getPivot(const verseOff & a) const
{
    UINT i = 0, start0 = start, start1 = a.start,
        len0 = len, len1 = a.len;
    //if ((start0 == INIT_DATA) || (start1 == INIT_DATA)) return 0;
    char * c0 = &TXT_START + start0, * c1 = &TXT_START + start1;
    for (; i < _MIN(len0, len1); ++i)
    {
        if (*(c0++) != *(c1++)) return i;
    }
    return i;
}*/

string TRIE::verseOff::toStr(void)
{ // display
    return string(&TXT_START + start, len);
}

string TRIE::verseOff::allToStr(void)
{
    char sBuff[20];
    int cCt = sprintf(sBuff, "%X", start);
    string s = "start at [0x" + string(sBuff, cCt) + "]";

    cCt = sprintf(sBuff, "%d", len);
    s += " length [" + string(sBuff, cCt) + "]";

    s += " display string is [" + toStr() + "]";
    /*chapter, book, testament, lAdd, rSub*/
    cCt = sprintf(sBuff, "%d", chapter);
    s += " chapter [" + string(sBuff, cCt) + "]";
    
    cCt = sprintf(sBuff, "%d", verse);
    s += " verse [" + string(sBuff, cCt) + "]";
    
    s += " book [" + string(KJV::BOOKS_ABBR[testament][book]) + "]";
    
    s += " testament [" + string(KJV::TESTAMENTS_ABBR[testament]) + "]";
    
    cCt = sprintf(sBuff, "%X", sstart);
    s += " search start at [0x" + string(sBuff, cCt) + "]";
    
    cCt = sprintf(sBuff, "%d", slen);
    s += " search length [" + string(sBuff, cCt) + "]";

    s += " search string is [" + string(&VERSE_START + sstart, slen) + "]";

    return s;
}


/*UINT TRIE::verseOff::find(const string & s)
{
    UINT sLen = s.size();
    if (sLen == 0) return len;
    const char * c0 = &TXT_START + start;
    char first = s[0];
    for (UINT i = 0; i < len; ++i)
    {
        if (*c0 == first)
        {
            const char * c2 = c0;
            ++c0;
            UINT j = 1;
            for (; j < _MIN(sLen, len - i); ++j)
            {
                if (*(c0++) != s[j]) break;
            }
            if (j == sLen) return i;
            c0 = c2;

        }
        ++c0;
    }
    return len;
}*/



char TRIE::verseOff::getChar(UINT pos) // for search input: relative position
{
    return *(&VERSE_START + sstart + pos);
}
string TRIE::verseOff::getString(UINT off, UINT l) // for display
{
    return string(&TXT_START + off, l);

}
string TRIE::verseOff::getVerseAtPos(UINT pos) // for results list search input: position
{
    return string(&VERSE_START + sstart + pos, slen - pos);
}

UINT TRIE::verseOff::getStartDisp(void) // for display
{
    return start;
}
UINT TRIE::verseOff::getStartSrch(void)
{
    return sstart;
}
USHRT TRIE::verseOff::getLenDisp(void) 
{
    return len;
}
USHRT TRIE::verseOff::getLenSrch(void) 
{
    return slen;
}
string TRIE::verseOff::getVerse(void) // for search results
{
    return string(&VERSE_START + sstart, slen);
}
UINT TRIE::verseOff::getChapterIdx(void)
{
    return chapter;
}
UINT TRIE::verseOff::getBookIdx(void)
{
    return book;
}
Glib::ustring TRIE::verseOff::getChapterFromVerse(UINT & b, UINT & e, UCHAR & chMx) // display
{
    pDiv chDiv = KJV::DIVS->indices->at(testament)->indices->at(book)->indices->at(chapter - 1);
    chMx = chDiv->endOff;
    verseOff & v0 = KJV::VERSES[chDiv->startOff], & v1 = KJV::VERSES[chDiv->startOff + chDiv->endOff - 1];
    UINT 
        chOff0 = v0.start,
        chOff1 = v1.start + v1.len,
        l = chOff1 - chOff0;
    b = start - chOff0;
    Glib::ustring uStr = getString(chOff0, b);
    //std::cout << "Chap from Vrs:" << chOff0 << " to selected verse:" << b << " utf8 chars:" << uStr.size() << " cap:" << uStr.capacity() << "\n";
    // uStr storing byte encoding of utf8
    b = uStr.size();
    uStr = getString(start, len);
    e = b + uStr.size();
    uStr = getString(chOff0, l);
    return uStr;

}
string TRIE::verseOff::getBookTitle(void)
{
    return KJV::BOOKS_ABBR[testament][book];
}
string TRIE::verseOff::getBookTitleLong(void)
{
    return KJV::BOOKS[testament][book];
}
string TRIE::verseOff::getBookFromVerse(void)
{
    pDiv bkDiv = KJV::DIVS->indices->at(testament)->indices->at(book);
    return bkDiv->toStr();

}

//string TRIE::KJVtype::getChapterFromIdx(UINT chIdx) // input: chapter index
//{
//    UINT 
//        ch0Idx = chIdx, ch1Idx = ch0Idx + 1, chCt = CHAPTERS.size(),
//        ch0Off = CHAPTERS[ch0Idx], 
//        ch1Off = ch1Idx >= chCt? KJV_END: CHAPTERS[ch1Idx],
//        l = ch1Off - ch0Off;

//    return getString(ch0Off, l);

//}

//string TRIE::KJVtype::getBookFromIdx(UINT bkIdx) // input: book index
//{
//    UINT 
//        bk0Idx = bkIdx, bk1Idx = bk0Idx + 1, bkCt = sizeof(BOOKS),
//        bk0Off = BOOKS_OFFS[bk0Idx], 
//        bk1Off = bk1Idx >= bkCt? KJV_END: BOOKS_OFFS[bk1Idx],
//        l = bk1Off - bk0Off;

//    return getString(bk0Off, l);

//}

bool TRIE::KJVtype::isWS(char c)  // whitespace for KJV is ' ', '\r' or '\n'
{
    return (c == ' ') || (c == '\r') || (c == '\n');
}

UINT TRIE::KJVtype::getLstNonWS(UINT pos) // gets 1st non-WS before offset at input
{
    UINT lws = pos - 1;
    while (isWS(*(&TXT_START + lws))) --lws;
    return lws;
}

string TRIE::KJVtype::replaceEOLN(UINT start, UINT len)
{
    string s = string(&TXT_START + start, len), r = "";
    bool addSpace = false, setLine = false;
    char c = ' ';
    UINT eolnCt = 0;
    for (UINT i = 0; i < s.size(); ++i)
    {
        c = s[i];
        if ((c == '\r') || (c == '\n')) 
        {
            addSpace = true;
            if (c == '\r') ++eolnCt; // EOLN is \r\n so this counts as 1
        }
        else 
        {
            if (addSpace) r += ' ';
            r += c;
            addSpace = false;
            if (eolnCt > KJV::reptCount) 
            {
                KJV::reptCount = eolnCt;
                setLine = true;
            }
            eolnCt = 0;
        }
    }
    if (setLine) KJV::reptLine = r;
    return r;
}
string TRIE::KJVtype::restoreApostrophe(const string & sIn)
{
    string r = "";
    UINT sSz = sIn.size();
    for (UINT i = 0; i < sSz; ++i)
    {
        UCHAR c[3] = {static_cast<UCHAR>(sIn[i]), static_cast<UCHAR>(sIn[(i + 1) % sSz]), static_cast<UCHAR>(sIn[(i + 2) % sSz])};
        if (c[0] > 0x7f)
        {
            assert ((c[0] == 0xe2) && (c[1] == 0x80) && (c[2] == 0x99)); // translates to U+2019
            r += "'";
            i += 2;
        }
        else r += c[0];
    }
    return r;
}
void TRIE::KJVtype::parseText(void)
{ // outputs file parse.dat & verse.txt
  // w/ lo-endian UINT count of verses,
  // verse: UINT offset, USHRT len, BYTE localChapter, BYTE localVerse, BYTE book, BYTE testament, UINT offset2, USHRT len2

    TRIE::KJV::reptCount = 0;
    TRIE::KJV::reptLine = "";
    std::cout << "parsing embedded KJV.txt file\n";
    //char * txt = NULL; 
    vector<UINT> 
        offs, lens,     // these represent the interval for the displayed text
        soffs, slens;   // these are for search (they rep an interval w/in the 2nd file verse.txt)
    vector<UCHAR> chaps, verses, books, testaments;
    fstream fs;
    string fNme = "verse.txt", line = ""; // this is for debug to get the search text
    fs.open(fNme, fstream::out | fstream::binary);

    //std::cout << "writing " << fNme << "\n";

    UINT offset = KJV_START, trav = 0,
        tstNxt = TESTAMENTS_OFFS[1],
        bkNxt = BOOKS_OFFS[0][1], 
        end0 = 0, start0 = 0, start1 = 0, strOffset = 0,
        len = 0, slen = 0, adj0 = 0, adj1 = 0;
    UCHAR chap0 = 0, verse0 = 0, chap = 0, verse = 0, 
        bkIdx = 0, tstIdx = 0, replCt = 0,
        bkMax[] = {OTBK_COUNT, NTBK_COUNT},
        bkNxtIdx = 0;
    USHRT vCount = 0;
    bool ck = true, addSpace = false, atBOLN = true;
    char c = ' ', cD = ' ', * pc = &c;
    while (offset < KJV_END)
    {
        c = *(&TXT_START + offset);
        if (ck)
        {
            if (isdigit(c) > 0)
            {
                trav = offset;
                cD = c;
                chap = cD - '0';
                while (isdigit(cD) > 0) 
                {
                    cD = *(&TXT_START + (++trav));
                    if (isdigit(cD) > 0) chap = 10 * chap + (cD - '0');
                }
                if (cD == ':')
                {
                    cD = *(&TXT_START + (++trav));
                    if (isdigit(cD) > 0)
                    {
                        verse = cD - '0';
                        while(isdigit(cD) > 0)
                        {
                            cD = *(&TXT_START + (++trav));
                            if (isdigit(cD) > 0) verse = 10 * verse + (cD - '0');
                        }
                        
                        assert (isWS(cD));
                        if (cD == ' ') ++trav;
                        else trav += 2;
                        cD = *(&TXT_START + trav);
                        assert (!isWS(cD));

                        offs.push_back(offset);
                        //if ((trav - offset) > adj0) adj0 = trav - offset;
                        end0 = offset;
                        //lens.push_back(0);
                        chaps.push_back(chap);
                        verses.push_back(verse);
                        if (offset > bkNxt) 
                        { // new book
                            ++bkIdx;
                            //std::cout << ((UINT)bkIdx) << ") " << TRIE::KJV::BOOKS_ABBR[bkIdx] << " @" << soffs[vCount - 1] << "\n";
                            end0 = bkNxt;
                            if (offset > tstNxt)
                            { // this should happen once after Malachi
                                end0 = tstNxt; // - 1;
                                slen = getLstNonWS(TESTAMENTS_OFFS[2]) + 1 - start1;
                                line = restoreApostrophe(replaceEOLN(start1, slen));
                                tstNxt = KJV_END;
                                ++tstIdx;
                                bkIdx = 0; 
                            }
                            else
                            {
                                slen = getLstNonWS(bkNxt) + 1 - start1;
                                line = restoreApostrophe(replaceEOLN(start1, slen));
                            }
                            bkNxtIdx = bkIdx + 1;
                            if (((tstIdx == 0) && (bkNxtIdx >= OTBK_COUNT)) ||
                                ((tstIdx == 1) && (bkNxtIdx >= NTBK_COUNT)))
                            {
                                if  (tstIdx == 0) bkNxt = BOOKS_OFFS[1][0];
                                else bkNxt = KJV_END;
                            }
                            else bkNxt = BOOKS_OFFS[tstIdx][bkNxtIdx];
                        }
                        else if (vCount > 0) 
                        {
                            slen = getLstNonWS(offset) + 1 - start1;
                            line = restoreApostrophe(replaceEOLN(start1, slen));
                        }

                        books.push_back(bkIdx);
                        testaments.push_back(tstIdx);
                        if (start0 > 0) 
                        { // after 1st verse:
                            len = end0 - start0;
                            lens.push_back(len);
                            soffs.push_back(strOffset);
                            slens.push_back(line.size());
                            fs.write(line.data(), line.size());
                            c = '\n';
                            fs.write(pc, 1);
                            strOffset += line.size() + 1;
                        }
                        start0 = offset;
                        if ((chap > 1) && (chap > chap0)) assert(chap == (chap0 + 1)); 
                        if (verse > 1) assert(verse == (verse0 + 1));
                        chap0 = chap;
                        verse0 = verse;
                        offset = trav;
                        start1 = trav;
                        c = *(&TXT_START + offset);
                        ++vCount;
                    }
                }
            }
        }
        ck = ((c == ' ') || (c == '\n'));
        ++offset;
    }
    lens.push_back(offset - start0);
    soffs.push_back(strOffset);
    slen = getLstNonWS(offset) + 1 - start1;
    line = restoreApostrophe(replaceEOLN(start1, slen));
    slens.push_back(line.size());
    fs.write(line.data(), line.size());
    c = '\n';
    fs.write(pc, 1);

    std::cout << "max internal eoln " << reptCount << " at line " << reptLine << "\n";
    //std::cout << "max adjustments display to search on the left: " << adj0 << " and on the right: " << adj1 << "\n";
    // stream to file:
    fs.close();

    bool L2H = lo2hi();
    std::cout << "computer is " << (L2H? "lo": "hi") << "endian.\n";
    fNme = "parse.dat";
    std::cout << "writing " << vCount << " verses to file " << fNme << "\n";
    fs.open(fNme, fstream::out | fstream::binary);
    assert (sizeof(UINT) == 4);
    //if (sizeof(UINT) != 4) throw(BIBX::integer());
    USHRT i = 0, j = 0, k = 0;
    //UCHAR lAdd = 0, rSub = 0;
    char * fw = reinterpret_cast<char *>(&vCount); if (!L2H) fw += 1;
    for (k = 0; k < 2; ++k) 
    { // 2 byte UINT
        fs.write(fw, 1); 
        if (L2H) ++fw;
        else --fw;
    }

    for (i = 0; i < vCount; ++i)
    {
        offset = offs[i];
        len = lens[i];
        chap0 = chaps[i];
        verse0 = verses[i];
        bkIdx = books[i];
        tstIdx = testaments[i];
        strOffset = soffs[i];
        slen = slens[i];

        fw = reinterpret_cast<char *>(&offset); 
        if (!L2H) fw += 3;
        for (k = 0; k < 4; ++k) 
        { // 4 byte UINT
            fs.write(fw, 1);
            if (L2H) ++fw;
            else --fw;
        }

        fw = reinterpret_cast<char *>(&len); 
        if (!L2H) fw += 3;
        for (k = 0; k < 2; ++k) 
        { // 2 byte USHRT
            fs.write(fw, 1);
            if (L2H) ++fw;
            else --fw;
        }

        fw = reinterpret_cast<char *>(&chap0); 
        fs.write(fw, 1);

        fw = reinterpret_cast<char *>(&verse0); 
        fs.write(fw, 1);

        fw = reinterpret_cast<char *>(&bkIdx); 
        fs.write(fw, 1);

        fw = reinterpret_cast<char *>(&tstIdx); 
        fs.write(fw, 1);

        fw = reinterpret_cast<char *>(&strOffset); 
        if (!L2H) fw += 3;
        for (k = 0; k < 4; ++k) 
        { // 4 byte UINT
            fs.write(fw, 1);
            if (L2H) ++fw;
            else --fw;
        }

        fw = reinterpret_cast<char *>(&slen); 
        if (!L2H) fw += 3;
        for (k = 0; k < 2; ++k) 
        { // 2 byte USHRT
            fs.write(fw, 1);
            if (L2H) ++fw;
            else --fw;
        }

    }
    fs.close();
    std::cout << fNme << " written to working directory.\nMove to resource directory & re-run program normally.\n";
}

void TRIE::KJVtype::getNonASCII(void)
{
    string acc = ""; //, conv = "";
    //string buff = "";

    char sBuff[20];
    int cCt = 0; //sprintf(sBuff, "%X", start);
    string s = ""; //"start at [0x" + string(sBuff, cCt) + "]";

    UINT offset = KJV_START, len = 0;
    while (offset < KJV_END)
    {
        UCHAR c = *(&TXT_START + offset);
        if (c > 0x7f)
        {
            cCt = sprintf(sBuff, "%X", offset);
            s = "@[0x" + string(sBuff, cCt) + "]{0x";
            cCt = sprintf(sBuff, "%X", c);
            s += string(sBuff, cCt) + " ";
            c = *(&TXT_START + (++offset));
            while (c > 0x7f)
            {
                cCt = sprintf(sBuff, "%X", c);
                s += string(sBuff, cCt) + " ";
                c = *(&TXT_START + (++offset));
            }
            s = s.substr(0, s.size() - 1);
            acc +=  s + "} ";
        }
        ++offset;
    }
    std::cout << "nonASCII characters in the KJV text file:\n";
    std::cout << acc;
    std::cout << "\n";
}

TRIE::trieStr::trieStr(void): vIdx(INIT_USHRT), bPos(INIT_USHRT), ePos(INIT_USHRT) {}
TRIE::trieStr::trieStr(const char & c): vIdx(CHAR_IDX), bPos(c), ePos(INIT_USHRT) {assert (c < 0x80);/**/}
TRIE::trieStr::trieStr(const trieStr & a): vIdx(a.vIdx), bPos(a.bPos), ePos(a.ePos) {}
TRIE::trieStr::trieStr(const USHRT & v, const USHRT & b, const USHRT & e): vIdx(v), bPos(b), ePos(e) {}

//UINT TRIE::trieStr::verseIdx(void) const 
//{ // probably shouldn't use this as it redoes what KJV functions already do
//    UINT vIdx = 0x7fff & data;
//    return vIdx;
//}
TRIE::verseOff TRIE::trieStr::verse(void) const
{
    //UINT vIdx = verseIdx();
    assert ((vIdx != INIT_USHRT) && (vIdx != CHAR_IDX));
    return KJV::VERSES[vIdx];    
}
USHRT TRIE::trieStr::len(void) const 
{ // len at bits 15 - 24
    //UINT l = (0x1ff8000 & data) >> LEN_LO_BIT;
    return ePos - bPos;
}
UINT TRIE::trieStr::start(void) const 
{ // probably shouldn't use this as it redoes what KJV functions already do
    verseOff v = verse();
    UINT 
        s0 = v.getStartSrch(),
        //l0 = v.getLenSrch(),
        //l1 = len(),
        s = s0 + bPos;
    return s;
}
//UINT TRIE::trieStr::getData(const UINT & vIdx, const UINT & len) 
//{
//    verseOff v = KJV::VERSES[vIdx];
//    char c = len == 0? END_CHR: v.getChar(len);
//    assert(c < 0x80);
    //assert (c != '\n'); // no LFs
    //if (c == '\r') c = ' ';  // replace CR w/ space
//    UINT d = (c << CHAR_LO_BIT) | (len << LEN_LO_BIT) | vIdx;
//    return d;
//}
char TRIE::trieStr::getChar(void) const
{
    if (vIdx == CHAR_IDX) return static_cast<char>(0x7F & bPos);
    if (bPos == ePos) return END_CHR;
    verseOff v = verse();
    return v.getChar(bPos);
}

//TRIE::trieStr::trieStr(const UINT & l): data(getData(l)) 
//{
    //assert (l < 0x80); // limit length to 127 chars
//}

TRIE::trieStr & TRIE::trieStr::operator = (const trieStr & a)
{
    //data = a.data;
    vIdx = a.vIdx;
    bPos = a.bPos;
    ePos = a.ePos;
    return *this;
}

bool TRIE::trieStr::IsEQ(const trieStr & a) const
{
    UINT len0 = len(), len1 = a.len(),
        vIdx0 = vIdx, vIdx1 = a.vIdx;
    char c0 = getChar(), c1 = a.getChar();
    //if (caseInsensitive)
    //{
    //    c0 = toupper(c0);
    //    c1 = toupper(c1);
    //}
    if ((vIdx0 == CHAR_IDX) || (vIdx1 == CHAR_IDX) || (len0 <= 1) || (len1 <= 1)) return (c0 == c1);
    if (len0 == len1) return getPivot(a) == len0;
    return false;
}

bool TRIE::trieStr::IsLT(const trieStr & a) const
{
    UINT i = 0, len0 = len(), len1 = a.len(), m = _MIN(len0, len1),
        vIdx0 = vIdx, vIdx1 = a.vIdx;
    char c0 = getChar(), c1 = a.getChar();
    //if (caseInsensitive)
    //{
    //    c0 = toupper(c0);
    //    c1 = toupper(c1);
    //}
    if ((vIdx0 == CHAR_IDX) || (vIdx1 == CHAR_IDX) || (len0 <= 1) || (len1 <= 1)) return (c0 < c1);
    UINT start0 = start(), start1 = a.start();
    const char * pc0 = &VERSE_START + start0, * pc1 = &VERSE_START + start1;
    for (; i < m; ++i)
    {
        if (*pc0 != *pc1) break;
        ++pc0;
        ++pc1;
    }
    if (i == m) return len0 < len1;
    return *pc0 < *pc1;
}

string TRIE::trieStr::toStr(void)
{
    if (vIdx == INIT_USHRT) return "string not actualized";
    if (vIdx == CHAR_IDX) return string(1, getChar());
    verseOff v = verse();
    return string(&VERSE_START + v.sstart + bPos, len());
}

string TRIE::trieStr::toLStr(void)
{
    string s = toStr(), r = "";
    for (UINT i = 0; i < s.size(); ++i)
    {
        char c = s[i];
        r += tolower(c);
    }
    return r;
}

string TRIE::trieStr::allToStr(void)
{
    string s = "verse [" + to_string(vIdx) + "] at 1st char[" + string(1, getChar()) + "] ";
    char sBuff[20];
    int cCt = sprintf(sBuff, "%X", start());
    s += "starting at [" + string(sBuff, cCt) + "]";
    cCt = sprintf(sBuff, "%X", len());
    s += " length [" + string(sBuff, cCt) + "]";
    s += " string is [" + toStr() + "]";
    return s;
}

/*char TRIE::trieStr::getNextSearchChar(UINT & len0) const
{
    verseOff & v = verse();
    char c = ' ';
    if (len0 == 0) return END_CHR;
    --len0;
    if (len0 == 0) return END_CHR;
    c = v.getChar(len0);
    if (c == '\r') return ' ';
    if (c == '\n')
    { // skip all returns
        while (len0 > 0)
        {
            --len0;
            c = v.getChar(len0);
            if ((c != '\n') && (c != '\r')) break;
        }
    }
    if (len0 == 0) return END_CHR;
    return c;
}*/


UINT TRIE::trieStr::getPivot(const trieStr & a) const
{
    UINT i = 0, start0 = start(), start1 = a.start(),
        len0 = len(), len1 = a.len(), m = _MIN(len0, len1),
        vIdx0 = vIdx, vIdx1 = a.vIdx;
    //if ((vIdx0== INIT_USHRT) || (vIdx1 == INIT_USHRT)) return 0; // at least one not actualized
    const char * c0 = &VERSE_START + start0, * c1 = &VERSE_START + start1; 
    for (; i < m; ++i)
    {
        if (*(c0++) != *(c1++)) return i;
    }
    return i;
}
        
UINT TRIE::trieStr::getPivot(const char *& a, const UINT strLen) const
{
    UINT i = 0, start0 = start(), len0 = len(),
        m = _MIN(len0, strLen), vIdx0 = vIdx;
    //if (vIdx0 == INIT_USHRT) return 0;
    const char * c0 = &VERSE_START + start0, * c1 = a;
    for (; i < m; ++i)
    {
        if (*(c0++) != *(c1++)) return i;
    }
    return i;
}

UINT TRIE::trieStr::find(const char *& a, const UINT slen) 
{
    UINT start0 = start(), len0 = len();
    const char * c0 = &VERSE_START + start0, * c1 = a;
    for (UINT i = 0; i < len0; ++i)
    {
        if (*c0 == *c1)
        {
            const char * c2 = c0;
            ++c0; 
            ++c1;
            UINT j = 1;
            for (; j < _MIN(slen, len0 - i); ++j)
            {
                if (*(c0++) != *(c1++)) break;
            }
            if (j == slen) return i;
            c0 = c2;
            c1 = a;
        }
        ++c0;
    }
    return len0;
}

UINT TRIE::trieStr::find(const string & s)
{
    UINT sLen = s.size(), start0 = start(), len0 = len();
    if (sLen == 0) return len0;
    const char * c0 = &VERSE_START + start0;
    char first = s[0];
    for (UINT i = 0; i < len0; ++i)
    {
        if (*c0 == first)
        {
            const char * c2 = c0;
            ++c0;
            UINT j = 1;
            for (; j < _MIN(sLen, len0 - i); ++j)
            {
                if (*(c0++) != s[j]) break;
            }
            if (j == sLen) return i;
            c0 = c2;

        }
        ++c0;
    }
    return len0;
}

void TRIE::trieStr::advance(const UINT & i)
{ // alters this trieStr
    UINT len0 = len();
    if (len0 < i) throw(BIBX::advance());
    bPos += i;
    //data = getData(vIdx, len0);
}

void TRIE::trieStr::toLast(void)
{ // alters this trieStr
    UINT len0 = len();
    if (len0 == 0) throw(BIBX::advance());
    bPos = ePos;
    //data = getData(vIdx, len0);

}

void TRIE::trieStr::toNext(void)
{ // alters this trieStr
    verseOff v = verse();
    UINT len0 = len();
    if (len0 == 0) throw(BIBX::advance());
    ++bPos;
    //data = getData(vIdx, len0);

}

//char TRIE::trieStr::getChar(const UINT & i) const 
//{
//    UINT vIdx0 = verseIdx(), len0 = len();
//    if (len0 == 0) return END_CHR;
//    if (i >= len0) throw(BIBX::get_char());
//    if (i == 0) return getChar();
//    return KJV::getChar(vIdx0, len0); 
//}


TRIE::trieEdge::trieEdge(void): pfx(trieStr()), sfx(INIT_UINT) {}
TRIE::trieEdge::trieEdge(const trieEdge & a): pfx(a.pfx), sfx(a.sfx), indices(a.indices) {}
TRIE::trieEdge::trieEdge(const char & c): pfx(trieStr(c)), sfx(INIT_UINT) {}
TRIE::trieEdge::trieEdge(const trieStr & s): pfx(s), sfx(INIT_UINT) {indices.push(s.vIdx);}
TRIE::trieEdge::trieEdge(const trieStr & p, const UINT & s): pfx(p), sfx(s) {indices.push(p.vIdx);}
//TRIE::trieEdge::trieEdge(const trieStr & p, const trieNode & s): pfx(p), sfx(TRIE_NODES.size()) {TRIE_NODES.push_back(s);}
TRIE::trieEdge::~trieEdge(void) {}
TRIE::trieEdge & TRIE::trieEdge::operator =(const trieEdge & a)
{
    pfx = a.pfx;
    sfx = a.sfx;
    indices = a.indices;
    return *this;
}
bool TRIE::trieEdge::IsEQ(const trieEdge & a) const {return pfx == a.pfx;}
bool TRIE::trieEdge::IsLT(const trieEdge & a) const {return pfx < a.pfx;}
bool TRIE::trieEdge::findChar(char c)
{
    if (pfx.len() > 0)
    {
        if (pfx.getChar() == c)
        {
            pfx.toNext();
            return true;
        }
        return false;
    }
    if (sfx == INIT_UINT) return false;
    trieEdge e = trieEdge(c);
    UINT dIdx = 0;
    //trieTree::TRIE_NODES[sfx].printAVL();
    if (trieTree::TRIE_NODES[sfx].getEdge(e, dIdx))
    {
        *this = e;
        pfx.toNext();
        return true;
    }
    return false;
}

bool TRIE::trieEdge::findAny(vector<trieEdge> & eVec)
{
    eVec.clear();
    if (pfx.len() > 0)
    {
        eVec.push_back(*this);
        return true;
    }
    else
    {
        if (sfx == INIT_UINT) return false;
        else
        {
            eVec = trieTree::TRIE_NODES[sfx].getEdges();
            return eVec.size() > 0;
        }
    }
}

bool TRIE::trieEdge::findAny1(vector<trieEdge> & eVec)
{
    eVec.clear();
    if (pfx.len() > 0)
    {
        trieEdge e = *this;
        e.pfx.toNext();
        if (pfx.len() > 0)
        {
            eVec.push_back(e);
            return true;
        }
        else
        {
            if (sfx == INIT_UINT) return false;
            else
            {
                eVec = trieTree::TRIE_NODES[sfx].getEdges();
                return eVec.size() > 0;
            }
        }
    }
    else
    {
        if (sfx == INIT_UINT) return false;
        else
        {
            eVec = trieTree::TRIE_NODES[sfx].getEdges1();
            return eVec.size() > 0;
        }
    }

}

bool TRIE::trieEdge::findEnd(void)
{ // sets this edge to the appropriate edge for offset searching if end is found
    if (pfx.len() > 0) return false;
    if (sfx != INIT_UINT)
    {
        trieEdge e = trieEdge(trieStr::END_CHR);
        UINT dIdx = 0;
        if (!trieTree::TRIE_NODES[sfx].getEdge(e, dIdx)) return false;
        *this = e;
    }
    return true;
}

bool TRIE::trieEdge::atEnd(void)
{
    return (pfx.len() == 0) && (sfx == INIT_UINT);
}

bool TRIE::trieEdge::actualized(void) const
{
    return pfx.vIdx != INIT_USHRT;
}

void TRIE::trieEdge::add_idxs(vector<USHRT> & res)
{
    //map<UINT, vector<UINT>>::iterator 
    //    iIT = TRIE::OFFS.lower_bound(pfx.start());
    //offsetLU oLU = offsetLU(pfx.start());
    //UINT dIdx = 0;
    //bool foundLE = getOFFS().GetLE(oLU, dIdx);
    //if (!foundLE) throw(BIBX::offset_not_found());
    //vector_oat<UINT, UCHAR>
    //    & iVec = oLU.indices; // iIT->second;
    for (UCHAR i = 0; i < indices.size(); ++i)
    {
        res.push_back(indices[i]);
    }

}

void TRIE::trieEdge::add_tree(vector<USHRT> & res)
{
    if (pfx.len() > 0) pfx.toLast();
    if (sfx == INIT_UINT) add_idxs(res);
    else
    {
        vector<trieEdge> any;
        findAny(any);
        for (UINT i = 0; i < any.size(); ++i)
        {
            any[i].add_tree(res);
        }
    }

}

void TRIE::trieEdge::search(
        const trieEdge & swcPTR,
        vector<USHRT> & res, 
        const char *& patt, 
        const unsigned char pattLEN, 
        unsigned char pattIDX, 
        unsigned char wcIDX)
{
    if (pattLEN == 0) return;
    vector<trieEdge> any;
    trieEdge a;
    UINT i;

    char c = patt[pattIDX];


    //std::cout << "@[" << c << "] sz[" << static_cast<UINT>(indices.size()) << "] [";
    //for (i = 0; i < indices.size(); ++i) std::cout << indices[i] << " ";
    //std::cout << "] sfx [" << sfx << "] pfx[" << pfx.toStr() << "]\n"; 
    

    if (pattLEN == pattIDX)
    {
        if (patt[pattLEN - 1] == trieStr::S_WC) add_tree(res);
        else if (findEnd()) add_idxs(res);
    }
    else
    {
        if (findChar(c))
        {
            search(swcPTR, res, patt, pattLEN, pattIDX + 1, wcIDX);
        }
        else if (c == trieStr::C_WC)
        {
            if (findAny1(any))
            {
                for (i = 0; i < any.size(); ++i)
                {
                    *this = any[i];
                    search(swcPTR, res, patt, pattLEN, pattIDX + 1, wcIDX);
                }
            }
        }
        else if (c == trieStr::S_WC)
        {
            if (findAny(any))
            {
                for (i = 0; i < any.size(); ++i)
                {
                    *this = any[i];
                    search(any[i], res, patt, pattLEN, pattIDX + 1, pattIDX);
                }
            }
        }
        else if (swcPTR.actualized())
        {
            *this = swcPTR;
            if (findAny1(any))
            {
                for (i = 0; i < any.size(); ++i)
                {
                    *this = any[i];
                    search(any[i], res, patt, pattLEN, wcIDX + 1, wcIDX);
                }
            }
        }
        else return;
    }
}

void TRIE::trieEdge::add_idx(const USHRT & dup)
{
    indices.push(dup);
    ++KJV::dupCount;
}


TRIE::trieNode::trieNode(void): avlID(INIT_UINT) {}
TRIE::trieNode::trieNode(const trieNode & a): avlID(a.avlID) {} // pointer copy only
TRIE::trieNode::~trieNode(void) {}

/*void TRIE::trieNode::delEdges(void)
{
    if (edges != NULL)
    {
        vector<trieEdge> eVec;
        edges->getAll(eVec);
        UINT eSz = eVec.size();
        for (UINT i = 0; i < eSz; ++i)
        {
            trieEdge e = eVec[i];
            if (e.sfx != NULL) e.sfx->delEdges();
        }
        //edges->clear();
        delete edges;
        edges = NULL;
    }
}*/

bool TRIE::trieNode:: getEdge(trieEdge & e, UINT & dIdx)
{
    if (avlID == INIT_UINT) return false;
    return getEdgeAVL(avlID).findData(e, dIdx);

}

vector<TRIE::trieEdge> TRIE::trieNode::getEdges(void)
{
    vector<trieEdge> r;
    if (avlID == INIT_UINT) return r;
    getEdgeAVL(avlID).getAll(r);
    //for (map<char, trieEdge>::iterator eIT = edges->begin(); eIT != edges->end(); ++eIT) r.push_back(eIT->second);
    return r;
}

vector<TRIE::trieEdge> TRIE::trieNode::getEdges1(void)
{
    vector<trieEdge> eVec0, eVec1;
    if (avlID == INIT_UINT) return eVec0;
    getEdgeAVL(avlID).getAll(eVec0);
    UINT eSz = eVec0.size();
    for (UINT i = 0; i < eSz; ++i)
    {
        trieEdge e = eVec0[i];
        if (!e.atEnd()) 
        {
            e.pfx.toNext(); // will this update the vector element?
            eVec1.push_back(e);
        }
    }
    return eVec1;
}

void TRIE::trieNode::add_idx(const UINT & primary, const UINT & dup)
{ // primary and dup are offsets


    //std::cout << ++(KJV::reptCount) << ") duplicate detected between verses [" << 
    //    KJV::VERSES[primary].toStr() << " & " << 
    //    KJV::VERSES[dup].toStr() << "]\n";
    //map<UINT, vector<UINT>>::iterator 
    //    pIT = TRIE::OFFS.lower_bound(primary),
    //    dIT = TRIE::OFFS.lower_bound(dup);
    /*offsetLU oLUp = offsetLU(primary), oLUd = offsetLU(dup);
    UINT dIDXp = 0, dIDXd = 0;
    bool foundPrimary = getOFFS().GetLE(oLUp, dIDXp), foundDup = getOFFS().GetLE(oLUd, dIDXd);
    if ((!foundPrimary) || (!foundDup)) throw(BIBX::offset_not_found());
    vector_oat<UINT, UCHAR>
        pVec = oLUp.indices, //pIT->second,
        dVec = oLUd.indices; //dIT->second;
    if (dVec.size() > 1) throw(BIBX::duplicate_indices());  // duplicate should only ever have it's own index in the vector
                                // the only time it will be looked up is once here
    UINT dIdx = dVec[0];
    
    pVec.push(dIdx);
    OFFS->data_store[dIDXp].indices = pVec;
    ++reptCount;*/
    //UINT * start = OFFS2.GetLE(primary);
    //std::cout << "in add_idx AVL start[" << *start << "] map start[" << WORDS[pVec[0]].start() << "]\n";
    //static UINT dupCt = 0;
    //if (pVec.size() == 2)
    //{
    //    std::cout << "[" << dupCt << "] duplicates found for " << TRIE::WORDS[pVec[0]].toStr() << "\n";
    //    ++dupCt;
    //}
}

void TRIE::trieNode::insert(trieEdge eIn)
{
    trieEdge eBuff; // = trieEdge(s);
    ptrieEdge p = NULL;
    //ptrieNode nd = NULL;
    UINT pvt = 0u, nodeIdx = 0u, dataIdx = 0u;
    char f = ' ';
    bool iChk = false;

    //std::cout << "|" << avlID << " " << eIn.pfx.toStr() << "|";
    if (eIn.pfx.len() == 0)
    { 
        eBuff = trieEdge(trieStr::END_CHR);
        if (getEdge(eBuff, dataIdx)) EDGE_NEXUS->data_store[dataIdx].add_idx(eIn.pfx.vIdx); // duplicate string detected
        else
        { // inserting end of string:
            if (avlID == INIT_UINT) avlID = EDGE_NEXUS->getNext(); //edges = new AVL<trieEdge, UCHAR>; //map<char, trieEdge>;
            p = &eIn;
            iChk = getEdgeAVL(avlID).Insert(p, dataIdx); assert(iChk);
            if (!iChk) throw(BIBX::insert());
            ++KJV::edgeCount;
            //std::cout << "l";
        }
    }
    else
    {
        f = eIn.pfx.getChar();
        eBuff = trieEdge(f);
        if (getEdge(eBuff, dataIdx))
        { // eBuff is the edge beginning with f so parse eIn.pfx with eBuff.pfx:
            pvt = eIn.pfx.getPivot(eBuff.pfx);
            if (pvt == 0) throw(BIBX::pivot());
            if ((eBuff.sfx == INIT_UINT) || (pvt < eBuff.pfx.len()))
            { // prefix needs to be divided:
                nodeIdx = trieTree::TRIE_NODES.size(); trieTree::TRIE_NODES.push_back(trieNode()); ++KJV::nodeCount;

                // old node cleanup eBuff in the store:
                EDGE_NEXUS->data_store[dataIdx].pfx.ePos = eBuff.pfx.bPos + pvt;
                EDGE_NEXUS->data_store[dataIdx].sfx = nodeIdx;

                // new node inserts:
                eIn.pfx.advance(pvt);
                eBuff.pfx.advance(pvt);
                trieTree::TRIE_NODES[nodeIdx].insert(eBuff); //trieStr(e.pfx.start() + pvt, e.pfx.len() - pvt), e.sfx);
                trieTree::TRIE_NODES[nodeIdx].insert(eIn); //trieStr(s.start() + pvt, s.len() - pvt));


            }
            else
            { // pvt should equal pfx.len which is probably 1 here
                if (pvt != eBuff.pfx.len()) throw(BIBX::pivot());
                eIn.pfx.advance(pvt);
                trieTree::TRIE_NODES[eBuff.sfx].insert(eIn); //trieStr(s.start() + pvt, s.len() - pvt));
            }
        }
        else
        { // no edge begins with f so add eIn:
            if (avlID == INIT_UINT) avlID = EDGE_NEXUS->getNext(); //edges = new AVL<trieEdge, UCHAR>; //map<char, trieEdge>;
            //(*edges)[f] = trieEdge(s);
            p = &eIn; //e = trieEdge(s); // e initialized w/ trieStr s above
            iChk = getEdgeAVL(avlID).Insert(p, dataIdx); assert(iChk);
            if (!iChk) throw(BIBX::insert());
            ++KJV::edgeCount;
            //if (((f == 'W') || (f == 'T') || (f == 'U')) && (avlID == 0)) 
            //{
            //    std::cout << "char is " << f << " ";
            //    printAVL();
            //}
            //std::cout << "+";
        }
    }
}

void TRIE::trieNode::printAVL(void)
{
    std::cout << "AVL[" << avlID << "] ";
    if (avlID == INIT_UINT) 
    {
        std::cout << "tree is empty.\n";
        return;
    }
    vector<trieEdge> eVec;
    vector<UINT> nVec;
    getEdgeAVL(avlID).getAllWith(eVec, nVec);

    std::cout << "tree contains [" << eVec.size() << "] nodes. Here are the first characters: <";
    for (UINT i = 0; i < eVec.size(); ++i)
    {
        char c = eVec[i].pfx.getChar();
        USHRT l = eVec[i].pfx.len();
        if (c < 10) std::cout << "\\" << static_cast<UINT>(c);
        else std::cout << " " << c;
        std::cout << "[" << l << ", " << nVec[i] << "]";
    }
    std::cout << ">\n";
}

/*void TRIE::trieNode::insert(const trieStr & s, const UINT & n)
{
    if (avlID == INIT_UINT) avlID = EDGE_NEXUS->getNext(); //edges = new AVL<trieEdge, UCHAR>; //map<char, trieEdge>;
    //char f = s.getChar(0);
    //if (s.len() == 0) f = END_CHR;

    trieEdge e = trieEdge(s, n);
    ptrieEdge p = &e;
    bool iChk = getEdgeAVL(avlID).Insert(p);
    assert(iChk);
    
    //pair<map<char, trieEdge>::iterator, bool> ret =
    //    edges->insert( pair<char, trieEdge>(f, trieEdge(s)));

    //assert (ret.second);
    //ret.first->second.sfx = n;
    ++edgeCount;
}*/

UINT TRIE::trieNode::getAVLsize(void)
{
    if (avlID == INIT_UINT) return 0;
    return getEdgeAVL(avlID).Size();
}

AVL<TRIE::trieEdge> & TRIE::trieNode::getEdgeAVL(const UINT & i)
{
    return *EDGE_NEXUS->avl_store[i];
}

TRIE::trieTree::trieTree(void)
{
    KJV::nodeCount = 0;
    KJV::edgeCount = 0;
    KJV::reptCount = 0;
    KJV::dupCount = 0;
    root = 0;
    getData();
    //testDelete();
}

TRIE::trieTree::~trieTree(void) 
{
    if (trieNode::EDGE_NEXUS != NULL) delete trieNode::EDGE_NEXUS;
    trieNode::EDGE_NEXUS = NULL;
    if (KJV::DIVS != NULL) delete KJV::DIVS;
    KJV::DIVS = NULL;

    TRIE_NODES.clear();
}

void TRIE::trieTree::getData(void)
{ // uses data from parse.dat to initialize data structures root, KJV::VERSES and KJV::CHAPTERS
  // file structure is: lo-endian UINT count of verses,
  // verse: UINT offset, USHRT len, BYTE localChapter, BYTE localVerse, BYTE book, BYTE testament, BYTE lAdd, BYTE rSub


    TRIE_NODES.clear();
    TRIE_NODES.push_back(trieNode());
    ++KJV::nodeCount;

    KJV::VERSES.clear();

    if (KJV::DIVS != NULL) delete KJV::DIVS;
    KJV::DIVS = new Div(KJV::KJV_START, KJV::KJV_END); // top division representing the whole KJV bible
    pDiv & div0 = KJV::DIVS;
    div0->indices = new vector<pDiv>;
    div0->indices->push_back(new Div(KJV::TESTAMENTS_OFFS[0], KJV::TESTAMENTS_OFFS[1]));
    div0->indices->push_back(new Div(KJV::TESTAMENTS_OFFS[1], KJV::KJV_END));
    pDiv tDivs[] = {div0->indices->at(0), div0->indices->at(1)};
    UINT bksPerTestament[] = {OTBK_COUNT, NTBK_COUNT};
    for (UINT i = 0; i < 2; ++i)
    {
        tDivs[i]->indices = new vector<pDiv>;
        for (UINT j = 0; j < bksPerTestament[i]; ++j)
        {
            UINT bkOffNxt = KJV::KJV_END;
            if ((j + 1) < bksPerTestament[i]) bkOffNxt = KJV::BOOKS_OFFS[i][j + 1];
            else if (i == 0) bkOffNxt = KJV::TESTAMENTS_OFFS[2]; // position of asterisks between testaments
            tDivs[i]->indices->push_back(new Div(KJV::BOOKS_OFFS[i][j], bkOffNxt));
        }
    }

    if (trieNode::EDGE_NEXUS != NULL) delete trieNode::EDGE_NEXUS;
    trieNode::EDGE_NEXUS = new avlNexus<trieEdge>;

    //trieStr tStr;
    //string firstChars = "";

    bool L2H = lo2hi();
    //std::cout << "computer is " << (L2H? "little": "big") << "endian\n";
    UINT 
        testIdx = 0, 
        bkIdx = 0, 
        start = 0, //start0 = 0, 
        sstart = 0;
    USHRT 
        vCount = 0, 
        len = 0, slen = 0,
        i = 0, j = 0, k = 0;
        //len0 = 0;
    UCHAR 
        chap = 0, vrs = 0, bk = 0, tst = 0, //ladd = 0, rsub = 0,
        chap0 = 0, vrs0 = 0, bk0 = 0, tst0 = 0, //ladd0 = 0, rsub0 = 0,
        maxVerse = 0, maxChap = 0, maxBk = 0, maxTst = 0;
    char 
        * dat = &DATA_START, * rd = reinterpret_cast<char *>(&vCount),
        * rd_start = reinterpret_cast<char *>(&start),
        * rd_len = reinterpret_cast<char *>(&len),
        * rd_chap = reinterpret_cast<char *>(&chap),
        * rd_vrs = reinterpret_cast<char *>(&vrs),
        * rd_bk = reinterpret_cast<char *>(&bk),
        * rd_tst = reinterpret_cast<char *>(&tst),
        * rd_sstart = reinterpret_cast<char *>(&sstart),
        * rd_slen = reinterpret_cast<char *>(&slen);
    
    if (!L2H)
    {
        rd += 1; rd_start += 3; rd_len += 1; rd_sstart += 3; rd_slen += 1;
    }
    for (k = 0; k < 2; ++k) 
    { // 2 bytes
        *rd = *(dat++);
        if (L2H) ++rd;
        else --rd;
    }
    //std::cout << vCount << " verses in data.\n";
    for (i = 0; i < vCount; ++i)
    {
        rd = rd_start; 
        for(k = 0; k < 4; ++k) 
        { // 4 bytes
            *rd = *(dat++);
            if (L2H) ++rd;
            else --rd;
        }
        
        rd = rd_len; 
        for(k = 0; k < 2; ++k) 
        { // 2 bytes
            *rd = *(dat++);
            if (L2H) ++rd;
            else --rd;
        }

        rd = rd_chap; *rd = *(dat++);
        rd = rd_vrs; *rd = *(dat++);
        rd = rd_bk; *rd = *(dat++);
        rd = rd_tst; *rd = *(dat++);
        
        rd = rd_sstart; 
        for(k = 0; k < 4; ++k) 
        { // 4 bytes
            *rd = *(dat++);
            if (L2H) ++rd;
            else --rd;
        }
        
        rd = rd_slen; 
        for(k = 0; k < 2; ++k) 
        { // 2 bytes
            *rd = *(dat++);
            if (L2H) ++rd;
            else --rd;
        }

        verseOff v = verseOff(start, len, chap, vrs, bk, tst, sstart, slen);
        KJV::VERSES.push_back(v);
        //firstChars += *(&VERSE_START + sstart);
        //std::cout << i << ") " << v.allToStr() << "\n";
        //tStr.data = trieStr::getData(i, slen);
        TRIE_NODES[0].insert(trieEdge(trieStr(i, 0u, slen)));
        if ((chap != chap0) || (bk != bk0) || (tst != tst0))
        { // set up new chapter in DIVS
            pDiv cdiv = KJV::DIVS->indices->at(tst)->indices->at(bk);
            if (cdiv->indices == NULL)
            {
                assert (chap == 1);
                cdiv->indices = new vector<pDiv>;
            }
            cdiv->indices->push_back(new Div(i, INIT_UINT));
            if (i > 0)
            { // finalize previous chapter
                pDiv prvdiv = KJV::DIVS->indices->at(tst0)->indices->at(bk0)->indices->at(chap0 - 1);
                assert (prvdiv->indices == NULL); // indices shall be NULL for all chapter DIVs
                prvdiv->endOff = i - prvdiv->startOff; // a count of verses in this chapter DIV
            }
        }
        chap0 = chap;
        bk0 = bk;
        tst0 = tst;
        if (vrs > maxVerse) 
        {
            maxVerse = vrs;
            maxChap = chap;
            maxBk = bk;
            maxTst = tst;
        }
    }
    // fixing the final chapter div:
    pDiv prvdiv = KJV::DIVS->indices->at(tst0)->indices->at(bk0)->indices->at(chap0 - 1);
    assert (prvdiv->indices == NULL); // indices shall be NULL for all chapter DIVs
    prvdiv->endOff = i - prvdiv->startOff; // a count of verses in this chapter DIV
    //std::cout << "max verse [" << to_string(maxVerse) << "] in book [" << KJV::BOOKS_ABBR[maxTst][maxBk] << "] chapter [" << to_string(maxChap) << "]\n";
    //std::cout << "the first characters in the verses are:\n" << firstChars << "\n";
    //std::cout << "nodeCount = [" << KJV::nodeCount << "] edgeCount = [" << KJV::edgeCount << "] dupCount = [" << KJV::dupCount << "]\n";
}

string TRIE::trieTree::debug_pattern(const Glib::ustring & sIn)
{ // replaces strings of string wildcase characters with one
  // E.G. HI%%%%%%%%there%%%%%%% will become HI%there% if the string wildcard character is %
    
    string rebuild = "";
    UINT i = 0, pSz = sIn.size(), j = 0;
    while (i < pSz)
    {
        char c = sIn[i]; //toupper(sIn[i]); // all words in the dictionary are upper case
        if (c == trieStr::S_WC)
        {
            while((i < pSz) && (sIn[i + 1] == trieStr::S_WC)) ++i;
        }
        rebuild += c;
        ++i;
    }
    return rebuild;
}

void TRIE::trieTree::search(void)
{
    trieEdge e, swcPOS;
    const char * test = pattern.c_str();
    unsigned char ptt_len = pattern.size(), ptt_idx = 0, swc_pos = 0;
    results.clear();
    //wrdvec.clear();
    resultString = "";
    e.sfx = root;
    e.search(swcPOS, results, test, ptt_len, ptt_idx, swc_pos);

    UINT rSz = results.size(), vrsWdth = 0, chapWdth = 0;
    //std::cout << rSz << " search results w/ pattern[" << test << "]\n";
    //e.sfx = NULL;
    //swcPOS.sfx = NULL;
    string s = "", ref = "";
    for (UINT i = 0; i < rSz; ++i)
    {
        verseOff v = KJV::VERSES[results[i]];
        char tst = KJV::TESTAMENTS_ABBR[v.testament][0];
        s = tolower(tst);
        s += ' ';
        s += KJV::BOOKS_ABBR[v.testament][v.book];
        vrsWdth = log10f(v.verse) + 1;
        chapWdth = log10f(v.chapter) + 1;
        ref = string(3 - chapWdth, ' ');
        ref += to_string(v.chapter);
        ref += ':';
        ref += to_string(v.verse);
        ref += string(3 - vrsWdth, ' ');
        s += ' ' + ref + ' ';
        s += v.getVerse();
        //wrdvec.push_back(s);
        resultString += s;
        resultString += "\n";
    }
    //std::cout << "done string.\n";
    //for (UINT i = 0; i < results.size(); ++i)
    //{
    //    vector<UINT> & idxs = results[i];
    //    for (UINT j = 0; j < idxs.size(); ++j)
    //    {
    //        std::cout << "[" << i << "-" << j << "] " << WORDS[idxs[j]].toStr() << " {" << ENTRIES[idxs[j]].toStr() << "}\n";
    //    }
    //}
}

Glib::ustring TRIE::trieTree::getEntry(const int & idx, UINT & b, UINT & e, UCHAR & tst, UCHAR & bk, UCHAR & ch, UCHAR & chMax, UCHAR & v)
{
    Glib::ustring r = "";
    UINT rSz = results.size();
    if ((idx < 0) || (idx >= rSz)) return r;
    verseOff es = KJV::VERSES[results[idx]];
    r = es.getChapterFromVerse(b, e, chMax); // es.toStr();
    tst = es.testament;
    bk = es.book;
    ch = es.chapter;
    v = es.verse;
    return r;
}

//string TRIE::trieTree::getWord(const int & idx)
//{
//    return KJV::VERSES[results[idx][0]].toStr();
//}

void TRIE::trieTree::showSize(ptrieNode nd)
{
    UINT bCt = 0, nCt = 0;
    UINT ctOfByte = nd->getAVLsize();
    bCt += ctOfByte;
    cout << "node [" << nCt++ << "] AVL size [" << ctOfByte << "] total [" << bCt << "]\n";
}

void TRIE::trieTree::showSizes(void)
{
    /*UINT bCt = 0, iCt = 0;
    std::cout << "sizes:\n";
    iCt = WORDS.capacity() * sizeof(trieStr) + sizeof(WORDS);
    bCt += iCt;
    std::cout << "WORDS is " << WORDS.capacity() << " * sizeof(trieStr) " << sizeof(trieStr) << 
        " + sizeof vector " << sizeof(WORDS) << " = " << iCt << "\n";
    iCt = ENTRIES.capacity() * sizeof(verseOff) + sizeof(ENTRIES);
    bCt += iCt;
    std::cout << "ENTRIES is " << ENTRIES.capacity() << " * sizeof(verseOff) " << sizeof(verseOff) <<
        " + sizeof vector " << sizeof(ENTRIES) << " = " << iCt << "\n";
    iCt = TRIE_NODES.capacity() * sizeof(trieNode) + sizeof(TRIE_NODES);
    bCt += iCt;
    std::cout << "TRIE_NODES is " << TRIE_NODES.capacity() << " * sizeof(trieNode) " << sizeof(trieNode) <<
        " + sizeof vector " << sizeof(TRIE_NODES) << " = " << iCt << "\n";
    //iCt = sizeof(OFFS) + sizeof(*OFFS) + OFFS->Size();
    iCt = OFFS->Size();
    //bCt += iCt;
    std::cout << "OFFS is ptr size " << sizeof(OFFS) << " + avlNexus size " << sizeof(*OFFS) << 
        " + sum of vectors w/in " << iCt << " = " << (iCt + sizeof(OFFS) + sizeof(*OFFS)) << "\n";
    iCt += sizeof(OFFS) + sizeof(*OFFS);
    bCt += iCt;
    std::cout << "detail:\n";
    getOFFS().detailSizes();
    std::cout << "\n\n";
    iCt = EDGE_NEXUS->Size();
    std::cout << "EDGE_NEXUS is ptr size " << sizeof(EDGE_NEXUS) << " + avlNexus size " << sizeof(*EDGE_NEXUS) << 
        " + sum of vectors w/in " << iCt << " = " << (iCt + sizeof(EDGE_NEXUS) + sizeof(*EDGE_NEXUS)) << "\n";
    iCt += sizeof(EDGE_NEXUS) + sizeof(*EDGE_NEXUS);
    bCt += iCt;
    std::cout << "Total: " << bCt << "\n";*/
    //std::cout << "details:\n";
    //UINT eSz = EDGE_NEXUS->avl_store.size(), tot = 0;
    //for (UINT i = 0; i < eSz; ++i)
    //{
    //    tot += getEdgeAVL(i).detailSizes();
    //}
    //std::cout << "total edge AVL: " << tot << "\n";

}

void TRIE::trieTree::testDelete(void)
{
    std::cout << "root trieNode is " << root << "\n";
    trieNode rNd = TRIE_NODES[root];
    rNd.printAVL();
    AVL<trieEdge> & avl = rNd.getEdgeAVL(root);
    UINT dRtIdx = rNd.EDGE_NEXUS->roots[root];
    trieEdge aRt = rNd.EDGE_NEXUS->data_store[rNd.EDGE_NEXUS->node_store[dRtIdx].data];
    std::cout << "root of AVL is [" << aRt.pfx.toStr() << "]\n";
    std::cout << "deleting...\n";
    UINT dIdx = 0;
    bool found = false;
    found = avl.findData(aRt, dIdx);
    avl.Delete();
    std::cout << "root index " << dIdx << " " << dRtIdx << "\n";
    rNd.printAVL();
    dRtIdx = rNd.EDGE_NEXUS->roots[root];
    aRt = rNd.EDGE_NEXUS->data_store[rNd.EDGE_NEXUS->node_store[dRtIdx].data];
    std::cout << "root of AVL is now [" << aRt.pfx.toStr() << "] @" << dRtIdx << "\n";
    std::cout << "testing defrag\n";
    std::cout << "nodes before: " << rNd.EDGE_NEXUS->data_store.size() << "\n";
    std::cout << "node 0 " << rNd.EDGE_NEXUS->node_store[0].toStr();
    std::cout << "node 1 " << rNd.EDGE_NEXUS->node_store[1].toStr();
    std::cout << "node 2299 " << rNd.EDGE_NEXUS->node_store[2299].toStr();
    std::cout << "node 2300 " << rNd.EDGE_NEXUS->node_store[2300].toStr();
    std::cout << "node 2301 " << rNd.EDGE_NEXUS->node_store[2301].toStr();
    std::cout << "top root [" << rNd.EDGE_NEXUS->roots[rNd.EDGE_NEXUS->roots.size() - 1] << "]\n";
    rNd.EDGE_NEXUS->Defrag();
    std::cout << "nodes after: " << rNd.EDGE_NEXUS->data_store.size() << "\n";
    std::cout << "node 0 " << rNd.EDGE_NEXUS->node_store[0].toStr();
    std::cout << "node 1 " << rNd.EDGE_NEXUS->node_store[1].toStr();
    std::cout << "node 2299 " << rNd.EDGE_NEXUS->node_store[2299].toStr();
    std::cout << "node 2300 " << rNd.EDGE_NEXUS->node_store[2300].toStr();
    std::cout << "top root [" << rNd.EDGE_NEXUS->roots[rNd.EDGE_NEXUS->roots.size() - 1] << "]\n";
    rNd.printAVL();


}
