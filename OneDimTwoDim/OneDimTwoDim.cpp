/*======================================================================================================================

    Copyright 2011, 2012, 2013, 2014, 2015 Institut fuer Neuroinformatik, Ruhr-Universitaet Bochum, Germany

    This file is part of cedar.

    cedar is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the
    Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    cedar is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
    License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with cedar. If not, see <http://www.gnu.org/licenses/>.

========================================================================================================================

    Institute:   Ruhr-Universitaet Bochum
                 Institut fuer Neuroinformatik

    File:        EarSubscriber.h

    Maintainer:  Tutorial Writer Person
    Email:       cedar@ini.rub.de
    Date:        2011 12 09

    Description:

    Credits:

======================================================================================================================*/

// CEDAR INCLUDES
#include "OneDimTwoDim.h"
#include <cedar/processing/ExternalData.h> // getInputSlot() returns ExternalData
#include <cedar/auxiliaries/MatData.h> // this is the class MatData, used internally in this step
#include "cedar/auxiliaries/math/functions.h"
#include <cmath>
#include <iostream>

using namespace std;





// SYSTEM INCLUDES

//----------------------------------------------------------------------------------------------------------------------
// constructors and destructor
//----------------------------------------------------------------------------------------------------------------------
OneDimTwoDim::OneDimTwoDim()
:
cedar::proc::Step(true),
mOutput(new cedar::aux::MatData(cv::Mat::zeros(1, 100, CV_32F))),
mInputX(new cedar::aux::MatData(cv::Mat::zeros(10, 10, CV_32F)))
{
this->declareInput("1D", true);
this->declareOutput("2D",mOutput);

mGaussMatrixSizes.clear();
mGaussMatrixCenters.clear();
mGaussMatrixSigmas.clear();



valPeak = 0;

}
//----------------------------------------------------------------------------------------------------------------------
// methods
//----------------------------------------------------------------------------------------------------------------------
//
void OneDimTwoDim::compute(const cedar::proc::Arguments&)
{

  cv::Mat& field = mInputX->getData();
  cedar::aux::ConstDataPtr opX = this->getInputSlot("1D")->getData();
  field = opX->getData<cv::Mat>();

  mGaussMatrixSizes.clear();
  mGaussMatrixCenters.clear();

  cv::Size s = field.size();

  //getting the size of the future 2D matrix
  int size_twodim = static_cast<int>(sqrt(static_cast<float>(s.height)));

  maxX = 0;
  minX = s.height;

  //finding peak location within the 1D field

  for(int i = 0;i < s.height; i++ )
  {
     valPeak = field.at<float>(i,0);
     if(valPeak > 0.9)
     {
        if(i < minX)
        {
           minX = i;
        }
        if(i > maxX)
        {
           maxX = i;
        }
     }
  }

  posX = (static_cast<double>(minX) + static_cast<double>(maxX))/2;
  int x = static_cast<int>(posX);

  int new_posY = x/size_twodim;
  int new_posX = x - new_posY * size_twodim;

  //setting up the peak location in 2D space.
  mGaussMatrixSizes.push_back(size_twodim);
  mGaussMatrixSizes.push_back(size_twodim);
  mGaussMatrixCenters.push_back(new_posY);
  mGaussMatrixCenters.push_back(new_posX);
  mGaussMatrixSigmas.push_back(3.0);
  mGaussMatrixSigmas.push_back(3.0);

  this->mOutput->setData(cedar::aux::math::gaussMatrix(2,mGaussMatrixSizes,1.0,mGaussMatrixSigmas,mGaussMatrixCenters,false));


}

void OneDimTwoDim::reCompute()
{

}

void OneDimTwoDim::reName()
{

}

void OneDimTwoDim::reset()
{

	//ros::shutdown();

}
