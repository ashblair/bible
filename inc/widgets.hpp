#pragma once

/*CONCEPTUAL INCLUDES FOR THIS PROJECT:
#include "stdafx.h" which should contain
#include <gtkmm.h>
#include <assert.h>
#include <iostream>
#include <string>
#include <map>

*/
/*
	usage: (in main start with:) GEXT::argc = argc; GEXT::argv = argv;
	from the glade file, an extract:
	MAINS:
		MainDlg, a GtkDialog
		MessageBox, a GtkDialog


	STYLES:
		MainDlgCloseBox, a GtkButtonBox
		MainDlgLUBox, a GtkBox
		MessageButtonBox, a GtkButtonBox


	CONTAINERS:
		patternBox, a GtkBox
		listScroll, a GtkScrolledWindow
		txtViewScrolled, a GtkScrolledWindow
		MessageVBox, a GtkBox


	CONTROLS:
		MainDlgCloseButton, a GtkButton
		dictionaryLabel, a GtkLabel
		patternLabel, a GtkLabel
		patternEntry, a GtkEntry
		resultsList, a GtkTextView
		txtView, a GtkTextView
		statusLabel, a GtkLabel
		MessageCloseButton, a GtkButton
		MessageLabel, a GtkLabel
*/
typedef class GUI * pGUI;

class glade_info
{
public:
	std::string classType, id;
	Gtk::Widget * pW;

	glade_info(void):classType{}, id{}, pW{NULL}{}
	glade_info(const glade_info &a):classType{a.classType}, id{a.id}, pW{a.pW}{}
	~glade_info(void){}

	Gtk::Widget * getWidget(void) {return pW;}
	std::string getName() {return id;}
	std::string getClassType() {return classType;}
};
typedef class glade_extract GEXT;
typedef GEXT * pGEXT;

class glade_extract
{
enum wdg_enum{MainDlg = 0, MessageBox = 1, MainDlgCloseBox = 2, MainDlgLUBox = 3, MessageButtonBox = 4, patternBox = 5, listScroll = 6, txtViewScrolled = 7, MessageVBox = 8, MainDlgCloseButton = 9, patternLabel = 11, patternEntry = 12, resultsList = 13, txtView = 14, statusLabel = 15, MessageCloseButton = 16, MessageLabel = 17, TOCTree = 18, luNotebook = 19, HeaderBox = 20, BookBox = 21, ChapBox = 22, BookBackButton = 23, BookNextButton = 24, BookLabel = 25, ChapterBackButton = 26, ChapterNextButton = 27, ChapterLabel = 28};
	Gtk::Widget * get(const std::string &);
public:
	void get(const std::string & s, Gtk::Box*&gtk){gtk=dynamic_cast<Gtk::Box*>(get(s));}
	void get(const std::string & s, Gtk::Button*&gtk){gtk=dynamic_cast<Gtk::Button*>(get(s));}
	void get(const std::string & s, Gtk::ButtonBox*&gtk){gtk=dynamic_cast<Gtk::ButtonBox*>(get(s));}
	void get(const std::string & s, Gtk::Dialog*&gtk){gtk=dynamic_cast<Gtk::Dialog*>(get(s));}
	void get(const std::string & s, Gtk::Entry*&gtk){gtk=dynamic_cast<Gtk::Entry*>(get(s));}
	void get(const std::string & s, Gtk::Label*&gtk){gtk=dynamic_cast<Gtk::Label*>(get(s));}
	void get(const std::string & s, Gtk::TextView*&gtk){gtk=dynamic_cast<Gtk::TextView*>(get(s));}
	void get(const std::string & s, Gtk::TreeView*&gtk){gtk=dynamic_cast<Gtk::TreeView*>(get(s));}
	//void get(const std::string & s, Gtk::SpinButton*&gtk){gtk=dynamic_cast<Gtk::SpinButton*>(get(s));}
	void get(const std::string & s, Gtk::Notebook*&gtk){gtk=dynamic_cast<Gtk::Notebook*>(get(s));}

	bool on_MainDlg_delete_event(GdkEventAny*);
	void on_MainDlg_size_allocate(Gtk::Allocation&);
	bool on_MessageBox_delete_event(GdkEventAny*);
	void on_MessageBox_size_allocate(Gtk::Allocation&);
	void on_MainDlgCloseButton_clicked(void);
	void on_patternEntry_activate(void);
	void on_MessageCloseButton_clicked(void);
	void on_TOCTree_row_activated(const Gtk::TreeModel::Path&, Gtk::TreeViewColumn*);
	bool on_resultsList_button_release_event(GdkEventButton*);
	bool on_resultsList_motion_notify_event(GdkEventMotion *);
	bool on_resultsList_leave_notify_event(GdkEventCrossing *);
	void on_BookNextButton_clicked(void);
	void on_BookBackButton_clicked(void);
	void on_ChapterNextButton_clicked(void);
	void on_ChapterBackButton_clicked(void);
	void on_luNotebook_switch_page(Gtk::Widget *, guint);
	
	static Gtk::Dialog* CMW;
	static int argc;
	static char ** argv;
	static Glib::RefPtr<Gtk::Application> the_app;
	static Glib::RefPtr<Gtk::Builder> refBuilder;
	static Glib::RefPtr<Gtk::CssProvider> provider;
	static Glib::RefPtr<Gdk::Display> display;
	static Glib::RefPtr<Gdk::Screen> screen;
	static pGEXT getInst(void);
	std::map<std::string, glade_info *> mains, styles, containers, controls;
	pGUI pCI;
	~glade_extract(void);
private:
	glade_info GI[29];
	glade_extract(void);
	static pGEXT pGEXTInstance;
};
