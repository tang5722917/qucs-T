/***************************************************************************
                          phaseshifter.cpp  -  description
                             -------------------
    begin                : Sat Aug 23 2003
    copyright            : (C) 2003 by Michael Margraf
    email                : margraf@mwt.ee.tu-berlin.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "phaseshifter.h"


Phaseshifter::Phaseshifter()
{
  Description = "phase shifter";

  Lines.append(new Line(-14,-14, 14,-14,QPen(QPen::darkBlue,2)));
  Lines.append(new Line(-14, 14, 14, 14,QPen(QPen::darkBlue,2)));
  Lines.append(new Line(-14,-14,-14, 14,QPen(QPen::darkBlue,2)));
  Lines.append(new Line( 14,-14, 14, 14,QPen(QPen::darkBlue,2)));
  Arcs.append(new Arc( -9, -9, 18, 18, 0, 16*360,QPen(QPen::darkBlue,2)));
  Lines.append(new Line(-10, 10, 10,-10,QPen(QPen::darkBlue,2)));

  Lines.append(new Line(-30,  0,-14,  0,QPen(QPen::darkBlue,2)));
  Lines.append(new Line( 14,  0, 30,  0,QPen(QPen::darkBlue,2)));

  Ports.append(new Port(-30,  0));
  Ports.append(new Port( 30,  0));

  x1 = -30; y1 = -17;
  x2 =  30; y2 =  17;

  tx = x1+4;
  ty = y2+4;
  Sign  = "pshift";
  Model = "pshift";
  Name  = "X";

  Props.append(new Property("phi", "90", true, "phase shift in degree"));
  Props.append(new Property("Zref", "50 Ohm", false, "reference impedance"));
}

Phaseshifter::~Phaseshifter()
{
}

Phaseshifter* Phaseshifter::newOne()
{
  return new Phaseshifter();
}
