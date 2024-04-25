#pragma once

class glade_extract;
typedef class glade_extract GEXT;
typedef GEXT * pGEXT;

namespace TRIE
{
	class trieTree;
};

class GUI
{
public:
	GUI(void);
	~GUI(void);

	void ResetGUI(pGEXT);
	void HandleMainDlgCloseButton(void);
	void HandlepatternEntry(void);
	void HandleMessageCloseButton(void);
	void HandleTreeRowActivated(const Gtk::TreeModel::Path&, Gtk::TreeViewColumn*);
	bool HandleresultsListClick(GdkEventButton *);
	bool HandleresultsListMouse(GdkEventMotion *);
	bool HandleresultsListLeave(GdkEventCrossing *);
	void reflectSelection(void);
	void HandleBookChange(char);
	void HandleChapterChange(char);
	void resetResultsFont(void);
	void scrollTextView(void);
	void HandleNotebookSwitch(Gtk::Widget *, guint);

	pGEXT pG;
	Gtk::Dialog * MainDlg;
	Gtk::Dialog * MessageBox;
	Gtk::Button * MainDlgCloseButton;
	//Gtk::Label * dictionaryLabel;
	Gtk::Label * patternLabel;
	Gtk::Entry * patternEntry;
	Gtk::TextView * resultsList;
	Gtk::TextView * txtView;
	Gtk::Label * statusLabel;
	Gtk::Button * MessageCloseButton;
	Gtk::Label * MessageLabel;
	Gtk::TreeView * TOCTree;
	TRIE::trieTree * pTree;
	Gtk::Label * chapterLabel, * bookLabel;
	Gtk::Box * HeaderBox;
	Gtk::Button * BookBackButton, * BookNextButton, * ChapterBackButton, * ChapterNextButton;

	Glib::RefPtr<Gtk::TextBuffer> txtBuff, matchBuff;
	Glib::RefPtr<Gdk::Window> rlWin;
	Glib::RefPtr<Gdk::Cursor> rlArrow;
	Glib::RefPtr<Gtk::TextTag> gray, hlite, fnt;
	Gtk::TextIter grayITb, grayITe, hliteITb, hliteITe;
	int grayIdx, hliteIdx;
	UCHAR selTestament, selBook, selChap, selChapMax, selVerse;

	Glib::RefPtr<Gtk::TextMark> mrk;
	//Glib::RefPtr<Gtk::Adjustment> otAdj, ntAdj, chAdj;
	//Glib::RefPtr<Glib::IdleSource> idle_source;
	//sigc::connection svConn;

	//Tree model columns:
	class ModelColumns : public Gtk::TreeModel::ColumnRecord
	{
	public:

		ModelColumns(void) { add(m_col_name); }

		//Gtk::TreeModelColumn<int> m_col_id;
		Gtk::TreeModelColumn<Glib::ustring> m_col_name;
	};

	ModelColumns m_Columns;

	//Child widgets:
	//Gtk::Box m_VBox;

	//Gtk::ScrolledWindow m_ScrolledWindow;
	//Gtk::TreeView m_TreeView;
	Glib::RefPtr<Gtk::TreeStore> m_refTreeModel;

	//Gtk::Box m_ButtonBox;
	//Gtk::Button m_Button_Quit;
	
};
