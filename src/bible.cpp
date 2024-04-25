#include "first.hpp"
#include "GUI.hpp"
#include "widgets.hpp"
#include "trie.hpp"

using namespace std;

int main (int argc, char **argv)
{
	//TRIE::KJV::parseText();
	//TRIE::KJV::getNonASCII();
	GEXT::argc = argc;
	GEXT::argv = argv;

	pGEXT pG = GEXT::getInst();
	GUI * p_CI = new GUI;
	pG->pCI = p_CI;
	p_CI->ResetGUI(pG);
	GEXT::the_app->run(*GEXT::CMW);
	delete pG;
	exit(EXIT_SUCCESS);
}
