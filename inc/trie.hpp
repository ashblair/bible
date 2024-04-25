#pragma once
#include "AVL_c.hpp"
#include "vector_c.hpp"
// these are offsets in the embedded bible text file:
#define LEN_LO_BIT 15
#define CHAR_LO_BIT 25

#define TEST_COUNT 2
#define OTBK_COUNT 39
#define NTBK_COUNT 27

namespace TRIE
{
    //void checkBookHardCodes(void);
    //void checkTestamentHardCodes(void);

    typedef struct DivType * pDiv;

    typedef struct DivType
    {
        DivType(void);
        DivType(const DivType &);
        DivType(const UINT &, const UINT &);
        ~DivType(void);

        static void delIndices(const pDiv &);
        ::std::string toStr(void);

        UINT startOff, endOff;
        ::std::vector<pDiv> * indices;
    } Div;

    typedef class verseOff
    {
    public:
        verseOff(void);
        verseOff(const verseOff&);
        verseOff(const UINT &, const USHRT &, const UCHAR &, const UCHAR &, const UCHAR &, const UCHAR &, const UINT &, const USHRT &);
        verseOff & operator = (const verseOff &);
        //bool IsEQ(const verseOff &) const;
        //friend bool operator == (const verseOff & a, const verseOff & b) {return a.IsEQ(b);}
        //UINT getPivot(const verseOff &) const;
        //UINT find(const ::std::string &);

        ::std::string toStr(void);
        ::std::string allToStr(void);

        char getChar(UINT); // for search input: relative position
        ::std::string getString(UINT, UINT); // input: KJV offset + length
        ::std::string getVerseAtPos(UINT); // input: postion

        UINT getStartDisp(void);
        UINT getStartSrch(void);
        USHRT getLenDisp(void);
        USHRT getLenSrch(void);
        ::std::string getVerse(void);
        UINT getChapterIdx(void);
        UINT getBookIdx(void);
        ::Glib::ustring getChapterFromVerse(UINT &, UINT &, UCHAR &); 
        ::std::string getBookTitle(void);
        ::std::string getBookTitleLong(void);
        ::std::string getBookFromVerse(void);


        UINT start; 
        USHRT len; 
        UCHAR chapter, verse, book, testament;
        UINT sstart; // the offset into the search strings in verse.txt
        USHRT slen; // the length of the search string in verse.txt

    } * pverseOff;

    typedef struct KJVtype
    {
        static const UINT EXTENTS[];
        static const UINT KJV_START;
        static const UINT KJV_END;
        static const char * TESTAMENTS[];
        static const char * TESTAMENTS_ABBR[];
        static const UINT TESTAMENTS_OFFS[];
        static const char * OTBOOKS[];
        static const char * NTBOOKS[];
        static const char ** BOOKS[];
        static const char * OTBOOKS_ABBR[];
        static const char * NTBOOKS_ABBR[];
        static const char ** BOOKS_ABBR[];
        static const UINT OTBOOKS_OFFS[];
        static const UINT NTBOOKS_OFFS[];
        static const UINT * BOOKS_OFFS[];
        static ::std::vector<verseOff> VERSES;
        static pDiv DIVS; // offsets into embedded txt file
        
        static bool isWS(char);  // whitespace for KJV is ' ', '\r' or '\n'
        static UINT getLstNonWS(UINT); // gets 1st non-WS before offset at input
        static ::std::string replaceEOLN(UINT, UINT);
        static ::std::string restoreApostrophe(const ::std::string &);
        static void parseText(void);
        static void getNonASCII(void);
        //static ::std::string getBookFromIdx(UINT); // input: book index
        static UINT edgeCount, nodeCount, reptCount, offsetAVLidx, dupCount;
        static ::std::string reptLine;
    } KJV;


    typedef class trieStr
    {
    public:
        trieStr(void);
        trieStr(const char &);
        trieStr(const trieStr &);
        trieStr(const USHRT &, const USHRT &, const USHRT &);
        //UINT verseIdx(void) const;
        verseOff verse(void) const;
        UINT start(void) const;
        USHRT len(void) const;
        //static UINT getData(const UINT &, const UINT &);
        char getChar(void) const;
        //trieStr(const UINT &);

        trieStr & operator =(const trieStr &);
        bool IsEQ(const trieStr &) const;
        friend bool operator == (const trieStr & a, const trieStr & b) {return a.IsEQ(b);}
        bool IsLT(const trieStr &) const;
        friend bool operator < (const trieStr & a, const trieStr & b) {return a.IsLT(b);}
        ::std::string toStr(void);
        ::std::string toLStr(void);
        ::std::string allToStr(void);

        //char getNextSearchChar(UINT &) const;
        UINT getPivot(const trieStr &) const;
        UINT getPivot(const char *&, const UINT) const;
        UINT find(const char *&, const UINT);
        UINT find(const ::std::string &);
        void advance(const UINT &);
        void toLast(void);
        void toNext(void);
        //char getChar(const UINT &) const;

        USHRT vIdx, bPos, ePos;
        static const char END_CHR, C_WC, S_WC;
        static bool caseInsensitive;

    } * ptrieStr;


    //static AVL<offsetLU> & getOFFS(void);


    typedef class trieNode * ptrieNode;

    typedef class trieEdge
    {
    public:
        trieEdge(void);
        trieEdge(const trieEdge &);
        trieEdge(const trieStr &);
        trieEdge(const char &);
        trieEdge(const trieStr &, const UINT &);
        //trieEdge(const trieStr &, const trieNode &);
        ~trieEdge(void);

        trieEdge & operator =(const trieEdge &);

        bool IsEQ(const trieEdge &) const;
        friend bool operator == (const trieEdge & a, const trieEdge & b) {return a.IsEQ(b);}
        bool IsLT(const trieEdge &) const;
        friend bool operator < (const trieEdge & a, const trieEdge & b) {return a.IsLT(b);}

        bool findChar(char);
        bool findAny(::std::vector<trieEdge> &);
        bool findAny1(::std::vector<trieEdge>&);
        bool findEnd(void);
        bool atEnd(void);
        bool actualized(void) const;
        void add_idxs(::std::vector<USHRT>&);
        void add_tree(::std::vector<USHRT>&);
        void search(const trieEdge &, ::std::vector<USHRT> &, const char *&, const unsigned char, unsigned char, unsigned char);
        void add_idx(const USHRT &);
        
        trieStr pfx;
        UINT sfx; // index into TRIE_NODES
        vector_c<USHRT, UCHAR> indices;

    } * ptrieEdge;


    class trieNode
    {
        //::std::map<char, trieEdge> * edges;
        //pAVL<trieEdge> edges;
        UINT avlID;
    public:
        trieNode(void);
        trieNode(const trieNode &);
        ~trieNode(void);

        //void delEdges(void);
        bool getEdge(trieEdge &, UINT &);
        ::std::vector<trieEdge> getEdges(void);
        ::std::vector<trieEdge> getEdges1(void);
        // add_idx below is for duplicates.  
        // if you have duplicates add a vector<edge>-based class above & 
        // store this class in your AVLs 
        void add_idx(const UINT &, const UINT &); 
        void insert(trieEdge);
        void printAVL(void);
        //void insert(const trieStr &, const UINT &);
        UINT getAVLsize(void);
        static avlNexus<trieEdge> * EDGE_NEXUS;
        static AVL<trieEdge> & getEdgeAVL(const UINT &);

    };


    class trieTree
    {
    public:
        trieTree(void);
        ~trieTree(void);

        void getData(void);
        ::std::string debug_pattern(const ::Glib::ustring &);
        void search(void);
        ::Glib::ustring getEntry(const int &, UINT &, UINT &, UCHAR &, UCHAR &, UCHAR &, UCHAR &, UCHAR &);
        //::std::string getWord(const int &);
        void showSize(ptrieNode);
        void showSizes(void);
        void testDelete(void);

        UINT root;
        trieEdge srchEdge;
        ::std::string pattern, resultString;
        ::std::vector<USHRT> results;
        //::std::vector<::std::string> wrdvec;
        static ::std::vector<trieNode> TRIE_NODES;
    };
};