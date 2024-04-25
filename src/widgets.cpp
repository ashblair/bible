#include "first.hpp"
#include "GUI.hpp"
#include "widgets.hpp"

using namespace std;

Glib::RefPtr<Gtk::CssProvider> GEXT::provider;
Glib::RefPtr<Gdk::Display> GEXT::display;
Glib::RefPtr<Gdk::Screen> GEXT::screen;
Glib::RefPtr<Gtk::Application> GEXT::the_app;
Glib::RefPtr<Gtk::Builder> GEXT::refBuilder;
Gtk::Dialog* GEXT::CMW = NULL;
pGEXT GEXT::pGEXTInstance = NULL;
//initialize these next statics first in main before getInst():
int GEXT::argc = 0;
char ** GEXT::argv = NULL;

extern char glade_start		asm("_binary_rsc_bible_glade_start");
extern char glade_end		asm("_binary_rsc_bible_glade_end");
extern char style_start		asm("_binary_rsc_style_css_start");
extern char style_end		asm("_binary_rsc_style_css_end");

glade_extract::glade_extract(void)
{
	the_app = Gtk::Application::create(argc, argv, "from.the.glade");
	
	//Load the GtkBuilder file and instantiate its widgets:
	refBuilder = Gtk::Builder::create();
	/*
	try
	{
		refBuilder->add_from_file("rsc/bible.glade");
	}
	catch(const Glib::FileError& ex)
	{
		cout << "FileError: " << ex.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	catch(const Glib::MarkupError& ex)
	{
		cout << "MarkupError: " << ex.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	catch(const Gtk::BuilderError& ex)
	{
		cout << "BuilderError: " << ex.what() << std::endl;
		exit(EXIT_FAILURE);
	}

	provider = Gtk::CssProvider::create();
	Gtk::CssProvider * pProvider = provider.get();
	display = Gdk::Display::get_default();
	Gdk::Display * pDisplay = display.get();
	screen = pDisplay->get_default_screen();
	Gtk::StyleContext::add_provider_for_screen(screen, provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
	pProvider->load_from_path("rsc/style.css");
	*/

	char * g_s = &glade_start, * g_e = &glade_end;
	gsize g_z = g_e - g_s;
	refBuilder->add_from_string(g_s, g_z);
	provider = Gtk::CssProvider::create();
	display = Gdk::Display::get_default();
	screen = display->get_default_screen();
	Gtk::StyleContext::add_provider_for_screen(screen, provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
	char * s_s = &style_start, * s_e = &style_end;
	string s_str(s_s, s_e);
	provider->load_from_data(s_str);

	GI[MainDlg].classType = "GtkDialog";
	GI[MainDlg].id = "MainDlg";
	refBuilder->get_widget("MainDlg", GI[MainDlg].pW);
	mains["MainDlg"] = &GI[MainDlg];
	((Gtk::Dialog*)GI[MainDlg].pW)->signal_delete_event().connect(sigc::mem_fun<GdkEventAny *, bool>(*this, &glade_extract::on_MainDlg_delete_event));
	((Gtk::Dialog*)GI[MainDlg].pW)->signal_size_allocate().connect(sigc::mem_fun<Gtk::Allocation&, void>(*this, &glade_extract::on_MainDlg_size_allocate));
	CMW = ((Gtk::Dialog*)GI[MainDlg].pW);
	GI[MessageBox].classType = "GtkDialog";
	GI[MessageBox].id = "MessageBox";
	refBuilder->get_widget("MessageBox", GI[MessageBox].pW);
	mains["MessageBox"] = &GI[MessageBox];
	((Gtk::Dialog*)GI[MessageBox].pW)->signal_delete_event().connect(sigc::mem_fun<GdkEventAny *, bool>(*this, &glade_extract::on_MessageBox_delete_event));
	((Gtk::Dialog*)GI[MessageBox].pW)->signal_size_allocate().connect(sigc::mem_fun<Gtk::Allocation&, void>(*this, &glade_extract::on_MessageBox_size_allocate));
	GI[MainDlgCloseBox].classType = "GtkButtonBox";
	GI[MainDlgCloseBox].id = "MainDlgCloseBox";
	refBuilder->get_widget("MainDlgCloseBox", GI[MainDlgCloseBox].pW);
	styles["MainDlgCloseBox"] = &GI[MainDlgCloseBox];
	GI[MainDlgLUBox].classType = "GtkBox";
	GI[MainDlgLUBox].id = "MainDlgLUBox";
	refBuilder->get_widget("MainDlgLUBox", GI[MainDlgLUBox].pW);
	styles["MainDlgLUBox"] = &GI[MainDlgLUBox];
	GI[MessageButtonBox].classType = "GtkButtonBox";
	GI[MessageButtonBox].id = "MessageButtonBox";
	refBuilder->get_widget("MessageButtonBox", GI[MessageButtonBox].pW);
	styles["MessageButtonBox"] = &GI[MessageButtonBox];
	GI[patternBox].classType = "GtkBox";
	GI[patternBox].id = "patternBox";
	refBuilder->get_widget("patternBox", GI[patternBox].pW);
	containers["patternBox"] = &GI[patternBox];
	GI[listScroll].classType = "GtkScrolledWindow";
	GI[listScroll].id = "listScroll";
	refBuilder->get_widget("listScroll", GI[listScroll].pW);
	containers["listScroll"] = &GI[listScroll];
	GI[txtViewScrolled].classType = "GtkScrolledWindow";
	GI[txtViewScrolled].id = "txtViewScrolled";
	refBuilder->get_widget("txtViewScrolled", GI[txtViewScrolled].pW);
	containers["txtViewScrolled"] = &GI[txtViewScrolled];
	GI[MessageVBox].classType = "GtkBox";
	GI[MessageVBox].id = "MessageVBox";
	refBuilder->get_widget("MessageVBox", GI[MessageVBox].pW);
	containers["MessageVBox"] = &GI[MessageVBox];
	GI[MainDlgCloseButton].classType = "GtkButton";
	GI[MainDlgCloseButton].id = "MainDlgCloseButton";
	refBuilder->get_widget("MainDlgCloseButton", GI[MainDlgCloseButton].pW);
	controls["MainDlgCloseButton"] = &GI[MainDlgCloseButton];
	((Gtk::Button*)GI[MainDlgCloseButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_MainDlgCloseButton_clicked));
	//GI[dictionaryLabel].classType = "GtkLabel";
	//GI[dictionaryLabel].id = "dictionaryLabel";
	//refBuilder->get_widget("dictionaryLabel", GI[dictionaryLabel].pW);
	//controls["dictionaryLabel"] = &GI[dictionaryLabel];
	GI[patternLabel].classType = "GtkLabel";
	GI[patternLabel].id = "patternLabel";
	refBuilder->get_widget("patternLabel", GI[patternLabel].pW);
	controls["patternLabel"] = &GI[patternLabel];
	GI[patternEntry].classType = "GtkEntry";
	GI[patternEntry].id = "patternEntry";
	refBuilder->get_widget("patternEntry", GI[patternEntry].pW);
	controls["patternEntry"] = &GI[patternEntry];
	((Gtk::Entry*)GI[patternEntry].pW)->signal_activate().connect(sigc::mem_fun(*this, &glade_extract::on_patternEntry_activate));
	GI[resultsList].classType = "GtkTextView";
	GI[resultsList].id = "resultsList";
	refBuilder->get_widget("resultsList", GI[resultsList].pW);
	controls["resultsList"] = &GI[resultsList];
	((Gtk::TextView*)GI[resultsList].pW)->signal_button_release_event().connect(sigc::mem_fun<GdkEventButton *, bool>(*this, &glade_extract::on_resultsList_button_release_event));
	((Gtk::TextView*)GI[resultsList].pW)->signal_motion_notify_event().connect(sigc::mem_fun<GdkEventMotion *, bool>(*this, &glade_extract::on_resultsList_motion_notify_event));
	((Gtk::TextView*)GI[resultsList].pW)->signal_leave_notify_event().connect(sigc::mem_fun<GdkEventCrossing *, bool>(*this, &glade_extract::on_resultsList_leave_notify_event));
	GI[txtView].classType = "GtkTextView";
	GI[txtView].id = "txtView";
	refBuilder->get_widget("txtView", GI[txtView].pW);
	controls["txtView"] = &GI[txtView];
	GI[statusLabel].classType = "GtkLabel";
	GI[statusLabel].id = "statusLabel";
	refBuilder->get_widget("statusLabel", GI[statusLabel].pW);
	controls["statusLabel"] = &GI[statusLabel];
	GI[MessageCloseButton].classType = "GtkButton";
	GI[MessageCloseButton].id = "MessageCloseButton";
	refBuilder->get_widget("MessageCloseButton", GI[MessageCloseButton].pW);
	controls["MessageCloseButton"] = &GI[MessageCloseButton];
	((Gtk::Button*)GI[MessageCloseButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_MessageCloseButton_clicked));
	GI[MessageLabel].classType = "GtkLabel";
	GI[MessageLabel].id = "MessageLabel";
	refBuilder->get_widget("MessageLabel", GI[MessageLabel].pW);
	controls["MessageLabel"] = &GI[MessageLabel];
	GI[TOCTree].classType = "GtkTreeView";
	GI[TOCTree].id = "TOCTree";
	refBuilder->get_widget("TOCTree", GI[TOCTree].pW);
	controls["TOCTree"] = &GI[TOCTree];
	((Gtk::TreeView*)GI[TOCTree].pW)->signal_row_activated().connect(sigc::mem_fun<const Gtk::TreeModel::Path &, Gtk::TreeViewColumn *, void>(*this, &glade_extract::on_TOCTree_row_activated));
	GI[luNotebook].classType = "GtkNotebook";
	GI[luNotebook].id = "luNotebook";
	refBuilder->get_widget("luNotebook", GI[luNotebook].pW);
	controls["luNotebook"] = &GI[luNotebook];
	((Gtk::Notebook*)GI[luNotebook].pW)->signal_switch_page().connect(sigc::mem_fun<Gtk::Widget *, guint, void>(*this, &glade_extract::on_luNotebook_switch_page));	
	GI[BookNextButton].classType = "GtkButton";
	GI[BookNextButton].id = "BookNextButton";
	refBuilder->get_widget("BookNextButton", GI[BookNextButton].pW);
	controls["BookNextButton"] = &GI[BookNextButton];
	((Gtk::Button*)GI[BookNextButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_BookNextButton_clicked));
	GI[BookBackButton].classType = "GtkButton";
	GI[BookBackButton].id = "BookBackButton";
	refBuilder->get_widget("BookBackButton", GI[BookBackButton].pW);
	controls["BookBackButton"] = &GI[BookBackButton];
	((Gtk::Button*)GI[BookBackButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_BookBackButton_clicked));
	GI[ChapterNextButton].classType = "GtkButton";
	GI[ChapterNextButton].id = "ChapterNextButton";
	refBuilder->get_widget("ChapterNextButton", GI[ChapterNextButton].pW);
	controls["ChapterNextButton"] = &GI[ChapterNextButton];
	((Gtk::Button*)GI[ChapterNextButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_ChapterNextButton_clicked));
	GI[ChapterBackButton].classType = "GtkButton";
	GI[ChapterBackButton].id = "ChapterBackButton";
	refBuilder->get_widget("ChapterBackButton", GI[ChapterBackButton].pW);
	controls["ChapterBackButton"] = &GI[ChapterBackButton];
	((Gtk::Button*)GI[ChapterBackButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_ChapterBackButton_clicked));
	GI[BookLabel].classType = "GtkLabel";
	GI[BookLabel].id = "BookLabel";
	refBuilder->get_widget("BookLabel", GI[BookLabel].pW);
	controls["BookLabel"] = &GI[BookLabel];
	GI[ChapterLabel].classType = "GtkLabel";
	GI[ChapterLabel].id = "ChapterLabel";
	refBuilder->get_widget("ChapterLabel", GI[ChapterLabel].pW);
	controls["ChapterLabel"] = &GI[ChapterLabel];
	GI[HeaderBox].classType = "GtkBox";
	GI[HeaderBox].id = "HeaderBox";
	refBuilder->get_widget("HeaderBox", GI[HeaderBox].pW);
	controls["HeaderBox"] = &GI[HeaderBox];

	
	//the_app->run(*CMW);
}
glade_extract::~glade_extract(void)
{
	//cout << "~glade_extract\n";	
	delete pCI;
}
pGEXT glade_extract::getInst(void)
{
	if(argv == NULL)
	{
		cout << "Error: intitialize GEXT::argc & GEXT::argv before calling getInst\n";
		exit(EXIT_FAILURE);
	}

	if(pGEXTInstance == NULL) pGEXTInstance = new glade_extract;
	return pGEXTInstance;
}
Gtk::Widget * glade_extract::get(const string & wName)
{
	map<string, glade_info *>::iterator mit = controls.find(wName);
	if (mit != controls.end()) return (*mit).second->getWidget();
	mit = containers.find(wName);
	if (mit != containers.end()) return (*mit).second->getWidget();
	mit = mains.find(wName);
	if (mit != mains.end()) return (*mit).second->getWidget();
	mit = styles.find(wName);
	if (mit != styles.end()) return (*mit).second->getWidget();
	return NULL;
}
bool glade_extract::on_MainDlg_delete_event(GdkEventAny* any_event)
{
	//cout << "MainDlg delete connected\n";
	return false;
}
void glade_extract::on_MainDlg_size_allocate(Gtk::Allocation & allocation)
{
	//cout << "MainDlg size connected\n";
}
bool glade_extract::on_MessageBox_delete_event(GdkEventAny* any_event)
{
	//cout << "MessageBox delete connected\n";
	return false;
}
void glade_extract::on_MessageBox_size_allocate(Gtk::Allocation & allocation)
{
	//cout << "MessageBox size connected\n";
}
void glade_extract::on_MainDlgCloseButton_clicked(void)
{
	pCI->HandleMainDlgCloseButton();
}
void glade_extract::on_patternEntry_activate(void)
{
	pCI->HandlepatternEntry();
}
void glade_extract::on_MessageCloseButton_clicked(void)
{
	pCI->HandleMessageCloseButton();
}
void glade_extract::on_TOCTree_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column)
{
	//cout << "anything?\n";
	pCI->HandleTreeRowActivated(path, column);
}
bool glade_extract::on_resultsList_button_release_event(GdkEventButton* b)
{
	return pCI->HandleresultsListClick(b);
}
bool glade_extract::on_resultsList_motion_notify_event(GdkEventMotion * m)
{
	return pCI->HandleresultsListMouse(m);
}
bool glade_extract::on_resultsList_leave_notify_event(GdkEventCrossing * c)
{
	return pCI->HandleresultsListLeave(c);
}
void glade_extract::on_BookNextButton_clicked(void)
{
	//std::cout << "bookNextButton clicked\n";
	pCI->HandleBookChange('u');
}
void glade_extract::on_BookBackButton_clicked(void)
{
	pCI->HandleBookChange('d');
}
void glade_extract::on_ChapterNextButton_clicked(void)
{
	//std::cout << "chapterNextButton clicked\n";
	pCI->HandleChapterChange('u');
}
void glade_extract::on_ChapterBackButton_clicked(void)
{
	pCI->HandleChapterChange('d');
}
void glade_extract::on_luNotebook_switch_page(Gtk::Widget * page, guint pIdx)
{
	//std::cout << "on_luNotebook_switch_page " << pIdx << "\n";
	pCI->HandleNotebookSwitch(page, pIdx);
}


