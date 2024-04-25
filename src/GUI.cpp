#include "first.hpp"
#include "widgets.hpp"
#include "GUI.hpp"
#include "trie.hpp"
#include "bibleExceptions.hpp"

using namespace std;

GUI::GUI(void)
{
	pG = NULL;
	MainDlg = NULL;
	MessageBox = NULL;
	MainDlgCloseButton = NULL;
	//dictionaryLabel = NULL;
	patternLabel = NULL;
	patternEntry = NULL;
	resultsList = NULL;
	txtView = NULL;
	statusLabel = NULL;
	MessageCloseButton = NULL;
	MessageLabel = NULL;
	TOCTree = NULL;
	HeaderBox = NULL;
	BookBackButton = NULL;
	BookNextButton = NULL;
	ChapterBackButton = NULL;
	ChapterNextButton = NULL;
	bookLabel = NULL;
	chapterLabel = NULL;
}

GUI::~GUI(void)
{
	//std::cout << "~GUI\n";
	TOCTree->unset_model();
	delete pTree;
	delete MainDlg;
}

void GUI::ResetGUI(pGEXT p_g)
{
	pG = p_g;
	pG->get("MainDlg", MainDlg);
	pG->get("MessageBox", MessageBox);
	pG->get("MainDlgCloseButton", MainDlgCloseButton);
	//pG->get("dictionaryLabel", dictionaryLabel);
	pG->get("patternLabel", patternLabel);
	pG->get("patternEntry", patternEntry);
	pG->get("resultsList", resultsList);
	pG->get("txtView", txtView);
	pG->get("statusLabel", statusLabel);
	pG->get("MessageCloseButton", MessageCloseButton);
	pG->get("MessageLabel", MessageLabel);
	pG->get("TOCTree", TOCTree);
	pG->get("HeaderBox", HeaderBox);
	pG->get("BookBackButton", BookBackButton);
	pG->get("BookNextButton", BookNextButton);
	pG->get("ChapterBackButton", ChapterBackButton);
	pG->get("ChapterNextButton", ChapterNextButton);
	pG->get("BookLabel", bookLabel);
	pG->get("ChapterLabel", chapterLabel);

	m_refTreeModel = Gtk::TreeStore::create(m_Columns);
	TOCTree->set_model(m_refTreeModel);	
	pTree = new TRIE::trieTree;

	//Gtk::TreeRow toprow = *(m_refTreeModel->append());
	//toprow[m_Columns.m_col_id] = 0;  // bible ID
	//toprow[m_Columns.m_col_name] = "KJV";
	TRIE::pDiv dv = TRIE::KJV::DIVS, tdv = NULL, bdv = NULL, cdv = NULL;
	for (int i = 0; i < 2; ++i)
	{
		//int tst = i + 1;
		Gtk::TreeRow tstrow = *(m_refTreeModel->append());
		//tstrow[m_Columns.m_col_id] = tst;  // testaments 1 or 2
		tstrow[m_Columns.m_col_name] = TRIE::KJV::TESTAMENTS[i];
		tdv = dv->indices->at(i);
		for (int j = 0; j < tdv->indices->size(); ++j)
		{
			//int bk = 100 * tst + j;
			Gtk::TreeRow bkrow = *(m_refTreeModel->append(tstrow.children()));
			//bkrow[m_Columns.m_col_id] = bk;  // books 100 - 227 (not inclusive)
			bkrow[m_Columns.m_col_name] = TRIE::KJV::BOOKS[i][j];
			bdv = tdv->indices->at(j);
			for (int k = 0; k < bdv->indices->size(); ++ k)
			{
				//int chap = 1000 * bk + k;
				Gtk::TreeRow chrow = *(m_refTreeModel->append(bkrow.children()));
				//chrow[m_Columns.m_col_id] = bk;  // chapters 100000 - 227150 (not inclusive)
				cdv = bdv->indices->at(k);
				chrow[m_Columns.m_col_name] = "chapter " + to_string(k + 1) + " (" + to_string(cdv->endOff) + " verses)";
				//for (int l = 0; l < cdv->endOff; ++ l)
				//{
				//	Gtk::TreeRow vrow = *(m_refTreeModel->append(chrow.children()));
					//vrow[m_Columns.m_col_id] = 1000 * chap + l;  // verses 100000000 - 227150999 (not inclusive)
				//	vrow[m_Columns.m_col_name] = "verse " + to_string(l + 1);
				//}
			}
		}
	}
	//Add the TreeView's view columns:
	TOCTree->append_column("Table Of Contents", m_Columns.m_col_name);
	TOCTree->property_activate_on_single_click() = true;
	//MainDlg->maximize();

	statusLabel->set_text("");
	txtBuff = Gtk::TextBuffer::create();
	txtView->set_buffer(txtBuff);
	matchBuff = Gtk::TextBuffer::create();
	resultsList->set_buffer(matchBuff);
	
	hlite = matchBuff->create_tag("hlite");
	hlite->property_background() = "blue";
	hlite->property_paragraph_background() = "blue";
	hlite->property_foreground() = "white";
	hliteIdx = -1;

	gray = matchBuff->create_tag("grayTag");
	gray->property_background() = "lightgray";
	gray->property_paragraph_background() = "lightgray";
	grayIdx = -1;

	fnt = matchBuff->create_tag("fntTag");
	fnt->property_font() = "bold italic 12";
	fnt->property_family() = "monospace, 'Courier New', Courier";

	rlArrow = Gdk::Cursor::create(Gdk::ARROW);

	mrk = txtBuff->create_mark("scrollTo", txtBuff->get_iter_at_offset(0));

	HeaderBox->hide();
	selTestament = 0;
	selBook = 0;
	selChap = 0;
	selChapMax = 0;
	selVerse = 0;
}

void GUI::HandleMainDlgCloseButton(void)
{
	//cout << "GUI::HandleMainDlgCloseButton called.\n";
	MainDlg->close();
}

void GUI::HandlepatternEntry(void)
{
	//cout << "GUI::HandlepatternEntry called.\n";
	try
	{
		txtBuff->set_text("");
		matchBuff->set_text("");
		HeaderBox->hide();
		Glib::ustring ptt = patternEntry->get_text();
		int pos = patternEntry->get_position();
		bool atEnd = pos == ptt.size();
		if (atEnd) pos = -1;
		string r = pTree->debug_pattern(ptt);
		patternEntry->set_text(r);
		if (r.size() != ptt.size()) pos = -1;
		patternEntry->set_position(pos);
		pTree->pattern = r;
		statusLabel->set_text("searching bible ...");
		//unload_listbox();
		while(gtk_events_pending()) {gtk_main_iteration_do(false);}	
		pTree->search();
		statusLabel->set_text("loading results list ...");
		while(gtk_events_pending()) {gtk_main_iteration_do(false);}	
		//vector<string> & wrds = pTree->wrdvec;
		//UINT wSz = wrds.size();
		/*for (UINT i = 0; i < wSz; ++i)
		{
			LBRow * lbr = new LBRow;
			string wrd = wrds[i];
			lbr->WORD = new Gtk::Label(wrd.c_str(), Gtk::ALIGN_START);
			lbr->add_m_all();
			lbRows.push_back(lbr);
			resultsList->append(*lbr);
			resultsList->show_all();
		}*/
		UINT rSz = pTree->results.size();
		//std::cout << "searched " << r << " got " << rSz << " results.\n";
		if (rSz > 0) 
		{
			Glib::ustring resStr = pTree->resultString;
			matchBuff->set_text(resStr);
			grayIdx = -1;
			hliteIdx = -1;
			statusLabel->set_text("select a row to read the entry");
			rlWin = resultsList->get_window(Gtk::TEXT_WINDOW_TEXT);
			//Glib::RefPtr<Gdk::Cursor> rlArrow = Gdk::Cursor::create(Gdk::ARROW);
			rlWin->set_cursor(rlArrow);
			resetResultsFont();
		}
		else statusLabel->set_text("");
	}
	catch (BIBX::bibleexception & e)
	{
		MessageLabel->set_text(e.what());
		int m = MessageBox->run();
	}
	catch (AVLX::avlexception & e)
	{
		MessageLabel->set_text(e.what());
		int m = MessageBox->run();

	}
	

}

void GUI::HandleMessageCloseButton(void)
{
	//cout << "GUI::HandleMessageCloseButton called.\n";
	MainDlg->close();
}

void GUI::HandleTreeRowActivated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn*)
{
	const Gtk::TreeModel::iterator iter = m_refTreeModel->get_iter(path);
	if(iter)
	{
		const Gtk::TreeRow row = *iter;
		//std::cout << "Row activated: Name=" << row[m_Columns.m_col_name] << " path [" << path.to_string() << "]\n";
		TRIE::pDiv d = TRIE::KJV::DIVS;
		for (int i = 0; i < path.size(); ++i)
		{
			//std::cout << path[i] << " ";
			d = d->indices->at(path[i]);
		}
		//std::cout << "\n";
		txtBuff->set_text(d->toStr());
	}
}

bool GUI::HandleresultsListClick(GdkEventButton * b)
{
	int xBuff = 0, yBuff = 0, lineTop = 0, charCt = 0, rSz = pTree->results.size();
	if (rSz == 0) return true;
	resultsList->window_to_buffer_coords(Gtk::TEXT_WINDOW_TEXT, b->x, b->y, xBuff, yBuff);
	Gtk::TextIter tITb, tITe;
	resultsList->get_line_at_y(tITb, yBuff, lineTop);
	int idx = tITb.get_line();
	if (hliteIdx >= 0) matchBuff->remove_tag(hlite, hliteITb, hliteITe);
	hliteIdx = -1;
	if (idx >= rSz) return true;
	charCt = tITb.get_chars_in_line();
	tITe = tITb;
	tITe.forward_chars(charCt);
	hliteITb = tITb;
	hliteITe = tITe;
	if (idx == grayIdx) 
	{
		matchBuff->remove_tag(gray, hliteITb, hliteITe);
		grayIdx = -1;
	}
	matchBuff->apply_tag(hlite, hliteITb, hliteITe);
	hliteIdx = idx;
	//tITb.forward_chars(2);
	//tITe = tITb;
	//tITe.forward_chars(11);
	UINT begin = 0, end = 0;
	Glib::ustring entry = pTree->getEntry(idx, begin, end, selTestament, selBook, selChap, selChapMax, selVerse);
	Glib::ustring s = 
		"you have selected " + 
		string(TRIE::KJV::BOOKS[selTestament][selBook]) + 
		" " +
		to_string(selChap) + 
		":" + 
		to_string(selVerse) + 
		" at row " + 
		to_string(idx + 1);
	statusLabel->set_text(s);
	if (!entry.empty())
	{
		reflectSelection();
		HeaderBox->show_all();
		txtBuff->set_text(entry);
		txtBuff->get_bounds(tITb, tITe);
		tITe = tITb;
		tITb.forward_chars(begin); //= txtBuff->get_iter_at_offset(begin);
		tITe.forward_chars(end); // = txtBuff->get_iter_at_offset(end);
		//txtBuff->place_cursor(tITb);
		txtBuff->move_mark(mrk, tITb);

		//svConn = idle_source->connect(sigc::mem_fun<bool>(*this, &GUI::srollTextView));
		//Glib::SignalIdle si; si.connect_once(std::bind(GUI::srollTextView), 200); //sigc::mem_fun(*this, &GUI::srollTextView));
		txtBuff->select_range(tITb, tITe);
		while(gtk_events_pending()) {gtk_main_iteration_do(false);}	
		scrollTextView();
	}
	rlWin = resultsList->get_window(Gtk::TEXT_WINDOW_TEXT);
	rlWin->set_cursor(rlArrow);

	return true;

}

bool GUI::HandleresultsListMouse(GdkEventMotion * m)
{

	int xBuff = 0, yBuff = 0, lineTop = 0, charCt = 0, rSz = pTree->results.size();
	if (rSz == 0) return true;
	resultsList->window_to_buffer_coords(Gtk::TEXT_WINDOW_TEXT, m->x, m->y, xBuff, yBuff);
	Gtk::TextIter tITb, tITe;
	resultsList->get_line_at_y(tITb, yBuff, lineTop);
	int idx = tITb.get_line();
	if (grayIdx >= 0) matchBuff->remove_tag(gray, grayITb, grayITe);
	grayIdx = -1;
	//bool ooWin = (m->x < 0.0) || (m->y < 0.0) || (m->x > rlAlloc.get_width()) || (m->y > rlAlloc.get_height());
	if ((idx >= rSz) || (idx == hliteIdx)) return true;
	charCt = tITb.get_chars_in_line();
	tITe = tITb;
	tITe.forward_chars(charCt);
	grayITb = tITb;
	grayITe = tITe;
	matchBuff->apply_tag(gray, grayITb, grayITe);
	grayIdx = idx;
	//Glib::RefPtr<Gdk::Window> rlWin = resultsList->get_window(Gtk::TEXT_WINDOW_TEXT);
	//Glib::RefPtr<Gdk::Cursor> rlArrow = Gdk::Cursor::create(Gdk::ARROW);
	//rlWin->set_cursor(rlArrow);

	return true;

}

bool GUI::HandleresultsListLeave(GdkEventCrossing * c)
{
	//std::cout << "HandleresultsListLeave\n";
	if (grayIdx >= 0)
	{
		matchBuff->remove_tag(gray, grayITb, grayITe);
		grayIdx = -1;
	}
	return true;
}

void GUI::resetResultsFont(void)
{
	//int xBuff = 0, yBuff = 0, lineTop = 0, charCt = 0, rSz = pTree->results.size();
	//if (rSz == 0) return true;
	//resultsList->window_to_buffer_coords(Gtk::TEXT_WINDOW_TEXT, b->x, b->y, xBuff, yBuff);
	Gtk::TextIter tITb, tITe, tITl, tITlft;
	matchBuff->get_bounds(tITb, tITe);
	if (tITb == tITe) return;
	tITl = tITb;
	int charCt = 14; //, lnChrCt = 0, eolnCt = 1;
	bool eol = false;
	do
	{
		//lnChrCt = tITb.get_chars_in_line();
		//tITeoln = tITl;
		tITlft = tITl;
		//tITeoln.forward_chars(lnChrCt);
		tITlft.forward_chars(charCt);
		matchBuff->apply_tag(fnt, tITl, tITlft);
		//tITl = tITeoln;
		eol = tITl.forward_line();
	} while (eol);
}

void GUI::scrollTextView(void)
{
	txtView->scroll_to(mrk);
	gtk_text_view_scroll_to_mark (
		txtView->gobj(),
		mrk.get()->gobj(),
		0.3, //gdouble within_margin,
		TRUE, //gboolean use_align,
		0.5, //gdouble xalign,
		0.0 //gdouble yalign
	);
	//return false;
}
void GUI::reflectSelection(void)
{
	bookLabel->set_text(TRIE::KJV::BOOKS_ABBR[selTestament][selBook]);
	chapterLabel->set_text("Chap " + to_string(selChap));
}

void GUI::HandleBookChange(char ctl)
{
	assert ((ctl == 'u') || (ctl == 'd'));
	if (ctl == 'u')
	{
		++selBook;
		if (selBook == TRIE::KJV::EXTENTS[selTestament + 1])
		{
			selBook = 0;
			selTestament = (selTestament + 1) % TRIE::KJV::EXTENTS[0];
		}
	}
	else
	{ // ctl is 'd'
		if (selBook == 0)
		{
			selTestament = (selTestament + TRIE::KJV::EXTENTS[0] - 1) % TRIE::KJV::EXTENTS[0];
			selBook = TRIE::KJV::EXTENTS[selTestament + 1] - 1;
		}
		else --selBook;
	}
	selChap = 1;

	TRIE::pDiv div = TRIE::KJV::DIVS;
	div = div->indices->at(selTestament)->indices->at(selBook);
	selChapMax = div->indices->size();

	reflectSelection();
	txtBuff->set_text(div->toStr());
	txtBuff->move_mark(mrk, txtBuff->get_iter_at_offset(0));
	while(gtk_events_pending()) {gtk_main_iteration_do(false);}	
	scrollTextView();
	statusLabel->set_text("");
}

void GUI::HandleChapterChange(char ctl)
{
	assert ((ctl == 'u') || (ctl == 'd'));
	if (ctl == 'u')
	{
		++selChap;
		if (selChap > selChapMax)
		{
			HandleBookChange('u');
			return;
		}
	}
	else
	{  // ctl is 'd'
		--selChap;
		if (selChap == 0) 
		{
			HandleBookChange('d');
			return;
		}
	}
	reflectSelection();
	
	TRIE::pDiv div = TRIE::KJV::DIVS;
	div = div->indices->at(selTestament)->indices->at(selBook)->indices->at(selChap - 1);
	txtBuff->set_text(div->toStr());
	txtBuff->move_mark(mrk, txtBuff->get_iter_at_offset(0));
	while(gtk_events_pending()) {gtk_main_iteration_do(false);}	
	scrollTextView();
	statusLabel->set_text("");

}

void GUI::HandleNotebookSwitch(Gtk::Widget * page, guint pIdx)
{
	HeaderBox->hide();
	txtBuff->set_text("");
	statusLabel->set_text("");

}
