/***************************************************************************
    copyright            : (C) 2020 Felix Salfelder
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
/*--------------------------------------------------------------------------*/
#include "command.h"
#include "qio.h"
#include "element_list.h"
#include "qucs_globals.h"
#include "painting.h"
/*--------------------------------------------------------------------------*/
namespace{
/*--------------------------------------------------------------------------*/
// ignore "<Spice>" section. (use <Model> instead.)
class Model : public Command{
	void do_it(istream_t& cs, ElementList*) override {
	  auto fullstring = cs.fullString();
	  trace1("Model", fullstring);

	  std::string M;
	  std::string buf;
	  while(true){
		  cs.read_line();
		  trace1("Model", cs.fullString());
		  if(cs.is_end()){
			  break;
		  }else if(cs.umatch("</Spice>")){
			  break;
		  }else{
			  cs.skipbl();
			  M += cs.tail() + "\n";
		  }
	  }
#if 0 // this does not work (surprise!)
      // but it may help to integrate spice hacks.
	  trace1("hack", M);
	  Symbol* textdef = symbol_dispatcher.clone("spiceVerbatimHack");
	  assert(textdef);
	  textdef->setParameter("spiceVerbatimHack", M);
	  textdef->set_label(":spiceVerbatimHack:");
	  assert(s);
	  s->pushBack(textdef);
#endif
  }
}d0;
Dispatcher<Command>::INSTALL p0(&qucs::command_dispatcher, "Spice", &d0);
Dispatcher<Command>::INSTALL p1(&qucs::command_dispatcher, "Spice>", &d0); // BUG
Dispatcher<Command>::INSTALL p2(&qucs::command_dispatcher, "<Spice>", &d0); // ...
/*--------------------------------------------------------------------------*/
} // namespace
