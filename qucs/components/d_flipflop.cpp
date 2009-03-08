/***************************************************************************
                              d_flipflop.cpp
                             ----------------
    begin                : Fri Jan 06 2006
    copyright            : (C) 2006 by Michael Margraf
    email                : michael.margraf@alumni.tu-berlin.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <stdlib.h>

#include "d_flipflop.h"
#include "node.h"
#include "main.h"

D_FlipFlop::D_FlipFlop()
{
  Type = isDigitalComponent;
  Description = QObject::tr("D flip flop with asynchron reset");

  Props.append(new Property("t", "0", false, QObject::tr("delay time")));

  Lines.append(new Line(-20,-20, 20,-20,QPen(QPen::darkBlue,2)));
  Lines.append(new Line(-20, 20, 20, 20,QPen(QPen::darkBlue,2)));
  Lines.append(new Line(-20,-20,-20, 20,QPen(QPen::darkBlue,2)));
  Lines.append(new Line( 20,-20, 20, 20,QPen(QPen::darkBlue,2)));

  Lines.append(new Line(-30,-10,-20,-10,QPen(QPen::darkBlue,2)));
  Lines.append(new Line(-30, 10,-20, 10,QPen(QPen::darkBlue,2)));
  Lines.append(new Line( 30,-10, 20,-10,QPen(QPen::darkBlue,2)));
  Lines.append(new Line(  0, 20,  0, 30,QPen(QPen::darkBlue,2)));

  Texts.append(new Text(-17,-21, "D", QPen::darkBlue, 12.0));
  Texts.append(new Text(  6,-21, "Q", QPen::darkBlue, 12.0));
  Texts.append(new Text( -4,  5, "R", QPen::darkBlue, 9.0));
  Lines.append(new Line(-20,  6,-12, 10,QPen(QPen::darkBlue,0)));
  Lines.append(new Line(-20, 14,-12, 10,QPen(QPen::darkBlue,0)));

  Ports.append(new Port(-30,-10));  // D
  Ports.append(new Port(-30, 10));  // Clock
  Ports.append(new Port( 30,-10));  // Q
  Ports.append(new Port(  0, 30));  // Reset

  x1 = -30; y1 = -24;
  x2 =  30; y2 =  30;
  tx = x1+4;
  ty = y2+4;
  Model = "DFF";
  Name  = "Y";
}

// -------------------------------------------------------
QString D_FlipFlop::vhdlCode(int NumPorts)
{
  QString s = ";\n";
  if(NumPorts <= 0)  // no truth table simulation ?
    if(strtod(Props.getFirst()->Value.latin1(), 0) != 0.0) { // delay time
      s = Props.getFirst()->Value;
      if(!VHDL_Time(s, Name))
        return s;    // time has not VHDL format
      s = " after " + s + ";\n";
    }

  s = "  " + Name + " : process (" +
      Ports.at(0)->Connection->Name + ", " +
      Ports.at(1)->Connection->Name + ")\n  begin\n    if (" +
      Ports.at(3)->Connection->Name + "='1') then  " +
      Ports.at(2)->Connection->Name + " <= '0'" + s +"    elsif (" +
      Ports.at(1)->Connection->Name + "='1' and " +
      Ports.at(1)->Connection->Name + "'event) then\n      " +
      Ports.at(2)->Connection->Name + " <= " +
      Ports.at(0)->Connection->Name + s + "    end if;\n  end process;\n\n";
  return s;
}

// -------------------------------------------------------
QString D_FlipFlop::verilogCode(int NumPorts)
{
  QString t = "";
  if(NumPorts <= 0)  // no truth table simulation ?
    if(strtod(Props.getFirst()->Value.latin1(), 0) != 0.0) { // delay time
      t = Props.getFirst()->Value;
      if(!Verilog_Time(t, Name))
        return t;    // time has not VHDL format
      t = "    #" + t + ";\n";
    }
  
  QString s = "";
  QString q = Ports.at(2)->Connection->Name;
  QString d = Ports.at(0)->Connection->Name;
  QString r = Ports.at(3)->Connection->Name;
  QString c = Ports.at(1)->Connection->Name;
  QString v = "net_reg" + Name + q;
  
  s = "\n  // " + Name + " D-flipflop\n" +
    "  assign  " + q + " = " + v + ";\n" +
    "  reg     " + v + " = 0;\n" +
    "  always @ (" + c + " or " + r + ") begin\n" + t +
    "    if (" + r + ") " + v + " <= 0;\n" +
    "    else if (~" + r + " && " + c + ") " + v + " <= " + d + ";\n" +
    "  end\n\n";
  return s;
}

// -------------------------------------------------------
Component* D_FlipFlop::newOne()
{
  return new D_FlipFlop();
}

// -------------------------------------------------------
Element* D_FlipFlop::info(QString& Name, char* &BitmapFile, bool getNewOne)
{
  Name = QObject::tr("D-FlipFlop");
  BitmapFile = (char *) "dflipflop";

  if(getNewOne)  return new D_FlipFlop();
  return 0;
}
