/*
  October 2012

  aq32Plus Rev -

  Copyright (c) 2012 John Ihlein.  All rights reserved.

  Open Source STM32 Based Multicopter Controller Software

  Includes code and/or ideas from:

  1)AeroQuad
  2)BaseFlight
  3)CH Robotics
  4)MultiWii
  5)S.O.H. Madgwick
  6)UAVX

  Designed to run on the AQ32 Flight Control Board

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

///////////////////////////////////////////////////////////////////////////////

#include "board.h"

///////////////////////////////////////////////////////////////////////////////
// Coordinate Transformation Defines and Variables
///////////////////////////////////////////////////////////////////////////////

float earthAxisAccels[3] = { 0.0f, 0.0f, 0.0f };

float rotationMatrix[9];

///////////////////////////////////////////////////////////////////////////////
// Create Rotation Matrix
///////////////////////////////////////////////////////////////////////////////

void createRotationMatrix(void)
{
    rotationMatrix[0] = q0q0 + q1q1 -q2q2 - q3q3;

    rotationMatrix[1] = 2.0f * (q1q2 - q0q3);

    rotationMatrix[2] = 2.0f * (q0q2 + q1q3);

    rotationMatrix[3] = 2.0f * (q1q2 + q0q3);

    rotationMatrix[4] = q0q0 - q1q1 + q2q2 - q3q3;

    rotationMatrix[5] = 2.0f * (q2q3 - q0q1);

    rotationMatrix[6] = 2.0f * (q1q3 - q0q2);

    rotationMatrix[7] = 2.0f * (q0q1 + q2q3);

    rotationMatrix[8] = q0q0 - q1q1 - q2q2 + q3q3;
}

///////////////////////////////////////////////////////////////////////////////
// Rotate Body Accels to Earth Accels
///////////////////////////////////////////////////////////////////////////////

void bodyAccelToEarthAccel(void)
{
    matrixMultiply(3, 3, 1, earthAxisAccels, rotationMatrix, sensors.accel100Hz);

    earthAxisAccels[ZAXIS] += accelOneG;
}

///////////////////////////////////////////////////////////////////////////////




